void codeForCore0( void * parameter )
{
for (;;){
    delay(1);
    unsigned long currentMillis = millis();

    if(currentMillis - previousMillisprintT >= intervalprintT){
    printLocalTime();
    Serial.println("Core 0 now read the temp");
    Serial.println(readBME280Temperature());
    Serial.println(WiFi.status());
    bollsinZeit3();
    previousMillisprintT=currentMillis;
    }

    // if(currentMillis - previousMillisWifi >= intervalWifi){
    //
    // Serial.println(WiFi.status());
    // previousMillisWifi=currentMillis;
    // }



  }
}
