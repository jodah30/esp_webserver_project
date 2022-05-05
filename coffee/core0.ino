void codeForCore0( void * parameter )
{
  for (;;){
    delay(1);
    unsigned long currentMillis = millis();

    if(currentMillis - previousMillisprintT >= intervalprintT){
      printLocalTime();
      Serial.println(WiFi.status());
      bollsinZeit3();
      previousMillisprintT=currentMillis;
      //testscrolltext();
      display_test();


    }
    delay(1);



    //SYSTEM
   button_status();


  //  idle
    if(button_pump_status == LOW && button_hot_status == LOW && button_hebel_pin == LOW) {

      // Soll

      digitalWrite(relay_pump_pin, HIGH); //reversed logic
      Setpoint = Standart;
      digitalWrite(led_hot_pin, LOW);
      digitalWrite(led_pump_pin, LOW);
      //Display Normal
      //display_when_idle();
      // Für Timer
      idle_millis=millis();
      //Zähler für Kaffee
   }
    //brew_coffee




  }
}
