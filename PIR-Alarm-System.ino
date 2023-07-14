int led = 13;                // the pin the LED is atteched to
int sensor = 2;              // the pin the PIR sensor is atteched to
int state = LOW;             // LOW = no motion, HIGH = motion
int val = 0;                 // Stores sensor status
int buzzerPin = 12;          // The pin the buzzer is attached to

void setup() {
  // Initialise IO
  pinMode(led, OUTPUT);
  pinMode(buzzerPin, OUTPUT);
  pinMode(sensor, INPUT); 

  Serial.begin(9600);
}

void activateAlarm() {
  // Turn on the buzzer
  tone(buzzerPin, 50);
  // Turn on the LED
  digitalWrite(led, HIGH);
}


void deactivateAlarm() {
  // Turn off the buzzer
  noTone(buzzerPin);
  // Turn off the LED
  digitalWrite(led, LOW);
}

void loop() {
  // Read sensor status
  val = digitalRead(sensor);

  // If motion is detected
  if (val == HIGH) {           
    activateAlarm();
    delay(100);                
    
    // If the motion has been detected for the first time
    if (state == LOW) {
      Serial.println("Motion detected!"); 
      state = HIGH;       
    }
  } 
  else {
      deactivateAlarm();
      delay(200);             
      
      if (state == HIGH){
        Serial.println("Motion stopped!");
        state = LOW;       
    }
  }
}