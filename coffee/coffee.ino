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

// setup bools for timer
bool stunde_eins = 0;
bool stunde_zwei = 0;
bool stunde_vier = 0;
bool stunde_acht = 0;

bool minute_funf = 0;
bool minute_zehn = 0;
bool minute_zwanzig = 0;
bool minute_dreisig = 0;




// Replace with your network credentials
const char* ssid = "K-J";
const char* password = "!Tru3L0v3!";

// Create AsyncWebServer object on port 80
AsyncWebServer server(80);






// Replaces placeholder with button section in your web page





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



connect_to_wifi(ssid, password);


server_and_requests();




}

void loop(){

}
