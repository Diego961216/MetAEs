# MetAEs
Metereological automatic estation 

##Libraries

time / timeLibrary
by michael Margolis
link: [Documentation](https://playground.arduino.cc/Code/Time/)

#Arduino Uno WIFI 
Atmega328p
wifi  ESP8266 + 8 Mb 

driver para USB
usb TTL CH340G


CODIGO DE USOS CHIP 	
https://forum.arduino.cc/t/atmega328p-esp8266-wifi-tutorial/944380

Dip Switches
Communication mode is set using the dip switches as follows:
ATmega <-> ESP8266 1100000
USB <-> ATmega 0011000
USB <-> ESP8266 0000111 (Update firmware or sketch)
USB <-> ESP8266 0000110
All independent 0000000

Upload ESP8266
pin 5,6,7 On 

Use ESP8266
only 5,6 On

Al usar ESP8266 
Now, before uploading anything you have to reset the board with the red reset button before pressing upload in the IDE. After you upload your code I believe you have to put dip-switch 7 to OFF so that your sketch remains after rebooting the board.


librería
https://github.com/esp8266/Arduino/blob/master/libraries/ESP8266WiFi/examples/WiFiClient/WiFiClient.ino

gestor de placa:
https://arduino.esp8266.com/stable/package_esp8266com_index.json

(archivo, preferencias), luego intalar libreria esp8266 comunity
