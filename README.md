# RSA Encryption and Decryption with Arduino

This project demonstrates RSA encryption and decryption using two Arduino boards. One board is responsible for encrypting a message and sending it over a serial connection, while the other board receives the encrypted message and decrypts it. This example showcases the basics of RSA cryptography implemented on Arduino using the `SoftwareSerial` library for communication.

## Overview

The project consists of two main components:
1. **Encryptor (Sender):** Encrypts a plaintext message using RSA and sends the encrypted data over a serial connection.
2. **Decryptor (Receiver):** Receives the encrypted data, decrypts it, and displays the original message.

## Components

- **Arduino Uno (or compatible) x2**
- **Jumper wires**
- **USB cables**
- **SoftwareSerial library**
- **RSA library (custom implementation)**

## Wiring

### Encryptor (Sender) Board:
- **Pin 10** (TX) connected to **Pin 11** (RX) of the Receiver board.
- **Pin 11** (RX) connected to **Pin 10** (TX) of the Receiver board.
- **GND** of both boards connected together.

### Decryptor (Receiver) Board:
- **Pin 10** (RX) connected to **Pin 11** (TX) of the Sender board.
- **Pin 11** (TX) connected to **Pin 10** (RX) of the Sender board.
- **GND** of both boards connected together.

## Code Breakdown

### Encryptor (Sender) Code

The encryptor initializes with a predefined public key `(n, e)`. It then encrypts the message, prints the encrypted message to the serial monitor, and sends it via serial communication to the decryptor.

- **Public Key**: `publicKey[2] = {901, 33};`
- **Message**: `HELLO its a test`
- **Functions**:
  - `printEncryptedMessage`: Displays the encrypted message in hexadecimal format.
  - `sendEncryptedMessage`: Sends the encrypted message over the serial connection.

### Decryptor (Receiver) Code

The decryptor board receives the encrypted message via serial communication, decrypts it using the private key, and displays the decrypted message.

- **Private Key**: `(n, d)` generated dynamically based on two prime numbers `p` and `q`.
- **Functions**:
  - `initializePrimes`: Initializes prime numbers and calculates `phi`.
  - `calculateKeys`: Generates RSA keys `(n, d)` and ensures that the chosen `e` is coprime with `phi`.
  - `receiveEncryptedMessage`: Reads the encrypted message from the serial connection.
  - `printDecryptedMessage`: Displays the decrypted message.

## Setup and Usage

1. **Upload the Encryptor Code** to the first Arduino.
2. **Upload the Decryptor Code** to the second Arduino.
3. **Connect the boards** as per the wiring instructions.
4. Open the Serial Monitor for both boards.
5. The encryptor will send an encrypted message, and the decryptor will receive and display the original message after decryption.

## Notes

- The RSA implementation here is simplified for educational purposes. In real-world applications, larger prime numbers and more sophisticated methods would be used.
- Ensure that both boards are operating at the same baud rate (9600 in this example).

## Library
You can download it from https://github.com/arpitchauhan/cryptographic-protocols-arduino-and-PC
