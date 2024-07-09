### Day 13: Advanced Topics - DMA and Power Management
Today, we will cover two advanced topics in embedded systems: Direct Memory Access (DMA) and power management. These concepts are essential for optimizing performance and efficiency in embedded applications.

1. Direct Memory Access (DMA)
DMA is a feature that allows peripherals to directly transfer data to and from memory without involving the CPU, significantly improving data transfer efficiency and freeing the CPU for other tasks.

DMA Basics:

Memory-to-Memory Transfers: Data is moved between memory regions.
Peripheral-to-Memory Transfers: Data from a peripheral is moved to memory.
Memory-to-Peripheral Transfers: Data from memory is moved to a peripheral.
Code: DMA Example (Pseudo-code for ARM Cortex-M)

cpp
Copy code
#include "stm32f4xx.h"

void initDMA() {
    RCC->AHB1ENR |= RCC_AHB1ENR_DMA1EN; // Enable DMA1 clock

    DMA1_Stream0->CR = 0; // Reset control register
    DMA1_Stream0->CR |= DMA_SxCR_PL_1 | DMA_SxCR_MINC | DMA_SxCR_DIR_1; // Set high priority, memory increment, memory-to-memory
    DMA1_Stream0->NDTR = 100; // Number of data items to transfer
    DMA1_Stream0->PAR = (uint32_t)sourceBuffer; // Source address
    DMA1_Stream0->M0AR = (uint32_t)destinationBuffer; // Destination address

    DMA1_Stream0->CR |= DMA_SxCR_EN; // Enable DMA stream
}

void waitForDMACompletion() {
    while (!(DMA1->LISR & DMA_LISR_TCIF0)); // Wait for transfer complete flag
    DMA1->LIFCR |= DMA_LIFCR_CTCIF0; // Clear transfer complete flag
}

int main() {
    uint32_t sourceBuffer[100] = {1, 2, 3, 4, 5}; // Example source data
    uint32_t destinationBuffer[100] = {0}; // Destination buffer

    initDMA();
    waitForDMACompletion();

    while (1) {
        // Main loop
    }
}
Explanation:

initDMA(): Configures DMA for memory-to-memory transfers.
waitForDMACompletion(): Waits for the DMA transfer to complete.
DMA in Peripherals:

DMA can be used with peripherals like UART, SPI, and ADC for efficient data transfers.

Code: DMA with UART (Pseudo-code for ARM Cortex-M)

cpp
Copy code
#include "stm32f4xx.h"

void initUART_DMA() {
    RCC->APB1ENR |= RCC_APB1ENR_USART2EN; // Enable USART2 clock
    RCC->AHB1ENR |= RCC_AHB1ENR_DMA1EN; // Enable DMA1 clock

    // USART2 configuration
    USART2->BRR = 0x683; // Set baud rate (assuming 16 MHz clock, 9600 baud)
    USART2->CR3 |= USART_CR3_DMAT; // Enable DMA transmitter
    USART2->CR1 |= USART_CR1_TE | USART_CR1_UE; // Enable transmitter and USART

    // DMA configuration for USART2 TX
    DMA1_Stream6->CR = 0; // Reset control register
    DMA1_Stream6->CR |= DMA_SxCR_PL_1 | DMA_SxCR_MINC | DMA_SxCR_DIR_0; // Set high priority, memory increment, memory-to-peripheral
    DMA1_Stream6->NDTR = sizeof(txBuffer); // Number of data items to transfer
    DMA1_Stream6->PAR = (uint32_t)&USART2->DR; // Peripheral address (USART2 data register)
    DMA1_Stream6->M0AR = (uint32_t)txBuffer; // Memory address (transmit buffer)
}

void startDMATransfer() {
    DMA1_Stream6->CR |= DMA_SxCR_EN; // Enable DMA stream
}

int main() {
    uint8_t txBuffer[] = "Hello, DMA!"; // Data to transmit

    initUART_DMA();
    startDMATransfer();

    while (1) {
        // Main loop
    }
}
Explanation:

initUART_DMA(): Configures USART2 and DMA for UART transmission.
startDMATransfer(): Starts the DMA transfer.
2. Power Management
Power management is critical in embedded systems to extend battery life and reduce energy consumption. Techniques include low-power modes, peripheral control, and efficient coding practices.

Low-Power Modes:

Microcontrollers often support multiple low-power modes, such as sleep, deep sleep, and standby.

Code: Entering Low-Power Mode (Pseudo-code for ARM Cortex-M)

cpp
Copy code
#include "stm32f4xx.h"

void enterSleepMode() {
    SCB->SCR &= ~SCB_SCR_SLEEPDEEP_Msk; // Clear SLEEPDEEP bit
    __WFI(); // Wait for interrupt
}

void enterDeepSleepMode() {
    SCB->SCR |= SCB_SCR_SLEEPDEEP_Msk; // Set SLEEPDEEP bit
    PWR->CR |= PWR_CR_PDDS; // Set power-down mode
    __WFI(); // Wait for interrupt
}

int main() {
    // System configuration for low-power mode
    RCC->APB1ENR |= RCC_APB1ENR_PWREN; // Enable power interface clock

    while (1) {
        enterSleepMode(); // Enter sleep mode
        // enterDeepSleepMode(); // Enter deep sleep mode
    }
}
Explanation:

enterSleepMode(): Enters sleep mode.
enterDeepSleepMode(): Enters deep sleep mode.
Peripheral Control:

Enable and disable peripherals as needed to save power.

Code: Peripheral Control (Pseudo-code for ARM Cortex-M)

cpp
Copy code
#include "stm32f4xx.h"

void enablePeripheral() {
    RCC->APB1ENR |= RCC_APB1ENR_TIM2EN; // Enable Timer2 clock
    TIM2->CR1 |= TIM_CR1_CEN; // Enable Timer2
}

void disablePeripheral() {
    TIM2->CR1 &= ~TIM_CR1_CEN; // Disable Timer2
    RCC->APB1ENR &= ~RCC_APB1ENR_TIM2EN; // Disable Timer2 clock
}

int main() {
    enablePeripheral();
    // Use peripheral

    disablePeripheral();

    while (1) {
        // Main loop
    }
}
Explanation:

enablePeripheral(): Enables Timer2.
disablePeripheral(): Disables Timer2.
Efficient Coding Practices:

Write efficient code to minimize CPU usage and power consumption.

Code: Efficient Looping

cpp
Copy code
#include "stm32f4xx.h"

void processSensorData(const uint32_t* data, size_t size) {
    for (size_t i = 0; i < size; ++i) {
        // Process data[i]
    }
}

int main() {
    uint32_t sensorData[100];
    // Initialize and read sensor data

    processSensorData(sensorData, 100);

    while (1) {
        // Main loop
    }
}
Explanation:

processSensorData(): Efficiently processes sensor data.
Daily Challenge:
Implement DMA to transfer data from a peripheral (e.g., ADC) to memory.
Enter a low-power mode and wake up on an external interrupt.
Enable and disable peripherals based on the application's needs to save power.
Optimize an existing piece of code to reduce CPU usage and power consumption.