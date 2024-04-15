
#include <Wire.h>
#include "Adafruit_TMP006.h"
#define USE_USCI_B1 

const int button1 = 33; 
const int button2 = 32; 
const int GLED = 38;     //green LED
const int RLED = 39;     //red LED
const int xpin = 23;     // x-axis of the accelerometer
const int ypin = 24;     // y-axis
const int zpin = 25;     // z-axis (only on 3-axis models)

Adafruit_TMP006 tmp006;
void printFloat(float value, int places) ;

int m;
int n;
int y = 0;
int result = 0;
unsigned long seriesValue;
String b = "";
unsigned long previousMillis = 0;   // will store last time LED was updated
unsigned long currentMillis = 0;    //number of milliseconds since running program
unsigned long switchBounce = 0;

const long interval = 1000; 

//State
int ledState = LOW;  
int button1State = 0;
int button2State = 0;

void setup() {
        pinMode(GLED, OUTPUT);     
        pinMode(RLED, OUTPUT); 
 
       pinMode(button1, INPUT_PULLUP);     
       pinMode(button2, INPUT_PULLUP);
       
       
       Serial.begin(9600);	// opens serial port, sets data rate to 9600 bps
       //attachInterrupt(button1, blink, CHANGE);
        
  // Initalizes the TMP006 for operation and for I2C communication
        if (! tmp006.begin(TMP006_CFG_8SAMPLE)) {
        Serial.println("No sensor found");
        while (1);
  }
}

void loop() {
  
  
      button1State = digitalRead(button1);  
      
      
      if (button1State == LOW && ((switchBounce + 500) < (millis() )))  
     {
       switchBounce = millis();
       float objt = tmp006.readObjTempC();
       Serial.print("Object Temperature: "); Serial.print(objt); Serial.println("*C");
       float diet = tmp006.readDieTempC();
       Serial.print("Die Temperature: "); Serial.print(diet); Serial.println("*C");
   
       delay(1000); // 4 seconds per reading for 16 samples per reading
     }
     
      button2State = digitalRead(button2);
     
     if (button2State == LOW && ((switchBounce + 500) < (millis() )))  
     {
      switchBounce = millis();
      // print the sensor values:
      Serial.print(((int) analogRead(xpin)) - 2048);
      // print a tab between values:
      Serial.print("\t");
      Serial.print(((int) analogRead(ypin)) - 2048);
      // print a tab between values:
      Serial.print("\t");
      Serial.print(((int) analogRead(zpin)) - 2048);
      Serial.println();
      // delay before next reading:
      delay(500);
     }
     
	// reply only when you receive data:
        if (Serial.available()){
		// read the incoming byte:
         
        char  incomingByte = Serial.read();
  
         
          b += incomingByte;
         
         //Red LED
         if (b.indexOf("POW") > -1)
         {
          
          int index = b.indexOf(' ');
          
          String c = b.substring(0, index);
          
          String d = b.substring(index + 1);//reads from first blank space to the end
          int index1 = d.indexOf(' ');
          String e = d.substring(0, index1); //e has the value of the first number
          
          String f = d.substring(index1 + 1);
          
          int index2 = f.indexOf(' ');
          String g = f.substring(0, index2);//g holds the second value
          
           m = e.toInt(); //convert to integer
           n = g.toInt();
           
           if (incomingByte == '\n')
       {
         
         result = Pow(m, n); //Call POWER Function
         
          
         int z = 0;
        while (z < (result*2)) //multiply by 2 because Z gets couted for both light on and light off
        {
         
         currentMillis = millis();//number of milliseconds since running program
         if (currentMillis - previousMillis > interval)
         {
           
           previousMillis = currentMillis;
           if (ledState == LOW)
               ledState = HIGH;
            else 
               ledState = LOW;
               
               digitalWrite(RLED, ledState);
               z++;
         }  
         
        }
        Serial.println("Executed");
        
       
      
       }
           
       }
      
       
       //GREEN LED
         if (b.indexOf("SRS") > -1)
         {
          
          int index = b.indexOf(' ');
          
          String h = b.substring(0, index);
          
          String k = b.substring(index + 1);//reads from first blank space to the end
       
          
          int index1 = k.indexOf(' ');
          String l = k.substring(0, index1); //l has the value of the first number
          
          
           n = l.toInt(); //convert to integer
           
           
           if (incomingByte == '\n')
       {
         
         result = Series(n);//Call function Series
          
         int z = 0;
         while (z < (result*2))
        {
          
         currentMillis = millis();//number of milliseconds since running program
         if (currentMillis - previousMillis > interval)
         {
           
           previousMillis = currentMillis;
           if (ledState == LOW)
               ledState = HIGH;
            else 
               ledState = LOW;
               
               digitalWrite(GLED, ledState);
               z++;
         }  
         
        }
        Serial.println("Executed");
        
       }
           
       }
         /* if (b.indexOf("POW") == -1 && b.indexOf("SRS") == -1){
           
            Serial.println("Invalid Command");
            
          }*/
}
}

int Pow(int m, int n)
{
 double result = 1;
  
 if(n > 0)
  {
   for (int i = 1; i <= n; i++)
   {
    result *= m;
   }
  }   
  return result;
}

int Series(int n)
{

 unsigned long Series1 = 1;
 for (int x=1; x <= n; ++x)
 {
  Series1 *= x; 
 }
 return Series1;
}

//void blink(){
//}

