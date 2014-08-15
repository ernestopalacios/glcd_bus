/**********************************************\
 *       Kradac Robotics & Electronics        *
 *                                            *
 *  Proyecto:       GLCD BUS LOJA             *
 *  Programadores:  Vicente Q &&              *
 *                  Ernesto P &&              *
 *                  David Novillo             *
 *  version:        0.8.3                     *
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

//SE AGREGAN LAS LIBRERIAS QUE SE VAN A UTILIZAR
#include <mega324.h>
#include <delay.h>
#include <stdio.h>
#include <stdlib.h>
#include "Includes/GLCD.h"
#include "Includes/bus.h"


//////////////////////////////// INTERRUPCION SERIAL /////////////////////////////////
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


typedef char int8;    //sirve para definir enteros consigno de 8

#define NOMBRE_PANTALLA  "SITU"
#define NUMERO_PANTALLA  "1697"
#define DELAY_BUZZER_MS     100
#define DELAY_BOTONES_MS    200
#define INIT_DELAY_GLCD_MS   10
#define DELAY_PANTALLA_INI 2000
#define TOTAL_RUTAS          10  //Número total de rutas

#define RX_BUFFER_SIZE0 200             //BUFFER DE 200 CARACTERES
char rx_b0 [RX_BUFFER_SIZE0];           //nombre del buffer 

#if RX_BUFFER_SIZE0 <= 256
unsigned char rx_wr_index0,rx_rd_index0,rx_counter0;
#else
unsigned int rx_wr_index0,rx_rd_index0,rx_counter0;
#endif

// This flag is set on USART0 Receiver buffer overflow
bit rx_buffer_overflow0;
bit BIT_UART;


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
//-----------------------------  FIN INTERRUPCION SERIAL  -----------------------------//



////////////////////  DEFINIR PUERTOS BOTONES - BUZZER  //////////////////
#define BT5 PINA.0
#define BT4 PINA.1
#define BT3 PINA.2
#define BT2 PINA.3
#define BT1 PINA.4
#define buzzer PORTD.4
//---------------------------------------------------------------------//


///////////////////////////////////////////////////////////////////////// VARIABLES ///////////////////////////////////////////////////////////////
char NOMBRE_DISP[] = NOMBRE_PANTALLA;                 // variable 
char NUM_DISP[] = NUMERO_PANTALLA;                    // variable
char ruta_aux = ' ';                                  // variable auxiliar para almacenar la ruta a seleccionar
char ruta= ' ';                                       // variable donde se almacena la ruta que se enviarÃ¡ al servidor
char bandera1 = 0;                                       // variable auxiliar para evitar el rebote al oprimir el botÃ³n 1
char bandera2 = 0;                                       // variable auxiliar para evitar el rebote al oprimir el botÃ³n 2
char bandera3 = 0;                                       // variable auxiliar para evitar el rebote al oprimir el botÃ³n 3
char bandera4 = 0;                                       // variable auxiliar para evitar el rebote al oprimir el botÃ³n 4
char aceptar  = 0;                                        // variable que permite enviar ruta de trabajo al servidor

unsigned int btn1=0, btn2=0, btn3=0, btn4=0, btn5=0;  // variables botones
char aux;
char punto[4], pt=0;                                  // variables para reconocer geocercas
//--------------------------------------------------------------------------------------------------------------------------------------------//

static unsigned int time_count;   // Contador del timer para los segundos
static unsigned int act;          // Variable que guarda si la pantalla es autorizada

eeprom int seg   @0x10;
eeprom int seg1  @0x12;    // segundos en unidades y decenas
eeprom int minu  @0x14;   
eeprom int min1  @0x16;    // minutos en unidades y decenas
eeprom int hora  @0x18;  
eeprom int hora1 @0x1A;   // hora en unidades y decenas
eeprom int dia   @0x1C;   
eeprom int dia1  @0x1E;    // dias en unidades y decenas
eeprom int mes   @0x20;   
eeprom int mes1  @0x22;    // mes en unidades y decenas
eeprom int an    @0x24;
eeprom int an1   @0x26;     // anos en unidades y decenas

eeprom int8 num_ruta @0x28;        // Transforma la letra de la ruta a un número
eeprom int laborando     @0x2A;        // Sabe si el chofer ha iniciado sesion o no.

int gsm, gps, ind_sen; //indicadores de señal
char reloj[8], fecha[8];  //vectores para imprmir GLCD




/////////////////////////////////////////////// INTERRUPCION DEL TIMER0 (CUENTA CADA SEGUNDO) /////////////////////////////////////////////////
interrupt [TIM0_OVF] void timer0_ovf_isr(void)
{
   TCNT0 = 6; 
   ++time_count; 
   
   if ( time_count == 43 )
   {
      seg++; 
      time_count = 0;  //reiniciar contador
      
      //Envia las tramas para validar el nombre y la seÃ±al del equipo - cada segundo
         if(seg==4) printf("AT$TTDEVID?\n\r");  // Pregunta el ID del equipo
         if(seg==9) printf("AT+CSQ\n\r");      // Pregunta la intensidad de senal
          
      if (seg>9)
      {
         seg=0; seg1++;
      
         //EnvÃ­o pra ver antenas, igualar hora y fecha...
         // Envio cada 20 segundos
         if (seg1%2==0)  
         {
            printf("AT$TTNETIP?\n\r");
         }else{
            printf("AT$TTGPSQRY=10,0\n\r");   // Igualar la hora
         }  //
           
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


\
//***********************************************************************************************************************************//
//////////////////////////////////////////////////////////// FUNCIONES ////////////////////////////////////////////////////////////////
//***********************************************************************************************************************************//



