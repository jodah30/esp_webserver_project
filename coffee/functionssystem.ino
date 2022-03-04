

// int, int returntime(){
//   struct tm timeinfo;
//     if(!getLocalTime(&timeinfo)){
//     Serial.println("Failed to obtain time");
//     return;
//   }
//   ZeitH ==
//
//       struct tm timeinfo;
//       if(!getLocalTime(&timeinfo)){
//         Serial.println("Failed to obtain time");
//         return;
//       }
//       ZeitH==timeinfo.tm_hour;
//       Serial.print("hier kommt der versuch: ");
//       Serial.println(ZeitH);
//
//
//
// }

void bollsinZeit(){


if( stunde_eins == 1 || stunde_zwei == 1 || stunde_vier == 1 || stunde_acht == 1){

  if( stunde_eins == 1 && stunde_zwei == 0 && stunde_vier == 0 && stunde_acht == 0){sollZeitH =1;}
  else if( stunde_eins == 0 && stunde_zwei == 1 && stunde_vier == 0 && stunde_acht == 0){sollZeitH =2;}
  else if( stunde_eins == 1 && stunde_zwei == 1 && stunde_vier == 0 && stunde_acht == 0){sollZeitH =3;}
  else if( stunde_eins == 0 && stunde_zwei == 0 && stunde_vier == 1 && stunde_acht == 0){sollZeitH =4;}
  else if( stunde_eins == 1 && stunde_zwei == 0 && stunde_vier == 1 && stunde_acht == 0){sollZeitH =5;}
  else if( stunde_eins == 0 && stunde_zwei == 1 && stunde_vier == 1 && stunde_acht == 0){sollZeitH =6;}
  else if( stunde_eins == 1 && stunde_zwei == 1 && stunde_vier == 1 && stunde_acht == 0){sollZeitH =7;}
  else if( stunde_eins == 0 && stunde_zwei == 0 && stunde_vier == 0 && stunde_acht == 1){sollZeitH =8;}
  else if( stunde_eins == 1 && stunde_zwei == 0 && stunde_vier == 0 && stunde_acht == 1){sollZeitH =9;}
  else if( stunde_eins == 0 && stunde_zwei == 1 && stunde_vier == 0 && stunde_acht == 1){sollZeitH =10;}
  else if( stunde_eins == 1 && stunde_zwei == 1 && stunde_vier == 0 && stunde_acht == 1){sollZeitH =11;}
  else if( stunde_eins == 0 && stunde_zwei == 0 && stunde_vier == 1 && stunde_acht == 1){sollZeitH =12;}
  else if( stunde_eins == 1 && stunde_zwei == 0 && stunde_vier == 1 && stunde_acht == 1){sollZeitH =13;}
  else if( stunde_eins == 0 && stunde_zwei == 1 && stunde_vier == 1 && stunde_acht == 1){sollZeitH =14;}
  else {sollZeitH =15;}
  //if( stunde_eins == 1 && stunde_zwei == 1 && stunde_vier == 1 && stunde_acht == 1)


  if( minute_funf == 0 && minute_zehn == 0 && minute_zwanzig == 0 && minute_dreisig == 0){sollZeitMin =0;}
  else if( minute_funf == 1 && minute_zehn == 0 && minute_zwanzig == 0 && minute_dreisig == 0){sollZeitMin =5;}
  else if( minute_funf == 0 && minute_zehn == 1 && minute_zwanzig == 0 && minute_dreisig == 0){sollZeitMin =10;}
  else if( minute_funf == 1 && minute_zehn == 1 && minute_zwanzig == 0 && minute_dreisig == 0){sollZeitMin =15;}
  else if( minute_funf == 0 && minute_zehn == 0 && minute_zwanzig == 1 && minute_dreisig == 0){sollZeitMin =20;}
  else if( minute_funf == 1 && minute_zehn == 0 && minute_zwanzig == 1 && minute_dreisig == 0){sollZeitMin =25;}
  else if( minute_funf == 0 && minute_zehn == 1 && minute_zwanzig == 1 && minute_dreisig == 0){sollZeitMin =30;}
  else if( minute_funf == 1 && minute_zehn == 1 && minute_zwanzig == 1 && minute_dreisig == 0){sollZeitMin =35;}
  else if( minute_funf == 0 && minute_zehn == 0 && minute_zwanzig == 0 && minute_dreisig == 1){sollZeitMin =30;}
  else if( minute_funf == 1 && minute_zehn == 0 && minute_zwanzig == 0 && minute_dreisig == 1){sollZeitMin =35;}
  else if( minute_funf == 0 && minute_zehn == 1 && minute_zwanzig == 0 && minute_dreisig == 1){sollZeitMin =40;}
  else if( minute_funf == 1 && minute_zehn == 1 && minute_zwanzig == 0 && minute_dreisig == 1){sollZeitMin =45;}
  else if( minute_funf == 0 && minute_zehn == 0 && minute_zwanzig == 1 && minute_dreisig == 1){sollZeitMin =50;}
  else if( minute_funf == 1 && minute_zehn == 0 && minute_zwanzig == 1 && minute_dreisig == 1){sollZeitMin =55;}
  else if( minute_funf == 0 && minute_zehn == 1 && minute_zwanzig == 1 && minute_dreisig == 1){sollZeitMin =0;sollZeitH += 1;}
  else if( minute_funf == 1 && minute_zehn == 1 && minute_zwanzig == 1 && minute_dreisig == 1){sollZeitMin =5;sollZeitH += 1;}

    Serial.print("Die Zeit ist gesetzt auf: ");
    Serial.print( sollZeitH);
    Serial.print(":");
    Serial.println(sollZeitMin);
  }
  else{
    sollZeit
    Serial.println("no timer is set");
  }
}

