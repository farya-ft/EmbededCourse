### روز 12:
### رابط‌های جانبی - 
### GPIO، UART، I2C و SPI
 با استفاده از 
### HAL

#### مقدمه

رابط‌های جانبی 
(Peripheral Interfacing)
 نقش حیاتی در سیستم‌های تعبیه‌شده دارند. با استفاده از این رابط‌ها، می‌توانیم میکروکنترلر را به سایر قطعات و سنسورها متصل کنیم. امروز، به بررسی و پیاده‌سازی چهار رابط مهم شامل 
 GPIO، UART، I2C و SPI
  با استفاده از کتابخانه 
  HAL
   خواهیم پرداخت.

### 1. GPIO (General Purpose Input/Output)

#### GPIO چیست؟

GPIO
 به پین‌هایی گفته می‌شود که می‌توانند به عنوان ورودی یا خروجی تنظیم شوند. این پین‌ها برای خواندن وضعیت سنسورها یا کنترل کردن المان‌های خروجی مانند 
 LED
 ها و رله‌ها استفاده می‌شوند.

#### پیکربندی 
#### GPIO
 با استفاده از 
#### HAL

بیایید یک پین 
GPIO
 را به عنوان ورودی (مثلاً برای دکمه) و یک پین دیگر را به عنوان خروجی (مثلاً برای 
 LED)
  پیکربندی کنیم.

##### مراحل:

1. **باز کردن STM32CubeMX** و ایجاد یک پروژه جدید.
2. **انتخاب میکروکنترلر STM32F446RE**.
3. **پیکربندی 
PA0** به عنوان ورودی و 
**PA5**
 به عنوان خروجی.
4. **تولید پروژه** و باز کردن آن در 
STM32CubeIDE.

##### کد تولید شده (`main.c`)

```c
/* Includes ------------------------------------------------------------------*/
#include "main.h"

/* Private function prototypes -----------------------------------------------*/
void SystemClock_Config(void);
static void MX_GPIO_Init(void);

int main(void) {
  /* Reset of all peripherals, Initializes the Flash interface and the Systick. */
  HAL_Init();

  /* Configure the system clock */
  SystemClock_Config();

  /* Initialize all configured peripherals */
  MX_GPIO_Init();

  /* Infinite loop */
  while (1) {
    if (HAL_GPIO_ReadPin(GPIOA, GPIO_PIN_0) == GPIO_PIN_SET) {
      HAL_GPIO_WritePin(GPIOA, GPIO_PIN_5, GPIO_PIN_SET);
    } else {
      HAL_GPIO_WritePin(GPIOA, GPIO_PIN_5, GPIO_PIN_RESET);
    }
  }
}

/* GPIO Initialization Function */
static void MX_GPIO_Init(void) {
  GPIO_InitTypeDef GPIO_InitStruct = {0};

  /* GPIO Ports Clock Enable */
  __HAL_RCC_GPIOA_CLK_ENABLE();

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(GPIOA, GPIO_PIN_5, GPIO_PIN_RESET);

  /*Configure GPIO pin : PA0 */
  GPIO_InitStruct.Pin = GPIO_PIN_0;
  GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);

  /*Configure GPIO pin : PA5 */
  GPIO_InitStruct.Pin = GPIO_PIN_5;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);
}

/* System Clock Configuration */
void SystemClock_Config(void) {
  // System clock configuration code
}

/* Error Handler */
void Error_Handler(void) {
  while (1) {
    // Stay here
  }
}
```

### 2. UART (Universal Asynchronous Receiver/Transmitter)

#### UART چیست؟

UART یک پروتکل ارتباطی سریال است که برای تبادل داده بین میکروکنترلر و دستگاه‌های دیگر مانند کامپیوتر یا ماژول‌های سریال استفاده می‌شود.

#### پیکربندی UART با استفاده از HAL

بیایید یک رابط UART را برای ارتباط سریال پیکربندی کنیم.

##### مراحل:

1. **باز کردن STM32CubeMX** و ایجاد یک پروژه جدید.
2. **انتخاب میکروکنترلر STM32F446RE**.
3. **فعال کردن USART2** و تنظیم Baud Rate به 9600.
4. **تولید پروژه** و باز کردن آن در STM32CubeIDE.

##### کد تولید شده (`main.c`)

