#include <Servo.h>

Servo theVessel;

void setup(){
  //Set up pins and Serial output
  pinMode(9, OUTPUT);
  pinMode(A0, INPUT);
  Serial.begin(9600);
  pinMode(8, INPUT);
  theVessel.attach(9);
  pinMode(2,INPUT);
  theVessel.write(0);
  
}

int buttonPin = 2;
boolean isLocked = false;
boolean buttonActive = false;
boolean longPressActive = false;
boolean manual = false;

long buttonTimer = 0;
long longPressTime = 250;

void loop(){
  //A very long, convoluted, and messy conditional statement allowing dual function of the button.
  //It's like a circus funhouse for my manual boolean, twisted every which way.
  if (digitalRead(buttonPin) == HIGH) {
    if (buttonActive == false) {
      buttonActive = true;
      buttonTimer = millis();
    }
    if ((millis() - buttonTimer > longPressTime) && (longPressActive == false)) {
      longPressActive = true;
      manual = !manual;
      Serial.println("Switching sides");
    }
  } else {
    if (buttonActive == true) {
      if (longPressActive == true) {
        longPressActive = false;
      } else {
        if(!manual){
          if(isLocked){
                doUnLock();
              }
              else{
                doLock();
              }
        }
      }
      buttonActive = false;
    }
  }
  //Actully only works when manual is false, I don't know why
  if(manual == true){
    //I don't know why it does this
    Serial.println("Manual off");
    if(analogRead(A0) > 800 && isLocked == false){
     doLock();
    }
    if(digitalRead(8) == HIGH && isLocked == false){
      doLock();
    }  
  }
}


//Sets the boolean to true, then rotate it around
void doLock(){
  isLocked = true;
  theVessel.write(179);
  //delay(1000);
  //theVessel.write(90);
  Serial.println("Did lock");
}


//Sets the boolean to false, then rotates it around
void doUnLock(){
  isLocked = false;
  theVessel.write(0);
  Serial.println("Did unlock");
}
