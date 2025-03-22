# 🎛️ CtrlDeck

A sleek Arduino-powered media control module with a rotary encoder and 8 customizable buttons for seamless audio and shortcut management.

*This project repository is a work-in-progress*
To-Do:  
Add 3D models & files.  
Add wiring section.  

## ✨ Features

- 🔄 **Rotary Encoder**: Adjust media volume or navigate effortlessly.
- 🎮 **Customizable Buttons**: 9 programmable buttons for your favorite shortcuts or system controls.
- 💡 **LED Indicators**: RGB LED for visual feedback.
- 💤 **Power Management**: Sleep mode and power-down functionality to save energy.

## 🛠️ Requirements

- 🖥️ Arduino IDE
- 📦 HID-Project Library
- 🌙 LowPower Library

### 🎛️ Usage *(Normal Mode)*

#### 🔧 Programming Mode *(used to stop recording keypresses or as a panic mode)*  
1. **Press and hold Button 1** while powering up the device until the status LED flashes red.  
   *(You can achieve this by clicking the reset button or disconnecting and reconnecting the device.)*  
2. To exit programming mode, simply **press Button 2**.

#### 🔊 Media Control  
- Turn the rotary encoder to **increase or decrease volume**.  
- Press customizable buttons to trigger specific shortcuts.


#### 🔧 Micro-Mode  
1. Activate Micro-Mode by **pressing Button 2**:  
   - The status LED flashes while Micro-Mode is enabled.  
   - Micro-Mode stays active for 5 seconds and extends by 2.5 seconds whenever the rotary encoder is used.  
   - To cancel Micro-Mode, press **Button 2** again.  
2. Use the rotary encoder to **navigate through text letter by letter** (e.g., forward or backward).


#### 💤 Power Management  *(OS independent)*
- Press **Button 3** to put the system to sleep.  
- Press **Button 4** to power down the system.  
*These should™ be OS independent. From my testing they have worked on Windows, Ubunto & linux Mint.*

#### 🎯 Shortcut Examples  
- 🔈/🎧 **Button 5**: Switch Audio Output devices *(Requires [SoundSwitch](https://github.com/Belphemur/SoundSwitch))* (`Ctrl + Tab`).  
- 🎨 **Button 6**: Open terminal (`Ctrl + Alt + T`).  
- **Button 7 & 8**: *(Work in progress)*  

---

### 💡 About Modes and Micro-Modes  

The **Modes** and **Micro-Modes** allow for flexible, user-configurable setups:  
- **Modes**: Each mode assigns a specific combination of keys to the buttons, configurable in the code. This feature enables users to switch between setups tailored to different activities. Examples include:  
  - A mode for **normal use**,  
  - A mode for **programming**,  
  - A mode for **gaming**, and  
  - A mode for **photo editing** *(e.g., Photoshop & Illustrator)*.  

- **Micro-Modes**: These allow temporary access to a different key combination without leaving the current mode.
  - When activated, Micro-Mode remains active for 5 seconds.
  - If the user clicks a button that is mapped specifically for a Micro-Mode, an additional 5 seconds is added to the timer.
  - Once the timer runs out, the system seamlessly returns to the normal mode.
  - This feature is especially useful for quick tasks requiring alternate keys momentarily while maintaining the active mode configuration.


## 🖼️ 3D Assembly

##### (Placeholder for assembly instructions)

## 🧩 Wiring Diagram
### 📌 Pin Configuration

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

##### (Placeholder for wiring section)

## ⚖️ License

CtrlDeck - Media & Shortcut control module  
Copyright (c) 2025 João Fernandes  
This work is licensed under the Creative Commons Attribution-NonCommercial 4.0 International License.  
To view a copy of this license, visit:  
[http://creativecommons.org/licenses/by-nc/4.0/](http://creativecommons.org/licenses/by-nc/4.0/)  

---

### 📚 Useful Documentation
- [Arduino Keyboard Modifiers](https://docs.arduino.cc/language-reference/en/functions/usb/Keyboard/keyboardModifiers/)