void bollsinZeit2(){


if( stunde_eins == 1 || stunde_zwei == 1 || stunde_vier == 1 || stunde_acht == 1){

  if( stunde_eins == 1 && stunde_zwei == 0 && stunde_vier == 0 && stunde_acht == 0){sollZeitH =1;}
  else if( stunde_eins == 0 && stunde_zwei == 1 && stunde_vier == 0 && stunde_acht == 0){sollZeitH =2;}
  else if( stunde_eins == 1 && stunde_zwei == 1 && stunde_vier == 0 && stunde_acht == 0){sollZeitH =3;}
  else if( stunde_eins == 0 && stunde_zwei == 0 && stunde_vier == 1 && stunde_acht == 0){sollZeitH =4;}
  else if( stunde_eins == 1 && stunde_zwei == 0 && stunde_vier == 1 && stunde_acht == 0){sollZeitH =5;}
  else if( stunde_eins == 0 && stunde_zwei == 1 && stunde_vier == 1 && stunde_acht == 0){sollZeitH =6;}
  else if( stunde_eins == 1 && stunde_zwei == 1 && stunde_vier == 1 && stunde_acht == 0){sollZeitH =7;}
  else if( stunde_eins == 0 && stunde_zwei == 0 && stunde_vier == 0 && stunde_acht == 1){sollZeitH =8;}
  else if( stunde_eins == 1 && stunde_zwei == 0 && stunde_vier == 0 && stunde_acht == 1){sollZeitH =9;}
  else if( stunde_eins == 0 && stunde_zwei == 1 && stunde_vier == 0 && stunde_acht == 1){sollZeitH =10;}
  else if( stunde_eins == 1 && stunde_zwei == 1 && stunde_vier == 0 && stunde_acht == 1){sollZeitH =11;}
  else if( stunde_eins == 0 && stunde_zwei == 0 && stunde_vier == 1 && stunde_acht == 1){sollZeitH =12;}
  else if( stunde_eins == 1 && stunde_zwei == 0 && stunde_vier == 1 && stunde_acht == 1){sollZeitH =13;}
  else if( stunde_eins == 0 && stunde_zwei == 1 && stunde_vier == 1 && stunde_acht == 1){sollZeitH =14;}
  else {sollZeitH =15;}
  //if( stunde_eins == 1 && stunde_zwei == 1 && stunde_vier == 1 && stunde_acht == 1)


  if( minute_funf == 0 && minute_zehn == 0 && minute_zwanzig == 0 && minute_dreisig == 0){sollZeitMin =0;}
  else if( minute_funf == 1 && minute_zehn == 0 && minute_zwanzig == 0 && minute_dreisig == 0){sollZeitMin =5;}
  else if( minute_funf == 0 && minute_zehn == 1 && minute_zwanzig == 0 && minute_dreisig == 0){sollZeitMin =10;}
  else if( minute_funf == 1 && minute_zehn == 1 && minute_zwanzig == 0 && minute_dreisig == 0){sollZeitMin =15;}
  else if( minute_funf == 0 && minute_zehn == 0 && minute_zwanzig == 1 && minute_dreisig == 0){sollZeitMin =20;}
  else if( minute_funf == 1 && minute_zehn == 0 && minute_zwanzig == 1 && minute_dreisig == 0){sollZeitMin =25;}
  else if( minute_funf == 0 && minute_zehn == 1 && minute_zwanzig == 1 && minute_dreisig == 0){sollZeitMin =30;}
  else if( minute_funf == 1 && minute_zehn == 1 && minute_zwanzig == 1 && minute_dreisig == 0){sollZeitMin =35;}
  else if( minute_funf == 0 && minute_zehn == 0 && minute_zwanzig == 0 && minute_dreisig == 1){sollZeitMin =30;}
  else if( minute_funf == 1 && minute_zehn == 0 && minute_zwanzig == 0 && minute_dreisig == 1){sollZeitMin =35;}
  else if( minute_funf == 0 && minute_zehn == 1 && minute_zwanzig == 0 && minute_dreisig == 1){sollZeitMin =40;}
  else if( minute_funf == 1 && minute_zehn == 1 && minute_zwanzig == 0 && minute_dreisig == 1){sollZeitMin =45;}
  else if( minute_funf == 0 && minute_zehn == 0 && minute_zwanzig == 1 && minute_dreisig == 1){sollZeitMin =50;}
  else if( minute_funf == 1 && minute_zehn == 0 && minute_zwanzig == 1 && minute_dreisig == 1){sollZeitMin =55;}
  else if( minute_funf == 0 && minute_zehn == 1 && minute_zwanzig == 1 && minute_dreisig == 1){sollZeitMin =0;sollZeitH += 1;}
  else if( minute_funf == 1 && minute_zehn == 1 && minute_zwanzig == 1 && minute_dreisig == 1){sollZeitMin =5;sollZeitH += 1;}

    Serial.print("Die Zeit ist gesetzt auf: ");
    Serial.print( sollZeitH);
    Serial.print(":");
    Serial.println(sollZeitMin);
  }
  else{
    sollZeit
    Serial.println("no timer is set");
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
