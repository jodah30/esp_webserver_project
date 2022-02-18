


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





String processor(const String& var){
  //return slidervalue, setpoint of temp
  if (var == "SLIDERVALUE"){
    return sliderValue;
  }
  // buttons for html
  else  if(var == "BUTTONPLACEHOLDER"){
    String buttons = "";
    buttons += "<h4>Stunden -1-  Minuten-5-</h4><label class=\"switch\"><input type=\"checkbox\" onchange=\"toggleCheckbox(this)\" id=\"S1\" " + State_of_bool(stunde_eins) + "><span class=\"slider_switch\"></span></label>";
    buttons += "<label class=\"switch\"><input type=\"checkbox\" onchange=\"toggleCheckbox(this)\" id=\"m5\" " + State_of_bool(minute_funf) + "><span class=\"slider_switch\"></span></label>";

    buttons += "<h4>Stunden -2-  Minuten-10-</h4><label class=\"switch\"><input type=\"checkbox\" onchange=\"toggleCheckbox(this)\" id=\"S2\" " + State_of_bool(stunde_zwei) + "><span class=\"slider_switch\"></span></label>";
    buttons += "<label class=\"switch\"><input type=\"checkbox\" onchange=\"toggleCheckbox(this)\" id=\"m10\" " + State_of_bool(minute_zehn) + "><span class=\"slider_switch\"></span></label>";

    buttons += "<h4>Stunden -4-  Minuten-20-</h4><label class=\"switch\"><input type=\"checkbox\" onchange=\"toggleCheckbox(this)\" id=\"S4\" " + State_of_bool(stunde_vier) + "><span class=\"slider_switch\"></span></label>";
    buttons += "<label class=\"switch\"><input type=\"checkbox\" onchange=\"toggleCheckbox(this)\" id=\"m20\" " + State_of_bool(minute_zwanzig) + "><span class=\"slider_switch\"></span></label>";

    buttons += "<h4>Stunden -8-  Minuten-30-</h4><label class=\"switch\"><input type=\"checkbox\" onchange=\"toggleCheckbox(this)\" id=\"S8\" " + State_of_bool(stunde_acht) + "><span class=\"slider_switch\"></span></label>";
    buttons += "<label class=\"switch\"><input type=\"checkbox\" onchange=\"toggleCheckbox(this)\" id=\"m30\" " + State_of_bool(minute_dreisig) + "><span class=\"slider_switch\"></span></label>";

    return buttons;
  }
  return String();
}




String State_of_bool(bool buttonstate){
  if (buttonstate == 1){
    Serial.print("This Button is ");
    Serial.println(buttonstate);
    return "checked";
  }
  else {
    Serial.print("This Button is off: ");
    Serial.println(stunde_eins);
    return "";
  }
}

bool write_input_to_bool(String inputMessage1, String inputMessage2){
    if (inputMessage1 == "S1"){
    stunde_eins= inputMessage2;
    return stunde_eins;
    }
    else if (inputMessage1 == "S2"){
    stunde_zwei= inputMessage2;
    return stunde_zwei;
    }
    else if (inputMessage1 == "S4"){
    stunde_vier= inputMessage2;
    return stunde_vier;
    }
    else if (inputMessage1 == "S8"){
    stunde_acht= inputMessage2;
    return stunde_acht;
    }

    if (inputMessage1 == "m5"){
    minute_funf= inputMessage2;
    return minute_funf;
    }
    else if (inputMessage1 == "m10"){
    minute_zehn= inputMessage2;
    return minute_zehn;
    }
    else if (inputMessage1 == "m20"){
    minute_zwanzig= inputMessage2;
    return minute_zwanzig;
    }
    else if (inputMessage1 == "m30"){
    minute_dreisig= inputMessage2;
    return minute_dreisig;
    }
}

