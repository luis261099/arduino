#include <SoftwareSerial.h>
SoftwareSerial gprsSerial(7, 8);

void setup()
{
  gprsSerial.begin(19200);
  Serial.begin(19200);

  Serial.println("Config SIM900...");
  delay(2000);
  Serial.println("Done!...");
  gprsSerial.flush();
  Serial.flush();

  
  gprsSerial.println("AT+CGATT?");
  delay(100);
  toSerial();



  gprsSerial.println("AT+SAPBR=3,1,\"CONTYPE\",\"GPRS\"");
  delay(2000);
  toSerial();

  
  gprsSerial.println("AT+SAPBR=3,1,\"APN\",\"taif\"");
  delay(2000);
  toSerial();

  
  gprsSerial.println("AT+SAPBR=1,1");
  delay(2000);
  toSerial();
}


void loop()
{
   
   gprsSerial.println("AT+HTTPINIT");
   delay(2000); 
   toSerial();

   
   gprsSerial.println("AT+HTTPPARA=\"URL\",\"http://albusaidi.16mb.com/write_data.php?data1=2.88&data2=2.93\""); 
   delay(2000);
   toSerial();

   
   gprsSerial.println("AT+HTTPACTION=0");
   delay(6000);
   toSerial();

   
   gprsSerial.println("AT+HTTPREAD"); 
   delay(1000);
   toSerial();

   gprsSerial.println("");
   gprsSerial.println("AT+HTTPTERM");
   toSerial();
   delay(300);

   gprsSerial.println("");
   delay(10000);
}

void toSerial()
{
  while(gprsSerial.available()!=0)
  {
    Serial.write(gprsSerial.read());
  }
}
