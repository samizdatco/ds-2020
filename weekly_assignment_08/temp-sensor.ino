// DHT Temperature & Humidity Sensor
// Unified Sensor Library Example
// Written by Tony DiCola for Adafruit Industries
// Released under an MIT license.

// REQUIRES the following Arduino libraries:
// - DHT Sensor Library: https://github.com/adafruit/DHT-sensor-library
// - Adafruit Unified Sensor Lib: https://github.com/adafruit/Adafruit_Sensor

#include <Adafruit_Sensor.h>
#include <DHT.h>
#include <DHT_U.h>

#define DHTPIN 2     // Digital pin connected to the DHT sensor
// Feather HUZZAH ESP8266 note: use pins 3, 4, 5, 12, 13 or 14 --
// Pin 15 can work but DHT must be disconnected during program upload.

// Uncomment the type of sensor in use:
//#define DHTTYPE    DHT11     // DHT 11
#define DHTTYPE    DHT22     // DHT 22 (AM2302)
//#define DHTTYPE    DHT21     // DHT 21 (AM2301)

// See guide for details on sensor wiring and usage:
//   https://learn.adafruit.com/dht/overview

// Create the DHT22 temperature sensor object
DHT_Unified dht(DHTPIN, DHTTYPE);

// Define a global variable to store temperature readings
double temperature;

void setup()
{
  // Initialize device.
  dht.begin();

  // sensor takes 250 ms to get first readings
  delay(500);

  // bind the temperature global to a Particle variable
  Particle.variable("tempsensor", &temperature, DOUBLE);
}

void loop()
{
  // Read the temp in C and convert to F
  sensors_event_t event;
  dht.temperature().getEvent(&event);
  if (!isnan(event.temperature)) {
    double c = event.temperature;
    double f = (c * 9 / 5) + 32;

    // store the current temp in our global variable
    temperature = f;
  }

  dht.humidity().getEvent(&event);
  if (!isnan(event.relative_humidity)) {
    // optionally do something with event.relative_humidity...
  }

  // pause before taking the next reading
  delay(500);
}
