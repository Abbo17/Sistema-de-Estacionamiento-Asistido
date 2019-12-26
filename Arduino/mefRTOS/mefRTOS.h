#ifndef mefRTOS_h
#define mefRTOS_h

#include "Arduino.h"

/* Definicion de puertos */
#define LED1      5 //Led correspondiente al sensor ultrasonido de atras derecha
#define LED2      4 //Led correspondiente al sensor ultrasonido de atras izquierda
#define LED3      3 //Led correspondiente al sensor ultrasonido de adelante
#define LED_CTRL  13 //Led correspondiente al prendido y apagado del sistema	
#define PULSADOR  2 //Pin asociado al pulsador que utiliza la interrupcion 3


/* Definicion de las interrupciones, cada tick equivale a 100ms */
#define INTERRUPCION_RELOJ 31
#define INTERRUPCION_SENSOR 10

/* Definicion de Limites y tiempo de parpadeo de los leds */

#define LIMITE_UNO 30
#define LIMITE_DOS 20
#define LIMITE_TRES 10

#define PARPADEO_UNO 10
#define PARPADEO_DOS 7
#define PARPADEO_TRES 4
#define PARPADEO_CUATRO 2

/* Definicion de estructuras */


struct StructHora{
	int minutos;
	int segundos;
};


/* Definicion de funcions */
void init_Prueba(void);
void Prueba(void);

void Init(void);
void Init_Led(void);
void Init_Timers(void);
void sensando(void *pvParameters);

void TareaTimer(void *pvParameters ); //Actualiza la hora
void ActualizarHora(void); //Actualiza la hora y la envia

void ActualizarLed(void); //Actualiza los leds en base a las distancias calculadas
void AlternarLed(int i); //Cambiar el estado del led dependiendo si estaba apagado o prendido
void apagarLed(int i);
void prenderLed(int i);

/*Tareas */
void Init_Semaforos(void);
void Eliminar_Semaforos(void); 

void Init_Tareas(void);
void Eliminar_Tareas(void);

void TareaReloj( void *pvParameters );
void TareaSensor(void *pvParameters);
void TareaLeds(void *pvParameters);
void info(void);

#endif
