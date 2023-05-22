# Preview
This area is for all the code that I have made and tested. I hope this code can help you develop some insight on what the product does.

# How do the 2 codes link?
I am using the UART connection to send and recieve data via the Boron. The Serial interface used is the Serial1. This is used as it is completely unattached to Serial and is usually not affected by it. Usually any Baud Rate is good enough but it is very useful for us to use the 9600 as it allows us to debug the issues. However I have switched to 115200 as soon as I felt that I had enough confidence in my equipment.



# Issues Faced
Sometimes the Serial1 would not upload the right values to the Boron. It was due to main 3 reasons:
- The Serial was displaying some outputs and it was taking up some amount of power.
- The connection between RX-TX on the feather and TX-RX on the Boron were not impedance proof.
- The Connection for RX-TX was not connected properly.This is RX of one board connected to TX of the other. 
