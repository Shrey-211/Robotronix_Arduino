#include <Wire.h>
#include <LiquidCrystal_I2C.h>

LiquidCrystal_I2C lcd(0x27, 16, 2); // Set the LCD address and dimensions

const int smokePin = A0;  // Analog pin for smoke sensor
const int buzzerPin = 9;  // Digital pin for the buzzer

void setup() {
  lcd.init();                      // Initialize the LCD
  lcd.backlight();                 // Turn on the backlight
  lcd.setCursor(0, 0);
  lcd.print("Smoke Detector");
  delay(2000);                    // Display the title for 2 seconds
  lcd.clear();                    // Clear the display
  lcd.setCursor(0, 0);
  lcd.print("Smoke Level:");

  pinMode(buzzerPin, OUTPUT);
  noTone(buzzerPin);

  Serial.begin(9600);
}

void loop() {
  int smokeLevel = analogRead(smokePin); // Read the analog value from the smoke sensor
  int smokePercentage = (smokeLevel / 1023.0) * 100; // Convert to a percentage

  lcd.setCursor(12, 0);  // Position the cursor
  lcd.print("   ");     // Clear previous reading
  lcd.setCursor(12, 0);  // Position the cursor
  lcd.print(smokePercentage); // Display the smoke percentage

  Serial.print("Smoke Level: ");
  Serial.print(smokeLevel);
  Serial.print(" - Smoke Percentage: ");
  Serial.print(smokePercentage);
  Serial.println("%");

  if (smokePercentage > 50) { // Adjust the threshold as needed
    // Smoke detected, trigger the buzzer
    tone(buzzerPin, 1000); // You can adjust the frequency and duration
  } else {
    noTone(buzzerPin); // Turn off the buzzer
  }

  delay(1000); // Delay for a second before the next reading
}
