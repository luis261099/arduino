
#include "DHT.h"
#include <Adafruit_Sensor.h>

#include <SoftwareSerial.h>


#define DHTPIN 2
  

#define DHTTYPE DHT11   

DHT dht(DHTPIN, DHTTYPE);


float t; 
float f; 
float h; 


SoftwareSerial SIM900(7, 8);


char incomingChar;

void setup() {
  dht.begin();
  
  Serial.begin(19200); 
  SIM900.begin(19200);

  
  delay(20000);
  Serial.print("SIM900 ready...");

  
  SIM900.print("AT+CMGF=1\r"); 
  delay(100);
  
  SIM900.print("AT+CNMI=2,2,0,0,0\r");
  delay(100);
}

void loop(){
  if (SMSRequest()){
    if(readData()){
      delay(10);
     // mandar sms 
      SIM900.println("AT + CMGS = \"+5541988970244\"");
      delay(100);
     
      String dataMessage = ("Temperatura: " + String(t) + "*C " + " Humidade: " + String(h) + "%");
       
      
     
      SIM900.print(dataMessage);
      delay(100);
      
      SIM900.println((char)26); 
      delay(100);
      SIM900.println();
     
      delay(5000);  
    }
  }
  delay(10); 
}

boolean readData() {
  //humidity
  h = dht.readHumidity();
  //  Celsius
  t = dht.readTemperature();
  // Fahrenheit
  f = dht.readTemperature(true);

  //  Celcius
  t = dht.computeHeatIndex(t,h,false);

  
  
 
  if (isnan(h) || isnan(t) || isnan(f)) {
    Serial.println("Failed to read from DHT sensor!");
    return false;
  }
  Serial.print("Humidity: "); 
  Serial.print(h);
  Serial.print(" %\t");
  Serial.print("Temperature: "); 
  Serial.print(t);
  Serial.print(" *C ");

  return true;
}

boolean SMSRequest() {
  if(SIM900.available() >0) {
    incomingChar=SIM900.read();
    if(incomingChar=='S') {
      delay(10);
      Serial.print(incomingChar);
      incomingChar=SIM900.read();
      if(incomingChar =='T') {
        delay(10);
        Serial.print(incomingChar);
        incomingChar=SIM900.read();
        if(incomingChar=='A') {
          delay(10);
          Serial.print(incomingChar);
          incomingChar=SIM900.read();
          if(incomingChar=='T') {
            delay(10);
            Serial.print(incomingChar);
            incomingChar=SIM900.read();
            if(incomingChar=='E') {
              delay(10);
              Serial.print(incomingChar);
              Serial.print("...Request Received \n");
              return true;
            }
          }
        }
      }
    }
  }
  return false;
}
