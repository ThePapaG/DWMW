#include <Servo.h>

/*
 * Define motor pins
 */
//Motor A
#define mA      3
#define mAin1   2
#define mAin2   4
//Motor B
#define mB      6
#define mBin1   5
#define mBin2   7

/*
 * Define ultrasonic sensor
 */
#define trigPin 8
#define echoPin 9

/*
 * Servo defines
 */
#define servoPin  10
#define servoMax  160
#define servoMin  20
#define RESOLUTION  10
Servo servoMotor;
int servoAngle;
int servoDir;

/*
 * This function is to set the speed of two motors.
 * Parameters should be [-1,1] where sign denotes direction
 * (-ve reverse).
 */
void driveMotors(double motorA, double motorB){

  /*
   * bound values to [-1, 1]
   * if absolute value is greater than 1
   *  then = 1 * sgn (0=0 and will stop)
   *  else continue
   */
  motorA = abs(motorA)>1? 1*(motorA/abs(motorA)): motorA;
  motorB = abs(motorB)>1? 1*(motorB/abs(motorB)): motorB;
  
  if(motorA>0){
    //Switch to forward
    digitalWrite(mAin1, LOW);
    digitalWrite(mAin2, HIGH);
  }else if(motorA<0){
    //Switch to forward
    digitalWrite(mAin1, HIGH);
    digitalWrite(mAin2, LOW);
  }else{
    //Kill
    digitalWrite(mAin1, LOW);
    digitalWrite(mAin2, LOW);
  }

  if(motorB>0){
    //Switch to forward
    digitalWrite(mBin1, LOW);
    digitalWrite(mBin2, HIGH);
  }else if(motorB<0){
    //Switch to forward
    digitalWrite(mBin1, HIGH);
    digitalWrite(mBin2, LOW);
  }else{
    //Kill
    digitalWrite(mBin1, LOW);
    digitalWrite(mBin2, LOW);
  }

  analogWrite(mA, abs(motorA)*255);
  analogWrite(mB, abs(motorB)*255);
}
double readSensor(){

  /*
   * Read sensor here after moving the servo
   */
  // Clears the trigPin
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  
  // Sets the trigPin on HIGH state for 10 micro seconds
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);
  
  // Reads the echoPin, returns the sound wave travel time in microseconds
  return pulseIn(echoPin, HIGH) * (0.034/2);
}

//void moveServo(){
//  
//  /*
//   * Rotate Sensor
//   */
//  if(servoDir > 0){
//    servoAngle += RESOLUTION;
//
//    if(servoAngle > servoMax){
//      servoAngle = servoMax;
//      servoDir *= -1;
//    }
//  }else if(servoDir < 0){
//    servoAngle -= RESOLUTION;
//
//    if(servoAngle < servoMin){
//      servoAngle = servoMin;
//      servoDir *= -1;
//    }
//  }
//
//  servoMotor.write(servoAngle);
//}

void setup() {

  //setup motor pins
  pinMode(mA, OUTPUT);
  pinMode(mAin1, OUTPUT);
  pinMode(mAin2, OUTPUT);

  pinMode(mB, OUTPUT);
  pinMode(mBin1, OUTPUT);
  pinMode(mBin2, OUTPUT);

  //setup sensor pins
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);

  randomSeed(analogRead(0));

//  //setup servo
//  servoMotor.attach(servoPin);
//  servoAngle = servoMin;
//  servoDir = 1;
//  servoMotor.write(0);
//  servoMotor.write(servoAngle);

  //setup Serial
  Serial.begin(9600);
}

void loop() {
  if(readSensor()<25){
    Serial.println("I can't see! ");
    Serial.println(readSensor());
    driveMotors(0.8, -0.8);
  }else{
    Serial.println("I know the way");
    driveMotors(0.8,0.8);
  }
}
