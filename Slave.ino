#include <Wire.h>
#include <Servo.h>

Servo shutter;

#define servoPin 9
#define redLed 4
#define blueLed 3
#define greenLed 2

int lightValue = 0;
signed int tempValue = 0;

void setup() {
  Wire.begin(8); // I2C address of this slave
  Wire.onReceive(receiver);

  shutter.attach(servoPin);

  Serial.begin(9600);

  pinMode(redLed, OUTPUT);
  pinMode(blueLed, OUTPUT);
  pinMode(greenLed, OUTPUT);
}

void loop() {
  // SERVO CONTROL BASED ON LIGHT VALUE
  if (lightValue > 190) {
    shutter.write(0);   // Fully open
  } 
  else if (lightValue > 140 && lightValue <= 190) {
    shutter.write(90);  // Halfway
  } 
  else {
    shutter.write(180); // Fully closed
  }

  // LED CONTROL BASED ON TEMP VALUE
  if (tempValue <= 15) {
    digitalWrite(greenLed, HIGH);
    digitalWrite(redLed, LOW);
    digitalWrite(blueLed, LOW);
  } 
  else if (tempValue >= 40) {
    digitalWrite(blueLed, LOW);
    digitalWrite(redLed, HIGH);
    digitalWrite(greenLed, LOW);
  } 
  else {
    digitalWrite(greenLed, LOW);
    digitalWrite(redLed, LOW);
    digitalWrite(blueLed, HIGH);
  }

  delay(200); // Give the servo some time to reach the position
}

void receiver(int count) {
  if (count >= 2) {
    lightValue = Wire.read();
    tempValue = (int8_t)Wire.read(); // Receive as signed integer

    Serial.print("Light: ");
    Serial.print(lightValue);
    Serial.print("\tTemp: ");
    Serial.println(tempValue);
  }
}
