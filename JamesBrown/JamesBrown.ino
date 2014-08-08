/*
  The circuit:
 * LCD RS pin to digital pin 12
 * LCD Enable pin to digital pin 11
 * LCD D4 pin to digital pin 5
 * LCD D5 pin to digital pin 4
 * LCD D6 pin to digital pin 3
 * LCD D7 pin to digital pin 2
 * LCD R/W pin to ground
 * 10K resistor:
 * ends to +5V and ground
 * GND to LCD VO pin (pin 3)
*/


#include <LiquidCrystal.h>

const int pin_thermistor{A0};
const int pin_humidity{A1};
const int pin_speaker{6};
LiquidCrystal lcd(12, 11, 5, 4, 3, 2);
int prev_temperature{0};
int prev_humidity{0};
double delta_temperature{0.0};
double delta_humidity{0.0};
double max_delta_temperature{0.0};
double max_delta_humidity{0.0};
int cnt = 0;

void setup() 
{
  pinMode(pin_speaker,OUTPUT);
  pinMode(pin_thermistor,INPUT);
  pinMode(pin_humidity,INPUT);
  lcd.begin(20, 4);
  prev_temperature = analogRead(pin_thermistor);
  prev_humidity = analogRead(pin_humidity);
  Serial.begin(9600);
}

void loop() 
{
  const int temperature{analogRead(pin_thermistor)}; 
  const int humidity{analogRead(pin_humidity)}; 
  lcd.setCursor(0, 0);
  lcd.print("T: ");
  lcd.print(temperature);
  lcd.print(",");
  lcd.print(delta_temperature);
  lcd.print(",");
  lcd.print(max_delta_temperature);
  lcd.setCursor(0, 1);
  lcd.print("H: ");
  lcd.print(humidity);
  lcd.print(",");
  lcd.print(delta_humidity);
  lcd.print(",");
  lcd.print(max_delta_humidity);
  lcd.setCursor(0, 3);
  lcd.print("Time: ");
  lcd.print(millis() / 1000);
  delay(1000);
  ++cnt;
  if (cnt % 10 == 0)
  {
    delta_temperature 
      = static_cast<double>(temperature - prev_temperature) / 10.0;
    delta_humidity
      = static_cast<double>(humidity - prev_humidity) / 10.0;
    if (delta_temperature > max_delta_temperature)
    {
      const double increase{delta_temperature-max_delta_temperature}; 
      if (increase > 1.0)
      {
        tone(pin_speaker,440.0 * increase,100);
      }
      max_delta_temperature = delta_temperature;
    } 
    max_delta_humidity = max(delta_humidity,max_delta_humidity);
    prev_temperature = temperature;
    prev_humidity = humidity;
    Serial.print("T:");
    Serial.print(temperature);
    Serial.print(", dT:");
    Serial.print(delta_temperature);
    Serial.print(", max_dT:");
    Serial.print(max_delta_temperature);
    Serial.print(", H:");
    Serial.print(humidity);
    Serial.print(", dH:");
    Serial.print(delta_humidity);
    Serial.print(", max_dH:");
    Serial.print(max_delta_humidity);
    Serial.println();
  }
}

