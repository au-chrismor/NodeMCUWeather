#include "NodeWeather2.h"

int readSolar(void) {
  int val = 0;
  Wire.begin();
  lux.begin();
  val = lux.GetLightIntensity();
//  Wire.end();
  return val;
}

float readTemperature(void) {
  float val = 0.0;
  Wire.begin();
  while(!bme.begin()) {
    ;
  }
  val = bme.temp();
//  Wire.end();
  return val;
}

float readHumidity(void) {
  float val = 0.0;
  Wire.begin();
  while(!bme.begin()) {
    ;
  }
  val = bme.hum();
//  Wire.end();
  return val;
}

float readPressure(void) {
  float val = 0.0;
  Wire.begin();
  while(!bme.begin()) {
    ;
  }
  val = bme.pres() /100;
//  Wire.end();
  return val;
}

int readUV(void) {
    return map(analogRead(UV_PIN), 0, 1023, 0, (VREF * 1000));
}

void setup() {
  Serial.begin(115200);
  delay(100);


  Serial.print("Connecting to: ");
  Serial.println(ssid);
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    Serial.print(".");
    delay(500);
  }
  Serial.println("\nConnected");
  Serial.print("Got IP: ");  Serial.println(WiFi.localIP());
  Wire.begin();
  Serial.print("BME280 Init: ");
  Serial.println(bme.begin());
//  Serial.print("BH1750 Init: ");
//  Serial.print(lux.begin());

  ThingSpeak.begin(client);

  seconds = 0;
  beenReset = 1;
}

void loop() {
  if(millis() - oldTime > 1000) {
    oldTime = millis();
    seconds++;
  }
    if(seconds > 59) {
      temperature = readTemperature();
      humidity = readHumidity();
      pressure = readPressure();
      light = readSolar();
      uv = readUV();
#ifdef _DEBUG
      Serial.println("Sending update");
#endif

#ifdef _DEBUG
      Serial.print("Temperature: ");
      Serial.println(temperature);
      Serial.print("Humidity: ");
      Serial.println(humidity);
      Serial.print("Pressure: ");
      Serial.println(pressure);
      Serial.print("Light: ");
      Serial.println(light);
      Serial.print("UV: ");
      Serial.println(uv);
#endif
      ThingSpeak.setField(1, (float)temperature);
      ThingSpeak.setField(2, (float)humidity);
      ThingSpeak.setField(3, (float)pressure);
      ThingSpeak.setField(4, (float)light);
      ThingSpeak.setField(5, (float)uv);
      if(beenReset != 0) {
        ThingSpeak.setStatus("Reset: " + ESP.getResetReason());
        beenReset = 0;
      }
      ThingSpeak.writeFields(channelId, apiKey);
      seconds = 0;
    }

}
