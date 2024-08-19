#include <SoftwareSerial.h>
#include <rsa.h>

SoftwareSerial mySerial(10, 11); //RX, TX

long* decrypted;
uint8_t length = 32; 
long encryptedMessage[32];
long p = 53;
long q = 17;
long n;
long d;
long phi;
long e;
long privateKey[2] = {0, 0}; //(n, d)
bool primeq;
bool primep;

void initializePrimes();
void calculateKeys();
void printKeyDetails();
void receiveEncryptedMessage(long* encryptedMessage, uint8_t length);

void setup() {
  Serial.begin(9600);
  mySerial.begin(9600);
  Serial.println();

  initializePrimes();
  calculateKeys();
  
}

void loop() {
  if (mySerial.available()){
    receiveEncryptedMessage(encryptedMessage, length);
    decrypted = rsa_decrypt(encryptedMessage, privateKey, length);
    printDecryptedMessage(decrypted, length);
  }
}

void initializePrimes(){
  phi = (p-1)*(q-1);
  e = (phi/p) + q;
  primeq = isprime(q, 1);
  primep = isprime(p, 1);
  //Serial.print(primep);
  //Serial.print(primeq);
}

void calculateKeys(){
  if (!primep && primeq){
    n = p*q; 

    while (gcd(e, phi) != 1){
        e += 1;
    }

    if (gcd(e, phi) == 1){
      d = modinv(e, phi);
      privateKey[0] = n;
      privateKey[1] = d;

      printKeyDetails();
    }
  } 
  else{
    Serial.println("p or q is not prime!");
  }
}

void printKeyDetails(){
  Serial.print("phi is : ");
  Serial.println(phi);
  Serial.print("e is : ");
  Serial.println(e);
  Serial.print("n is : ");
  Serial.println(n);
  Serial.print("d is : ");
  Serial.println(d);
}

void receiveEncryptedMessage(long* encryptedMessage, uint8_t length){
  for (int i = 0; i < length; i++){
    if (mySerial.available() > 2){
      uint8_t Byte1 = mySerial.read();
      uint8_t Byte2 = mySerial.read();
      uint8_t Byte3 = mySerial.read();
      uint8_t Byte4 = mySerial.read();

      encryptedMessage[i] = Byte1 | (Byte2 << 8) | (Byte3 << 16) | (Byte4 << 24);

      Serial.print("0x");
      Serial.print(encryptedMessage[i], HEX);
      Serial.print("  ");
    }
  }
  Serial.println();
}

void printDecryptedMessage(long* decryptedMessage, uint8_t length){
  Serial.print("Decrypted message: ");
  for (uint8_t i = 0; i < length; i++){
    Serial.print((char)decryptedMessage[i]); 
  }
  Serial.println();
}
