###  : تکنیک‌های مدیریت توان در سیستم‌های تعبیه شده

امروز به تکنیک‌های مدیریت توان در سیستم‌های تعبیه شده می‌پردازیم. مدیریت کارآمد توان برای افزایش عمر باتری، کاهش اتلاف حرارت و بهینه‌سازی عملکرد کلی سیستم بسیار مهم است.

#### 1. اهمیت مدیریت توان

مدیریت موثر توان در سیستم‌های تعبیه شده چندین مزیت دارد:
- **افزایش عمر باتری:** برای دستگاه‌های قابل حمل و باتری‌دار حیاتی است.
- **کاهش مصرف انرژی:** هزینه‌های عملیاتی کمتر و تأثیر کمتر بر محیط زیست.
- **بهبود قابلیت اطمینان:** جلوگیری از گرم شدن بیش از حد و سایش قطعات.

#### 2. تکنیک‌های مدیریت توان

**2.1. حالت‌های کم‌مصرف**

بیشتر میکروکنترلرها حالت‌های کم‌مصرف مختلفی برای کاهش مصرف توان در دوره‌های بیکار یا غیر فعال دارند.

**مثال: کتابخانه Low Power در Arduino**

```cpp
#include <LowPower.h>

void setup() {
    // Initialization code
}

void loop() {
    // Main program loop

    // Enter power-down mode for 8 seconds
    LowPower.powerDown(SLEEP_8S, ADC_OFF, BOD_OFF);
}
```

**توضیح:**
- `LowPower.powerDown(mode, adc, bod)`:
 میکروکنترلر را به حالت کم‌مصرف (در این مثال 
 `SLEEP_8S`)
  با 
  ADC و BOD
   خاموش می‌برد.
در این خط کد، تابع `LowPower.powerDown()` میکروکنترلر را به حالت کم‌مصرف می‌برد. پارامترهای ورودی این تابع مشخص می‌کنند که میکروکنترلر به چه مدتی در حالت خواب (sleep) بماند و کدام بخش‌های میکروکنترلر در طول این مدت غیرفعال شوند.

```cpp
LowPower.powerDown(SLEEP_8S, ADC_OFF, BOD_OFF);
```

**توضیح پارامترهای این تابع:**

- `SLEEP_8S`: این پارامتر نشان می‌دهد که میکروکنترلر به مدت 8
 ثانیه در حالت خواب قرار گیرد.
- `ADC_OFF`: این پارامتر نشان می‌دهد که مبدل آنالوگ به دیجیتال 
(ADC) در طول این مدت غیرفعال شود تا مصرف توان کاهش یابد.
- `BOD_OFF`: این پارامتر نشان می‌دهد که مدار تشخیص کاهش ولتاژ 
(Brown-out Detector یا BOD)
 غیرفعال شود.

### BOD (Brown-out Detector)

**مدار تشخیص کاهش ولتاژ (BOD)** 
یک ویژگی در میکروکنترلرها است که به منظور نظارت بر ولتاژ تغذیه استفاده می‌شود. وظیفه‌ی 
BOD
 این است که هنگامی که ولتاژ تغذیه میکروکنترلر از یک مقدار مشخص (آستانه) پایین‌تر می‌آید، میکروکنترلر را ریست کند یا به حالت امن ببرد. این کار باعث جلوگیری از عملکرد نادرست میکروکنترلر به دلیل ولتاژ پایین و ناپایدار می‌شود.

**غیرفعال کردن BOD (BOD_OFF):**

در برخی کاربردها، ممکن است نیاز باشد که برای کاهش مصرف توان، 
BOD
 غیرفعال شود. با این حال، باید توجه داشت که این کار خطراتی نیز به همراه دارد، زیرا در صورت کاهش ولتاژ تغذیه، میکروکنترلر ممکن است به درستی کار نکند و دچار مشکلات عملکردی شود.

### جمع‌بندی

خط کد `LowPower.powerDown(SLEEP_8S, ADC_OFF, BOD_OFF);` میکروکنترلر را به مدت 8 ثانیه به حالت خواب می‌برد و در این مدت 
ADC و BOD
 را غیرفعال می‌کند تا مصرف توان کاهش یابد. غیرفعال کردن 
 BOD
  به مصرف توان کمتر کمک می‌کند، اما باید با احتیاط انجام شود زیرا ممکن است میکروکنترلر را در برابر کاهش ولتاژ تغذیه آسیب‌پذیر کند.
**2.2. مدیریت کلاک**

کاهش فرکانس کلاک یا استفاده از اسیلاتورهای داخلی به جای کریستال‌های خارجی با فرکانس بالا می‌تواند توان را صرفه‌جویی کند.

**مثال: مدیریت کلاک**

```cpp
#include <avr/power.h>

void setup() {
    // Set system clock to 8 MHz
    clock_prescale_set(clock_div_2);
}

void loop() {
    // Main program loop
}
```

