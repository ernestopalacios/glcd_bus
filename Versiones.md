Registro de cambios:

Pendientes:
* Login Mediante contraseña
* Habilitar BOTON DE ESTADO MECANICO
* Habilitar NOMBRE BUS desde SkyPatrol.

Observaciones:


--------------------------       27-10-2014      -------------------------------------------
version 0.9.7.x

- Se añadio el inicio por contraseña, se utiliza un algoritmo simple para comprobar si la clave ingresada es valida.

- Se cambio a Estructuras de datos y se divivio el código en futuras librerias.

- Se cambinaron algunas imagenes y se ahorro un 15% de la memoria del micro.

- Se creo una lista de elementos ENUM para la variable 'pantalla' la cual controla lo que se muestra en la GLCD



--------------------------       27-10-2014      -------------------------------------------
version 0.9.6.0

- Se cambio el reloj, ya no guarda en la EEPROM, y cada reinicio commienza el reloj en 00:00:00

- Se creo la Libreria de reloj_display.h en la cual se implementa funciones para verificar que la
  fecha y la hora sea correcta.

- Se requiere el ingreso mediante identificativo del conductor, comprueba que el codigo sea valido mediante algoritmo.

  
