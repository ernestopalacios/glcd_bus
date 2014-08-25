/**********************************************\
 *       Kradac Robotics & Electronics        *
 *                                            *
 *  Proyecto:       GLCD BUS LOJA             *
 *  Programadores:  Vicente Q &&              *
 *                  Ernesto P &&              *
 *                  David Novillo             *
 *                  Jeferson C                *
 *  version:        0.9.0.1                   *
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


//////////////////////////////// INTERRUPCION SERIAL //////////////////////////////////
   #ifndef RXB8
   #define RXB8 1
   #endif
   #ifndef TXB8
   #define TXB8 0
   #endif
   #ifndef UPE
   #define UPE 2
   #endif
   #ifndef DOR
   #define DOR 3
   #endif
   #ifndef FE
   #define FE 4
   #endif
   #ifndef UDRE
   #define UDRE 5
   #endif
   #ifndef RXC
   #define RXC 7
   #endif

   #define FRAMING_ERROR (1<<FE)
   #define PARITY_ERROR (1<<UPE)
   #define DATA_OVERRUN (1<<DOR)
   #define DATA_REGISTER_EMPTY (1<<UDRE)
   #define RX_COMPLETE (1<<RXC)
//---------------------------------------------------------------------------------------

/////////////////////////  CONFIGURACIONES GLOBALES DEL PROGRAMA //////////////////////

   typedef char int8;    //sirve para definir enteros consigno de 8

   #define VERSION               "VER_0.9.0"
   #define NOMBRE_PANTALLA       "SITU"
   #define NUMERO_PANTALLA       "8888"
   #define DELAY_BUZZER_MS          100
   #define DELAY_BOTONES_MS         200
   #define INIT_DELAY_GLCD_MS        10
   #define DELAY_PANTALLA_INI      2000
   #define DELAY_TXT_SERVIDOR      3000
   #define TOTAL_RUTAS              100  //Número total de rutas
   #define MOSTRAR_NUM_RUTA_MS     2000  // Tiempo que se muestra el nombre de la Geocerca
   #define MOSTRAR_MSN_ENV_MS      1000  // Tiempo que muestra MENSAJE ENVIADO

   #define RX_BUFFER_SIZE0 200             //BUFFER DE 200 CARACTERES
   char rx_b0 [RX_BUFFER_SIZE0];           //nombre del buffer 

   # define TXT_BUF_SZ 160
   char txt_glcd_b0[ TXT_BUF_SZ ];            // Buffer para almacenar los caracteres a mostrarse en la GLCD
   char i_txt_glcd = 0;             // contador para recorrer el arreglo del buffer
   char i_txt_overflow = 0;        // Si los caracteres son mas de 100 ignora los demas caracteres
   
   /////////////////////////  DEFINIR PUERTOS BOTONES - BUZZER  //////////////////////////
   #define BT5 PINA.0
   #define BT4 PINA.1
   #define BT3 PINA.2
   #define BT2 PINA.3
   #define BT1 PINA.4
   #define buzzer PORTD.4
//----------------------------------------------------------------------------------------

/////////////////////////////// DEFINICIONES DE PUERTO SERIAL   //////////////////////////

   #if RX_BUFFER_SIZE0 <= 256
   unsigned char rx_wr_index0,rx_rd_index0,rx_counter0;
   #else
   unsigned int rx_wr_index0,rx_rd_index0,rx_counter0;
   #endif

   // This flag is set on USART0 Receiver buffer overflow
   bit rx_buffer_overflow0;
   bit BIT_UART;
//----------------------------------------------------------------------------------------




///////////////////////////////////////////////// VARIABLES  GLOBALES   /////////////////////////////////////////

   char NOMBRE_DISP[] = NOMBRE_PANTALLA;       // variable 
   char NUM_DISP[] = NUMERO_PANTALLA;          // variable
   char ruta= ' ';                             // variable donde se almacena la ruta que se enviarA al servidor
   char ruta_aux = ' ';                        // variable auxiliar para almacenar la ruta a seleccionar
   char bandera1 = 0;                          // variable auxiliar para evitar el rebote al oprimir el boton 1
   char bandera2 = 0;                          // variable auxiliar para evitar el rebote al oprimir el boton 2
   char bandera3 = 0;                          // variable auxiliar para evitar el rebote al oprimir el boton 3
   char bandera4 = 0;                          // variable auxiliar para evitar el rebote al oprimir el boton 4
   char bandera5 = 0;                          // variable auxiliar para evitar el rebote al oprimir el boton 4
   char aceptar  = 0;                          // variable que permite enviar ruta de trabajo al servidor

   // Contadores de las presiones de botones
   char btn1=0;          //  Cuenta entre 1 y 2 = 1 Inicia Sesion, 2 Cierra sesion 
   char btn2=0;         // Cuentra entre 1 y 12 =  Ruta seleccionada. Boton 2 aumenta el contador
   char btn3=0;        // No se usa, Boton 3 disminuye el contador btn2
   char btn4=0;       // Cuenta entre 1 y 2 = 1 Acepta Ruta, 2 Cancela Carrera
   char btn5=0;      // Cuenta entre 1 y 5 = Cambia los estados mecanicos del bus.

   int gsm, gps, ind_sen;     //indicadores de señal
   char reloj[8], fecha[8];  //vectores para imprmir GLCD

   char punto[4], pt=0, no_pt[4], nombre_pt[20];        // variables para reconocer geocercas
   int unidades_ruta, decenas_ruta, centenas_ruta;
   
   
   
//-----------------------------------------     VARIABLES EEPROM     --------------------------------------//

   static unsigned int time_count;    // Contador del timer para los segundos
   static unsigned int act;           // Variable que guarda si la pantalla es autorizada

   eeprom int8 seg   @0x80;
   eeprom int8 seg1  @0x82;           // segundos en unidades y decenas
   eeprom int8 minu  @0x84;          
   eeprom int8 min1  @0x86;           // minutos en unidades y decenas
   eeprom int8 hora  @0x88;         
   eeprom int8 hora1 @0x8A;           // hora en unidades y decenas
   eeprom int8 dia   @0x8C;          
   eeprom int8 dia1  @0x8E;           // dias en unidades y decenas
   eeprom int8 mes   @0x90;          
   eeprom int8 mes1  @0x92;           // mes en unidades y decenas
   eeprom int8 an    @0x94;       
   eeprom int8 an1   @0x96;           // anos en unidades y decenas
     
   eeprom int8 num_ruta   @0x28;      // Transforma la letra de la ruta a un número
                                      // Si su valor es de CERO no tiene ruta asignada
                                      // No este en recorrido

   eeprom int8 laborando  @0x2A;      // Sabe si el chofer ha iniciado sesion o no.
                                      // Para poder escoger la ruta debe iniciar sesion

   //----------------------------------   VARIABLES EERPOM EN LA FLASH  ------------------------------------//
   
   int8 _seg  = 0;
   int8 _seg1 = 0;    // segundos en unidades y decenas
   int8 _minu = 0;   
   int8 _min1 = 0;    // minutos en unidades y decenas
   int8 _hora = 0;  
   int8 _hora1= 0;    // hora en unidades y decenas
   int8 _dia  = 0;   
   int8 _dia1 = 0;    // dias en unidades y decenas
   int8 _mes  = 0;   
   int8 _mes1 = 0;    // mes en unidades y decenas
   int8 _an   = 0;
   int8 _an1  = 0;    // anos en unidades y decenas

   int8 _num_ruta  = 0;
   int8 _laborando = 0;




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
      seg++; 
      time_count = 0;  //reiniciar contador
      
      //Envia las tramas para validar el nombre y la señal del equipo - cada segundo
         if(seg==1 && seg1==1) printf("AT$TTDEVID?\n\r");  // Pregunta el ID del equipo
         if(seg==1 && seg1==2) printf("AT+CSQ\n\r");      // Pregunta la intensidad de senal
      //Envio pra ver antenas, igualar hora y fecha...
         // Envio cada 20 segundos
         if (seg==1 && seg1==3) printf("AT$TTNETIP?\n\r");
         if (seg==1 && seg1==4) printf("AT$TTGPSQRY=10,0\n\r");   // Igualar la hora
                    
          
      if (seg>9)
      {
         seg=0; seg1++;
           
         if(seg1>5)  // Cambio de minuto
         {
            seg1=0; minu++;
            if(minu>9)
            {
               minu=0; min1++;
               if(min1>5)
               {
                  min1=0; hora++;
                  if(hora>9)
                  {
                     hora=0; hora1++;
                     if((hora1==2 && hora==3)&&(min1==5 && minu==9)&&(seg1==5 && seg==9))
                     {
                        hora1=0; hora=0; min1=0; minu=0;seg1=0;seg=0;    
                     }
                  }
               }
            }
         }
      }
   }
}
//-------------------------------------------------------------------------------------------------------------------------------------------//



//***********************************************************************************************************************************//
//////////////////////////////////////////////////////////// FUNCIONES ////////////////////////////////////////////////////////////////
//***********************************************************************************************************************************//

   ////////////////// FUNCIÓN PARA EL SONIDO DEL BUZZER /////////////////////
      /** \brief Genera el sonido del buffer
       *
       * El tiempo que suena depende del Macro: DELAY BUZZER
       */
      void buzz()
      {       //Sonido de Buzzer
         buzzer=1; delay_ms( DELAY_BUZZER_MS );
         buzzer=0; delay_ms( DELAY_BUZZER_MS );
      }
   //---------------------------------------------------------------------------//

   ////////////////// FUNCIÓN PARA CALCULAR NUMERO DE RUTA //////////////////
      /** \brief Transforma el caracter de ruta a un número
       *
       * Cambia de A -> 1; B->2 ...  etc, en caso de que el caracter pasado no 
       * Corresponda a una letra devolvera -1
       * 
       * Solo soporta un carcater, máximo se puede tener 35 rutas.
       */
      int8 calcuar_ruta( char ruta )
      {
         int8 numero_ruta = ruta - 0x40;

         // Verificar que la letra corresponde a un número de ruta
         if ( numero_ruta > 0 && numero_ruta <= TOTAL_RUTAS )
            return numero_ruta;
         else
            return 0; // El caracter no corresponde a una ruta.

      }
   //---------------------------------------------------------------------------//

   ////////////////// FUNCION PARA ENVIAR RUTA AL SERVIDOR //////////////////
      /** \brief Envia inicio o fin de ruta para el calulo del recorrido
       *
       * Para el inicio de trama envia un numero que representa la ruta y luego
       * envia el estado de esa ruta: ej R2,2,0. Fin de Ruta dos
       * 
       */
      void enviar_estado_ruta(){
         
         _num_ruta = calcuar_ruta( ruta );
         printf("AT$TTSNDMG=4,\"$$BL%s,%d%d%d%d20%d%d,%d%d%d%d%d%d,R2,%d,%d:XX##\"\r\n", 
                                          NUM_DISP, 
                                               _dia1,_dia,
                                               _mes1,_mes,
                                               _an1,_an,
                                                   _hora1,hora,
                                                   _min1 ,minu,
                                                   _seg1 ,seg, 
                                                      _num_ruta,aceptar  );
      }
   //---------------------------------------------------------------------------//


   ////////////////// FUNCION PARA ENVIAR LOGIN AL SERVIDOR /////////////////
      /** \brief Envia inicio o fin de LOGIN del chofer para el calulo del recorrido
       *
       * Para el inicio de trama envia un numero que representa el ID del chofer
       * luego el estado. LOGIN/LOGOUT
       * 
       */
      void envia_estado_login(){
         printf("AT$TTSNDMG=4,\"$$BL%s,%d%d%d%d20%d%d,%d%d%d%d%d%d,S2,1234,%d:XX##\"\r\n", 
                                       NUM_DISP, 
                                            _dia1,_dia,
                                            _mes1,_mes,
                                            _an1,_an,
                                                _hora1,hora,
                                                _min1 ,minu,
                                                _seg1 ,seg, 
                                                  // id_conductor, 1234 temporalmente
                                                     _laborando  );
      }
   //---------------------------------------------------------------------------//


   ////////////////// FUNCION DEL BOTON 1 (INICIO/FIN DE JORNADA) ///////////
      void boton1()
      {  
         // Primera presion del botòn
         if( BT1 == 0 && bandera1==0)
         {
            btn1++;                          // Aumenta el contador del boton
            bandera1=1;                     // Evita que vuelva a entrar al mismo boton
            
            buzz();
            delay_ms( DELAY_BOTONES_MS );

            switch (btn1) 
            {
               // PRIMERA PRESION DEL BOTON
               case 1:
                  
                  // Envia Inicio de sesion al servidor
                  pt=2;                             // Para q muestre en la glcd MENSAJE ENVIADO
                  _laborando = 1;                  // INICIA SESION  ***
                  envia_estado_login();
                  // DEBE HABILITAR EL BOTON 4

                  // Muestra la RUTA A: primero y por defecto
                  btn2 = 1;
                  
                  //Muestra el chofer
                  bmp_disp(chofer,0,5,35,7); 

                  // Muestra la ruta
                  glcd_puts("RUTA:",44,7,0,1,-1);
               
               break;
               
               // SEGUNDA PRESION DEL BOTON
               //solamente quita la ruta de la pantalla
               //no cierra sesion de la ruta actual
               case 2:

                  // Si esta en ruta no puede salir,
                  // Primero debe terminar la jornada
                  if( aceptar == 1)
                  {
                     btn1--;  // Como si aún no lo hubiera presionado
                     break;

                     // Muestra mensaje que primero termine la carrera

                  }else{

                     bmp_disp( vacio, 0, 5, 25, 7);   // Borra el chofer
                     
                     _laborando = 0;     // No se encuentra en laborando.
                     pt=5;             // Muestra mensaje de FIN JORNADA  ***
                     envia_estado_login();

                     
                     // Borra el caracter de la carrera
                     glcd_putchar(' ',79,7,0,1); 
                     // Borra una trama de caracteres RUTA:
                     glcd_puts("      ",44,7,0,1,-1); 

                     // Reiniciliza el contador, siguiente presion btn = 1;
                     btn1 = 0;
                  }
                        
               break; 

            }  
         } 

         // Cuando se levanta el boton del dedo levant la bandera
         else if( BT1 == 1 && bandera1 == 1 )
         {
            bandera1=0;
         }
      }
   //---------------------------------------------------------------------------//


   ////////////////// FUNCION DEL BOTON 2 (ESCOGER RUTA AUMENTAR LETRA) /////
      void boton2(){     
         
         // Si se presiona el boton dos, luego de haber presionado el boton
         // uno, una vez. Y aún no se ha aceptado carrera
         if( BT2 == 0 && bandera2==0 && aceptar == 0 && _laborando == 1 )
         {
            btn2++; 
            buzz();
            bandera2 = 1;  

            if( btn2 > 12 && btn2 != 15) 
               btn2 = 1;
            
            delay_ms(DELAY_BOTONES_MS);
         }  
         

         // Luego de presionar el boton, puede volver a presionarlo.
         else if(BT2==1 && bandera2==1)
         {
            bandera2=0;
         }

         
         // El switch lo hace constantemente, ya que esta en el main y
         // no depende de ningun IF

         switch (btn2){
            case 1:
              ruta_aux='A';
           
              break;
            case 2:  
              ruta_aux='B';
           
            break;
            case 3:   
              ruta_aux='C';
          
            break; 
            case 4:  
              ruta_aux='D';
          
            break; 
            case 5:  
              ruta_aux='E';
            break; 
            case 6:    
              ruta_aux='F';
           
            break; 
            case 7:  
              ruta_aux='G';
              
            break; 
            case 8:  
              ruta_aux='H';
              
            break;
            case 9:  
              ruta_aux='I';
              
            break; 
            case 10: 
              ruta_aux='J';
              
            break; 
            case 11: 
              ruta_aux='K';
              
            break;
            case 12: 
              ruta_aux='L';
              
            break;  
            case 15:
              ruta_aux=' ';  // Carrera vacia
            break; 
         }         
      }
   //---------------------------------------------------------------------------//


   ////////////////// FUNCION DEL BOTON 3 (ESCOGER RUTA DECREMENTAR LETRA) //
      void boton3()
      {     //Boton 3
         if( BT3 == 0 && bandera3 == 0 && aceptar == 0 && _laborando == 1)
         {
            btn2--; 
            buzz();
            bandera3=1;  
            if(btn2<=0 && btn2!=15) 
               btn2=12;
            delay_ms(200);
         }  
         else if(BT3==1 && bandera3==1){
            bandera3=0;
         }
      }
   //---------------------------------------------------------------------------//


   ////////////////// FUNCION DEL BOTON 4 (INICIO/FIN DE RUTA) //////////////
      void boton4()
      {     //Boton 4
         
         // Primera presiónn del boton 4. Acepta la carrera. 
         if ( BT4 == 0 && bandera4 == 0 && _laborando == 1  )
         { 
            bandera4++;           // Evita reentrada
            btn4++;              // Incrementa conteo de presiones del boton
            ruta = ruta_aux;    // Actualiza la ruta
            
            buzz();
            delay_ms(200);

            switch(btn4){

               case 1:
                  aceptar = 1;        //Ha aceptado la carrera
                  pt=4;              // Muestra RUTA ACPETADA
                  enviar_estado_ruta();
                  
               break;

               case 2:
                  btn2    = 15;     // Borra el caracter de ruta
                  aceptar = 0;     // Fin de la ruta
                  pt=3;           // Muestra FIN RUTA 
                  enviar_estado_ruta();
                  ruta=' ';      // Cambia la ruta a Vacia
                  
                  btn4 = 0;     // Reinicializa el cntador
               break;
            }
         }

         
         // si se ha presionado el boton cuatro por tercera vez
         else if(BT4 == 1 && bandera4 == 1)
         {
            bandera4 = 0;
         }
      }
   //---------------------------------------------------------------------------//


   ////////////////// FUNCION DEL BOTON 5 (ESTADO MECANICO) /////////////////
      void boton5(){     

         btn5++;
         bandera5++;
         
         buzz();
         delay_ms( DELAY_BOTONES_MS );

         switch( btn5 ){

            case 1:
               //envia estado mecanico 1:
            break;

            case 2:
               //envia estado mecanico 1:
            break;

            case 3:
               //envia estado mecanico 1:
            break;

            case 4:
               //envia estado mecanico 1:
            break;

            case 5:
               //envia estado mecanico 1:
            break;

            case 6:
               //envia estado mecanico 1:
            break;

            case 7:
               //envia estado mecanico 1:
            break;

            case 8:
               //envia estado mecanico 1:
            break;

            case 9:
               //envia estado mecanico 1:
            break;

            case 10:
               //envia estado mecanico 1:
            break;

            case 11:
               //envia estado mecanico 1:
               btn5 = 0;
            break;
         }

      }
   //---------------------------------------------------------------------------//


   ////////////////// DIBUJAR BARRAS DE SENAL GPRS //////////////////////////
      void dibujar_senal(void)
      {
          switch (ind_sen){
          case 1:
          bmp_disp(GSM3,0,0,20,1);
          break;
          case 2:
          bmp_disp(GSM2,0,0,20,1);
          break;
          case 3:
          bmp_disp(GSM1,0,0,20,1);
          break;
          case 4:
          bmp_disp(GSM4,0,0,20,1);
          break;
          }; 

      }
   //---------------------------------------------------------------------------//


   //////////////// FUNCION PARA OBTENER LA TRAMA DEL GPS SKYPATROL+ ///////////////////////////
      void obt(void)
      {

         int i;                        // Contador de lazo FOR() buffer serial
         int j;                       // Contador de ??
         int n=0;                    //
         int ini;
         int coma=0;
         int pos1=0;
         int pos2=0;
         int pos3=0;
         int barras;
         int n1,n2,n3,n4; // Variables para Hora, sirven para -5 UTC de Ecuador

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

               do
               {
                  if (i_txt_glcd <= TXT_BUF_SZ )
                  {

                     txt_glcd_b0[ i_txt_glcd ] = rx_b0[ i+6 + i_txt_glcd ]; 
                     i_txt_glcd++;
                     
                  }else{  // Mas de 100 caracteres recibidos. Romper el while

                     i_txt_overflow = 1;  //Legaron mas de 100 Caracteres

                     rx_b0[ i+6 + i_txt_glcd ] = ',';//Obliga a salir del while:
                  }

               }while( rx_b0[ i+6 + i_txt_glcd ] != ',' ); // Mientras el caracter no sea com

               pt = 7;          // Muestra en mensaje en main()
            }

            //+CSQ: 
            if ( rx_b0[i+0]== '+' &&    //43d
                  rx_b0[i+1]== 'C' &&     //67d
                   rx_b0[i+2]== 'S' &&    //83d
                    rx_b0[i+3]== 'Q' &&   //81d
                     rx_b0[i+4]== ':')    //58d
            { 
              // Valor decimal de la intensidad de la seÃ±al
              barras = ((rx_b0[i+6]-48)*10)+(rx_b0[i+7]-48);

              // Dibuja las barras en la panalla de acuerdo a la intensidad
              // de la seÃ±al
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
              else{   }

            }
           
           
                //________________________
           //PARA PUNTO DE CONTROL: 
            //por ahora detecto el encabezado "BUS" para tener de referencia en las posiciones del vector
            if ( rx_b0[i+0]== 'B' &&    
                  rx_b0[i+1]== 'U' &&     
                   rx_b0[i+2]== 'S')    
            { 
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
                   
               //El 18 es el numero de evento, lo identifico para determinar si es geocerca, si esta bien se pone en 1 la variable "pt"
               if( rx_b0[i+22]=='1' &&  rx_b0[i+23]=='8'){
                  
                  pt = 1;
                 
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
                     gsm=0;   // Sin seÃ±al GSM
                  
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
               ini = i+4; 
               
               // Limpia las lineas 2,3,4,5
               glcd_clrln(2); 
               glcd_clrln(3); 
               glcd_clrln(4); 
               glcd_clrln(5);
                
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
                     
                  act=0;  // PANTALLA INCORRECTA !!!
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
               
               glcd_clrln(3);    
               glcd_clrln(4);   
               glcd_clrln(5);

               
               // Comprueba que las comas no esten seguidas
               // en caso de no haber senial gps.
               if( (rx_b0[ pos1+1 ]-48)>= 0 && 
                   (rx_b0[ pos1+1 ]-48)< 10 &&
                    pos2 != (pos1 +1)
                 )
               {
           
                  digito_hora_temp = rx_b0[pos1 + 6 ] - 48;
                  if ( digito_hora_temp >= 0 && digito_hora_temp <= 9)
                     seg = digito_hora_temp;

                  digito_hora_temp = rx_b0[pos1 + 5 ] - 48;
                  if ( digito_hora_temp >= 0 && digito_hora_temp <= 9)
                     seg1 = digito_hora_temp;

                  digito_hora_temp = rx_b0[pos1 + 4 ] - 48;
                  if ( digito_hora_temp >= 0 && digito_hora_temp <= 9)
                     minu = digito_hora_temp;

                  digito_hora_temp = rx_b0[pos1 + 3 ] - 48;
                  if ( digito_hora_temp >= 0 && digito_hora_temp <= 9)
                     min1  = digito_hora_temp;

                  digito_hora_temp = rx_b0[pos1 + 2 ] - 48;
                  if ( digito_hora_temp >= 0 && digito_hora_temp <= 9)
                     n2 = digito_hora_temp;

                  digito_hora_temp = rx_b0[pos1 + 1 ] - 48;
                  if ( digito_hora_temp >= 0 && digito_hora_temp <= 9)
                     n1  = digito_hora_temp;
                   
                        
                  n3 = ( n1*10 ) + n2;   // Hora total suma unidades y decenas
                  n4 = n3 - 5;  // Zona horaria

                  if( n4 < 0 )
                  {
                     n4    = n4 + 24;
                     hora  = n4 % 10;
                     hora1 = n4 / 10;
                  }  
                  
                  hora = n4 % 10;
                  hora1= n4 / 10;
               
               }
          
               // Comprueva la conexión de GPS
               gps = rx_b0 [ pos2 + 1 ]; 
               printf( "%c", gps);  //Herramienta de DEBUG
           
               //Obtener Hora y dia
               if( (rx_b0[pos3+1]-48) >= 0 && 
                   (rx_b0[pos3+1]-48) < 10 )
               {
              
                  dia1 = rx_b0[pos3+1]-48;
                  dia  = rx_b0[pos3+2]-48;
                  mes1 = rx_b0[pos3+3]-48;
                  mes  = rx_b0[pos3+4]-48;
                  an1  = rx_b0[pos3+5]-48;
                  an   = rx_b0[pos3+6]-48;  

                  if( n4 > 18)
                     dia = dia-1;  // Por la zona horaria de EC-5GTM
                  
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

      DATADDR = 0xff;

      PORTA=0xFF;
      DDRA=0xF0;

      PORTB=0x00;
      DDRB=0xFF;

      PORTD=0x00;
      DDRD=0b11110000;

      // USART0 initialization
      // Communication Parameters: 8 Data, 1 Stop, No Parity
      // USART0 Receiver: On
      // USART0 Transmitter: On
      // USART0 Mode: Asynchronous
      //// USART0 Baud Rate: 9600 11.0592 MHz
      //UCSR0A=0x00;
      //UCSR0B=0x98;
      //UCSR0C=0x06;
      //UBRR0H=0x00;
      //UBRR0L=0x47;

      // USART0 Baud Rate: 115200
      UCSR0A=0x00;
      UCSR0B=0x98;
      UCSR0C=0x06;
      UBRR0H=0x00;
      UBRR0L=0x05;

      //USART0 Baud Rate: 9600 8 MHz
      //UCSR0A=0x00;
      //UCSR0B=0x18;
      //UCSR0C=0x06;
      //UBRR0H=0x00;
      //UBRR0L=0x33;

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
      glcd_puts("BUS",59,5,0,1,-1);
      glcd_puts(NUM_DISP,82,5,0,1,-1);
      glcd_puts(VERSION,40,7,0,1,-1);

      //Tiempo q muestra la pantalla de inicio
      delay_ms( DELAY_PANTALLA_INI ); 
      glcd_clear();             

   
   ////////////  VALORES INICIALES PARA VARIABLES DE LA EEPROM ///////////

      // En caso de que no haya recibido tramas del sky
      // previene que muestre valores de -1 en la hora y fecha
      if (hora1 == 0xff )
      {
         hora1 = 0; min1 = 0; seg1 = 0;
           hora = 0; minu = 0;  seg = 0;
      }

      // En caso de que no haya fecha
      if (mes == 0xff && dia == 0xff && an == 0xff)
      {
         dia = 0; dia1 = 0; 
          mes = 0; mes1 = 0;
           an = 0;  an1 = 0; 
      }

      // Iniciala la eeprom.
      if (num_ruta  == 0xff) 
      {
         num_ruta  = 0;
         _num_ruta = 0;
      }   
      else
         _num_ruta = num_ruta;

      if (laborando > 2) 
      {
         laborando = 0;
         _laborando= 0;
      }
      //else
      //   _laborando = laborando;

      // Limpia el buffer de mensaje recibido
      for( j = 0; j < TXT_BUF_SZ; j++ )
              txt_glcd_b0[j] = 0x00;
   //------------------------------------------------------------------------//
   

   // Encender interrupciones
   #asm("sei")

   // Muestra vacio
   bmp_disp(vacio,0,5,25,7);

   // Pide el ID del Skypatrol para verificar la pantalla
   printf("AT$TTDEVID?\n\r"); 
   delay_us( 500 );
   obt();
   
   // Estados iniciales de los botones  
   bandera1 = 0;
   bandera2 = 0;
   bandera3 = 0;
   
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
      
      // GRAFICA LA RUTA ACTUAL.
      glcd_putchar(ruta_aux,79,7,0,1);  
                   
      boton1();

      boton2();    
      
      boton3();

      boton4();                                      

      dibujar_senal();
      
      
      // act = autoirzado
      if(act==1)
      {
         if( gsm == 1)
         {
            glcd_putchar('E',19,0,1,1);
         }else{
            glcd_putchar(' ',19,0,1,1);
         } 
      

         // Muestra el reloj al conductor
         if(pt==0) 
         {
            sprintf(reloj,"%d%d:%d%d:%d%d",hora1, hora, min1, minu, seg1, seg);
            //printf("%d%d:%d%d:%d%d\n\r",hora1, hora, min1, minu, seg1, seg);
            
            // pasa de la eeprom a la flash del micro
            _seg  = seg  ;
            _seg1 = seg1 ;    // segundos en unidades y decenas
            _minu = minu ;   
            _min1 = min1 ;    // minutos en unidades y decenas
            _hora = hora ;  
            _hora1= hora1;    // hora en unidades y decenas
            _dia  = dia  ;   
            _dia1 = dia1 ;    // dias en unidades y decenas
            _mes  = mes  ;   
            _mes1 = mes1 ;    // mes en unidades y decenas
            _an   = an   ;
            _an1  = an1  ;     // anos en unidades y decenas

            num_ruta  = _num_ruta;
            laborando = _laborando;

            glcd_puts(reloj,7,2,0,2,-1);     
         } 
         
         //Entra a esta funcion cuando llega un punto de control, verificando por el evento 18  pt=1
         else if(pt==1)
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
            pt=0;  
         }

         // CHOFER HA INICIADO SESION
         else if (pt==2){
            glcd_clrln(2); 
            glcd_clrln(3); 
            glcd_clrln(4); 
            glcd_clrln(5); 
            
            delay_ms(1);
            
            // Simulacion de un inicio de sesion
            glcd_puts("INICIO DE SESION",5,2,0,1,-1);
            delay_ms( 500 );
            glcd_puts("*",45,4,0,1,-1);
            delay_ms( 300 );
            glcd_puts("*",53,4,0,1,-1);
            delay_ms( 300 );
            glcd_puts("*",61,4,0,1,-1);
            delay_ms( 300 );
            glcd_puts("*",69,4,0,1,-1);
            delay_ms( 500 );
                         
            buzz();  
            buzz();
            
            delay_ms(MOSTRAR_MSN_ENV_MS);                  
            
            glcd_clrln(2); 
            glcd_clrln(3); 
            glcd_clrln(4); 
            glcd_clrln(5);    
            
            pt=0;  //esta variable se pone en 0 para que se vuelva a mostrar el reloj
         }

         // FINALIZO LA RUTA
         else if (pt==3){
               
            glcd_clrln(2); 
            glcd_clrln(3); 
            glcd_clrln(4); 
            glcd_clrln(5);  
            delay_ms(1);

            glcd_puts("FIN RUTA",28,3,0,1,-1);

            buzz();  
            buzz();
            
            delay_ms(1000);                  
            
            glcd_clrln(2); 
            glcd_clrln(3); 
            glcd_clrln(4); 
            glcd_clrln(5);    
            pt=0;  //esta variable se pone en 0 para que se vuelva a mostrar el reloj
         }
         
         else if (pt==4){
               
            glcd_clrln(2); 
            glcd_clrln(3); 
            glcd_clrln(4); 
            glcd_clrln(5);
            delay_ms(1);

            glcd_puts("INICIO RUTA",20,3,0,1,-1);
            buzz();  
            buzz();
            delay_ms(MOSTRAR_MSN_ENV_MS);

            glcd_clrln(2); 
            glcd_clrln(3); 
            glcd_clrln(4); 
            glcd_clrln(5);     
            pt=0;  //esta variable se pone en 0 para que se vuelva a mostrar el reloj
         }
         //  CIERRA SESION
         else if (pt==5){
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
            
            pt=0;  //esta variable se pone en 0 para que se vuelva a mostrar el reloj

            // CONSIDERAR - Cuando cierre sesion que se pida iniciar o no muestra nada.
            //pt=0;  //esta variable se pone en 0 para que se vuelva a mostrar el reloj
         }

         // Debe iniciar sesion // Aun no implementada
         else if (pt==6){
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
            
            pt=0;  //esta variable se pone en 0 para que se vuelva a mostrar el reloj
         }
          
         // Mostrar el texto que llego desde el servidor
         else if ( pt == 7)
         {
            
            glcd_clear(); 

            glcd_puts( "MENSAJE:",30,0,0,1,-1 );  // Muestra el mensaje
            
            // Falta para hacer mensajes grandes
            glcd_puts( txt_glcd_b0,0,1,0,1,-1 );  // Muestra el mensaje
            
            delay_ms( DELAY_TXT_SERVIDOR );

            while( BT1 &&
                    BT2 &&
                     BT3 &&
                      BT4 &&
                       BT5 )
            {
               // Espera a que se presione un boton cualquiera
               delay_ms(DELAY_BOTONES_MS);
            }

            glcd_clear(); 
            delay_ms( DELAY_BOTONES_MS );

            if ( _laborando == 1)
            {
               //Muestra el chofer y la ruta
               bmp_disp(chofer,0,5,35,7); 
               glcd_puts("RUTA:",44,7,0,1,-1);
            }else{
               //Muestra el bus sin chofer
               bmp_disp( vacio, 0, 5, 25, 7);   // Borra el chofer
               // Borra el caracter de la carrera
               glcd_putchar(' ',79,7,0,1); 
               // Borra una trama de caracteres RUTA:
               glcd_puts("      ",44,7,0,1,-1); 

            }


            printf("AT+CSQ\n\r"); // Vuelve a dibujar la senal

            
            // Vacia el buffer
           for( j = 0; j < TXT_BUF_SZ; j++ )
              txt_glcd_b0[j] = 0x00;

            pt = 0; // Mostrar el reloj
            
         }

         // Con senal GPS
         if( gps == 'A' )
         {     
            bmp_disp(GPS1,95,0,127,1);   

            sprintf(fecha,"20%d%d-%d%d-%d%d",an1, an, mes1, mes, dia1, dia);
            glcd_puts(fecha,34,5,0,1,-1); 
         
         }
         // Sin senal GPS
         else if (gps == 'V' || gps == '9' )
         {
            bmp_disp(GPS2,95,0,127,1);
            
            sprintf(fecha,"20%d%d-%d%d-%d%d",an1, an, mes1, mes, dia1, dia);
            glcd_puts(fecha,34,5,0,1,-1); 
            
         }
         else
         { 
            bmp_disp(GPS2,95,0,127,1);
            sprintf(fecha,"20%d%d-%d%d-%d%d",an1, an, mes1, mes, dia1, dia);
            glcd_puts(fecha,34,5,0,1,-1);
         }
      }
      
      else 
      {   
         glcd_puts("Pantalla",30,2,0,1,-1);
         glcd_puts("No Autorizada",15,4,0,1,-1);
      }  
         
         bmp_disp(frente,105,5,127,7);  
   } // Fin del While
}
//---------------------------------------- FIN DEL PROGRAMA PRINCIPAL ---------------------------------------------//