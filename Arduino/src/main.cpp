#include <Arduino.h>

const int trigPin = 9;
const int echoPin = 10;
const int ledPin1 = 6;
const int ledPin2 = 5;
const int ledPin3 = 3;

long duration;
float distanceCm;

void setup() {
  Serial.begin(9600);
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
  pinMode(ledPin1, OUTPUT);
  pinMode(ledPin2, OUTPUT);
  pinMode(ledPin3, OUTPUT);
}

void loop() {
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);

  duration = pulseIn(echoPin, HIGH);

  distanceCm = (duration * 0.034) / 2.0;
  
  if (distanceCm < 100) 
  {
    digitalWrite(ledPin1, HIGH);
    if (distanceCm < 50){
      digitalWrite(ledPin2, HIGH);
      if (distanceCm < 10) {
		    digitalWrite(ledPin3, HIGH);
      }
    }
  } else {
    digitalWrite(ledPin1, LOW);
    digitalWrite(ledPin2, LOW);
    digitalWrite(ledPin3, LOW);
  }
  

  delay(250);
}