# Preview
This area is for all the code that I have made and tested. I hope this code can help you develop some insight on what the product does.


# Equipments Used
-  [Stacking Header](https://www.adafruit.com/product/2830)
-  [Adafruit Feather M0 Basic Proto - ATSAMD21 Cortex M0](https://www.adafruit.com/product/2772)
-  [Adalogger FeatherWing - RTC + SD Add-on For All Feather Boards](https://www.adafruit.com/product/2922)
-  [SparkFun Triad Spectroscopy Sensor - AS7265x (Qwiic)](https://www.sparkfun.com/products/15050)
-  [Melexis Contact-less Infrared Sensor - MLX90614 3V](https://www.adafruit.com/product/1747)
-  [RGB COLOR SENSOR WITH IR FILTER](https://www.digikey.com/en/products/detail/adafruit-industries-llc/1334/5629426)
-  [TCA9548A I2C Multiplexer](https://www.adafruit.com/product/2717)
-  [Adafruit BME280 I2C or SPI Temperature Humidity Pressure Sensor](https://www.adafruit.com/product/2652)
-  [3.7V 6600mAh Lithium Ion Battery Pack](https://www.adafruit.com/product/353)
-  [CR1220 Coin Battery*](https://www.adafruit.com/product/380)

# How do the 2 codes link?
I am using the UART connection to send and recieve data via the Boron. The Serial interface used is the Serial1. This is used as it is completely unattached to Serial and is usually not affected by it. Usually any Baud Rate is good enough but it is very useful for us to use the 9600 as it allows us to debug the issues. However I have switched to 115200 as soon as I felt that I had enough confidence in my equipment.

# Construction
## Setting up the Feather M0
- Solder the stacking header onto Feather M0 Proto.(Its preferred that you use a breadboard to solder inorder to align them perfectly.)
- Add the Cr1220 button battery to the battery slot in the Adalogger.
- Cut the trace of the SDCS on the Adalogger. (Please check the guide in 1.2)
- Cut and strip a 22 AWG stranded wire and solder it between SDCS pin and 13 pin on the Feather Adalogger, as shown below. Pin 13 is not printed out on the Adalogger, so always double check the pin number on the Feather M0 Proto. 
- Solder the stacking header onto Feather Adalogger now.
## Setting up the Sensors and the Multiplexer
- Solder the pin heads to the RGB sensors and BME280 Environment sensors
- Cut the trace of the Power LED on the Sparkfun Triad sensor. 
- Cut and strip 4 pieces of 20 AWG solid wire, roughly 9 ft (3m) each.
- Separate the 2 pieces of wires using either tape or some heat shrink tube.
- Solder the 4 wires to 3V3, GND, SDA and SCL pins on the triad. (Use the 2 Wires with heat shrink tube on SDA and SCL)
- Solder the Multiplexer to the ProtoPermea Breadboard (Its preffered that you solder the pins on C and G) \footnote{The steps change if you have printed the personalized PCB. See Appendix A}
- Solder 2 very small stripped to Vin and GND and connect them to + and - terminal on the Permea board. Solder 2 more longer wires to the + and - Terminal and connect them to 3V and GND on the Feather M0.
- Solder 3 equally long wired to A0,A1,A2 and connect them to the A0, A1, A2 in the Feather M0.
- Solder 2 stripped wires to SDA and SCL on the Multiplexer and connect them to the SDA and SCL pins on the feather.
- Solder a 12 pin stacking header on the side with 6 SDA and SCL's side. This will be used to connect the sensor pins and multiplexer.
- Solder 2 more stacking headers on the + and - terminals to power the sensors.
- We will now solder the Triad sensors to the PermeaBoard. Solder the SDA and SCL wires to SD0 and SC0/SD1 and SC1. Now Solder the 3V3 and GND pin to + and - respectively.
- Solder some wires to SDA, SCL, 3V/Vin and GND on the sensors. Dont solder the other ends to the PermeaBoard so that we can make it modular. Connect them to the stacking headers.


# Issues Faced
Sometimes the Serial1 would not upload the right values to the Boron. It was due to main 3 reasons:
- The Serial was displaying some outputs and it was taking up some amount of power.
- The connection between RX-TX on the feather and TX-RX on the Boron were not impedance proof.
- The Connection for RX-TX was not connected properly.This is RX of one board connected to TX of the other. 
