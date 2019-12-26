
#ifndef bluetooth_h
#define bluetooth_h

#include "Arduino.h"

#define BTPWR 3
#define BLUETOOTH_RX 6
#define BLUETOOTH_TX 7

#define INDICE_RELOJ 1
#define INDICE_SENSOR1 2
#define INDICE_SENSOR2 3
#define INDICE_SENSOR3 4
#define INDICE_LED1 5
#define INDICE_LED2 6
#define INDICE_LED3 7
#define INDICE_STOP 8
#define INDICE_CHICHARRA 9

#define PRENDIDO "1"
#define APAGADO "0"






void Init_BLE();


// Envia el dato que le viene por parametro, con el indice indicado en la segunda variable
void EnviarDato(String,int);

// Enviar 1 para prender el LED, Enviar 0 para apagar el LED, ledLeft, ledRight, ledFront
void EnviarLed(boolean, boolean, boolean);

// Enviar minutos,segundos
void EnviarReloj(int,int);

// Enviar la distancia de cada sensor, sensorLeft, sensorRight, sensorFront
void EnviarSensor(int, int, int);

// Enviar un 1 para avisar que se detuvo
void EnviarStop(void);

// Envia la frequecia con la que va a sonar la chicharra
//seindo 1 la mas freq mas baja y 4 la mas alta
void EnviarChicharra(int);




void ConfigurarBT();


// Hay que conectarlo con un voltaje de 5 V


#endif