```c
/* Includes ------------------------------------------------------------------*/
#include "main.h"

/* Private variables ---------------------------------------------------------*/
UART_HandleTypeDef huart2;

/* Private function prototypes -----------------------------------------------*/
void SystemClock_Config(void);
static void MX_GPIO_Init(void);
static void MX_USART2_UART_Init(void);

int main(void) {
  /* Reset of all peripherals, Initializes the Flash interface and the Systick. */
  HAL_Init();

  /* Configure the system clock */
  SystemClock_Config();

  /* Initialize all configured peripherals */
  MX_GPIO_Init();
  MX_USART2_UART_Init();

  /* Infinite loop */
  while (1) {
    uint8_t msg[] = "Hello, UART!\r\n";
    HAL_UART_Transmit(&huart2, msg, sizeof(msg), HAL_MAX_DELAY);
    HAL_Delay(1000);
  }
}

/* USART2 Initialization Function */
static void MX_USART2_UART_Init(void) {
  huart2.Instance = USART2;
  huart2.Init.BaudRate = 9600;
  huart2.Init.WordLength = UART_WORDLENGTH_8B;
  huart2.Init.StopBits = UART_STOPBITS_1;
  huart2.Init.Parity = UART_PARITY_NONE;
  huart2.Init.Mode = UART_MODE_TX_RX;
  huart2.Init.HwFlowCtl = UART_HWCONTROL_NONE;
  huart2.Init.OverSampling = UART_OVERSAMPLING_16;
  if (HAL_UART_Init(&huart2) != HAL_OK) {
    Error_Handler();
  }
}

/* System Clock Configuration */
void SystemClock_Config(void) {
  // System clock configuration code
}

/* Error Handler */
void Error_Handler(void) {
  while (1) {
    // Stay here
  }
}
```

### 3. I2C (Inter-Integrated Circuit)

#### I2C چیست؟

I2C یک پروتکل ارتباطی سریال دو سیمه است که برای تبادل داده بین میکروکنترلر و دستگاه‌های جانبی مانند سنسورها و حافظه‌های خارجی استفاده می‌شود.

#### پیکربندی I2C با استفاده از HAL

بیایید یک رابط I2C را برای ارتباط با یک دستگاه جانبی پیکربندی کنیم.

##### مراحل:

1. **باز کردن STM32CubeMX** و ایجاد یک پروژه جدید.
2. **انتخاب میکروکنترلر STM32F446RE**.
3. **فعال کردن I2C1** و تنظیمات پیش‌فرض.
4. **تولید پروژه** و باز کردن آن در STM32CubeIDE.

##### کد تولید شده (`main.c`)

```c
/* Includes ------------------------------------------------------------------*/
#include "main.h"

/* Private variables ---------------------------------------------------------*/
I2C_HandleTypeDef hi2c1;

/* Private function prototypes -----------------------------------------------*/
void SystemClock_Config(void);
static void MX_GPIO_Init(void);
static void MX_I2C1_Init(void);

int main(void) {
  /* Reset of all peripherals, Initializes the Flash interface and the Systick. */
  HAL_Init();

  /* Configure the system clock */
  SystemClock_Config();

  /* Initialize all configured peripherals */
  MX_GPIO_Init();
  MX_I2C1_Init();

  /* Infinite loop */
  while (1) {
    uint8_t data[2] = {0x01, 0x02};
    HAL_I2C_Master_Transmit(&hi2c1, 0x50 << 1, data, sizeof(data), HAL_MAX_DELAY);
    HAL_Delay(1000);
  }
}

/* I2C1 Initialization Function */
static void MX_I2C1_Init(void) {
  hi2c1.Instance = I2C1;
  hi2c1.Init.ClockSpeed = 100000;
  hi2c1.Init.DutyCycle = I2C_DUTYCYCLE_2;
  hi2c1.Init.OwnAddress1 = 0;
  hi2c1.Init.AddressingMode = I2C_ADDRESSINGMODE_7BIT;
  hi2c1.Init.DualAddressMode = I2C_DUALADDRESS_DISABLE;
  hi2c1.Init.OwnAddress2 = 0;
  hi2c1.Init.GeneralCallMode = I2C_GENERALCALL_DISABLE;
  hi2c1.Init.NoStretchMode = I2C_NOSTRETCH_DISABLE;
  if (HAL_I2C_Init(&hi2c1) != HAL_OK) {
    Error_Handler();
  }
}

/* System Clock Configuration */
void SystemClock_Config(void) {
  // System clock configuration code
}

/* Error Handler */
void Error_Handler(void) {
  while (1) {
    // Stay here
  }
}
```

### 4. SPI (Serial Peripheral Interface)

#### SPI چیست؟

SPI یک پروتکل ارتباطی سریال چهار سیمه است که برای تبادل داده بین میکروکنترلر و دستگاه‌های جانبی مانند سنسورها و نمایشگرها استفاده می‌شود.

#### پیکربندی SPI با استفاده از HAL

بیایید یک رابط SPI را برای ارتباط با یک دستگاه جانبی پیکربندی کنیم.

##### مراحل:

