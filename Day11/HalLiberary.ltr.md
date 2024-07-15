### روز 11: مدیریت وقفه‌ها، محدودیت‌های زمان واقعی، و جیتربا استفاده از 
### HAL

#### مقدمه

وقفه‌ها یک مفهوم اساسی در سیستم‌های تعبیه‌شده هستند که به میکروکنترلر اجازه می‌دهند به سرعت به رویدادهای داخلی و خارجی پاسخ دهد. محدودیت‌های زمان واقعی برای اطمینان از رعایت الزامات زمانی مشخص بسیار حیاتی هستند، و جیتربا یک عامل مهم در مواجهه با سیستم‌های زمان واقعی است.

امروز، این مباحث را با تمرکز بر میکروکنترلر 
STM32F446RE
 و استفاده از کتابخانه 
 HAL (Hardware Abstraction Layer)
  بررسی می‌کنیم.

### 1. درک وقفه‌ها

#### وقفه چیست؟

یک وقفه مکانیزمی است که به میکروکنترلر اجازه می‌دهد اجرای کد فعلی را متوقف کند تا یک رویداد یا وضعیت خاص را مدیریت کند. پس از مدیریت رویداد، میکروکنترلر اجرای کد متوقف‌شده را ادامه می‌دهد.

#### انواع وقفه‌ها

- **وقفه‌های خارجی**: توسط رویدادهای خارجی (مانند فشار دادن یک دکمه) تحریک می‌شوند.
- **وقفه‌های داخلی**: توسط رویدادهای داخلی (مانند سرریز تایمر) تحریک می‌شوند.

### 2. پیکربندی وقفه‌های خارجی با استفاده از HAL

بیایید یک وقفه خارجی را که توسط فشار دادن دکمه در پین 
PA0
 تحریک می‌شود، پیکربندی کنیم.

#### راهنمای گام‌به‌گام

1. **باز کردن STM32CubeMX** و ایجاد یک پروژه جدید.
2. **انتخاب میکروکنترلر STM32F446RE**.
3. **پیکربندی GPIO PA0** به عنوان وقفه خارجی:
   - انتخاب 
   PA0
    و تنظیم آن به عنوان 
    GPIO_EXTI0.
4. **تولید پروژه** و باز کردن آن در 
STM32CubeIDE.

#### کد تولید شده (`main.c`)

کد تولید شده شامل توابع اولیه‌سازی است. باید کد مدیریت وقفه را اضافه کنیم.

```c
/* Includes ------------------------------------------------------------------*/
#include "main.h"

/* Private variables ---------------------------------------------------------*/
GPIO_InitTypeDef GPIO_InitStruct = {0};

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
    // Main loop
  }
}

/* GPIO Initialization Function */
static void MX_GPIO_Init(void) {
  /* GPIO Ports Clock Enable */
  __HAL_RCC_GPIOA_CLK_ENABLE();

  /*Configure GPIO pin : PA0 */
  GPIO_InitStruct.Pin = GPIO_PIN_0;
  GPIO_InitStruct.Mode = GPIO_MODE_IT_RISING;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);

  /* EXTI interrupt init */
  HAL_NVIC_SetPriority(EXTI0_IRQn, 0, 0);
  HAL_NVIC_EnableIRQ(EXTI0_IRQn);
}

/* External interrupt handler */
void EXTI0_IRQHandler(void) {
  HAL_GPIO_EXTI_IRQHandler(GPIO_PIN_0);
}

/* Callback function for GPIO EXTI */
void HAL_GPIO_EXTI_Callback(uint16_t GPIO_Pin) {
  if (GPIO_Pin == GPIO_PIN_0) {
    // Handle the interrupt (e.g., toggle an LED)
    HAL_GPIO_TogglePin(GPIOA, GPIO_PIN_5);
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

### توضیحات:

- **EXTI0_IRQHandler**: مدیریت کننده وقفه 
EXTI0
 است.
- **HAL_GPIO_EXTI_Callback**: تابع 
callback
 که توسط 
 `HAL_GPIO_EXTI_IRQHandler`
  فراخوانی می‌شود. در این تابع، وقفه را با تغییر وضعیت 
  LED
   در 
   PA5
    مدیریت می‌کنیم.

### 3. محدودیت‌های زمان واقعی و جیتربا

#### محدودیت‌های زمان واقعی

سیستم‌های زمان واقعی باید در یک بازه زمانی قابل پیش‌بینی به رویدادها پاسخ دهند. دو نوع محدودیت زمان واقعی وجود دارد:

- **زمان واقعی سخت**: از دست دادن یک ضرب‌الاجل می‌تواند به شکست سیستم منجر شود.
- **زمان واقعی نرم**: از دست دادن یک ضرب‌الاجل عملکرد سیستم را کاهش می‌دهد اما به شکست منجر نمی‌شود.

#### جیتربا

جیتربا به تغییرات زمانی در اجرای یک رویداد اشاره دارد. در سیستم‌های زمان واقعی، حداقل کردن جیتربا برای حفظ رفتار قابل پیش‌بینی بسیار مهم است.

### 4. کاهش جیتربا در مدیریت وقفه‌ها

برای کاهش جیتربا:

1. **ISR را کوتاه نگه دارید**: روال سرویس وقفه 
(ISR)
 باید تا حد امکان کوتاه باشد.
2. **اولویت بندی وقفه‌ها**: به وقفه‌ها اولویت‌های مناسب بدهید.
3. **غیر فعال کردن وقفه‌های غیر ضروری**: وقفه‌هایی که لازم نیستند را غیر فعال کنید تا سربار کاهش یابد.

### مثال: وقفه تایمر

بیایید یک وقفه تایمر را برای تولید وقفه‌های دوره‌ای با جیتربای کم پیکربندی کنیم.

#### راهنمای گام‌به‌گام

1. **باز کردن STM32CubeMX**.
2. **فعال کردن TIM2** و پیکربندی آن برای وقفه دوره‌ای (مثلاً هر ۱ میلی‌ثانیه).
3. **تولید پروژه** و باز کردن آن در 
STM32CubeIDE.

#### کد تولید شده (`main.c`)

```c
/* Includes ------------------------------------------------------------------*/
#include "main.h"

