// Import required libraries
#ifdef ESP32
  #include <WiFi.h>
  #include <ESPAsyncWebServer.h>
  #include <SPIFFS.h>
#else
  #include <Arduino.h>
 // #include <ESP8266WiFi.h>
  #include <Hash.h>
  #include <ESPAsyncTCP.h>
  #include <ESPAsyncWebServer.h>
  #include <FS.h>
#endif
#include <Adafruit_MAX31865.h>

// Use software SPI: CS, DI, DO, CLK
Adafruit_MAX31865 thermo = Adafruit_MAX31865(5, 23, 19, 18);
// use hardware SPI, just pass in the CS pin
//Adafruit_MAX31865 thermo = Adafruit_MAX31865(19);   //gpio 6

// The value of the Rref resistor. Use 430.0 for PT100 and 4300.0 for PT1000
#define RREF      430.0
// The 'nominal' 0-degrees-C resistance of the sensor
// 100.0 for PT100, 1000.0 for PT1000
#define RNOMINAL  100.0

/*#include <SPI.h>
#define BME_SCK 18
#define BME_MISO 19
#define BME_MOSI 23
#define BME_CS 5*/




// Replace with your network credentials
const char* ssid = "K-J";
const char* password = "!Tru3L0v3!";



// Create AsyncWebServer object on port 80
AsyncWebServer server(80);



String readBME280Temperature() {
  // Read temperature as Celsius (the default)

  float temp=0;
  int anzahl_mittelung=10;

   for (int i =0; i< anzahl_mittelung ; ++i)
   {
      float H = thermo.temperature(RNOMINAL, RREF);
      temp += H;
      delay(1);

   }
   float t=temp/anzahl_mittelung;



  if (isnan(t)) {
    Serial.println("Failed to read from BME280 sensor!");
    return "";
  }
  else {
    Serial.println(t);
    return String(t);
  }
}


void setup(){
  // Serial port for debugging purposes
  Serial.begin(115200);

Serial.println("Adafruit MAX31865 PT100 Sensor Test!");

thermo.begin(MAX31865_2WIRE);  // set to 2WIRE or 4WIRE as necessary




//  // Initialize SPIFFS
//  if(!SPIFFS.begin()){
//    Serial.println("An Error has occurred while mounting SPIFFS");
//    return;
//  }

if(!SPIFFS.begin()){
  Serial.println("An Error has occurred while mounting SPIFFS");
  return;
}

Serial.println("Filesystem ready");





  // Connect to Wi-Fi
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.println("Connecting to WiFi..");
  }

  // Print ESP32 Local IP Address
  Serial.println(WiFi.localIP());

  // Route for root / web page
  server.on("/", HTTP_GET, [](AsyncWebServerRequest *request){
    request->send(SPIFFS, "/index.html");
  });
  // server.on("/highcharts.js", HTTP_GET, [](AsyncWebServerRequest *request){
  //   request->send(SPIFFS, "/highcharts.js", "text/javascript");
  // });
  server.serveStatic("/", SPIFFS, "/");  // send all files of root, used for static files

  server.on("/temperature", HTTP_GET, [](AsyncWebServerRequest *request){
    request->send_P(200, "text/plain", readBME280Temperature().c_str());
  });


  // Start server
  server.begin();
  Serial.println("Server.begin");

    File file = SPIFFS.open("/index.html");
  if(!file){
    Serial.println("Failed to open file for reading");
    return;
  }
  else Serial.println("Spiffs opened");

}

void loop(){

}
