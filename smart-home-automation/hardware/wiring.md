
# Wiring Guide

> **Important:** Most relay boards are **active LOW**: `LOW = Relay ON` (appliance ON).

## Connections

- **HC‑05 → Arduino**
  - HC‑05 TX → D2 (Arduino RX for SoftwareSerial)
  - HC‑05 RX → D3 (Arduino TX for SoftwareSerial) *(use a voltage divider to drop 5V → 3.3V)*
  - VCC → 5V, GND → GND
- **Relays → Arduino**
  - IN1 (Red Light)  → D4
  - IN2 (Socket)     → D5
  - IN3 (Fan)        → D6
  - IN4 (Pink Light) → D7
  - VCC → 5V, GND → GND
- **Status LED**: D13 (on-board LED)

> Always respect electrical safety. Keep the high‑voltage relay side isolated. If unsure, ask a qualified person.
