#include <Servo.h>

int led = 13;                // the pin the LED is atteched to
int sensor = 2;              // the pin the PIR sensor is atteched to
int state = LOW;             // LOW = no motion, HIGH = motion
int val = 0;                 // Stores sensor status
int buzzerPin = 12;          // The pin the buzzer is attached to
Servo eyePivot;              // The servo controlling the eyes
int pos = 0;                 // The position of eyePivot
int laserPin = 10;           // The pin of the laser

void setup() {
  // Initialise IO
  pinMode(led, OUTPUT);
  pinMode(buzzerPin, OUTPUT);
  pinMode(sensor, INPUT); 
  pinMode(laserPin, OUTPUT);
  eyePivot.attach(11);
  digitalWrite(laserPin, HIGH);

  Serial.begin(9600);
}

void activateAlarm() {
  // Turn on the buzzer
  tone(buzzerPin, 50);
  // Turn on the LED
  digitalWrite(led, HIGH);
  // Turn on the laser
  digitalWrite(laserPin, LOW);
}


void deactivateAlarm() {
  // Turn off the buzzer
  noTone(buzzerPin);
  // Turn off the LED
  digitalWrite(led, LOW);
  // Turn on the laser
  digitalWrite(laserPin, HIGH);
}

void checkPIRSensor () {
  // Read sensor status
  val = digitalRead(sensor);

  // If motion is detected
  if (val == HIGH) {           
    activateAlarm();
    //delay(100);                
    
    // If the motion has been detected for the first time
    if (state == LOW) {
      Serial.println("Motion detected!"); 
      state = HIGH;       
    }
  } 
  else {
      deactivateAlarm();
      //delay(200);             
      
      if (state == HIGH){
        Serial.println("Motion stopped!");
        state = LOW;       
    }
  }
}

void loop() {
  // Spin the servo
  for (pos = 0; pos <= 180; pos += 1) { // goes from 0 degrees to 180 degrees
    eyePivot.write(pos);
    checkPIRSensor();            
    delay(15);                       
  }
  for (pos = 180; pos >= 0; pos -= 1) {
    eyePivot.write(pos);
    checkPIRSensor();         
    delay(15);                       
  }

  /**/
}