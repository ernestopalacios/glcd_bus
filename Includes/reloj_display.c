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


// determina si un año es bisiesto
#define isleapyear( year ) (( year % 4 == 0) && !(year % 100 == 0 && year % 400 != 0) )
		
// Estructira de datos para la Hora y Fecha del PLC
   typedef struct {
      int  dia;       
      int  mes;
      long anio;          // Fecha del anio con miles:  2014
      int  an;           // Dos ultimos digitos del anio 14 -> 2014
      int  hora; 
      int  minu;
      int  segu;
      int  dayWeek;
   } Tiempo;  //Fecha Interno del logo


/// Valida las horas
int esHoraValida( int hora, int minu, int seg )
{
	if ( hora >= 0 && hora <= 23)
	{
		if (minu >= 0 && minu <= 59)
		{
			if ( seg >= 0 && seg <= 59 )
			{
				return 1;
			
			}else{
				return 0;
			}
		}else{
			return 0;
		}
	}else{
		return 0;
	}
}


/// Valida la hora en una estructura de tiempo.
int esTiempoValido( Tiempo Reloj )
{
	if ( Reloj.hora >= 0 && Reloj.hora <= 23)
	{
		if ( Reloj.minu >= 0 && Reloj.minu <= 59)
		{
			if ( Reloj.segu >= 0 && Reloj.segu	<= 59 )
			{
				return 1;
			
			}else{
				return 0;
			}
		}else{
			return 0;
		}
	}else{
		return 0;
	}
}

//
//   Comprueba que la fecha sea correcta, devuleve 1 si lo es 0 si no
//
int esFechaValida(int mes, int dia, unsigned long anio)
{
  if (dia <= 0) return 0 ;
  switch( mes )
   {
     case 1  :
     case 3  :
     case 5  :
     case 7  :
     case 8  :
     case 10 :
     case 12 : if (dia > 31) return 0 ; else return 1 ;
     case 4  :
     case 6  :
     case 9  :
     case 11 : if (dia > 30) return 0 ; else return 1 ;
     case 2  : 
       if ( dia > 29 ) return 0 ;
       if ( dia < 29 ) return 1 ;
       if (isleapyear(anio)) return 1 ;   // anio bisiesto
    else return 0 ;
   }
  return 0 ;
}


/// Comprueba la fecha valida en  Una estructura de Tiempo
int esDiaValido( Tiempo Fecha)
{
  if ( Fecha.dia <= 0) return 0 ;
  switch( Fecha.mes )
   {
     case 1  :
     case 3  :
     case 5  :
     case 7  :
     case 8  :
     case 10 :
     case 12 : if ( Fecha.dia > 31) return 0 ; else return 1 ;
     case 4  :
     case 6  :
     case 9  :
     case 11 : if ( Fecha.dia > 30) return 0 ; else return 1 ;
     case 2  : 
       if ( Fecha.dia > 29 ) return 0 ;
       if ( Fecha.dia < 29 ) return 1 ;
       if (isleapyear(Fecha.anio)) return 1 ;   // anio bisiesto
    else return 0 ;
   }
  return 0 ;
}


// Restar Horas del UTC
int descontarUTC( int _hora, int _dia, int _mes, int _an )
{
	
	if ( _hora <= 5 )   // Las primeras cuatro horas del dia
	{
	  	_hora += 24;   // Agregarle un dia
	  	_hora -=  5;  // Restarle las 5 horas de ECU-UTC

		if ( _dia == 1) // Si tambien es el primer dia del mes
		{
		 	if ( _mes == 1 )  //Ajuste para el 01 Enero de cualquier anio
		 	{
		 	   _an--; // Regresar al anio anterior por las siguientes 5 horas
		 	   _mes = 12;   //Diciembre
		 	   _dia = 31;   //31
		 	}
		 	else if ( _mes == 3 ) // Si es marzo y debe volver a febrero
		 	{
		 	   
		 		if ( isleapyear( _an + 2000 ) ) // SI es anio bisiesto
		 			_dia = 29;
		 		else
		 	   		_dia = 28;
		 	   
		 	   _mes = 2;
		 	}
		 	
		 	else 
		 	{
		 		_mes--;     // Regresa un mes
		 		
		 		// Diferencia si el dia anterior es 30 o 31
		 		switch( _mes )
		 		{
		 		 	case 1  :
		 		 	case 3  :
    				case 5  :
    				case 7  :
    				case 8  :
    				case 10 : _dia = 31;
    				case 4  :
    				case 6  :
    				case 9  :
    				case 11 : _dia = 30;
		 		}
		    }

		}else _dia--; // Cualquier otro dia del mes
	  	
	
	}else _hora -= 5; // Si no necesita regresarse un dia simplemente resta cinco horas

	// Comprueba que la hora sea la adecuada
	if ( _hora < 24 && esFechaValida( _mes, _dia, _an+2000 ) )
	{
		return 1;
	  
	}else{

	  	return 0;
	}
}

// Restar Horas del UTC
Tiempo TiempoEcuador( Tiempo GPS )
{
	Tiempo Original;

	if ( GPS.hora <= 5 )   // Las primeras cuatro horas del dia
	{
	  	GPS.hora += 24;   // Agregarle un dia
	  	GPS.hora -=  5;  // Restarle las 5 horas de ECU-UTC

		if ( GPS.dia == 1) // Si tambien es el primer dia del mes
		{
		 	if ( GPS.mes == 1 )  //Ajuste para el 01 Enero de cualquier anio
		 	{
		 	   GPS.an--; // Regresar al anio anterior por las siguientes 5 horas
		 	   GPS.mes = 12;   //Diciembre
		 	   GPS.dia = 31;   //31
		 	}
		 	else if ( GPS.mes == 3 ) // Si es marzo y debe volver a febrero
		 	{
		 	   
		 		if ( isleapyear( GPS.anio ) ) // SI es anio bisiesto
		 			GPS.dia = 29;
		 		else
		 			GPS.dia = 28;
		 	   	
		 	    GPS.mes = 2;
		 	}

		 	else 
		 	{
		 		GPS.mes--;     // Regresa un mes
		 		
		 		// Diferencia si el dia anterior es 30 o 31
		 		switch( GPS.mes )
		 		{
		 		 	case 1  :
		 		 	case 3  :
    				case 5  :
    				case 7  :
    				case 8  :
    				case 10 : 
    					GPS.dia = 31;
    				break;

    				case 4  :
    				case 6  :
    				case 9  :
    				case 11 : 
    					GPS.dia = 30;
    				break;
		 		}
		    }

		}else GPS.dia--; // Cualquier otro dia del mes
	  	
	
	}else GPS.hora -= 5; // Si no necesita regresarse un dia simplemente resta cinco horas
	

	// Comprueba que la hora sea la adecuada
	if ( esTiempoValido( GPS ) && esDiaValido( GPS ))
	
		return GPS;
	else
	  	return Original; //Devulve sin alterar
	
}
