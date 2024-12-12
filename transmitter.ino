// This code is a modified version of the code from the SparkFun Hookup guide for the RFM69:
// https://learn.sparkfun.com/tutorials/rfm69hcw-hookup-guide/all
// Originally written by Mike Grusin.

// Uses the RFM69 library by Felix Rusu, LowPowerLab.com
// Original library: https://www.github.com/lowpowerlab/rfm69
// SparkFun repository: https://github.com/sparkfun/RFM69HCW_Breakout


// Include the RFM69 and SPI libraries:

#include <RFM69.h>
#include <SPI.h>

// Addresses for this node. CHANGE THESE FOR EACH NODE!

#define NETWORKID     0   // Must be the same for all nodes
#define MYNODEID      1   // My node ID
#define TONODEID      2   // Destination node ID

#define FREQUENCY     RF69_915MHZ

#define BUTTON        8 // Button input pin

// Create a library object for our RFM69HCW module:

RFM69 radio;

void setup()
{
 Serial.begin(9600);
 Serial.print("Node ");
 Serial.print(MYNODEID,DEC);
 Serial.println(" ready");  

 pinMode(BUTTON, INPUT_PULLUP); // Set up the button

 radio.initialize(FREQUENCY, MYNODEID, NETWORKID);
 radio.setHighPower(); // Always use this for RFM69HCW

}

void loop()
{
 // Set up a "buffer" for characters that we'll send:

 static char sendbuffer[62];
 static int sendlength = 0;

 // SENDING

 // In this section, we'll send a signal to the receiver.

 if (digitalRead(BUTTON) == 0) // Check if the button has been pressed
 {
    char input = "\r"; // Default message to get it to send right- the message is gibberish, but the point is just to send a signal

    Serial.print("sending to node ");
    Serial.print(TONODEID, DEC);
    Serial.print(", message [");
    for (byte i = 0; i < sendlength; i++)
    Serial.print(sendbuffer[i]);
    Serial.println("]");

    // There are two ways to send packets. If you want
    // acknowledgements, use sendWithRetry():

    radio.send(TONODEID, sendbuffer, sendlength);

    sendlength = 0; // reset the packet
 }
}