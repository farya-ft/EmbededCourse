### روز 13: مباحث پیشرفته - DMA و مدیریت توان با استفاده از کتابخانه HAL

#### مقدمه

امروز به بررسی دو موضوع پیشرفته در سیستم‌های تعبیه‌شده می‌پردازیم: **DMA (Direct Memory Access)** و **مدیریت توان**. هر دو موضوع برای بهبود عملکرد و کارایی سیستم‌های تعبیه‌شده بسیار مهم هستند. با استفاده از کتابخانه HAL، این مفاهیم را پیاده‌سازی خواهیم کرد.

### 1. DMA (Direct Memory Access)

#### DMA چیست؟

DMA به ما اجازه می‌دهد تا داده‌ها را بین حافظه و واحدهای جانبی (مثل ADC، UART و ...) بدون دخالت CPU جابجا کنیم. این امر باعث کاهش بار پردازشی CPU و افزایش کارایی سیستم می‌شود.

#### پیکربندی DMA با استفاده از HAL

بیایید یک مثال از انتقال داده از حافظه به UART با استفاده از DMA را پیاده‌سازی کنیم.

##### مراحل:

1. **باز کردن STM32CubeMX** و ایجاد یک پروژه جدید.
2. **انتخاب میکروکنترلر STM32F446RE**.
3. **فعال کردن USART2** و تنظیم Baud Rate به 9600.
4. **فعال کردن DMA برای USART2 TX**.
5. **تولید پروژه** و باز کردن آن در STM32CubeIDE.

##### کد تولید شده (`main.c`)

```c
/* Includes ------------------------------------------------------------------*/
#include "main.h"

/* Private variables ---------------------------------------------------------*/
UART_HandleTypeDef huart2;
DMA_HandleTypeDef hdma_usart2_tx;

/* Private function prototypes -----------------------------------------------*/
void SystemClock_Config(void);
static void MX_GPIO_Init(void);
static void MX_DMA_Init(void);
static void MX_USART2_UART_Init(void);

int main(void) {
  /* Reset of all peripherals, Initializes the Flash interface and the Systick. */
  HAL_Init();

  /* Configure the system clock */
  SystemClock_Config();

  /* Initialize all configured peripherals */
  MX_GPIO_Init();
  MX_DMA_Init();
  MX_USART2_UART_Init();

  /* Infinite loop */
  uint8_t msg[] = "Hello, DMA UART!\r\n";
  while (1) {
    HAL_UART_Transmit_DMA(&huart2, msg, sizeof(msg) - 1);
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

/* DMA Initialization Function */
static void MX_DMA_Init(void) {
  /* DMA controller clock enable */
  __HAL_RCC_DMA1_CLK_ENABLE();

  /* Configure DMA request hdma_usart2_tx on DMA1_Stream6 */
  hdma_usart2_tx.Instance = DMA1_Stream6;
  hdma_usart2_tx.Init.Channel = DMA_CHANNEL_4;
  hdma_usart2_tx.Init.Direction = DMA_MEMORY_TO_PERIPH;
  hdma_usart2_tx.Init.PeriphInc = DMA_PINC_DISABLE;
  hdma_usart2_tx.Init.MemInc = DMA_MINC_ENABLE;
  hdma_usart2_tx.Init.PeriphDataAlignment = DMA_PDATAALIGN_BYTE;
  hdma_usart2_tx.Init.MemDataAlignment = DMA_MDATAALIGN_BYTE;
  hdma_usart2_tx.Init.Mode = DMA_NORMAL;
  hdma_usart2_tx.Init.Priority = DMA_PRIORITY_LOW;
  hdma_usart2_tx.Init.FIFOMode = DMA_FIFOMODE_DISABLE;
  if (HAL_DMA_Init(&hdma_usart2_tx) != HAL_OK) {
    Error_Handler();
  }

  __HAL_LINKDMA(&huart2, hdmatx, hdma_usart2_tx);
}

/* System Clock Configuration */
void SystemClock_Config(void) {
  // System clock configuration code
}

/* GPIO Initialization Function */
static void MX_GPIO_Init(void) {
  // GPIO initialization code
}

/* Error Handler */
void Error_Handler(void) {
  while (1) {
    // Stay here
  }
}
```

