#define BLYNK_TEMPLATE_ID "TMPL3T46U3FRD"
#define BLYNK_TEMPLATE_NAME "Air Monitoring System"
#define BLYNK_AUTH_TOKEN "HNPdu1J60wOHg3QqHAlaP_08-NxtBGEf"
#include <ESP8266WiFi.h> 
#include "MQ135.h"
#include <Wire.h>
#include <LiquidCrystal_I2C.h>
#include <BlynkSimpleEsp8266.h>
#include <DHT.h>
#define BLYNK_PRINT Serial
int mq135 = A0;
MQ135 gasSensor=MQ135(A0);
DHT dht2(2,DHT11);  
char auth[] = BLYNK_AUTH_TOKEN;

char ssid[] = "Airel_7585824862";  // type your wifi name
char pass[] = "air18053";  // type your wifi password

double ppmImpurties=0;

BlynkTimer timer;
double data=0;
int bAlarm = 14;




LiquidCrystal_I2C lcd(0x27, 16, 2);




void sendSensor()
{


  data=analogRead(mq135);
  float t = dht2.readTemperature(); 
  float h = dht2.readHumidity();
  float ppmImpurities=gasSensor.getPPM();
 

  if(isnan(t)|| isnan(h) || isnan(ppmImpurities) || isnan(data)) {
    Serial.println("Failed to read from DHT sensor!");
    return;
  }
  if(data>=500){
    Blynk.logEvent("harmful_gas","harmful gas detected"); // To setup the notification event.
  }
  Blynk.virtualWrite(V0, t);
 
  // You can send any value at any time.
  // Please don't send more that 10 values per second.
  Blynk.virtualWrite(V1, h);
  Blynk.virtualWrite(V2, data);
  Blynk.virtualWrite(V3,ppmImpurities);
   
  Serial.println("Temperature : ");
  Serial.println(t);
  Serial.println("    Humidity : ");
  Serial.println(h);
  Serial.println("Aqi: ");
  Serial.println(data);
  Serial.println("ppmImpurities: ");
  Serial.println(ppmImpurities);
    
 
}     

void setup(){

      Serial.begin(9600);
      
      pinMode(bAlarm, OUTPUT); 
      Blynk.begin(auth, ssid, pass);
      dht2.begin();
      timer.setInterval(100L, sendSensor);
         
      lcd.begin();
      lcd.setBacklight(HIGH);
      lcd.setCursor(0,0);
      lcd.print("Welcome to ");
      lcd.setCursor(0,1);
      lcd.print("Air Monitoring");
      delay(1000);
}


void loop(){
  // Nothing Absolutely Nothing!


     float air_quality= analogRead(mq135);
     float ppmImpurities= gasSensor.getPPM();
     float t = dht2.readTemperature(); 
     float h = dht2.readHumidity();
     
    if(air_quality>=500){

     lcd.clear();
     lcd.setCursor(0,0);
     lcd.print("AQI is:- ");
     lcd.setCursor(0,1);
     lcd.print(air_quality);

     tone(bAlarm,700);
     delay(2000);
     tone(bAlarm,0);
     delay(300);
  
      lcd.clear();
      lcd.setCursor(0,0);
      lcd.print("impurity(ppm):- ");
      lcd.setCursor(0,1);
      lcd.print(ppmImpurities);
      delay(2000);


     lcd.clear();
     lcd.setCursor(0,0);
     lcd.print("Temperature is:- ");
     lcd.setCursor(0,1);
     lcd.print(t);
     delay(2000);


        lcd.clear();
     lcd.setCursor(0,0);
     lcd.print("Humidity is:- ");
     lcd.setCursor(0,1);
     lcd.print(h);
     delay(2000);

  }
  else{
     lcd.clear();
     lcd.setCursor(0,0);
     lcd.print("AQI is:- ");
     lcd.setCursor(0,1);
     lcd.print(air_quality);
     delay(3500);

      lcd.clear();
      lcd.setCursor(0,0);
      lcd.print("impurity(ppm):- ");
      lcd.setCursor(0,1);
      lcd.print(ppmImpurities);
      delay(2000);

      lcd.clear();
     lcd.setCursor(0,0);
     lcd.print("Temperature is:- ");
     lcd.setCursor(0,1);
     lcd.print(t);
      delay(2000);

     lcd.clear();
     lcd.setCursor(0,0);
     lcd.print("Humidity is:- ");
     lcd.setCursor(0,1);
     lcd.print(h);
      delay(2000);

    
  }

    
     Blynk.run();
     timer.run();


}