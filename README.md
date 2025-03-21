# 🎛️ CtrlDeck

A sleek Arduino-powered media control module with a rotary encoder and 8 customizable buttons for seamless audio and shortcut management.

## ✨ Features

- 🔄 **Rotary Encoder**: Adjust media volume or navigate effortlessly.
- 🎮 **Customizable Buttons**: 8 programmable buttons for your favorite shortcuts or system controls.
- 💡 **LED Indicators**: RGB LEDs for visual feedback.
- ⚡ **Micro-Mode**: Enhance your operations with quick and precise controls.
- 💤 **Power Management**: Sleep mode and power-down functionality to save energy.

## 🛠️ Requirements

- 🖥️ Arduino IDE
- 📦 HID-Project Library
- 🌙 LowPower Library

## 📌 Pin Configuration

| Component        | Pin Number |
|------------------|------------|
| Rotary Encoder A | 16         |
| Rotary Encoder B | 14         |
| Encoder Switch   | 15         |
| RGB LED Red      | 21         |
| RGB LED Green    | 20         |
| RGB LED Blue     | 19         |
| Button 1         | 6          |
| Button 2         | 3          |
| Button 3         | 2          |
| Button 4         | 8          |
| Button 5         | 4          |
| Button 6         | 5          |
| Button 7         | 7          |
| Button 8         | 9          |

## 🎛️ Usage

### 🔧 Programming Mode (used to stop recording keypresses or as a panic mode)
1. Press and hold Button 1 while powering up the device until the status led blinks red (click the reset button or unplug and plug the device)
2. Press Button 2 to cancel programming mode.

### 🔊 Media Control
- Turn the rotary encoder to increase/decrease volume.
- Press customizable buttons to trigger specific shortcuts.

### 💥 Micro-Mode
Activate Micro-Mode for advanced functionality:
1. Press Button 2 to enable Micro-Mode. (stays active for 5 seconds, and adds 2.5seconds to the timer when you use the rotary encoder, click Button 2 to cancel)
2. Use the rotary encoder to navigate through text letter by letter (e.g., forward/backward).

### 💤 Power Management
- Press Button 3 to put the system to sleep.
- Press Button 4 to power down the system.

### 🎯 Shortcut Examples
- 🖱️ Button 5: Switch Audio Output devices (Requires SoundSwitch) (`Ctrl + Tab`).
- 🎨 Button 6: Open terminal (`Ctrl + Alt + T`).
- 
- Button 7 & 8: (wip)

## 🖼️ 3D Assembly

##### (Placeholder for assembly instructions)

## 🧩 Wiring Diagram

##### (Placeholder for wiring section)

## ⚖️ License

CtrlDeck - Media & Shortcut control module 
Copyright (c) 2025 João Fernandes
This work is licensed under the Creative Commons Attribution-NonCommercial 4.0 International License. 
To view a copy of this license, visit: * http://creativecommons.org/licenses/by-nc/4.0/

---

### 📚 Useful Documentation
- [Arduino Keyboard Modifiers](https://docs.arduino.cc/language-reference/en/functions/usb/Keyboard/keyboardModifiers/)
