#include "sensorUltrasonido.h"
#include "Arduino.h"
#include <NewPing.h>

/* Definicion de variables para el ultrasonido */


volatile int distancia[3]; //Arreglo de distancias calculada

NewPing sonar[SONAR_NUM] = { // Sensor object array.
  NewPing(TRIGGER_PIN_SENSOR1, ECHO_PING_SENSOR1, MAX_DISTANCE),
  NewPing(TRIGGER_PIN_SENSOR2, ECHO_PING_SENSOR2, MAX_DISTANCE),
  NewPing(TRIGGER_PIN_SENSOR3, ECHO_PING_SENSOR3, MAX_DISTANCE)
};

/* Funciones */


/*Funcion que se encarga de hacer un sensado de cada sensor ultrasonico y devolver la distancia en centrimetros */

void comenzarSensado(void){

 for (int i=0;i<SONAR_NUM;i++){
    distancia[i]=sonar[i].ping_cm();

 }

}

