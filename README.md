# 🎛️ CtrlDeck

A sleek Arduino-powered media control module with a rotary encoder and 8 customizable buttons for seamless audio and shortcut management.


| ![](Images/CtrlDeck_Photo2.jpg) | ![](Images/CtrlDeck_Photo.jpg) |
| ------------------------------- | ----------------------------- |
| CtrlDeck                        | CtrlDeck                      |


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

<figure>
    <img src="Images/CtrlDeck_Exploded_view.png" alt="Wiring Diagram" width="500"/>
    <figcaption>CtrlDeck exploded view</figcaption>
</figure>

The 3D assembly consists of four main components: the main PCB, a rotary encoder, and a three-part shell, which includes the top shell, bottom shell, and LED diffuser.

The LED diffuser is glued to the top shell. If you're replicating this project, print the diffuser using a translucent material to allow the LEDs to shine through.

The main PCB is secured to the top shell using 2mm screws. The rotary encoder fits snugly into the top shell and is held in place by its own mounting screw. The button tops have to be clicked in before mounting the main PCB to the top shell.

The reset button sits in a recessed slot within the top shell and is secured with a holder using two 2mm screws.

A separate cable relief component fits onto the cable. In this build, a custom cable was used, but if you're using a pre-made USB cable, you can modify this part to fit your design.

#### 3D Files:
There are two folders: "Complete_Model", which contains STEP files that can be modified to fit your needs, and "STL", which includes files ready for 3D printing the shell.

During assembly, I noticed some manual errors when mounting the buttons to the perfboard. As a result, I had to adjust the holes in the top shell to accommodate these variations (with tolerances of ±0.5mm in any direction). This may not be necessary for your project.


## 🧩 Wiring Diagram

<figure>
    <img src="Images/WiringDiagram.png" alt="Wiring Diagram" width="500"/>
    <figcaption>Wiring Diagram</figcaption>
</figure>

### 📌 Pin Configuration

| Component          | Pin Number |
|--------------------|------------|
| Rotary Encoder CLK | 16         |
| Rotary Encoder DT  | 14         |
| Encoder Switch     | 15         |
| RGB LED Red        | 21         |
| RGB LED Green      | 20         |
| RGB LED Blue       | 19         |
| Button 1           | 6          |
| Button 2           | 3          |
| Button 3           | 2          |
| Button 4           | 8          |
| Button 5           | 4          |
| Button 6           | 5          |
| Button 7           | 7          |
| Button 8           | 9          |  

<br>
I layed out my main pcb like this:

<figure>
    <img src="Images/PCB_Layout.png" alt="Board Layout Image" width="300"/>
    <figcaption>Main Board Layout Image</figcaption>
</figure>

## Key Connections

### RGB LED
- Connect the **Red, Green, and Blue** pins to GPIOs via resistors (e.g., **220Ω**).  
- Common cathode to **GND** or common anode to **VCC**.

### Rotary Encoder
- **CLK, DT, and SW** → GPIO pins.  
- **VCC** and **GND** → Power connections.

### Reset Button
- Connect between **RST** and **GND**.

### Push Buttons (BTN1 - BTN8)
- One side to **GPIO**, the other to **GND**.  
- Internal pull-ups can be used if needed.

## Notes
- ✅ Double-check polarity and connections before powering up.  
- ✅ Ensure appropriate resistor values for LEDs.  


## ⚖️ License

This project is licensed under the **Creative Commons Attribution-NonCommercial 4.0 International License (CC BY-NC 4.0)**
Creative Commons Attribution-NonCommercial 4.0 International License (CC BY-NC 4.0)

CtrlDeck © 2025 by João Fernandes is licensed under Creative Commons Attribution-NonCommercial 4.0 International 

See the [LICENSE](LICENSE.txt) file for details  
Or visit:  
[http://creativecommons.org/licenses/by-nc/4.0/](http://creativecommons.org/licenses/by-nc/4.0/)  

or send a letter to:

    Creative Commons
    PO Box 1866  
    Mountain View,    
    CA 94042  
    USA  

In summary (not a substitute for the full license):
- You are free to share and adapt the material for non-commercial purposes
- You must give appropriate credit and indicate if changes were made
- You may not use the material for commercial purposes without specific permission


### 📚 Useful Documentation
- [Arduino Keyboard Modifiers](https://docs.arduino.cc/language-reference/en/functions/usb/Keyboard/keyboardModifiers/)
