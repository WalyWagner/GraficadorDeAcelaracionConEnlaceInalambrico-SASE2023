/* Copyright 2017, DSI FCEIA UNR - Sistemas Digitales 2
 *    DSI: http://www.dsi.fceia.unr.edu.ar/
 * Copyright 2017, Diego Alegrechi
 * Copyright 2017, Gustavo Muro
 * Copyright 2023, Walter Wagner => wagner@fceia.unr.edu.ar
 *
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions are met:
 *
 * 1. Redistributions of source code must retain the above copyright notice,
 *    this list of conditions and the following disclaimer.
 *
 * 2. Redistributions in binary form must reproduce the above copyright notice,
 *    this list of conditions and the following disclaimer in the documentation
 *    and/or other materials provided with the distribution.
 *
 * 3. Neither the name of the copyright holder nor the names of its
 *    contributors may be used to endorse or promote products derived from this
 *    software without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
 * AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
 * ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE
 * LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR
 * CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF
 * SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS
 * INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN
 * CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE)
 * ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
 * POSSIBILITY OF SUCH DAMAGE.
 */

#include <EnvRec_DATOS/UART_RingBuffer_DMA.h>

/*==================[macros and definitions]=================================*/
#define UART1_TX_DMA_CHANNEL 0U
#define TX_BUFFER_DMA_SIZE  64

/*==================[internal data declaration]==============================*/
static uint8_t txBuffer_dma[TX_BUFFER_DMA_SIZE];
static uart_dma_handle_t UART1DmaHandle;
static dma_handle_t UART1TxDmaHandle;
volatile bool txOnGoing = false;
static void* pRingBufferRx;

/*==================[internal functions declaration]=========================*/

/* UART1 user callback */
static void UART_UserCallback(UART_Type *base, uart_dma_handle_t *handle, status_t status, void *userData)
{
    if (kStatus_UART_TxIdle == status)
    {
        txOnGoing = false;
    }
}

void UART_RingBuffer_DMA_init(void)
{
	uart_config_t config;

    pRingBufferRx = ringBuffer_init(TX_BUFFER_DMA_SIZE); //crea cola circular de 64 Bytes

	UART_GetDefaultConfig(&config);		//config UART1 para encapsular datos con la estructura 8N1
	config.baudRate_Bps = 9600;			//setea Baud Rate
	config.enableTx = true;				//habilita Tx
	config.enableRx = true;				//habilita Rx

	//Inicialización de la UART1 con la configuración establecida y la frecuencia de clock del bus clock (UART1 opera exclusivamente con bus clock)
	UART_Init(UART1, &config, CLOCK_GetFreq(kCLOCK_BusClk));

	//Habilitacion de interrupciones
    UART_EnableInterrupts(UART1, kUART_RxDataRegFullInterruptEnable); 	//Habilitación de interrupciones en la UART1 por Buffer Rx lleno

    //Habilitación de interrupciones en la UART1 por OR, interrupción que será util en caso que esto ocurra para volver a habilitar Rx
    UART_EnableInterrupts(UART1, kUART_RxOverrunInterruptEnable);

    NVIC_EnableIRQ(UART1_IRQn); 	//Habilitación de interrupción en NVIC por pedido de UART1
    //NVIC_SetPriority(UART1_IRQn,0);

	/* CONFIGURACIÓN DMA (sólo para TX) */
	/* Init DMAMUX */
	DMAMUX_Init(DMAMUX0);

	/* Set channel for UART1  */
	DMAMUX_SetSource(DMAMUX0, UART1_TX_DMA_CHANNEL, kDmaRequestMux0UART1Tx);	//seleccion de fuente de request para DMA
	DMAMUX_EnableChannel(DMAMUX0, UART1_TX_DMA_CHANNEL);						//seleccion de fuente de informacion para DMA (canal 0)

	/* Init the DMA module */
	DMA_Init(DMA0);
	DMA_CreateHandle(&UART1TxDmaHandle, DMA0, UART1_TX_DMA_CHANNEL);

	/* Create UART1 DMA handle. */
	UART_TransferCreateHandleDMA(UART1,&UART1DmaHandle,UART_UserCallback,NULL,&UART1TxDmaHandle,NULL);
}

