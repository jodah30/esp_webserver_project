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
    }

    //SYSTEM



  }
}