////////////////// FUNCIÓN PARA EL SONIDO DEL BUZZER //////////////////
/** \brief Genera el sonido del buffer
 *
 * El tiempo que suena depende del Macro: DELAY BUZZER
 */
void buzz()
{       //Sonido de Buzzer
   buzzer=1; delay_ms( DELAY_BUZZER_MS );
   buzzer=0; delay_ms( DELAY_BUZZER_MS );
}
//-------------------------------------------------------------------//


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
   int8 num_ruta = ruta - 0x40;

   // Verificar que la letra corresponde a un número de ruta
   // se puede crecer hasta 5 rutas mas de las definidas
   if ( num_ruta > 0 && num_ruta <= TOTAL_RUTAS + 5 )
      return num_ruta;
   else
      return 0; // El caracter no corresponde a una ruta.

}


///////////////////// FUNCION DEL BOTON 1 (INICIO/FIN DE JORNADA) //////////////////////////
void boton1()
{  
   if( BT1 == 0 && bandera1==0)
   {
      btn1++;
      bandera1=1;
      laborando=1;
      buzz();
      aux = 1;  
      delay_ms( DELAY_BOTONES_MS );
      if(btn1 > 1)  // No pasa al caso 2
         btn1 = 0;

   } 
   else if(BT1==1 && bandera1==1){
      bandera1=0;
   }

   switch (btn1) {
      
      //solamente quita la ruta de la pantalla
      //no cierra sesion de la ruta actual
      case 0:
         if(aux == 1) // El aux 1 es para que se ejecute este codigo solo una vez?
         {
            bmp_disp( vacio, 0, 5, 25, 7);   // Borra el chofer
            btn2 = 15;                       // Carrera Vacia
            aux = 0;                         // Hace una vez mientras se presione 
                                             // el boton
            
            laborando = 0;  // No se encuentra en laborando.

            // Borra el caracter de la carrera
            glcd_putchar(' ',79,7,0,1); 
            // Borra una trama de caracteres RUTA:
            glcd_puts("      ",44,7,0,1,-1); 
         }      
      break; 
      

      case 1:
         if(aux==1)
         {
            aux=0; 

            // Muestra la RUTA A: primero y por defecto
            btn2 = 1;
            
            //Muestra el chofer
            bmp_disp(chofer,0,5,35,7); 

            // Muestra la ruta
            glcd_puts("RUTA:",44,7,0,1,-1);
         } 
         break;
      
      case 2:
      break;
   };  
}
//------------------------------------------------------------------------------------------//



///////////////////////// FUNCION DEL BOTON 2 (ESCOGER RUTA AUMENTAR LETRA) /////////////////////////////////
void boton2(){     
   
   // Si se presiona el boton dos, luego de haber presionado el boton
   // uno, una vez. Y aún no se ha aceptado carrera
   if(BT2==0 && btn1==1 && bandera2==0 && aceptar == 0)
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
   };         
      
     //printf("AT$TTDEVID?\n\r")                     
}
//----------------------------------------------------------------------------------------//



