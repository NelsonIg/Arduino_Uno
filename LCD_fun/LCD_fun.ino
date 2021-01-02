/*
 The circuit:
 * LCD RS pin to digital pin 12
 * LCD Enable pin to digital pin 11
 * LCD D4 pin to digital pin 5
 * LCD D5 pin to digital pin 4
 * LCD D6 pin to digital pin 3
 * LCD D7 pin to digital pin 2
 * LCD R/W pin to ground
 * 10K resistor:
 * ends to +5V and ground
 * wiper to LCD VO pin (pin 3)
*/

// include the library code:
#include <LiquidCrystal.h>
#include <Time.h>


// initialize the library by associating any needed LCD interface pin
// with the arduino pin number it is connected to
const int rs = 13, en = 12, d4 = 11, d5 = 10, d6 = 9, d7 = 8;
LiquidCrystal lcd(rs, en, d4, d5, d6, d7);

//Motion Sensor
const byte motionPin = 2;
// Alarm Pin
const int lightPin = 7;
volatile byte lightState = LOW;

float calc_resistance(int refRes){
  float analogPin = A0;
  float maxVal = 1023;
  float val = analogRead(analogPin); // var to store adc value 0-1023
  return refRes*(val/(maxVal-val));
}

void setup() {
  Serial.begin(9600);
  // set up the LCD's number of columns and rows:
  lcd.begin(16, 2);
  // set up pin for motion sensor
  pinMode(lightPin, OUTPUT);
  digitalWrite(lightPin, LOW);
  pinMode(motionPin, INPUT);
  attachInterrupt(digitalPinToInterrupt(motionPin), toggleLight, RISING);
}


void loop() {
  float resistance = calc_resistance(10000);
  lcd.clear();
  lcd.print(String(resistance)+" Ohm");
  delay(200);  
}

void toggleLight(){
  lightState = !lightState; // toggle light
  Serial.print("Light: ");
  Serial.println(lightState);
  digitalWrite(lightPin,lightState); 
}
