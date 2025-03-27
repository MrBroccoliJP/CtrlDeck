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
/**
 * @brief Encoder pin definitions
 */
#define ENCODER_CLK_PIN 16
#define ENCODER_D_PIN 14
#define ENCODER_SW_PIN 15

/**
 * @brief LED pin definitions
 */
#define LED_R_PIN 21
#define LED_G_PIN 20
#define LED_B_PIN 19

/**
 * @brief Button pin definitions
 */
#define BUTTON_1_PIN 6
#define BUTTON_2_PIN 3
#define BUTTON_3_PIN 2
#define BUTTON_4_PIN 8
#define BUTTON_5_PIN 4
#define BUTTON_6_PIN 5
#define BUTTON_7_PIN 7
#define BUTTON_8_PIN 9

/**
 * @brief Button pin array for convenience
 */
int buttonPinArray[] = { BUTTON_1_PIN, BUTTON_2_PIN, BUTTON_3_PIN,
                         BUTTON_4_PIN, BUTTON_5_PIN, BUTTON_6_PIN,
                         BUTTON_7_PIN, BUTTON_8_PIN, ENCODER_SW_PIN };


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
  pinMode(LED_R_PIN, OUTPUT);
  pinMode(LED_G_PIN, OUTPUT);
  pinMode(LED_B_PIN, OUTPUT);

  pinMode(ENCODER_CLK_PIN, INPUT);
  pinMode(ENCODER_D_PIN, INPUT);
  pinMode(ENCODER_SW_PIN, INPUT_PULLUP);

  pinMode(BUTTON_1_PIN, INPUT_PULLUP);
  pinMode(BUTTON_2_PIN, INPUT_PULLUP);
  pinMode(BUTTON_3_PIN, INPUT_PULLUP);
  pinMode(BUTTON_4_PIN, INPUT_PULLUP);
  pinMode(BUTTON_5_PIN, INPUT_PULLUP);
  pinMode(BUTTON_6_PIN, INPUT_PULLUP);
  pinMode(BUTTON_7_PIN, INPUT_PULLUP);
  pinMode(BUTTON_8_PIN, INPUT_PULLUP);

  lastStateClk = digitalRead(ENCODER_CLK_PIN);

  Serial.begin(9600);

  if (digitalRead(BUTTON_1_PIN) == LOW) {
    Serial.println("Programing mode");
    while (digitalRead(BUTTON_2_PIN) == HIGH) {
      digitalWrite(LED_R_PIN, HIGH);
      delay(500);
      digitalWrite(LED_R_PIN, LOW);
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

        if (microMode == 1 && millis() < targetTime) {
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
        } else {
          targetTime = 0;
          microMode = 0;
        }

        switch (checkEncoderPosition()) {
          case 1:
            if (microMode == 1) {
              Keyboard.press(KEY_RIGHT);
              Keyboard.releaseAll();
              targetTime = millis() + 5000;
            } else {
              Consumer.write(MEDIA_VOLUME_UP);
            }
            break;
          case -1:
            if (microMode == 1) {
              Keyboard.press(KEY_LEFT);
              Keyboard.releaseAll();
              targetTime = millis() + 5000;
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

/**
 * @brief Check encoder position
 *
 * @return int Encoder position (1 or -1) if rotated, otherwise 0
 */
int checkEncoderPosition() {
  currentStateClk = digitalRead(ENCODER_CLK_PIN);
  if (currentStateClk != lastStateClk) {
    if (digitalRead(ENCODER_D_PIN) != currentStateClk) {
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

/**
 * @brief Check button states
 *
 * @return int Button number pressed (1-9) if a button is pressed,
 *         otherwise 0.
 */
int checkButtons() {

  for (int i = 0; i < 9; i++) {
    if (digitalRead(buttonPinArray[i]) == LOW && millis() - lastButtonPress > 300) {
      //Serial.print("Button");
      //Serial.print(i);
      //Serial.println(" Pressed");
      lastButtonPress = millis();
      return i + 1;
    }
  }
  return 0;
}

void checkIfUsbDeviceIsAsleep() {
  if (USBDevice.isSuspended() == true) {
    wakeFromSleep = true;
    ledControl(0, 0, 0);

    while (USBDevice.isSuspended() == true) {
      LowPower.idle(SLEEP_4S, ADC_OFF, TIMER4_OFF, TIMER3_OFF, TIMER1_OFF,
                    TIMER0_OFF, SPI_OFF, USART1_OFF, TWI_OFF, USB_ON);
    }

    wakeFromSleepToggle();
  }
}

/**
   * @brief flash the status led 3 times with the color of the mode set
   */
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

/**
   * @brief Set the color of the LEDs
   */
void ledControl(bool r, bool g, bool b) {
  digitalWrite(LED_R_PIN, r);
  digitalWrite(LED_G_PIN, g);
  digitalWrite(LED_B_PIN, b);
}