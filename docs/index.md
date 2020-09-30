---
title: Firmware
parent: Assembly
grand_parent: Generation 4
nav_order: 1
---

# Firmware

Each Modular LED display of Generation 4 uses five micro controller units per panel. This text explains how flash a firmware on these MCUs.

The [driver](../../Panel/docs/driver.md) and [comm board](../../Hardware/docs/comm.md) use a total of 5 micro controller units. To program these 5 ATmega328, you will need the [programmer](programmer.md) you built during the [acquisition](../../../docs/G4-Acquisition.md).

## Prerequisites

- [driver board](../../Panel/docs/driver.md)
- [comm board](../../Hardware/docs/comm.md)
- [Arduino](../../../docs/G4-COTS.md#arduino)
- [Arduino shield](programmer.md#arduino)
- [driver board shield](programmer.md#driver)
- [comm board shield](programmer.md#comm)
- computer

Install the custom version of the Arduino IDE on your computer. This IDE has the PanelsG4 board added as a target.

{::comment}
TODO: Add better explanation for how to get the IDE. Possibly provide alternative
{:/comment}

## Turn Arduino into In-circuit Serial Programmer (ISP)

To flash the firmware to the panel MCUs, the Arduino will act as a programmer.

1. Connect Arduino (Make sure programmer shield is off it will prevent programming)
1. Open Arduino IDE.
1. Go to *Tools*{:.gui-txt} ­→ *Board*{:.gui-txt} and select *Arduino UNO*{:.gui-txt}.
1. Go to *Tools*{:.gui-txt} ­→ *Port*{:.gui-txt} and select correct Port
1. Go to *File*{:.gui-txt} ­→ *Examples*{:gui-txt} select *ArduinoISP*{:.gui-txt}
1. *Verify*{:.gui-btn} (check button) and *Upload*{:.gui-btn} (right point arrow button).

These steps should be similar to what is described in an [Arduino tutorial online](https://www.arduino.cc/en/Tutorial/BuiltInExamples/ArduinoISP).

## Programming a driver panel

1. Open Arduino IDE
1. Connect Arduino w/ programmer shield attached[^1].
1. Go to *Tools*{:.gui-txt} ­→ *Board*{:.gui-txt} and select *PanelG4*{:.gui-txt}
1. Go to *Tools*{:.gui-txt} ­→ *Programmer*{:.gui-txt} and select *Arduino as ISP*{:.gui-txt} (not ArduinoISP!!!)
1. Note, you do not need external power supply the Arduino will provide power
1. Connect panel to programmer
1. Connect programmer to shield via ribbon cable (note)
1. Go to *Tools*{:.gui-txt} ­→ *Burn Bootloader*{:.gui-txt}
1. Open the `driver.ino` sketch (latest version is in [`hardware_v0p2/driver/`](https://github.com/floesche/panels_g4_firmware/tree/master/hardware_v0p2/driver))
1. Select subdevice using dip switch. Up is selected ­only one should be up at a time[^2].
1. Go to *Sketch*{:.gui-txt} ­→ *Upload Using Programmer*{:.gui-txt} to upload sketch to panel.

## Programming a comm panel.

1. Connect Arduino w/ programmer shield attached[^1].
1. Open Arduino IDE
1. Go to *Tools*{:.gui-txt} ­→ *Board*{:.gui-txt} and select *PanelG4*{:.gui-txt}
1. Go to *Tools*{:.gui-txt} ­→ *Programmer*{:.gui-txt} and select *Arduino as ISP*{:.gui-txt} (not ArduinoISP!!!)
1. Connect panels programmer to Arduino shield via ribbon cable
1. Note, you do not need external power supply the Arduino will provide power
1. Connect panel to programmer
1. Go to *Tools*{:.gui-txt} ­→ *Burn Bootloader*{:.gui-txt}
1. Open the `comm.ino` sketch (latest version is in [`hardware_v0p2/comm/`](https://github.com/floesche/panels_g4_firmware/tree/master/hardware_v0p2/comm))
1. Go to *Sketch*{:.gui-txt} ­→ *Upload Using Programmer*{:.gui-txt} to upload sketch to panel.

---

[^1]: Always remove ribbon cable before removing and attaching new driver subpanel as sometimes attaching a panel without doing so will corrupt the ArduinoISP program on the Uno

[^2]: To fully program the driver you chip you need to all four atmega328's which means programming the bootloader and firmware for all four dip switch "on" positions.
