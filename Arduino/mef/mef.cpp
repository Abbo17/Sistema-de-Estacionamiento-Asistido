#include "mef.h"
#include "sensorUltrasonido.h"
#include "bluetooth.h"
#include <TimerOne.h>

/* Declaracion de variables */


StructHora hora;

long presionado = 0;

int parlante=0; //Indica la intensidad del sonido del parlante 0,1,2,3

boolean led[3]; //Indica si los led estan prendido
boolean ledEstado[3]; //Indica si el led esta apagado o prendido
int parpadear[3];  //Indica cada cuanto debe parpadear los Leds

boolean flagSensor= false; //Indica si hay que realizar un sesando
boolean flagReloj=false; //Indica si hay que actualizar la hora
boolean flagLed[3]; //Indica si hay que alternar el led

boolean estadoSistema; //Indica si el sistema esta apagado o encendido

extern int distancia[3];  //Variable externa que indica las ultimas lecturas de la distancia


int ticksReloj=0; //ticks del reloj
int ticksSensor=0; //tick del sensor
int ticksLed[3]={0};

/* Declaracion de funciones */

/* Funcion que inicializa los led como salida y apagados */
void Init_Led(void){

  pinMode(LED_CTRL,OUTPUT);
  pinMode(LED1,OUTPUT); // Led 1,2,3 como salida
  pinMode(LED2,OUTPUT);
  pinMode(LED3,OUTPUT);

  digitalWrite(LED_CTRL,LOW);
  digitalWrite(LED1,LOW); // Led 1,2,3 apagados
  digitalWrite(LED2,LOW);
  digitalWrite(LED3,LOW);

 for(int i=0; i<3; i++){
  led[i]=false;  //Indico los led que van a estar apagado
  ledEstado[i]=false;
  parpadear[i]=-1;
  flagLed[i]=false;
 }
}

/* Funcion de inicializacion del Pulsador */
void Init_Pulsador(void){
  pinMode(PULSADOR, INPUT_PULLUP);  //Activamos la resistencia interna de Pull UP en el Pin 2
  attachInterrupt(digitalPinToInterrupt(PULSADOR), Init_Timers, FALLING);  //definimos una interrupción al evento de bajada en el PIN, y en la función ISR asociada simplemente iniciamos el timer.
}



/* Funcion de inicializacion de los Timers */
void Init_Timers(void){
if (digitalRead(PULSADOR) == LOW)     //Pregunta si el pulsador está presionado
      {
        presionado = 1;     //La variable cambia de valor
      }
      if (digitalRead(PULSADOR) == HIGH && presionado == 1)
      {
        //Realiza la acción deseada
        presionado = 0;    //La variable vuelve a su valor original
     
      if (!estadoSistema){
          estadoSistema=true;
          digitalWrite(LED_CTRL,HIGH);
          Timer1.initialize(100000); //Inicializamos el Timer1 cada 100 ms
          Timer1.attachInterrupt(interruptHandler); // Asignamos la funcion para enviar los datos
          flagSensor=true;
      }else{
          EnviarStop();
          Init();
          estadoSistema=false;
          digitalWrite(LED_CTRL,LOW);
      }
    }
}

void Init(void){
  Init_Led(); //Inicializo los led

  Init_BLE(); //Inicializo el bluetooth

  for (int i=0;i<3;i++){
    distancia[i]=0;
  }
  hora.minutos=0;
  hora.segundos=0;
  EnviarReloj(hora.minutos,hora.segundos);
  Init_Pulsador(); 
}
 /* Manejador de interrupciones del timer 1 */
void interruptHandler (void){
  ticksReloj++;
  ticksSensor++;
  ticksLed[0]++;
  ticksLed[1]++;
  ticksLed[2]++;

  if (ticksReloj == INTERRUPCION_RELOJ){
    flagReloj = true;
    ticksReloj=0;
  }
  if (ticksSensor == INTERRUPCION_SENSOR){
    flagSensor=true;
    ticksSensor=0;
  }
  if (ticksLed[0] == parpadear[0]){
    flagLed[0]=true;
    ticksLed[0]=0;
  }
   if (ticksLed[1] == parpadear[1]){
    flagLed[1]=true;
    ticksLed[1]=0;
  }
   if (ticksLed[2] == parpadear[2]){
    flagLed[2]=true;
    ticksLed[2]=0;
  }

}

/* Funcion que espera el inicio del sensado y comienza */
void sensando(void){

    if (estadoSistema){
        if (flagReloj){
          ActualizarHora();
          EnviarReloj(hora.minutos,hora.segundos);
          flagReloj=false;
        }

        if (flagSensor){
          comenzarSensado();
          EnviarSensor(distancia[0],distancia[1],distancia[2]);
          
          ActualizarLed();
          EnviarLed(led[0],led[1],led[2]);
          flagSensor=false;
        }
        for(int i=0;i<3;i++){
          if (flagLed[i] && led[i]){
            AlternarLed(i);
            flagLed[i] = false;
          }
        }

    }
}

/* Funcion que cambia el estado del Led i */

void AlternarLed(int led){
  if (!ledEstado[led]){
    prenderLed(led);
    ledEstado[led]=true;
  } else {
    apagarLed(led);
    ledEstado[led]=false;
  }
}

/* Funcion que actualiza los LED en base a las distancias calculadas */

void ActualizarLed(void){
  int chicharra = 5;
  for(int i=0;i<3;i++){
    if (distancia[i] != 0){
      led[i]=true; 

      if (distancia[i] < LIMITE_UNO) {
      
        if (distancia[i] < LIMITE_DOS) { 

          if (distancia[i] < LIMITE_TRES) {            
             parpadear[i]=PARPADEO_CUATRO;
             if ( chicharra > 1 ) chicharra = 1;

          } else {        
            parpadear[i]=PARPADEO_TRES;
            if ( chicharra > 2 ) chicharra = 2;
          }

        } else {
          parpadear[i]=PARPADEO_DOS;
         if ( chicharra > 3 ) chicharra = 3;
        }

      } else {
        parpadear[i]=PARPADEO_UNO;
       if ( chicharra > 4 ) chicharra = 4;
      }

    } else {
      led[i]=false;
      apagarLed(i);
      parpadear[i]=-1;
      if ( chicharra > 5 ) chicharra = 5;
    }
    ticksLed[i]=0;
  }
  //EnviarChicharra(chicharra);
}

/* Funcion que actualiza la hora y envia los datos */
void ActualizarHora(void){

  hora.segundos=hora.segundos+1;
  if (hora.segundos == 60){
    hora.minutos=hora.minutos+1;
    hora.segundos=0;
  }
}

void apagarLed(int i){
  switch (i){
    case 0: digitalWrite(LED1,LOW); break;
    case 1: digitalWrite(LED2,LOW); break;
    case 2: digitalWrite(LED3,LOW); break;
  }
}

void prenderLed(int i){
    switch (i){
    case 0: digitalWrite(LED1,HIGH); break;
    case 1: digitalWrite(LED2,HIGH); break;
    case 2: digitalWrite(LED3,HIGH); break;
  }
}

