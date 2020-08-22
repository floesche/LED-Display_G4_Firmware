---
title: Firmware
parent: Setup
grand_parent: Generation 4
nav_order: 11
---

# Firmware

The current firmware for the G4 panels, driver board and comm board. Both boards are ATMEGA328 based. Refer to [G4 Panel Programmer](../Display_Tools/G4 Panel Programming/G4_Panel-programmer_instructions.md) on how to flash the firmware.

The current Generation 4 arenas use the SPI protocol for communication. 

The exact changes are unclear, but the commit message for the `driver_w_comp` says: 

> Added modified version of driver firmware which stretchs the row 'on' duration based on the number of leds being illuminated. Added teensy based test controller. Modified due controller to add brightness compensation test patterns.

# Files: 

```
├── hardware_v0p1                   - old firmware, using I2C communication
│   ├── comm
│   └── driver
├── hardware_v0p2                   - current firmware, SPI communication
│   ├── comm                        - firmware for comm board (up to v0.3)
│   ├── driver                      - firmware for driver board (up to v0.3)
│   ├── driver_w_comp               - firmware for driver board, stretch row on duration
│   └── spi_test                    - SPI signal test setup
├── library
│   └── ic2master
└── test_controllers
    ├── due_test_controller
    ├── teensy3x_test_controller
    └── uno_test_controller
```