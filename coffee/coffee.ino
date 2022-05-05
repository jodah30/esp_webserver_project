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
#include <Preferences.h>
Preferences preferences;
#include <Adafruit_MAX31865.h>
#include <SPI.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>




//OLED
// DO =clock, D1= MOSI,sda, DC=data command ,
#define SCREEN_WIDTH 128 // OLED display width, in pixels
#define SCREEN_HEIGHT 64 // OLED display height, in pixels
// Declaration for SSD1306 display connected using software SPI (default case):
#define OLED_MOSI   23
#define OLED_CLK   18
#define OLED_DC    19
#define OLED_CS    17
#define OLED_RESET 13
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT,
  OLED_MOSI, OLED_CLK, OLED_DC, OLED_RESET, OLED_CS);

//Hardware SPi, declare Pin
Adafruit_MAX31865 thermo = Adafruit_MAX31865(5);
#define RREF      430.0 // The value of the Rref resistor
#define RNOMINAL  100.0 // The 'nominal' 0-degrees-C resistance of the sensor, 100.0 for PT100, 1000.0 for PT1000

//create button_status and pins
int button_hot_pin      =   32;
int button_pump_pin     =   35;
int button_hebel_pin    =   33;
int button_power_pin    =   34;

int led_hot_pin         =   27;
int led_pump_pin        =   26;
int led_power_pin       =   25;

int relay_pump_pin      =   14;
int relay_power_pin     =   12;
int relay_ss            =   22;
int waterlevel_pin      =   0;

bool button_hot_status   =  0;
bool button_pump_status  =  0;
bool button_hebel_status =  0;
bool button_power_status =  0;

boolean button_hot_pin_new;
boolean button_hot_pin_old;

String string_setpoint, string_temperature, string_power;

String T, S, P, Timer;
double Setpoint, Input, Output, Standart, Drinnen;

//doubles for timers
double idle_millis;

int analog_waterlevel;
int analog_waterlevel_max;
int analog_waterlevel_min;
int digital_waterlevel;
// Settings for build in led and Slider
const int output =2; //gpio led
String sliderValue = "80";
String waterValue ;
String standbyValue ="92";
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
const char* ssid = "Jonas iPhone";
//passwod stored in password.ino

// Create AsyncWebServer object on port 80
AsyncWebServer server(80);

// Define NTP Client to get time
const char* ntpServer = "pool.ntp.org";
const long  gmtOffset_sec = 3600;
const int   daylightOffset_sec = 3600;
//const char updateInterval = 36000000;  // In ms

// creating task handle
TaskHandle_t Task0;
TaskHandle_t Task1;

void setup(){

  pinMode(button_hot_pin,INPUT_PULLDOWN);
  pinMode(button_pump_pin,INPUT);
  pinMode(button_hebel_pin,INPUT);
  pinMode(button_power_pin,INPUT);

  //create namespace to store values
  preferences.begin("settings", false);
  sliderValue=preferences.getString("sliderValue","");
  standbyValue=preferences.getString("standbyValue","");

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
    //  thermo.begin(MAX31865_2WIRE);  // set to 2WIRE or 4WIRE as necessary
      Serial.println("thermo begin");

      //start displayBtn
      if(!display.begin(SSD1306_SWITCHCAPVCC, 0x3C)) { // Address 0x3D for 128x64
        Serial.println(F("SSD1306 allocation failed"));
        for(;;);
      }

      // configure LED PWM functionalitites
      ledcSetup(ledChannel, freq, resolution);
      // attach the channel to the GPIO to be controlled
      ledcAttachPin(output, ledChannel);
      ledcWrite(ledChannel, sliderValue.toInt());

      //call wifi function and password
      connect_to_wifi(ssid, callpassword());
      //call  server function
      server_and_requests();
      //define ntp and Setup
      configTime(gmtOffset_sec, daylightOffset_sec, ntpServer);
      //display_for_timer();
    }

    void loop(){
    //  display_for_timer();

    }
