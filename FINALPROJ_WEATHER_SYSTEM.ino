#include "DHT.h" 
#define DHTPIN 7 
#define DHTTYPE DHT11 
DHT dht(DHTPIN, DHTTYPE);

#include <LiquidCrystal_I2C.h>
LiquidCrystal_I2C lcd(0x27,16,2);

const int lightsensor = A0; 
int lightsensorValue = 0; 

const int motorpin1 = 2;
const int motorpin2 = 3;

void setup() {
  Serial.begin(9600);
  dht.begin();
  lcd.init();
  lcd.clear();         
  lcd.backlight();
  pinMode(motorpin1, OUTPUT);
  pinMode(motorpin2, OUTPUT);
}

void loop() {
  delay(1000); // delay before measurement

  int h = dht.readHumidity();
  float t = dht.readTemperature(); //default: Celsius

  if (isnan(h) || isnan(t)) {
    Serial.println(F("Failed to read from DHT sensor!"));
    return;
  }

  Serial.print(F("Humid: ")); //humidity
  Serial.print(h);

  Serial.print(F(" Temp: ")); //temp
  Serial.print(t);

  lightsensorValue = analogRead(lightsensor); //light
  Serial.print(" Light: ");
  Serial.println(lightsensorValue); 

 if (t>=28 && lightsensorValue >= 500){
    Serial.print("ON ");
    digitalWrite(motorpin1, HIGH);
    digitalWrite(motorpin2, LOW);
  }
  else if (t<28 && lightsensorValue < 500){
    Serial.print("OFF ");
    digitalWrite(motorpin1, LOW);
    digitalWrite(motorpin2, LOW);
  }
  else if (t>=28 && lightsensorValue < 500){
    Serial.print("OFF ");
    digitalWrite(motorpin1, LOW);
    digitalWrite(motorpin2, LOW);
  }
   else if (t<28 && lightsensorValue >= 500){
    Serial.print("OFF ");
    digitalWrite(motorpin1, LOW);
    digitalWrite(motorpin2, LOW);
  }

  lcd.setCursor(0,0);   
  lcd.print("H:");  
  lcd.print(h);
  lcd.print("%");  

  lcd.setCursor(7,0);
  lcd.print("T:");   
  lcd.print(t);
    lcd.print("C");  

  lcd.setCursor(0,1);   
  lcd.print("L:");
  lcd.print(lightsensorValue);
}
