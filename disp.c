/**********************************************\
 *       Kradac Robotics & Electronics        *
 *                                            *
 *  Proyecto:     Kioskos UTPL                *
 *  Programador:  Vicente Q && Ernesto P && David Novillo      *
 *  version:      1.0.1                       *
 *  Fecha:        11/08/2014                  *
 *                                            *
 **********************************************
 *
 *  
 *  TEXTO AGREGADO
 *  
 *  
 *
 *  
 *
 *  
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


////////////////////   INTERRUPCIÓN SERIAL  /////////////////////
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



#define NOMBRE_PANTALLA  "SITU"
#define NUMERO_PANTALLA  "BUS1697"
#define DELAY_BUZZER     100

#define RX_BUFFER_SIZE0 200             //BUFFER DE 200 CARACTERES
char rx_b0 [RX_BUFFER_SIZE0];           //nombre del buffer 

#if RX_BUFFER_SIZE0 <= 256
unsigned char rx_wr_index0,rx_rd_index0,rx_counter0;
#else
unsigned int rx_wr_index0,rx_rd_index0,rx_counter0;
#endif

// This flag is set on USART0 Receiver buffer overflow
bit rx_buffer_overflow0;
bit d;


/** \brief USART0 Receiver interrupt service routine
 *
 * Captura datos desde el puerto serial UART0
 */
