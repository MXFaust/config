#include <Servo.h>

Servo theVessel;

void setup(){
  //Set up pins and Serial output
  pinMode(9, OUTPUT);
  pinMode(A0, INPUT);
  Serial.begin(9600);
  pinMode(8, OUTPUT);
  //digitalWrite(8,HIGH);
  theVessel.attach(9);
  pinMode(2,INPUT);
  
}

int buttonPin = 2;
boolean isLocked = false;
boolean buttonActive = false;
boolean longPressActive = false;
boolean manual = false;

long buttonTimer = 0;
long longPressTime = 250;

void loop(){
  
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
  if(manual == true){
    //I don't know why it does this
    Serial.println("Manual off");
    if(analogRead(A0) > 800 && isLocked == false){
     doLock();
    }
    
  
    
    
    
    
    
  }
//  if(manual){
//    Serial.println("This is manual mode");
//  }
//  if(isLocked){
//    Serial.println("This is locked");
//  }
//  if(!isLocked){
//    Serial.println("This is not locked");
//    
// }
//  Serial.println(analogRead(A0));
//  delay(100);
  
  
  
}


//Sets the boolean to true, then rotate it around
void doLock(){
  isLocked = true;
  theVessel.write(180);
  Serial.println("Did lock");
}


//Sets the boolean to false, then rotates it around
void doUnLock(){
  isLocked = false;
  theVessel.write(0);
  Serial.println("Did unlock");
}
//Changes the isOut boolean from true or to false;