/* Private variables ---------------------------------------------------------*/
TIM_HandleTypeDef htim2;

/* Private function prototypes -----------------------------------------------*/
void SystemClock_Config(void);
static void MX_GPIO_Init(void);
static void MX_TIM2_Init(void);

int main(void) {
  /* Reset of all peripherals, Initializes the Flash interface and the Systick. */
  HAL_Init();

  /* Configure the system clock */
  SystemClock_Config();

  /* Initialize all configured peripherals */
  MX_GPIO_Init();
  MX_TIM2_Init();

  /* Start Timer Interrupt */
  HAL_TIM_Base_Start_IT(&htim2);

  /* Infinite loop */
  while (1) {
    // Main loop
  }
}

/* TIM2 Initialization Function */
static void MX_TIM2_Init(void) {
  TIM_ClockConfigTypeDef sClockSourceConfig = {0};
  TIM_MasterConfigTypeDef sMasterConfig = {0};

  htim2.Instance = TIM2;
  htim2.Init.Prescaler = 16000 - 1; // Prescaler to generate 1ms tick
  htim2.Init.CounterMode = TIM_COUNTERMODE_UP;
  htim2.Init.Period = 1000 - 1; // 1 second period
  htim2.Init.ClockDivision = TIM_CLOCKDIVISION_DIV1;
  htim2.Init.AutoReloadPreload = TIM_AUTORELOAD_PRELOAD_DISABLE;
  if (HAL_TIM_Base_Init(&htim2) != HAL_OK) {
    Error_Handler();
  }
  sClockSourceConfig.ClockSource = TIM_CLOCKSOURCE_INTERNAL;
  if (HAL_TIM_ConfigClockSource(&htim2, &sClockSourceConfig) != HAL_OK) {
    Error_Handler();
  }
  sMasterConfig.MasterOutputTrigger = TIM_TRGO_RESET;
  sMasterConfig.MasterSlaveMode = TIM_MASTERSLAVEMODE_DISABLE;
  if (HAL_TIMEx_MasterConfigSynchronization(&htim2, &sMasterConfig) != HAL_OK) {
    Error_Handler();
  }
}

/* Timer Interrupt Callback Function */
void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef *htim) {
  if (htim->Instance == TIM2) {
    // Handle Timer Interrupt (e.g., toggle an LED)
    HAL_GPIO_TogglePin(GPIOA, GPIO_PIN_5);
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

### توضیحات:

- **MX_TIM2_Init**: تایمر 
TIM2
 را برای تولید وقفه دوره‌ای هر ۱ میلی‌ثانیه اولیه‌سازی می‌کند.
- **HAL_TIM_PeriodElapsedCallback**: تابع 
callback
 که وقتی دوره تایمر به پایان می‌رسد فراخوانی می‌شود. ما در این تابع وضعیت 
 LED
  روی PA5 را تغییر می‌دهیم.

!!!  چالش روزانه:

1. **پیکربندی یک تایمر دیگر** (مثلاً 
TIM3) 
و تنظیم آن برای یک وقفه دوره‌ای متفاوت.
2. **پیاده‌سازی وقفه‌های تو در تو** با تنظیم اولویت‌های مختلف برای وقفه‌های 
EXTI
 و تایمر.
3. **اندازه‌گیری و کاهش جیتربا** در وقفه‌های تایمر خود.

---

