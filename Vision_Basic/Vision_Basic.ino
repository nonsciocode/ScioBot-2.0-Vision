    Copyright (C) 2021  Nonscio, LLC
    This program is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with this program.  If not, see <https://www.gnu.org/licenses/>.

//================================================================================
//CONSTANTS
//================================================================================

const int motorRightA = 2;
const int motorRightB = 4;
const int motorLeftA = 7;
const int motorLeftB = 8;
const int enableRight = 5;
const int enableLeft = 6; 

const int echoPin = 12; //NEW* Define the Echo Pin
const int trigPin = 13; //NEW* Define the Trig Pin

//================================================================================
//VARIABLES
//================================================================================

long duration;          //NEW* Define a variable to hold the ping duration
int distance;           //NEW* Define a variable to hold the distance value
long randomNumber;      //NEW* Define a variable to hold a random value

//================================================================================
//FUNCTIONS
//================================================================================

/**
 * Function: setup()
 * Description: The setup() function runs once after the microcontroller is 
 * booted or reset. Sets the pin modes of the defined motor logic pin to OUTPUT
 * mode. Sets the echoPin as INPUT and the trigPin as OUTPUT. Initializes
 * distance and duration as 0. Initializes rand function, and serial monitor for
 * debugging.
 */

void setup() {
  
  pinMode(motorRightA, OUTPUT);
  pinMode(motorRightB, OUTPUT);
  pinMode(motorLeftA, OUTPUT);
  pinMode(motorLeftB, OUTPUT);
  pinMode(enableRight, OUTPUT);
  pinMode(enableLeft, OUTPUT);

  pinMode(echoPin, INPUT);    //NEW* Set Echo Pin as INPUT
  pinMode(trigPin, OUTPUT);   //NEW* Set Trig Pin as OUTPUT

  duration = 0;               //NEW* Initilize duration as 0
  distance = 0;               //NEW* Initilize distance as 0

  randomSeed(analogRead(0));  //NEW* Initilize rand function with seed

  Serial.begin(9600);

}

/**
 * Function: loop()
 * Description: The loop() function runs repeatedly in a loop after the setup()
 * function has completed. Executes code to operate the Ultrasonic sensor,
 * interpret sensor data and make and execute descisions based on sensor data.
 */

void loop() {
  // put your main code here, to run repeatedly:

  digitalWrite(trigPin, LOW);          //Clears the Trig Pin
  delayMicroseconds(2);                //Wait for clear
  digitalWrite(trigPin, HIGH);         //Set the Trig Pin to HIGH
  delayMicroseconds(10);               //Leave on HIGH for 10 μs
  digitalWrite(trigPin, LOW);          //End Ping by setting trig pin to LOW  
  duration = pulseIn(echoPin, HIGH);   //Reads the Echo Pin and returns the duration of sound wave travel
  distance = duration * 0.034 / 2;     //Calculate the speed of the sound wave and divide by 2 (out and back)

  Serial.print("Distance: ");
  Serial.println(distance);

  if(distance > 15) {                  //If the distance is more than 15cm

    digitalWrite(enableLeft, HIGH);    //Configure the motors to go forward
    digitalWrite(enableRight, HIGH);

    digitalWrite(motorLeftA, HIGH);
    digitalWrite(motorLeftB, LOW);

    digitalWrite(motorRightA, HIGH);
    digitalWrite(motorRightB, LOW);
    
  } else {                              //Otherwise

    digitalWrite(enableLeft, LOW);      //Stop
    digitalWrite(enableRight, LOW);

    delay(500);                         //Wait 1/2 second (500ms)

    digitalWrite(enableLeft, HIGH);   //Configure the motors to reverse
    digitalWrite(enableRight, HIGH);

    digitalWrite(motorLeftA, LOW);
    digitalWrite(motorLeftB, HIGH);

    digitalWrite(motorRightA, LOW);
    digitalWrite(motorRightB, HIGH);

    delay(750);                         //Reverse for 750 ms

    digitalWrite(enableLeft, LOW);      //Stop
    digitalWrite(enableRight, LOW);

    delay(500);                         //Wait 1/2 second (500ms)



    randomNumber = random(100);         //Generate a random number between 0 and 100

    if(randomNumber < 50 ) {            //If rand is less than 50
      digitalWrite(motorLeftA, LOW);    //Configure the motors to turn Left
      digitalWrite(motorLeftB, HIGH);

      digitalWrite(motorRightA, HIGH);
      digitalWrite(motorRightB, LOW);
      
    } else {                            //Otherwise
      digitalWrite(motorLeftA, HIGH);   //Configure the motors to turn Left
      digitalWrite(motorLeftB, LOW);

      digitalWrite(motorRightA, LOW);
      digitalWrite(motorRightB, HIGH);
    }

    digitalWrite(enableLeft, HIGH);
    digitalWrite(enableRight, HIGH);
    
    delay(1000);                        //Turn for 1 second

    digitalWrite(enableLeft, LOW);      //Stop
    digitalWrite(enableRight, LOW);

    delay(500);                         //Wait 1/2 second (500ms)
  }
}
