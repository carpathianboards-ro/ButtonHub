# ButtonHub

![Version](https://img.shields.io/badge/version-1.0.0-blue) ![License](https://img.shields.io/badge/license-MIT-green) ![Hardware](https://img.shields.io/badge/hardware-Carpathian_Boards-orange)

**Stop wasting GPIO pins.** ButtonHub is a smart, offloaded input module designed to handle rotary encoders and buttons over a simple I2C connection.

<p align="center">
  <img src="extras/images/buttonhub_pinout.jpg" alt="ButtonHub Pinout" width="600">
</p>

## 🏔️ Overview

Crafted with the **Carpathian engineering spirit**, ButtonHub is designed to be clean, efficient, and immediately useful. Instead of using 3 pins for an encoder and 2 more for buttons (total 5 GPIOs), ButtonHub does all the heavy lifting internally using a dedicated **ATtiny404** processor running at 20MHz.

It delivers clean, debounced data to your main microcontroller using just **2 wires** (SDA/SCL).

### Key Features
* **Minimal Wiring:** Only requires VCC, GND, SDA, and SCL.
* **Smart Processing:** Internal hardware debounce and state management.
* **Versatile Inputs:** Handles 1 Rotary Encoder (with push button) + 2 External Buttons.
* **Configurable:** Change I2C address and encoder limits via software.
* **High Performance:** Powered by ATtiny404 @ 20MHz for zero latency.
* **Arduino Ready:** Comes with an easy-to-use library.

---

## 🚀 Getting Started

### Hardware Connection
Connect the ButtonHub to your microcontroller's I2C pins.

| ButtonHub Pin | Arduino/ESP32 | Description |
| :--- | :--- | :--- |
| **VCC** | 3.3V / 5V | Power Supply |
| **GND** | GND | Ground |
| **SDA** | SDA | I2C Data |
| **SCL** | SCL | I2C Clock |

### Default Settings
* **I2C Address:** `0x10` (Decimal: 16)
* **Encoder Limit:** `0 - 100` (Default)

---

## 💻 Arduino Library Usage

### Installation
1.  Download this repository as a ZIP file.
2.  Open Arduino IDE -> Sketch -> Include Library -> Add .ZIP Library.
3.  Select the downloaded file.

### Basic Example
Here is a simple sketch to read the encoder value and button states.

```cpp
#include <Wire.h>
#include "ButtonHub.h"

// Initialize ButtonHub with default address 0x10
ButtonHub hub(0x10);

void setup() {
  Serial.begin(115200);
  
  // Start the I2C connection
  if (!hub.begin()) {
    Serial.println("ButtonHub not found. Check wiring!");
    while (1);
  }
  
  Serial.println("ButtonHub Connected!");
  
  // Optional: Change the encoder limit (e.g., for a servo 0-180)
  // hub.setLimit(180);
}

void loop() {
  // You must call update() to fetch new data from the module
  if (hub.update()) {
    
    // Print Encoder Value
    Serial.print("Encoder: ");
    Serial.print(hub.getEncoderValue());
    
    // Check Buttons
    if (hub.isEncoderPressed()) {
      Serial.print(" | Enc Button: PRESSED");
    }
    
    if (hub.isButton1Pressed()) {
      Serial.print(" | Btn 1: PRESSED");
    }
    
    if (hub.isButton2Pressed()) {
      Serial.print(" | Btn 2: PRESSED");
    }
    
    Serial.println();
  }
  
  delay(50); // Small delay to keep serial readable
}
