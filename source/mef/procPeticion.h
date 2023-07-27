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
#ifndef PROCPETICION_H_
#define PROCPETICION_H_

/*==================[inclusions]=============================================*/
#include <EnvRec_DATOS/UART_RingBuffer_DMA.h>
#include <stdbool.h>
#include <math.h>
#include <onBoard_KL46/SD2_Mma8451.h>
#include <onBoard_KL46/SD2_Board.h>

#include "pin_mux.h"
#include "MKL46Z4.h"

/*==================[cplusplus]==============================================*/
#ifdef __cplusplus
extern "C" {
#endif

/*==================[typedef]================================================*/
typedef union {
	struct {
		char initChar;
		char teamCode[2];
		char actionType;
		char actionCode[2];
	};
	char data[6];
}tramaData;

/*==================[internal functions definition]==========================*/
void Acel();
void Switch();
void Leds();


/*==================[external functions definition]==========================*/
uint8_t* get_bufferEnv();
bool procPeticion(char *trama, int size);

/*==================[cplusplus]==============================================*/
#ifdef __cplusplus
}
#endif

/*==================[end of file]============================================*/
#endif /* PROCPETICION_H_ */
