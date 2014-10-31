/**********************************************\
 *       Kradac Robotics & Electronics        *
 *                                            *
 *  Proyecto:       GLCD BUS LOJA             *
 *  Programadores:  Vicente Q &&              *
 *                  Ernesto P &&              *
 *                  David Novillo             *
 *                  Jeferson C                *
 *  version:        0.9.6.2                   *
 *  Fecha:          11/08/2014                *
 *                                            *
 **********************************************
 *
 *  
 *  uC:             ATmega324PA
 *  Compilador:     CodeVision 2.x
 *  Cryst:          11.092 MHz
 *  
 *
 */               

//////////////////  SE AGREGAN LAS LIBRERIAS QUE SE VAN A UTILIZAR ////////////////////
#include <mega324.h>
#include <delay.h>
#include <stdio.h>
#include <stdlib.h>
#include "Includes/GLCD.h"
#include "Includes/bus.h"
#include "Includes/reloj_display.h"
#include "Includes/GLCD_CONFIG.c"
#include "Includes/SkyPatrol_TT8750_plus.c"

 

////////////////////////////  RUTINA DE INTERRUPCION SERIAL   ////////////////////////////
/** \brief USART0 Receiver interrupt service routine
 *
 * Captura datos desde el puerto serial UART0
 */
   interrupt [USART0_RXC] void usart0_rx_isr(void)
   {  
      char status,data;
      status = UCSR0A;
      data   = UDR0;
      BIT_UART = UCSR0A & 0b10000000;

      if ((status & (FRAMING_ERROR | PARITY_ERROR | DATA_OVERRUN)) == 0)
      {
         rx_b0 [rx_wr_index0++] = data;
         #if RX_BUFFER_SIZE0 == 256
            // special case for receiver buffer size=256
            if (++rx_counter0 == 0) rx_buffer_overflow0=1;   
         
         #else
            if (rx_wr_index0 == RX_BUFFER_SIZE0) rx_wr_index0=0;
            if (++rx_counter0 == RX_BUFFER_SIZE0)
            {
               rx_counter0=0;
               rx_buffer_overflow0=1;
            }
         #endif
      }
   }
//-----------------------------------------------------------------------------------------


/////////////////////////////////////////////// INTERRUPCION DEL TIMER0 (CUENTA CADA SEGUNDO) /////////////////////////////////////////////////
interrupt [TIM0_OVF] void timer0_ovf_isr(void)
{
   TCNT0 = 6; 
   ++time_count; 
   
   if ( time_count == 43 )  
   {
      time_count = 0;  //reiniciar contador
      
      Reloj.segu++;              // Aumenta Segundos
      timer_sin_conexion++;      // Aumenta Segundos Sin que llegue tramas del SkyPatrol
      

      //Envia las tramas para validar el nombre y la señal del equipo - cada segundo

         if( Reloj.segu == 10 ) printf("AT$TTDEVID?\n\r");  // Pregunta el ID del equipo
         if( Reloj.segu == 15 ) printf("AT+CSQ\n\r");      // Pregunta la intensidad de senal
      //Envio pra ver antenas, igualar hora y fecha...
         // Envio cada 20 segundos
         if ( Reloj.segu == 20 ) printf("AT$TTNETIP?\n\r");
         if ( Reloj.segu == 5 ) printf("AT$TTGPSQRY=10,0\n\r");   // Igualar la hora
                    
      if ( Reloj.segu > 59)
      {
         Reloj.segu = 0; Reloj.minu++;
            
         if( Reloj.minu > 59)
         {
            Reloj.minu = 0; Reloj.hora++;
               
            if( Reloj.hora == 24 && Reloj.minu == 00 && Reloj.segu == 00)
            {
               Reloj.hora = 0; Reloj.minu = 0; Reloj.segu = 0;
            }
            
         }
         
      }
   }
}
//-------------------------------------------------------------------------------------------------------------------------------------------//

