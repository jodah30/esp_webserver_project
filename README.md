# Temperature control for  a coffee machine
The old Coffee machines from VBM are beautiful and makes amazing coffee. Unfortunately, the electronics and control are outdated. For challenging myself and learning new stuff, I decide to update the electronics.
![domobar](https://github.com/jodah30/esp_webserver_project/blob/main/pictures/$_59.JPG)

Using microcontroller for precise temperature control on a 30 years old Domobar Inox with useless feature like Wi-Fi, a webpage in the local network for monitoring and controlling


## Hardware
<img src='https://github.com/jodah30/esp_webserver_project/blob/main/pictures/IMG_3111.JPG' width = '500'/>

1. Esp32
2. Measuring Amplifier MAX 31865
3. PT100
4. Solid-State-Relay
5. OLED Display SSD1306
   - actual value
   - target value
   - water level
<img src='https://github.com/jodah30/esp_webserver_project/blob/main/pictures/IMG_3108.JPG' width = '500'/>
6. Modified VDO fuel tank sensor for water level
<img src='https://github.com/jodah30/esp_webserver_project/blob/main/pictures/IMG_3110.JPG' width = '500'/>





 ## Added Features 

1. PID proportional–integral–derivative controller for temperature control
2. PT100 Sensor
3. Water level
4. Asynchronous web interface
5. Visualized water level in CSS picture, blue rectangle represents water level
6. Using both core of the ESP32. One for temperature/controlling, one for the webpage

 <p>           
<img src='https://github.com/jodah30/esp_webserver_project/blob/main/pictures/IMG_7126.PNG' width = '400'/>  
<img src='https://github.com/jodah30/esp_webserver_project/blob/main/pictures/IMG_7127.PNG' width = '400'/>
 </p>   
 
6.Slider for target temperature


7.Chart for temperature


<img src='https://github.com/jodah30/esp_webserver_project/blob/main/pictures/IMG_7130.PNG' width = '500'/>

8.Time over NTP

9.Wake-up timer

<img src='https://github.com/jodah30/esp_webserver_project/blob/main/pictures/IMG_7131.PNG' width = '500'/>










Shout-out to https://randomnerdtutorials.com/, https://www.youtube.com/c/AndreasSpiess, https://lenadesign.org/2020/04/27/css-coffee-express-animation/ and the amazing open source community for sharing their stuff and knowledge!!
Thanks Timm for the cinematic picture
