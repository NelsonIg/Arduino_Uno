/*
 * Pins for ESP82666  LCD1601 (0x27) BMP280 (0x76)
 *            Vin       VCC           VIN
 *            GND       GND           GND
 *            D2        SDA           SDA
 *            D1        SCL           SCL
*/

#include <Adafruit_Sensor.h>
#include <Adafruit_BME280.h>

#include <LiquidCrystal_I2C.h>
#include <ESP8266WiFi.h>
#include "secrets.h"


const String ssid = STASSID;
const String key  = STAPSK;

unsigned int localPort = 8888;      // local port to listen on

LiquidCrystal_I2C lcd(0x27,16,2);  // set the LCD address to 0x27 for a 16 chars and 2 line display
Adafruit_BME280 bme; // I2C


void setup()
{
  Serial.begin(9600);
  
  lcdInit();
  wifiInit();
  sensorInit();
  
}


void loop()
{
  delay(5000);
  printValues();
  printValuesLCD();
  delay(5000);
  printHostIp();
  
}

void wifiInit(){
  lcd.setCursor(0,1);
  lcd.print("Connecting");
  WiFi.mode(WIFI_STA);
  WiFi.begin(ssid, key);
  while (WiFi.status() != WL_CONNECTED) {
    Serial.print('.');
    lcd.print('.');
    delay(500);
  }
  Serial.print("Connected! IP address: ");
  Serial.println(WiFi.localIP());
  Serial.printf("UDP server on port %d\n", localPort);
  printHostIp();
}

void lcdInit(){
  lcd.begin(16,2);                      // initialize the lcd 
  lcd.init();
  lcd.backlight();
  lcd.print("LCD Test");
}
void printHostIp(){
  lcd.clear();
  lcd.setCursor(0,0);
  lcd.print(WiFi.localIP());
  lcd.setCursor(0,1);
  lcd.print("Port:");
  lcd.print(localPort);
}

void sensorInit(){
  unsigned status;
  status = bme.begin(0x76);
    if (!status) {
        Serial.println("Could not find a valid BME280 sensor, check wiring, address, sensor ID!");
        Serial.print("SensorID was: 0x"); Serial.println(bme.sensorID(),16);
        Serial.print("        ID of 0xFF probably means a bad address, a BMP 180 or BMP 085\n");
        Serial.print("   ID of 0x56-0x58 represents a BMP 280,\n");
        Serial.print("        ID of 0x60 represents a BME 280.\n");
        Serial.print("        ID of 0x61 represents a BME 680.\n");
        while (1) delay(10);
    }
    
    Serial.println("-- Default Test --");
    Serial.println();
}

void printValues() {
    Serial.print("Temperature = ");
    Serial.print(bme.readTemperature());
    Serial.println(" °C");

    Serial.print("Humidity = ");
    Serial.print(bme.readHumidity());
    Serial.println(" %");

    Serial.println();
}

void printValuesLCD(){
  lcd.clear();
  lcd.setCursor(0,0);
  lcd.print(bme.readTemperature(),1);
  lcd.print((char)223); // Degree sign "°"
  lcd.print("C");
  lcd.setCursor(0,1);
  lcd.print(bme.readHumidity(),1);
  lcd.print("% Humidity");
}
