
/*
 ADXL3xx 3-axis accelerometer example for Educational BoosterPack MK II
 http://boosterpackdepot.info/wiki/index.php?title=Educational_BoosterPack_MK_II
 
 Absolute rating/conversion can be determined from the ADXL3xx datasheet.
 As a quick reference, for LaunchPads with 12-bit ADC (MSP430F5529, Tiva C, etc.), 
 the entire analog  range is [0,4096]. For simple tilting calculation 
 [-1g,1g] ~ = [mid-800, mid + 800] = [2048-800,2048+800] = [1248,2848]
 
 Modified from ADXL3xx example by David A. Mellis & Tom Igoe
 
 Reads an Analog Devices ADXL3xx accelerometer and communicates the
 acceleration to the computer.  The pins used are designed to be easily
 compatible with the breakout boards from Sparkfun, available from:
 http://www.sparkfun.com/commerce/categories.php?c=80

 http://www.arduino.cc/en/Tutorial/ADXL3xx

 The circuit:

 * analog 25: z-axis
 * analog 24: y-axis
 * analog 23: x-axis
 
 created 2 Jul 2008
 by David A. Mellis
 modified 30 Aug 2011
 by Tom Igoe 
 modified 03 Dec 2013
 by Dung Dang
 
 This example code is in the public domain.

*/
#include <Wire.h>
#include "Adafruit_TMP006.h"
#define USE_USCI_B1 
#define HX8353E 
#include "Screen_HX8353E.h"
Screen_HX8353E myScreen;
Adafruit_TMP006 tmp006;
#include "SPI.h"

const int xpin = 23;                  // x-axis of the accelerometer
const int ypin = 24;                  // y-axis
const int zpin = 25;   // z-axis (only on 3-axis models)
const int LEDG = 38;
const int LEDR = 39;
const int buttonOne = 33;
const int buttonTwo = 39;
int blinks = 0;
String incomingByte;
String command;
boolean execute = false;
unsigned long previousMillis = 0;
boolean Accel;
boolean temp;



void setup()
{
  // By default MSP432 has analogRead() set to 10 bits. 
  // This Sketch assumes 12 bits. Uncomment to line below to set analogRead()
  // to 12 bit resolution for MSP432.
  analogReadResolution(12);

  // initialize the serial communications:
  pinMode (LEDG, OUTPUT);
  pinMode (LEDR, OUTPUT);
  pinMode (buttonOne, INPUT_PULLUP);
  pinMode (buttonTwo, INPUT_PULLUP);
 
  

  Serial.begin(9600);
  
   // Initalizes the TMP006 for operation and for I2C communication
  if (! tmp006.begin(TMP006_CFG_8SAMPLE)) {
    Serial.println("No sensor found");
    while (1);
  }
  
  myScreen.begin();
  myScreen.setFontSize(myScreen.fontMax());
  myScreen.clear(darkGrayColour);
  myScreen.clear();
  
}

void loop()
{
  if(Serial.available() >0){
     incomingByte = Serial.readStringUntil('\r');
     execute = true;
     processCommand(command);
     blinks = blinks *2;
     previousMillis = millis();
  }
  
  if (Accel){
  // print the sensor values:
  Serial.print(((int) analogRead(xpin)) - 2048);
  // print a tab between values:
  Serial.print("\t");
  Serial.print(((int) analogRead(ypin)) - 2048);
  // print a tab between values:
  Serial.print("\t");
  Serial.print(((int) analogRead(zpin)) - 2048);
  Serial.println();
  Accel = false;
  }
 
 if(temp){
 float objt = tmp006.readObjTempC();
  Serial.print("Object Temperature: "); Serial.print(objt); Serial.println("*C");
  float diet = tmp006.readDieTempC();
  Serial.print("Die Temperature: "); Serial.print(diet); Serial.println("*C");
  temp = false;
 }
}


