#include <SoftwareSerial.h>
#include <Servo.h>

SoftwareSerial mySerial(10, 11); //TX, RX
Servo esc;

const uint8_t VescOutputPin = 5;
const int stopLed = 13;
const int goLed = 12;
const int throttleLed = 8;
const int statusPin = 3;
int mappedSpeed = 0;
unsigned int btInputValue;

void setup() {
  // put your setup code here, to run once:  
  pinMode(stopLed, OUTPUT);
  pinMode(throttleLed, OUTPUT);
  pinMode(goLed, OUTPUT);
  pinMode(statusPin, INPUT);
  Serial.begin(9600);
  mySerial.begin(9600);

  esc.attach(VescOutputPin);
}

void loop() {
  // put your main code here, to run repeatedly:

  int statusValue = digitalRead(statusPin);

  if (statusValue == 0) {
    // Bluetooth Disconnected - Stop Board
  //  Serial.print("Status Pin: ");
  //  Serial.print(statusValue);
  //  Serial.print("\n");
    stopBoard();
  }
  else {
    if (mySerial.available() >= 2) {
      unsigned int btInputA = mySerial.read();
      unsigned int btInputB = mySerial.read();
      btInputValue = (btInputB * 256) + btInputA;
      
     // Serial.print(btInputValue);
     // Serial.print('\n');
      
      if (btInputValue == 2000) {
        stopBoard();
      }
      else if (btInputValue >= 0 && btInputValue <= 255) {
        mappedSpeed = map(btInputValue, 50, 255, 1000, 2000);
        esc.writeMicroseconds(mappedSpeed);
        Serial.print("Mapped Speed");
        Serial.print('\n');
        Serial.print(mappedSpeed);
        digitalWrite(throttleLed, HIGH);
      }  
      digitalWrite(stopLed, LOW);
      digitalWrite(goLed, LOW);
      digitalWrite(throttleLed, LOW);
    }
  }
}

void stopBoard() {
  digitalWrite(stopLed, HIGH);

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
        esc.writeMicroseconds(mappedSpeed);
        Serial.print("Mapped Speed");
        Serial.print('\n');
        Serial.print(mappedSpeed);
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
        esc.writeMicroseconds(mappedSpeed);

        Serial.print("Mapped Speed");
        Serial.print('\n');
        Serial.print(mappedSpeed);
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
        esc.writeMicroseconds(mappedSpeed);

        Serial.print("Mapped Speed");
        Serial.print('\n');
        Serial.print(mappedSpeed);
      }
      delay(63);
      Serial.print(mappedSpeed); 
      Serial.print('\n');
    }       
  }
  digitalWrite(stopLed, LOW);
}

