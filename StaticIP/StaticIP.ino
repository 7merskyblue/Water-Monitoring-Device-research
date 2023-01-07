// Load Wi-Fi library
#include <WiFi.h>
#include <ESP32Ping.h>

//Enter your SSID and PASSWORD
const char* ssid     = "WIFI_SSID";
const char* password = "WIFI_PASS";

WiFiServer server(80);

// Set your Static IP address
IPAddress local_IP(192, 168, 1, 125);
// Set your Gateway IP address
IPAddress gateway(192, 168, 1, 123);
IPAddress subnet(255, 255, 0, 0);
IPAddress DNS(192, 168, 1, 123); 

void setup() {
  Serial.begin(9600);

  // Configures static IP address
  if (WiFi.config(local_IP, gateway, subnet, DNS, DNS) == false) {
    Serial.println("STA Failed to configure");
  }

  // Connect to Wi-Fi network with SSID and password
  Serial.print("Connecting to ");
  Serial.println(ssid);
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  // Print local IP address and start web server
  Serial.println("");
  Serial.println("WiFi connected.");
  Serial.print("IP address: ");
  Serial.println(WiFi.localIP());
  Serial.print("Subnet Mask: ");
  Serial.println(WiFi.subnetMask());
  Serial.print("Gateway IP: ");
  Serial.println(WiFi.gatewayIP());
  Serial.print("DNS 1: ");
  Serial.println(WiFi.dnsIP(0));
  Serial.print("DNS 2: ");
  Serial.println(WiFi.dnsIP(1));
  //server.begin();

  bool success = Ping.ping("www.google.com", 3);

  if(!success)
  {
    Serial.println("\nPing Success!");
    return;
  }
  Serial.println("\nPing Success!");

}

void loop() {

}
