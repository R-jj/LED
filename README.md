# 8-LED Dual-Mode Animation Controller

This project implements a sequence controller for 8 LEDs using the MAX78000. It features two animation patterns that can be toggled in real time using a push-button.

## Hardware Wiring

This project uses 8 external LEDs and 1 push-button. The LEDs are configured as active-low (the MCU sinks current).

### LED Connections

Connect the LED cathode (-) to the MCU pin.  
Connect the LED anode (+) to 3.3V through a resistor (330–1kΩ).

| LED Index | Description       | Port/Pin | Voltage Domain     |
|----------|-------------------|----------|---------------------|
| 0        | Outer Left        | P2.3     | VDDIOH (3.3V)       |
| 1        | Mid-Outer Left    | P2.4     | VDDIOH (3.3V)       |
| 2        | Mid-Inner Left    | P1.0     | VDDIO (1.8V/3.3V)   |
| 3        | Inner Left        | P0.7     | VDDIO (1.8V/3.3V)   |
| 4        | Inner Right       | P0.5     | VDDIO (1.8V/3.3V)   |
| 5        | Mid-Inner Right   | P0.6     | VDDIO (1.8V/3.3V)   |
| 6        | Mid-Outer Right   | P2.6     | VDDIOH (3.3V)       |
| 7        | Outer Right       | P2.7     | VDDIOH (3.3V)       |

### Button Connection

- Pin: P0.2  
- Type: Active Low  
- Wiring: P0.2 → Button → GND  
- Internal pull-up enabled in software.

## Functionality Overview

The program continuously checks the button. Each valid press toggles between two animation modes.

## Animation Modes

### Mode 0: Convergence (Inward)

```
Step 1: [X . . . . . . X]  (0,7)
Step 2: [. X . . . . X .]  (1,6)
Step 3: [. . X . . X . .]  (2,5)
Step 4: [. . . X X . . .]  (3,4)
```

### Mode 1: Divergence (Outward)

```
Step 1: [. . . X X . . .]  (3,4)
Step 2: [. . X . . X . .]  (2,5)
Step 3: [. X . . . . X .]  (1,6)
Step 4: [X . . . . . . X]  (0,7)
```

## Mode Switching Logic

```
current_mode = (current_mode + 1) % 2;
```

| Press Count | Mode        |
|-------------|-------------|
| 0           | Convergence |
| 1           | Divergence  |
| 2           | Convergence |
| 3           | Divergence  |

## Program Flow

```
Initialize LEDs (output, active-low)
Initialize Button (input, pull-up)

current_mode = 0

Loop:
    If button pressed:
        Toggle mode
        Debounce

    If mode 0: run inward sequence
    Else: run outward sequence
```

## LED Layout (Conceptual)

```
0 1 2 3   4 5 6 7
[Outer → Inner][Inner → Outer]
```

## Timing

Animation speed is controlled by:

```
MXC_Delay(MXC_DELAY_MSEC(150));
```

Increase or decrease this value to change animation speed.

## Troubleshooting

**LED always ON**
- Check polarity (cathode to MCU, anode to 3.3V)
- Confirm active-low configuration

**Button not working**
- Ensure P0.2 floats high when idle  
- Press must connect P0.2 to GND

**Incorrect LED behavior**
- Verify correct pin mapping  
- Check wiring and polarity

## Repository Structure

```
main.c
Makefile
project.mk
flash.log
.vscode/
README.md
```

## Build & Flash

```
make clean
make
make flash
```

Press the RESET button after flashing.

## License

MIT License (or any license you choose).

## Author

R-jj
