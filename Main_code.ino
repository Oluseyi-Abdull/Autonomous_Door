#include <LiquidCrystal.h> // include the library code:
#include <Servo.h> // Include servo library 
Servo myservo;

// initialize the library by associating any needed LCD interface pin
// with the arduino pin number it is connected to
const int rs = 12, en = 11, d4 = 5, d5 = 4, d6 = 3, d7 = 2;
LiquidCrystal lcd(rs, en, d4, d5, d6, d7);
int startpos = 0;
int led = 10; // Test component, Will be replaced wil LCD screen
int trigPin = 9;    // Trigger
int echoPin = 8;    // Echo
long duration, cm, inches; // measuring values 

 
void setup() {
    // set up the LCD's number of columns and rows:
  lcd.begin(16, 2);
  myservo.attach(6); // Select pin for servo
//servo.write(0) // put servo to one of the limits to calibrate 
//should be at 0 degree position
  //Serial Port begin
  Serial.begin (9600);
  //Define inputs and outputs
  pinMode(trigPin, OUTPUT); // Setting digital pins 
  pinMode(echoPin, INPUT);
  pinMode(led,OUTPUT);
}
 
void loop() {
  // The sensor is triggered by a HIGH pulse of 10 or more microseconds.
  // Give a short LOW pulse beforehand to ensure a clean HIGH pulse:
  digitalWrite(trigPin, LOW);
  delayMicroseconds(5);
  digitalWrite(trigPin, HIGH);//Selecting digital writes and delays 
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);
 
  // Read the signal from the sensor: a HIGH pulse whose
  // duration is the time (in microseconds) from the sending
  // of the ping to the reception of its echo off of an object.
  pinMode(echoPin, INPUT);
  duration = pulseIn(echoPin, HIGH);// 
 
  // Convert the time into a distance
  cm = (duration/2) / 29.1;     // Divide by 29.1 or multiply by 0.0343
  inches = (duration/2) / 74;   // Divide by 74 or multiply by 0.0135
  
  Serial.print(inches);
  Serial.print("in, ");
  Serial.print(cm);
  Serial.print("cm");
  Serial.println();
  
  delay(250);// Quater second delay 
  if (cm <= 50){// conditional statement to trigger test LED
    digitalWrite(led,HIGH);//Enter relevant LCD messages here 
  Serial.print("LED, ");//Serialprints for LED states within 
    //the conditional statements
  Serial.println("On");
     myservo.write(90); //newstart post for every incriment 
    lcd.setCursor(0,1);
    lcd.print("Opening");
  }//Using a led to demonstrate a working concept of the code.
    else {
      digitalWrite(led,LOW);// Turn off when the 
      //object is not 50cm or closer 
  Serial.print("LED, ");// LED state
  Serial.println("Off");
       myservo.write(startpos); //newstart post for every incriment 
  	lcd.setCursor(0,2);
    lcd.print("Closing");
    }
  
}
