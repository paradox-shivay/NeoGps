#include <TinyGPS++.h>
#include <SoftwareSerial.h>

double lati, longi;
String x, y;
TinyGPSPlus gps;

SoftwareSerial ss(52,50);
SoftwareSerial sim(51,53);


void setup() {
  Serial.begin(9600);
  sim.begin(9600);
  ss.begin(9600);
  Serial.println("Starting...Device on");
  get_latlon();
}

void get_latlon() {
  ss.begin(9600);

   while (ss.available() > 0){
    gps.encode(ss.read());
    
    if (gps.location.isUpdated()){
     x = gps.location.lat() ;
     y = gps.location.lng()  ;
      x=String(lati);
      y=String(longi);
    }
  }

}
void data_dump()  {
  
  
  Serial.begin(9600);
  ss.begin(9600);
  sim.begin(9600);
  
  Serial.println("Starting...");

  sim.println("ATH");
  delay(100);
  while(sim.available())
  {
     Serial.write(sim.read());
  }

 sim.println("AT+CSQ");
 delay(100);
 while(sim.available())
 {
    Serial.write(sim.read());
 }

 sim.println("AT+CGATT?");
 delay(100);
 while(sim.available())
 {
    Serial.write(sim.read());
 }

 sim.println("AT+SAPBR=3,1,\"CONTYPE\",\"GPRS\"");
 delay(100);
 while(sim.available())
 {
    Serial.write(sim.read());
 }

 sim.println("AT+SAPBR=3,1,\"APN\",\"airtelgprs.com\"");
 delay(100);
 while(sim.available())
 {
    Serial.write(sim.read());
 }

 sim.println("AT+SAPBR=1,1");
 delay(2000);
 while(sim.available())
 {
    Serial.write(sim.read());
 }

 sim.println("AT+HTTPINIT");
 delay(2000);
 while(sim.available())
 {
    Serial.write(sim.read());
 }

 sim.println("AT+HTTPPARA=\"URL\",\"http://crash.microinstance.com/api/accident-log?device_number=00&latitude="+x+"&longitude="+y+"\"\n");
 delay(3000);
 while(sim.available())
 {
    Serial.write(sim.read());
 }

 sim.println("AT+HTTPACTION=0");
 delay(5000);
 while(sim.available())
 {
    Serial.write(sim.read());
 }

 delay(9000);

}


void loop() {
  
 data_dump() ;
  
}
