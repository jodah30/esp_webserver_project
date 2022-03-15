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
#include <SPI.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

//#include <NTPClient.h>
//#inlcude "time.h"



//Hardware SPi, declare Pin
Adafruit_MAX31865 thermo = Adafruit_MAX31865(5);   //

// The value of the Rref resistor. Use 430.0 for PT100 and 4300.0 for PT1000
#define RREF      430.0
// The 'nominal' 0-degrees-C resistance of the sensor
// 100.0 for PT100, 1000.0 for PT1000
#define RNOMINAL  100.0

// Settings for build in led and Slider
const int output =2; //gpio led
String sliderValue = "80";
String waterValue= "80";
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

int istZeitH;
int istZeitMin;

int sollZeitH;
int sollZeitMin;

bool POWER = 0;
unsigned long previousMillisprintT = 0;
unsigned long intervalprintT = 10000;

unsigned long previousMillisWifi = 0;
unsigned long intervalWifi = 10000;

// Replace with your network credentials
//const char* ssid = "K-J";
const char* ssid = "Jonas iPhone";
//passwod stored in password.ino

// Create AsyncWebServer object on port 80
AsyncWebServer server(80);

// Define NTP Client to get time
// WiFiUDP ntpUDP;
// NTPClient timeClient(ntpUDP, "pool.ntp.org");
//NTP
const char* ntpServer = "pool.ntp.org";
const long  gmtOffset_sec = 3600;
const int   daylightOffset_sec = 3600;
//const char updateInterval = 36000000;  // In ms


// creating task handle
TaskHandle_t Task0;
TaskHandle_t Task1;
//Declaration OLED

//Adafruit_SSD1306 display(128,32, &Wire, -1);
// #define SCREEN_WIDTH 128 // OLED display width, in pixels
// #define SCREEN_HEIGHT 32 // OLED display height, in pixels
// #define I2C_SDA 33 // new pins fot set others then the degailt one
// #define I2C_SCL 32
// #define OLED_RESET     -1 // Reset pin # (or -1 if sharing Arduino reset pin)
// #define SCREEN_ADDRESS 0x3C ///< See datasheet for Address; 0x3D for 128x64, 0x3C for 128x32
// //display.begin(SSD1306_SWITCHCAPVCC, 0x3C);
// TwoWire I2COLED = TwoWire(1);
//
// Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &I2COLED, OLED_RESET);


void setup(){



//initialize Cores
//create Task to run code in it
xTaskCreatePinnedToCore(
  codeForCore0,            /* Task function. */
  "Task0",                 /* name of task. */
  8192,                    /* Stack size of task */
  NULL,                     /* parameter of the task */
  1,                        /* priority of the task */
  &Task0,                   /* Task handle to keep track of created task */
  0);                    /* Core */
delay(500);

xTaskCreatePinnedToCore(
  codeForCore1,            /* Task function. */
  "Task1",                 /* name of task. */
  8192,                    /* Stack size of task */
  NULL,                     /* parameter of the task */
  1,                        /* priority of the task */
  &Task1,                   /* Task handle to keep track of created task */
  1);                    /* Core */
delay(500);

// Serial port for debugging purposes
Serial.begin(115200);
//start temp
thermo.begin(MAX31865_2WIRE);  // set to 2WIRE or 4WIRE as necessary
Serial.println("thermo begin");
// configure LED PWM functionalitites
ledcSetup(ledChannel, freq, resolution);
// attach the channel to the GPIO to be controlled
ledcAttachPin(output, ledChannel);
ledcWrite(ledChannel, sliderValue.toInt());
//call wifi function and password

connect_to_wifi(ssid, callpassword());
//call  server function
server_and_requests();
// Initialize a NTPClient to get time
  // timeClient.begin();
  // // Set offset time in seconds to adjust for your timezone, for example:
  // // GMT +1 = 3600
  // // GMT +8 = 28800
  // // GMT -1 = -3600
  // // GMT 0 = 0
  // timeClient.setTimeOffset(0);

//define ntp and Setup
configTime(gmtOffset_sec, daylightOffset_sec, ntpServer);
//Setup OLED
//
// I2COLED.begin(I2C_SDA,I2C_SCL,200000);
// if(!display.begin(SSD1306_SWITCHCAPVCC, SCREEN_ADDRESS)) {
//   Serial.println(F("SSD1306 allocation failed"));
//   for(;;); // Don't proceed, loop forever
// }

}

void loop(){

}
