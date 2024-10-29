#include <Servo.h>

#define TRIGGER_PIN A3  
#define ECHO_PIN A2     
#define MAX_DISTANCE 200  
#define STOP_DIST 35  

Servo myservo;  

int ledRojo = 9;
int ledVerde = 11;
int motorA1 = 3, motorA2 = 5;
int motorB1 = 2, motorB2 = 4;
int servoPin = 6;

void setup() {
  pinMode(ledRojo, OUTPUT);
  pinMode(ledVerde, OUTPUT);
  pinMode(motorA1, OUTPUT);
  pinMode(motorA2, OUTPUT);
  pinMode(motorB1, OUTPUT);
  pinMode(motorB2, OUTPUT);

  pinMode(TRIGGER_PIN, OUTPUT);
  pinMode(ECHO_PIN, INPUT);

  myservo.attach(servoPin);
  myservo.write(90);  // Posición inicial del servo

  Serial.begin(9600);
}

void loop() {
  int distancia = medirDistancia();  // Llama a la función para medir distancia
  Serial.print("Distancia: ");
  Serial.println(distancia);

  if (distancia == 0 || distancia >= STOP_DIST) {
    moverAdelante();
    digitalWrite(ledVerde, HIGH);
    digitalWrite(ledRojo, LOW);
  } else {
    detener();
    digitalWrite(ledRojo, HIGH);
    digitalWrite(ledVerde, LOW);
    girarServo();
  }
  
  delay(100);
}

int medirDistancia() {
  // Envía un pulso de 10 microsegundos para iniciar la medición
  digitalWrite(TRIGGER_PIN, LOW);
  delayMicroseconds(2);
  digitalWrite(TRIGGER_PIN, HIGH);
  delayMicroseconds(10);
  digitalWrite(TRIGGER_PIN, LOW);

  // Lee el tiempo que tarda en recibir el eco
  long duracion = pulseIn(ECHO_PIN, HIGH);

  // Calcula la distancia en cm (velocidad del sonido: 343 m/s)
  int distancia = duracion * 0.034 / 2;

  if (distancia > MAX_DISTANCE) return 0;  // Si está fuera del rango
  return distancia;
}

void moverAdelante() {
  digitalWrite(motorA1, HIGH);
  digitalWrite(motorA2, LOW);
  digitalWrite(motorB1, HIGH);
  digitalWrite(motorB2, LOW);
}

void detener() {
  digitalWrite(motorA1, LOW);
  digitalWrite(motorA2, LOW);
  digitalWrite(motorB1, LOW);
  digitalWrite(motorB2, LOW);
}

void girarServo() {
  myservo.write(0);   // Gira a la izquierda
  delay(500);
  myservo.write(180);  // Gira a la derecha
  delay(500);
  myservo.write(90);   // Regresa al centro
}
