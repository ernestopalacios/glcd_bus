/**********************************************\
 *       Kradac Robotics & Electronics        *
 *                                            *
 *  Proyecto:     LIBRERIA SKYPATROL          *
 *  Programadores:  Ernesto P                 *
 *                  						  * 
 *  version:        0.1.0.0                   *
 *  Fecha:          31/08/2014                *
 *                                            *
 **********************************************
 *
 *  
 *  Libreria para las configuraciones del 
 *  GLCD Busses Loja
 *
 */

 /**
  * @filename: SkyPatrol_TT8750_plus.c
  * 
  * @detail: Archivo donde se alojan las configuraciones para la GLCD_DISPLAY 
  *          de los buses de la ciudad de Loja.
  *          
  */

 #ifndef SKYPATROL_TT8750_C
 #define SKYPATROL_TT8750_C


void prueba_ptr( char *ptr_caracteres ){

	printf("\r\nPUNTERO %s\n END", ptr_caracteres );
}


   //////////////// FUNCION PARA OBTENER LA TRAMA DEL GPS SKYPATROL+ ///////////////////////////
      void obtener_trama( char *ptr_TRAMA)
      {

         int i;                        // Contador de lazo FOR() buffer serial
         int n=0;                    //
         int ini;
         int coma=0;
         int pos1=0;
         int pos2=0;
         int pos3=0;
         int barras;
         

         char digito_hora_temp; //Variable temporal para la hora y fecha

         
         
         
         for (i=0; i<RX_BUFFER_SIZE0 ;i++) 
         {     
           
            // $$Txt,   Mensaje para mostrar en la GLCD.
            if ( ptr_TRAMA[i+0]== '$' &&    
                  ptr_TRAMA[i+1]== '$' &&     
                   ptr_TRAMA[i+2]== 'T' &&    
                    ptr_TRAMA[i+3]== 'x' &&  
                     ptr_TRAMA[i+4]== 't' &&
                      ptr_TRAMA[i+5]== ',')    
            {
               // Guarda lo que hay entre las comillas en el 
               // buffer txt_glcd
               i_txt_glcd = 0;

               // Se ha recibido una trama desde el SkyPatrol, se deben refrescar los
               // las banderas de desconexion
               conexion_skypatrol = 1; timer_sin_conexion = 0;
               i_timer_1 = 0;  


               do
               {
                  if (i_txt_glcd < TXT_BUF_SZ )
                  {

                     txt_glcd_b0[ i_txt_glcd ] = ptr_TRAMA[ i+6 + i_txt_glcd ]; 
                     i_txt_glcd++;
                     
                  }else{  // Mas de 100 caracteres recibidos. Romper el while

                     i_txt_overflow = 1;  //Legaron mas de 100 Caracteres
                     ptr_TRAMA[ i+6 + i_txt_glcd ] = ',';//Obliga a salir del while:
                  }

               }while( ptr_TRAMA[ i+6 + i_txt_glcd ] != ',' ); // Mientras el caracter no sea com

               pantalla = 7;          // Muestra en mensaje en main()
            }

            //+CSQ: 
            if ( ptr_TRAMA[i+0]== '+' &&    //43d
                  ptr_TRAMA[i+1]== 'C' &&     //67d
                   ptr_TRAMA[i+2]== 'S' &&    //83d
                    ptr_TRAMA[i+3]== 'Q' &&   //81d
                     ptr_TRAMA[i+4]== ':')    //58d
            { 
               
               // Se ha recibido una trama desde el SkyPatrol, se deben refrescar los
               // las banderas de desconexion
               conexion_skypatrol = 1; timer_sin_conexion = 0;
               i_timer_1 = 0;  
               

               // Valor decimal de la intensidad de la seÃ±al
               barras = ((ptr_TRAMA[i+6]-48)*10)+(ptr_TRAMA[i+7]-48);

               // Dibuja las barras en la panalla de acuerdo a la intensidad
               // de la senal
               if( barras > 10 && barras < 15 ){
                  ind_sen=1;
               }

               else if( barras >= 15 && barras < 18){
                  ind_sen=2;
               } 

               else if( barras >= 18 && barras < 31){
                  ind_sen=3;
               }

               else if( barras > 31 && barras < 50){
                  ind_sen=4;
               }

               // En caso de que el valor en barras
               // no sea ninguno de los anteriores, es posible
               // que la trama recibida no sea valida.
               else{  
                  ind_sen = 0;
               }

            }
           
           
              //________________________
             //PARA PUNTO DE CONTROL: 
            //por ahora detecto el encabezado "BUS" para tener de referencia en las posiciones del vector
            if ( ptr_TRAMA[i+0]== 'B' &&    
                  ptr_TRAMA[i+1]== 'U' &&     
                   ptr_TRAMA[i+2]== 'S')    
            { 
               
               // Se ha recibido una trama desde el SkyPatrol, se deben refrescar los
               // las banderas de desconexion
               conexion_skypatrol = 1; timer_sin_conexion = 0;
               i_timer_1 = 0;  
               

              // Datos de punto de control, en cada posicion del vector guardo una letra, luego hay que procesar para obtener el numero correcto. 
                                       //010A
               punto[0] = ptr_TRAMA[i+16]-48;  //   1 
               punto[1] = ptr_TRAMA[i+17]-48;  //   F
               punto[2] = ptr_TRAMA[i+18]-48;  //   0
               punto[3] = ptr_TRAMA[i+19]-48;  //   A
             
               if(punto[3]==17){
                  punto[3]=10;
               } 
              
               if(punto[0]>=17){
                  punto[0]=punto[0]-7;
               }

               if(punto[1]>=17){
                  punto[1]=punto[1]-7;
               }
                   
               //El 18 es el numero de evento, lo identifico para determinar si es geocerca, si esta bien se pone en 1 la variable "pantalla"
               if( ptr_TRAMA[i+22]=='1' &&  ptr_TRAMA[i+23]=='8'){
                  
                  pantalla = 1;
                 
                  unidades_ruta= (punto[2]*10) + punto[3];
                  decenas_ruta = (((punto[0]*16)-1)+ punto[1])*10; 
                  centenas_ruta=     unidades_ruta  +decenas_ruta;
                 
                  sprintf(no_pt,"P%d", centenas_ruta);     
               }
                 
            }

           
            //NETIP
            if ( ptr_TRAMA[i+0]== 'N' && 
                  ptr_TRAMA[i+1]== 'E' && 
                   ptr_TRAMA[i+2]== 'T' && 
                    ptr_TRAMA[i+3]== 'I' && 
                     ptr_TRAMA[i+4]== 'P')
            { 
               // Se ha recibido una trama desde el SkyPatrol, se deben refrescar los
               // las banderas de desconexion
               conexion_skypatrol = 1; timer_sin_conexion = 0;
               i_timer_1 = 0;  
               

               ini = i + 4; 

               for (n=0; n<201; n++) 
               {
                  // Busca el caracter ':'
                  if(ptr_TRAMA[ ini + n + 1 ] == ':' ) 
                  {
                     coma++; 
                     if(coma == 1) pos1 = n + ini + 1; // Guarda la posicion de la primera trama
                  }
               }
               
               // Verifica si despues del primer ':' Hay comillas
               if( ptr_TRAMA[ pos1 + 2] == 34 )
               {      
                  if( (ptr_TRAMA[pos1+3] - 48) == 0 && 
                      (ptr_TRAMA[pos1+4] - 48) == 0 && 
                      (ptr_TRAMA[pos1+5] - 48) == 0 && 
                      (ptr_TRAMA[pos1+7] - 48) == 0 && 
                      (ptr_TRAMA[pos1+8] - 48) == 0 && 
                      (ptr_TRAMA[pos1+9] - 48) == 0)
                  { 
                     gsm=0;   // Sin senal GSM
                  
                  }else
                     gsm=1;
               }   
            }
           
            //DEVID
            if ( ptr_TRAMA[i+0] == 'D' && 
                  ptr_TRAMA[i+1] == 'E' && 
                   ptr_TRAMA[i+2] == 'V' && 
                    ptr_TRAMA[i+3] == 'I' && 
                     ptr_TRAMA[i+4] == 'D')
            { 
               
               // Se ha recibido una trama desde el SkyPatrol, se deben refrescar los
               // las banderas de desconexion
               conexion_skypatrol = 1; timer_sin_conexion = 0;
               i_timer_1 = 0;  
               

               ini = i+4; 
               
               for (n=0;n<201;n++)
               {
                  if( ptr_TRAMA[ini+n+1] == ':') 
                  {
                     coma++; 
                     if(coma==1) pos1 = n+ini+1;
                  }
               }

               //Comprobar nombre      
               if(ptr_TRAMA[pos1+1]==34)
               { 
                  if( ptr_TRAMA[pos1+2] == NUM_DISP[0] && 
                      ptr_TRAMA[pos1+3] == NUM_DISP[1] && 
                      ptr_TRAMA[pos1+4] == NUM_DISP[2] && 
                      ptr_TRAMA[pos1+5] == NUM_DISP[3] )
                  {
                  
                  act=1;  // PANTALLA Y EQUIPO CORRECTA !!!
                  
                  }
                  else {
                     
                  act=1;  // PANTALLA INCORRECTA !!!
                  }
                              
               }
            }
           
            //Encabezado: GPRMC para igualar el reloj desde trama GPS
            if ( ptr_TRAMA[i+0] == 'G' && 
                  ptr_TRAMA[i+1] == 'P' && 
                   ptr_TRAMA[i+2] == 'R' && 
                    ptr_TRAMA[i+3] == 'M' && 
                     ptr_TRAMA[i+4] == 'C')
            { 
            
               // Se ha recibido una trama desde el SkyPatrol, se deben refrescar los
               // las banderas de desconexion
               conexion_skypatrol = 1; timer_sin_conexion = 0;
               i_timer_1 = 0;  
               
               ini=i+4;
               for (n=0;n<201;n++) 
               {
                  if(ptr_TRAMA[ini+n+1]==44) 
                  {
                     coma++;
                     if(coma==1) pos1=n+ini+1;
                     if(coma==2) pos2=n+ini+1;
                     if(coma==9) pos3=n+ini+1;
                  }
               }
               
                              
               // Comprueba que las comas no esten seguidas
               // en caso de no haber senial gps.
               if( (ptr_TRAMA[ pos1+1 ]-48) >= 0 && 
                    (ptr_TRAMA[ pos1+1 ]-48) < 10 &&
                     pos2 != (pos1 +1)             )
               {
           
                  digito_hora_temp = ptr_TRAMA[pos1 + 6 ] - 48;
                  if ( digito_hora_temp >= 0 && digito_hora_temp <= 9)
                     _seg = digito_hora_temp;

                  digito_hora_temp = ptr_TRAMA[pos1 + 5 ] - 48;
                  if ( digito_hora_temp >= 0 && digito_hora_temp <= 9)
                     _seg1 = digito_hora_temp;

                  digito_hora_temp = ptr_TRAMA[pos1 + 4 ] - 48;
                  if ( digito_hora_temp >= 0 && digito_hora_temp <= 9)
                     _minu = digito_hora_temp;

                  digito_hora_temp = ptr_TRAMA[pos1 + 3 ] - 48;
                  if ( digito_hora_temp >= 0 && digito_hora_temp <= 9)
                     _min1  = digito_hora_temp;

                  digito_hora_temp = ptr_TRAMA[pos1 + 2 ] - 48;
                  if ( digito_hora_temp >= 0 && digito_hora_temp <= 9)
                     _hora = digito_hora_temp;

                  digito_hora_temp = ptr_TRAMA[pos1 + 1 ] - 48;
                  if ( digito_hora_temp >= 0 && digito_hora_temp <= 9)
                     _hora1  = digito_hora_temp;
                   
                  RelojGPS.segu = _seg + (10 * _seg1 );
                  RelojGPS.minu = _minu + (10 * _min1 );
                  RelojGPS.hora = _hora + (10 * _hora1 );

               }
          
               // Comprueva la conexión de GPS
               gps = ptr_TRAMA [ pos2 + 1 ]; 
               
               //Obtener Hora y dia
               if( (ptr_TRAMA[pos3+1]-48) >= 0 && 
                    (ptr_TRAMA[pos3+1]-48) < 10 )
               {
              
                  _dia1 = ptr_TRAMA[pos3+1]-48;
                  _dia  = ptr_TRAMA[pos3+2]-48;
                  _mes1 = ptr_TRAMA[pos3+3]-48;
                  _mes  = ptr_TRAMA[pos3+4]-48;
                  _an1  = ptr_TRAMA[pos3+5]-48;
                  _an   = ptr_TRAMA[pos3+6]-48;  

                  RelojGPS.dia = _dia + (10*_dia1);
                  RelojGPS.mes = _mes + (10*_mes1);
                  RelojGPS.an = _an  + (10*_an1);
                  RelojGPS.anio = (long)RelojGPS.an + 2000;
                  
                  // Solo asigna la hora al display si es
                  if( esDiaValido( RelojGPS ) && esTiempoValido( RelojGPS ) )
                  {
                     Reloj = TiempoEcuador(RelojGPS);
                     //Reloj = RelojGPS;
                  }

                  
               }else{

                // No actualizar la hora, continuar con la anterior
               }
            }
         }
          
         rx_counter0  = 0;
         rx_wr_index0 = 0; 
          
         BIT_UART=1;     
         
         // Limpia el buffer
         for( i=0; i<RX_BUFFER_SIZE0; i++ ) 
         {
            ptr_TRAMA[i]=0;
         }
      }
   //---------------------------------------------------------------------------------------------//


  
 #endif
