#include <WiFi.h>
#include <WiFiClient.h>
#include <WebServer.h>
#include <dht11.h>

#include "index.h"  //Web page header file

WebServer server(80); //default port for the local IP

//Declare objects
dht11 DHT11;
int sensor = 0;
int DHT11PIN = 13;
#define relayPin 14

//Enter your SSID and PASSWORD
const char* ssid     = "IDreamMusic";
const char* password = "musiclover";

int sensorVal; // soil moisture sensor value
String soilAnalog; // app returns string value
float h; //holds the humidity value
float t; //holds the temperature value
int waterPlant = 0; //this declaration doesn't need
String pumpString = "ON"; //send to app if the pump was on or off

void setup(void){
  Serial.begin(115200); //baud rate for the serial monitor
  pinMode(sensor, INPUT); //soil sensor mode for input mode
  pinMode(relayPin, OUTPUT); //relay for output mode
  digitalWrite(relayPin, HIGH); //relay to off = LOW for ON the pump
  Serial.println("Booting Sketch..."); 
//ESP32 connects to your wifi -----------------------------------
  WiFi.mode(WIFI_STA); //Connect your wifi = WFIF_STA means set the esp32 to connect wifi
  WiFi.begin(ssid, password); // your wifi credentials was begin

  Serial.println("Connecting to ");
  Serial.print(ssid); // display on the serial monitor, what is the name of your WIFI

  //Wait for WiFi to connect
  while(WiFi.waitForConnectResult() != WL_CONNECTED){      
      Serial.print("."); 
      delay(500);
    }
    
  //If connection successful show IP address in serial monitor
  Serial.println("");
  Serial.print("Connected to ");
  Serial.println(ssid);//bdw you can only see this if you open your serial monitor do not forget the baudrate
  Serial.print("IP address: "); // here you can see what is your IP address and copy thay addres to your app and input that IP.
  Serial.println(WiFi.localIP());  //IP address assigned to your ESP32
//----------------------------------------------------------------
 
  server.on("/", handleRoot);      //This is display page
  server.on("/readTemp", handleTemp);//To get update of Temperature Value only
  
  server.on("/", handleRoot);      //This is display page
  server.on("/readHum", handleHum);//To get update of Humidity Value only

  server.on("/", handleRoot);      //This is display page
  server.on("/readPump", handlePump);//To get update of Pump if it is ON or OFF

  server.on("/", handleRoot);      //This is display page
  server.on("/readSoil", handleSoil);//To get update of Soil moisture Value only
 
  server.begin(); //Start server
  Serial.println("HTTP server started");
}
//===============================================================
// This routine is executed when you open its IP in browser
//===============================================================
void loop(void){
  server.handleClient();
  Serial.print("IP address: ");
  Serial.println(WiFi.localIP()); // displays the IP address
  sensorVal = digitalRead(sensor); // reading the soil sensor value
  Serial.println(sensorVal); // display the value of the soil sensor
  int chk = DHT11.read(DHT11PIN); // read the DHT11 sensor value
  sensorVal = digitalRead(sensor);
  h = DHT11.humidity; // read the humidity value 
  t = DHT11.temperature; // read the temperature value

  //if the soil is dry then execute this statement
  if(sensorVal == 1) {
    //Serial.println("Watering the plant");
    digitalWrite(relayPin, LOW);
    pumpString = "ON"; // send this string to app
    soilAnalog = "DRY"; //send this string to app
    delay(5000);
  //if not then execute this statement
  }else {
    //Serial.println("does not need water");
    digitalWrite(relayPin, HIGH);
    pumpString = "OFF";
    soilAnalog = "WET";
  }
  delay(1000);
}



//===============================================================
// This routine is executed when you open its IP in browser
//===============================================================
void handleRoot() {
 String s = MAIN_page; //Read HTML contents
 server.send(200, "text/html", s); //Send web page
}
 

void handleHum() {
  String humVal = String(h); //updated the humidity value and assign it to string.
  server.send(200, "text/plane", humVal); //Send humidity value only to client ajax request
}

void handleTemp() {
  String tempVal = String(t); //updated the temperature value and assign it to string.
  server.send(200, "text/plane", tempVal); //Send temperature value only to client ajax request
}

void handlePump() {
  String pumpVal = pumpString; //updated the pump
  server.send(200, "text/plane", pumpVal); //Send pump string only to client ajax request
}

void handleSoil() {
  String soilVal = soilAnalog; //updated the soil moisture
  Serial.println("Temperature: "+ String(t)); //it will display this in the serial monitor
  Serial.println("Humidity: "+ String(h));
  Serial.println("Soil Moisture Sensor: "+ String(soilAnalog));
  Serial.println("Water Pump: "+ pumpString);
  server.send(200, "text/plane", soilVal); //Send soil moisture value only to client ajax request
}