**توضیح:**
- `clock_prescale_set(clock_div)`:
 تنظیم تقسیم فرکانس کلاک سیستم به فرکانس کمتر 
 (`clock_div_2`
  فرکانس کلاک را نصف می‌کند).

**2.3. مدیریت پریفرال‌ها**

غیر فعال کردن پریفرال‌ها و ماژول‌های غیر ضروری برای کاهش مصرف توان.

**مثال: مدیریت پریفرال‌ها**

```cpp
void setup() {
    // Disable ADC and other unused peripherals
    ADCSRA &= ~(1 << ADEN); // Disable ADC
}

void loop() {
    // Main program loop
}
```

**2.4. بهینه‌سازی اجرای کد**

الگوریتم‌های کارآمد و کد بهینه‌شده مصرف CPU و توان کلی را کاهش می‌دهد.

**مثال: کد بهینه‌شده**

```cpp
void loop() {
    // Use efficient algorithms and minimize unnecessary computations
}
```

#### 3. برداشت انرژی

استفاده از منابع انرژی تجدیدپذیر (خورشیدی، بادی) یا انرژی محیطی (ارتعاش، گرما) برای تأمین توان سیستم‌های تعبیه شده و کاهش وابستگی به باتری‌ها.

#### 4. پروفایلینگ توان و تست

اندازه‌گیری مصرف توان با استفاده از ابزارهایی مانند مولتی‌مترها، اسیلوسکوپ‌ها یا ابزارهای اختصاصی پروفایلینگ توان برای بهینه‌سازی و تأیید استراتژی‌های مدیریت توان.

#### 5. کاربردهای دنیای واقعی

پیاده‌سازی تکنیک‌های مدیریت توان در کاربردهای واقعی سیستم‌های تعبیه شده نیاز به تعادل بین الزامات عملکرد و اهداف کارایی توان دارد.

#### چالش روزانه:
1. حالت‌های کم‌مصرف را در پروژه تعبیه شده خود پیاده‌سازی کنید تا عمر باتری را افزایش دهید.
2. با تکنیک‌های مدیریت کلاک برای بهینه‌سازی مصرف توان آزمایش کنید.
3. پریفرال‌ها یا ماژول‌های غیر استفاده را شناسایی و غیر فعال کنید تا مصرف توان در حالت بیکار را کاهش دهید.
4. مصرف توان را با استفاده از ابزارها اندازه‌گیری و تحلیل کنید تا بهبودها را تأیید کنید.

### پیاده‌سازی با HAL

در اینجا مثال‌هایی از مدیریت توان با استفاده از 
HAL
 در میکروکنترلرهای 
 STM32
  آمده است.

#### مثال: حالت کم‌مصرف با HAL

```c
#include "main.h"

void SystemClock_Config(void);
void MX_GPIO_Init(void);
void MX_RTC_Init(void);

int main(void) {
    HAL_Init();
    SystemClock_Config();
    MX_GPIO_Init();
    MX_RTC_Init();

    while (1) {
        // Enter Stop Mode with RTC
        HAL_PWR_EnterSTOPMode(PWR_LOWPOWERREGULATOR_ON, PWR_STOPENTRY_WFI);

        // Reconfigure system clock after wake-up
        SystemClock_Config();
    }
}

void SystemClock_Config(void) {
    // Configure system clock
}

void MX_GPIO_Init(void) {
    // Initialize GPIO
}

void MX_RTC_Init(void) {
    // Initialize RTC
}
```

این کد یک برنامه ساده برای یک میکروکنترلر است که از کتابخانه HAL (Hardware Abstraction Layer) استفاده می‌کند. برنامه سیستم را به حالت کم‌مصرف (Stop Mode) با استفاده از تایمر RTC می‌برد و سپس بعد از بیدار شدن دوباره ساعت سیستم را پیکربندی می‌کند.

### توضیح بخش‌های مختلف کد

```cpp
#include "main.h"

void SystemClock_Config(void);
void MX_GPIO_Init(void);
void MX_RTC_Init(void);

int main(void) {
    HAL_Init();
    SystemClock_Config();
    MX_GPIO_Init();
    MX_RTC_Init();

    while (1) {
        // Enter Stop Mode with RTC
        HAL_PWR_EnterSTOPMode(PWR_LOWPOWERREGULATOR_ON, PWR_STOPENTRY_WFI);

        // Reconfigure system clock after wake-up
        SystemClock_Config();
    }
}

void SystemClock_Config(void) {
    // Configure system clock
}

void MX_GPIO_Init(void) {
    // Initialize GPIO
}

void MX_RTC_Init(void) {
    // Initialize RTC
}
```

### توضیح جزئیات کد

1. **شامل کردن فایل هدر اصلی:**
   ```cpp
   #include "main.h"
   ```
   این خط کد فایل هدر اصلی پروژه را شامل می‌کند که شامل تعریف‌ها و اعلان‌های مورد نیاز است.

