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



# Code
## Setup
We are going to setup the code and the libraries in the IDE. Please make sure that you have downloaded the libraries that have been specified in Preamble 1.2. Now we will initialize the libraries. Now each and every sensor has a specified struct and constructor which is expected to be called before using. Since our goal is not just to save the data but to also use it for future we want to make sure that we know which all sensors is it using and at which multiplexer select is it at, we are going to use predefined char array of an optimal length. \newline
Now in the void Setup() loop we will create the testing conditions where, we can test to see if the sensors are responding and what are its I2C values. This part is not really important but can be used for debugging mainly. In the setup we will begin the Wire and Serial library first and foremost, then we see if the SD card is inserted or not and if we can open the filename in the SD card. Now we iterate through the TCAselect from the Multiplexer to see if there is a sensor and if the sensor is found then we look for its I2C to confirm the type of the sensor and save it in an array to be used in the loop().
### Psuedocode:

## Triad Sensor
We are going to use the Sparkfun AS7265X library for the Triad sensor. The data is collected in 18 different string values (even if they are actually floating numbers.). We will have to define the sensor name. Now we for everytime we take a measurement we will have to go like "\textit{sensor}.takeMeasurements()". This takes the measurements from the sensors and stores it in a heap, now to pop the values of the heap we will call the getcalibrated\textbf{X}() function where \textbf{X} denotes the letters and its wavelength corresponding to it.

        \hline
        Letter & Wavelength & Color (Hex) \\[0.5ex]
        \hline\hline
        A & 410nm & \#7e00db \\
        \hline
        B & 435nm & \#2300ff \\
        \hline
        C & 460nm & \#007bff \\
        \hline        
        D & 485nm & \#00eaff \\
        \hline
        E & 510nm & \#00ff00 \\
        \hline
        F & 535nm & \#70ff00 \\
        \hline
        G & 560nm & \#c3ff00 \\
        \hline
        H & 585nm & \#ffef00 \\
        \hline
        R & 610nm & \#ff9b00 \\
        \hline
        I & 645nm & \#ff0000 \\
        \hline
        S & 680nm & \#cc0000 \\
        \hline
        J & 705nm & \#c90000 \\
        \hline
        T & 730nm & \#990000 \\
        \hline
        U & 760nm & \#940000 \\
        \hline
        V & 810nm & Infrared \\
        \hline
        W & 860nm & Infrared \\
        \hline
        K & 900nm & Infrared \\
        \hline
        L & 940nm & Infrared \\
        \hline       

Once we have saved this value in a string we have to go through a few more steps like converting the string into a char and then into an array of char and saving it in the data variables.
### Psuedocode:

```
void triad(int sel){
  tcaselect(sel);
  //digitalWrite(13, HIGH);

  sensor.takeMeasurements();
  
  String  a = String(sensor.getCalibratedA(), 2);
  String b = String(sensor.getCalibratedB(), 2);
  String c = String(sensor.getCalibratedC(), 2);
  String d = String(sensor.getCalibratedD(), 2);
  String e = String(sensor.getCalibratedE(), 2);
  String f = String(sensor.getCalibratedF(), 2);

  String g = String(sensor.getCalibratedG(), 2);
  String h = String(sensor.getCalibratedH(), 2);
  String i = String(sensor.getCalibratedR(), 2);
  String j = String(sensor.getCalibratedI(), 2);
  String k = String(sensor.getCalibratedS(), 2);
  String l = String(sensor.getCalibratedJ(), 2);

  String m = String(sensor.getCalibratedT(), 2);
  String n = String(sensor.getCalibratedU(), 2);
  String o = String(sensor.getCalibratedV(), 2);
  String p = String(sensor.getCalibratedW(), 2);
  String q = String(sensor.getCalibratedK(), 2);
  String r = String(sensor.getCalibratedL(), 2);
  
  char A[9]; char B[9]; char C[9]; char D[9]; char E[9]; char F[9];
  char G[9]; char H[9]; char I[9]; char J[9]; char K[9]; char L[9];
  char M[9]; char N[9]; char O[9]; char P[9]; char Q[9]; char R[9];
  
  a.toCharArray(A, 9); b.toCharArray(B, 9); c.toCharArray(C, 9); d.toCharArray(D, 9); e.toCharArray(E, 9); f.toCharArray(F, 9);
  g.toCharArray(G, 9); h.toCharArray(H, 9); i.toCharArray(I, 9); j.toCharArray(J, 9); k.toCharArray(K, 9); l.toCharArray(L, 9);
  m.toCharArray(M, 9); n.toCharArray(N, 9); o.toCharArray(O, 9); p.toCharArray(P, 9); q.toCharArray(Q, 9); r.toCharArray(R, 9);
  //IMPORTANT
  //edit this line every time you build a new sensor
  sprintf(dat0, "Triad, UP, SEN%u,%9s,%9s,%9s,%9s,%9s,%9s,%9s,%9s,%9s,%9s,%9s,%9s,%9s,%9s,%9s,%9s,%9s,%9s\n",/* now.year(), now.month(), now.day(), now.hour(), now.minute(), now.second(), now.unixtime(),*/sel, A, B, C, D, E, F, G, H, I, J, K, L, M, N, O, P, Q, R);
  /*%04d/%02d/%02d,%02d:%02d:%02d,%010d,*/
  
  //Serial.println(sizeof(dat0));
  Serial.print(dat0);
  logfile.print(dat0);
}
```

## RGB Sensor
For the RGB sensor we are using the TCS34725 Library. When creating the constructor we are going to allot a gain and integration time too. The values from the sensor are saved as a "uint16\_t", however the Cpp doesn't support it like C used to do, so we have to convert these into int or float values.
### Psuedocode:
## Thermal sensor
The thermal sensor uses the MLX90614 library. The data is saved as a double value. The sensor can take both the object temperature and the ambient temperature. 
### Psuedocode
## Environment Sensor
The environment sensor is the sensor which is used to measure pressure, altitude, humidty and temperature. 
### Psuedocode



# Issues Faced
Sometimes the Serial1 would not upload the right values to the Boron. It was due to main 3 reasons:
- The Serial was displaying some outputs and it was taking up some amount of power.
- The connection between RX-TX on the feather and TX-RX on the Boron were not impedance proof.
- The Connection for RX-TX was not connected properly.This is RX of one board connected to TX of the other. 
