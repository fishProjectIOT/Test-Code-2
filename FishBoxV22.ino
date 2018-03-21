// Uses a PIR sensor to detect movement, buzzes a buzzer
// more info here: http://blog.makezine.com/projects/pir-sensor-arduino-alarm/
// 
// based upon:
// PIR sensor tester by Limor Fried of Adafruit
// tone code by michael@thegrebs.com

#include <Wire.h>
#include "rgb_lcd.h"

rgb_lcd lcd;



 
int ledPin = 7;                // choose the pin for the LED
int inputPin = 4;               // choose the input pin (for PIR sensor)
const int buttonPin = 6;        //Button Pin
int pirState = LOW;             // we start, assuming no motion detected
int val = 0;                    // variable for reading the pin status
int pinSpeaker = 8;           //Set up a speaker on a PWM pin (digital 9, 10, or 11)
int fishCounter = 0;

int buttonState = 0; 

char dtaUart[15];
char dtaLen = 0;


void setup() {

Serial.begin(115200);
  pinMode(ledPin,OUTPUT);

  
  pinMode(ledPin, OUTPUT);      // declare LED as output
  pinMode(inputPin, INPUT);     // declare sensor as input
  pinMode(pinSpeaker, OUTPUT);
  Serial.begin(9600);
  lcd.begin(16, 2);

  pinMode(ledPin, OUTPUT);
  pinMode(buttonPin, INPUT);

    //Startup message
    lcd.setRGB(0, 255, 0);
    lcd.setCursor(0, 0);
    lcd.print("Fish Counter v1");
    lcd.setCursor(0, 1);
    lcd.print("Initialising..");
    delay(4000);
    lcd.clear();
    lcd.setCursor(0, 0);
    playTone(10, 40);
    lcd.print("Ready!");
    lcd.setRGB(255, 255, 255);
    
}

void loop()
{
  

  buttonState = digitalRead(buttonPin);
  if (buttonState == HIGH){
    lcd.setRGB(255, 255, 255);
    lcd.clear();
    playTone(10, 40);
    delay(250);
    playTone(10, 100);
    lcd.setCursor(0, 0);
    lcd.print("Resetting");
    lcd.setCursor(0,1) ;
    lcd.print("Counter... ");
    delay(2500);
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("Count: 0");
    fishCounter = 0;
  }
  else {
          val = digitalRead(inputPin);  // read input value
         
            if (val == HIGH) 
            {            // check if the input is HIGH
              lcd.setRGB(255, 255, 255);
              lcd.clear();
              digitalWrite(ledPin, HIGH);  // turn LED ON
                playTone(10, 160);
                fishCounter ++;
                lcd.print("Count: ");
                lcd.print(fishCounter);
                lcd.setCursor(0, 1);
                lcd.print("Quota: 3");
                delay(2500);
                digitalWrite(ledPin, LOW); 
                
                
                if (fishCounter == 3)
                { 
                  lcd.clear();
                  playTone(500, 160);
                  digitalWrite(ledPin, LOW);
                  lcd.setCursor(0, 0);
                  lcd.print("Quota Reached!");
                  lcd.setRGB(255, 0, 0);
                  delay(2500);   
                }
            }
    
  }
}


void playTone(long duration, int freq) 
{
    duration *= 1000;
    int period = (1.0 / freq) * 1000000;
    long elapsed_time = 0;
    while (elapsed_time < duration) 
    {
        digitalWrite(pinSpeaker,HIGH);
        delayMicroseconds(period / 2);
        digitalWrite(pinSpeaker, LOW);
        delayMicroseconds(period / 2);
        elapsed_time += (period);
    }    
}


