/*
 * CtrlDeck - Media & Shortcut control module 
 * Copyright (c) 2025 João Fernandes
 * 
 * This work is licensed under the Creative Commons Attribution-NonCommercial 
 * 4.0 International License. To view a copy of this license, visit:
 * http://creativecommons.org/licenses/by-nc/4.0/
 */

//useful documentation: https://docs.arduino.cc/language-reference/en/functions/usb/Keyboard/keyboardModifiers/

const char version = 'V0.7';

#define encoderClk 16
#define encoderD 14
#define encoderSW 15

#define LED_R 21
#define LED_G 20
#define LED_B 19

#define button_1 6
#define button_2 3
#define button_3 2
#define button_4 8
#define button_5 4
#define button_6 5
#define button_7 7
#define button_8 9

#include "HID-Project.h"
#include "LowPower.h"

int currentStateClk;
int lastStateClk;
unsigned long lastButtonPress = 0;
bool wakeFromSleep = true;

unsigned long int targetTime = 0;
unsigned long int lastToggleTime = 0;
bool toggle = 1;

short int mode = 0;

short int microMode = 0;

void setup() {
  pinMode(LED_R, OUTPUT);
  pinMode(LED_G, OUTPUT);
  pinMode(LED_B, OUTPUT);

  pinMode(encoderClk, INPUT);
  pinMode(encoderD, INPUT);
  pinMode(encoderSW, INPUT_PULLUP);

  pinMode(button_1, INPUT_PULLUP);
  pinMode(button_2, INPUT_PULLUP);
  pinMode(button_3, INPUT_PULLUP);
  pinMode(button_4, INPUT_PULLUP);
  pinMode(button_5, INPUT_PULLUP);
  pinMode(button_6, INPUT_PULLUP);
  pinMode(button_7, INPUT_PULLUP);
  pinMode(button_8, INPUT_PULLUP);

  lastStateClk = digitalRead(encoderClk);

  Serial.begin(9600);

  if (digitalRead(button_1) == LOW) {
    Serial.println("Programing mode");
    while (digitalRead(button_2) == HIGH) {
      digitalWrite(LED_R, HIGH);
      delay(500);
      digitalWrite(LED_R, LOW);
      delay(500);
    }
  }
  Consumer.begin();
  Keyboard.begin();
  checkIfUsbDeviceIsAsleep();
}


void loop() {

  if (mode == 1) {

    ledControl(1, 0, 0);
    while (mode == 1) {
      checkIfUsbDeviceIsAsleep();

      switch (checkButtons()) {
        case 1:
          mode = 0;
          break;
      }
    }
  } else {

    ledControl(1, 1, 1);
    {
      while (mode != 1) {

        switch (checkEncoderPosition()) {
          case 1:
            if (microMode = 1) {
              
            } else {
              Consumer.write(MEDIA_VOLUME_UP);
            }
            break;
          case -1:
            if (microMode = 1) {

            } else {
              Consumer.write(MEDIA_VOLUME_DOWN);
            }
            break;
        };


        switch (checkButtons()) {
          case 1:
            mode = 1;  //reserved for mode switching
            break;
          case 2:
            //reserved for micro-mode switching
            targetTime = millis() + 5000;
            while (millis() < targetTime) {

              if (millis() - lastToggleTime >= 125) {
                if (toggle) {
                  ledControl(1, 0, 1);
                  toggle = 0;
                } else {
                  ledControl(1, 1, 1);
                  toggle = 1;
                }
                lastToggleTime = millis();
              }
            }
            break;
          case 3:
            System.write(SYSTEM_SLEEP);
            break;
          case 4:
            System.write(SYSTEM_POWER_DOWN);
            break;
          case 5:
            Keyboard.press(KEY_LEFT_CTRL);
            Keyboard.press(KEY_TAB);
            delay(50);
            Keyboard.releaseAll();
            break;
          case 6:
            Keyboard.press(KEY_LEFT_CTRL);
            Keyboard.press(KEY_LEFT_ALT);
            Keyboard.press(KEY_T);
            delay(50);
            Keyboard.releaseAll();
            break;
          case 7:
            Keyboard.write(KEY_G);
            break;
          case 8:
            Keyboard.write(KEY_H);
            break;
          case 9:
            Consumer.write(MEDIA_PLAY_PAUSE);
            break;
        }

        checkIfUsbDeviceIsAsleep();
      }
    }
  }
}

int checkEncoderPosition() {
  currentStateClk = digitalRead(encoderClk);
  if (currentStateClk != lastStateClk) {
    if (digitalRead(encoderD) != currentStateClk) {

      lastStateClk = currentStateClk;
      return 1;

    } else {

      lastStateClk = currentStateClk;
      return -1;
    }
  }
  return 0;
}


int checkButtons() {

  for (int i = 1; i <= 8; i++) {
    int buttonPin = (i == 1) ? button_1 : (i == 2) ? button_2
                                        : (i == 3) ? button_3
                                        : (i == 4) ? button_4
                                        : (i == 5) ? button_5
                                        : (i == 6) ? button_6
                                        : (i == 7) ? button_7
                                                   : button_8;
    if (digitalRead(buttonPin) == LOW && millis() - lastButtonPress > 200) {
      //Serial.print("Button");
      //Serial.print(i);
      //Serial.println(" Pressed");
      lastButtonPress = millis();
      return i;
    }
  }

  //encoder button
  if (digitalRead(encoderSW) == LOW && millis() - lastButtonPress > 200) {
    //Serial.println("encoder Button Pressed");
    lastButtonPress = millis();
    return 9;
  }

  return 0;
}

void checkIfUsbDeviceIsAsleep() {
  if (USBDevice.isSuspended() == true) {
    wakeFromSleep = true;
    digitalWrite(LED_R, LOW);
    digitalWrite(LED_G, LOW);
    digitalWrite(LED_B, LOW);

    while (USBDevice.isSuspended() == true) {
      LowPower.idle(SLEEP_4S, ADC_OFF, TIMER4_OFF, TIMER3_OFF, TIMER1_OFF,
                    TIMER0_OFF, SPI_OFF, USART1_OFF, TWI_OFF, USB_ON);
    }

    wakeFromSleepToggle();
  }
}


void wakeFromSleepToggle() {
  bool r;
  bool g;
  bool b;
  if (wakeFromSleep) {
    if (mode == 1) {
      r = 1;
      g = 0;
      b = 0;

    } else {
      r = 1;
      g = 1;
      b = 1;
    }

    for (int i = 0; i < 3; i++) {
      ledControl(0, 0, 0);
      delay(200);
      ledControl(r, g, b);
      delay(200);
    }
  }
}

void ledControl(bool r, bool g, bool b) {
  digitalWrite(LED_R, r);
  digitalWrite(LED_G, g);
  digitalWrite(LED_B, b);
}
