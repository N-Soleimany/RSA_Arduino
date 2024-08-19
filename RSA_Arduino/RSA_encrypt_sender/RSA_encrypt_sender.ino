#include <SoftwareSerial.h>
#include <rsa.h>

long publicKey[2] = {901, 33};  //(n, e)
SoftwareSerial mySerial(10, 11); //RX, TX

uint8_t message[] = "HELLO its a test";
uint8_t length = strlen((char*)message);
long* encryptedMessage;

void printEncryptedMessage(long* encryptedMessage, uint8_t length);
void sendEncryptedMessage(long* encryptedMessage, uint8_t length);


void setup() {
  Serial.begin(9600);
  mySerial.begin(9600);
  Serial.println();

  encryptedMessage = rsa_encrypt(message, publicKey);
  printEncryptedMessage(encryptedMessage, length);
  sendEncryptedMessage(encryptedMessage, length);
}

void loop() {

}

void printEncryptedMessage(long* encryptedMessage, uint8_t length){

  Serial.print("Encrypted message: ");
  for (uint8_t i = 0; i < length; i++){
    Serial.print("0x");
    Serial.print(encryptedMessage[i], HEX);
    Serial.print("  ");
  }
  Serial.println();
}

void sendEncryptedMessage(long* encryptedMessage, uint8_t length){
  for (uint8_t i = 0; i < length; i++){
    mySerial.write((uint8_t)(encryptedMessage[i]));
    mySerial.write((uint8_t)(encryptedMessage[i] >> 8));
    mySerial.write((uint8_t)(encryptedMessage[i] >> 16));
    mySerial.write((uint8_t)(encryptedMessage[i] >> 24));
  }
}



