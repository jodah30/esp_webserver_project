void codeForCore1( void * parameter )
{

  //call wifi function and password
  connect_to_wifi(ssid, callpassword());
  //call  server function
  server_and_requests();
  //define ntp and Setup
  configTime(gmtOffset_sec, daylightOffset_sec, ntpServer);
  //display_for_timer();


for (;;){
  //WIFI
  previousMillisWifi = WiFireconnect(previousMillisWifi);
  delay(1);

  }
}
