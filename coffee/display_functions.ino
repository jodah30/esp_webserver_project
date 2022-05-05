void display_when_idle(){
  string_temperature = String(Input,1);
  string_setpoint = String(Setpoint ,1);
  string_power = String(Output/2.55,0);

  display.clearDisplay();
  display.setTextSize(1);
  display.setCursor(80,0);
  display.println(T);
  display.setCursor(110,0);
  display.println("C");
  display.drawPixel(107,0,1);
  display.drawPixel(107,1,1);
  display.drawPixel(108,0,1);
  display.drawPixel(108,1,1);

  display.setCursor(80,8);
  display.println(S);
  display.setCursor(110,8);
  display.println("C");
  display.drawPixel(107,8,1);
  display.drawPixel(107,9,1);
  display.drawPixel(108,8,1);
  display.drawPixel(108,9,1);

  display.setCursor(80, 16);
  display.println(P);
  display.setCursor(110,16);
  display.println("%");

  //Wasserstand

  display.drawRect(80,24,35,8,1);
  display.fillRect(82,26,digital_waterlevel,4,1);
  // display.setCursor(80,24);
  // display.println("Sensor!");
  display.display();
}

void display_for_timer(){
  String brew_time;
  display.clearDisplay();
  display.setTextSize(1);
  display.setCursor(83,0);
  display.println("Time");
  display.drawLine(83,8,107,8,1);
  display.setTextSize(2);
  display.setTextColor(WHITE);

  brew_time=String(millis()-idle_millis/1000,0);
  if(millis()-idle_millis<=9000) {
    display.setCursor(78,13);
    display.println(brew_time);
    display.display();
  }
  else{
    display.setCursor(83,13);
    display.println(brew_time);
    display.display();
  }


                                       // if(Zeit>=20000)  {
                                       //
                                       //   Kaffee= HIGH;
                                       //   digitalWrite(Lpower,HIGH);
                                       //   display.drawLine(83,30,107,30,1);
                                       //   display.display();
                                       // }


}



void display_test(){
  display.clearDisplay();
  display.setTextSize(1);
  display.setTextColor(SSD1306_WHITE);

  display.setCursor(0,0);
  display.println(button_hot_pin);
  display.setCursor(40,0);
  display.println(button_hot_status);
  display.setCursor(0,10);
  display.println(button_power_pin);
  display.setCursor(40,10);
  display.println(button_power_status);
  display.setCursor(0,20);
  display.println(button_hebel_pin);
  display.setCursor(40,20);
  display.println(button_hebel_status);
  display.setCursor(0,30);
  display.println(button_pump_pin);
  display.setCursor(40,30);
  display.println(button_pump_status);
  delay(1);
  display.display();
  delay(1);
}

void testdrawrect(void) {
  display.clearDisplay();

  for(int16_t i=0; i<display.height()/2; i+=2) {
    display.drawRect(i, i, display.width()-2*i, display.height()-2*i, SSD1306_WHITE);
    display.display(); // Update screen with each newly-drawn rectangle
    delay(1);
  }
  delay(2000);
}

void testscrolltext(void) {
  display.clearDisplay();

  display.setTextSize(2); // Draw 2X-scale text
  display.setTextColor(SSD1306_WHITE);
  display.setCursor(10, 0);
  display.println(F("scroll"));
  display.display();      // Show initial text
  delay(100);

  // Scroll in various directions, pausing in-between:
  display.startscrollright(0x00, 0x0F);
  delay(2000);
  display.stopscroll();
  delay(1000);
  display.startscrollleft(0x00, 0x0F);
  delay(2000);
  display.stopscroll();
  delay(1000);
  display.startscrolldiagright(0x00, 0x07);
  delay(2000);
  display.startscrolldiagleft(0x00, 0x07);
  delay(2000);
  display.stopscroll();
  delay(1000);
}
