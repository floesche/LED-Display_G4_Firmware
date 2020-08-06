---
title: Firmware
parent: Generation 4
---

# Firmware

Firmware (atmega328) for the fourth generation (G4) panels prototypes.

hardware_v0p1: firmware for hardware version 0.1 - i2c is used for comm/driver sub-panel communications. 

hardware_v0p2: firmware for hardware version 0.2 - spi is used for comm/driver sub-panel communications. 


## Project structure: 

```
.
├── hardware_v0p1
│   ├── comm
│   └── driver
├── hardware_v0p2
│   ├── comm
│   ├── driver
│   ├── driver_w_comp
│   └── spi_test
├── library
│   └── ic2master
└── test_controllers
    ├── due_test_controller
    ├── teensy3x_test_controller
    └── uno_test_controller
```