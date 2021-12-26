#include <Servo.h>

Servo rightServo;
#define rightServoPin 5
const float rightSpdStp = 90 ;
float rightSpd = rightSpdStp; // "90" is the input number at which the Servo doesn't move in either direction. 

Servo leftServo;
#define leftServoPin 6
const float leftSpdStp = 90;
float leftSpd = leftSpdStp;

#define sensPin A5
int sensLvlRaw;

#define irRightPin A0
int valueRight;
#define ledRightPin 11
bool ledSwitchRight = 0; //active low (WHITE = LOW)

#define irLeftPin A1
int valueLeft;
#define ledLeftPin 12
bool ledSwitchLeft = 0; //active low (WHITE = LOW)

#define butOnOffPin 10 //active low
bool butOnOffState = 1;
bool lastButOnOffState = 1;
bool onOff = 0; //Variable to toggle on/off for the running of the main program. Default off. 

#define butAddPin 2 // button to increase overall speeds. Active low. 
bool butAddState = 1;
bool lastButAddState = 1;
#define butMinPin 3 // button to decrease overall speeds.
bool butMinState = 1;
bool lastButMinState = 1;
#define butRstPin 4 // button to reset to default speeds. 
bool butRstState = 1;
bool lastButRstState = 1;
float spdOffset = 0; //speed offset from default. 

#define irModuleRightPin 7 
bool irModuleRightRead; //active low 
#define irModuleLeftPin 8  
bool irModuleLeftRead; //active low 

bool part2Toggle = 0;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  rightServo.attach(rightServoPin);
  leftServo.attach(leftServoPin);
  
  pinMode(sensPin, INPUT);
  pinMode(irRightPin, INPUT);
  pinMode(ledRightPin, OUTPUT);
  pinMode(irLeftPin, INPUT);
  pinMode(ledLeftPin, OUTPUT);
  
  pinMode(butOnOffPin, INPUT_PULLUP);
  
  pinMode(butAddPin, INPUT_PULLUP);
  pinMode(butMinPin, INPUT_PULLUP);
  pinMode(butRstPin, INPUT_PULLUP);

  //Mark 3:
  pinMode(irModuleRightPin, INPUT);
  pinMode(irModuleLeftPin, INPUT);
}

