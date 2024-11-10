/*
Copyright (c) 2024 Bert Melis. All rights reserved.

This work is licensed under the terms of the MIT license.  
For a copy, see <https://opensource.org/licenses/MIT> or
the LICENSE file.
*/

#include <Arduino.h>

#include <OnkyoRI_RMT.h>

constexpr int RI_PIN = 15;
constexpr int VOLUME_UP_PIN = 23;
constexpr int VOLUME_DOWN_PIN = 18;

OnkyoRI_RMT myAmplifier(RI_PIN);
bool buttonVolUpPressed = false;
bool buttonVolDownPressed = false;

void ARDUINO_ISR_ATTR isr(void *arg) {
  int button = reinterpret_cast<int>(arg);
  if (button == 1) {
    buttonVolUpPressed = true;
  } else if (button == 2) {
    buttonVolDownPressed = true;
  }
}

void setup() {
  Serial.begin(115200);
  pinMode(VOLUME_UP_PIN, INPUT_PULLUP);
  pinMode(VOLUME_DOWN_PIN, INPUT_PULLUP);
  attachInterruptArg(VOLUME_UP_PIN, isr, reinterpret_cast<void*>(1), FALLING);
  attachInterruptArg(VOLUME_DOWN_PIN, isr, reinterpret_cast<void*>(2), FALLING);
}

void loop() {
  if (buttonVolUpPressed && myAmplifier.write(OnkyoRI::Command::VOLUMEUP)) {  // write built-in commands
    buttonVolUpPressed = false;
  }
  if (buttonVolUpPressed && myAmplifier.write(0x003)) {  // write custom 2-byte code
    buttonVolDownPressed = false;
  }
}
