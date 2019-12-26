#include "bluetooth.h"
#include <SoftwareSerial.h>
#include "Arduino.h"


char nombreBT[10] = "BTCAM";
char velocidad [] ="9600,0,0";
char pin [5]= "1996";
char modo = '0';
char terminacion[5] = "\r\n";
SoftwareSerial BTserial(BLUETOOTH_RX, BLUETOOTH_TX);

boolean eaLED1 = 0;
boolean eaLED2 = 0;
boolean eaLED3 = 0;
int eaSensor1 = 0;
int eaSensor2 = 0;
int eaSensor3 = 0;
int eaFreq = 5;


void Init_BLE(){
  BTserial.begin(9600);
  EnviarDato(String(0),  INDICE_SENSOR1);
  EnviarDato(String(0),  INDICE_SENSOR2);
  EnviarDato(String(0),  INDICE_SENSOR3);

}

void ConfigurarBT(){
  pinMode(BTPWR, OUTPUT);

  BTserial.begin(38400);
  Serial.begin(9600);

  //Presionar pulsador
  delay(4000);
  //Le doy energia al BT
  digitalWrite(BTPWR, HIGH);
  delay(2000);

  //Configuro el Bt con comando AT
  Serial.print("Comienzo Comunicacion\n");
  BTserial.print("AT");
  BTserial.print(terminacion);
  delay(1000);

  Serial.print("Configuro nombre\n");
  BTserial.print("AT+NAME=");
  BTserial.print(nombreBT);
  BTserial.print(terminacion);
  delay(1000);

  Serial.print("Configuro Baud Rate\n");
  BTserial.print("AT+UART=");
  BTserial.print(velocidad);
  BTserial.print(terminacion);
  delay(1000);

 Serial.print("Configuro Contraseña\n");
  BTserial.print("AT+PSWD=");
  BTserial.print(pin);
  BTserial.print(terminacion);
  delay(1000);

 Serial.print("Configuro Rol\n");
  BTserial.print("AT+ROLE=");
  BTserial.print(modo);
  BTserial.print(terminacion);
  delay(1000);

  BTserial.begin(9600);
}

void EnviarDato(String datos, int index){

  //Inicializo un String vacio
  String mainString = "";
  //Coloco el indice correspondiente
  mainString.concat(String(index));
  //Coloco los datos
  mainString.concat(datos);
  //Coloco el final de linea
  mainString.concat(String("#"));
  
  //Escribo el dato en el Bluetooth
  BTserial.print(mainString);
  
}

// Enviar 1 para prender el LED, Enviar 0 para apagar el LED, ledLeft, ledRight, ledFront
void EnviarLed(boolean led1, boolean led2, boolean led3){

if(led1 != eaLED1){
  if (led1 ){
    EnviarDato(PRENDIDO, INDICE_LED1);
  } else {
    EnviarDato(APAGADO, INDICE_LED1);
  }
}
if(led2 != eaLED2){
  if (led2){
    EnviarDato(PRENDIDO, INDICE_LED2);
  } else {
    EnviarDato(APAGADO, INDICE_LED2);
  }
}
if(led3 != eaLED3){
  if (led3){
    EnviarDato(PRENDIDO, INDICE_LED3);
  } else {
    EnviarDato(APAGADO, INDICE_LED3);
  }
}
  eaLED1 = led1;
  eaLED2 = led2;
  eaLED3 = led3;

}

// Enviar 4 digitos
void EnviarReloj(int minuto,int segundo){

  String hora = "";
  String minute = "";
  String second = "";

  if (minuto < 10){
     minute = String(0);
     minute.concat(String(minuto));
  } else {
     minute=String(minuto);
  }

  if (segundo < 10){
     second = String(0);
     second.concat(String(segundo));
  } else{
     second=String(segundo);
  }
  hora.concat(minute);
  hora.concat(second);

  EnviarDato(hora, INDICE_RELOJ);

}

// Enviar la distancia de cada sensor, sensorLeft, sensorRight, sensorFront
void EnviarSensor(int sensor1, int sensor2, int sensor3){
  
  if(sensor1 != eaSensor1) {
    EnviarDato(String(sensor1),  INDICE_SENSOR1);
  }

  if (sensor3 != eaSensor2){
    EnviarDato(String(sensor2), INDICE_SENSOR2);
  }

  if (sensor2 != eaSensor3){
    EnviarDato(String(sensor3), INDICE_SENSOR3);  
  }

  eaSensor1 = sensor1;
  eaSensor2 = sensor2;
  eaSensor3 = sensor3;
  
  
}

// Enviar un 1 para avisar que se detuvo
void EnviarStop(){
  EnviarDato(String("1"), INDICE_STOP);
}


// Envia la frequecia con la que va a sonar la chicharra
//seindo 1 la mas freq mas baja y 4 la mas alta
void EnviarChicharra(int freq){
  if (freq != eaFreq)
      EnviarDato(String(freq), INDICE_CHICHARRA);
  eaFreq = freq;
}