2. **اعلان توابع:**
   ```cpp
   void SystemClock_Config(void);
   void MX_GPIO_Init(void);
   void MX_RTC_Init(void);
   ```
   این خطوط توابعی را اعلان می‌کنند که بعداً در برنامه استفاده می‌شوند. این توابع برای پیکربندی ساعت سیستم، مقداردهی اولیه به پورت‌های GPIO و مقداردهی اولیه به تایمر RTC استفاده می‌شوند.

3. **تابع main:**
   ```cpp
   int main(void) {
       HAL_Init();
       SystemClock_Config();
       MX_GPIO_Init();
       MX_RTC_Init();

       while (1) {
           // Enter Stop Mode with RTC
           HAL_PWR_EnterSTOPMode(PWR_LOWPOWERREGULATOR_ON, PWR_STOPENTRY_WFI);

           // Reconfigure system clock after wake-up
           SystemClock_Config();
       }
   }
   ```
   - `HAL_Init()`: این تابع کتابخانه HAL را مقداردهی اولیه می‌کند و تنظیمات اولیه میکروکنترلر را انجام می‌دهد.
   - `SystemClock_Config()`: این تابع ساعت سیستم را پیکربندی می‌کند.
   - `MX_GPIO_Init()`: این تابع پورت‌های GPIO را مقداردهی اولیه می‌کند.
   - `MX_RTC_Init()`: این تابع تایمر RTC را مقداردهی اولیه می‌کند.

   درون حلقه بی‌نهایت (`while (1)`):
   - `HAL_PWR_EnterSTOPMode(PWR_LOWPOWERREGULATOR_ON, PWR_STOPENTRY_WFI)`: این تابع میکروکنترلر را به حالت کم‌مصرف (Stop Mode) می‌برد. پارامتر `PWR_LOWPOWERREGULATOR_ON` نشان می‌دهد که از رگولاتور توان کم استفاده شود و `PWR_STOPENTRY_WFI` نشان می‌دهد که از دستور `Wait For Interrupt` برای ورود به حالت توقف استفاده شود.
   - `SystemClock_Config()`: این تابع دوباره ساعت سیستم را بعد از بیدار شدن از حالت توقف پیکربندی می‌کند.

4. **تعریف توابع:**
   ```cpp
   void SystemClock_Config(void) {
       // Configure system clock
   }

   void MX_GPIO_Init(void) {
       // Initialize GPIO
   }

   void MX_RTC_Init(void) {
       // Initialize RTC
   }
   ```
   این توابع در اینجا فقط اعلان شده‌اند و باید با کد پیکربندی مربوطه پر شوند. تابع `SystemClock_Config` برای پیکربندی ساعت سیستم، تابع `MX_GPIO_Init` برای مقداردهی اولیه پورت‌های GPIO و تابع `MX_RTC_Init` برای مقداردهی اولیه تایمر RTC استفاده می‌شوند.

### نتیجه‌گیری

این برنامه یک ساختار ساده برای استفاده از حالت کم‌مصرف (Stop Mode) با استفاده از تایمر RTC در میکروکنترلر فراهم می‌کند. میکروکنترلر به حالت کم‌مصرف می‌رود و بعد از بیدار شدن ساعت سیستم دوباره پیکربندی می‌شود تا میکروکنترلر بتواند به درستی به کار خود ادامه دهد.
#### مثال: مدیریت کلاک با HAL

```c
#include "main.h"

void SystemClock_Config(void);

int main(void) {
    HAL_Init();
    SystemClock_Config();

    while (1) {
        // Reduce clock frequency to save power
        HAL_RCC_DeInit();
        RCC_OscInitTypeDef RCC_OscInitStruct = {0};
        RCC_ClkInitTypeDef RCC_ClkInitStruct = {0};

        RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSI;
        RCC_OscInitStruct.HSIState = RCC_HSI_ON;
        RCC_OscInitStruct.HSICalibrationValue = RCC_HSICALIBRATION_DEFAULT;
        RCC_OscInitStruct.PLL.PLLState = RCC_PLL_NONE;
        if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK) {
            Error_Handler();
        }

        RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK | RCC_CLOCKTYPE_SYSCLK
                                    | RCC_CLOCKTYPE_PCLK1 | RCC_CLOCKTYPE_PCLK2;
        RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_HSI;
        RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
        RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV1;
        RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV1;

        if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_0) != HAL_OK) {
            Error_Handler();
        }

        // Main program loop
    }
}

void SystemClock_Config(void) {
    // Configure system clock
}
```

در این کد:
- **HAL_RCC_DeInit**: پیکربندی مجدد کلاک سیستم برای کاهش فرکانس و صرفه‌جویی در توان.
- **HAL_RCC_OscConfig**: تنظیم اسیلاتور HSI برای کلاک سیستم.

اگر سوال بیشتری دارید یا نیاز به توضیحات بیشتری دارید، حتماً بپرسید.