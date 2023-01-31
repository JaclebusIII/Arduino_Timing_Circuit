# Arduino Timing Circuit
The purpose of this project is to trigger four different 3D cameras at 20 FPS with each camera offset by 2ms. The implementation that was used can be adapted to trigger up to 8 cameras at any frequency or time offset with just a few changes to the code. The code has been commented to make this as intuitive as possible. 

## Hardware Implementation
For the hardware, I used an Arduino Nano soldered onto a custom made PCB for quick and reliable wire connections. To complexity and cost down, the PCB design is meant to be milled from a small piece of single sided copper clad board on a desktop CNC mill. For the connectors, I used 8 barrel jacks, 4 of which are connected to analog pins and the other 4 connected to digital pins. This was done so that I could keep the board as small as possible with the widest wires possible to ensure proper connection. I mounted the Nano to the bottom of the board to make soldering the Nano as easy as possible and maximize the room for wires on the top.

Board files and images are included below. 

## Code Implementation 
To trigger the cameras, I used the Nano's hardware triggers along with a simple state machine to trigger the exposure of each individual camera. This means that the main "loop" function is completely empty and the function that actually does all the triggering is the Interrupt Service Routine or IRS. This is where the state machine is implemented. 

The timing parameters are set at the top of the code, and can be changed very easily for other timing needs. The two parameters are the compare match register or cmr and the numstates variable. The internal clock of the Arduino runs at 16GHZ and the cmr is used to subsample this internal clock at the rate of the camera offset frequency. The equation for ocr given frequency is given below:

    compare match register = [(Arduino clock speed 16,000,000Hz) / (interrupt frequency (Hz) * prescaler)] - 1

For my purposes, I used a prescaler of 1024 because the value of the cmr cannot exceed 256 due to hardware limitations and this allowed me to get enough timer precision. The prescaler is configured in the setup function at the bottom of the code. 

The numstates variable determines the camera's FPS. It is basically the number of subsampled clock ticks to wait between individual camera triggers. The equation of that variable is shown below.

    numstates = interrupt frequency (Hz) / Camera frequency 

The PCB board is not necessary to use the code and is simply there for quick and reliable connection to the Arduino

## Images
![](/images/photo1.jpg)

![](/images/photo2.jpg)

![](/images/photo3.jpg)

![](/images/photo4.jpg)