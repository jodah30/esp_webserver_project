#include <DS1307RTC.h>
#include <Time.h>


#include <OneWire.h> 
#include <DallasTemperature.h>
#include <PID_v1.h>
#include <EEPROM.h>


#include <SPI.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

#define OLED_RESET 4
Adafruit_SSD1306 display(OLED_RESET);

#define NUMFLAKES 10
#define XPOS 0
#define YPOS 1
#define DELTAY 2

#define LOGO16_GLCD_HEIGHT 16 
#define LOGO16_GLCD_WIDTH  16 
//const unsigned char coffee [] PROGMEM = {
//  // 'Kaffeetasse-klein, 32x32px
// 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
// 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
//  0x00, 0x3f, 0x80, 0x00, 0x02, 0x00, 0x08, 0x00, 0x00, 0x00, 0x02, 0x00, 0x08, 0x3f, 0xe1, 0x00, 
//  0x0b, 0xff, 0xf9, 0xd0, 0x08, 0xff, 0xf0, 0x00, 0x00, 0x00, 0x02, 0x50, 0x0c, 0x00, 0x03, 0x20, 
//  0x20, 0x00, 0x01, 0xc0, 0x42, 0x00, 0x04, 0x40, 0x81, 0x00, 0x10, 0x20, 0xa0, 0x40, 0x20, 0x20, 
//  0x10, 0x0e, 0x00, 0x20, 0x40, 0x00, 0x00, 0x40, 0x10, 0x80, 0x01, 0x80, 0x03, 0x00, 0x0e, 0x00, 
//  0x00, 0x1f, 0xc0, 0x00, 0x00, 0x00, 0x00, 0x3e, 0x00, 0x00, 0x00, 0x6e, 0x00, 0x00, 0x00, 0x38, 
//  0x00, 0x00, 0x01, 0x80, 0x00, 0x00, 0x01, 0x0e, 0x00, 0x00, 0x00, 0x1f, 0x00, 0x00, 0x00, 0x06
//};

const unsigned char dampf [] PROGMEM = {
  // 'Nebel, 32x32px
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01, 0x80, 0x00, 
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
  0x00, 0x00, 0x80, 0x00, 0x00, 0x01, 0x80, 0x00, 0x00, 0x01, 0x80, 0x00, 0x00, 0x01, 0x80, 0x00, 
  0x00, 0x01, 0x80, 0x00, 0x00, 0x01, 0x80, 0x00, 0x00, 0x01, 0x80, 0x00, 0x00, 0x01, 0x80, 0x00, 
  0x00, 0x01, 0x80, 0x00, 0x00, 0x01, 0xc0, 0x00, 0x00, 0x03, 0x80, 0x00, 0x00, 0x01, 0xb0, 0x00, 
  0x00, 0x17, 0xf8, 0x00, 0x00, 0x3f, 0xff, 0x00, 0x00, 0x3f, 0xff, 0x00, 0x00, 0x3f, 0xff, 0x00, 
  0x00, 0x0f, 0xff, 0x80, 0x00, 0x1f, 0xf8, 0x00, 0x00, 0x0b, 0xc0, 0x00, 0x00, 0x00, 0x00, 0x00, 
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
};

#if (SSD1306_LCDHEIGHT != 32)
#error("Height incorrect, please fix Adafruit_SSD1306.h!");
#endif



// t 0.3 war eigentlich 0.5
//jezuz t 1
//I 75
//min55

/********************************************************************/
// Data wire is plugged into pin 9 on the Arduino 
#define ONE_WIRE_BUS 9 

const int Thot = 10;
const int Tpump = 6;
const int Thebel = 8;
const  int pump = 12;
const int power = 11;
int ThotStat = 0;
int TpumpStat = 0;
int ThebelStat = 0;
int powerStat = 1;
int level0=A2;

//int ErrorWlevel=A0;

int stunde=7;
int minuten=30;
int f=0;    // Variable für faden

int balken;
int a0;
//int errorw;

const int Lhot=7;
const int Lpump=2;
const int Lpower=5;

boolean Kaffee, Lamp, FehlerH, FehlerW, H, Zeitschalt, Autooff;

