
const int ledPin = 13;

const int motorLeft[] = {2, 4};
const int motorRight[] = {7, 8};
const int speedPinLeft = 5;
const int speedPinRight = 6;

const int echoPin = 12;
const int trigPin = 13;

const int LEFT = 0;
const int RIGHT = 1;

const float WHEEL_CIRCUMFERENCE_IN = 10.63;
const float WHEEL_BASE_IN = 6.89;
const float MOTOR_RPM_AT_9V = 55.0;

const float SECONDS_IN_MINUTE = 60.0;

long duration;
int distance;
long randomNumber;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);

  for(int i = 0; i < 2; i++) {
    pinMode(motorLeft[i], OUTPUT);
    pinMode(motorRight[i], OUTPUT);
  }

  pinMode(speedPinLeft, OUTPUT);
  pinMode(speedPinRight, OUTPUT);

  pinMode(echoPin, INPUT);
  pinMode(trigPin, OUTPUT);
  
  pinMode(ledPin, OUTPUT);

  duration = 0;
  distance = 0;

  randomSeed(analogRead(0));

}

void loop() {
  // put your main code here, to run repeatedly:

  
  
  digitalWrite(ledPin, HIGH);
  avoidObstacles();
  
  

}

void driveForwardDistance(int speed, int inches) {
  
  float secondsPerInch = 1/(MOTOR_RPM_AT_9V/SECONDS_IN_MINUTE*WHEEL_CIRCUMFERENCE_IN);

  analogWrite(speedPinLeft, speed);
  analogWrite(speedPinRight, speed);

  digitalWrite(motorLeft[0], HIGH);
  digitalWrite(motorLeft[1], LOW);

  digitalWrite(motorRight[0], HIGH);
  digitalWrite(motorRight[1], LOW);

  float delayMilli = ((float)inches * secondsPerInch) * (255/speed) * 1000;

  Serial.print(secondsPerInch);
  Serial.print(", ");
  Serial.print(delayMilli);
  Serial.print(", ");
  Serial.println((int)delayMilli);
  
  delay((int)delayMilli);

}

void turnDegrees(int direction, float degrees) {

  //43.29" turn circumference

  float turnCircumference = 2*PI*WHEEL_BASE_IN;
  float inchesPerDegree = turnCircumference/360;
  
  float secondsPerInch = 1/(MOTOR_RPM_AT_9V/SECONDS_IN_MINUTE*WHEEL_CIRCUMFERENCE_IN);
  float secondsPerDegree = inchesPerDegree * secondsPerInch;

  analogWrite(speedPinLeft, direction=LEFT?0:255);
  analogWrite(speedPinRight, direction=RIGHT?0:255);

  digitalWrite(motorLeft[0], direction=LEFT?LOW:HIGH);
  digitalWrite(motorLeft[1], LOW);

  digitalWrite(motorRight[0], direction=LEFT?LOW:HIGH);
  digitalWrite(motorRight[1], LOW);

  

  float delayMillis = degrees * secondsPerDegree *1000;

  Serial.print(degrees);
  Serial.print(", ");
  Serial.println(delayMillis);

  delay(delayMillis);
}

void avoidObstacles() {

  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  // Sets the trigPin HIGH (ACTIVE) for 10 microseconds
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);
  // Reads the echoPin, returns the sound wave travel time in microseconds
  duration = pulseIn(echoPin, HIGH);
  // Calculating the distance
  distance = duration * 0.034;

  Serial.print("Distance: ");
  Serial.print(distance);
  Serial.println(" cm");


  if(distance > 15) {

    digitalWrite(speedPinLeft, HIGH);
    digitalWrite(speedPinRight, HIGH);

    digitalWrite(motorLeft[0], HIGH);
    digitalWrite(motorLeft[1], LOW);

    digitalWrite(motorRight[0], HIGH);
    digitalWrite(motorRight[1], LOW);
    
  } else {

    digitalWrite(speedPinLeft, LOW);
    digitalWrite(speedPinRight, LOW);

    delay(500);

    digitalWrite(speedPinLeft, HIGH);
    digitalWrite(speedPinRight, HIGH);

    digitalWrite(motorLeft[0], LOW);
    digitalWrite(motorLeft[1], HIGH);

    digitalWrite(motorRight[0], LOW);
    digitalWrite(motorRight[1], HIGH);

    delay(750);

    randomNumber = random(100);

    if(randomNumber < 50 ) {
      digitalWrite(motorLeft[0], LOW);
      digitalWrite(motorLeft[1], HIGH);

      digitalWrite(motorRight[0], HIGH);
      digitalWrite(motorRight[1], LOW);
      
    } else {
      digitalWrite(motorLeft[0], HIGH);
      digitalWrite(motorLeft[1], LOW);

      digitalWrite(motorRight[0], LOW);
      digitalWrite(motorRight[1], HIGH);
    }
    delay(1000);
  }
  
}
