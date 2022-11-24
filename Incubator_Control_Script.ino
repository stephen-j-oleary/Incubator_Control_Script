
#include <string>
#include <map>

#include <WiFiClient.h>
#include <ESP8266WiFi.h>
#include <ESP8266WebServer.h>
#include <DHTesp.h>

#include "htmlPage.h"
#include "PinState.h"
#include "Scheduler.h"
#include "TempMonitor.h"
#include "env.h"

// Pins
#define DHT_PIN D7
#define HEAT_TAPE_PIN D5

// Network config
const char * DEVICE_NAME = "Incubator"; /* Name the device on your network */
const IPAddress STATIC_IP(192, 168, 0, 200); /* Configure a static ip for the device */
const IPAddress GATEWAY(192, 168, 0, 1);
const IPAddress DNS(8, 8, 8, 8);

// Global variables
Scheduler scheduler;
DHTesp dht;
ESP8266WebServer server(80); // The web server responsible for creating the control panel page
std::map<std::string, PinState> state; // Hold the state of the pins and the dht readings

void initializeState() {
  state["INDICATOR_LIGHT"] = PinState(false);
  state["HEAT_TAPE"] = PinState(false);
  state["EXPECTED_INTERNAL_TEMPERATURE"] = PinState(37.5f);
}

// Read the state of input pins
void readPins() {
  float t = dht.getTemperature();
  state["INTERNAL_TEMPERATURE"] = PinState(t);

  float h = dht.getHumidity();
  state["INTERNAL_HUMIDITY"] = PinState(h);
}

// Set state of output pins
void setPins() {
  digitalWrite(LED_BUILTIN, (state["INDICATOR_LIGHT"].boolValue) ? LOW : HIGH); // HIGH = off, LOW = on
  digitalWrite(HEAT_TAPE_PIN, (state["HEAT_TAPE"].boolValue) ? HIGH : LOW);
}

// Set pin modes
void initializePinModes() {
  pinMode(LED_BUILTIN, OUTPUT);
  pinMode(DHT_PIN, INPUT_PULLUP);
  pinMode(HEAT_TAPE_PIN, OUTPUT);
}

// Initialize the network settings and connection
void initializeWifi() {
  WiFi.mode(WIFI_STA);
  WiFi.hostname(DEVICE_NAME);
  WiFi.begin(NETWORK_SSID, NETWORK_PASSWORD);

  Serial.println(F(""));
  Serial.println(F("Configuring wifi"));
  while (!WiFi.config(STATIC_IP, DNS, GATEWAY)) {
    delay(100);
    Serial.print(F("."));
  }

  Serial.println(F(""));
  Serial.print(F("Connecting to "));
  Serial.println(NETWORK_SSID);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(F("."));
  }
  Serial.println(F(""));
  Serial.print(F("IP address: "));
  Serial.println(WiFi.localIP());
}

// Replace template variables in html page
String processHtml() {
  String s = htmlPage;
  s.replace("{{INDICATOR_LIGHT}}", (state["INDICATOR_LIGHT"].boolValue) ? "ON" : "OFF");
  s.replace("{{INTERNAL_TEMPERATURE}}", String(state["INTERNAL_TEMPERATURE"].floatValue));
  s.replace("{{INTERNAL_HUMIDITY}}", String(state["INTERNAL_HUMIDITY"].floatValue));
  s.replace("{{HEAT_TAPE}}", (state["HEAT_TAPE"].boolValue) ? "ON" : "OFF");
  s.replace("{{EXPECTED_INTERNAL_TEMPERATURE}}", String(state["EXPECTED_INTERNAL_TEMPERATURE"].floatValue));
  return s;
}

// Serve html page
void handleRoot() {
  if (server.args() > 0) {
    for (int i = 0; i < server.args(); i++) {
      if (server.argName(i) == "EXPECTED_INTERNAL_TEMPERATURE") {
        state["EXPECTED_INTERNAL_TEMPERATURE"] = server.arg(i).toFloat();
      }
    }
  }

  server.send(200, "text/html", String(processHtml()));
}

// Toggle indicator light
void handleIndicatorLightToggle() {
  state["INDICATOR_LIGHT"].toggleBoolValue();

  server.sendHeader("Location", String("/"), true);
  server.send(302, "text/plain", "");
}

// Toggle heat tape
void handleHeatTapeToggle() {
  state["HEAT_TAPE"].toggleBoolValue();

  server.sendHeader("Location", String("/"), true);
  server.send(302, "text/plain", "");
}

// Turn on heat tape
void raiseTemperature() {
  state["HEAT_TAPE"].setBoolValue(true);
}

// Turn off heat tape
void lowerTemperature() {
  state["HEAT_TAPE"].setBoolValue(false);
}

void noOp() {}

// Monitor the temperature state value and change heat tape state accordingly
void monitorTemperature() {
  tempMonitor(state["INTERNAL_TEMPERATURE"].floatValue, state["EXPECTED_INTERNAL_TEMPERATURE"].floatValue, &raiseTemperature, &lowerTemperature, &noOp);
}

// Arduino setup function
void setup(void) {
  Serial.begin(115200);

  initializePinModes();
  initializeState();

  dht.setup(DHT_PIN, DHTesp::DHT22);

  initializeWifi();

  // Initialize the web server
  server.on("/", handleRoot);
  server.on("/indicator-light/toggle", handleIndicatorLightToggle);
  server.on("/heat-tape/toggle", handleHeatTapeToggle);
  server.begin();
  Serial.println(F("Server started"));
}

// Arduino loop function
void loop(void) {
  server.handleClient();

  scheduler.every(10000, "readPins", readPins);
  scheduler.every(10000, "monitorTemperature", monitorTemperature);
  setPins();
}
