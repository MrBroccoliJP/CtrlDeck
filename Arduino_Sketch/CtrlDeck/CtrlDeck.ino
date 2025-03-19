#define encoderClk 16
#define encoderD 14
#define encoderSW 15

#define RGB_R 21
#define RGB_G 20
#define RGB_B 19

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
  pinMode(RGB_R, OUTPUT);
  pinMode(RGB_G, OUTPUT);
  pinMode(RGB_B, OUTPUT);


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
      digitalWrite(RGB_R, HIGH);
      delay(500);
      digitalWrite(RGB_R, LOW);
      delay(500);
    }
  }
}

void loop() {

  checkEncoderPosition();
  //checkButtons();

  if(mode == 1){

  }
  else{
    switch(checkButtons()) {
      case 1:
        Keyboard.write(KEY_A);
      break;
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