int32_t UART_RingBuffer_recDatos(uint8_t *pBuf, int32_t size)
{
    int32_t ret = 0;

    //Deshabilita interupción por la UART1 momentáneamente para asegurar la integridad de los datos en la cola circular
    DisableIRQ(UART1_IRQn);

    //Deshabilitacion de IRQ mma8451 (lentas), se evita perder datos que llegan por UART1 y error por OverRun (que genera detencion en la recepcion de datos)
    DisableIRQ(PORTC_PORTD_IRQn);

    while (!ringBuffer_isEmpty(pRingBufferRx) && ret < size)
    {
        ringBuffer_getData(pRingBufferRx, &pBuf[ret]);
        ret++;
    }
    EnableIRQ(UART1_IRQn); 			//habilita interrupción del procesador por la UART1
    EnableIRQ(PORTC_PORTD_IRQn);	//habilita nuevamente responder a interrupciones pedidas por el acelerómetro
    return ret;
}

int32_t UART_DMA_envDatos(uint8_t *pBuf, int32_t size)
{
	uart_transfer_t xfer;

    if (txOnGoing) {
        size = 0;
    }
    else {
        /* Limita size */
        if (size > TX_BUFFER_DMA_SIZE) size = TX_BUFFER_DMA_SIZE;

        // Hace copia del buffer a transmitir en otro arreglo para garantizar que el dato a transmitir es el deseado
        //(dado que podría haberse almacenado otro dato en la dirección de memoria que apunta pBuf)
        memcpy(txBuffer_dma, pBuf, size);

        xfer.data = txBuffer_dma;
        xfer.dataSize = size;

        board_Tx_Rx_485_Enable(Tx);		//habilita transmision en el módulo RS485 y deshabilita recepcion

        /* Se inicia la transferencia del dato desde memoria hacia UART1 via DMA */
        txOnGoing = true;
        UART_TransferSendDMA(UART1, &UART1DmaHandle, &xfer);
        UART_EnableInterrupts(UART1, kUART_TransmissionCompleteInterruptEnable); //Se habilita interrupción en UART1 cuando la transferencia de datos este completa
    }
    return size;
}

void UART1_IRQHandler(void)
{
	uint8_t data;
    if ( (kUART_RxDataRegFullFlag)            & UART_GetStatusFlags(UART1) &&
         (kUART_RxDataRegFullInterruptEnable) & UART_GetEnabledInterrupts(UART1) )
	{
        /* obtiene dato recibido por puerto serie */
	    data = UART_ReadByte(UART1);

		/* pone dato en ring buffer */
		ringBuffer_putData(pRingBufferRx, data);
	}
    if ( (kUART_RxOverrunFlag)            & UART_GetStatusFlags(UART1) &&
         (kUART_RxOverrunInterruptEnable) & UART_GetEnabledInterrupts(UART1) )
	{
        /* obtiene dato recibido por puerto serie */
	    data = UART_ReadByte(UART1);
		/* pone dato en ring buffer */
		ringBuffer_putData(pRingBufferRx, data);
		/* Se limpia la bandera de overrun para que el Rx continue funcionando*/
		UART_ClearStatusFlags(UART1, kUART_RxOverrunFlag);
	}
	if ( (kUART_TransmissionCompleteFlag)            & UART_GetStatusFlags(UART1) &&
         (kUART_TransmissionCompleteInterruptEnable) & UART_GetEnabledInterrupts(UART1) )
	{
		board_Tx_Rx_485_Enable(Rx);													//Se habilita la recepción en el módulo RS485
        UART_DisableInterrupts(UART1, kUART_TransmissionCompleteInterruptEnable);	//se deshabilita la transmisión, no interesa escuchar lo que se envía
        UART_ClearStatusFlags(UART1, kUART_TransmissionCompleteFlag);				//se limpia bandera transmision completa
	}
}

/*==================[end of file]============================================*/
