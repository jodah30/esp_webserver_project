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
// Settings for build in led and Slider
const int output =2; //gpio led
String sliderValue = "80";
const char* PARAM_INPUT_1 = "output";
const char* PARAM_INPUT_2 = "state";


// setting PWM properties
const int freq = 5000;
const int ledChannel = 0;
const int resolution = 8;

const char* PARAM_INPUT = "value";



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


// Replaces placeholder with button section in your web page
String processor(const String& var){
  //Serial.println(var);
  if (var == "SLIDERVALUE"){
    return sliderValue;
  }
  // second template
  else  if(var == "BUTTONPLACEHOLDER"){
    String buttons = "";
    buttons += "<h4>Stunden -1-  Minuten-5-</h4><label class=\"switch\"><input type=\"checkbox\" onchange=\"toggleCheckbox(this)\" id=\"17\" " + outputState(17) + "><span class=\"slider_switch\"></span></label>";
    buttons += "<label class=\"switch\"><input type=\"checkbox\" onchange=\"toggleCheckbox(this)\" id=\"3\" " + outputState(3) + "><span class=\"slider_switch\"></span></label>";

    buttons += "<h4>Stunden -2-  Minuten-10-</h4><label class=\"switch\"><input type=\"checkbox\" onchange=\"toggleCheckbox(this)\" id=\"4\" " + outputState(4) + "><span class=\"slider_switch\"></span></label>";
    buttons += "<label class=\"switch\"><input type=\"checkbox\" onchange=\"toggleCheckbox(this)\" id=\"17\" " + outputState(17) + "><span class=\"slider_switch\"></span></label>";

    buttons += "<h4>Stunden -4-  Minuten-20-</h4><label class=\"switch\"><input type=\"checkbox\" onchange=\"toggleCheckbox(this)\" id=\"13\" " + outputState(13) + "><span class=\"slider_switch\"></span></label>";
    buttons += "<label class=\"switch\"><input type=\"checkbox\" onchange=\"toggleCheckbox(this)\" id=\"14\" " + outputState(14) + "><span class=\"slider_switch\"></span></label>";

    buttons += "<h4>Stunden -8-  Minuten-30-</h4><label class=\"switch\"><input type=\"checkbox\" onchange=\"toggleCheckbox(this)\" id=\"15\" " + outputState(15) + "><span class=\"slider_switch\"></span></label>";
    buttons += "<label class=\"switch\"><input type=\"checkbox\" onchange=\"toggleCheckbox(this)\" id=\"16\" " + outputState(16) + "><span class=\"slider_switch\"></span></label>";

    return buttons;
  }
  return String();
}



String outputState(int output){
  if(digitalRead(output)){
    Serial.print("outputStat is: ");
    Serial.println(output);
    return "checked";
  }
  else {
    return "";
  }
}


void setup(){
  // Serial port for debugging purposes
Serial.begin(115200);

pinMode(17, OUTPUT);
digitalWrite(17, LOW);
pinMode(3, OUTPUT);
digitalWrite(3, LOW);
pinMode(4, OUTPUT);
digitalWrite(4, LOW);
pinMode(17, OUTPUT);
digitalWrite(17, LOW);

pinMode(13, OUTPUT);
digitalWrite(13, LOW);
pinMode(14, OUTPUT);
digitalWrite(14, LOW);
pinMode(15, OUTPUT);
digitalWrite(15, LOW);
pinMode(16, OUTPUT);
digitalWrite(16, LOW);



thermo.begin(MAX31865_2WIRE);  // set to 2WIRE or 4WIRE as necessary
Serial.println("thermo begin");
// configure LED PWM functionalitites
ledcSetup(ledChannel, freq, resolution);

// attach the channel to the GPIO to be controlled
ledcAttachPin(output, ledChannel);
ledcWrite(ledChannel, sliderValue.toInt());


//  // Initialize SPIFFSs
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
    request->send(SPIFFS, "/index.html", String(), false, processor);

  });
  // server.on("/", HTTP_GET, [](AsyncWebServerRequest *request){
  // request->send_P(processor);
  // });
  // server.on("/highcharts.js", HTTP_GET, [](AsyncWebServerRequest *request){
  //   request->send(SPIFFS, "/highcharts.js", "text/javascript");
  // });
  server.serveStatic("/", SPIFFS, "/");  // send all files of root, used for static files

  server.on("/temperature", HTTP_GET, [](AsyncWebServerRequest *request){
    request->send_P(200, "text/plain", readBME280Temperature().c_str());
  });

  // Send a GET request to <ESP_IP>/slider?value=<inputMessage>
server.on("/slider", HTTP_GET, [] (AsyncWebServerRequest *request) {
  String inputMessage;
  // GET input1 value on <ESP_IP>/slider?value=<inputMessage>
  if (request->hasParam(PARAM_INPUT)) {
    inputMessage = request->getParam(PARAM_INPUT)->value();
    sliderValue = inputMessage;
    ledcWrite(ledChannel, sliderValue.toInt());
  }
  else {
    inputMessage = "No message sent";
  }
  Serial.println(inputMessage);
  request->send(200, "text/plain", "OK");
});



// Send a GET request to <ESP_IP>/update?output=<inputMessage1>&state=<inputMessage2>
server.on("/update", HTTP_GET, [] (AsyncWebServerRequest *request) {
  String inputMessage1;
  String inputMessage2;
  // GET input1 value on <ESP_IP>/update?output=<inputMessage1>&state=<inputMessage2>
  if (request->hasParam(PARAM_INPUT_1) && request->hasParam(PARAM_INPUT_2)) {
    inputMessage1 = request->getParam(PARAM_INPUT_1)->value();
    inputMessage2 = request->getParam(PARAM_INPUT_2)->value();
    digitalWrite(inputMessage1.toInt(), inputMessage2.toInt());
  }
  else {
    inputMessage1 = "No message sent";
    inputMessage2 = "No message sent";
  }
  Serial.print("GPIO: ");
  Serial.print(inputMessage1);
  Serial.print(" - Set to: ");
  Serial.println(inputMessage2);
  request->send(200, "text/plain", "OK");
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
