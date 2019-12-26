#ifndef mef_h
#define mef_h

#include "Arduino.h"

/* Definicion de puertos */
#define LED1      5 //Led correspondiente al sensor ultrasonido de atras derecha
#define LED2      4 //Led correspondiente al sensor ultrasonido de atras izquierda
#define LED3      3 //Led correspondiente al sensor ultrasonido de adelante
#define LED_CTRL  13 //Led correspondiente al prendido y apagado del sistema	
#define PULSADOR  2 //Pin asociado al pulsador que utiliza la interrupcion 3


/* Definicion de las interrupciones, cada tick equivale a 100ms */
#define INTERRUPCION_RELOJ 10
#define INTERRUPCION_SENSOR 5

/* Definicion de Limites y tiempo de parpadeo de los leds */

#define LIMITE_UNO 30
#define LIMITE_DOS 20
#define LIMITE_TRES 10

#define PARPADEO_UNO 4
#define PARPADEO_DOS 3
#define PARPADEO_TRES 2
#define PARPADEO_CUATRO 1

/* Definicion de estructuras */


struct StructHora{
	int minutos;
	int segundos;
};


/* Definicion de funcions */

void Init(void);
void Init_Led(void);
void Init_Timers(void);
void Init_Pulsador(void);


void sensando(void); //Estado esperando
void interruptHandler(void); //Actualiza la hora
void ActualizarLed(void); //Actualiza los leds en base a las distancias calculadas
void ActualizarHora(void); //Actualiza la hora y la envia
void AlternarLed(int i); //Cambiar el estado del led dependiendo si estaba apagado o prendido
void apagarLed(int i);
void prenderLed(int i);

#endif
