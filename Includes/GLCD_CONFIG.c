/**********************************************\
 *       Kradac Robotics & Electronics        *
 *                                            *
 *  Proyecto:       GLCD BUS LOJA             *
 *  Programadores:  Ernesto P                 *
 *                  						          * 
 *  version:        0.9.6.2                   *
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
  * @filename: GLCD_CONFIG.c
  * 
  * @detail: Archivo donde se alojan las configuraciones para la GLCD_DISPLAY 
  *          de los buses de la ciudad de Loja.
  *          
  */

 #ifndef GLCD_CONFIG_C
 #define GLCD_CONFIG_C


/////////////////////////  CONFIGURACIONES GLOBALES DEL PROGRAMA //////////////////////

   ////////////////////////////////  TIPOS DE VARIABLES  /////////////////////////////////

      typedef char int8;    // sirve para definir enteros SIN SIGNO de 8 bits

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

   /////////////////////////////// DEFINICIONES DE PUERTO SERIAL   //////////////////////////

      #define RX_BUFFER_SIZE0 200              //BUFFER DE 200 CARACTERES para la recepcion serial  ***
      char rx_b0 [RX_BUFFER_SIZE0];           // nombre del buffer 

      char test[12] = {'H','o','l','a',' ','P','T','R',0x00};

      char *ptr_HOLA = test;


      // char* ptr_BUFFER_SERIAL = rx_b0;      // Puntero al buffer serial

      # define TXT_BUF_SZ 160                     // TAMANIO maximo que puede ser el mensaje a la GLCD 
      char txt_glcd_b0[ TXT_BUF_SZ ];            // Buffer para almacenar los caracteres a mostrarse en la GLCD
      char i_txt_glcd = 0;             // contador para recorrer el arreglo del buffer
      char i_txt_overflow = 0;        // Si los caracteres son mas de 100 ignora los demas caracteres
   
      #if RX_BUFFER_SIZE0 <= 256
      unsigned char rx_wr_index0,rx_rd_index0,rx_counter0;
      #else
      unsigned int rx_wr_index0,rx_rd_index0,rx_counter0;
      #endif
      
      // This flag is set on USART0 Receiver buffer overflow
      bit rx_buffer_overflow0;
      bit BIT_UART;
   //----------------------------------------------------------------------------------------
  

   #define VERSION               "ver 0.9.7"        // BERSION QUE SE MUESTRA EN EL DISPLAY ***
   #define NOMBRE_PANTALLA       "SITU"
   #define NUMERO_PANTALLA       "8888"             // Hay que obtener el ID desde el skypatrol
   
   #define NUM_RUTAS_ACTIVAS         12             // Numero maximo de rutas activas
   #define TOTAL_RUTAS              100             // Número total de rutas
   #define MOSTRAR_NUM_RUTA_MS     2000             // Tiempo que se muestra el nombre de la Geocerca
   #define MOSTRAR_MSN_ENV_MS      1000             // Tiempo que muestra MENSAJE ENVIADO
   
   #define DELAY_BUZZER_MS          100             // Delay del Pitido del Buzzer
   #define DELAY_BOTONES_MS         100             // Delay Para evitar rebotes en los botones
   #define INIT_DELAY_GLCD_MS        10             // Delay para que se dibuje siempre bien la GLCD
   #define DELAY_PANTALLA_INI      2000             // Tiempo que se muestra el logo de KRADAC
   #define DELAY_TXT_SERVIDOR      3000             // Tiempo que se muestra el MENSAJE DESDE EL SERVIDOR

   #define DESCONEXION_SKYPATROL    180             // Segundos antes que asuma que no tiene conectado un 
                                                    // SkyPatrol, si llega trama serial desde Sky se resetea el contador


   /////////////////////////  DEFINIR PUERTOS BOTONES - BUZZER  //////////////////////////
   #define BT5 PINA.0
   #define BT4 PINA.1
   #define BT3 PINA.2
   #define BT2 PINA.3
   #define BT1 PINA.4
   #define buzzer PORTD.4
//----------------------------------------------------------------------------------------


