// This #include statement was automatically added by the Particle IDE.
#include "Adafruit_DHT_Particle.h"

// Example testing sketch for various DHT humidity/temperature sensors
// Written by ladyada, public domain

#define DHTPIN D2     // what pin we're connected to
#define DHTTYPE DHT22 // the sensor model ID: DHT 22 (AM2302)

// Connect pin 1 (on the left) of the sensor to +5V
// Connect pin 2 of the sensor to whatever your DHTPIN is
// Connect pin 4 (on the right) of the sensor to GROUND
// Connect a 10K resistor from pin 2 (data) to pin 1 (power) of the sensor

double tempF = 0;

DHT dht(DHTPIN, DHTTYPE);

void setup() {
  Serial.begin(9600);
  Serial.println("DHT22 initialized");

  Particle.publish("state", "DHT22 initialized");
  Particle.variable("temp", tempF);

  dht.begin();
  delay(2000);
}

void loop() {
  // Wait a couple seconds between measurements.
  delay(2000);

  // Reading temperature or humidity takes about 250 milliseconds!
  // Sensor readings may also be up to 2 seconds 'old' (its a very slow sensor)
  float h = dht.getHumidity();
  float t = dht.getTempCelcius();   // Read temperature as Celsius
  float f = dht.getTempFarenheit(); // Read temperature as Farenheit

  tempF = f;

  // check if any reads failed and exit early (to try again).
  if (isnan(h) || isnan(t) || isnan(f)) {
    Serial.println("Failed to read from DHT sensor!");
    return;
  }

  // Compute heat index
  float hi = dht.getHeatIndex();
  float dp = dht.getDewPoint();
  float k = dht.getTempKelvin();

  // log the readings to the console
  Serial.print("Humid: ");
  Serial.print(h);
  Serial.print("% - ");
  Serial.print("Temp: ");
  Serial.print(t);
  Serial.print("*C ");
  Serial.print(f);
  Serial.print("*F ");
  Serial.print(k);
  Serial.print("*K - ");
  Serial.print("DewP: ");
  Serial.print(dp);
  Serial.print("*C - ");
  Serial.print("HeatI: ");
  Serial.print(hi);
  Serial.println("*C");
  Serial.println(Time.timeStr());

  // combine the various numbers into a valid JSON string and publish it
  Particle.publish("readings", String::format("{\"Hum(\%)\": %4.2f, \"Temp(°C)\": %4.2f, \"DP(°C)\": %4.2f, \"HI(°C)\": %4.2f}", h, t, dp, hi));
}
