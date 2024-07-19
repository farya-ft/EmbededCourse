### روز 18: مدیریت رویدادهای بی‌درنگ و وقفه‌ها در سیستم‌های تعبیه شده

امروز به مفاهیم مدیریت رویدادهای بی‌درنگ و وقفه‌ها در سیستم‌های تعبیه شده می‌پردازیم. مدیریت کارآمد وقفه‌ها برای پاسخگویی به موقع به رویدادهای خارجی و اطمینان از رفتار تعیین‌پذیر در برنامه‌های بی‌درنگ بسیار مهم است.

#### 1. درک وقفه‌ها

وقفه‌ها رویدادهای غیرهمزمانی هستند که توسط سخت‌افزار یا نرم‌افزار فعال می‌شوند و به طور موقت 
CPU 
را برای رسیدگی به وظایف یا رویدادهای حساس به زمان متوقف می‌کنند. آنها برای مدیریت رویدادهای بی‌درنگ مانند ورودی‌های سنسور، رویدادهای تایمر و سیگنال‌های ارتباطی ضروری هستند.

#### 2. مدیریت وقفه‌ها در سیستم‌های تعبیه شده

**2.1. روتین خدمات وقفه (ISR)**

یک روتین خدمات وقفه 
(ISR)
 تابعی است که در پاسخ به یک وقفه اجرا می‌شود. ISRها باید کوتاه و کارآمد باشند تا تاخیر وقفه را به حداقل برسانند و پاسخگویی به موقع را تضمین کنند.

**مثال: ISR ساده**

```cpp
// Interrupt Service Routine (ISR) for external interrupt
void externalInterruptHandler() {
    // Handle external interrupt event
}

void setup() {
    // Initialize external interrupt pin and ISR
    attachInterrupt(digitalPinToInterrupt(2), externalInterruptHandler, CHANGE);
}

void loop() {
    // Main program loop
}
```

**توضیح:**
- `attachInterrupt()`: تابع `externalInterruptHandler()` را برای مدیریت وقفه در پین 2 زمانی که وضعیت تغییر می‌کند، متصل می‌کند.

#### 3. انواع وقفه‌ها

**3.1. وقفه‌های خارجی**

این وقفه‌ها توسط رویدادهای خارجی مانند فشردن دکمه، خروجی سنسور یا سیگنال‌های ارتباطی ایجاد می‌شوند.

**مثال: وقفه خارجی**

```cpp
void setup() {
    pinMode(2, INPUT_PULLUP); // Set pin 2 as input with internal pull-up resistor
    attachInterrupt(digitalPinToInterrupt(2), externalInterruptHandler, FALLING);
}

void loop() {
    // Main program loop
}

void externalInterruptHandler() {
    // Handle external interrupt event
}
```

**3.2. وقفه‌های تایمر**

این وقفه‌ها توسط تایمرهای سخت‌افزاری تولید می‌شوند تا وظایف را در فواصل منظم اجرا کنند که برای وظایف بی‌درنگ مانند نمونه‌برداری دوره‌ای داده‌ها یا عملیات‌های کنترلی ضروری هستند.

**مثال: وقفه تایمر**

```cpp
void setup() {
    // Configure Timer1 to interrupt every 100ms
    Timer1.initialize(100000); // Set period in microseconds (100ms)
    Timer1.attachInterrupt(timerInterruptHandler); // Attach interrupt handler
}

void loop() {
    // Main program loop
}

void timerInterruptHandler() {
    // Handle timer interrupt event
}
```

#### 4. وقفه‌های تو در تو

مدیریت وقفه‌ها در داخل سایر وقفه‌ها نیاز به مدیریت دقیق اولویت‌ها و اطمینان از اینکه زمان اجرای 
ISR
 از محدودیت‌های تاخیر وقفه تجاوز نکند دارد.

#### 5. بهترین روش‌ها برای مدیریت وقفه‌ها

- **ISRها را کوتاه نگه دارید:** عملیات‌های داخل 
ISR
ها را به حداقل برسانید تا تاخیر وقفه کاهش یابد.
- **اجتناب از توابع تاخیر:** توابع تاخیر (مثل 
`delay()`) نباید در ISRها استفاده شوند زیرا می‌توانند وقفه‌های دیگر را مسدود کرده و بر پاسخگویی سیستم تأثیر بگذارند.
- **استفاده از عملیات اتمیک:** اطمینان حاصل کنید که بخش‌های بحرانی در ISRها با استفاده از عملیات اتمیک یا به طور موقت غیر فعال کردن وقفه‌ها 
(`noInterrupts()` و `interrupts()`
 در 
 Arduino)
  محافظت می‌شوند.

#### چالش روزانه:
1. یک رویکرد مبتنی بر وقفه در پروژه تعبیه شده خود برای مدیریت یک رویداد بی‌درنگ (مثل فشردن دکمه، ورودی سنسور) پیاده‌سازی کنید.
2. با انواع مختلف وقفه‌ها (مثل خارجی، تایمر) آزمایش کنید تا کاربرد و رفتار آنها را درک کنید.
3. روتین‌های مدیریت وقفه را بهینه‌سازی کنید تا تاخیر را به حداقل برسانید و پاسخگویی را بهبود دهید.
4. سناریوهای وقفه‌های تو در تو را بررسی کنید و استراتژی‌های مناسب برای مدیریت آنها در پروژه خود پیاده‌سازی کنید.

### پیاده‌سازی با HAL

در اینجا یک مثال برای مدیریت وقفه‌ها با استفاده از HAL آمده است.

#### مثال: وقفه خارجی با HAL

```c
#include "main.h"

void HAL_GPIO_EXTI_Callback(uint16_t GPIO_Pin) {
    if (GPIO_Pin == GPIO_PIN_0) {
        // Handle external interrupt event
    }
}

void SystemClock_Config(void);
static void MX_GPIO_Init(void);

int main(void) {
    HAL_Init();
    SystemClock_Config();
    MX_GPIO_Init();

    while (1) {
        // Main program loop
    }
}

void SystemClock_Config(void) {
    // Configure system clock
}

static void MX_GPIO_Init(void) {
    GPIO_InitTypeDef GPIO_InitStruct = {0};

    __HAL_RCC_GPIOA_CLK_ENABLE();

    GPIO_InitStruct.Pin = GPIO_PIN_0;
    GPIO_InitStruct.Mode = GPIO_MODE_IT_RISING;
    GPIO_InitStruct.Pull = GPIO_NOPULL;
    HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);

    HAL_NVIC_SetPriority(EXTI0_IRQn, 0, 0);
    HAL_NVIC_EnableIRQ(EXTI0_IRQn);
}

void EXTI0_IRQHandler(void) {
    HAL_GPIO_EXTI_IRQHandler(GPIO_PIN_0);
}
```

در این کد:
- **HAL_GPIO_EXTI_Callback**: تابع بازگشتی برای وقفه خارجی است.
- **MX_GPIO_Init**: پیکربندی پین 
GPIO برای وقفه.
- **EXTI0_IRQHandler**: مدیریت کننده وقفه خارجی برای پین 0.

این مثال نشان می‌دهد که چگونه می‌توانید وقفه‌های خارجی را با استفاده از 
HAL در میکروکنترلرهای 
STM32 مدیریت کنید. 

