# 8-LED Dual-Mode Animation Controller

This project implements a sequence controller for 8 LEDs using the MAX78000. It features two distinct animation patterns that can be toggled in real-time using a physical push-button.

## 🔌 Hardware Wiring

This code requires **8 external LEDs** and **1 Button**. The GPIOs are configured as **Active Low** (Sink Current).

### LED Connections
Connect the **Cathode (-)** of the LEDs to the pins below, and the **Anode (+)** to VCC (3.3V) via a resistor.

| LED Index | Logic Name | Port/Pin | Voltage Domain |
| :--- | :--- | :--- | :--- |
| **0** | Outer Left | **P2.3** | VDDIOH (3.3V) |
| **1** | Mid-Outer Left | **P2.4** | VDDIOH (3.3V) |
| **2** | Mid-Inner Left | **P1.0** | VDDIO (1.8V/3.3V) |
| **3** | Inner Left | **P0.7** | VDDIO (1.8V/3.3V) |
| **4** | Inner Right | **P0.5** | VDDIO (1.8V/3.3V) |
| **5** | Mid-Inner Right| **P0.6** | VDDIO (1.8V/3.3V) |
| **6** | Mid-Outer Right| **P2.6** | VDDIOH (3.3V) |
| **7** | Outer Right | **P2.7** | VDDIOH (3.3V) |

### Button Connection
* **Pin**: **P0.2**
* **Type**: Active Low (Connect Pin to Switch -> Switch to Ground).
* **Resistor**: Internal Pull-up is enabled in software; no external resistor needed.

## 🕹️ Functionality

The program runs in an infinite loop, constantly polling the button status.

### The Modes
The system toggles between two visual modes when the button is pressed.



[Image of LED array schematic]


**Mode 0: Convergence (Inward)**
The LEDs light up in pairs starting from the outside and meeting in the middle.
```text
Step 1: [X . . . . . . X]  (LEDs 0 & 7)
Step 2: [. X . . . . X .]  (LEDs 1 & 6)
Step 3: [. . X . . X . .]  (LEDs 2 & 5)
Step 4: [. . . X X . . .]  (LEDs 3 & 4)