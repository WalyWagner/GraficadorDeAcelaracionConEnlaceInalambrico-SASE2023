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
 * **************************************************************************************************
 * Se reconoce la participación de Martín Pissia como co-autor de la primera versión de este código	*
 ****************************************************************************************************/
#ifndef _MEF_DETECCIONTRAMA_PROCPETICION_H_
#define _MEF_DETECCIONTRAMA_PROCPETICION_H_

/*==================[inclusions]=============================================*/
#include <dataTransfer/dataTransfer_EnvDMA_RecRingBuff.h>
#include <stdbool.h>
#include <math.h>
#include <onBoard/onBoard_General.h>
#include <onBoard/onBoard_Mma8451.h>
#include "pin_mux.h"
#include "MKL46Z4.h"

/*==================[cplusplus]==============================================*/
#ifdef __cplusplus
extern "C" {
#endif

/*==================[external functions definition]==========================*/
uint8_t* mefDeteccionTrama_ProcPeticion_get_bufferEnv();
bool mefDeteccionTrama_ProcPeticion_procPeticion(char *trama, int size);

/*==================[cplusplus]==============================================*/
#ifdef __cplusplus
}
#endif

/*==================[end of file]============================================*/
#endif /* _MEF_DETECCIONTRAMA_PROCPETICION_H_ */
