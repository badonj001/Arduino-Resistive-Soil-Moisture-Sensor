/* 
 Arduino Resistive Soil Moisture Sensor 
 Amazon Product ID: B076DDWDJK 
 Link: https://www.amazon.com/Icstation-Resistive-Soil-Moisture-Sensor/dp/B076DDWDJK/ref=sr_1_1?dchild=1&keywords=B076DDWDJK&qid=1595666070&sr=8-1
 Created on 25 July 2020 
 by /chaoren a.k.a. badonj001

 Measurement Made With "MY" Probe DRY and WET 
 Ensure you calibrate Using your probe and board.
 Analog_DRY = 1023.10 //Probe Pins out of water and dried.
 Analog_WET = 70.37   //Probe Pins submerged in water with a little sports drink mixed in to increase conductivity.
 Analog_Conversion_Factor = ((Analog_DRY - Analog_WET) / 100)
 Caluculation for Moisture Percentage = (100 - ((MeasuredAnalogValue - Analog_WET) / Analog_Conversion_Factor))
*/

//Define Measurement Pins
#define SensorPinA A0 //Analog Pin A0 on Arduino
#define SensorPinD 2  //Digital Pin 2 on Arduino

//Create Analog and Digital Measurement Variables
float sensorValueA = 0; 
float sensorValueD = 0; 

//Specify number of measurements to acquire in a sample
int numMeasurements = 10000;


//Specify Probe DRY and WET Values for Percentage Calculation.
float analog_DRY = 1023.10; 
float analog_WET = 70.37;
float analog_Conversion_Factor = ((analog_DRY - analog_WET) / 100);


void setup() { 
  //Initialize serial and wait for port to open:
  Serial.begin(9600);
  while (!Serial) {
    ; // wait for serial port to connect. Needed for native USB
  }

  //Initialize Digital Measurement Pin
  pinMode(SensorPinD, INPUT);
} 


void loop() { 

 //Reset Analog and Digital Measurement Variables to Zero Before Using them
 sensorValueA = 0;
 sensorValueD = 0;

 //Acquire measurements desired using numMeasurements
 for (int i = 0; i <= numMeasurements; i++) 
 { 
   sensorValueA += analogRead(SensorPinA);
   sensorValueD += analogRead(SensorPinD); 
   delay(1); 
 } 

 //Average Collected Measurements usingnumMeasurements
 sensorValueA = sensorValueA/numMeasurements; 
 sensorValueD = sensorValueD/numMeasurements; 

//Print Analog Reading of Moisture Level 
 Serial.print("A: ");
 Serial.println(sensorValueA);

//Print Digital Reading of Moisture Level
 Serial.print("D: ");
 Serial.println(sensorValueD);

//Print Percentage Value of Moisture Level
 Serial.print("Moisture: ");
 Serial.print(abs(100 - ((sensorValueA - analog_WET) / analog_Conversion_Factor)));
 Serial.println("%");
 
 delay(30); 
} 