void loop() {
  // put your main code here, to run repeatedly:
  //Reading: 
  sensLvlRaw=analogRead(sensPin);
  
  valueRight = analogRead(irRightPin);//analogRead(irRightPin);
  valueLeft = analogRead(irLeftPin); 
  
  butOnOffState = digitalRead(butOnOffPin);
  butAddState = digitalRead(butAddPin);
  butMinState = digitalRead(butMinPin);
  butRstState = digitalRead(butRstPin);

  irModuleRightRead = digitalRead(irModuleRightPin);
  irModuleLeftRead = digitalRead(irModuleLeftPin);

  //Code: 
  if (valueRight<sensLvlRaw)
  {
    ledSwitchRight = 0;
  }
  else
  {
    ledSwitchRight = 1;
  }
  if (valueLeft<sensLvlRaw)
  {
    ledSwitchLeft = 0;
  }
  else
  {
    ledSwitchLeft = 1;
  }
  digitalWrite(ledRightPin, ledSwitchRight);
  digitalWrite(ledLeftPin, ledSwitchLeft);

  if (butOnOffState == LOW)
  {
    if (butOnOffState !=lastButOnOffState)
    {
      onOff = !onOff;
    }
  }
  lastButOnOffState = butOnOffState;

  if (butRstState == LOW)
  {
    if (butRstState != lastButRstState)
    {
      spdOffset = 0;
    }
   }
  lastButRstState = butRstState;

  if (butAddState == LOW)
  {
    if (butAddState != lastButAddState)
    {
      spdOffset ++;
    }
  }
 lastButAddState = butAddState;

 if (butMinState == LOW)
 {
    if (butMinState != lastButMinState)
    {
      spdOffset --;
    }
 }
 lastButMinState = butMinState;

  if (onOff == HIGH)
  {
    if (part2Toggle == LOW)
    {
      if (ledSwitchLeft == LOW && ledSwitchRight == LOW) //forward
      {
        rightSpd = rightSpdStp - (5 + spdOffset);
        leftSpd = leftSpdStp + (5 + spdOffset);
        rightServo.write(rightSpd);
        leftServo.write(leftSpd);
      }
      else if (ledSwitchLeft == HIGH && ledSwitchRight == LOW) //turn left
      {
        rightServo.write(rightSpdStp+ (4+spdOffset));
        leftServo.write(leftSpdStp-(4+spdOffset));      
        rightSpd = rightSpdStp -(6 + spdOffset); // go
        leftSpd = leftSpdStp - (4 + spdOffset); // reverse
        rightServo.write(rightSpd);
        leftServo.write(leftSpd);
        
      }
      else if (ledSwitchRight == HIGH && ledSwitchLeft == LOW) //turn right
      {
          rightServo.write(rightSpdStp+(4+spdOffset));
          leftServo.write(leftSpdStp-(4+spdOffset));
          
          rightSpd = rightSpdStp + (4 + spdOffset); //reverse
          leftSpd = leftSpdStp + (6 + spdOffset); //go
          rightServo.write(rightSpd);
          leftServo.write(leftSpd);
      }
      else if (ledSwitchRight == HIGH && ledSwitchLeft == HIGH)
      {
        part2Toggle = HIGH;
        rightServo.write(rightSpdStp+(4+spdOffset));
        leftServo.write(leftSpdStp-(4+spdOffset));
        
        rightSpd = rightSpdStp + (4 + spdOffset); //reverse
        leftSpd = leftSpdStp + (6 + spdOffset); //go
        rightServo.write(rightSpd);
        leftServo.write(leftSpd);
      }
    }
    else if (part2Toggle == HIGH)
    {
      if (ledSwitchLeft == LOW && ledSwitchRight == LOW) //forward
      {
        rightSpd = rightSpdStp - (5 + spdOffset);
        leftSpd = leftSpdStp + (5 + spdOffset);
        rightServo.write(rightSpd);
        leftServo.write(leftSpd);
      }
      else if (ledSwitchLeft == HIGH && ledSwitchRight == LOW) //turn left
      {
        rightServo.write(rightSpdStp+ (4+spdOffset));
        leftServo.write(leftSpdStp-(4+spdOffset));      
        rightSpd = rightSpdStp -(6 + spdOffset); // go
        leftSpd = leftSpdStp - (4 + spdOffset); // reverse
        rightServo.write(rightSpd);
        leftServo.write(leftSpd);
        
      }
      else if (ledSwitchRight == HIGH && ledSwitchLeft == LOW) //turn right
      {
          rightServo.write(rightSpdStp+(4+spdOffset));
          leftServo.write(leftSpdStp-(4+spdOffset));
          
          rightSpd = rightSpdStp + (4 + spdOffset); //reverse
          leftSpd = leftSpdStp + (6 + spdOffset); //go
          rightServo.write(rightSpd);
          leftServo.write(leftSpd);
      }
      //if robot still on Task 8
      else if (ledSwitchRight == HIGH && ledSwitchLeft == HIGH && irModuleRightRead == LOW && irModuleLeftRead == HIGH)
      {
        rightServo.write(rightSpdStp+(4+spdOffset));
        leftServo.write(leftSpdStp-(4+spdOffset));
        
        rightSpd = rightSpdStp + (4 + spdOffset); //reverse
        leftSpd = leftSpdStp + (6 + spdOffset); //go
        rightServo.write(rightSpd);
        leftServo.write(leftSpd);
      }
      //TASK 12
      else if (ledSwitchRight == HIGH && ledSwitchLeft == HIGH && irModuleRightRead == HIGH && irModuleLeftRead == LOW)
      {
        rightSpd = rightSpdStp - (5 + spdOffset);
        leftSpd = leftSpdStp + (5 + spdOffset);
        rightServo.write(rightSpd);
        leftServo.write(leftSpd);
      }
      //TASK 13
      else if (ledSwitchRight == HIGH && ledSwitchLeft == HIGH && irModuleRightRead == HIGH && irModuleLeftRead == HIGH)
      {
        rightSpd = rightSpdStp;
        leftSpd = leftSpdStp;
        rightServo.write(rightSpd);
        leftServo.write(leftSpd);
      }
    }
  }
  else
  {
    rightSpd = rightSpdStp;
    leftSpd = leftSpdStp;
    rightServo.write(rightSpd);
    leftServo.write(leftSpd);
  }
    
  Serial.print(valueLeft);
  Serial.print("\t");
  Serial.print(ledSwitchLeft);
  Serial.print("\t");
  Serial.print(valueRight);
  Serial.print("\t");
  Serial.print(ledSwitchRight);
  Serial.print("\t");
  Serial.print(sensLvlRaw);
  Serial.print("\t");
  Serial.print(butOnOffState);
  Serial.print("\t");
  Serial.print(onOff);
  Serial.print("\t");
  Serial.print(butAddState);
  Serial.print("\t");
  Serial.print(butMinState);
  Serial.print("\t");
  Serial.print(butRstState);
  Serial.print("\t");
  Serial.print(spdOffset);
  Serial.print("\t");
  Serial.print(leftSpd);
  Serial.print("\t");
  Serial.print(rightSpd);
  Serial.print("\t");
  Serial.print(irModuleLeftRead);
  Serial.print("\t");
  Serial.print(irModuleRightRead);
  Serial.print("\t");
  Serial.println(part2Toggle);

  delay(50);
}
