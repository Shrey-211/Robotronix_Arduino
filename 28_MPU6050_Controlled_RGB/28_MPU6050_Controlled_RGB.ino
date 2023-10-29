#include <Wire.h>
#include <L3G.h>

#include RED 11
#include GREEN 10
#include BLUE 9

L3G gyro;

void setup() {
  Serial.begin(9600);
  Wire.begin();

  if (!gyro.init()) {
    Serial.println("Failed to autodetect gyro type!");
    while (1);
  }

  gyro.enableDefault();
  pinMode(RED,OUTPUT);
  pinMode(GREEN,OUTPUT);
  pinMode(BLUE,OUTPUT);
}

void loop() {

  gyro.read();

  Serial.print("X: ");
  Serial.print(gyro.g.x);
  Serial.print(" Y: ");
  Serial.print(gyro.g.y);
  Serial.print(" Z: ");
  Serial.println(gyro.g.z);

    // Adjust the pitch and roll values to map to RGB colors
  int redValue = map(gyro.g.x, -90, 90, 0, 255);
  int greenValue = map(gyro.g.y, -90, 90, 0, 255);
  int blueValue = map(gyro.g.z, -90, 90, 0, 255);

  analogWrite(redPin, redValue);
  analogWrite(greenPin, greenValue);
  analogWrite(bluePin, blueValue);

  delay(20);
}