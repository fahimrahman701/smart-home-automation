
# Smart Home Automation — Arduino + Bluetooth

![Cover](assets/cover.svg)

[![Arduino](https://img.shields.io/badge/Arduino-Uno-00979D?logo=arduino&logoColor=white)](#)
[![Platform](https://img.shields.io/badge/HC--05-Bluetooth-blue)](#)
[![Relays](https://img.shields.io/badge/Relays-4--Channel-orange)](#)
[![License: MIT](https://img.shields.io/badge/License-MIT-green.svg)](LICENSE)

Control a **fan**, **red light**, **pink light**, and **power socket** from your phone over Bluetooth (HC‑05) with an **Arduino Uno** and a **4‑channel relay**. This repo includes the **firmware**, **wiring guides**, and a downloadable copy of the **final project report**.

> Based on the *Final IoT Project Report* for CSE234 (Embedded Systems & IoT Lab), Daffodil International University. See `docs/Final-IoT-Project-Report.pdf` for details.

---

## ✨ Features

- Bluetooth control via **HC‑05** (≈ 10m line‑of‑sight range)
- Simple & readable Arduino firmware with clear **command reference**
- **Active‑LOW** relay handling with safe startup (all appliances OFF)
- Status query (`STATUS`) returns the state of each appliance
- Ready‑to‑fork structure: docs, issue templates, code of conduct, etc.

## 🧱 Architecture

```mermaid
flowchart LR
  A[Android Phone<br/>Bluetooth Terminal] -- "ASCII commands" --> B{{HC-05<br/>Bluetooth Module}}
  B <-- "Serial @9600" --> C[Arduino Uno]
  C -- "Pins 4,5,6,7" --> D[4-Channel Relay]
  D --> L1[Red Light]
  D --> L2[Power Socket]
  D --> F[Fan]
  D --> L3[Pink Light]
  C --> LED[Status LED (13)]
```

## 🔌 Pin Map

| Appliance     | Short code | Arduino Pin | Relay logic |
|---------------|------------|-------------|-------------|
| **Red Light** | `1`        | `4`         | Active LOW  |
| **Socket**    | `2`        | `5`         | Active LOW  |
| **Fan**       | `3`        | `6`         | Active LOW  |
| **Pink Light**| `4`        | `7`         | Active LOW  |

> Status LED on `13` blinks after each command.

## 🗣️ Command Reference

You can send commands from any **Bluetooth Serial Terminal** app:

- `RED_LIGHT_ON` / `1ON` … `RED_LIGHT_OFF` / `1OFF`
- `SOCKET_ON` / `2ON` … `SOCKET_OFF` / `2OFF`
- `FAN_ON` / `3ON` … `FAN_OFF` / `3OFF`
- `PINK_LIGHT_ON` / `4ON` … `PINK_LIGHT_OFF` / `4OFF`
- `ALL_ON`, `ALL_OFF`, `STATUS`

> Commands are case‑insensitive; spaces and underscores are ignored.

## 🚀 Getting Started

### Hardware
- Arduino Uno, HC‑05 Bluetooth, 4‑channel relay, and four appliances.
- **Important:** Most relay boards are **active LOW** (LOW = ON). Make sure VCC and JD-VCC jumpers are wired correctly per your relay board’s manual.

### Firmware
1. Open `firmware/HomeAutomation.ino` in **Arduino IDE**.
2. Select board **Arduino Uno** and port.
3. Upload.
4. Pair your phone with **HC‑05** (default PIN often `1234` or `0000`).
5. Open a Bluetooth serial terminal and send commands (e.g., `ALL_ON`).

## 📊 Results (from the report)

- Response time: **< 1s**
- Command success rate: **~98%**
- Bluetooth range: **~10 m**
- Idle current: **~50 mA**

> See the full report in `docs/Final-IoT-Project-Report.pdf` for evaluation details.

## 📂 Repo Structure

```
.
├── assets/cover.svg
├── docs/Final-IoT-Project-Report.pdf
├── firmware/HomeAutomation.ino
├── hardware/wiring.md
├── .github/ISSUE_TEMPLATE/bug_report.md
├── .github/ISSUE_TEMPLATE/feature_request.md
├── .github/pull_request_template.md
├── .github/workflows/arduino-lint.yml
├── CODE_OF_CONDUCT.md
├── CONTRIBUTING.md
├── SECURITY.md
├── CHANGELOG.md
├── LICENSE
├── .gitignore
└── README.md
```

## 🛣️ Roadmap

- Sensor‑based automation (DHT11, PIR, LDR)
- Voice assistants (Alexa / Google Assistant)
- Predictive automation / anomaly detection
- ESP32 + Wi‑Fi backend & mobile app

## 🤝 Contributing

PRs welcome! Check out `CONTRIBUTING.md` and open an issue.

## 🪪 License

[MIT](LICENSE) © 2025 Md. Fahimur Rahman
