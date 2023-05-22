Hey, This is a main PCB for the work that I have done.
I would suggest you that you download the GRB files as a whole. This is what the old PCB looked like:
<!-- ![image](https://user-images.githubusercontent.com/45959802/211195725-e7094c48-b94b-49dc-b3df-4082b863f839.png) -->

<img src="https://user-images.githubusercontent.com/45959802/211195725-e7094c48-b94b-49dc-b3df-4082b863f839.png" width="600">

Since Then I have updated the PCB to add Boron and the Charging system via Solar Panel. The new PCB's look like:

<img src="https://github.com/amsheth/Work/assets/45959802/e866a806-7da7-4504-8698-e2e7e4470534" width="600">
<img src="https://github.com/amsheth/Work/assets/45959802/e1919a9d-257e-41fc-8a9c-9874fcff0c1a" width="600">
<img src="https://github.com/amsheth/Work/assets/45959802/984c091a-96d2-4b21-a784-d92d8b74c328" width="600">


# Building
The PCB can be easily assembled by attaching the [Stacking Headers](https://www.adafruit.com/product/2830) on the PCB for all the spots except the bottom where the Charging port will come. Since the [I2C Multiplexer](https://www.adafruit.com/product/2717) is usually not likely to fail and we will never upgrade it again without changing the PCB we can solder it to the board, hence we will only need 3 packs of stacking headers per PCB if we want to make it interchangeable.

## Equipments Required.
- Solder
- Soldering iron
- Soldering Paste
- Smoke dissipator
- Electric Tape
- [Stacking Headers](https://www.adafruit.com/product/2830) x 3
- [I2C Multiplexer](https://www.adafruit.com/product/2717)
- [Adalogger FeatherWing](https://www.adafruit.com/product/2922)
- [Adafruit Feather M0 Express](https://www.adafruit.com/product/3403)
- [Boron LTE CAT-M1](https://store.particle.io/products/boron-lte-cat-m1-noram-with-ethersim-4th-gen)
- [Adafruit Universal USB / DC / Solar LiPo charger](https://www.adafruit.com/product/4755)


## Instructions
[How to Solder](https://www.youtube.com/watch?v=Z0joOKaQ43A)

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


- Solder the I2C Multiplexer onto the PCB.
- We will now solder the Headers to Adalogger first but we will not trim the headers as we are going to use the headers to solder it again on the PCB it should look like this:
- We will now solder the headers to the Vin and GND and the I2C lines. We will also trim the headers after they have been soldered.
- We now Solder the Boron into the socket.
- Its is very important that we coved the trimmed and soldered headers on the board with electric tape to prevent any short circuit with the charger.
- Last but not the Least we will now solder the Charger but we will flip the PCB and attach it on the Bottom as it allows us to save space and seperate the charging connectors from other connectors.



## Finished Product

This is what a finished PCB looks like:
