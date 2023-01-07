//Include the library files 
//
#define BLYNK_PRINT Serial
#include <WiFi.h>
#include <WiFiClient.h>
#include <SimpleTimer.h>
#include <BlynkSimpleEsp32.h>
#include <dht11.h>
//Declare objects
dht11 DHT11;
//Pin Numbers
#define DHT11PIN 13
#define relayPin 14

// Enter your Auth token
char auth[] = "U8T_cXeGHooLXi3Q8AmsMF39NLQmQ2dU";

//Enter your WIFI SSID and password
char ssid[] = "Nike7BlueMERCADAL";
char pass[] = "pass1111";

int sensor = 0;
int waterPlant = 0;
SimpleTimer timer;

WidgetLCD lcd(V3);

void setup(){
  // Debug console
  Serial.begin(115200);
  Blynk.begin(auth, ssid, pass);
  pinMode(relayPin, OUTPUT);
  timer.setInterval(1000L, sendSensor);
}

void loop(){
  Blynk.run();
  timer.run();
}

void sendSensor()
{
  int chk = DHT11.read(DHT11PIN);
  float h = DHT11.humidity;
  float t = DHT11.temperature;
  sensor = 523;

  Blynk.virtualWrite(V2, h);  //V2 is for Humidity
  Blynk.virtualWrite(V1, t);  //V1 is for Temperature
  Blynk.virtualWrite(V0, sensor);  //V0 is for Soil sensor
  lcd.clear();
  lcd.print(1, 0, "Soil Moisture");
  lcd.print(5, 1, "Sensor");

//  sendTemps();

  if (sensor > 700) {
    Serial.println("Watering the plant");
    digitalWrite(relayPin, HIGH);
    delay(1000);
  }else {
    Serial.println("does not need water");
    digitalWrite(relayPin, LOW);
    delay(1000);
  }

  delay(100);

}


//void sendTemps()
//{
//  int chk = DHT11.read(DHT11PIN);
//  float temp = DHT11.temperature;
//  Serial.println(temp);
//  Serial.println(sensor);
//  Blynk.virtualWrite(V1, temp);
//  Blynk.virtualWrite(V0, sensor);
//  delay(1000);
//}
