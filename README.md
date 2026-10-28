# MetAEs
Metereological automatic estation 

## I2C Protocol 
 SCL := serial clock Pin
 SDA :=serial data pins
 
https://docs.arduino.cc/learn/communication/wire/


## Libraries

## time / timeLibrary
by michael Margolis
link: [Documentation](https://playground.arduino.cc/Code/Time/)
## Wire.h
https://github.com/czukowski/Wire.h/tree/master

for I2C

## BH1750 
low fracuency irradiance
https://github.com/claws/BH1750
aplication example: https://www.studiopieters.nl/the-complete-guide-to-the-bh1750-digital-light-sensor/

## GUVA s12SD
UV rad
https://github.com/ma2shita/GUVA-S12SD

hay que cambiar el archivo .cpp para arreglar "arduino.h" → <Arduino.h>

## LOG Data OPENLOG
https://www.fredscave.com/interface/int-12openlog-data-logger.html

#### Pins
VCC : Power supply; 3.3V to 12V, preferably 3.3V or 5V.
GND : Ground
TXO : OpenLog's transmit pin. This must be cross connected to the Rx pin on the other device.
RXI : OpenLog's receive pin. This must be cross connected to the Tx pin on the other device.
GRN : Reset pin; when pulled low causes the OpenLog to reset to a state ready to receive data.
BLK : Arduino specific pin; not used on other platforms such as the micro:bit.

#### Led`s

Status 1 LED : Used to display the UART serial activity.

    This LED flashes each time data is transferred between the devices across the UART serial channel.
    If the LED blinks three times on startup it means that the MicroSD card has failed to initialise.
    
Status 2 LED : This LED blinks when the OpenLog is writing its buffer to the MicroSD card. This happens very quickly.

#### The OpenLog has two different user selectable file modes:

    New File Logging
        This mode creates a new file each time OpenLog powers up. The initial file is the LOG00000.txt noted above.
        Each new log file increments the number; LOG00001.txt then LOG00002.txt and so on.
        This logging file mode is the system default but can be changed in the config.txt file by the user - discussed below.
    Append File Logging
        This file creates a file called SEQLOG.txt if not already on the MicroSD card.
        All data from the current session and all the following sessions will be appended to this single file.
        This mode is user selectable by editing the config.txt file - discussed below.

#### Configuration file

The config.txt file created by the OpenLog on its very first power up contains two lines that can be edited with any text editor:

9600,26,3,0,1,1,0
baud,escape,esc#,mode,verb,echo,ignoreRX
            


## Arduino Uno WIFI 
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