1. **باز کردن STM32CubeMX** و ایجاد یک پروژه جدید.
2. **انتخاب میکروکنترلر STM32F446RE**.
3. **فعال کردن SPI1** و تنظیمات پیش‌فرض.
4. **تولید پروژه** و باز کردن آن در STM32CubeIDE.

##### کد تولید شده (`main.c`)

```c
/* Includes ------------------------------------------------------------------*/
#include "main.h"

/* Private variables ---------------------------------------------------------*/
SPI_HandleTypeDef hspi1;

/* Private
```

### مقایسه‌ی سه پروتکل SPI، I2C و UART

#### 1. SPI (Serial Peripheral Interface)

**مزایا:**
- **سرعت بالا:** SPI
 به دلیل استفاده از خطوط انتقال داده جداگانه برای ارسال و دریافت اطلاعات، سرعت بالایی دارد.
- **سادگی:** پروتکل 
SPI
 ساده‌ترین از این سه پروتکل است و به راحتی قابل پیاده‌سازی است.
- **عدم وابستگی به تعداد دستگاه‌های متصل:**
 SPI
  به عنوان یک رابط تمام دو طرفه عمل می‌کند و هیچ محدودیتی برای تعداد دستگاه‌های متصل به آن وجود ندارد.

**معایب:**
- **نیاز به سیگنال‌های جداگانه:** به دلیل استفاده از خطوط جداگانه برای ارسال و دریافت داده‌ها، SPI به چندین خط اضافی نیاز دارد که ممکن است بر روی فضای مدار چاپی 
(PCB)
 تأثیر منفی بگذارد.
- **محدودیت در فاصله:** SPI
 برای ارتباطات بلند مدت یا در فواصل طولانی ممکن است مناسب نباشد به دلیل نیاز به سیگنال‌های با کیفیت بالا.

#### 2. I2C (Inter-Integrated Circuit)

**مزایا:**
- **تعداد پین‌ها:** I2C نیاز به تعداد کمتری پین برای اتصال دارد (دو خط: خط داده و خط ساعت) که این امر به توسعه و پیاده‌سازی آسان‌تر کمک می‌کند.
- **قابلیت اتصال بین بردی:** I2C برای اتصال از طریق کابل‌های بین بردی (Inter-board) مناسب است و فاصله بین دستگاه‌ها را پوشش می‌دهد.
- **مصرف توان کم:** به دلیل استفاده از خطوط با توان کمتر، I2C مصرف توان کمتری دارد که برای برنامه‌های با باتری مناسب است.

**معایب:**
- **سرعت کمتر:** I2C
 در مقایسه با 
 SPI
  سرعت پایین‌تری دارد و برای انتقال داده‌های حجیم و سریع مناسب نیست.
- **محدودیت در تعداد دستگاه‌ها:** برای هر دستگاه در شبکه I2C نیاز به آدرس منحصر به فرد است که ممکن است باعث محدودیت در تعداد دستگاه‌های متصل شده شود.

#### 3. UART (Universal Asynchronous Receiver/Transmitter)

**مزایا:**
- **سادگی:** UART
 به دلیل ساختار ساده‌تر، به راحتی قابل پیاده‌سازی است و نیاز به تنظیمات پیچیده‌تری ندارد.
- **استفاده رایج:** UART
 به عنوان یک استاندارد رایج در بیشتر سیستم‌های تعبیه‌شده و ارتباطات سریالی استفاده می‌شود.
- **پشتیبانی از بردارهای برنامه‌نویسی متعدد:** UART
 با بردارهای برنامه‌نویسی مختلف (مثل 
 POSIX) 
 سازگار است و از طریق 
 USB
  به سادگی با کامپیوترها متصل می‌شود.

**معایب:**
- **محدودیت در فاصله:** نسبت به 
I2C و SPI، UART
 برای ارتباطات بلند مدت یا در فواصل طولانی مناسب نیست و ممکن است نویز بر روی خطوط سریالی تأثیر بگذارد.
- **سرعت پایین‌تر:** UART
 در مقایسه با 
 SPI
  سرعت پایین‌تری دارد و برای انتقال داده‌های بزرگ و سریع، مناسب نیست.

### نتیجه‌گیری

- **SPI**: برای ارتباطات با سرعت بالا و ازدحام کم مناسب است.
- **I2C**: برای ارتباطات کوتاه تراکم دار و کاربردهایی که نیاز به تعداد زیادی از دستگاه‌ها دارند مناسب است.
- **UART**: برای ارتباطات سریال ساده و کاربردهایی که نیاز به استفاده از بردارهای برنامه‌نویسی مختلف دارند مناسب است.

هر یک از این پروتکل‌ها دارای ویژگی‌ها و محدودیت‌های خود هستند که بسته به نیازهای مختلف، انتخاب می‌شوند.