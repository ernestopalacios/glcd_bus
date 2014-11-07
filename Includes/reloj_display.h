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
int esTiempoValido( struct Tiempo Reloj );


/**
 * @brief Esta funcion devuelve 1 si la fecha es valida, 0 si no lo es
 * @details Verifica si la fecha es correcta, tomando en cuenta los dias de Feberero y el anio bisiesto
 * 
 * @param mes Mes del anio entre 01 y 12
 * @param dia dia del mes entre 01 y 31
 * @param anio Anio contando los miles, es decir 2013 
 * @return 1 si es valida la fecha, 0 si no lo es
 */
int esFechaValida(int mes, int dia, unsigned long anio);


/**
 * @brief Verifica que la fecha sea valida para una estructura Tiempo
 * @details Utilizando las variables de la estructura comprueba que contenga una fecha valida
 * 
 * @param Fecha Estructura de Tiempo a comprobar
 * @return 1 Si la fecha es valida 0 si no lo es
 */
int esDiaValido( struct Tiempo Fecha);


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
int descontarUTC( int _hora, int _dia, int _mes, int _an );


/**
 * @brief Descuenta las 5 horas de Ecuador a la estrucutra de tiempo pasada
 * @details En el caso de que la operacion de una hora o fecha invalida no realiza la operacion
 * 
 * @param Tiempo Puntero a la estructura de tiempo a la cual restar 5 horas
 * @return 1 si la operacion fue completada con exito, 0 en caso contrario
 */
int TiempoEcuador( struct Tiempo * GPS );

#endif  