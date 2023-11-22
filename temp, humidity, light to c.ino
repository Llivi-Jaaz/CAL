#include "DHT.h" 
#define DHTPIN 2 
#define DHTTYPE DHT11 
DHT dht(DHTPIN, DHTTYPE);

#include <LiquidCrystal_I2C.h>
LiquidCrystal_I2C lcd(0x27,16,2);

const int lightsensor = A0; 
int lightsensorValue = 0; 

const int motorpin = 3;

void setup() {
  Serial.begin(9600);
  dht.begin();
  lcd.init();
  lcd.clear();         
  lcd.backlight();
}

void loop() {
  delay(1000); // delay before measurement

  float h = dht.readHumidity();
  float t = dht.readTemperature(); //default: Celsius

  if (isnan(h) || isnan(t)) {
    Serial.println(F("Failed to read from DHT sensor!"));
    return;
  }


  Serial.print(h);
  Serial.print(" ");
  Serial.print(t);
  Serial.print(" ");

  lightsensorValue = analogRead(lightsensor); //light
  Serial.println(lightsensorValue); 
  delay(1000); 
