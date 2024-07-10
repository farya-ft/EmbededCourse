### Day 13: Advanced Topics - DMA and Power Management
Today, we will cover two advanced topics in embedded systems: Direct Memory Access (DMA) and power management. These concepts are essential for optimizing performance and efficiency in embedded applications.

#### 1. Direct Memory Access (DMA)
DMA is a feature that allows peripherals to directly transfer data to and from memory without involving the CPU, significantly improving data transfer efficiency and freeing the CPU for other tasks.

##### DMA Basics:

* Memory-to-Memory Transfers: Data is moved between memory regions.
* Peripheral-to-Memory Transfers: Data from a peripheral is moved to memory.
* Memory-to-Peripheral Transfers: Data from memory is moved to a peripheral.
##### DMA Example (Pseudo-code for ARM Cortex-M)

```cpp

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
```
##### Explanation:

initDMA(): Configures DMA for memory-to-memory transfers.
waitForDMACompletion(): Waits for the DMA transfer to complete.
DMA in Peripherals:

DMA can be used with peripherals like UART, SPI, and ADC for efficient data transfers.

##### DMA with UART (Pseudo-code for ARM Cortex-M)

```cpp

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

void startDMATransfer() { //This function enables DMA1 Stream 6 to start the data transfer.
    DMA1_Stream6->CR |= DMA_SxCR_EN; // Enable DMA stream
}

int main() { //The main loop runs indefinitely, with the DMA handling the data transmission in the background.
    uint8_t txBuffer[] = "Hello, DMA!"; // A transmit buffer txBuffer is defined with the string "Hello, DMA!"

    initUART_DMA(); //is called to set up USART2 and DMA1
    startDMATransfer(); //is called to start the DMA transfer

    while (1) {
        // Main loop
    }
}
```
##### Explanation:
* This code sets up UART (USART2) with DMA (Direct Memory Access) to transmit data on an STM32F4 microcontroller.

initUART_DMA(): Configures USART2 and DMA for UART transmission.
startDMATransfer(): Starts the DMA transfer.

#### What Happens Overall
##### 1.Initialization:

* The clock for USART2 and DMA1 is enabled.
* USART2 is configured for a baud rate of 9600, with DMA transmission enabled.
* DMA1 Stream 6 is configured to transfer data from the memory (txBuffer) to the USART2 data register.
##### 2.Starting DMA Transfer:

* The DMA stream is enabled, starting the transfer of data from txBuffer to USART2.
##### 3.Main Loop:

* The main loop runs indefinitely, but the actual data transmission is handled by the DMA, offloading the CPU.


#### What is DMA and Its Advantages
 DMA (Direct Memory Access) allows peripherals to directly read from or write to memory without involving the CPU. This has several advantages:

* Reduced CPU Load: Offloads data transfer tasks from the CPU, allowing it to perform other operations or enter low-power states.
* Efficient Data Transfer: Enables fast and efficient data transfers, especially useful for large data blocks.
* Minimized Latency: Reduces the time latency compared to CPU-driven data transfers.
##### Summary
* The code sets up UART (USART2) with DMA on an STM32F4 microcontroller to transmit data.
* DMA is configured to handle data transmission, freeing up the CPU.
* The main loop runs indefinitely, with DMA handling the data transfer in the background.
* Using DMA reduces CPU load and improves data transfer efficiency.
---
### 2. Power Management
Power management is critical in embedded systems to extend battery life and reduce energy consumption. Techniques include low-power modes, peripheral control, and efficient coding practices.

### Low-Power Modes:

Microcontrollers often support multiple low-power modes, such as sleep, deep sleep, and standby.

##### Entering Low-Power Mode (Pseudo-code for ARM Cortex-M)

