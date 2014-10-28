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

int hora_correcta( int hora, int minu, int seg )
{
	if ( hora >= 0 && hora < 23)
	{
		if (minu >= 0 && minu < 59)
		{
			if ( seg >= 0 && seg	< 59 )
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
