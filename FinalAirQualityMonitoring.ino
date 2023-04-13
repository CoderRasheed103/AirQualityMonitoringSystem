#define BLYNK_TEMPLATE_ID "TMPL3eWcSUvWx"
#define BLYNK_TEMPLATE_NAME "Water Level Monitoring"
#define BLYNK_AUTH_TOKEN "BFFT9HT1lYDpXysY9ReWEX1NZeK2ftdu"
#define BLYNK_PRINT Serial
#include <BlynkSimpleEsp8266.h>
#include <ESP8266WiFi.h> 
const int trigpin= 12;  
const int echopin= 14;  
const int led=13;
int soundVelocity=0.034;
int cmToInch=0.393701;

char auth[] = BLYNK_AUTH_TOKEN;

char ssid[] = "Airel_7585824862";  // type your wifi name
char pass[] = "air18053";  // type your wifi password
BlynkTimer timer;

float cmDistance;
int distance;
long duration;
float inchDistance;
int bAlarm=16;

void sendSensor()
{


  digitalWrite(trigpin,HIGH);  
  delayMicroseconds(10);  
  digitalWrite(trigpin,LOW);  
  long duration1=pulseIn(echopin,HIGH);  
  int distance1 = duration*0.034/2;  

  if(isnan(distance)) {
    Serial.println("Failed to read from sensor!");
    return;
  }
  if(distance1>10){
        Blynk.virtualWrite(V0, 10);
  }
  else if(distance<=10 and distance>7){
        Blynk.virtualWrite(V0,60);
  }
  else if(distance<=7){
        Blynk.virtualWrite(V0,95);
        //Blynk.email("aritra.chakraborty203@gmail.com","Alert","Container is  Full");
        Blynk.logEvent("water_level_full","Water Level is Full");
  }
  Serial.println("Data Sent");

 
 
    
 
}     


void setup(){  
   
 
  pinMode(trigpin,OUTPUT);  
  pinMode(echopin,INPUT);  
  Serial.begin(9600);  
  pinMode(led,OUTPUT);
  pinMode(bAlarm,OUTPUT);
  Blynk.begin(auth, ssid, pass);
  timer.setInterval(100L, sendSensor);
}  
  
void loop(){  
   

  Blynk.run();
  timer.run();

  digitalWrite(trigpin,HIGH);  
  delayMicroseconds(10);  
  digitalWrite(trigpin,LOW);  
  duration=pulseIn(echopin,HIGH);  
  distance = duration*0.034/2;  
  Serial.println(distance);  
  delay(1000);
  if(distance<=7){
      tone(bAlarm,500);
      digitalWrite(led,HIGH);
      delay(4000);
      noTone(bAlarm);
      digitalWrite(led,LOW);
 
  }

  
  
}  