// function for read state of buttons
String outputState(int output){
  if(digitalRead(output)){
    Serial.print("This Button is on: ");
    Serial.println(output);
    return "checked";
  }
  else {
    Serial.print("This Button is off: ");
    Serial.println(output);
    return "";
  }
}



// wifi
void connect_to_wifi(const char* ssid, const char* password){
  // Connect to Wi-Fi
  WiFi.begin(ssid, password);
  Serial.print("wifi runs on core ");
  Serial.println(xPortGetCoreID());
  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.println("Connecting to WiFi..");
    
  }
// Print ESP32 Local IP Address
  Serial.println(WiFi.localIP());

}




void  server_and_requests(){

Serial.print("server and request runs on core ");
Serial.println(xPortGetCoreID());
//root
 server.on("/", HTTP_GET, [](AsyncWebServerRequest *request){
    request->send(SPIFFS, "/index.html", String(), false, processor);
  });
// json adn css
server.serveStatic("/", SPIFFS, "/");  // send all files of root, used for static files


  // temperature
  server.on("/temperature", HTTP_GET, [](AsyncWebServerRequest *request){
    Serial.print("get /temp runs on core ");
    Serial.println(xPortGetCoreID());
    request->send_P(200, "text/plain", readBME280Temperature().c_str());

  });

  // slider
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

//get button state
server.on("/update", HTTP_GET, [] (AsyncWebServerRequest *request) {
  String inputMessage1;
  String inputMessage2;
  // GET input1 value on <ESP_IP>/update?output=<inputMessage1>&state=<inputMessage2>
  if (request->hasParam(PARAM_INPUT_1) && request->hasParam(PARAM_INPUT_2)) {
    inputMessage1 = request->getParam(PARAM_INPUT_1)->value();
    inputMessage2 = request->getParam(PARAM_INPUT_2)->value();
    //digitalWrite(inputMessage1.toInt(), inputMessage2.toInt());
    write_input_to_bool(inputMessage1,inputMessage2);
  }
  else {
    inputMessage1 = "No message sent";
    inputMessage2 = "No message sent";
  }
  Serial.print("Zeit: ");
  Serial.print(inputMessage1);
  Serial.print(" - Set to: ");
  Serial.println(inputMessage2);
  request->send(200, "text/plain", "OK");
});


// Start server
server.begin();
Serial.println("Server.begin");


// Start SPIFFS
if(!SPIFFS.begin()){
  Serial.println("An Error has occurred while mounting SPIFFS");
  return;
  }
  Serial.println("Filesystem ready");

  File file = SPIFFS.open("/index.html");
  if(!file){
    Serial.println("Failed to open file for reading");
    return;
  }
  else Serial.println("Spiffs opened");

}


void printLocalTime(){
  struct tm timeinfo;
  if(!getLocalTime(&timeinfo)){
    Serial.println("Failed to obtain time");
    return;
  }
  Serial.println(&timeinfo, "%A, %B %d %Y %H:%M:%S");
  Serial.print("Day of week: ");
  Serial.println(&timeinfo, "%A");
  Serial.print("Month: ");
  Serial.println(&timeinfo, "%B");
  Serial.print("Day of Month: ");
  Serial.println(&timeinfo, "%d");
  Serial.print("Year: ");
  Serial.println(&timeinfo, "%Y");
  Serial.print("Hour: ");
  Serial.println(&timeinfo, "%H");
  Serial.print("Hour (12 hour format): ");
  Serial.println(&timeinfo, "%I");
  Serial.print("Minute: ");
  Serial.println(&timeinfo, "%M");
  Serial.print("Second: ");
  Serial.println(&timeinfo, "%S");

  Serial.println("Time variables");
  char timeHour[3];
  strftime(timeHour,3, "%H", &timeinfo);
  Serial.println(timeHour);
  char timeWeekDay[10];
  strftime(timeWeekDay,10, "%A", &timeinfo);
  Serial.println(timeWeekDay);
  Serial.println();
}
