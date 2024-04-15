#include "Energia.h" // Core library for code-sense
#include "SPI.h" // Include application, user and local libraries
#define HX8353E
#include "Screen_HX8353E.h"
Screen_HX8353E myScreen;

const int xpin = 23;                  // x-axis of the accelerometer
const int ypin = 24;                  // y-axis
const int zpin = 25;                  // z-axis (only on 3-axis models)
const int button1 = 33; 
const int button2 = 32;
const int RLED = 39;     //red LED
int buzzerPin = 40; 

String displayingText = "";
int i = 1;
int sec =-1;
int mi = 0;
int hr = 0;
unsigned long time = 0;
unsigned long switchBounce = 0;
unsigned long currentMillis = 0;
unsigned long prevMillis = 0;
const long interval = 1000;
const long interval_2 = 1500;


int ledState = LOW;  
int button1State = 0;
int button2State = 0;
int resetState = 0;

int toneFreq = 1000; 

int minuteChangeFlag = false;
int hourChangeFlag = false;
int sentForChnage = false;


void setup()
{
       analogReadResolution(12);

       Serial.begin(9600);	// opens serial port, sets data rate to 9600 bps
       pinMode(RLED, OUTPUT); 
       pinMode(buzzerPin, OUTPUT);
       
       pinMode(button1, INPUT_PULLUP);     
       pinMode(button2, INPUT_PULLUP);
       attachInterrupt(button1,minuteChange,FALLING);
       attachInterrupt(button2,hourChange,FALLING);
       
      myScreen.begin();
       myScreen.setFontSize(myScreen.fontMax());
       myScreen.clear(whiteColour); 
       
}

void loop()
{
 if ((analogRead(ypin)-2048)  <= -200){
   
    
time = millis();
 if (time/i >= interval){ 
  sec++;
  i++;
  Serial.println(sec);
  Serial.print("Min: ");
  Serial.println(mi);
  Serial.print("Hr: ");
  Serial.println(hr);
    if (ledState == LOW)
          ledState = HIGH;
    else 
          ledState = LOW;
               
          digitalWrite(RLED, ledState);
 
 
 if (sec == 60){
   sec = 0;
   mi++;
 }
 
 if(mi == 60){
   mi=0;
   hr++;
 }
 
 if (hr == 24){
   hr = 0;
 }
 
 clock();
 }

   
 
 
  
    if (minuteChangeFlag && ((switchBounce + 500) < (millis() )) && !sentForChnage)  
    {
      sentForChnage = true;
      switchBounce = millis();  
      toneFreq = toneFreq + 1; 
      tone(buzzerPin, toneFreq ,200); 
      mi++;
      if(mi == 60)
      {
        mi=0;
      }
      minuteChangeFlag = false;
      sentForChnage = false;
    }
    

  
    if (hourChangeFlag && ((switchBounce + 500) < (millis() )) && !sentForChnage)  
    {
      sentForChnage = true;
      switchBounce = millis();  
      toneFreq = toneFreq + 1; 
      tone(buzzerPin, toneFreq ,200); 
      hr++;
      hourChangeFlag = false;
      sentForChnage = false;
    }
  }
  
  else {
    
      myScreen.clear(whiteColour);
  }
  
}



void minuteChange(){
  switchBounce = millis(); 
  minuteChangeFlag = true;
}

void hourChange(){
  switchBounce = millis(); 
  hourChangeFlag = true;
}

void clock(){
displayingText = displayingText + hr + ":" + mi + ":" + sec;
myScreen.gText(35, 54, displayingText, blueColour);
displayingText = "";
myScreen.clear(whiteColour);
}


