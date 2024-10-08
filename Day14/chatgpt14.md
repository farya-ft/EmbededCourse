### Day 14: Communication Protocols and Security in Embedded Systems
Today, we will cover various communication protocols used in embedded systems and delve into security aspects that are crucial for ensuring the integrity and confidentiality of data.

#### 1. Communication Protocols
Communication protocols facilitate data exchange between devices in an embedded system. We'll explore a few common protocols: CAN, MQTT, and Modbus.

##### 1.1. Controller Area Network (CAN)

CAN is a robust protocol used for real-time communication in automotive and industrial applications. It supports high-speed data exchange and error detection.

##### CAN Example (Pseudo-code for ARM Cortex-M)

```cpp

#include "stm32f4xx.h"

void initCAN() {
    RCC->APB1ENR |= RCC_APB1ENR_CAN1EN; // Enable CAN1 clock
    RCC->AHB1ENR |= RCC_AHB1ENR_GPIOAEN; // Enable GPIOA clock

    // Configure PA11 (CAN_RX) and PA12 (CAN_TX)
    GPIOA->MODER |= GPIO_MODER_MODER11_1 | GPIO_MODER_MODER12_1; // Set PA11, PA12 to alternate function
    GPIOA->AFR[1] |= 0x99; // Set alternate function for PA11, PA12 to CAN1

    CAN1->MCR = CAN_MCR_INRQ; // Initialize CAN
    CAN1->BTR = 0x001c0003; // Set baud rate (assuming 16 MHz clock, 500 kbps)
    CAN1->MCR &= ~CAN_MCR_INRQ; // Leave initialization mode
}

void canTransmit(uint32_t id, uint8_t* data, uint8_t length) {
    CAN1->sTxMailBox[0].TIR = id << 21; // Set standard identifier
    CAN1->sTxMailBox[0].TDTR = length; // Set data length
    for (int i = 0; i < length; i++) {
        CAN1->sTxMailBox[0].TDLR |= data[i] << (i * 8); // Load data
    }
    CAN1->sTxMailBox[0].TIR |= CAN_TI0R_TXRQ; // Request transmission
}

int main() {
    initCAN();

    uint8_t data[8] = {0x11, 0x22, 0x33, 0x44, 0x55, 0x66, 0x77, 0x88};
    canTransmit(0x123, data, 8);

    while (1) {
        // Main loop
    }
}
```
##### Explanation:

initCAN(): Initializes the CAN peripheral.
canTransmit(uint32_t id, uint8_t* data, uint8_t length): Transmits a CAN message.
#### 1.2. Message Queuing Telemetry Transport (MQTT)

MQTT is a lightweight protocol designed for IoT applications, enabling communication between devices over TCP/IP.

##### MQTT Example (Using PubSubClient Library for ESP8266)

```cpp

#include <ESP8266WiFi.h>
#include <PubSubClient.h>

const char* ssid = "your_SSID";
const char* password = "your_PASSWORD";
const char* mqttServer = "broker.hivemq.com";
const int mqttPort = 1883;
const char* mqttUser = "your_MQTT_USER";
const char* mqttPassword = "your_MQTT_PASSWORD";

WiFiClient espClient;
PubSubClient client(espClient);

void setup() {
    Serial.begin(115200);
    WiFi.begin(ssid, password);

    while (WiFi.status() != WL_CONNECTED) {
        delay(500);
        Serial.print(".");
    }
    Serial.println("WiFi connected");

    client.setServer(mqttServer, mqttPort);
    client.setCallback(callback);

    while (!client.connected()) {
        Serial.println("Connecting to MQTT...");
        if (client.connect("ESP8266Client", mqttUser, mqttPassword)) {
            Serial.println("Connected to MQTT");
        } else {
            Serial.print("Failed with state ");
            Serial.print(client.state());
            delay(2000);
        }
    }

    client.subscribe("test/topic");
}

void callback(char* topic, byte* payload, unsigned int length) {
    Serial.print("Message arrived [");
    Serial.print(topic);
    Serial.print("] ");
    for (int i = 0; i < length; i++) {
        Serial.print((char)payload[i]);
    }
    Serial.println();
}

void loop() {
    client.loop();
    client.publish("test/topic", "Hello from ESP8266");
    delay(2000);
}
```
##### Explanation:

setup(): Initializes WiFi and connects to the MQTT broker.
callback(char* topic, byte* payload, unsigned int length): Handles incoming MQTT messages.
loop(): Publishes a message to the MQTT topic.
### 1.3. Modbus

Modbus is a serial communication protocol used in industrial automation systems. It enables communication between devices over RS485, RS232, and TCP/IP.

#### Modbus RTU Example (Using ModbusMaster Library for Arduino)

