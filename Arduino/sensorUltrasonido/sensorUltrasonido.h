#ifndef sensorUltrasonido_h
#define sensorUltrasonido_h

// Sensor de la izquierda
#define TRIGGER_PIN_SENSOR1 8
#define ECHO_PING_SENSOR1 9

// Sensor de la derecha
#define TRIGGER_PIN_SENSOR2 8
#define ECHO_PING_SENSOR2 9

// Sensor del centro
#define TRIGGER_PIN_SENSOR3 10
#define ECHO_PING_SENSOR3 11

#define SONAR_NUM     3
#define MAX_DISTANCE 40

void comenzarSensado(void); //Funcion que realiza un sensado de todos los sensores ultrasonico


#endif