/////////////////////// FUNCION DEL BOTON 3 (ESCOGER RUTA DECREMENTAR LETRA) /////////////////////////////////
void boton3()
{     //Boton 3
   if(BT3 == 0 && btn1==1 && bandera3==0 && aceptar==0)
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
//------------------------------------------------------------------------------------------------------//



//////////////////////// FUNCION DEL BOTON 4 (INICIO/FIN DE RUTA) /////////////////////////////////
void boton4()
{     //Boton 4
   

   // Primera presiónn del boton 4. Acepta la carrera. 
   if ( BT4 == 0 && bandera4 == 0 && aceptar==0 && laborando==1 )
   { 
      bandera4++;
      ruta = ruta_aux;
      aceptar = 1;
      buzz();
      delay_ms(200);

      // AQUI SE DEBE ENVIAR LA TRAMA CON LA RUTA
      // NO SE PUEDE ENVIAR SI NO SE HA ESCOGIDO UNA RUTA
      num_ruta = calcuar_ruta( ruta );

      printf("AT$MSGSND=4,\"$$BL%s,%d%d%d%d20%d%d,%d%d%d%d%d%d,R2,%d,%d:XX##\"\r\n", 
                                 NUM_DISP, 
                                      dia1,dia,
                                      mes1,mes,
                                      an1,an,
                                          hora1,hora,
                                          min1,min,
                                          seg1,seg,
                                             num_ruta,aceptar  );
      

   }

   
   //  ?? Porq
   // si esque ya se ha presionado el BOTON 3 y se levanta el BOTON 4
   else if(BT4 == 1 && bandera3==1)
   {
      bandera4++;
   }
   
   // La segunda vez que se presiona el boton dos
   if ( BT4==0 && aceptar == 1)
   {
      btn2=15;
      bandera4++;
      ruta=' ';
      aceptar=0;
      buzz();
      delay_ms( DELAY_BOTONES_MS );
      
      // AQUÍ SE DEBE ENVIAR LA TRAMA CON LA RUTA VACIA (FIN DE RUTA)
      num_ruta = calcuar_ruta( ruta );

      printf("AT$MSGSND=4,\"$$BL%s,%d%d%d%d20%d%d,%d%d%d%d%d%d,R2,%d,%d:XX##\"\r\n", 
                              NUM_DISP, 
                                   dia1,dia,
                                   mes1,mes,
                                   an1,an,
                                       hora1,hora,
                                       min1,min,
                                       seg1,seg,
                                          num_ruta,aceptar  );

   }
   
   // si se ha presionado el boton cuatro por tercera vez
   else if(BT4==1 && bandera4==1)
   {
      bandera4=0;
   }
}
//----------------------------------------------------------------------------------------//



////////////////////// FUNCION DEL BOTON 5 (ESTADO MECÃNICO) //////////////////////////////
void boton5(){     //Boton 5
  btn5++;
}
//----------------------------------------------------------------------------------------//



////////////////////////////////// DIBUJAR BARRAS DE SEÃ‘AL GPRS //////////////////////////////////////
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
//------------------------------------------------------------------------------------------------//



/////////////////////////////////// FUNCIÃ“N PARA OBTENER LA TRAMA DEL GPS SKYPATROLL+ //////////////////////////////////
void obt(void)
{

   int i,j,n=0,n1,n2,n3,n4,ini,coma=0,pos1=0,pos2=0,pos3=0,barras;
   
   for (i=0; i<RX_BUFFER_SIZE0 ;i++) 
   {     
     
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
        // Datos de punto de control, en cada posiciÃ³n del vector guardo una letra, luego hay que procesar para obtener el numero correcto. 
        punto[3] = rx_b0[i+19];
        punto[2] = rx_b0[i+18];
        punto[1] = rx_b0[i+17];
        punto[0] = rx_b0[i+16];
        
      //El 18 es el numero de evento, lo identifico para determinar si es geocerca, si esta bien se pone en 1 la variable "pt"
        if( rx_b0[i+22]=='1' &&  rx_b0[i+23]=='8'){
        pt = 1;   
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
            }else{
               
               //  ?? Porq volver a limpiar
               glcd_clrln(2); 
               glcd_clrln(3); 
               glcd_clrln(4); 
               glcd_clrln(5);

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
         // en caso de no haber seÃ±al gps.
         if( (rx_b0[ pos1+1 ]-48)>= 0 && 
             (rx_b0[ pos1+1 ]-48)< 10 &&
              pos2 != (pos1 +1)
           )
         {
     
            seg  =rx_b0[pos1 + 6 ]-48;
            seg1 =rx_b0[pos1 + 5 ]-48;
            minu =rx_b0[pos1 + 4 ]-48;
            min1 =rx_b0[pos1 + 3 ]-48;
            n2   =rx_b0[pos1 + 2 ]-48;
            n1   =rx_b0[pos1 + 1 ]-48;
      
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
    
         gps = rx_b0 [ pos2 + 1 ]; 
         printf( "%c", gps);
     
         //Obtener Hora y dÃ­a
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

            // ??
            an1  = an1;
            an   = an;
            mes1 = mes1;
            mes  = mes;
            dia1 = dia1;
            dia  = dia; 
         }
      }
   }
    
   rx_counter0  = 0;
   rx_wr_index0 = 0; 
    
   BIT_UART=1;     
   
   for (j=0;j<201;j++) 
   {
      rx_b0[j]=0;
   };
}

//-------------------------------------------------------------------------------------------------------------------//




/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//******************************************** PROGRAMA PRINCIPAL *************************************************//
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void main(void)
{
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

   //Tiempo q muestra la pantalla de inicio
   delay_ms( DELAY_PANTALLA_INI ); 
   glcd_clear();             

   
   ////////////  VALORES INICIALES PARA VARIABLES DE LA EEPROM ///////////

   // En caso de que no haya recibido tramas del sky
   // previene que muestre valores de -1 en la hora y fecha
   if (hora1 < 0 )
   {
      hora1 = 0; min1 = 0; seg1 = 0;
        hora = 0; minu = 0;  seg = 0;
   }

   // En caso de que no haya fecha
   if (mes < 0 )
   {
      dia = 0; dia1 = 0; 
       mes = 0; mes1 = 0;
        an = 0;  an1 = 0; 
   }

   if (num_ruta < 0) num_ruta = 0;

   ////////////////////////////////////////////////////////////////////
   

   // Encender interrupciones
   #asm("sei")

   // Muestra vacio
   bmp_disp(vacio,0,5,25,7);

   // Pide el ID del Skypatrol para verificar la pantalla
   printf("AT$TTDEVID?\n\r"); 
   delay_us( 500 );
   obt();
   
   act =1;
   bandera1 = 0;
   bandera2 = 0;
   bandera3 = 0;

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
      

         // Para mostrar el  Reloj
         if(pt==0) 
         {
            
            sprintf(reloj,"%d%d:%d%d:%d%d",hora1, hora, min1, minu, seg1, seg);
            glcd_puts(reloj,7,2,0,2,-1);     
         } 
         
         else
         {     //Entra a esta funcion cuando llega un punto de control, verificando por el evento 18  pt=1
               glcd_clrln(2); 
               glcd_clrln(3); 
               glcd_clrln(4); 
               glcd_clrln(5);
               delay_ms(1);
               glcd_puts("Punto de control",5,2,0,1,-1);
               glcd_puts(punto,34,4,0,1,-1);       
               buzz();
               buzz();
               delay_ms(2000);
               pt=0;   //esta variable se pone en 0 para que se vuelva a mostrar el reloj
               glcd_clrln(2); 
               glcd_clrln(3); 
               glcd_clrln(4); 
               glcd_clrln(5); 
          }


         // Con seÃ±al GPS
         if( gps == 'A' )
         {     
            bmp_disp(GPS1,95,0,127,1);   

            // En caso de que no haya recibido tramas del sky
            if (hora1 == 0xff )
            {
               hora1 = 0; min1 = 0; seg1 = 0;
                 hora = 0; minu = 0;  seg = 0;
            }
            sprintf(fecha,"20%d%d-%d%d-%d%d",an1, an, mes1, mes, dia1, dia);
            glcd_puts(fecha,34,5,0,1,-1); 
         
         }
         // Sin seÃ±al GPS
         else if (gps == 'V' || gps == '9' )
         {
            bmp_disp(GPS2,95,0,127,1);
            
            // En caso de que no haya recibido tramas del sky
            if (hora1 == 0xff )
            {
               hora1 = 0; min1 = 0; seg1 = 0;
                 hora = 0; minu = 0;  seg = 0;
            }
            sprintf(fecha,"20%d%d-%d%d-%d%d",an1, an, mes1, mes, dia1, dia);
            glcd_puts(fecha,34,5,0,1,-1);
         }
         else
         { 
            bmp_disp(GPS2,95,0,127,1);
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
