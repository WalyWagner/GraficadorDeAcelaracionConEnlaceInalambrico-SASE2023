/****************************************************************************************************
 *************************GRAFICADOR DE ACELERACIÓN CON ENLACE INALÁMBRICO***************************
 ***************************Simposio Argentino de Sistemas Embebidos 2023****************************
 ****************************************************************************************************
 ***************************************************************************WsS**********************
 *************************************************************************Copyright 2023*************
 ****************************************************************************************************
 * La documentación de este proyecto se acompaña en la carpeta raíz de mismo						*
 * Autor de la presente implementación: WALTER SEBASTIAN WAGNER               					 	*
 * Correo Electrónico: wagner@fceia.unr.edu.ar                           						 	*
 * Docente tutor: Ing. Gustavo Muro																	*
 * Correo Electrónico: gmuro@fceia.unr.edu.ar														*
 * Fecha última modificación: 31/07/2023                                         				 	*
 *                                                                       						 	*
 * Institución: UNIVERSIDAD NACIONAL DE ROSARIO                          							*
 * Dependencia: Facultad de Ciencias Exactas, Ingeniería y Agrimensura   							*
 * Escuela: Ingeniería Electrónica                                             						*
 * Departamento: Sistemas e Informática                                              				*
 * Cátedra: Sistemas Digitales 2                                                  					*
 * 																									*
 * Este código está protegido por los derechos de autor y copyright      							*
 * aplicables. Por favor, consulte el archivo ReadMe.txt que acompaña    							*
 * a este archivo para ver los términos de la licencia correspondiente.   							*
 ****************************************************************************************************/

#include <stdio.h>
#include <mef/mef_Modo.h>

int main(void){

	Board_init();									//Inicializa periféricos
	UART_RingBuffer_DMA_init();						//Inicializa UART+DMA y crea el Buffer Circular
	mefModo_init();									//Inicializa la Máquina de Estados Finitos (MEF)
	SysTick_Config(SystemCoreClock / 1000U); 		//Inicializa interrupción de systick cada 1 ms

    while(1){
    	mefModo();									//Polling sobre la MEF
    }
}

void SysTick_Handler(void) {						//El SysTick interrumpe cada 1ms
	key_periodicTask1ms();
	mefModo_task1ms();
}

/*==========================================[end of file]==========================================*/
