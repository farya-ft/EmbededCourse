### Day 30: Power Management Techniques for Embedded Systems

Today, we'll cover power management techniques to optimize energy consumption in embedded systems. Efficient power management is critical for battery-powered devices and applications where power availability is limited.

#### 1. Introduction to Power Management

Power management involves techniques to reduce the energy consumption of a system without compromising performance. This is crucial for extending battery life and ensuring reliable operation in power-constrained environments.

#### 2. Low-Power Modes

Most microcontrollers have various low-power modes to reduce energy consumption when full processing power is not needed.

**2.1. Sleep Modes**

- Sleep modes reduce the clock speed or stop the clock to lower power consumption.
- Wake-up sources (e.g., timers, external interrupts) can bring the microcontroller out of sleep mode.

**Example: Using Sleep Mode (Arduino)**

```cpp
#include <avr/sleep.h>
#include <avr/wdt.h>

void setup() {
    Serial.begin(9600);
    pinMode(LED_BUILTIN, OUTPUT);
    digitalWrite(LED_BUILTIN, LOW);
}

void enterSleep() {
    set_sleep_mode(SLEEP_MODE_PWR_DOWN); // Set sleep mode
    sleep_enable(); // Enable sleep mode
    sleep_mode(); // Enter sleep mode
    sleep_disable(); // Disable sleep mode upon wake-up
}

void loop() {
    Serial.println("Going to sleep...");
    enterSleep();
    Serial.println("Woke up!");
    digitalWrite(LED_BUILTIN, HIGH);
    delay(1000);
    digitalWrite(LED_BUILTIN, LOW);
}
```

**Explanation:**
- `set_sleep_mode()`: Sets the desired sleep mode.
- `sleep_enable()`: Enables the sleep mode.
- `sleep_mode()`: Enters the sleep mode.
- `sleep_disable()`: Disables sleep mode after wake-up.

**2.2. Deep Sleep Modes**

- Deep sleep modes provide the lowest power consumption by shutting down most of the peripherals.
- Wake-up time is longer compared to regular sleep modes.

**Example: Using Deep Sleep Mode (ESP8266)**

```cpp
void setup() {
    Serial.begin(115200);
    Serial.println("Entering deep sleep mode...");
    ESP.deepSleep(10e6); // Sleep for 10 seconds (10e6 microseconds)
}

void loop() {
    // This will never be reached
}
```

**Explanation:**
- `ESP.deepSleep()`: Puts the ESP8266 into deep sleep mode for a specified duration.

#### 3. Dynamic Power Management

**3.1. Dynamic Voltage and Frequency Scaling (DVFS)**

- Adjusts the voltage and frequency according to the processing requirements to save power.

**Example: Dynamic Frequency Scaling**

```cpp
void setup() {
    Serial.begin(9600);
    noInterrupts();
    CLKPR = 0x80; // Enable clock prescaler change
    CLKPR = 0x01; // Set prescaler to 2 (divide clock by 2)
    interrupts();
}

void loop() {
    // Your code here
}
```

**Explanation:**
- `CLKPR`: Clock prescale register to adjust the clock frequency.

**3.2. Peripheral Management**

- Enable and disable peripherals as needed to reduce power consumption.

**Example: Disabling ADC to Save Power (Arduino)**

```cpp
void setup() {
    Serial.begin(9600);
    ADCSRA &= ~(1 << ADEN); // Disable ADC
}

void loop() {
    // Your code here
}
```

**Explanation:**
- `ADCSRA`: ADC control and status register.
- `ADEN`: ADC enable bit.

#### 4. Energy-Efficient Coding Practices

**4.1. Use Interrupts Instead of Polling**

- Polling continuously checks for a condition, which wastes power.
- Interrupts respond only when an event occurs, saving power.

**Example: Using Interrupts (Arduino)**

```cpp
const int buttonPin = 2;

void setup() {
    pinMode(buttonPin, INPUT_PULLUP);
    attachInterrupt(digitalPinToInterrupt(buttonPin), handleButtonPress, FALLING);
}

void handleButtonPress() {
    Serial.println("Button pressed!");
}

void loop() {
    // Your code here
}
```

**Explanation:**
- `attachInterrupt()`: Attaches an interrupt to a pin and specifies the ISR.

**4.2. Optimize Code Efficiency**

- Reduce computational complexity and avoid unnecessary operations.

**Example: Efficient Code for LED Blinking**

```cpp
void setup() {
    pinMode(LED_BUILTIN, OUTPUT);
}

void loop() {
    digitalWrite(LED_BUILTIN, HIGH);
    delay(100);
    digitalWrite(LED_BUILTIN, LOW);
    delay(900); // 10% duty cycle to save power
}
```

**Explanation:**
- Adjust the duty cycle to reduce power consumption.

#### 5. Power Supply Design

**5.1. Use Low-Power Components**

- Choose components with low power requirements.
- Consider components with sleep modes or low-power states.

**5.2. Efficient Voltage Regulation**

- Use low-dropout (LDO) regulators or switching regulators for efficient voltage conversion.

**Example: Using an LDO Regulator**

```cpp
void setup() {
    // No specific code, but use an LDO regulator in your circuit design
}

void loop() {
    // Your code here
}
```

**Explanation:**
- An LDO regulator maintains a stable output voltage with minimal power loss.

**5.3. Battery Management**

- Implement battery monitoring and management to optimize battery life.

**Example: Battery Voltage Monitoring (Arduino)**

```cpp
const int batteryPin = A0;

void setup() {
    Serial.begin(9600);
    analogReference(INTERNAL); // Use internal reference voltage
}

void loop() {
    int sensorValue = analogRead(batteryPin);
    float voltage = sensorValue * (1.1 / 1023.0); // Convert to voltage
    Serial.print("Battery Voltage: ");
    Serial.println(voltage);
    delay(1000);
}
```

**Explanation:**
- `analogRead()`: Reads the voltage from the battery pin.
- Convert the analog reading to the actual voltage.

#### Daily Challenge:
1. Implement a sleep mode in your microcontroller project and measure the power savings.
2. Use dynamic frequency scaling to adjust the clock speed based on processing needs.
3. Enable and disable peripherals as needed to reduce power consumption.
4. Rewrite a polling-based code to use interrupts and measure the power savings.
5. Design a simple power supply circuit using an LDO regulator and monitor the battery voltage.

