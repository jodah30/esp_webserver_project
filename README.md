# Temperatur control for  a coffee maschine
The old Coffeemaschines from VBM are beatiful and makes amazing coffee. Unfortunately the electronics and control are outdated. For challenging myself and learning new stuff i decide to update the electronics.
![domobar](https://github.com/jodah30/esp_webserver_project/blob/main/pictures/$_59.JPG)

Using microcontroler for precised temperature control on an 30years old Domobar Inox with useless feature like a webpage in the local network for monitorung and controling
-PID controller

## Hardware
<img src='https://github.com/jodah30/esp_webserver_project/blob/main/pictures/IMG_3111.JPG' width = '500'/>

1. Esp32
2. Measuring Amplifier MAX 31865
3. PT100
4. Solid-State-Relay
5. OLED Display SSD1306
   - actual value
   - target value
   - waterlevel
<img src='https://github.com/jodah30/esp_webserver_project/blob/main/pictures/IMG_3108.JPG' width = '500'/>
7. Modified VDO Fueltank Sensor for waterlevel
<img src='https://github.com/jodah30/esp_webserver_project/blob/main/pictures/IMG_3110.JPG' width = '500'/>





 ## Added Features 

1. PID proportional–integral–derivative controller for temperature Controll
2. PT100 Sensor
3. Waterlevel
4. Webinterface
5. Visualized water level in CSS Picture
      blue rectangle is actual water level

 <p>           
<img src='https://github.com/jodah30/esp_webserver_project/blob/main/pictures/IMG_7126.PNG' width = '400'/>  
<img src='https://github.com/jodah30/esp_webserver_project/blob/main/pictures/IMG_7127.PNG' width = '400'/>
 </p>   
 
6.Slider for target temperature

7.Wakeup timer

<img src='https://github.com/jodah30/esp_webserver_project/blob/main/pictures/IMG_7131.PNG' width = '500'/>

7. Time over NTP

9.Chart for Temperature

<img src='https://github.com/jodah30/esp_webserver_project/blob/main/pictures/IMG_7130.PNG' width = '500'/>






shout-out to to https://randomnerdtutorials.com/, https://www.youtube.com/c/AndreasSpiess, https://lenadesign.org/2020/04/27/css-coffee-express-animation/ and the amazing open spurce community for sharing there stuff and knowledge
