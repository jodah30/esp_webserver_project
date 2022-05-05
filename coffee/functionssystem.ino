
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


      long time1=0;
      long time2=0;
      long time3=0;
      long time4=0;
      long debounce =100;

      button_hot_pin_new=digitalRead(button_hot_pin);
      button_pump_pin_new=digitalRead(button_pump_pin);
      button_hebel_pin_new=digitalRead(button_hebel_pin);
      button_power_pin_new=digitalRead(button_power_pin);

      if(button_hot_pin_new==1 && button_hot_pin_old==0 && millis() - time1 > debounce){
        button_hot_status   =! button_hot_status;
        time1 = millis();
      }
      button_hot_pin_old=button_hot_pin_new;

      if(button_power_pin_new==1 && button_power_pin_old==0 && millis() - time2 > debounce){
        button_power_status   =! button_power_status;
        time2 = millis();
      }
      button_power_pin_old=button_power_pin_new;

      if(button_hebel_pin_new==1 && button_hebel_pin_old==0 && millis() - time3 > debounce){
        button_hebel_status   =! button_hebel_status;
        time3 = millis();
      }
      button_hebel_pin_old=button_hebel_pin_new;

      if(button_pump_pin_new==1 && button_pump_pin_old==0 && millis() - time4 > debounce){
        button_pump_status   =! button_pump_status;
        time4 = millis();
      }
      button_pump_pin_old=button_pump_pin_new;
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
