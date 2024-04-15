#include "Energia.h" // Core library for code-sense
#include "SPI.h" // Include application, user and local libraries
#define HX8353E
#include "Screen_HX8353E.h"
Screen_HX8353E myScreen;
#include <Wire.h>
#include "Adafruit_TMP006.h"
#include "OPT3001.h"
#define USE_USCI_B1 

opt3001 opt3001;

const int BLED = 37;
const int GLED = 38;     //green LED
const int RLED = 39; //red LED
int buzzerPin = 40; 
const int xpin = 23;     // x-axis of the accelerometer
const int ypin = 24;     // y-axis
const int zpin = 25;     // z-axis (only on 3-axis models)
const int joystickSel = 5;     // the number of the joystick select pin
const int joystickX = 2;       // the number of the joystick X-axis analog
const int joystickY =  26;     // the number of the joystick Y-axis analog
int joystickSelState = 0;      // variable for reading the joystick sel status
int joystickXState, joystickYState ;

Adafruit_TMP006 tmp006;
void printFloat(float value, int places) ;

char buffer[7];
char buffer2[7];
int lenght = 10;
int check = 0;
int toneFreq = 200;
int incomingByte = 0;
int RLEDvalue = 0;
int GLEDvalue = 0;
int BLEDvalue = 0;
String b = "";

String displayingText = "";

unsigned long currentMillis = 0;
unsigned long previousMillis = 0;
const long interval = 5000;

void setup()
{
       analogReadResolution(12);

        pinMode(GLED, OUTPUT);     
        pinMode(RLED, OUTPUT);
        pinMode(BLED, OUTPUT);
        
        // initialize the pushbutton pin as an input:
        pinMode(joystickSel, INPUT_PULLUP);  
        
        unsigned int readings = 0;
        opt3001.begin();
        
        Serial.begin(9600);	// opens serial port, sets data rate to 9600 bps
        //delay(2000);
        
        // Initalizes the TMP006 for operation and for I2C communication
        if (! tmp006.begin(TMP006_CFG_8SAMPLE)) {
        Serial.println("No sensor found");
        while (1);
        
         myScreen.begin();
         myScreen.setFontSize(myScreen.fontMax());
         myScreen.clear(whiteColour);
                                          
}
}

void loop()
{
 currentMillis = millis();//number of milliseconds since running program
 if (currentMillis - previousMillis > interval){
   previousMillis = currentMillis;
   
  //menu
while(check == 0){
 Serial.println("Troubleshooting Program");
  Serial.println("");
  Serial.println("1. Read the object temperature and print the value in Celsius");
  Serial.println("2. Read the accelerometer and print the x and y angle");
  Serial.println("3. Read the ambient light intensity and print the Lux value");
  Serial.println("4. Read the joystick x and y and print the x and y angle");
  Serial.println("5. Write the input text to the LCD screen by capitalizing the first alphabet of the input text");
  Serial.println("along with the number of spaces, alphabets, words, and vowels");
  Serial.println("6. Generate a color on the LED [indigo or tan] with a brightness [0 to 100%]");
  Serial.println("7. Generate a beep tone on the buzzer");
  Serial.println("");
  Serial.print("Please input the selection [1 - 7]: ");
  digitalWrite(RLED,LOW);
  digitalWrite(GLED,LOW);
  digitalWrite(BLED,LOW);
 check=1;
 }
 }
 
 if (Serial.available() > 0){
   
	// read the incoming byte:
        incomingByte = Serial.read();
        incomingByte -= 48;
        Serial.println(incomingByte,DEC);
        
        //option 1
        if(incomingByte == 1){
          
        float objt = tmp006.readObjTempC();
        Serial.print("Object Temperature: "); Serial.print(objt); Serial.println("*C");Serial.println("");
        
        check = 0; 
        }
        
        //option 2
        if(incomingByte == 2){
          
          // print the sensor values:
          Serial.print(((int) analogRead(xpin)) - 2048);
          // print a tab between values:
          Serial.print("\t");
          Serial.print(((int) analogRead(ypin)) - 2048);
          // print a tab between values:
          Serial.print("\t");
          
          check = 0;
        }
        
        //option 3
        if(incomingByte == 3){
          
          uint32_t readings;
     
          // Read OPT3001
          readings = opt3001.readResult();  
          Serial.println(readings, DEC);
          
          check = 0;
        }
        
        //option 4
        if(incomingByte == 4){
          
          // read the analog value of joystick x axis
          joystickXState = analogRead(joystickX);
          joystickYState = analogRead(joystickY);
         
          Serial.print(joystickXState);Serial.print(" ,"); Serial.println(joystickYState); Serial.println(" ");
          
          check = 0;
        }
        
        //option 5 
        if(incomingByte == 5){
          
           /*Serial.print("Input the string: ");
           char holder = Serial.read();
            b  += holder;
           
           Serial.println(holder);
           Serial.println("");
           myScreen.gText(35, 54, displayingText, blueColour);
           displayingText = "";
           myScreen.clear(whiteColour);*/
          
          check = 0;
        }
        
        //option 6
        if(incomingByte == 6){
         
          colorCheck();
          check = 0;
          }


        
        //option 7
        if(incomingByte == 7){
          
          toneFreq = toneFreq + 1; 
          tone(buzzerPin, toneFreq ,1000);
          Serial.println("Tone generated!");
          Serial.println("");
          
          check = 0;
        }
        
        
 }
}

void colorCheck(){
  
  Serial.print("Input the color: ");
  int incomingByte2 = Serial.readBytesUntil('tan ' , buffer, lenght);
 
  Serial.println(buffer);
  
  if (incomingByte2 == 3){
    
   analogWrite(RLED, 210);
   analogWrite(GLED, 180);
   analogWrite(BLED, 140);
   
   incomingByte2 = 0;
    
     
  }
  
      
        
        
}



  
