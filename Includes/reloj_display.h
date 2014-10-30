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
int esHoraValida( int hora, int minu, int seg );


/**
 * @brief Valida que la Hora sea valida en una estructura de tiempo
 * @details Verifica que las estructura de tiempo contenga una hora valida
 * 
 * @param Reloj Puntero a la estructura de tiempo
 * @return 1 si es valida 0 si no es valida
 */
int esTiempoValido( Tiempo Reloj );

/**@brief: 
 * Esta funcion devuelve 1, si la fecha es valida, caso contrario 
 * devuelve 0, por ejemplo:
 *
 * Mes Febrero: 02
 * día        : 29
 * Anio       : 2013      Retorna 0
 *
 * Tambien toma en cuenta si es anio bisiesto.
 *
 */
int esFechaValida(int mes, int dia, unsigned long an);


/**
 * @brief Rectifica a la hora local del Ecuador
 * @details Cambia la hora tipo UTC que envia el GPS para ajustarla a la hora local -5 de Ecuador
 * 
 * @param hora Puntero a la hora en UTC
 * @param minu Puntero a los minutos en UTC
 * @param seg Puntero a los segundos en UTC
 * @param dia Puntero al dia en UTC
 * @param mes Puntero al mes
 * @param an Puntero al anio en formato 20xx, solo dos ultimos digitos	
 * @return 1 Operacion valida 0 Sin cambios.
 */
int descontarUTC( int* hora, int* minu, int* seg, int* dia, int* mes, int* an );


#endif  