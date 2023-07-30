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

#ifndef MEF_DETECCIONTRAMA_H_
#define MEF_DETECCIONTRAMA_H_

/*==================[inclusions]=============================================*/
#include <mef/mef_DeteccionTrama_ProcPeticion.h>
#include <MKL46Z4.h>

/*==================[cplusplus]==============================================*/
#ifdef __cplusplus
extern "C" {
#endif

/*==================[macros]=================================================*/
#define BYTES_TRAMA			8
#define BYTE_INICIO			':'
#define BYTE_FIN			0x0A
#define FIN_CADENA			'\0'
#define ID_GRUPO			":08"

/*==================[typedef]================================================*/
typedef enum {
	ESPERANDO = 0,
	RECIBIENDO ,
} estMefDeteccionTrama_enum;


/*==================[external functions definition]==========================*/
void mefDeteccionTrama_reset();
void mefDeteccionTrama_init();
void mefDeteccionTrama();

/*==================[cplusplus]==============================================*/
#ifdef __cplusplus
}
#endif

/*==================[end of file]============================================*/
#endif /* MEF_DETECCIONTRAMA_H_ */
