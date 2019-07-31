#include <SoftwareSerial.h>

SoftwareSerial mySerial(10, 11); //TX, RX

const int stopLed = 13;
const int goLed = 12;
const int throttleLed = 8;
int mappedSpeed = 0;
unsigned int btInputValue;

void setup() {
  // put your setup code here, to run once:
  pinMode(stopLed, OUTPUT);
  pinMode(throttleLed, OUTPUT);
  pinMode(goLed, OUTPUT);
  Serial.begin(9600);
  
  mySerial.begin(9600);
}

void loop() {
  // put your main code here, to run repeatedly:
  if (mySerial.available() >= 2) {
    unsigned int btInputA = mySerial.read();
    unsigned int btInputB = mySerial.read();
    btInputValue = (btInputB * 256) + btInputA;
    Serial.print(btInputValue);
    Serial.print('\n');
    
    if (btInputValue == 2000) {
      stopBoard();
    }
    else if (btInputValue >= 0 && btInputValue <= 255) {
      mappedSpeed = map(btInputValue, 50, 255, 1000, 2000);
      digitalWrite(throttleLed, HIGH);
//      Serial.print(btInputValue);
//      Serial.print("Acceleration Value: " + mappedSpeed);
    }

//    if (btInputValue == 1000) {
//      digitalWrite(goLed, HIGH);
//      Serial.print("Motor GO");
//      delay(100);
//    }

    digitalWrite(stopLed, LOW);
    digitalWrite(goLed, LOW);
    digitalWrite(throttleLed, LOW);
  }
  else {
    // No Connection - figure out what to do here.
  }
}

void stopBoard() {
  digitalWrite(stopLed, HIGH);
  Serial.print(mappedSpeed);

  if (mappedSpeed > 1640) {
    Serial.print("Long Stop");
    Serial.print('\n');
    for (int i = 0; i < 50; i++){
      int newSpeed = mappedSpeed - 20;

      if (newSpeed < 1000) {
        break;
      }
      else {
        mappedSpeed = newSpeed;
      }
      delay(60);
      Serial.print(mappedSpeed);
      Serial.print('\n');
    }
  }
  else if (mappedSpeed > 1450) {
    Serial.print("Medium Stop");
    Serial.print('\n');
    for (int i = 0; i < 36; i++) {
      int newSpeed = mappedSpeed - 20;

      if (newSpeed < 1000) {
        break;
      }
      else {
        mappedSpeed = newSpeed;
      }
      delay(85);
      Serial.print(mappedSpeed);
      Serial.print('\n');
    }
  }
  else {
    Serial.print("Short Stop");
    Serial.print('\n');
    for (int i = 0; i < 28; i++) {
      int newSpeed = mappedSpeed - 20;

      if (newSpeed < 1000) {
        break;
      }
      else {
        mappedSpeed = newSpeed;
      }
      delay(63);
      Serial.print(mappedSpeed); 
      Serial.print('\n');
    }       
  }

  digitalWrite(stopLed, LOW);
}

