### Day 12: Peripheral Interfacing - GPIO, UART, I2C, and SPI
Today, we'll cover interfacing with various peripherals commonly used in embedded systems: General Purpose Input/Output (GPIO), Universal Asynchronous Receiver/Transmitter (UART), Inter-Integrated Circuit (I2C), and Serial Peripheral Interface (SPI).

1. General Purpose Input/Output (GPIO)
GPIO pins are used for digital input and output operations. They can read the state of a button or control an LED.

Code: GPIO Example (Pseudo-code for ARM Cortex-M)

cpp
Copy code
#include "stm32f4xx.h"

void initGPIO() {
    RCC->AHB1ENR |= RCC_AHB1ENR_GPIOAEN; // Enable GPIOA clock
    GPIOA->MODER |= GPIO_MODER_MODER5_0; // Set PA5 as output
    GPIOA->MODER &= ~(GPIO_MODER_MODER0); // Set PA0 as input
}

void toggleLED() {
    GPIOA->ODR ^= GPIO_ODR_OD5; // Toggle LED connected to PA5
}

int readButton() {
    return (GPIOA->IDR & GPIO_IDR_ID0) ? 1 : 0; // Read button state on PA0
}

int main() {
    initGPIO();

    while (1) {
        if (readButton()) {
            toggleLED();
            for (int i = 0; i < 100000; ++i); // Simple delay
        }
    }
}
Explanation:

initGPIO(): Initializes GPIOA, setting PA5 as output and PA0 as input.
toggleLED(): Toggles the state of the LED connected to PA5.
readButton(): Reads the state of the button connected to PA0.
2. Universal Asynchronous Receiver/Transmitter (UART)
UART is used for serial communication between the microcontroller and peripherals such as PCs, sensors, and other microcontrollers.

Code: UART Example (Pseudo-code for ARM Cortex-M)

cpp
Copy code
#include "stm32f4xx.h"

void initUART() {
    RCC->APB1ENR |= RCC_APB1ENR_USART2EN; // Enable USART2 clock
    RCC->AHB1ENR |= RCC_AHB1ENR_GPIOAEN; // Enable GPIOA clock
    
    GPIOA->MODER |= GPIO_MODER_MODER2_1 | GPIO_MODER_MODER3_1; // Set PA2, PA3 to alternate function
    GPIOA->AFR[0] |= 0x7700; // Set alternate function for PA2, PA3 to USART2

    USART2->BRR = 0x683; // Set baud rate (assuming 16 MHz clock, 9600 baud)
    USART2->CR1 |= USART_CR1_TE | USART_CR1_RE; // Enable transmitter and receiver
    USART2->CR1 |= USART_CR1_UE; // Enable USART
}

void uartSendChar(char c) {
    while (!(USART2->SR & USART_SR_TXE)); // Wait until transmit data register is empty
    USART2->DR = c; // Send character
}

char uartReceiveChar() {
    while (!(USART2->SR & USART_SR_RXNE)); // Wait until receive data register is not empty
    return USART2->DR; // Read character
}

int main() {
    initUART();
    
    while (1) {
        char received = uartReceiveChar();
        uartSendChar(received); // Echo received character
    }
}
Explanation:

initUART(): Initializes USART2 for UART communication.
uartSendChar(char c): Sends a character via UART.
uartReceiveChar(): Receives a character via UART.
3. Inter-Integrated Circuit (I2C)
I2C is used for communication between microcontrollers and low-speed peripherals such as sensors, EEPROMs, and other ICs.

Code: I2C Example (Pseudo-code for ARM Cortex-M)

cpp
Copy code
#include "stm32f4xx.h"

