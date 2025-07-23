#include <Wire.h>

#define LIGHT A0
#define TEMP A1

float lightValue = 0;
float tempValue = 0;

void setup() {
  Wire.begin();
  Serial.begin(9600);
}

void loop() {
  lightValue = analogRead(LIGHT);
  int sensorRead = analogRead(TEMP);
  tempValue = (sensorRead * 5.0)/ 1023.0;
  tempValue = (tempValue - 0.5) * 100; 

  Serial.println(tempValue);
  Serial.println((int)lightValue);

  Wire.beginTransmission(8); 
  Wire.write((uint8_t)lightValue); // assuming light is 0–255
  Wire.write((int8_t)tempValue);   // tempValue must be between -128 and 127
  Wire.endTransmission();

  delay(500);
}