///////////////////////////////////////////////// VARIABLES  GLOBALES   /////////////////////////////////////////

   char NOMBRE_DISP[] = NOMBRE_PANTALLA;       // variable Cadena de Caracteres 
   char NUM_DISP[] = NUMERO_PANTALLA;          // variable Cadena de Caracteres
   char ruta= ' ';                             // variable donde se almacena la ruta que se enviarA al servidor
   char bandera1 = 0;                          // variable auxiliar para evitar el rebote al oprimir el boton 1
   char bandera2 = 0;                          // variable auxiliar para evitar el rebote al oprimir el boton 2
   char bandera3 = 0;                          // variable auxiliar para evitar el rebote al oprimir el boton 3
   char bandera4 = 0;                          // variable auxiliar para evitar el rebote al oprimir el boton 4
   char bandera5 = 0;                          // variable auxiliar para evitar el rebote al oprimir el boton 4
   char aceptar  = 0;                          // variable que permite enviar ruta de trabajo al servidor
   char _laborando = 0;                        // variable para saber si la Contraseña se ha validado
   
   int  timer_sin_conexion = 0;                // Cuenta los segundos que pasa sin recibir trama desde SkyPatrol
   char bnd_sin_sesion = 0;                    // variable para saber si aun no inicia sesion
   int8 conexion_skypatrol = 0;                // Espera 3min antes de declarar que no hay conexion con SkyPatrol = 0;
   char bnd_sin_conexion = 0;                  // variable para saber si ha perdido conexion con el Skypatrol
                                               // Depende del sin que se haya recibido alguna trama desde SkyPatrol

   // Contadores de las presiones de botones
   char btn1 = 0;                           //  Cuenta entre 1 y 2 = 1 Inicia Sesion, 2 Cierra sesion 
   char btn4 = 0;                         // Cuenta entre 1 y 2 = 1 Acepta Ruta, 2 Cancela Carrera
   char btn5 = 0;                        // Cuenta entre 0 y 11 = Cambia los estados mecanicos del bus.
   char num_ruta_sel = 0;               // Cuentra entre 1 y 12 =  Ruta seleccionada. Boton 2 aumenta el contador

   int gsm, gps, ind_sen;       //indicadores de señal
   char reloj_c[8], fecha[8];  //vectores para imprmir GLCD

   char punto[4];            // Punto de control
   char no_pt[4];           // variables para reconocer geocercas
   int unidades_ruta; 
   int decenas_ruta; 
   int centenas_ruta;
   
   int8 pantalla = 0;       // Numero de pantalla a mostrar en la GLCD

   // Estado mecanico
   char bnd_cambio_mecanico = 0;
 
   int8 i_timer_1 = 0;                  // Contador Timer_1
   
   static unsigned int time_count;    // Contador del timer para los segundos
   static unsigned int act;           // Variable que guarda si la pantalla es autorizada

     
   //----------------------------------   VARIABLES TIEMPO  ------------------------------------//
   
   struct Tiempo Reloj;                 // Crea una estructura de tiempo para el Reloj que se muestra en el Display
   struct Tiempo RelojGPS;              // Crea una estructura de tiempo para el Reloj que se recibe desde el GPS


   // Estas vatribles se usan para obtener la hora desde la cadena de caracteres.
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

   //-----------------------------   VARIABLES CODIGO DE INGRESO    -----------------------//

   int8 bnd_ingresa_clave = 0;
   char id_conductor[7] = {0, 0, 0, 0, 0, 0, 0};

   int8 i_digitos = 0;
   
   int8 digito_0 = 0;
   int8 digito_1 = 0;
   int8 digito_2 = 0;
   int8 digito_3 = 0;
   int8 digito_4 = 0;
   int8 digito_5 = 0;