double Startmillis, Startmillis2,Startmillis3, AutooffZeit,AutooffStart, AutooffIst, Istmillis, Zeit, Timeout;
short  SumKaffee,Start,ErrorH, Counter;//,ErrorW, Start;

String T, S, P, Timer;
double Setpoint, Input, Output, Standart, Drinnen ;
PID myPID(&Input, &Output, &Setpoint,11.5,10,280, DIRECT);



/********************************************************************/
// Setup a oneWire instance to communicate with any OneWire devices  
// (not just Maxim/Dallas temperature ICs) 
OneWire oneWire(ONE_WIRE_BUS); 
/********************************************************************/
// Pass our oneWire reference to Dallas Temperature. 
DallasTemperature sensors(&oneWire);
DeviceAddress Gehause = {0x28, 0x61, 0x64, 0x11, 0xB2, 0x40, 0x17, 0x25};
DeviceAddress Kessel = {0x28, 0xFF, 0x22, 0x3C, 0x71, 0x17, 0x03, 0x4D};
/********************************************************************/ 
void setup(void) { 
   Autooff=LOW;
   AutooffStart=0;
   Zeitschalt=LOW;
   Timeout=5400000;
   H=LOW;
   Counter=0;
   
  digitalWrite(pump,HIGH);
  digitalWrite(power, HIGH);

  //Temp lesen
sensors.requestTemperatures(); // Send the command to get temperature readings 
Input = sensors.getTempC(Kessel); // Ist Temperatur für PID in Variable schreiben

  
  // PinMode
  pinMode(3,OUTPUT);   //Outputpin für SSR
  pinMode(8,INPUT);     // Schalter für Hebel
  pinMode(6, INPUT);      //Schalter für Pumpe
  pinMode(10, INPUT);      //Schalter für Hot
  pinMode(12,OUTPUT);     // Relais für Ground
  pinMode(11, OUTPUT);    //Relais für Pumpe ein
  pinMode(level0, INPUT);


  //TempSensor starten
  sensors.begin(); 

  //RTC lesen
  setSyncProvider(RTC.get);

  
//CONFIG für 

    Standart=EEPROM.read(0);
    Setpoint=Standart;
    myPID.SetMode(AUTOMATIC);

 //Display  

      display.begin(SSD1306_SWITCHCAPVCC, 0x3C);
      display.display();

           
          
         SumKaffee=EEPROM.read(1);
         ErrorH=EEPROM.read(2);
        // ErrorW=EEPROM.read(3);
         Start=EEPROM.read(4);
         Start++;
         EEPROM.update(4,Start);


     
  
  display.clearDisplay();


  display.setTextSize(1);
  display.setTextColor(WHITE);
  display.setCursor(80,0);
  display.drawLine(80,8,115,8,1);
  display.println("Coffee");

  display.setTextSize(2);

  if(SumKaffee<=99) {
    display.setCursor(88,14);
    display.println(SumKaffee);
    display.display();
  }else{
    display.setCursor(80,14);
    display.print(SumKaffee);
    display.display();
  }
  
  delay(1000);

  
  display.clearDisplay();
  display.setTextSize(1);
  display.setCursor(79,0);
  display.println("Stats");
  display.drawLine(79,8,117,8,1);
  display.setCursor(79,12);
  display.println("Start:");
  display.setCursor(113,12);
  display.println(Start);
  display.setCursor(79,20);
  display.println("Hot:");
  display.setCursor(113,20);
  display.println(ErrorH);
 
  display.display();
  
  delay(1000);
//  display.clearDisplay();
//  display.drawBitmap(80,0,coffee,32,32,1);
//  display.display();
//
//  delay(1000);
//  display.clearDisplay();
//  display.setCursor(80,0);
//  Drinnen = sensors.getTempC(Gehause); // Ist Temperatur für PID in Variable schreiben
//  display.println(Drinnen);
//  display.setCursor(80,8);
//  display.println("Start");
//  display.setCursor(80,16);
//  display.println(Start);
//  display.display();
//  digitalWrite(Lpower, HIGH);
//     delay(300);
//     digitalWrite(Lpower,LOW);
//     delay(50);
//     digitalWrite(Lpower, HIGH);
//     delay(300); 
//     digitalWrite(Lpower, HIGH);
//     delay(300);
//     digitalWrite(Lpower,LOW);
  
   //Startrelais starten
   digitalWrite(power, LOW);


    //Lamp für toggle
    Lamp=1;
}


  
void loop(void) 
{ 



    analogWrite(3,Output);
 sei();




//Fehler Sensor
if(Input<= 10 || Input>= 135){
  Counter=Counter+1;
                if(Counter>= 5){
                    digitalWrite(power, HIGH);
                    FehlerH= HIGH;
                    Standart=0;
                    Setpoint=0;
                }    
 }

  if(FehlerH==HIGH && H==LOW){

    ErrorH=ErrorH+1;
    EEPROM.update(2,ErrorH);
    H=HIGH;
  }

 //Fehler Wasser im Gehäuse
//  errorw=analogRead(ErrorWlevel);
// if(errorw>=100){
//  
//  
//  digitalWrite(power, HIGH);
//  FehlerW= HIGH;
//  Standart=0;
//  Setpoint=0;  }
//
//  if(FehlerW==HIGH && H==LOW){
//
//    ErrorW=ErrorW+1;
//    EEPROM.update(3,ErrorW  );
//    H=HIGH;
//  }

  //Fehler Pumpe zu lange an

  if(Zeit>=60000){
    digitalWrite(power, HIGH);
  
     Standart=0;
     Setpoint=0; 
  }
    
 // Stat abfagen
 Stat();
//Autooff
/////////////////////////////////
////////////////////////////////



if(Autooff==HIGH){

                          digitalWrite(power, HIGH);          //Ausschalten
                        digitalWrite(pump, HIGH);
                        Output=0;
                        analogWrite(3,Output);
                        display.clearDisplay();
                        display.setTextSize(1);
                        Zeitanzeigen();
                        
                        display.setCursor(80,10);
                        display.println("AutoOff");
                        display.display();
                        digitalWrite(Lpower,LOW);
                        digitalWrite(Lhot,LOW);
                        digitalWrite(Lpump,LOW);

                                      if(TpumpStat == HIGH || ThebelStat == HIGH || ThotStat == HIGH){

                                        Autooff=LOW;
                                        AutooffStart=millis();
                                        Startmillis=millis();
                                        digitalWrite(power,LOW);
                                      }
                        
                        
}




 
 
//schleife für Zeitschaltuhr
/////////////////////////////////////////////////
////////////////////////////////////////////////
if(Zeitschalt==HIGH && Autooff==LOW){

//Soll               
                        digitalWrite(power, HIGH);          //Ausschalten
                        digitalWrite(pump, HIGH);
                        Output=0;
                        analogWrite(3,Output);
//Lpower aufleuchten lassen
         if(TpumpStat == LOW && ThebelStat == LOW && ThotStat == LOW){
                         digitalWrite(Lhot, LOW);
                         digitalWrite(Lpump, LOW);
                        if((millis()-Startmillis2)>=10000){
                          analogWrite(Lpower,20);
                          delay(100);
                           analogWrite(Lpower,50);
                           delay(100);
                            analogWrite(Lpower,80);
                            delay(100);
                             analogWrite(Lpower,150);
                             delay(100);
                              analogWrite(Lpower,200);
                              delay(100);
                               analogWrite(Lpower,235);
                               delay(100);
                               analogWrite(Lpower,220);
                          delay(100);
                           analogWrite(Lpower,235);
                           delay(100);
                            analogWrite(Lpower,200);
                            delay(100);
                             analogWrite(Lpower,150);
                             delay(100);
                              analogWrite(Lpower,80);
                              delay(100);
                               analogWrite(Lpower,20);
                               delay(100);
                               analogWrite(Lpower,0);
                            
                            Startmillis2=millis();
                            
                            }
                }
          
//Display         
                  if((millis()-Startmillis3)<=60000){
                        display.clearDisplay();
                        display.setTextSize(1);
                        Zeitanzeigen();
                        display.setCursor(80,8);
                        display.print("ready:");
                        display.drawLine(80,17,110,17,1);
                        
                                      display.setCursor(80,20);
                                        if(stunde<10){
                                        display.setCursor(85,20);
                                        }
                                      display.print(stunde);
                                      display.setCursor(92,20);
                                      display.print(":");
                                      display.setCursor(98,20);
                                         if(minuten<10){
                                         display.println("0");
                                         display.setCursor(103,20);
                                         }
                                      display.println(minuten);
                          display.display();   
                  }else{
                    display.clearDisplay();
                    display.display();
                  }
                  
                                      

                                      delay(1000);    //Zeit für zurücksetzen
//Zeit setzen

   //Stunden
                       if(TpumpStat == HIGH && ThebelStat == LOW && ThotStat == LOW){
                          digitalWrite(Lpump, HIGH);
                          delay(800);
                          digitalWrite(Lpump,LOW);
                          delay(200);
                          Stat();
                                 if(TpumpStat == HIGH && ThebelStat == LOW && ThotStat == LOW){
                                     stunde=stunde+1;
                                          if(stunde>=24){
                                          stunde=0;
                                          }
                                    }
                        }           
    //minuten
                        if(TpumpStat == LOW && ThebelStat == LOW && ThotStat == HIGH){
                          digitalWrite(Lhot, HIGH);
                          delay(800);
                          digitalWrite(Lhot,LOW);
                          delay(200);
                          Stat();
                                 if(TpumpStat == LOW && ThebelStat == LOW && ThotStat == HIGH){
                                     minuten=minuten+15;
                                          if(minuten>=60){
                                          stunde=stunde+1;
                                          minuten=0;
                                          }
                                    }
                        }           


  //minuten+stunden
                        if(TpumpStat == HIGH && ThebelStat == LOW && ThotStat == HIGH){
                          digitalWrite(Lhot, HIGH);
                          digitalWrite(Lpump, HIGH);
                          delay(800);
                          digitalWrite(Lhot,LOW);
                          digitalWrite(Lpump, LOW);
                          delay(200);
                          Stat();
                                 if(TpumpStat == HIGH && ThebelStat == LOW && ThotStat == HIGH){
                                     minuten=minuten+15;
                                     stunde=stunde+1;
                                          if(minuten>=60){
                                          stunde=stunde+1;
                                          minuten=0;
                                          }
                                          if(stunde>=24){
                                          stunde=0;
                                          }
                                    }
                        }  

 //---minuten           
                        if(TpumpStat == LOW && ThebelStat == HIGH && ThotStat == HIGH){
                          digitalWrite(Lhot, HIGH);
                          delay(800);
                          digitalWrite(Lhot,LOW);
                          delay(200);
                          Stat();
                                 if(TpumpStat == LOW && ThebelStat == HIGH && ThotStat == HIGH){
                                     minuten=minuten-5;
                                          if(minuten<=0){
                                             minuten=0;
                                          }
                                    }
                        }           

//---stunde           
                        if(TpumpStat == HIGH && ThebelStat == HIGH && ThotStat == LOW){
                          digitalWrite(Lpump, HIGH);
                          delay(800);
                          digitalWrite(Lpump,LOW);
                          delay(200);
                          Stat();
                                 if(TpumpStat == HIGH && ThebelStat == HIGH && ThotStat == LOW){
                                     stunde=stunde-1;
                                          if(stunde<=0){
                                             stunde=24;
                                          }
                                    }
                        }           



 
      //Zurücksetzen
                         if(TpumpStat == LOW && ThebelStat == HIGH && ThotStat == LOW){
                          Startmillis3=millis();
                          delay(1500);
                          Stat();
                                 if(TpumpStat == LOW && ThebelStat == HIGH && ThotStat == LOW){
                                     minuten=0;
                                     stunde=6;     
                                    }
                        }           







//Zurückschaltung bei erreichter Zeit
                        
                        if(hour()==stunde && minute() == minuten){
                          Zeitschalt=LOW;
                          AutooffStart=millis();
                          Startmillis=millis();
                          digitalWrite(power,LOW);
                        }  

}
//Schleife für Kaffeebetrieb
/////////////////////////////////////////////////
/////////////////////////////////////////////////

if(Zeitschalt==LOW && Autooff==LOW){
AutooffIst=millis();
AutooffZeit=AutooffIst-AutooffStart;

if(AutooffZeit>=Timeout){                //Autooff Funktion
  Autooff=HIGH;
}


sensors.requestTemperatures(); // Send the command to get temperature readings 
Input = sensors.getTempC(Kessel); // Ist Temperatur für PID in Variable schreiben
//Drinnen = sensors.getTempC(Gehause); // Ist Temperatur für PID in Variable schreiben


myPID.Compute();
analogWrite(3,Output);


   // Normal
if(TpumpStat == LOW && ThebelStat == LOW && ThotStat == LOW) {

// Soll 
                                    
                                    digitalWrite(pump, HIGH);
                                    Setpoint = Standart;
                                    digitalWrite(Lpump, LOW);
                                    digitalWrite(Lhot, LOW);
//Display Normal
                                     DisplayNormal();
// Für Timer
                                    Startmillis=millis();   
                                    Zeit=0;
//Zähler für Kaffee

                                if(Kaffee ==  HIGH)  {

                                  SumKaffee=SumKaffee+1;
                                  EEPROM.update(1,SumKaffee);
                                  delay(1000);
                                  Kaffee = LOW;
                                  }

// PowerLampe
                                  ZielTemp();

   
}
    //Kaffee
   if (TpumpStat == LOW && ThebelStat == HIGH && ThotStat == LOW)  {
                                  
    // Soll
                                    digitalWrite(pump, LOW);
                                    Setpoint=Standart;
                                    AutooffStart=millis();


    //Display Timer
                                    
                                    

                                     display.clearDisplay();
                                     display.setTextSize(1);
                                     display.setCursor(83,0);
                                     display.println("Time"); 
                                     display.drawLine(83,8,107,8,1);
                                     display.setTextSize(2);
                                     display.setTextColor(WHITE);
                                     Istmillis=millis();
                                     Zeit=Istmillis-Startmillis;
                                     Timer=String(Zeit/1000,0);
                                     if(Zeit<=9000) {
                                      
                                     digitalWrite(Lpower, LOW);
                                     display.setCursor(78,13);
                                     display.println(Timer);
                                     display.display();
                                     }
                                     else{
                                     display.setCursor(83,13);
                                     display.println(Timer);
                                     display.display();
                                     }


                                      if(Zeit>=20000)  {

                                        Kaffee= HIGH;
                                        digitalWrite(Lpower,HIGH);
                                        display.drawLine(83,30,107,30,1);
                                        display.display();
                                      }
}

// für Wasser
    if(TpumpStat == HIGH && ThebelStat == LOW && ThotStat == LOW) {

    //Soll                    Zei=0
                              digitalWrite(pump, LOW);
                              digitalWrite(Lpump, HIGH);
                              Setpoint=Standart;
                              AutooffStart=millis();
                              
                                
    //Display Normal
                               DisplayNormal();
                               
    // ZielTemp                  
                              ZielTemp();         

     // Abschaltung
                               Istmillis=millis();
                               Zeit=Istmillis-Startmillis;
 
}

//schleife für Dampf

  if(ThotStat == HIGH && ThebelStat == LOW && TpumpStat == LOW)  {
                                   
  //Soll                             Zeit=0
                                     Setpoint = 125;
                                     digitalWrite(Lhot, HIGH);
                                     digitalWrite(pump, HIGH);
                                     AutooffStart=millis();
//ZielTemp

                                     ZielTemp();                                    


   // Display bei ZielTemp ereicht
                                      if(Input>=105)  { 
                                      T = String(Input,1);
                                      
                                      
                                     display.clearDisplay();
                                     display.drawBitmap(80,0,dampf,32,32,1);
                                     
                                     display.display();
                                     display.setCursor(80,0);
                                     display.println(T);
                                     display.setCursor(110,0);
                                     display.display();
                                     
                                      }else {

                     //Sonst DisplayNormal 
                              
                                    DisplayNormal();
                                      }
}
  
//Zieltemperatur einstellen  ++++
if(ThotStat == HIGH && ThebelStat == HIGH && TpumpStat == HIGH)    {


 //SOLL                              
                                     Setpoint=0;
                                     digitalWrite(pump, HIGH);              //Pumpe aus

                                     digitalWrite(Lpump, HIGH);             //Lampen an
                                     digitalWrite(Lhot, HIGH);
                                     digitalWrite(Lpower, HIGH);
                                     DisplayT();                            // Display 
                                     delay(1000);

                                     digitalWrite(Lpump, LOW);              //Lampen aus für Blinkmodus
                                     digitalWrite(Lhot, LOW);
                                     digitalWrite(Lpower, LOW);

                                     delay(1000);
                                     Stat();
                                     if(ThotStat == HIGH && ThebelStat == HIGH && TpumpStat == HIGH){
                                     Standart=Standart+1;
                                     
                                             if (Standart>=100) {
                                              Standart=100;
                                              }
                                      
                                      EEPROM.update(0,Standart);
                                     }
}                                     

// Zieltemperatur einstellen ----
 if(ThotStat == HIGH && ThebelStat == LOW && TpumpStat == HIGH)    {

                                      Setpoint=0;
//SOLL
                                     digitalWrite(pump, HIGH);              //Pumpe aus
                                     digitalWrite(Lpower, LOW);
                                   

                                     digitalWrite(Lpump, HIGH);             //Lampen an
                                     digitalWrite(Lhot, HIGH);
                                     DisplayT();                            // Display 
                                     delay(1000);

                                     digitalWrite(Lpump, LOW);              //Lampen aus für Blinkmodus
                                     digitalWrite(Lhot, LOW);

                                     delay(1000);
                                     Stat();
                                     if(ThotStat == HIGH && ThebelStat == LOW && TpumpStat == HIGH){
                                        Standart=Standart-1;
                                     
                                          if (Standart<=80) {
                                            Standart=80;
                                           }
                                      
                                      EEPROM.update(0,Standart);
                                     }
}




//Aufheizen während kaffee bezug
 if(ThotStat == HIGH && ThebelStat == HIGH && TpumpStat == LOW && Zeit >=1000) {



                                      // Soll
                                    digitalWrite(pump, LOW);
                                    Setpoint=125;
                              


    //Display Timer
                                    
                                    

                                     display.clearDisplay();
                                     display.setTextSize(1);
                                     display.setCursor(83,0);
                                     display.println("HOT!"); 
                                     display.drawLine(83,8,107,8,1);
                                     display.setTextSize(2);
                                     display.setTextColor(WHITE);
                                     Istmillis=millis();
                                     Zeit=Istmillis-Startmillis;
                                     Timer=String(Zeit/1000,0);
                                     if(Zeit<=9000) {
                                      
                                     digitalWrite(Lpower, LOW);
                                     display.setCursor(78,13);
                                     display.println(Timer);
                                     display.display();
                                     }
                                     else{
                                     display.setCursor(83,13);
                                     display.println(Timer);
                                     display.display();
                                     }


                                      if(Zeit>=20000)  {

                                        Kaffee= HIGH;
                                        digitalWrite(Lpower,HIGH);
                                        display.drawLine(83,30,107,30,1);
                                        display.display();
                                      }
                                    
 }
// Zeitschaltuhr
          if(ThotStat == LOW && ThebelStat == HIGH && TpumpStat == HIGH){
                                     
                                     Setpoint=0;
                                     
                                     digitalWrite(pump , HIGH);                     // Pumpe aus
                                     
                                     display.clearDisplay();
                                     display.setTextSize(1);
                                     
                                     Zeitanzeigen();
                                   
                                     display.setCursor(80,8);
                                     display.println("Starte");
                                     display.setCursor(80,16);
                                     display.println("Zeitschaltuhr");
                                     display.setCursor(80,25);
                                     display.println("in 5s");
                                     display.display();
                                     delay(5000);
                                     Stat();
                                        if(ThotStat == LOW && ThebelStat == HIGH && TpumpStat == HIGH){
                                           Zeitschalt=HIGH;
                                           Startmillis2=millis();
                                           Startmillis3=millis();
                                           
                                        }
            }

}
//Error
 if(ThotStat == HIGH && ThebelStat == HIGH && TpumpStat == LOW && Zeit <=1000) {
                                     
                                     Drinnen = sensors.getTempC(Gehause); // Ist Temperatur für PID in Variable schreiben

                                   
                                     Setpoint=0;
                                     digitalWrite(pump, HIGH);                    //Pumpe aus


                                      a0=analogRead(level0);
                                     display.clearDisplay();
                                     display.setTextSize(1);
                                     display.setTextColor(WHITE);
                                     display.setCursor(80,0);
                                     display.println(Timeout/60000);
                                     display.setCursor(80,8);
                                     display.print(a0);
                                     display.setCursor(80,16);
                                     display.println(Drinnen);
                                     
                                      display.display();
                                    
 }

}
//Function Display set T
void DisplayT(){                                     
                                     display.clearDisplay();
                                     display.setTextSize(1);
                                     display.setCursor(83,0);
                                     display.println("set T"); 
                                     display.drawLine(73,8,118,8,1);
                                     
                                     display.setTextSize(2);
                                     display.setTextColor(WHITE);
                                     
                                     display.setCursor(73,13);
                                     display.println(Standart);
                                     display.display();

}

