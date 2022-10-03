//Programación del auto

//Librerias
#include <SoftwareSerial.h>

//Definiciones
//Puente H - L298N (Driver Motorreductores)
#define ENA 5
#define IN1 4
#define IN2 6
#define ENB 9
#define IN3 8
#define IN4 7
//Sensor HC-SR04 (Proximidad)
#define TRIGGER 10
#define ECHO 11

//Pines del Módulo Bluetooth HC-05
const byte Rx = 3, Tx = 2;

//Parámetros de velocidades
int full=255, medio=127, parar=0; 

//Objeto Serie - Mòdulo Bluetooth HC-05
SoftwareSerial BT(Rx, Tx);

void setup() {
  //Motorreductor 1
  pinMode(ENA, OUTPUT);
  pinMode(IN1, OUTPUT);
  pinMode(IN2, OUTPUT);
  
  //Motorreductor 2
  pinMode(ENB, OUTPUT);
  pinMode(IN3, OUTPUT);
  pinMode(IN4, OUTPUT);
  
  //Sensor HC-SR04
  pinMode(TRIGGER, OUTPUT);
  pinMode(ECHO, INPUT);
  
  //Módulo Bluetooth HC-05 y Puerto Serial
  BT.begin(9600);
  Serial.begin(9600);
}

void loop() { 
  //Main Loop
  char letra = '0'; 

  //Módulo Bluetooth
  if(BT.available()>0){
    letra = BT.read();
    botones(letra);
  }

  //Aplicación con Python
  if(Serial.available()>0){
    letra = Serial.read();
    botones(letra);
  }
}


void motores_full(){
  //Pone los motores al mámixo - 255 analog
  analogWrite(ENA, full);
  analogWrite(ENB, full);
  delay(3000);
  motores_parar();
}

void motores_media(){
  //Pone los motores a media - 127 analog
  analogWrite(ENA, medio);
  analogWrite(ENB, medio);
  delay(2000);
  motores_parar();
}

void motores_parar(){
  //Frena los motores - 0 analog
  analogWrite(ENA, parar);
  analogWrite(ENB, parar);
  delay(1000);
}

void avanzar(){
  //Pone a los motores sentido horario
  digitalWrite(IN1, 1);
  digitalWrite(IN2, 0);
  digitalWrite(IN3, 1);
  digitalWrite(IN4, 0);
  motores_media();
}

void retroceder(){
  //Pone a los motores sentido antihorario
  digitalWrite(IN1, 0);
  digitalWrite(IN2, 1);
  digitalWrite(IN3, 0);
  digitalWrite(IN4, 1);
  motores_media();
}

void derecha(){
  //Pone motor derecho sentido horario a full
  digitalWrite(IN1, 1);
  digitalWrite(IN2, 0);
  digitalWrite(IN3, 0);
  digitalWrite(IN4, 0);
  motores_full();
}

void izquierda(){
  //Pone motor izquierdo sentido horario a full
  digitalWrite(IN1, 0);
  digitalWrite(IN2, 0);
  digitalWrite(IN3, 1);
  digitalWrite(IN4, 0);
  motores_full();
}

int proximidad(int TriggerPin, int EchoPin){
  //Mide la proximidad con objetos del sensor HC-SR04 en cm
  float tiempo, distancia_cm;
   
  digitalWrite(TriggerPin, HIGH);  
  delayMicroseconds(1);
  digitalWrite(TriggerPin, LOW);
   
  tiempo = pulseIn(EchoPin, HIGH);  
  distancia_cm = tiempo * 58.2;   
  return distancia_cm;
}

void botones(char caracter){
  //Control awsd y sus funciones
  float distancia;
  
  distancia = proximidad(TRIGGER, ECHO);
  
  if(distancia>20){
    //Si la distancia es +20 cm se moverá
      
    switch(caracter){
      //Adelante - w
      case 119:
        avanzar();
        break;

      //Atras - s
      case 115:
        retroceder();
        break;

      //Izquierda - a
      case 97:
        izquierda();
        break;

      //Derecha - d
      case 100:
        derecha();
        break; 

      default:
        BT.println(">Comando inexistente!");
        Serial.println(">Comando inexistente!");
        break;
    }
  }

  else{
    //Distancia -20 cm
    BT.println("La distancia con otro objeto es menor a 20 cm!");
    Serial.println("La distancia con otro objeto es menor a 20 cm!");
  }
}
