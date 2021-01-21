/** Copyright (C) 2021  Nonscio, LLC
 *  This program is free software: you can redistribute it and/or modify
 *   it under the terms of the GNU General Public License as published by
 *  the Free Software Foundation, either version 3 of the License, or
 *  (at your option) any later version.
 *
 *  This program is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU General Public License for more details.
 *
 *  You should have received a copy of the GNU General Public License
 *  along with this program.  If not, see <https://www.gnu.org/licenses/>.
 */

//================================================================================
//CONSTANTS
//================================================================================

const int motorRightA = 2;
const int motorRightB = 4;
const int motorLeftA = 7;
const int motorLeftB = 8;
int enableRight = 5;
int enableLeft = 6; 

const int outputPin = 12;

//================================================================================
//VARIABLES
//================================================================================


//================================================================================
//FUNCTIONS
//================================================================================

/**
 * Function: setup()
 * Description: The setup() function runs once after the microcontroller is 
 * booted or reset. Sets the pin modes of the defined motor logic pin to OUTPUT
 * mode. Sets the IR Sensor OUT pin as INPUT. Initializes serial monitor for
 * debugging.
 */

void setup() {
  
  pinMode(motorRightA, OUTPUT);
  pinMode(motorRightB, OUTPUT);
  pinMode(motorLeftA, OUTPUT);
  pinMode(motorLeftB, OUTPUT);
  pinMode(enableRight, OUTPUT);
  pinMode(enableLeft, OUTPUT);

  pinMode(outputPin, INPUT);

  Serial.begin(9600);

}

/**
 * Function: loop()
 * Description: The loop() function runs repeatedly in a loop after the setup()
 * function has completed. Executes code to operate the Infrared sensor,
 * interpret sensor data and make and execute descisions based on sensor data.
 */

void loop() {

  if(digitalRead(outputPin)) {        //

    digitalWrite(enableLeft, LOW);    //Configure the motors to go left
    digitalWrite(enableRight, HIGH);

    digitalWrite(motorLeftA, LOW);
    digitalWrite(motorLeftB, LOW);

    digitalWrite(motorRightA, HIGH);
    digitalWrite(motorRightB, LOW);
    
  } else {

    digitalWrite(enableLeft, HIGH);    //Configure the motors to go right
    digitalWrite(enableRight, LOW);

    digitalWrite(motorLeftA, HIGH);
    digitalWrite(motorLeftB, LOW);

    digitalWrite(motorRightA, LOW);
    digitalWrite(motorRightB, LOW);
    
  }
}
