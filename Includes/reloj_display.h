/**********************************************\
 *       Kradac Robotics & Electronics        *
 *                                            *
 *  Proyecto:       GLCD BUS LOJA             *
 *  Programadores:  Ernesto P &&              *
 *  version:        0.1.0.0                   *
 *  Fecha:          28/10/2014                *
 *                                            *
 **********************************************
 *
 *  
 *  LIBRERIA PARA EL MANEJO DE TIEMPO
 *  
 *  Compilador:   Compilador C Generico
 *  
 *
 */


#ifndef RELOJ_DISPLAY_H
#define RELOJ_DISPLAY_H

#include "Includes/reloj_display.c"

/**
 * @brief Verifica si la hora enviada es correcta
 * @details Devuelve uno si la hora enviada es una hora valida
 * 
 * @param hora Hora a probar 0-23
 * @param minu Minuto a probar 0-59
 * @param seg Segundo a probar 0-59
 * @return 1 Correcto 0 Incorrecto
 */
int hora_correcta( int hora, int minu, int seg );


#endif  