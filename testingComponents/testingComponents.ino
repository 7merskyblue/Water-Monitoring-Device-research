#include <dht11.h>

dht11 DHT11;
int sensor = 4;
int DHT11PIN = 13;
#define relayPin 14

int sensorVal;
float h;
float t;
String pumpString = "ON";

void setup() {
  Serial.begin(9600);
  pinMode(sensor, INPUT);
  pinMode(relayPin, OUTPUT);
  digitalWrite(relayPin, HIGH);
}

void loop() {
  sensorVal = analogRead(sensor);
  Serial.println(sensorVal);
  int chk = DHT11.read(DHT11PIN);
  sensorVal = analogRead(sensor);
  h = DHT11.humidity;
  t = DHT11.temperature;

  if(sensorVal < 3000) {
    //Serial.println("Watering the plant");
    digitalWrite(relayPin, LOW);
    pumpString = "ON";
    delay(5000);
  }else {
    //Serial.println("does not need water");
    digitalWrite(relayPin, HIGH);
    pumpString = "OFF";
  }
  Serial.print("Temperature: ");
  Serial.println(t);
  Serial.print("Humidity: ");
  Serial.println(h);
  Serial.println("Pump is "+ pumpString);
  delay(1000);
}