/////////////////////////////////////////////// INTERRUPCION DEL TIMER0 (CUENTA CADA SEGUNDO) /////////////////////////////////////////////////
interrupt [TIM1_OVF] void timer1_ovf_isr(void)
{
   i_timer_1++;                     // Una interrupcion cada 6.06 seg.

}




   //////////////// FUNCION PARA OBTENER LA TRAMA DEL GPS SKYPATROL+ ///////////////////////////
      void obt(void)
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
            if ( rx_b0[i+0]== '$' &&    
                  rx_b0[i+1]== '$' &&     
                   rx_b0[i+2]== 'T' &&    
                    rx_b0[i+3]== 'x' &&  
                     rx_b0[i+4]== 't' &&
                      rx_b0[i+5]== ',')    
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

                     txt_glcd_b0[ i_txt_glcd ] = rx_b0[ i+6 + i_txt_glcd ]; 
                     i_txt_glcd++;
                     
                  }else{  // Mas de 100 caracteres recibidos. Romper el while

                     i_txt_overflow = 1;  //Legaron mas de 100 Caracteres
                     rx_b0[ i+6 + i_txt_glcd ] = ',';//Obliga a salir del while:
                  }

               }while( rx_b0[ i+6 + i_txt_glcd ] != ',' ); // Mientras el caracter no sea com

               pantalla = 7;          // Muestra en mensaje en main()
            }

            //+CSQ: 
            if ( rx_b0[i+0]== '+' &&    //43d
                  rx_b0[i+1]== 'C' &&     //67d
                   rx_b0[i+2]== 'S' &&    //83d
                    rx_b0[i+3]== 'Q' &&   //81d
                     rx_b0[i+4]== ':')    //58d
            { 
               
               // Se ha recibido una trama desde el SkyPatrol, se deben refrescar los
               // las banderas de desconexion
               conexion_skypatrol = 1; timer_sin_conexion = 0;
               i_timer_1 = 0;  
               

               // Valor decimal de la intensidad de la seÃ±al
               barras = ((rx_b0[i+6]-48)*10)+(rx_b0[i+7]-48);

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
            if ( rx_b0[i+0]== 'B' &&    
                  rx_b0[i+1]== 'U' &&     
                   rx_b0[i+2]== 'S')    
            { 
               
               // Se ha recibido una trama desde el SkyPatrol, se deben refrescar los
               // las banderas de desconexion
               conexion_skypatrol = 1; timer_sin_conexion = 0;
               i_timer_1 = 0;  
               

              // Datos de punto de control, en cada posicion del vector guardo una letra, luego hay que procesar para obtener el numero correcto. 
                                       //010A
               punto[0] = rx_b0[i+16]-48;  //   1 
               punto[1] = rx_b0[i+17]-48;  //   F
               punto[2] = rx_b0[i+18]-48;  //   0
               punto[3] = rx_b0[i+19]-48;  //   A
             
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
               if( rx_b0[i+22]=='1' &&  rx_b0[i+23]=='8'){
                  
                  pantalla = 1;
                 
                  unidades_ruta= (punto[2]*10) + punto[3];
                  decenas_ruta = (((punto[0]*16)-1)+ punto[1])*10; 
                  centenas_ruta=     unidades_ruta  +decenas_ruta;
                 
                  sprintf(no_pt,"P%d", centenas_ruta);     
               }
                 
            }

           
            //NETIP
            if ( rx_b0[i+0]== 'N' && 
                  rx_b0[i+1]== 'E' && 
                   rx_b0[i+2]== 'T' && 
                    rx_b0[i+3]== 'I' && 
                     rx_b0[i+4]== 'P')
            { 
               // Se ha recibido una trama desde el SkyPatrol, se deben refrescar los
               // las banderas de desconexion
               conexion_skypatrol = 1; timer_sin_conexion = 0;
               i_timer_1 = 0;  
               

               ini = i + 4; 

               for (n=0; n<201; n++) 
               {
                  // Busca el caracter ':'
                  if(rx_b0[ ini + n + 1 ] == ':' ) 
                  {
                     coma++; 
                     if(coma == 1) pos1 = n + ini + 1; // Guarda la posicion de la primera trama
                  }
               }
               
               // Verifica si despues del primer ':' Hay comillas
               if( rx_b0[ pos1 + 2] == 34 )
               {      
                  if( (rx_b0[pos1+3] - 48) == 0 && 
                      (rx_b0[pos1+4] - 48) == 0 && 
                      (rx_b0[pos1+5] - 48) == 0 && 
                      (rx_b0[pos1+7] - 48) == 0 && 
                      (rx_b0[pos1+8] - 48) == 0 && 
                      (rx_b0[pos1+9] - 48) == 0)
                  { 
                     gsm=0;   // Sin senal GSM
                  
                  }else
                     gsm=1;
               }   
            }
           
            //DEVID
            if ( rx_b0[i+0] == 'D' && 
                  rx_b0[i+1] == 'E' && 
                   rx_b0[i+2] == 'V' && 
                    rx_b0[i+3] == 'I' && 
                     rx_b0[i+4] == 'D')
            { 
               
               // Se ha recibido una trama desde el SkyPatrol, se deben refrescar los
               // las banderas de desconexion
               conexion_skypatrol = 1; timer_sin_conexion = 0;
               i_timer_1 = 0;  
               

               ini = i+4; 
               
               for (n=0;n<201;n++)
               {
                  if( rx_b0[ini+n+1] == ':') 
                  {
                     coma++; 
                     if(coma==1) pos1 = n+ini+1;
                  }
               }

               //Comprobar nombre      
               if(rx_b0[pos1+1]==34)
               { 
                  if( rx_b0[pos1+2] == NUM_DISP[0] && 
                      rx_b0[pos1+3] == NUM_DISP[1] && 
                      rx_b0[pos1+4] == NUM_DISP[2] && 
                      rx_b0[pos1+5] == NUM_DISP[3] )
                  {
                  
                  act=1;  // PANTALLA Y EQUIPO CORRECTA !!!
                  
                  }
                  else {
                     
                  act=1;  // PANTALLA INCORRECTA !!!
                  }
                              
               }
            }
           
            //Encabezado: GPRMC para igualar el reloj desde trama GPS
            if ( rx_b0[i+0] == 'G' && 
                  rx_b0[i+1] == 'P' && 
                   rx_b0[i+2] == 'R' && 
                    rx_b0[i+3] == 'M' && 
                     rx_b0[i+4] == 'C')
            { 
            
               // Se ha recibido una trama desde el SkyPatrol, se deben refrescar los
               // las banderas de desconexion
               conexion_skypatrol = 1; timer_sin_conexion = 0;
               i_timer_1 = 0;  
               
               ini=i+4;
               for (n=0;n<201;n++) 
               {
                  if(rx_b0[ini+n+1]==44) 
                  {
                     coma++;
                     if(coma==1) pos1=n+ini+1;
                     if(coma==2) pos2=n+ini+1;
                     if(coma==9) pos3=n+ini+1;
                  }
               }
               
                              
               // Comprueba que las comas no esten seguidas
               // en caso de no haber senial gps.
               if( (rx_b0[ pos1+1 ]-48) >= 0 && 
                    (rx_b0[ pos1+1 ]-48) < 10 &&
                     pos2 != (pos1 +1)             )
               {
           
                  digito_hora_temp = rx_b0[pos1 + 6 ] - 48;
                  if ( digito_hora_temp >= 0 && digito_hora_temp <= 9)
                     _seg = digito_hora_temp;

                  digito_hora_temp = rx_b0[pos1 + 5 ] - 48;
                  if ( digito_hora_temp >= 0 && digito_hora_temp <= 9)
                     _seg1 = digito_hora_temp;

                  digito_hora_temp = rx_b0[pos1 + 4 ] - 48;
                  if ( digito_hora_temp >= 0 && digito_hora_temp <= 9)
                     _minu = digito_hora_temp;

                  digito_hora_temp = rx_b0[pos1 + 3 ] - 48;
                  if ( digito_hora_temp >= 0 && digito_hora_temp <= 9)
                     _min1  = digito_hora_temp;

                  digito_hora_temp = rx_b0[pos1 + 2 ] - 48;
                  if ( digito_hora_temp >= 0 && digito_hora_temp <= 9)
                     _hora = digito_hora_temp;

                  digito_hora_temp = rx_b0[pos1 + 1 ] - 48;
                  if ( digito_hora_temp >= 0 && digito_hora_temp <= 9)
                     _hora1  = digito_hora_temp;
                   
                  RelojGPS.segu = _seg + (10 * _seg1 );
                  RelojGPS.minu = _minu + (10 * _min1 );
                  RelojGPS.hora = _hora + (10 * _hora1 );

               }
          
               // Comprueva la conexión de GPS
               gps = rx_b0 [ pos2 + 1 ]; 
               
               //Obtener Hora y dia
               if( (rx_b0[pos3+1]-48) >= 0 && 
                    (rx_b0[pos3+1]-48) < 10 )
               {
              
                  _dia1 = rx_b0[pos3+1]-48;
                  _dia  = rx_b0[pos3+2]-48;
                  _mes1 = rx_b0[pos3+3]-48;
                  _mes  = rx_b0[pos3+4]-48;
                  _an1  = rx_b0[pos3+5]-48;
                  _an   = rx_b0[pos3+6]-48;  

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
            rx_b0[i]=0;
         }
      }
   //---------------------------------------------------------------------------------------------//




/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//******************************************** PROGRAMA PRINCIPAL *************************************************//
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void main(void)
{
   
   int j = 0;
   // CODIGO GENERADO CON EL COMPILADOR CODEVISION
      #pragma optsize-
      CLKPR=0x80;
      CLKPR=0x00;
      #ifdef _OPTIMIZE_SIZE_
         #pragma optsize+
      #endif

      // COnfiguraciones PINES - TIMERS - UART 
         DATADDR = 0xff;

         PORTA=0xFF;
         DDRA=0xF0;

         PORTB=0x00;
         DDRB=0xFF;

         PORTD=0x00;
         DDRD=0b11110000;

         // USART0 Baud Rate: 115200
         UCSR0A=0x00;
         UCSR0B=0x98;
         UCSR0C=0x06;
         UBRR0H=0x00;
         UBRR0L=0x05;


         // Timer/Counter 0 initialization
         // Clock source: System Clock
         // Clock value: 10,800 kHz
         // Mode: Normal top=0xFF
         // OC0A output: Disconnected
         // OC0B output: Disconnected
         TCCR0A=0x00;
         TCCR0B=0x05;
         TCNT0=0x00;
         OCR0A=0x00;
         OCR0B=0x00;

         // Timer/Counter 0 Interrupt(s) initialization
         TIMSK0=0x01;

         // Timer/Counter 1 initialization
         // Clock source: System Clock
         // Clock value: 11059.200 kHz
         // Mode: Normal top=FFFFh
         // OC1A output: Discon.
         // OC1B output: Discon.
         // Noise Canceler: Off
         // Input Capture on Falling Edge
         // Timer1 Overflow Interrupt: On
         // Input Capture Interrupt: Off
         // Compare A Match Interrupt: Off
         // Compare B Match Interrupt: Off
         
         // 110592 / 1024(pr) = 10800 = / 65535 = 0.16479...
         // Overflow = 6.06805  segundos
         TCCR1A=0x00;
         TCCR1B=0x05;    // Prescaler de 1024
         TCNT1H=0x00;
         TCNT1L=0x00;
         ICR1H=0x00;
         ICR1L=0x00;
         OCR1AH=0x00;
         OCR1AL=0x00;
         OCR1BH=0x00;
         OCR1BL=0x00;

         // Timer/Counter 1 Interrupt(s) initialization
         TIMSK1=0x01;

   // Inicilizar GLCD
      glcd_on();
      delay_ms(INIT_DELAY_GLCD_MS);
      glcd_clear();

      buzz();
      buzz();

      // Dibuja KRADAC
      bmp_disp(arr,0,0,127,7);
      delay_ms( DELAY_PANTALLA_INI );
      glcd_clear();

      // Dibuja BUS
      bmp_disp(bus,0,0,45,7);

      // Escribe NOMBRE_PANTALLA "SITU"
      glcd_puts(NOMBRE_DISP,55,2,0,2,-1);    

      // Escribe NUMERO_PANTALLA "BUS####"
      glcd_puts("BUS SITU",59,5,0,1,-1);
      // glcd_puts(NUM_DISP,82,5,0,1,-1);
      glcd_puts(VERSION,40,7,0,1,-1);

      //Tiempo q muestra la pantalla de inicio
      delay_ms( DELAY_PANTALLA_INI ); 
      glcd_clear();             

   
   ////////////  VALORES INICIALES PARA VARIABLES HORA ///////////

      _seg   = 0;
      _seg1  = 0;
      _minu  = 0;
      _min1  = 0;
      _hora  = 0;
      _hora1 = 0;

      _dia   = 0;
      _dia1  = 0;
      _mes   = 0;
      _mes1  = 0;
      _an    = 0;
      _an1   = 0;

   //------------------------------------------------------------------------//

   // Limpia el buffer de mensaje recibido
      for( j = 0; j < TXT_BUF_SZ; j++ )
              txt_glcd_b0[j] = 0x00;
   
   

   // Encender interrupciones
   #asm("sei")

   
   // Muestra vacio
   bmp_disp(vacio,0,6,25,7);

   // Pide el ID del Skypatrol para verificar la pantalla
   printf("AT$TTDEVID?\n\r"); 
   delay_us( 500 );
   obt();
   
   // Estados iniciales de los botones  
   bandera1 = 0;
   bandera2 = 0;
   bandera3 = 0;

   num_ruta_sel = 0;
   
    // Forza la autorizacion de la pantalla
    act =1;   
    
   while (1)
   {

      // Verifica la bandera de interrupcion serial
      if( BIT_UART == 0 ) 
      {   
         obt();
         BIT_UART=1;  
      }
      
      if ( num_ruta_sel == 0 )
         ruta = ' ';
      else
         ruta = num_ruta_sel + 0x40; // pone el caracter 1 = A, 2 = B,

      if ( timer_sin_conexion >= DESCONEXION_SKYPATROL )
      {
         timer_sin_conexion = DESCONEXION_SKYPATROL;
         conexion_skypatrol = 0;
      }
      
      if( conexion_skypatrol == 1 )
      {  
         bnd_sin_conexion = 0;   
         glcd_clrln( 0 ); 
         dibujar_senal();
      }
                   
      boton1();

      boton2();    
      
      boton3();

      boton4();      

      boton5();

      
      
      // act = autoirzado
      if( act == 1 )
      {
         
         // Compueba que tenga ingresado la clave
         if( i_digitos == 6 ) //Ha escrito seis digitos
         {
            bnd_ingresa_clave = 0;   // Regresan las funciones a los botones

            i_digitos = 7;

            if( validar_clave() ){

               // Envia Evento de inicio de sesion
               printf("AT$TTTRGEV=42,1,24\r\n");

               glcd_clrln(4); 
               delay_ms( 1500 );

               glcd_clrln(1); 
               glcd_clrln(2); 
               glcd_clrln(3); 
               glcd_clrln(4); 
               glcd_clrln(5); 

               _laborando = 1;   //Permite interactuar con el sistema
               num_ruta_sel = 1;
               envia_estado_login();
               pantalla = 8;
            
            }else{

               //Muestra CLAVE NO VALIDA!
               glcd_clrln(4); 
               glcd_puts("NO AUTORIZADO",30,4,0,1,-1);
               delay_ms( 500 );

               glcd_clrln(3); 
               glcd_clrln(4); 
               glcd_clrln(5); 

               _laborando = 0;
               pantalla = 2;
               bnd_sin_sesion = 0;
               bnd_ingresa_clave = 1;   

               i_digitos = 0;

            }

         }

         // COMPRUEBA SI TIENE CONEXION AL SERVIDOR
         if( gsm == 1 && conexion_skypatrol == 1 )
         {
            glcd_putchar('E',21,0,1,1);
         
         }else if ( gsm == 0 && conexion_skypatrol == 1 ){
            
            // Grafica el simbolo de desconexion
            glcd_putchar(128,21,0,1,1);          
         }

      
         // COMPRUEBA SI TIENE CONEXION CON EL gps
         if( gps == 'A' && conexion_skypatrol == 1 )
         {     
            bmp_disp(GPS1,95,0,127,1);   
         }
         
         // Sin senal GPS y conectado Sky
         else if ( conexion_skypatrol == 1)
         { 
            bmp_disp(GPS2,95,0,127,1);
         }

         
         // SI HA PERDIDO CONEXION CON EL SKYPATROL 
         // POR MAS DE TRES MINUTOS
         if ( conexion_skypatrol == 0 && bnd_sin_conexion == 0 ){

            glcd_clrln( 0 ); 
            glcd_clrln( 1 ); 
            glcd_puts( "SIN CONEXION",22,0,0,1,-1); 
            bnd_sin_conexion = 1;
         }

         // Muestra el reloj al conductor
         if( pantalla == 0 ) 
         {
            // SE MUESTRA EL RELOJ CUANDO ESTA LABORANDO
            if (_laborando == 1 )
            {
               
               // Arma la trama de la  hora
               sprintf(reloj_c,"%02d:%02d:%02d", Reloj.hora, Reloj.minu, Reloj.segu);

               glcd_puts(reloj_c,7,2,0,2,-1);

               

               // Arma la trama de la  fecha
               sprintf(fecha,"20%02d-%02d-%02d", Reloj.an, Reloj.mes, Reloj.dia);

               glcd_puts(fecha,30,5,0,1,-1); 
               bmp_disp(chofer,0,6,35,7); // Pone el chofer
            
            }
            else if( _laborando == 0 && bnd_sin_sesion == 0  )
            {
               bnd_sin_sesion = 1;
               glcd_clrln(2); 
               glcd_clrln(3); 
               glcd_clrln(4); 
               glcd_clrln(7); 

               bmp_disp( vacio, 0, 6, 25, 7);   // Borra el chofer
               glcd_puts("NO HA INICIADO SESION",0,5,0,1,-2);
               
               
            }
            
            if ( num_ruta_sel == 0 && _laborando == 1  )
            {
               glcd_puts("SIN RUTA",35,7,0,1,-1);
               
            }

            else if( num_ruta_sel != 0 && _laborando == 1 )
            {
               glcd_puts("  RUTA:   ",30,7,0,1,-1);
               glcd_putchar(ruta,79,7,0,1);  // GRAFICA LA RUTA ACTUAL.

            }
            
            if ( conexion_skypatrol == 0 )
            {
               // Muestra mensaje de desconexión con SkyPatrol
            }
                                    
                        
         } 
         
         //Entra a esta funcion cuando llega un punto de control, 
         //verificando por el evento 18  pantalla = 1
         else if( pantalla == 1 )
         {     
            glcd_clrln(2); 
            glcd_clrln(3); 
            glcd_clrln(4); 
            glcd_clrln(5); 
            
            delay_ms(1);
            
            glcd_puts(no_pt,48,3,0,2,1);
            //glcd_puts(nombre_pt,10,2,0,1,-2);
             
            buzz();
            buzz();
            
            delay_ms(MOSTRAR_NUM_RUTA_MS);                  
            
            glcd_clrln(2); 
            glcd_clrln(3); 
            glcd_clrln(4); 
            glcd_clrln(5);    
               
            //esta variable se pone en 0 para que se vuelva a mostrar el reloj
            pantalla = 0;  
         }

         // CHOFER HA INICIADO SESION
         else if ( pantalla == 2)
         {
            glcd_clrln(2); 
            glcd_clrln(3); 
            glcd_clrln(4); 
            glcd_clrln(5); 
            
            delay_ms(1);
            
            // Simulacion de un inicio de sesion
            glcd_puts("INGRESE SU CODIGO",00,2,0,1,-1);
            bnd_ingresa_clave = 1;  //Los botones actuan como numeros.

            buzz();  
            buzz();

            pantalla = 99; // Para que se quede en espera
                        
         }

         // FINALIZO LA RUTA
         else if ( pantalla == 3 )
         {
               
            glcd_clrln(2); 
            glcd_clrln(3); 
            glcd_clrln(4); 
            glcd_clrln(5);  
            delay_ms(1);

            glcd_puts("FIN RUTA",28,3,0,1,-1);

            buzz();  
            buzz();
            
            delay_ms( MOSTRAR_NUM_RUTA_MS );                  
            
            glcd_clrln(2); 
            glcd_clrln(3); 
            glcd_clrln(4); 
            glcd_clrln(5); 

            pantalla=0;  //esta variable se pone en 0 para que se vuelva a mostrar el reloj
         }
         
         else if ( pantalla == 4 )
         {
               
            glcd_clrln(2); 
            glcd_clrln(3); 
            glcd_clrln(4); 
            glcd_clrln(5);
            delay_ms(1);

            glcd_puts("INICIO RUTA",20,3,0,1,-1);
            buzz();  
            buzz();
            delay_ms( MOSTRAR_MSN_ENV_MS );

            glcd_clrln(2); 
            glcd_clrln(3); 
            glcd_clrln(4); 
            glcd_clrln(5);     
            
            pantalla=0;  //esta variable se pone en 0 para que se vuelva a mostrar el reloj
         }
         //  CIERRA SESION
         else if ( pantalla == 5 )
         {
            glcd_clrln(2); 
            glcd_clrln(3); 
            glcd_clrln(4); 
            glcd_clrln(5); 
            
            delay_ms(1);
            
            glcd_puts(" HA SALIDO",20,2,0,1,-1);
            glcd_puts("DEL SISTEMA",20,4,0,1,-1);
             
            buzz();  
            buzz();
            
            delay_ms(MOSTRAR_MSN_ENV_MS);                  
            
            glcd_clrln(2); 
            glcd_clrln(3); 
            glcd_clrln(4); 
            glcd_clrln(5);    
            
            pantalla=0;  //esta variable se pone en 0 para que se vuelva a mostrar el reloj
            bnd_sin_sesion = 0; // Vuelve a mostrar NO HA INICIADO SESION

            // CONSIDERAR - Cuando cierre sesion que se pida iniciar o no muestra nada.
            //pantalla=0;  //esta variable se pone en 0 para que se vuelva a mostrar el reloj
         }

         // Debe iniciar sesion // Aun no implementada
         else if ( pantalla == 6 )
         {
            glcd_clrln(2); 
            glcd_clrln(3); 
            glcd_clrln(4); 
            glcd_clrln(5); 
            
            delay_ms(1);
            
            glcd_puts("NECESITA INICIAR JORNADA",20,2,0,1,-1);
             
            buzz();  
            buzz();
            
            delay_ms(MOSTRAR_MSN_ENV_MS);                  
            
            glcd_clrln(2); 
            glcd_clrln(3); 
            glcd_clrln(4); 
            glcd_clrln(5);    
            
            pantalla=0;  //esta variable se pone en 0 para que se vuelva a mostrar el reloj
         }
          
         // Mostrar el texto que llego desde el servidor
         else if ( pantalla == 7)
         {
            
            glcd_clear(); 

            glcd_puts( "MENSAJE:",30,0,0,1,-1 );  // Muestra el mensaje
            
            // Falta para hacer mensajes grandes
            glcd_puts( txt_glcd_b0,0,1,0,1,-1 );  // Muestra el mensaje
            
            delay_ms( DELAY_TXT_SERVIDOR );

            
            // Espera a que se presione un boton cualquiera
            while( BT1 && BT2 && BT3 && BT4 && BT5 )
            {}
            
            // Espera hasta que suelte el boton
            while( !( BT1 && BT2 && BT3 && BT4 && BT5) ) 
            {}

            
            glcd_clear(); 
            
            // Vacia el buffer
           for( j = 0; j < TXT_BUF_SZ; j++ )
              txt_glcd_b0[j] = 0x00;

            
            pantalla = 0; // Mostrar el reloj 
         }

         // CHOFER HA INICIADO SESION
         else if ( pantalla == 8 )
         {
            
            glcd_puts("ESCOJA SU RUTA",20,5,0,1,-1);
            glcd_puts("  RUTA:  ",30,7,0,1,-1);

            pantalla = 9;
         }

         else if ( pantalla == 9 )
         {
            
            // Arma la trama de la  hora
            sprintf(reloj_c,"%02d:%02d:%02d", Reloj.hora, Reloj.minu, Reloj.segu);

            glcd_puts(reloj_c,7,2,0,2,-1);

            // GRAFICA LA RUTA ACTUAL.
            glcd_putchar(ruta,79,7,0,1);  
            
            // Se mantiene en esta pantalla hasta que acepte la ruta
            pantalla = 9;
         }

      }
      
      else 
      {   
         glcd_puts("Pantalla",30,2,0,1,-1);
         glcd_puts("No Autorizada",15,4,0,1,-1);
      }  
         
       bmp_disp(frente,105,6,127,7);  
   } // Fin del While
}
//------------------- FIN DEL PROGRAMA PRINCIPAL ------------------------//
