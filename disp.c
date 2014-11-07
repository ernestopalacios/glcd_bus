/**********************************************\
 *       Kradac Robotics & Electronics        *
 *                                            *
 *  Proyecto:       GLCD BUS LOJA             *
 *  Programadores:  Vicente Q &&              *
 *                  Ernesto P &&              *
 *                  David Novillo             *
 *                  Jeferson C                *
 *  version:        0.9.7.0                   *
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


/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//******************************************** PROGRAMA PRINCIPAL *************************************************//
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void main(void)
{
   
   char* ptr_BUFFER_SERIAL = rx_b0;
   struct Tiempo * ptr_Reloj = &Reloj;
   
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

         Reloj.hora = 01;
         Reloj.minu = 02;
         Reloj.segu = 03;

         prueba_str( ptr_Reloj );


   // Inicilizar GLCD
      glcd_on();
      delay_ms(INIT_DELAY_GLCD_MS);
      glcd_clear();

      buzz();
      buzz();

      // Dibuja KRADAC
      bmp_disp(LogoKradac_bmp,0,0,127,7);
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
   bmp_disp( busVacio_bmp,0,6,25,7);

   // Pide el ID del Skypatrol para verificar la pantalla
   printf("AT$TTDEVID?\n\r"); 
   delay_us( 500 );
   obtener_trama( ptr_BUFFER_SERIAL );
   
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
         obtener_trama( ptr_BUFFER_SERIAL );
         BIT_UART=1;  
      }
      
      if ( num_ruta_sel == 0 )
         ruta = ' ';
      else
         ruta = num_ruta_sel + 0x40; // pone el caracter 1 = A, 2 = B,

      
      // Verifica si se ha desconectado el SkyPatrol
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
            bmp_disp(Full_BMP,95,0,127,1);   
         }
         
         // Sin senal GPS y conectado Sky
         else if ( conexion_skypatrol == 1)
         { 
            bmp_disp(busVacio_bmp,95,0,127,1);
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
               bmp_disp(Full_BMP,0,6,35,7); // Pone el chofer
            
            }
            else if( _laborando == 0 && bnd_sin_sesion == 0  )
            {
               bnd_sin_sesion = 1;
               glcd_clrln(2); 
               glcd_clrln(3); 
               glcd_clrln(4); 
               glcd_clrln(7); 

               bmp_disp( busVacio_bmp, 0, 6, 25, 7);   // Borra el chofer
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
