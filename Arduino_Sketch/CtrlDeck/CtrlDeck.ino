/*
 * CtrlDeck - Media & Shortcut control module 
 * Copyright (c) 2025 João Fernandes
 * 
 * This work is licensed under the Creative Commons Attribution-NonCommercial 
 * 4.0 International License. To view a copy of this license, visit:
 * http://creativecommons.org/licenses/by-nc/4.0/
 */

const char version = 'V0.4';

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
int counter = 0;
int currentStateClk;
int lastStateClk;
unsigned long lastButtonPress = 0;

short int mode = 0;

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
}

void loop() {

  checkEncoderPosition();

  if (mode == 1) {
    digitalWrite(LED_R, HIGH);
    digitalWrite(LED_G, LOW);
    digitalWrite(LED_B, LOW);
    while (mode == 1) {

      switch (checkButtons()) {
        case 1:
          mode = 0;
          break;
      }
    }
  } else {
    digitalWrite(LED_R, HIGH);
    digitalWrite(LED_G, HIGH);
    digitalWrite(LED_B, HIGH);
    {
      while (mode != 1) {
        switch (checkButtons()) {
          case 1:
            mode = 1;
            break;
          case 2:
            Keyboard.write(KEY_B);
            break;
          case 3:
            Keyboard.write(KEY_C);
            break;
          case 4:
            Keyboard.write(KEY_D);
            break;
          case 5:
            Keyboard.write(KEY_E);
            break;
          case 6:
            Keyboard.write(KEY_F);
            break;
          case 7:
            Keyboard.write(KEY_G);
            break;
          case 8:
            Keyboard.write(KEY_H);
            break;
        }
      }
    }
  }
}

void checkEncoderPosition() {
  currentStateClk = digitalRead(encoderClk);
  if (currentStateClk != lastStateClk) {
    if (digitalRead(encoderD) != currentStateClk) {
      counter++;
    } else {
      counter--;
    }
    Serial.print("Position: ");
    Serial.println(counter);
  }
  lastStateClk = currentStateClk;
}


int checkButtons() {
  //encoder button
  if (digitalRead(encoderSW) == LOW && millis() - lastButtonPress > 200) {
    Serial.println("encoder Button Pressed");
    lastButtonPress = millis();
  }

  for (int i = 1; i <= 8; i++) {
    int buttonPin = (i == 1) ? button_1 : (i == 2) ? button_2
                                        : (i == 3) ? button_3
                                        : (i == 4) ? button_4
                                        : (i == 5) ? button_5
                                        : (i == 6) ? button_6
                                        : (i == 7) ? button_7
                                                   : button_8;
    if (digitalRead(buttonPin) == LOW && millis() - lastButtonPress > 200) {
      Serial.print("Button");
      Serial.print(i);
      Serial.println(" Pressed");
      lastButtonPress = millis();
      return i;
    }
  }
  return 0;
}
