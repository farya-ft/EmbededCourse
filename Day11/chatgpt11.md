### Day 11: Interrupt Handling and Real-Time Constraints
Today, we will delve into the crucial aspects of embedded systems: handling interrupts and meeting real-time constraints. These topics are fundamental for developing responsive and reliable embedded applications.

#### 1. Interrupt Handling
Interrupts allow a system to respond to external events immediately, which is essential in real-time systems. We'll cover the basics of interrupts and how to handle them in embedded C++.

* Basics of Interrupts

An interrupt is a signal to the processor indicating an event that needs immediate attention. The processor temporarily halts the current execution flow to service the interrupt.

* Types of Interrupts:

External Interrupts: Triggered by external devices (e.g., GPIO pin change).
Internal Interrupts: Triggered by internal peripherals (e.g., timer overflow).
Interrupt Service Routine (ISR)

An ISR is a function that executes in response to an interrupt.

##### Simple ISR Example (Pseudo-code)

```cpp

#include <avr/io.h>
#include <avr/interrupt.h>

ISR(TIMER1_COMPA_vect) {
    // Timer1 compare match interrupt service routine
    PORTB ^= (1 << PB0); // Toggle LED connected to PB0
}

int main() {
    DDRB |= (1 << PB0); // Set PB0 as output
    TCCR1B |= (1 << WGM12) | (1 << CS12); // Configure Timer1 in CTC mode with prescaler
    OCR1A = 15624; // Set compare value for 1Hz toggle
    TIMSK1 |= (1 << OCIE1A); // Enable Timer1 compare interrupt
    sei(); // Enable global interrupts

    while (1) {
        // Main loop
    }
}
```
##### Explanation:

ISR(TIMER1_COMPA_vect): Defines the ISR for Timer1 compare match.
sei(): Enables global interrupts.
Nested Vectored Interrupt Controller (NVIC)

In ARM Cortex-M microcontrollers, the NVIC manages interrupts, allowing nested interrupts with different priority levels.

##### NVIC Example (Pseudo-code for ARM Cortex-M)

```cpp

#include "stm32f4xx.h"
//This function is the interrupt handler for Timer 2.
void TIM2_IRQHandler(void) {
    if (TIM2->SR & TIM_SR_UIF) { // Check if update interrupt flag is set
        TIM2->SR &= ~TIM_SR_UIF; // Clear the update interrupt flag
        GPIOA->ODR ^= GPIO_ODR_OD5; //Toggles the state of the LED connected to PA5 by using XOR on the output data register (ODR) of GPIOA.
    }
}

int main() {
    RCC->AHB1ENR |= RCC_AHB1ENR_GPIOAEN; // Enable GPIOA clock
    GPIOA->MODER |= GPIO_MODER_MODER5_0; // Set PA5 as output

    RCC->APB1ENR |= RCC_APB1ENR_TIM2EN; // Enable Timer2 clock
    TIM2->PSC = 1600 - 1; // Set prescaler to 1600
    TIM2->ARR = 10000 - 1; // Set auto-reload register to 10000 which defines the period of the timer.
    TIM2->DIER |= TIM_DIER_UIE; // Enable update interrupt
    TIM2->CR1 |= TIM_CR1_CEN; // Enable Timer2

    NVIC_EnableIRQ(TIM2_IRQn); // Enable Timer2 interrupt in NVIC

    while (1) {
        // Main loop.The main loop is empty and runs indefinitely.
    }
}
```

##### Explanation:
* This code is designed to configure and use Timer 2 (TIM2) on an STM32F4 microcontroller to toggle an LED connected to pin PA5 periodically
* TIM2_IRQHandler: Defines the ISR for Timer2.
* NVIC_EnableIRQ(TIM2_IRQn): Enables Timer2 interrupt in NVIC.
#### 2. Real-Time Constraints
Real-time systems must meet specific timing constraints to ensure correct operation. We'll discuss the key concepts and techniques for designing and implementing real-time systems.

##### Hard vs. Soft Real-Time Systems

Hard Real-Time: Missing a deadline can cause catastrophic failure (e.g., automotive airbag system).
Soft Real-Time: Missing a deadline results in degraded performance (e.g., video streaming).
Real-Time Scheduling

##### Real-time operating systems (RTOS) use various scheduling algorithms to manage tasks:

* Fixed-Priority Scheduling (FPS): Tasks are assigned fixed priorities.
* Rate Monotonic Scheduling (RMS): Static priority scheduling where tasks with shorter periods have higher priorities.
* Earliest Deadline First (EDF): Dynamic priority scheduling where tasks with the nearest deadlines have the highest priorities.
##### Fixed-Priority Scheduling (Pseudo-code using FreeRTOS)

```cpp

#include <FreeRTOS.h>
#include <task.h>

void vHighPriorityTask(void *pvParameters) {
    while (1) {
        // High priority task actions
        vTaskDelay(pdMS_TO_TICKS(100));
    }
}

void vLowPriorityTask(void *pvParameters) {
    while (1) {
        // Low priority task actions
        vTaskDelay(pdMS_TO_TICKS(200));
    }
}

int main() {
    xTaskCreate(vHighPriorityTask, "High Priority Task", configMINIMAL_STACK_SIZE, NULL, 2, NULL);
    xTaskCreate(vLowPriorityTask, "Low Priority Task", configMINIMAL_STACK_SIZE, NULL, 1, NULL);

    vTaskStartScheduler();

    for (;;);
    return 0;
}
```

