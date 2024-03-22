#include <Arduino.h>

#define outputPin D1 // Output pin for generating 40kHz signal
#define inputPin D2  // Input pin to measure phase shift

long pwmTime = 0; // Time of rising edge of input signal
long phaseShift = 0;     // Phase shift in microseconds
int measurement = 0;


void ICACHE_RAM_ATTR interrupt_pwm() {
  pwmTime = ESP.getCycleCount();
}

void ICACHE_RAM_ATTR interrupt_input() {
  phaseShift += ESP.getCycleCount() - pwmTime;
  measurement++;
}

void setup() {
  Serial.begin(115200); // Initialize serial communication for debugging
  pinMode(inputPin, INPUT_PULLUP);
  
  attachInterrupt(digitalPinToInterrupt(outputPin), interrupt_pwm, RISING);
  attachInterrupt(digitalPinToInterrupt(inputPin), interrupt_input, RISING);
  
  // Configure Timer1 to generate 40kHz square wave
  analogWriteFreq(39643);
  analogWrite(outputPin, 127);
}

void loop() {
  /*detachInterrupt(digitalPinToInterrupt(outputPin));
  detachInterrupt(digitalPinToInterrupt(inputPin));
  if(measurement == 0){
    Serial.println("No Transducer connection");
  }else{
    Serial.println(phaseShift/measurement);
  }
  measurement = 0;
  phaseShift = 0;
  attachInterrupt(digitalPinToInterrupt(outputPin), interrupt_pwm, RISING);
  attachInterrupt(digitalPinToInterrupt(inputPin), interrupt_input, RISING);*/
  delay(100);
}