interrupt [USART0_RXC] void usart0_rx_isr(void)
{  
   char status,data;
   status = UCSR0A;
   data   = UDR0;
   d = UCSR0A & 0b10000000;

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
////////////////////  FIN INTERRUPCIÓN SERIAL  ///////////////////



////////////////////  DEFINIR PUERTOS BOTONES - BUZZER  //////////
#define BT5 PINA.0
#define BT4 PINA.1
#define BT3 PINA.2
#define BT2 PINA.3
#define BT1 PINA.4
#define buzzer PORTD.4
///////////////////////////////////////////////////////////////////


//-----------------------VARIABLES---------------------------------
char str2[] = NOMBRE_PANTALLA;
char str3[] = NUMERO_PANTALLA;

unsigned int btn1=0, btn2=0, btn3=0, btn4=0, btn5=0;  //variables botones
char aux;
//----------------------------------------------------------------//

static unsigned int time_count, act;
eeprom int seg=0,seg1=0,minu=0,min1=0,hora=0,hora1=0,dia=0,dia1=0,mes=0,mes1=0,an=0,an1=0; //hora y fecha
int gsm, gps, ind_sen; //indicadores de señal
char reloj[8], fecha[8];  //vectores para imprmir GLCD



/** \brief Timer 0 overflow interrupt service routine
 *
 * Genera una interrupcíon cada: 
 */
interrupt [TIM0_OVF] void timer0_ovf_isr(void)
{
   TCNT0 = 6; 
   ++time_count; 
   
   if ( time_count == 43 )
   {
      seg++; 
      time_count = 0;  //reiniciar contador
      //Comprobar nombre
          if(seg==4) printf("AT$TTDEVID?\n\r");  // Pregunta el ID del equipo
          if(seg==9) printf("AT+CSQ\n\r");      // Pregunta la intensidad de senal
          
      if (seg>9)
      {
         seg=0; seg1++;
      
         //Envío pra ver antenas, igualar hora y fecha...
         // Envio cada dos minutos
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

//-----------------------FUNCIONES---------------------------------

/** \brief Genera el sonido del buffer
 *
 * El tiempo que suena depende de la variable DELAY BUZZER
 */
void buzz()
{       //Sonido de Buzzer
   buzzer=1; delay_ms(DELAY_BUZZER);
   buzzer=0; delay_ms(DELAY_BUZZER);
}

/** \brief Boton Uno - Cambiar de ruta
 *
 * Selecciona la acción de cambio de ruta
 */
void boton1()
{  
   if( BT1 == 0)
   {
      btn1++;
      buzz();
      aux = 1;
      
      delay_ms(200);
      
      if(btn1 > 1)  // No pasa al caso 2
         btn1 = 0;
   } 

   switch (btn1) {
      case 0:
         if(aux==1)
         {
            bmp_disp( vacio, 0, 5, 25, 7);
            btn2=0; 
            aux=0; 
            
            // Borra un caracter
            glcd_putchar(' ',76,7,0,1); 
            // Borra una trama de caracteres
            glcd_puts("     ",44,7,0,1,-1); 
         }      
         break; 
      
      case 1:
         if(aux==1)
         {
            aux=0; 
            
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

/** \brief Boton Dos - Selecciona la ruta
 *
 * Selecciona la ruta en la cual se va a trabajar
 *
 */
void boton2()
{     
   if(BT2==0 && btn1==1)
   {
      btn2++; 
      buzz(); 
      delay_ms(200);

      if(btn2>12) 
         btn2=0;
   }  
      switch (btn2){
      case 1:
      glcd_putchar('A',77,7,0,1);
      break;
      case 2:
      glcd_putchar('B',77,7,0,1);
      break;
      case 3:
      glcd_putchar('C',77,7,0,1);
      break; 
      case 4:
      glcd_putchar('D',77,7,0,1);
      break; 
      case 5:
      glcd_putchar('E',77,7,0,1);
      break; 
      case 6:
      glcd_putchar('F',77,7,0,1);
      break; 
      case 7:
      glcd_putchar('G',77,7,0,1);
      break; 
      case 8:
      glcd_putchar('H',77,7,0,1);
      break;
      case 9:
      glcd_putchar('I',77,7,0,1);
      break; 
      case 10:
      glcd_putchar('J',79,7,0,1);
      break; 
      case 11:
      glcd_putchar('K',79,7,0,1);
      break;
      case 12:
      glcd_putchar('L',79,7,0,1);
      break;   
      }; 
     //printf("AT$TTDEVID?\n\r")                
}

void boton3(){     //Botón 3
btn3++;
}

void boton4(){     //Botón 4
btn4++;
}

void boton5(){     //Botón 5
btn5++;
}

/** \brief ??
 *
 * 
 *
 */
void sen (void){
    switch (ind_sen) {
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

/** \brief Recorrer el arreglo que envia el SKYPATROL
 *
 * Obtiene las tramas
 *
 */
void obt(void)
{

   int i,j,n=0,n1,n2,n3,n4,ini,coma=0,pos1=0,pos2=0,pos3=0,sen;
   
   for (i=0; i<RX_BUFFER_SIZE0 ;i++) 
   {     
     
      //+CSQ: 
      if ( rx_b0[i+0]== '+' &&    //43d
            rx_b0[i+1]== 'C' &&     //67d
             rx_b0[i+2]== 'S' &&    //83d
              rx_b0[i+3]== 'Q' &&   //81d
               rx_b0[i+4]== ':')    //58d
      { 
        // Valor decimal
        sen = ((rx_b0[i+6]-48)*10)+(rx_b0[i+7]-48);

        
        if(sen>10 && sen<15){
        ind_sen=1;
        }

        else if(sen>=15 && sen<18){
        ind_sen=2;
        } 

        else if(sen>=18 && sen<31){
        ind_sen=3;
        }

        else{
        ind_sen=4;
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
               gsm=0;   // Sin señal GSM
            
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
            if( rx_b0[pos1+2]==str3[0] && 
                rx_b0[pos1+3]==str3[1] && 
                rx_b0[pos1+4]==str3[2] && 
                rx_b0[pos1+5]==str3[3] )
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
     
      //Encabezado: GPRMC
      if ( rx_b0[i]==71 && 
            rx_b0[i+1]==80 && 
             rx_b0[i+2]==82 && 
              rx_b0[i+3]==77 && 
               rx_b0[i+4]==67)
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

         if( (rx_b0[ pos1+1 ]-48)>= 0 && 
             (rx_b0[ pos1+1 ]-48)< 10 )
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
     
         //Obtener Hora y día
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
    
   d=1;     
   
   for (j=0;j<201;j++) 
   {
      rx_b0[j]=0;
   };

}

//---------------------------------------------------------------//

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
   delay_ms(10);
   glcd_clear();

   buzz();
   buzz();

   // Dibuja KRADAC
   bmp_disp(arr,0,0,127,7);
   delay_ms(2000);
   glcd_clear();

   // Dibuja BUS
   bmp_disp(bus,0,0,45,7);

   // Escribe NOMBRE_PANTALLA "SITU"
   glcd_puts(str2,55,2,0,2,-1);    

   // Escribe NUMERO_PANTALLA "BUS####"
   //glcd_puts("BUS",55,5,0,1,-1);
   glcd_puts(str3,59,5,0,1,-1);

   delay_ms(2000); 
   glcd_clear();             

   // Encender interrupciones
   #asm("sei")

   // Muestra vacio
   bmp_disp(vacio,0,5,25,7);

   // Pide el ID del Skypatrol
   printf("AT$TTDEVID?\n\r"); 
   delay_us( 500 );
   obt();

   while (1)
   {

      if( d == 0 ) 
      {   
         obt();
         d=1;  
      }
      
      boton1();

      boton2();                                          

      sen();
      
      // act = autoirzado
      if(act==1)
      {
         if(gsm==1)
         {
            glcd_putchar('E',19,0,1,1);
         }else{
            glcd_putchar(' ',19,0,1,1);
         } 
      
         // Iguala Reloj
         sprintf(reloj,"%d%d:%d%d:%d%d",hora1, hora, min1, minu, seg1, seg);
         glcd_puts(reloj,7,2,0,2,-1);     

         // Con señal GPS
         if( gps == 'A' )
         {     
            bmp_disp(GPS1,95,0,127,1);   
            sprintf(fecha,"20%d%d-%d%d-%d%d",an1, an, mes1, mes, dia1, dia);
            glcd_puts(fecha,34,5,0,1,-1); 
         
         }
         // Sin señal GPS
         else if (gps == 'V' || gps == '9' )
         {
            bmp_disp(GPS2,95,0,127,1);
            sprintf(fecha,"20%d%d-%d%d-%d%d",an1, an, mes1, mes, dia1, dia);
            glcd_puts(fecha,34,5,0,1,-1);
         }
         else
         { 
            bmp_disp(GPS2,95,0,127,1);
            glcd_puts(reloj,7,2,0,2,-1);  
            glcd_puts(fecha,34,5,0,1,-1);
         }
      }
      
      else 
      {   
         glcd_puts("Pantalla",30,2,0,1,-1);
         glcd_puts("No Autorizada",15,4,0,1,-1);
      }  
         
         bmp_disp(frente,105,5,127,7);  
      }
}
