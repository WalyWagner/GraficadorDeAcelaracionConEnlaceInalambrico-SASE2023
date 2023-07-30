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

/*==================[inclusions]=============================================*/
#include <onBoard/onBoard_UART_forDataTransfer.h>


/*==================[external functions definition]==========================*/
void onBoard_UART_forDataTransfer_Init(void){ //Inicializa UART1 para transferencia de datos por RF o RS485
	//IMPORTANTE: Si bien el proyecto trabaja con módulos para establecer comunicación RF
	//Sigue estando disponible la posibilidad de comunicarse con los módulos RS485, simplemente es conectar plug&play
	onBoard_UART_forDataTransfer_TxRx485_Enable(Rx);

	/* PORTE0 (pin 1) is configured as UART1_TX */
	PORT_SetPinMux(PORTE, 0U, kPORT_MuxAlt3);

	/* PORTE1 (pin 2) is configured as UART1_RX */
	PORT_SetPinMux(PORTE, 1U, kPORT_MuxAlt3);

	/* Selección de fuente Tx/Rx para la uart1 */
    SIM->SOPT5 = ((SIM->SOPT5 &
                  /* Mask bits to zero which are setting */
                  (~(SIM_SOPT5_UART1TXSRC_MASK | SIM_SOPT5_UART1RXSRC_MASK)))

                  /* UART1 Transmit Data Source Select: UART1_TX pin. */
                  | SIM_SOPT5_UART1TXSRC(SOPT5_UART1TXSRC_UART_TX)

                  /* UART1 Receive Data Source Select: UART1_RX pin. */
                  | SIM_SOPT5_UART1RXSRC(SOPT5_UART1RXSRC_UART_RX));
}

void onBoard_UART_forDataTransfer_TxRx485_Enable(board_RxTx_enum dato)
{
	if(dato) 		//Habilitación del modulo Tx RS-485 y deshabilitación del Rx
	{
		GPIO_PortSet(GPIOA, 1<<16);
		GPIO_PortSet(GPIOA, 1<<17);
	}
	else 			//Habilitación del módulo Rx RS-485 y deshabilitación del Tx
	{
		GPIO_PortClear(GPIOA, 1<<16);
		GPIO_PortClear(GPIOA, 1<<17);

	}
}
/*==================[end of file]============================================*/
