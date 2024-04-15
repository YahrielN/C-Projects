/*
  Joshua Kramer
  JoshuaKramer@my.unt.edu
  CSCE 3612
  11248559    jdk0209
*/


const int pushButton1 = 33; 
const int pushButton2 = 32; 
const int LEDgreen = 38; 
const int LEDred = 39; 
const int resetButton = PUSH1; 
int buzzerPin = 40; 

int button1State = 0;
int button2State = 0;
int resetState = 0;
  //set all of the button states to 0

int redCount = 0;  //keep track of the total presses of button 1
int greenCount = 0;  //keep track of the total presses of button 2
int redMath = 0; //The math integer for button 1
unsigned long switchBounce = 0; // integer to keep track of millis time
unsigned long delayTime = 100; // .1s set for bouncing delay

int toneFreq = 1000; // the frequency of the buzzer tone

void setup()
{
  pinMode(LEDgreen, OUTPUT);     
  pinMode(LEDred, OUTPUT);     
  pinMode(buzzerPin, OUTPUT);
    //sets the outputs of the program
    
  pinMode(pushButton1, INPUT_PULLUP);     
  pinMode(pushButton2, INPUT_PULLUP);
  pinMode(resetButton, INPUT_PULLUP);
    //sets the inputs of the program

}

void loop()
{
  button1State = digitalRead(pushButton1);  //read button1 on red board
  
    if (button1State == LOW && switchBounce == 0)  //sense when button 1 is pressed and do switch bounce checking
    {
      switchBounce = millis();  //set switch bounce to millis() to account for switch bouncing
      toneFreq = toneFreq + 1;  //change tone frequency to +1
      tone(buzzerPin, toneFreq ,500);  //play a tone on the buzzer
      delay(500);  //wait .5s
      noTone(buzzerPin);  //turn off the buzzer
      redCount++;  //increment the counter for the button 1 / red light 
      
      redMath = ((pow((redCount + 1),2)) / 4);  //perform the formula ((n+1)^2/4)
      
      for (int i = 0; i < redMath; i++)  //blink the red light for length of redMath
      {
        digitalWrite(LEDred, HIGH);  //turn light on red light
        delay(500);  //wait .5s
        digitalWrite(LEDred, LOW);  //turn red light off
        delay(500);  //wait .5s
      }  
      switchBounce = 0;  //reset the switch Bounce back to 0 to allow for buttons to be pressed again
    }
    else
    {
       digitalWrite(LEDred, LOW); //if there is no event make sure redLight is off
    }

  button2State = digitalRead(pushButton2);  //read button2 on red board
    
    if (button2State == LOW && switchBounce == 0)  //sense when button 2 is pressed and do switch bounce checking
    {
      switchBounce = millis();  //set switch bounce to millis() to account for switch bouncing
      toneFreq = toneFreq + 1;  //change tone frequency to +1
      tone(buzzerPin, toneFreq, 500);  //play a tone on the buzzer
      delay(500);  //wait .5s
      noTone(buzzerPin);  //turn off the buzzer
      greenCount++;  //increment the counter for the button 2 / green light
      
      for (int i = 0; i < greenCount; i++)  //blink the green light for length of greenCount
      {
        digitalWrite(LEDgreen, HIGH);  //turn on green light
        delay(500);  //wait .5s
        digitalWrite(LEDgreen, LOW);  //turn off green light
        delay(500);  //wait .5s
      }
      switchBounce = 0;  //reset the switch Bounce back to 0 to allow for buttons to be pressed again
    }
    else
    {
       digitalWrite(LEDgreen, LOW);  // if there is no event make sure greenLight is off
    }
    
  resetState = digitalRead(resetButton);  //read the resetButton assigned on the green board
  
  if (resetState == LOW)  //sense when the reset Button is pressed
  {
    toneFreq = 1000;  //reset the tone Frequency back to 1000
    greenCount = 0;  //reset the green counter back to 0
    redCount = 0;    //reset the red counter back to 0
    digitalWrite(LEDgreen, LOW);  //turn off the green light
    digitalWrite(LEDred, LOW);  //turn off the red light
  }

}

