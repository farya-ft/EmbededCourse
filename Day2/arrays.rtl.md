### آرایه‌ها در سیستم‌های تعبیه‌شده و استفاده از کتابخانه HAL

آرایه‌ها یکی از اصول پایه‌ای برنامه‌نویسی هستند که برای ذخیره و مدیریت مجموعه‌ای از داده‌ها استفاده می‌شوند. در اینجا به توضیح کامل آرایه‌ها و نحوه استفاده از آن‌ها در سیستم‌های تعبیه‌شده با استفاده از کتابخانه 
HAL (Hardware Abstraction Layer) می‌پردازیم.

#### تعریف آرایه‌ها

آرایه‌ها نوعی از متغیرها هستند که می‌توانند چندین مقدار از یک نوع داده‌ای خاص را ذخیره کنند. به هر عنصر آرایه با استفاده از یک اندیس (یا شاخص) دسترسی پیدا می‌کنیم.

##### تعریف آرایه

برای تعریف یک آرایه در زبان C یا ++C از ساختار زیر استفاده می‌کنیم:

```c
type arrayName[arraySize];
```

- `type`: نوع داده‌ای که آرایه ذخیره می‌کند (مثلاً `int`، `float`، `char`).
- `arrayName`: نام آرایه.
- `arraySize`: اندازه آرایه (تعداد عناصر).

مثال:

```c
int myArray[10]; // تعریف آرایه‌ای از نوع int با اندازه 10
```

##### مقداردهی آرایه

آرایه‌ها را می‌توان به صورت زیر مقداردهی کرد:

```c
int myArray[5] = {1, 2, 3, 4, 5};
```

#### استفاده از آرایه‌ها در سیستم‌های تعبیه‌شده

در سیستم‌های تعبیه‌شده، آرایه‌ها برای مدیریت داده‌هایی مانند خواندن داده‌های سنسور، ذخیره مقادیر پورت‌ها و موارد دیگر بسیار مفید هستند.

##### مثال: خواندن داده‌های سنسور

فرض کنید می‌خواهیم داده‌های چندین سنسور را بخوانیم و در یک آرایه ذخیره کنیم. از کتابخانه 
HAL
 برای خواندن داده‌های 
ADC
 استفاده می‌کنیم.

##### کد مثال با استفاده از HAL

```c
#include "main.h"
#include "stm32f1xx_hal.h"

#define NUM_SENSORS 5

ADC_HandleTypeDef hadc1;
uint32_t sensorValues[NUM_SENSORS];

void SystemClock_Config(void);
void MX_GPIO_Init(void);
void MX_ADC1_Init(void);

int main(void) {
    HAL_Init();
    SystemClock_Config();
    MX_GPIO_Init();
    MX_ADC1_Init();

    while (1) {
        for (int i = 0; i < NUM_SENSORS; i++) {
            HAL_ADC_Start(&hadc1);
            if (HAL_ADC_PollForConversion(&hadc1, 1000000) == HAL_OK) {
                sensorValues[i] = HAL_ADC_GetValue(&hadc1);
            }
            HAL_ADC_Stop(&hadc1);
        }

        HAL_Delay(1000); // تاخیر 1 ثانیه‌ای
    }
}

void SystemClock_Config(void) {
    // پیکربندی ساعت سیستم
}

void MX_GPIO_Init(void) {
    // پیکربندی GPIO
}

void MX_ADC1_Init(void) {
    ADC_ChannelConfTypeDef sConfig = {0};

    hadc1.Instance = ADC1;
    hadc1.Init.ScanConvMode = ADC_SCAN_DISABLE;
    hadc1.Init.ContinuousConvMode = DISABLE;
    hadc1.Init.DiscontinuousConvMode = DISABLE;
    hadc1.Init.ExternalTrigConv = ADC_SOFTWARE_START;
    hadc1.Init.DataAlign = ADC_DATAALIGN_RIGHT;
    hadc1.Init.NbrOfConversion = 1;
    if (HAL_ADC_Init(&hadc1) != HAL_OK) {
        // مدیریت خطا
    }

    sConfig.Channel = ADC_CHANNEL_0;
    sConfig.Rank = ADC_REGULAR_RANK_1;
    sConfig.SamplingTime = ADC_SAMPLETIME_1CYCLE_5;
    if (HAL_ADC_ConfigChannel(&hadc1, &sConfig) != HAL_OK) {
        // مدیریت خطا
    }
}
```

#### توضیحات کد

- **تعریف آرایه**: آرایه `sensorValues` برای ذخیره مقادیر خوانده شده از سنسورها تعریف شده است.
- **حلقه‌ی اصلی**: در حلقه‌ی اصلی برنامه، داده‌های هر سنسور خوانده شده و در آرایه ذخیره می‌شود.
- **تابع `HAL_ADC_Start`**: شروع تبدیل آنالوگ به دیجیتال.
- **تابع `HAL_ADC_PollForConversion`**: منتظر ماندن برای تکمیل تبدیل.
- **تابع `HAL_ADC_GetValue`**: دریافت مقدار تبدیل شده.
- **تاخیر 1 ثانیه‌ای**: برای نمونه‌گیری با فاصله زمانی.

### کاربردهای دیگر آرایه‌ها در سیستم‌های تعبیه‌شده

1. **ذخیره و پردازش داده‌های سریال**: آرایه‌ها برای ذخیره داده‌های دریافتی از UART، SPI یا I2C استفاده می‌شوند.
2. **مدیریت پورت‌ها**: ذخیره وضعیت پین‌های GPIO.
3. **پیاده‌سازی فیلترهای دیجیتال**: استفاده از آرایه‌ها برای ذخیره نمونه‌های ورودی و خروجی.

### نتیجه‌گیری

آرایه‌ها ابزار قدرتمندی برای مدیریت و پردازش داده‌ها در سیستم‌های تعبیه‌شده هستند. با استفاده از کتابخانه HAL، می‌توانیم به راحتی داده‌های سنسورها و پورت‌ها را خوانده و پردازش کنیم. تسلط بر آرایه‌ها و استفاده صحیح از آن‌ها در برنامه‌های تعبیه‌شده می‌تواند به بهبود عملکرد و کارایی سیستم کمک کند.