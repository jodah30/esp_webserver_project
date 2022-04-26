




void bollsinZeit3(){
  if( stunde_eins == 0 && stunde_zwei == 0 && stunde_vier == 0 && stunde_acht == 0){
              sollZeitH=0;
              sollZeitMin=0;
              Serial.println("no timer is set");
              Serial.print( sollZeitH);
              Serial.print(":");
              Serial.println(sollZeitMin);
              }
else{

  sollZeitH=(stunde_eins+(stunde_zwei*2)+(stunde_vier*4)+(stunde_acht*8));
  sollZeitMin=((minute_funf*5)+(minute_zehn*10)+(minute_zwanzig*20)+(minute_dreisig*30));
    if(sollZeitMin>=60){
      sollZeitH+=1;
      sollZeitMin-=60;
    }

  Serial.print("Timer is set to: ");
  Serial.print( sollZeitH);
  Serial.print(":");
  Serial.println(sollZeitMin);
  }

}














//   || minute_funf == 1 || minute_zehn == 1 || minute_zwanzig == 1 || minute_dreisig == 1){
//
//       struct tm timeinfo;
//       if(!getLocalTime(&timeinfo)){
//       Serial.println("Failed to obtain time");
//       return;
//
//       if(stunde_eins==1 && stunde_zwei && stunde_acht && timeinfo.tm_hour== 7){
//         POWER==0;
//       }
//
//
//   }
// else
// }