### 2. مدیریت توان (Power Management)

#### مدیریت توان چیست؟

مدیریت توان به مجموعه‌ای از تکنیک‌ها و روش‌ها گفته می‌شود که به کاهش مصرف انرژی در سیستم‌های تعبیه‌شده کمک می‌کنند. این تکنیک‌ها می‌توانند شامل استفاده از حالت‌های خواب (Sleep) و توقف (Stop) برای کاهش مصرف توان در زمان‌های غیر فعال بودن سیستم باشند.

#### پیکربندی و استفاده از حالت‌های مدیریت توان با HAL

بیایید به عنوان مثال یک میکروکنترلر را به حالت خواب (Sleep) ببریم و در صورت فشار دادن یک دکمه، از حالت خواب خارج شویم.

##### مراحل:

1. **باز کردن STM32CubeMX** و ایجاد یک پروژه جدید.
2. **انتخاب میکروکنترلر STM32F446RE**.
3. **پیکربندی PA0 به عنوان ورودی و فعال‌سازی External Interrupt برای این پین**.
4. **تولید پروژه** و باز کردن آن در STM32CubeIDE.

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
    HAL_SuspendTick();
    HAL_PWR_EnterSLEEPMode(PWR_MAINREGULATOR_ON, PWR_SLEEPENTRY_WFI);
    HAL_ResumeTick();
  }
}

/* GPIO Initialization Function */
static void MX_GPIO_Init(void) {
  GPIO_InitTypeDef GPIO_InitStruct = {0};

  /* GPIO Ports Clock Enable */
  __HAL_RCC_GPIOA_CLK_ENABLE();

  /*Configure GPIO pin : PA0 */
  GPIO_InitStruct.Pin = GPIO_PIN_0;
  GPIO_InitStruct.Mode = GPIO_MODE_IT_FALLING;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);

  /* EXTI interrupt init */
  HAL_NVIC_SetPriority(EXTI0_IRQn, 0, 0);
  HAL_NVIC_EnableIRQ(EXTI0_IRQn);
}

/* System Clock Configuration */
void SystemClock_Config(void) {
  // System clock configuration code
}

/* EXTI line0 interrupt service routine */
void EXTI0_IRQHandler(void) {
  HAL_GPIO_EXTI_IRQHandler(GPIO_PIN_0);
}

/* EXTI callback function */
void HAL_GPIO_EXTI_Callback(uint16_t GPIO_Pin) {
  if (GPIO_Pin == GPIO_PIN_0) {
    // Do something when the button is pressed
  }
}

/* Error Handler */
void Error_Handler(void) {
  while (1) {
    // Stay here
  }
}
```

### توضیحات:

- **HAL_SuspendTick و HAL_ResumeTick**: این توابع برای توقف و شروع مجدد تایمر SysTick استفاده می‌شوند تا در حالت خواب توان کمتری مصرف شود.
- **HAL_PWR_EnterSLEEPMode**: این تابع میکروکنترلر را به حالت خواب می‌برد.
- **HAL_GPIO_EXTI_Callback**: این تابع به عنوان کال‌بک (Callback) برای وقفه خارجی تنظیم شده است که وقتی دکمه فشار داده می‌شود، فراخوانی می‌شود.

### چالش روزانه

1. **پیاده‌سازی انتقال داده با DMA** برای رابط‌های جانبی دیگر مانند ADC یا SPI.
2. **پیکربندی حالت‌های مختلف مدیریت توان** و تست مصرف توان در هر حالت.
3. **استفاده از وقفه‌ها برای بیدار کردن میکروکنترلر از حالت خواب** و انجام عملیات‌های خاص.

با استفاده از این مفاهیم پیشرفته، می‌توانید کارایی و بهره‌وری سیستم‌های تعبیه‌شده خود را بهبود بخشید. اگر سوالی دارید یا نیاز به ادامه‌ی توضیحات دارید، حتماً بپرسید.