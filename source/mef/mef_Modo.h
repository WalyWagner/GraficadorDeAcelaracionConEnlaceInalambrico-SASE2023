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

#ifndef MEF_MODO_H_
#define MEF_MODO_H_

/*==================[inclusions]=============================================*/
#include <mef/mef_DeteccionTrama.h>
#include <mef/mef_plot3D.h>
#include <offBoard_KL46/Oled/oled.h>
#include <onBoard_KL46/SD2_board.h>
#include <onBoard_KL46/SD2_LCD_I2C.h>
#include <onBoard_KL46/SD2_SwitchsAndLeds.h>

/*==================[cplusplus]==============================================*/
#ifdef __cplusplus
extern "C" {
#endif

/*==================[macros]=================================================*/
#define MEF_DETECCION_TRAMA	"SD2 TP3 Master"
#define MEF_PLOT_3D			"Plot 3D"

/*==================[typedef]================================================*/
typedef enum {
	EST_DETECCION_TRAMA = 0,
	EST_PLOT_3D,
} estMefModo_enum;

/*==================[external functions definition]==========================*/
void mefModo_init();
void mefModo();
void mefModo_task1ms();

/*==================[cplusplus]==============================================*/
#ifdef __cplusplus
}
#endif

/*==================[end of file]============================================*/
#endif /* MEF_MODO_H_ */
