#include <ThingSpeak.h>
#include <ESP8266WiFi.h>
#include <Wire.h>
#include <BME280.h>
#include <BME280I2C.h>
#include <BH1750FVI.h>

#define _DEBUG

#define SEALEVELPRESSURE_HPA (1013.25)
#define UV_PIN A0
#define VREF 3.30

BME280I2C bme;

WiFiClient client;

uint8_t ADDRESSPIN = D0;
BH1750FVI::eDeviceAddress_t DEVICEADDRESS = BH1750FVI::k_DevAddress_H;
BH1750FVI::eDeviceMode_t DEVICEMODE = BH1750FVI::k_DevModeContHighRes;

BH1750FVI lux(ADDRESSPIN, DEVICEADDRESS, DEVICEMODE);

float temperature, humidity, pressure, light;
unsigned long oldTime;
unsigned int seconds, uv;
unsigned int beenReset;

/*Put your SSID & Password*/
const char* ssid = "Your_SSID";  // Enter SSID here
const char* password = "Your_Clever_Password";  //Enter Password here

// ThingSpeak Settings
const char *server = "api.thingspeak.com";
const char *  apiKey ="XXXXXXXXXXXXXXXX";
unsigned long channelId = 000000;