void initI2C() {
    RCC->APB1ENR |= RCC_APB1ENR_I2C1EN; // Enable I2C1 clock
    RCC->AHB1ENR |= RCC_AHB1ENR_GPIOBEN; // Enable GPIOB clock

    GPIOB->MODER |= GPIO_MODER_MODER8_1 | GPIO_MODER_MODER9_1; // Set PB8, PB9 to alternate function
    GPIOB->OTYPER |= GPIO_OTYPER_OT8 | GPIO_OTYPER_OT9; // Set PB8, PB9 to open-drain
    GPIOB->AFR[1] |= 0x4400; // Set alternate function for PB8, PB9 to I2C1

    I2C1->CR1 |= I2C_CR1_SWRST; // Reset I2C
    I2C1->CR1 &= ~I2C_CR1_SWRST; // Release reset

    I2C1->CR2 |= 16; // Set peripheral clock frequency (16 MHz)
    I2C1->CCR = 80; // Set clock control register (100 kHz)
    I2C1->TRISE = 17; // Configure maximum rise time

    I2C1->CR1 |= I2C_CR1_PE; // Enable I2C
}

void i2cWrite(uint8_t address, uint8_t data) {
    while (I2C1->SR2 & I2C_SR2_BUSY); // Wait until bus is free
    I2C1->CR1 |= I2C_CR1_START; // Generate start condition
    while (!(I2C1->SR1 & I2C_SR1_SB)); // Wait until start condition is generated
    I2C1->DR = address; // Send address
    while (!(I2C1->SR1 & I2C_SR1_ADDR)); // Wait until address is sent
    (void)I2C1->SR2; // Clear ADDR flag
    I2C1->DR = data; // Send data
    while (!(I2C1->SR1 & I2C_SR1_TXE)); // Wait until data is sent
    I2C1->CR1 |= I2C_CR1_STOP; // Generate stop condition
}

int main() {
    initI2C();
    
    while (1) {
        i2cWrite(0x50, 0xA5); // Write 0xA5 to address 0x50
        for (int i = 0; i < 100000; ++i); // Simple delay
    }
}
Explanation:

initI2C(): Initializes I2C1 for communication.
i2cWrite(uint8_t address, uint8_t data): Writes data to a given I2C address.
4. Serial Peripheral Interface (SPI)
SPI is a synchronous serial communication interface used for short-distance communication, primarily in embedded systems.

Code: SPI Example (Pseudo-code for ARM Cortex-M)

cpp
Copy code
#include "stm32f4xx.h"

void initSPI() {
    RCC->APB2ENR |= RCC_APB2ENR_SPI1EN; // Enable SPI1 clock
    RCC->AHB1ENR |= RCC_AHB1ENR_GPIOAEN; // Enable GPIOA clock

    GPIOA->MODER |= GPIO_MODER_MODER5_1 | GPIO_MODER_MODER6_1 | GPIO_MODER_MODER7_1; // Set PA5, PA6, PA7 to alternate function
    GPIOA->AFR[0] |= 0x55500000; // Set alternate function for PA5, PA6, PA7 to SPI1

    SPI1->CR1 = SPI_CR1_MSTR | SPI_CR1_BR_1 | SPI_CR1_SSM | SPI_CR1_SSI; // Configure SPI1 as master, baud rate, software slave management
    SPI1->CR1 |= SPI_CR1_SPE; // Enable SPI1
}

void spiWrite(uint8_t data) {
    while (!(SPI1->SR & SPI_SR_TXE)); // Wait until transmit buffer is empty
    SPI1->DR = data; // Send data
    while (!(SPI1->SR & SPI_SR_RXNE)); // Wait until data is received
    (void)SPI1->DR; // Read received data to clear RXNE flag
}

uint8_t spiRead() {
    spiWrite(0xFF); // Send dummy data
    while (!(SPI1->SR & SPI_SR_RXNE)); // Wait until data is received
    return SPI1->DR; // Return received data
}

int main() {
    initSPI();

    while (1) {
        spiWrite(0xA5); // Write data
        uint8_t received = spiRead(); // Read data
        for (int i = 0; i < 100000; ++i); // Simple delay
    }
}
Explanation:

initSPI(): Initializes SPI1 for communication.
spiWrite(uint8_t data): Writes data via SPI.
spiRead(): Reads data via SPI.
Daily Challenge:
Implement a GPIO interrupt to handle a button press and toggle an LED.
Set up UART communication between your microcontroller and a PC to send and receive data.
Interface with an I2C temperature sensor and read its data.
Communicate with an SPI flash memory to write and read data.
