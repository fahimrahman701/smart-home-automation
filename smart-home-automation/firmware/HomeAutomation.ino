
/*
 * Home Appliances Control System
 * Arduino Uno + HC-05 Bluetooth + 4-Channel Relay Module
 *
 * Controls 4 appliances via simple ASCII commands from a phone.
 * Relays are ACTIVE LOW (LOW = ON, HIGH = OFF).
 */

#include <SoftwareSerial.h>

// Bluetooth module pins
#define BT_RX_PIN 2  // Arduino pin 2 to HC-05 TX
#define BT_TX_PIN 3  // Arduino pin 3 to HC-05 RX

// Relay control pins (mapped to appliances)
#define RELAY_RED_LIGHT   4  // Device 1
#define RELAY_SOCKET      5  // Device 2
#define RELAY_FAN         6  // Device 3
#define RELAY_PINK_LIGHT  7  // Device 4

// LED pin for status indication
#define STATUS_LED 13

// Create SoftwareSerial object for Bluetooth communication
SoftwareSerial bluetooth(BT_RX_PIN, BT_TX_PIN);

// State variables
bool fanState = false;
bool redlightState = false;
bool socketState = false;
bool pinklightState = false;

void setup() {
  Serial.begin(9600);
  bluetooth.begin(9600);

  pinMode(RELAY_RED_LIGHT, OUTPUT);
  pinMode(RELAY_SOCKET, OUTPUT);
  pinMode(RELAY_FAN, OUTPUT);
  pinMode(RELAY_PINK_LIGHT, OUTPUT);
  pinMode(STATUS_LED, OUTPUT);

  // Start with all OFF (HIGH for active-LOW relays)
  digitalWrite(RELAY_RED_LIGHT, HIGH);
  digitalWrite(RELAY_SOCKET, HIGH);
  digitalWrite(RELAY_FAN, HIGH);
  digitalWrite(RELAY_PINK_LIGHT, HIGH);
  digitalWrite(STATUS_LED, LOW);

  Serial.println(F("Home Automation System Initialized"));
  Serial.println(F("Waiting for Bluetooth commands..."));

  // Blink status LED to indicate ready
  for (int i = 0; i < 3; i++) {
    digitalWrite(STATUS_LED, HIGH);
    delay(150);
    digitalWrite(STATUS_LED, LOW);
    delay(150);
  }
}

void loop() {
  // Read from Bluetooth
  if (bluetooth.available()) {
    String cmd = bluetooth.readStringUntil('\n');
    cmd.trim();
    processCommand(cmd);
  }

  // Read from Serial (for testing)
  if (Serial.available()) {
    String cmd = Serial.readStringUntil('\n');
    cmd.trim();
    processCommand(cmd);
  }
}

void processCommand(String command) {
  String cmd = normalize(command);

  // 1) Individual controls by name
  if (cmd == "FANON" || cmd == "3ON") {
    controlRelay(RELAY_FAN, true);
    fanState = true;
    ok("Fan turned ON");
  } else if (cmd == "FANOFF" || cmd == "3OFF") {
    controlRelay(RELAY_FAN, false);
    fanState = false;
    ok("Fan turned OFF");
  }

  else if (cmd == "REDLIGHTON" || cmd == "1ON") {
    controlRelay(RELAY_RED_LIGHT, true);
    redlightState = true;
    ok("Red Light turned ON");
  } else if (cmd == "REDLIGHTOFF" || cmd == "1OFF") {
    controlRelay(RELAY_RED_LIGHT, false);
    redlightState = false;
    ok("Red Light turned OFF");
  }

  else if (cmd == "SOCKETON" || cmd == "2ON") {
    controlRelay(RELAY_SOCKET, true);
    socketState = true;
    ok("Socket turned ON");
  } else if (cmd == "SOCKETOFF" || cmd == "2OFF") {
    controlRelay(RELAY_SOCKET, false);
    socketState = false;
    ok("Socket turned OFF");
  }

  else if (cmd == "PINKLIGHTON" || cmd == "4ON") {
    controlRelay(RELAY_PINK_LIGHT, true);
    pinklightState = true;
    ok("Pink Light turned ON");
  } else if (cmd == "PINKLIGHTOFF" || cmd == "4OFF") {
    controlRelay(RELAY_PINK_LIGHT, false);
    pinklightState = false;
    ok("Pink Light turned OFF");
  }

  // 2) Group controls
  else if (cmd == "ALLON") {
    controlRelay(RELAY_RED_LIGHT, true);
    controlRelay(RELAY_SOCKET, true);
    controlRelay(RELAY_FAN, true);
    controlRelay(RELAY_PINK_LIGHT, true);
    redlightState = socketState = fanState = pinklightState = true;
    ok("All appliances turned ON");
  } else if (cmd == "ALLOFF") {
    controlRelay(RELAY_RED_LIGHT, false);
    controlRelay(RELAY_SOCKET, false);
    controlRelay(RELAY_FAN, false);
    controlRelay(RELAY_PINK_LIGHT, false);
    redlightState = socketState = fanState = pinklightState = false;
    ok("All appliances turned OFF");
  }

  // 3) Status
  else if (cmd == "STATUS") {
    sendStatus();
  }

  else {
    err("Unknown command: " + command);
  }

  // Blink LED to indicate processing
  digitalWrite(STATUS_LED, HIGH);
  delay(80);
  digitalWrite(STATUS_LED, LOW);
}

String normalize(String in) {
  in.toUpperCase();
  // Remove spaces and underscores to support variants, e.g., "RED LIGHT_ON"
  String out = "";
  for (size_t i = 0; i < in.length(); i++) {
    char c = in[i];
    if (c != ' ' && c != '_') out += c;
  }
  return out;
}

void controlRelay(int pin, bool on) {
  // Active-LOW relay: LOW = ON, HIGH = OFF
  digitalWrite(pin, on ? LOW : HIGH);
}

void ok(const String &msg) {
  bluetooth.println(msg);
  Serial.println(msg);
}

void err(const String &msg) {
  bluetooth.println("ERR: " + msg);
  Serial.println("ERR: " + msg);
}

void sendStatus() {
  String status = "STATUS:";
  status += "RedLight:" + String(redlightState ? "ON" : "OFF") + ",";
  status += "Socket:" + String(socketState ? "ON" : "OFF") + ",";
  status += "Fan:" + String(fanState ? "ON" : "OFF") + ",";
  status += "PinkLight:" + String(pinklightState ? "ON" : "OFF");
  ok(status);
}