```cpp

#include "stm32f4xx.h"

void enterSleepMode() {
    SCB->SCR &= ~SCB_SCR_SLEEPDEEP_Msk; // Clear SLEEPDEEP bit
    //پاک کردن این بیت اطمینان می‌دهد که میکروکنترلر وارد حالت خواب  می‌شود نه حالت خواب عمیق.
    __WFI(); // Wait for interrupt
    //انتظار برای وقفه) یک تابع ذاتی است که سیبپو را تا زمان وقوع یک وقفه به حالت خواب می‌برد. این کار مصرف برق ان را تا زمان بیدار شدن  با وقفه بعدی کاهش می‌دهد.
}

void enterDeepSleepMode() {
    SCB->SCR |= SCB_SCR_SLEEPDEEP_Msk; // Set SLEEPDEEP bit
    // این بیت تعیین می‌کند که دستگاه وارد حالت خواب یا خواب عمیق شود.
    PWR->CR |= PWR_CR_PDDS; // Set power-down mode
    //خاموشی خواب عمیق را در رجیستر کنترل قدرت  تنظیم می‌کند.
    // این بیت میکروکنترلر را برای ورود به حالت خاموشی وقتی در خواب عمیق است پیکربندی می‌کند.
    __WFI(); // Wait for interrupt
}

int main() {
    // System configuration for low-power mode
    RCC->APB1ENR |= RCC_APB1ENR_PWREN; // Enable power interface clock

    while (1) { // به صورت نامحدود اجرا می‌شود
        enterSleepMode(); // Enter sleep mode
        // برای وارد کردن میکروکنترلر به حالت خواب فراخوانی می‌کند.
        // enterDeepSleepMode(); // Enter deep sleep mode
    }
}
```
##### Explanation:

* This code demonstrates how to enter different low-power modes on an ARM Cortex-M microcontroller, specifically the STM32F4 series. The code provides two functions to enter sleep mode and deep sleep mode, and it configures the system to use these low-power modes.

* enterSleepMode(): Enters sleep mode.
* enterDeepSleepMode(): Enters deep sleep mode.

#### Registers Used
##### 1.System Control Block (SCB) Registers:

   * SCR (System Control Register):
     * SLEEPDEEP (Bit 2): Controls whether the device enters sleep or deep sleep mode.
         * 0: Sleep mode.
         * 1: Deep sleep mode.
##### 2.Power Control (PWR) Registers:

* .CR (Control Register):
   * PDDS (Bit 1): Power Down Deep Sleep.
     * 0: Enter stop mode when the CPU enters deep sleep.
     * 1: Enter standby mode when the CPU enters deep sleep.
##### 3.Reset and Clock Control (RCC) Registers:

* APB1ENR (APB1 Peripheral Clock Enable Register):
  * PWREN (Bit 28): Power interface clock enable.
    * 0: Power interface clock disabled.
    * 1: Power interface clock enabled.
##### Summary
* The code configures the STM32F4 microcontroller to enter either sleep mode or deep sleep mode using two functions.
* enterSleepMode() clears the SLEEPDEEP bit in the SCR and calls __WFI() to put the CPU in sleep mode.
* enterDeepSleepMode() sets the SLEEPDEEP and PDDS bits to enter deep sleep mode and calls __WFI() to put the CPU in deep sleep mode.
* The main function enables the power interface clock and continuously puts the * microcontroller into sleep mode (or deep sleep mode if uncommented).
* These low-power modes reduce power consumption, which is useful for energy-efficient applications.
---
### Peripheral Control:

Enable and disable peripherals as needed to save power.

##### Peripheral Control (Pseudo-code for ARM Cortex-M)

```cpp

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
```
##### Explanation:

enablePeripheral(): Enables Timer2.
disablePeripheral(): Disables Timer2.
Efficient Coding Practices:

### Write efficient code to minimize CPU usage and power consumption.

##### Efficient Looping

```cpp

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
```
##### Explanation:

processSensorData(): Efficiently processes sensor data.

!!! Daily Challenge:
* Implement DMA to transfer data from a peripheral (e.g., ADC) to memory.
* Enter a low-power mode and wake up on an external interrupt.
* Enable and disable peripherals based on the application's needs to save power.
* Optimize an existing piece of code to reduce CPU usage and power consumption.