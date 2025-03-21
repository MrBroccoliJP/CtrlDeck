/*
 * CtrlDeck - Media & Shortcut control module 
 * Copyright (c) 2025 João Fernandes
 * 
 * This work is licensed under the Creative Commons Attribution-NonCommercial 
 * 4.0 International License. To view a copy of this license, visit:
 * http://creativecommons.org/licenses/by-nc/4.0/
 */

//useful documentation: https://docs.arduino.cc/language-reference/en/functions/usb/Keyboard/keyboardModifiers/

const char version = 'V0.8';

#define encoderClk 16
#define encoderD 14
#define encoderSW 15

#define LED_R 21
#define LED_G 20
#define LED_B 19

#define button_1_pin 6
#define button_2_pin 3
#define button_3_pin 2
#define button_4_pin 8
#define button_5_pin 4
#define button_6_pin 5
#define button_7_pin 7
#define button_8_pin 9

int buttonPinArray[9] = { button_1_pin, button_2_pin, button_3_pin, button_4_pin, button_5_pin, button_6_pin, button_7_pin, button_8_pin, encoderSW };

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

  pinMode(button_1_pin, INPUT_PULLUP);
  pinMode(button_2_pin, INPUT_PULLUP);
  pinMode(button_3_pin, INPUT_PULLUP);
  pinMode(button_4_pin, INPUT_PULLUP);
  pinMode(button_5_pin, INPUT_PULLUP);
  pinMode(button_6_pin, INPUT_PULLUP);
  pinMode(button_7_pin, INPUT_PULLUP);
  pinMode(button_8_pin, INPUT_PULLUP);

  lastStateClk = digitalRead(encoderClk);

  Serial.begin(9600);

  if (digitalRead(button_1_pin) == LOW) {
    Serial.println("Programing mode");
    while (digitalRead(button_2_pin) == HIGH) {
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

        if (microMode == 1) {
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
          else{
            microMode = 0;
          }
        }

        switch (checkEncoderPosition()) {
          case 1:
            if (microMode == 1) {
              Keyboard.press(KEY_RIGHT);
              Keyboard.releaseAll();
              targetTime+=2500;
            } else {
              Consumer.write(MEDIA_VOLUME_UP);
            }
            break;
          case -1:
            if (microMode == 1) {
              Keyboard.press(KEY_LEFT);
              Keyboard.releaseAll();
              targetTime+=2500;
            } else {
              Consumer.write(MEDIA_VOLUME_DOWN);
            }
            break;
        };


        switch (checkButtons()) {
          case 1:
            microMode = 0;
            targetTime = 0;
            mode = 1;  //reserved for mode switching
            break;
          case 2:
            //reserved for micro-mode switching
            targetTime = millis() + 5000;
            microMode = 1;
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
      //Serial.println("rotated+1");
      lastStateClk = currentStateClk;
      return 1;

    } else {

      lastStateClk = currentStateClk;
      //Serial.println("rotated-1");
      return -1;
    }
  }
  return 0;
}


int checkButtons() {

  for (int i = 0; i < 8; i++) {
    if (digitalRead(buttonPinArray[i]) == LOW && millis() - lastButtonPress > 200) {
      //Serial.print("Button");
      //Serial.print(i);
      //Serial.println(" Pressed");
      lastButtonPress = millis();
      return i + 1;
    }
  }

  //encoder button
  // if (digitalRead(encoderSW) == LOW && millis() - lastButtonPress > 200) {
  //   //Serial.println("encoder Button Pressed");
  //   lastButtonPress = millis();
  //   return 9;
  // }

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
