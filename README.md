![github-small](/Images/Handheld_16-9.jpg)   

# WiFi Signal Strength Checker
 Simple tool to check the WiFi signal strength at your office or home.    

## Parts required   
Markup : 1. NodeMCU or Wemos D1 Mini    
            Purchase links:    
              Amazon
              1. US: https://amzn.to/3vk56Ln   
              2. UK: https://amzn.to/3rPuMgW     
              3. Spain: https://amzn.to/3bGlHBf    
              4. Italy: https://amzn.to/3qKnnhm   
              5. Germany: https://amzn.to/3lcHyn0       
              6. India: https://amzn.to/3cxXKey   
              Ebay  
              https://ebay.us/hu7zJM    
              https://ebay.us/yhG7Da     
              https://ebay.us/loeNEr     
              https://ebay.us/JF5QYD      

          2. SSD1306 OLED Display   
          Purchase links:    
            Amazon
            1. US: https://amzn.to/3qKK0lU  
            2. UK: https://amzn.to/30FgqU6     
            3. Spain: https://amzn.to/3bK4Ttf    
            4. Italy: https://amzn.to/3rNfuce   
            5. Germany: https://amzn.to/3tib8dD          
            6. India: https://amzn.to/2OudLdB       
            Ebay  
            https://ebay.us/VkHi7j     
            https://ebay.us/F2lqOy        
            https://ebay.us/9swiZ4   

          3. PCB   
          Purchase links:    
            Amazon
            1. US: https://amzn.to/3ey6UKR     
            2. UK: https://amzn.to/3rHkrU2        
            3. Spain: https://amzn.to/3rG5uBH       
            4. Italy: https://amzn.to/3bJKJiX      
            5. Germany: https://amzn.to/3tmsUfX             
            6. India: https://amzn.to/3llFfOz           
            Ebay  
            https://ebay.us/ZmFTcu          

          4. USB to Micro USB Mini adapter  
          Purchase links:
          Amazon
          1. US: https://amzn.to/3tha4H4        
          2. UK: https://amzn.to/3bI4Q12           
          3. Spain: https://amzn.to/3tjUbzI          
          4. Italy: https://amzn.to/3lmz2SE https://amzn.to/3rP5y1W      
          5. Germany: https://amzn.to/38zQa28 https://amzn.to/30Gf4IV                 
          6. India: https://amzn.to/3qLvCKj              
          Ebay  
          https://ebay.us/r8BBUG   
          https://ebay.us/tnmWOc  
          https://ebay.us/jLesSJ       

          5. Portable power bank   
          6. Header Pins    
          7. Wires   
          8. Soldering iron   
          9. Lead-free solder    
          10. Soldering flux     

## PCB Wiring   
The easy way out and to save hassles of soldering, you could probably use the Wemos's OLED Display addon. But the addon screen is just 0.66". There are larger displays availble, but you need to get your hands dirty and make the connections. The Wemos D1 Mini - OLED Display wiring is shown below. In the diagram below, the display's SCL pin is connected to Wemos's D1 pin, display's SDA pin is connected to Wemos's D2 pin, display's ground to Wemos's ground and display's Vcc to Wemos's 3.3V pin. Just in case you wish to make a single PCB of the Wemos and the display, you can design the PCB in Fritzing and get the PCBs printed from https://jlcpcb.com.   

![github-small](/Images/Wemos_SSD1306_Wiring.jpg)      

## Getting the I2C Address     
After putting all the parts together, the Wemos or the NodeMCU is ready to be programmed. Most of the SSD1306 I2C OLED displays have the default address set to ```0x3c```. Just to double check, I would suggest you to run an I2C address scan. My library suggestion is the "i2cdetect" by [Mike Causer](https://github.com/mcauser). ![github-small](/Images/I2C_Scanner_Library.jpg). Use the ![i2cdetect example](/Images/I2C_Detect_Example.jpg) to check for the OLED's address. After uploading the sketch, open the serial monitor and set the baud rate to the value given in the code to see the ![detected address](Serial_Monitor_I2C_Detect.jpg)

## SSD1306 Library     
There are a number of different libraries for the SSD1306 based chipset. The one that I have used is the ["ESP8266 and ESP32 OLED driver for SSD1306 displays"](https://github.com/ThingPulse/esp8266-oled-ssd1306). [This library](/Images/SSD1306_Library.jpg) works great.   

## Arduino Code   
In the arduino code set your WiFi credentials    
```
char wifissid[] = "ENTER YOUR WiFi SSID HERE";    
char wifipass[] = "ENTER YOUR WiFi PASSWORD HERE";    
```     

Normally, the signal strength is displayed in dBm. But for a non techie person, the signal strength in terms of % would appeal more. Catering to people from both the spectrum, the program is set to display the signal values in both dBm and %. The dBm scale in non-linear or otherwise logarithmic. I have used values from this [article](https://www.intuitibits.com/2016/03/23/dbm-to-percent-conversion/) in this program. I made some quick calculations and indeed this is the closest representation that you can get.   

Set your display's address and the pins used if it is different from the one given in the code.  
```    
SSD1306  display(0x3c, D2, D1);    
```    
It follows the format   
```   
SSD1306 display(Address of Display, SDA_PIN, SCL_PIN)  
```   

Based on the orientation of the display, you can either comment out or retain the command to flip the display.   
```   
display.flipScreenVertically()    
```    

## Demo   
Checkout the following video to see the device in action.   