```cpp

#include <ModbusMaster.h>

#define MAX485_DE 3
#define MAX485_RE 2

ModbusMaster node;

void preTransmission() {
    digitalWrite(MAX485_RE, 1);
    digitalWrite(MAX485_DE, 1);
}

void postTransmission() {
    digitalWrite(MAX485_RE, 0);
    digitalWrite(MAX485_DE, 0);
}

void setup() {
    pinMode(MAX485_RE, OUTPUT);
    pinMode(MAX485_DE, OUTPUT);
    digitalWrite(MAX485_RE, 0);
    digitalWrite(MAX485_DE, 0);

    Serial.begin(9600);
    node.begin(1, Serial);
    node.preTransmission(preTransmission);
    node.postTransmission(postTransmission);
}

void loop() {
    uint8_t result;
    uint16_t data[6];

    result = node.readInputRegisters(0x3100, 6);
    if (result == node.ku8MBSuccess) {
        for (int j = 0; j < 6; j++) {
            data[j] = node.getResponseBuffer(j);
            Serial.println(data[j]);
        }
    }
    delay(1000);
}
```
##### Explanation:

setup(): Initializes the Modbus node and serial communication.
loop(): Reads input registers and prints the data.
## 2. Security in Embedded Systems
Security is paramount in embedded systems to protect against unauthorized access, data breaches, and tampering.

### 1. Secure Communication

Use encryption protocols such as TLS/SSL for secure communication.

##### Secure Communication with MQTT (Using PubSubClient and WiFiClientSecure for ESP8266)

```cpp

#include <ESP8266WiFi.h>
#include <WiFiClientSecure.h>
#include <PubSubClient.h>

const char* ssid = "your_SSID";
const char* password = "your_PASSWORD";
const char* mqttServer = "broker.hivemq.com";
const int mqttPort = 8883;

WiFiClientSecure espClient;
PubSubClient client(espClient);

void setup() {
    Serial.begin(115200);
    WiFi.begin(ssid, password);

    while (WiFi.status() != WL_CONNECTED) {
        delay(500);
        Serial.print(".");
    }
    Serial.println("WiFi connected");

    espClient.setInsecure(); // Use setInsecure for testing, replace with certificate verification in production

    client.setServer(mqttServer, mqttPort);
    client.setCallback(callback);

    while (!client.connected()) {
        Serial.println("Connecting to MQTT...");
        if (client.connect("ESP8266Client")) {
            Serial.println("Connected to MQTT");
        } else {
            Serial.print("Failed with state ");
            Serial.print(client.state());
            delay(2000);
        }
    }

    client.subscribe("test/secure_topic");
}

void callback(char* topic, byte* payload, unsigned int length) {
    Serial.print("Message arrived [");
    Serial.print(topic);
    Serial.print("] ");
    for (int i = 0; i < length; i++) {
        Serial.print((char)payload[i]);
    }
    Serial.println();
}

void loop() {
    client.loop();
    client.publish("test/secure_topic", "Hello from secure ESP8266");
    delay(2000);
}
```
##### Explanation:

Uses WiFiClientSecure for secure communication over MQTT.
### 2.2. Secure Boot

Implement secure boot to ensure that only authenticated firmware is executed on the device.

Pseudo-code: Secure Boot

```cpp

#include "secure_boot.h"

void verifyFirmware() {
    // Verify firmware signature using public key
    if (!verifySignature(firmware, signature, publicKey)) {
        // Invalid firmware, halt execution
        while (1);
    }
}

int main() {
    verifyFirmware();

    // Normal boot process
    initSystem();
    startApplication();

    while (1) {
        // Main loop
    }
}
```

##### Explanation:

verifyFirmware(): Verifies the firmware signature before executing it.
 ### 2.3. Secure Storage

Use secure storage to protect sensitive data such as encryption keys and credentials.

##### Pseudo-code: Secure Storage

```cpp

#include "secure_storage.h"

void storeSecretData(const uint8_t* data, size_t length) {
    // Encrypt data before storing
    uint8_t encryptedData[length];
    encryptData(data, encryptedData, length, encryptionKey);

    // Store encrypted data in non-volatile memory
    writeNVM(encryptedData, length);
}

void retrieveSecretData(uint8_t* data, size_t length) {
    // Read encrypted data from non-volatile memory
    uint8_t encryptedData[length];
    readNVM(encryptedData, length);

    // Decrypt data after reading
    decryptData(encryptedData, data, length, encryptionKey);
}

int main() {
    const uint8_t secretData[] = "SensitiveData";
    storeSecretData(secretData, sizeof(secretData));

    uint8_t retrievedData[sizeof(secretData)];
    retrieveSecretData(retrievedData, sizeof(retrievedData));

    // Use retrieved data
    processSecretData(retrievedData, sizeof(retrievedData));

    while (1) {
        // Main loop
    }
}
```
##### Explanation:

storeSecretData(const uint8_t* data, size_t length): Encrypts and stores data.
retrieveSecretData(uint8_t* data, size_t length): Reads and decrypts stored data.

!!! Daily Challenge:
* Implement secure communication using TLS/SSL in your embedded project.
* Implement a basic CAN communication between two devices.
* Implement a simple MQTT communication using secure protocols.
* Store and retrieve sensitive data securely in your embedded system.