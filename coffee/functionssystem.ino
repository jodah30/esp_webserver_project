
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



//read the state from the Buttons and asign to the bools
void button_status(){
      boolean button_hot_pin_new;
      boolean button_hot_pin_old;

      long time=0;
      long debounce =200;

      button_hot_pin_new=digitalRead(button_hot_pin);
      Serial.print("button_hot_pin_new:");
      Serial.println(button_hot_pin_new);
      Serial.print("button_hot_pin_old:");
      Serial.println(button_hot_pin_old);

      if(button_hot_pin_new==1 && button_hot_pin_old==0 && millis() - time > debounce){
        button_hot_status   =! button_hot_status;
        Serial.println("button_hot_status has changed");
        time = millis();
      }
      button_hot_pin_old=button_hot_pin_new;

      if(digitalRead(button_pump_pin)){
        button_pump_status  =! button_pump_status;
        Serial.println("button_pump_status has changed");
      }
      else if(digitalRead(button_hebel_pin)){
       button_hebel_status  =! button_hebel_status;
       Serial.println("button_hebel_status has changed");
      }
      else if(digitalRead(button_power_pin)){
       button_power_status  =! button_power_status;
       Serial.println("button_power_status has changed");
      }
}

int read_waterlevel(){

    analog_waterlevel=analogRead(waterlevel_pin);
      if(analog_waterlevel>= analog_waterlevel_max){
        analog_waterlevel_max=analog_waterlevel;
      }
      else if(analog_waterlevel<= analog_waterlevel_min){
        analog_waterlevel_min=analog_waterlevel;
      }
    digital_waterlevel=map(analog_waterlevel,analog_waterlevel_min,analog_waterlevel_max,0,31);
    return digital_waterlevel;
}
