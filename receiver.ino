// This code is a modified version of the code from the SparkFun Hookup guide for the RFM69:
// https://learn.sparkfun.com/tutorials/rfm69hcw-hookup-guide/all
// Originally written by Mike Grusin.

// Uses the RFM69 library by Felix Rusu, LowPowerLab.com
// Original library: https://www.github.com/lowpowerlab/rfm69
// SparkFun repository: https://github.com/sparkfun/RFM69HCW_Breakout

// Include the RFM69 and SPI libraries:

#include <RFM69.h>
#include <SPI.h>
#include <Servo.h>

#define NETWORKID     0   // Must be the same for all nodes
#define MYNODEID      2   // My node ID
#define TONODEID      1   // Destination node ID

#define FREQUENCY     RF69_915MHZ

#define BUTTON        8 // Input pin to receive signal from button
#define SERVO         6 // Output pin to give signal to servo

// Create a library object for our RFM69HCW module:

RFM69 radio;

Servo myservo;

void setup()
{
  Serial.begin(9600);
  Serial.print("Node ");
  Serial.print(MYNODEID,DEC);
  Serial.println(" ready");  

  pinMode(BUTTON, INPUT_PULLUP); // Set up button
  myservo.attach(SERVO); // Set up servo
  myservo.write(0);

  // Initialize the RFM69HCW:
  radio.initialize(FREQUENCY, MYNODEID, NETWORKID);
  radio.setHighPower(); // Always use this for RFM69HCW

}

void loop()
{

  // RECEIVING

  // In this section, we'll check with the RFM69HCW to see
  // if it has received any packets, or if the button is being held down:

  if (radio.receiveDone() || digitalRead(BUTTON) == 0) // Got an input!
  {
    myservo.write(90);
    delay(5000); // This is the delay time used for the example
    myservo.write(0);
    delay(1000); // Another delay to make it run smoother- no reason user will need to go again in such a short time
  }

}