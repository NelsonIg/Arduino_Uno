/*
 * Pins for ESP82666  LCD1601
 *            Vin       VCC
 *            GND       GND
 *            D2        SDA
 *            D1        SCL
*/
//#include <Wire.h> 
#include <LiquidCrystal_I2C.h>
#include <ESP8266WiFi.h>
#include "secrets.h"

/*#ifndef STASSID
#define STASSID STASSID
#define STAPSK  STAPSK
#endif*/

const String ssid = STASSID;
const String key  = STAPSK;

unsigned int localPort = 8888;      // local port to listen on

LiquidCrystal_I2C lcd(0x27,16,2);  // set the LCD address to 0x27 for a 16 chars and 2 line display


void lcdInit(){
  lcd.begin(16,2);                      // initialize the lcd 
  lcd.init();
  lcd.backlight();
}
void printHostIp(){
  lcd.clear();
  lcd.setCursor(0,0);
  lcd.print(WiFi.localIP());
  lcd.setCursor(0,1);
  lcd.print("Port:");
  lcd.print(localPort);
}
void setup()
{
  Serial.begin(115200);
  WiFi.mode(WIFI_STA);
  WiFi.begin(ssid, key);
  while (WiFi.status() != WL_CONNECTED) {
    Serial.print('.');
    delay(500);
  }
  Serial.print("Connected! IP address: ");
  Serial.println(WiFi.localIP());
  Serial.printf("UDP server on port %d\n", localPort);

  lcdInit();
  printHostIp();
  pinMode(D0, OUTPUT); // Setzt den Pin als output.
}


void loop()
{
  digitalWrite(D0, HIGH);
}
