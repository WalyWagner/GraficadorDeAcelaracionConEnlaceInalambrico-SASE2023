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

#include "mef_DeteccionTrama.h"

/*==================[internal data definition]==========================*/
static estMefDeteccionTrama_enum estMefDeteccionTrama;
static char trama[BYTES_TRAMA];
static int size;

/*==================[internal functions definition]==========================*/
static void mef_DeteccionTrama_procTrama(char *trama, int size) {													//subrutina encargada de procesar las tramas
	if((size >= strlen(ID_GRUPO)) && strncmp(ID_GRUPO, trama, strlen(ID_GRUPO))==0){	//se procesa el ID del grupo
		if(mefDeteccionTrama_ProcPeticion_procPeticion(trama, size)){													//se procesa la peticion
			dataTransfer_EnvDMA_RecRingBuff_envDatos(mefDeteccionTrama_ProcPeticion_get_bufferEnv(), strlen((char*)mefDeteccionTrama_ProcPeticion_get_bufferEnv()));//si el ID y peticion son validos, se envia la trama
		}
	}
}

static void mef_DeteccionTrama_limpiarTrama() {
	memset(trama, FIN_CADENA, sizeof(char) * BYTES_TRAMA);
	size = 0;
}

/*==================[external functions definition]==========================*/
void mefDeteccionTrama_init(){
	mefDeteccionTrama_reset();
}

void mefDeteccionTrama_reset(){
	estMefDeteccionTrama = ESPERANDO;
	mef_DeteccionTrama_limpiarTrama();
}

void mefDeteccionTrama() {
    uint8_t byteRec;
    uint32_t contByteRec = dataTransfer_EnvDMA_RecRingBuff_recDatos(&byteRec, sizeof(byteRec));

    switch (estMefDeteccionTrama) {
    	case ESPERANDO:
    		if (contByteRec && byteRec == BYTE_INICIO) {
    			trama[size++] = byteRec;
    			estMefDeteccionTrama = RECIBIENDO;
    		}
    		break;

    	case RECIBIENDO:
			if (contByteRec) {						//redundancia de seguridad
				switch (byteRec) {
					case BYTE_FIN:
						mef_DeteccionTrama_procTrama(trama, size);
						mef_DeteccionTrama_limpiarTrama();
						estMefDeteccionTrama = ESPERANDO;
						break;

					case BYTE_INICIO:
						mef_DeteccionTrama_limpiarTrama();
						trama[size++] = byteRec;
						break;

					default:
						if (size >= BYTES_TRAMA) {
							mef_DeteccionTrama_limpiarTrama();
							estMefDeteccionTrama = ESPERANDO;
						} else {
							trama[size++] = byteRec;
						}
				}
			}
			break;
	}
}

/*==================[end of file]============================================*/
