void codeForCore0( void * parameter )
{
for (;;){
    delay(30000);
    printLocalTime();
    Serial.print("Core 0 now read the temp");
    Serial.println(readBME280Temperature());



  }



}
