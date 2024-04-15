/*
  Yahriel Negrete
  yahrielnegrete@my.unt.edu
  CSCE 3612
  11216064   
*/


const int pushButton1 = 33; 
const int pushButton2 = 32; 
const int LEDgreen = 38; 
const int LEDred = 39; 
const int resetButton = PUSH1; 
int buzzerPin = 40; 

//set all of the button states to 0
int button1State = 0;
int button2State = 0;
int resetState = 0;

int redCount = 0;  //keeps track of the total presses of button 1
int greenCount = 0;  //keeps track of the total presses of button 2
int rMath = 0; //The math integer for button 1
unsigned long switchBounce = 0; // integer to keep track of millis time
unsigned long delayTime = 100; 

int toneFreq = 1000; 

void setup()
{
  //Outputs
  pinMode(LEDgreen, OUTPUT);     
  pinMode(LEDred, OUTPUT);     
  pinMode(buzzerPin, OUTPUT);
    
  //Inputs  
  pinMode(pushButton1, INPUT_PULLUP);     
  pinMode(pushButton2, INPUT_PULLUP);
  pinMode(resetButton, INPUT_PULLUP);
 

}

void loop()
{
  button1State = digitalRead(pushButton1);  //read button1 
  
    if (button1State == LOW && ((switchBounce + 500) < (millis() )))  
    {
      switchBounce = millis();  
      toneFreq = toneFreq + 1;  
      tone(buzzerPin, toneFreq ,500);  
      delay(500);  
      noTone(buzzerPin);  
      redCount++;  
      rMath = ((pow((redCount + 1),2)) / 4);  //perform the provided formula of ((n+1)^2)/4)
      
      for (int i = 0; i < rMath; i++)  //blink the red light for length of rMath
      {
        digitalWrite(LEDred, HIGH);  
        delay(500);  
        digitalWrite(LEDred, LOW);  
        delay(500);  
      }  
      
    }
    else
    {
       digitalWrite(LEDred, LOW); //light will stay off if there is no event
    }

  button2State = digitalRead(pushButton2);  //read button2 
    
    if (button2State == LOW && ((switchBounce + 500) < (millis() )))  
    {
      switchBounce = millis();  
      toneFreq = toneFreq + 1;  
      tone(buzzerPin, toneFreq, 500);  
      delay(500);  
      noTone(buzzerPin);  
      greenCount++;  
      
      for (int i = 0; i < greenCount; i++)  //blink the green light for length of greenCount
      {
        digitalWrite(LEDgreen, HIGH);  
        delay(500);  
        digitalWrite(LEDgreen, LOW);  
        delay(500);  
      }
     
    }
    else
    {
       digitalWrite(LEDgreen, LOW);  // light will stay off if there is no event
    }
    
  resetState = digitalRead(resetButton);  
  
  if (resetState == LOW)  
  {
    toneFreq = 1000;  
    greenCount = 0;  //reset the green counter 
    redCount = 0;    //reset the red counter
    digitalWrite(LEDgreen, LOW);  
    digitalWrite(LEDred, LOW);  
  }

}


//////////////////////////////////////////////////////////////////////
  //char myvalue [] = "alan";
    //Serial.println[myvalue[0]; //a
    //Serial.println[myvalue[1]; //l      
   int index = 0;
   char inch; //incoming character
   while (Serial.available() > 0) { //if there's a serial port connection
      inch = Serial.read(); //read the serial and assign it to inch
      //if (inch == '\n') {
      // Serial.print("You entered: ");
//Serial.println(buffer[0]);
        //Serial.println(buffer[1]);
       //Serial.print(buffer);
       //buffer[0] = 0;
       //index = 0;
      //}
      //else{
        String incomingString = Serial.readString();
        Serial.print("I received: ");
        Serial.println(incomingString);
        
       if (x <= 99) 
       {
         buffer[x] = inch; 
         //Serial.println(buffer[x]);
         //Serial.println(buffer);
         //Serial.println("value of x = ");
         //Serial.println(x); 
         
         /*
         if (buffer[x] == 'POW')
         {
          Serial.println("entered1");
         } */
         x++; 
         
            //char mychar = buffer[x];

       } 
       
    
        ///index++;
         //buffer[index] = 0;
         //Serial.println("index:") ;
         //Serial.println(index) ;
         
        
        //if (x == 99 )
        //{
         //Serial.println(buffer); 
        //}
       
         //Serial.println(buffer);
        //Serial.println(buffer[1]);
      //}
      
  }
 
  
  /*
  for (int x = 0; x<99; x++)
  {
    if (buffer[x] == 'a')
    {
     Serial.println("Found A ");
    }
  }*/
/* 
 if ( buffer[i] != null)
 {
  Serial.println(buffer[1]); 
 }
*/ 
  
  /*   for(int i = 0; i < 99; i++)
   {
      Serial.println(buffer[i]);
   }
  */ 

