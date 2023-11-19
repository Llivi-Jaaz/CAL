#include "DHT.h" 
#define DHTPIN 7 
#define DHTTYPE DHT11 
DHT dht(DHTPIN, DHTTYPE);

#include <LiquidCrystal_I2C.h>
LiquidCrystal_I2C lcd(0x27,16,2);

const int lightsensor = A0; 
int lightsensorValue = 0; 

const int motorpin = 2;

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

  Serial.print(F("Humid.: ")); //humidity
  Serial.print(h);

  Serial.print(F(" Temp: ")); //temp
  Serial.print(t);

  lightsensorValue = analogRead(lightsensor); //light
  Serial.print(" Light: ");
  Serial.println(lightsensorValue); 
  delay(1000); 

 if (t>=30 && lightsensorValue >= 500){
    Serial.println("MOTOR IS ON");
    digitalWrite(motorpin, HIGH);
  }
  else if (t<30 && lightsensorValue < 500){
    Serial.println("MOTOR IS OFF");
    digitalWrite(motorpin, LOW);
  }
  else if (t>=30 && lightsensorValue < 500){
    Serial.println("MOTOR IS OFF");
    digitalWrite(motorpin, LOW);
  }
   else if (t<30 && lightsensorValue >= 500){
    Serial.println("MOTOR IS OFF");
    digitalWrite(motorpin, LOW);
  }
  //using 20x4 lcd display
  // lcd.setCursor(0,0);   
  // lcd.print("Hum %    ");  
  // lcd.print(h);

  // lcd.setCursor(1,0);
  // lcd.print("Temp F    ");   
  // lcd.print(t);

  // lcd.setCursor(2,0);   
  // lcd.print("Bright    ");
  // lcd.print(lightsensorValue);
}

