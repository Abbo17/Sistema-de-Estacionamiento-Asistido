## Sistema de estacionamiento asistido 

Es un proyecto final de la materia Sistema de Tiempo Real de la carrera Ingeniería en Computación de la UNLP. 

### **Grupo de Desarrollo:**
- Abba, Pedro Nicolás
- Ares, Charo
- Galán, Martín Andrés

### **Fecha**
8/12/18

### **1.- Introducción**

  El proyecto que se nos ha asignado como trabajo final de la materia ha sido la implementación de un sistema de estacionamiento asistido. El principal objetivo es modelar este sistema tan difundido en la industria automotríz utilizando componentes electrónicos  básicos proporcionados por la cátedra y programar un microcontrolador  para que dicho sistema reaccione a las variables reales que se toman del medio, en un tiempo acotado y acorde.

### **2.- Objetivo**

  - Poder encender el sistema a través de un botón y que inmediatamente se inicie un timer para contar el tiempo que se tarda en estacionar
  - Poder apagar el sistema a través del mismo botón y que inmediatamente se detenga el timer
  - Sensar cada cierto tiempo uno a uno la distancia de los sensores de ultrasonido a su objeto más cercano
  - Encender leds para indicar que existe una distancia corta entre uno o más de los sensores ultrasónicos y sus objetos más cercanos
  - Enviar datos a través de un dispositivo Bluetooth a una aplicación Android creada por nosotros
  - Informar las distancias de cada sensor en la App
  - Llevar un registro histórico de los estacionamientos recientes

### **3.- Propuesta**
  Nuestra propuesta fue diseñar un sistema cuyo funcionamiento se centra en un microcontrolador conectado a sensores ultrasónicos que recogen datos sobre distancias y se informan a través de leds, y adicionalmente, una aplicación Android conectada mediante bluetooth. Como especifica la consigna, utilizamos un botón para prendido y apagado. Cuando el sistema se enciende, se inicia un timer y se muestra dicho tiempo en la app.

### **4.- Componentes**

  - Arduino UNO R3
  - 3 sensores ultrasónicos HC-SR04
  - Módulo bluetooth HC-05 ZC-040 
  - 3 LED rojos
  - Pulsador
  
  ### Para mas información leer el Informe del Proyecto