##### Explanation:

xTaskCreate: Creates tasks with different priorities.
vTaskStartScheduler(): Starts the RTOS scheduler.
Task Timing and Jitter

Ensuring that tasks run at precise intervals is critical. Jitter, the variability in task execution timing, should be minimized.

##### Minimizing Jitter (Pseudo-code using FreeRTOS)

```cpp

#include <FreeRTOS.h>
#include <task.h>

void vPeriodicTask(void *pvParameters) {
    TickType_t xLastWakeTime = xTaskGetTickCount();
    const TickType_t xFrequency = pdMS_TO_TICKS(100);

    while (1) {
        // Task actions
        vTaskDelayUntil(&xLastWakeTime, xFrequency);
    }
}

int main() {
    xTaskCreate(vPeriodicTask, "Periodic Task", configMINIMAL_STACK_SIZE, NULL, 1, NULL);

    vTaskStartScheduler();

    for (;;);
    return 0;
}
```
##### Explanation:
* This code demonstrates the use of FreeRTOS to create a periodic task that minimizes jitter
* TaskDelayUntil: Ensures the task runs at precise intervals, minimizing jitter.

###### Initialization:

* xLastWakeTime is initialized with the current tick count using xTaskGetTickCount().
* xFrequency is set to 100 milliseconds, converted to ticks using pdMS_TO_TICKS(100).
###### Task Loop:

Inside the infinite while (1) loop, the task performs its actions (not specified in this code).
vTaskDelayUntil(&xLastWakeTime, xFrequency) is used to delay the task until the next 100 ms interval, maintaining a precise periodic schedule.

#### What is Jitter?
Jitter is the variation in time between the actual execution of a task and its expected or scheduled execution time. It is essentially the "noise" in timing, where a task might not run exactly at its scheduled interval due to various delays in the system.

##### Sources of Jitter:

* Interrupts from other tasks.
* Operating system overhead.
* Variations in task execution time.
##### Minimizing Jitter:

* Using vTaskDelayUntil instead of vTaskDelay to ensure tasks wake up at fixed intervals.
* Prioritizing tasks appropriately.
* Ensuring tasks complete within their allotted time.
#### How the Code Minimizes Jitter
In this code, the use of vTaskDelayUntil(&xLastWakeTime, xFrequency) helps minimize jitter by ensuring that the task runs at precise intervals of 100 milliseconds. Unlike vTaskDelay, which adds a fixed delay to the current time and could accumulate timing errors, vTaskDelayUntil calculates the next wake-up time based on a reference time (xLastWakeTime). This helps maintain a consistent periodic execution schedule, reducing jitter.

##### summary
* The code sets up a periodic task in FreeRTOS to run every 100 milliseconds.
* It uses vTaskDelayUntil to ensure the task executes at precise intervals, minimizing jitter.
* Jitter is the variation in timing between scheduled and actual execution times, which the code aims to minimize for predictable task scheduling.

----

##### Real-Time Constraints in Embedded Systems

In embedded systems, meeting real-time constraints often involves:

* Using hardware timers to trigger tasks.
* Prioritizing interrupts and tasks.
* Optimizing critical sections to reduce latency.
##### Real-Time Constraints with Timer (Pseudo-code for ARM Cortex-M)

```cpp

#include "stm32f4xx.h"

void TIM2_IRQHandler(void) {
    if (TIM2->SR & TIM_SR_UIF) { // Check if update interrupt flag is set
        TIM2->SR &= ~TIM_SR_UIF; // Clear the update interrupt flag
        GPIOA->ODR ^= GPIO_ODR_OD5; // Toggle LED connected to PA5
    }
}

int main() {
    RCC->AHB1ENR |= RCC_AHB1ENR_GPIOAEN; // Enable GPIOA clock
    GPIOA->MODER |= GPIO_MODER_MODER5_0; // Set PA5 as output

    RCC->APB1ENR |= RCC_APB1ENR_TIM2EN; // Enable Timer2 clock
    TIM2->PSC = 1600 - 1; // Set prescaler to 1600
    TIM2->ARR = 10000 - 1; // Set auto-reload register to 10000
    TIM2->DIER |= TIM_DIER_UIE; // Enable update interrupt
    TIM2->CR1 |= TIM_CR1_CEN; // Enable Timer2

    NVIC_EnableIRQ(TIM2_IRQn); // Enable Timer2 interrupt in NVIC

    while (1) {
        // Main loop
    }
}
```
##### Explanation:

Timer2 generates periodic interrupts to toggle an LED, ensuring precise timing.

!!! Daily Challenge:
* Implement an ISR to handle a button press interrupt and toggle an LED.
* Create an RTOS application with tasks of different priorities, ensuring that high-priority tasks preempt lower-priority ones.
* Measure and minimize jitter in a periodic task using FreeRTOS.