// Function Zieltemperatur
void ZielTemp(){
                                       if(abs(Input-Setpoint)<=1.5) {
                                digitalWrite(Lpower, HIGH);  
                                  }

                                if(abs(Input-Setpoint)>=1.5) {


                                      if(Lamp==HIGH){

                                       f=f+10;
                                       analogWrite(Lpower, f);
                                                  if(f>=250){
                                                    Lamp=LOW;
                                                  }

                                      }

                                      if(Lamp==LOW){

                                       f=f-10;
                                       analogWrite(Lpower, f);
                                                  if(f<=10){
                                                    Lamp=HIGH;
                                                  }

                                      }
                                 
                                  }
}
// Function Displaynormal
void DisplayNormal(){ 


                                      a0=analogRead(level0);
                                  
                                      
                                
                                      
                                      T = String(Input,1);
                                      S = String(Setpoint ,1);
                                      P = String(Output/2.55,0);
                                      
                                     display.clearDisplay();
                                     display.setTextSize(1);
                                     display.setCursor(80,0);
                                     display.println(T);
                                     display.setCursor(110,0);
                                     display.println("C");
                                     display.drawPixel(107,0,1);
                                     display.drawPixel(107,1,1);
                                     display.drawPixel(108,0,1);
                                     display.drawPixel(108,1,1);
                                    
                                     display.setCursor(80,8);
                                     display.println(S);
                                     display.setCursor(110,8);
                                     display.println("C");
                                     display.drawPixel(107,8,1);
                                     display.drawPixel(107,9,1);
                                     display.drawPixel(108,8,1);
                                     display.drawPixel(108,9,1);

                       
                                     display.setCursor(80, 16);
                                     display.println(P);
                                     display.setCursor(110,16);
                                     display.println("%");
                                    
    //Wasserstand
                                   if (a0>=300){  
                                     
                                        display.drawRect(80,24,35,8,1);
                                        balken=map(a0,320,540,0,31);
                                        display.fillRect(82,26,balken,4,1);
                                   }else {  
                                        display.setCursor(80,24);
                                        display.println("Sensor!");
                                          }
                        display.display();
} 

//Function Zeit anzeigen
void Zeitanzeigen(){
                                  display.setCursor(80,0);
                                        if(hour()<10){
                                          display.setCursor(85,0);
                                        }
                                  display.print(hour());
                                  display.setCursor(92,0);
                                  display.print(":");
                                  display.setCursor(98,0);
                                         if(minute()<10){
                                          display.println("0");
                                          display.setCursor(103,0);
                                         }
                                 display.println(minute());
}
  
 void Stat(){
  ThotStat = digitalRead(Thot);
  TpumpStat = digitalRead(Tpump);
  ThebelStat= digitalRead(Thebel);
  }
  
        
