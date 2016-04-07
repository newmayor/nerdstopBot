/*
Nerdstop Robotics Workshop
Built by: Numair Ahmed - April 2016

VERSION CONTROL:
4/5/2016 - Initial code outline with new motor driver header file
4/6/2016 - Include ultrasonic sensor implementation
4/7/2016 - Changed motor frequency to syn with sensor data feed freqeuncy


*/

#include <AFMotor.h>


#define echoPin 6
#define trigPin 7

char user_input;

AF_DCMotor motor1(1, MOTOR12_64KHZ);
AF_DCMotor motor2(2, MOTOR12_64KHZ);



void setup() {
  Serial.begin (9600);
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
 // pinMode(led, OUTPUT);//
 // pinMode(led2, OUTPUT);//

}

void loop() {
  long duration, distance;
  digitalWrite(trigPin, LOW);  // Added this line
  delayMicroseconds(2); // Added this line
  digitalWrite(trigPin, HIGH);
//  delayMicroseconds(1000); - Removed this line
  delayMicroseconds(10); // Added this line
  digitalWrite(trigPin, LOW);
  duration = pulseIn(echoPin, HIGH);
  distance = (duration/2) / 29.1;
  if (distance < 40) {  // This is where the LED On/Off happens
     motor1.setSpeed(50);
     motor2.setSpeed(100);
      //"distance < 40" = object is too close
      Serial.println("Object detected within 40 centimeters if robot\n");
      motor1.run(RELEASE);  //stop motors
      motor2.run(RELEASE);  //stop motors

      Serial.println("Reversing robot to avoid object\n");
      motor1.run(BACKWARD);  //move robot backward
      motor2.run(FORWARD);  //move robot backward
      Serial.println("Object is now more than 40 centimeters away\n");
//     digitalWrite(led,HIGH); // When the Red condition is met, the Green LED should turn off
  //   digitalWrite(led2,LOW);
}
  else {
    Serial.println("Speed up and begin moving forward");
      motor1.run(100);
      motor2.run(100);

      motor1.run(FORWARD);
      motor2.run(BACKWARD);
   // digitalWrite(led,LOW);
   // digitalWrite(led2,HIGH);
  }
  if (distance >= 200 || distance <= 0){
    motor1.setSpeed(100);
      motor2.setSpeed(100);
      Serial.print("Out of Range");
      motor1.run(BACKWARD);
      motor2.run(FORWARD);
  }
  else {
    Serial.print(distance);
    Serial.println(" cm");
  }
  delay(500);
}