//***********************************************************************************************************************************//
////////////////////////////////////////////////////////     FUNCIONES     ////////////////////////////////////////////////////////////
//***********************************************************************************************************************************//

   
   /**
    * @brief Valida la clave ingresada por el usuario
    * @details Utiliza las variables globales previamente definidas
    * 
    * @param d Sin Parametros
    * @return 1 si la clave es valida, 0 si no lo es
    */
   int validar_clave( void ){

      // Sumatoria 
      unsigned int dobleDigito_1 = ( 2 * digito_1 ) % 10; 
      unsigned int dobleDigito_3 = ( 2 * digito_3 ) % 10; 

      unsigned int CRC_calc = ( digito_0 + dobleDigito_1 + digito_2 + dobleDigito_3 + digito_4 ) % 10; 

      //printf("\r  CRC Calculado: %d \n", CRC_calc );
      //printf("\r  CRC Ingresado: %d \n", digito_5 );

      if( CRC_calc == digito_5 && 
              (digito_0 + digito_1 + digito_2 + digito_3 + digito_4) != 0){  // Evita la clave 000000

        //printf("\r  CLAVE CORRECTA!\n"); 
        return 1;
      
      }else{

         //printf("\r  Clave ERRONEA \n");
         return 0;
      }

   }

   /**
    * @brief Genera el pitido del display
    * @details El tiempo que pita depende de #DEFINE
    */
   inline void buzz()
   {       //Sonido de Buzzer
      buzzer=1; delay_ms( DELAY_BUZZER_MS );
      buzzer=0; delay_ms( DELAY_BUZZER_MS );
   }
   

   /** @brief Envia inicio o fin de LOGIN del chofer para el calulo del recorrido
    *
    *  @details Para el inicio de trama envia un numero que representa el ID del chofer luego el estado. LOGIN/LOGOUT
    * 
    */
   void envia_estado_login(){
      printf("AT$TTSNDMG=4,\"$$BL%s,%02d%02d20%02d,%02d%02d%02d,S2,%s,%d:XX##\"\r\n", 
                                    NUM_DISP, 
                                         Reloj.dia, Reloj.mes, Reloj.an,
                                            Reloj.hora, Reloj.minu, Reloj.segu, 
                                                id_conductor, 
                                                  _laborando  );
   }
   

   /**
    * @brief Dibuja la intensidad de la senial GSM
    * @details El que se dibuje la senial no significa que se pueda enviar datos al servidor
    * 
    */
   void dibujar_senal( void )
   {
      switch ( ind_sen ){
         case 0:
            glcd_puts("___",0,0,0,1,-1);
         break;
         case 1:
            bmp_disp(GSM3,0,0,20,1);
         break;
         case 2:
            bmp_disp(GSM2,0,0,20,1);
         break;
         case 3:
            bmp_disp(Full_BMP,0,0,20,1);
         break;
         case 4:
            bmp_disp(GSM4,0,0,20,1);
         break;
         default:
            glcd_puts("___",0,0,0,1,-1);
         break;
      } 
   }
   //---------------------------------------------------------------------------//


   ////////////////// FUNCION DEL BOTON 1 (INICIO/FIN DE JORNADA) ///////////
      void boton1()
      {  
         if ( BT1 == 0 && bandera1 == 0 && bnd_ingresa_clave == 1 )  //Actua como numero
         {
            bandera1 = 1;

            // Actua como numero 0
            switch( i_digitos ){

               case 0:
                  digito_0 = 0;
                  glcd_puts("0",30,4,0,1,-1);
               break;
               
               case 1:
                  digito_1 = 0;
                  glcd_puts("*0",30,4,0,1,-1);
               break;
               
               case 2:
                  digito_2 = 0;
                  glcd_puts("**0",30,4,0,1,-1);
               break;
               
               case 3:
                  digito_3 = 0;
                  glcd_puts("***0",30,4,0,1,-1);
               break;
               
               case 4:
                  digito_4 = 0;
                  glcd_puts("****0",30,4,0,1,-1);
               break;

               case 5:
                  digito_5 = 0;
                  glcd_puts("*****0",30,4,0,1,-1);
               break;
                 
            }

            id_conductor[ i_digitos] = 0 + 48;
            i_digitos++;


         }else if( BT1 == 0 && bandera1 == 0 && aceptar == 0 ){   // Primera presion del boton

            btn1++;                          // Aumenta el contador del boton
            bandera1=1;                     // Evita que vuelva a entrar al mismo boton
            
            buzz();
            delay_ms( DELAY_BOTONES_MS );

            switch (btn1) 
            {
               // PRIMERA PRESION DEL BOTON
               case 1:
                  
                  // Envia Inicio de sesion al servidor
                  pantalla = 2;                     // Para q muestre en la glcd MENSAJE ENVIADO


               break;
               
               // SEGUNDA PRESION DEL BOTON
               //solamente quita la ruta de la pantalla
               //no cierra sesion de la ruta actual
               case 2:
                  
                  _laborando = 0;     // No se encuentra en laborando.
                  num_ruta_sel = 0;
                  pantalla=5;             // Muestra mensaje de FIN JORNADA  ***

                  bnd_sin_sesion = 0;
                  bnd_ingresa_clave = 0;
                  i_digitos = 0;

                  printf("AT$TTTRGEV=42,1,25\r\n");
                  
                  // Reiniciliza el contador, siguiente presion btn = 1;
                  btn1 = 0;
                  
               break; 

            }  
         }else if( BT1 == 1 && bandera1 == 1 ){ // Cuando se levanta el boton del dedo levant la bandera
            bandera1 = 0;
         }
      }
   //---------------------------------------------------------------------------//


   ////////////////// FUNCION DEL BOTON 2 (ESCOGER RUTA AUMENTAR LETRA) /////
      void boton2(){     
         
         if ( BT2 == 0 && bandera2 == 0 && bnd_ingresa_clave == 1 )
         {
            
            bandera2 = 1;

            // Actua como numero 1

            switch( i_digitos ){

               case 0:
                  digito_0 = 1;
                  glcd_puts("1",30,4,0,1,-1);
               break;
               
               case 1:
                  digito_1 = 1;
                  glcd_puts("*1",30,4,0,1,-1);
               break;
               
               case 2:
                  digito_2 = 1;
                  glcd_puts("**1",30,4,0,1,-1);
               break;
               
               case 3:
                  digito_3 = 1;
                  glcd_puts("***1",30,4,0,1,-1);
               break;
               
               case 4:
                  digito_4 = 1;
                  glcd_puts("****1",30,4,0,1,-1);
               break;

               case 5:
                  digito_5 = 1;
                  glcd_puts("*****1",30,4,0,1,-1);
               break;
                 
            }

            id_conductor[ i_digitos] = 1 + 48;
            i_digitos++;

         }


         // Si se presiona el boton dos, luego de haber presionado el boton
         // uno, una vez. Y aún no se ha aceptado carrera
         else if( BT2 == 0 && bandera2 == 0 && aceptar == 0 && _laborando == 1 )
         {
            num_ruta_sel++; 
            buzz();
            bandera2 = 1;  

            if( num_ruta_sel > NUM_RUTAS_ACTIVAS ) 
               num_ruta_sel = 1;

            if (pantalla == 9) // Solo actualiza el caracter de ruta, nada mas
               pantalla = 9;
            else
               pantalla = 8; // Muestra la pantalla de escoger ruta
               
            


            delay_ms(DELAY_BOTONES_MS);
         }  
         

         // Luego de presionar el boton, puede volver a presionarlo.
         else if(BT2==1 && bandera2==1)
         {
            bandera2=0;
         }

      }
   //---------------------------------------------------------------------------//


   ////////////////// FUNCION DEL BOTON 3 (ESCOGER RUTA DECREMENTAR LETRA) //
      void boton3()
      {     //Boton 3
         
         // Actua como numero 2

         if ( BT3 == 0 && bandera3 == 0 && bnd_ingresa_clave == 1 )
         {

            bandera3 = 1;
         
            switch( i_digitos ){

               case 0:
                  digito_0 = 2;
                  glcd_puts("2",30,4,0,1,-1);
               break;
               
               case 1:
                  digito_1 = 2;
                  glcd_puts("*2",30,4,0,1,-1);
               break;
               
               case 2:
                  digito_2 = 2;
                  glcd_puts("**2",30,4,0,1,-1);
               break;
               
               case 3:
                  digito_3 = 2;
                  glcd_puts("***2",30,4,0,1,-1);
               break;
               
               case 4:
                  digito_4 = 2;
                  glcd_puts("****2",30,4,0,1,-1);
               break;

               case 5:
                  digito_5 = 2;
                  glcd_puts("*****2",30,4,0,1,-1);
               break;
                 
            }

            id_conductor[ i_digitos] = 2 + 48;
            i_digitos++;


         }else if( BT3 == 0 && bandera3 == 0 && aceptar == 0 && _laborando == 1){
            num_ruta_sel--; 
            buzz();
            bandera3=1;  
            
            if(num_ruta_sel <= 0 || num_ruta_sel > NUM_RUTAS_ACTIVAS) 
               num_ruta_sel=NUM_RUTAS_ACTIVAS;
            
            if (pantalla == 9) // Solo actualiza el caracter de ruta, nada mas
               pantalla = 9;
            else
               pantalla = 8; // Muestra la pantalla de escoger ruta
            
            delay_ms( DELAY_BOTONES_MS );
         }  

         else if(BT3==1 && bandera3==1){
            bandera3=0;
         }
      }
   //---------------------------------------------------------------------------//


   ////////////////// FUNCION DEL BOTON 4 (INICIO/FIN DE RUTA) //////////////
      void boton4()
      {     //Boton 4
         
         // Actua como numero 3

         if ( BT4 == 0 && bandera4 == 0 && bnd_ingresa_clave == 1 )
         {

            bandera4 = 1;
            
            switch( i_digitos ){

               case 0:
                  digito_0 = 3;
                  glcd_puts("3",30,4,0,1,-1);
               break;
               
               case 1:
                  digito_1 = 3;
                  glcd_puts("*3",30,4,0,1,-1);
               break;
               
               case 2:
                  digito_2 = 3;
                  glcd_puts("**3",30,4,0,1,-1);
               break;
               
               case 3:
                  digito_3 = 3;
                  glcd_puts("***3",30,4,0,1,-1);
               break;
               
               case 4:
                  digito_4 = 3;
                  glcd_puts("****3",30,4,0,1,-1);
               break;

               case 5:
                  digito_5 = 3;
                  glcd_puts("*****3",30,4,0,1,-1);
               break;
                 
            }

            id_conductor[ i_digitos] = 3 + 48;
            i_digitos++;


         }
         // Primera presiónn del boton 4. Acepta la carrera. 
         else if ( BT4 == 0 && bandera4 == 0 && _laborando == 1  )
         { 
            bandera4++;           // Evita reentrada
            btn4++;              // Incrementa conteo de presiones del boton
            
            buzz();
            delay_ms(200);

            switch(btn4){

               case 1:
                  if ( num_ruta_sel != 0)
                  {
                     aceptar  = 1;         //Ha aceptado la Ruta
                     pantalla = 4;         // Muestra RUTA ACPETADA
                     printf("AT$TTTRGEV=42,1,%d\r\n",num_ruta_sel );
                     //enviar_estado_ruta();
                  }else{
                     btn4 --;
                  }
                  
               break;

               case 2:
                  aceptar  = 0;        // Fin de la ruta
                  printf("AT$TTTRGEV=42,1,23\r\n");
                  //enviar_estado_ruta();
                  num_ruta_sel = 0;     // Borra el caracter de ruta
                  pantalla = 3;       // Muestra FIN RUTA 
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
      void boton5()
      { 
      
         // Actua como numero 4

         if ( BT5 == 0 && bandera5 == 0 && bnd_ingresa_clave == 1 )
         {

            bandera5 = 1;
            
            switch( i_digitos ){

               case 0:
                  digito_0 = 4;
                  glcd_puts("4",30,4,0,1,-1);
               break;
               
               case 1:
                  digito_1 = 4;
                  glcd_puts("*4",30,4,0,1,-1);
               break;
               
               case 2:
                  digito_2 = 4;
                  glcd_puts("**4",30,4,0,1,-1);
               break;
               
               case 3:
                  digito_3 = 4;
                  glcd_puts("***4",30,4,0,1,-1);
               break;
               
               case 4:
                  digito_4 = 4;
                  glcd_puts("****4",30,4,0,1,-1);
               break;

               case 5:
                  digito_5 = 4;
                  glcd_puts("*****4",30,4,0,1,-2);               
               break;
                 
            }

            id_conductor[ i_digitos] = 4 + 48;
            i_digitos++;


         }else if( BT5 == 1 && bandera5 == 1 ){
            bandera5 = 0;         
         }
      }
   //---------------------------------------------------------------------------//

 #endif