### شمارنده‌ها (Counters) در سیستم‌های توکار

شمارنده‌ها یکی از امکانات مهم میکروکنترلرها هستند که برای شمارش رویدادها، اندازه‌گیری زمان و تولید سیگنال‌های دوره‌ای استفاده می‌شوند. در ادامه با جزئیات بیشتری به شمارنده‌ها می‌پردازیم و نحوه استفاده از آن‌ها با کتابخانه HAL را توضیح می‌دهیم.

### کاربردهای شمارنده‌ها

شمارنده‌ها در سیستم‌های توکار کاربردهای گسترده‌ای دارند، از جمله:
- اندازه‌گیری مدت زمان بین دو رویداد
- شمارش پالس‌های ورودی
- تولید سیگنال PWM برای کنترل موتورها
- زمان‌بندی عملیات‌های دوره‌ای

### استفاده از شمارنده‌ها با HAL

در اینجا یک مثال از استفاده از تایمر به عنوان شمارنده آورده شده است. در این مثال از تایمر TIM2 برای شمارش پالس‌های ورودی استفاده می‌کنیم.

#### پیکربندی شمارنده

ابتدا تایمر را به عنوان شمارنده پیکربندی می‌کنیم:

```cpp
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

    /* Start the Timer */
    HAL_TIM_Base_Start(&htim2);

    /* Infinite loop */
    while (1) {
        // Read the counter value
        uint32_t counterValue = __HAL_TIM_GET_COUNTER(&htim2);
        // Use the counter value for your application
    }
}

void SystemClock_Config(void) {
    // System clock configuration code
}

static void MX_GPIO_Init(void) {
    // GPIO initialization code
}

static void MX_TIM2_Init(void) {
    TIM_ClockConfigTypeDef sClockSourceConfig = {0};
    TIM_MasterConfigTypeDef sMasterConfig = {0};

    htim2.Instance = TIM2;
    htim2.Init.Prescaler = 0;
    htim2.Init.CounterMode = TIM_COUNTERMODE_UP;
    htim2.Init.Period = 0xFFFFFFFF;
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

void Error_Handler(void) {
    while (1) {
        // Stay here
    }
}
```

### توضیحات:

- `HAL_TIM_Base_Init()`: تایمر را مقداردهی اولیه می‌کند.
- `HAL_TIM_Base_Start()`: تایمر را شروع می‌کند.
- `__HAL_TIM_GET_COUNTER()`: مقدار فعلی شمارنده را برمی‌گرداند.

### شمارش پالس‌های ورودی

برای شمارش پالس‌های ورودی، باید پیکربندی GPIO مربوطه و پیکربندی تایمر را به صورت زیر انجام دهید:

#### پیکربندی GPIO

ابتدا پیکربندی پین GPIO به عنوان ورودی پالس:

```cpp
static void MX_GPIO_Init(void) {
    GPIO_InitTypeDef GPIO_InitStruct = {0};

    /* GPIO Ports Clock Enable */
    __HAL_RCC_GPIOA_CLK_ENABLE();

    /*Configure GPIO pin : PA0 */
    GPIO_InitStruct.Pin = GPIO_PIN_0;
    GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;
    GPIO_InitStruct.Pull = GPIO_NOPULL;
    GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
    GPIO_InitStruct.Alternate = GPIO_AF1_TIM2;
    HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);
}
```

### پیکربندی تایمر برای شمارش پالس‌های ورودی

```cpp
static void MX_TIM2_Init(void) {
    TIM_ClockConfigTypeDef sClockSourceConfig = {0};
    TIM_MasterConfigTypeDef sMasterConfig = {0};
    TIM_IC_InitTypeDef sConfigIC = {0};

    htim2.Instance = TIM2;
    htim2.Init.Prescaler = 0;
    htim2.Init.CounterMode = TIM_COUNTERMODE_UP;
    htim2.Init.Period = 0xFFFFFFFF;
    htim2.Init.ClockDivision = TIM_CLOCKDIVISION_DIV1;
    htim2.Init.AutoReloadPreload = TIM_AUTORELOAD_PRELOAD_DISABLE;
    if (HAL_TIM_Base_Init(&htim2) != HAL_OK) {
        Error_Handler();
    }
    sClockSourceConfig.ClockSource = TIM_CLOCKSOURCE_INTERNAL;
    if (HAL_TIM_ConfigClockSource(&htim2, &sClockSourceConfig) != HAL_OK) {
        Error_Handler();
    }
    if (HAL_TIM_IC_Init(&htim2) != HAL_OK) {
        Error_Handler();
    }

    sConfigIC.ICPolarity = TIM_INPUTCHANNELPOLARITY_RISING;
    sConfigIC.ICSelection = TIM_ICSELECTION_DIRECTTI;
    sConfigIC.ICPrescaler = TIM_ICPSC_DIV1;
    sConfigIC.ICFilter = 0;
    if (HAL_TIM_IC_ConfigChannel(&htim2, &sConfigIC, TIM_CHANNEL_1) != HAL_OK) {
        Error_Handler();
    }
}
```

### توضیحات:

- `HAL_TIM_IC_Init()`: تایمر را برای ورودی کپچر (Input Capture) مقداردهی اولیه می‌کند.
- `HAL_TIM_IC_ConfigChannel()`: کانال تایمر را برای ورودی کپچر پیکربندی می‌کند.

### نتیجه‌گیری

شمارنده‌ها ابزارهای قدرتمندی برای مدیریت زمان‌بندی و شمارش رویدادها در سیستم‌های توکار هستند. با استفاده از کتابخانه HAL، می‌توان به راحتی تایمرها را به عنوان شمارنده پیکربندی و استفاده کرد. این امکان به شما کمک می‌کند تا عملیات‌های مختلفی مانند شمارش پالس‌ها، تولید سیگنال PWM و اندازه‌گیری زمان را به صورت دقیق و کارآمد انجام دهید.



### PWM (مدولاسیون عرض پالس) در سیستم‌های توکار

مدولاسیون عرض پالس یا PWM یکی از تکنیک‌های مهم در سیستم‌های توکار برای کنترل توان ارائه شده به بار است. از PWM در کاربردهای مختلفی مانند کنترل سرعت موتورها، تنظیم روشنایی LED‌ها، و تولید سیگنال‌های صوتی استفاده می‌شود.

### 1. مفهوم PWM

PWM روشی برای کنترل توان الکتریکی است که با تغییر عرض پالس (Duty Cycle) سیگنال دیجیتال انجام می‌شود. این سیگنال‌ها با فرکانس ثابت تولید می‌شوند اما عرض پالس آن‌ها تغییر می‌کند تا متوسط توان تحویلی به بار کنترل شود.

- **Duty Cycle**: نسبت زمانی که سیگنال در حالت فعال (High) است به کل دوره (Period) سیگنال.
- **Period**: مدت زمان یک سیکل کامل از سیگنال PWM.

### 2. کاربردهای PWM

- **کنترل سرعت موتور DC**: با تغییر Duty Cycle، متوسط ولتاژ اعمال شده به موتور تغییر می‌کند و در نتیجه سرعت آن کنترل می‌شود.
- **تنظیم روشنایی LED**: با تغییر Duty Cycle، میزان روشنایی LED تنظیم می‌شود.
- **تولید سیگنال صوتی**: برای تولید سیگنال‌های صوتی با فرکانس و دامنه مشخص.

### 3. استفاده از PWM با HAL

در اینجا یک مثال از استفاده از PWM برای کنترل روشنایی یک LED با استفاده از کتابخانه HAL آورده شده است. در این مثال از تایمر TIM3 استفاده می‌کنیم.

#### پیکربندی PWM

ابتدا تایمر را برای تولید سیگنال PWM پیکربندی می‌کنیم:

```cpp
#include "main.h"

/* Private variables ---------------------------------------------------------*/
TIM_HandleTypeDef htim3;

/* Private function prototypes -----------------------------------------------*/
void SystemClock_Config(void);
static void MX_GPIO_Init(void);
static void MX_TIM3_Init(void);

int main(void) {
    HAL_Init();
    SystemClock_Config();
    MX_GPIO_Init();
    MX_TIM3_Init();

    // Start PWM
    if (HAL_TIM_PWM_Start(&htim3, TIM_CHANNEL_1) != HAL_OK) {
        Error_Handler();
    }

    while (1) {
        for (uint32_t dutyCycle = 0; dutyCycle <= 100; dutyCycle += 10) {
            __HAL_TIM_SET_COMPARE(&htim3, TIM_CHANNEL_1, dutyCycle);
            HAL_Delay(500);
        }
    }
}

void SystemClock_Config(void) {
    // System clock configuration code
}

static void MX_GPIO_Init(void) {
    GPIO_InitTypeDef GPIO_InitStruct = {0};

    /* GPIO Ports Clock Enable */
    __HAL_RCC_GPIOA_CLK_ENABLE();

    /*Configure GPIO pin : PA6 */
    GPIO_InitStruct.Pin = GPIO_PIN_6;
    GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;
    GPIO_InitStruct.Pull = GPIO_NOPULL;
    GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
    GPIO_InitStruct.Alternate = GPIO_AF2_TIM3;
    HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);
}

static void MX_TIM3_Init(void) {
    TIM_OC_InitTypeDef sConfigOC = {0};

    htim3.Instance = TIM3;
    htim3.Init.Prescaler = 0;
    htim3.Init.CounterMode = TIM_COUNTERMODE_UP;
    htim3.Init.Period = 100;
    htim3.Init.ClockDivision = TIM_CLOCKDIVISION_DIV1;
    htim3.Init.AutoReloadPreload = TIM_AUTORELOAD_PRELOAD_DISABLE;
    if (HAL_TIM_PWM_Init(&htim3) != HAL_OK) {
        Error_Handler();
    }

    sConfigOC.OCMode = TIM_OCMODE_PWM1;
    sConfigOC.Pulse = 0;
    sConfigOC.OCPolarity = TIM_OCPOLARITY_HIGH;
    sConfigOC.OCFastMode = TIM_OCFAST_DISABLE;
    if (HAL_TIM_PWM_ConfigChannel(&htim3, &sConfigOC, TIM_CHANNEL_1) != HAL_OK) {
        Error_Handler();
    }
}

void Error_Handler(void) {
    while (1) {
        // Stay here
    }
}
```

### توضیحات:

- `HAL_TIM_PWM_Init()`: تایمر را برای تولید PWM مقداردهی اولیه می‌کند.
- `HAL_TIM_PWM_Start()`: PWM را روی کانال مشخص شده شروع می‌کند.
- `__HAL_TIM_SET_COMPARE()`: مقدار مقایسه را تنظیم می‌کند که تعیین‌کننده Duty Cycle است.

### پیکربندی GPIO

پین GPIO مربوطه را به عنوان خروجی PWM پیکربندی می‌کنیم:

```cpp
static void MX_GPIO_Init(void) {
    GPIO_InitTypeDef GPIO_InitStruct = {0};

    /* GPIO Ports Clock Enable */
    __HAL_RCC_GPIOA_CLK_ENABLE();

    /*Configure GPIO pin : PA6 */
    GPIO_InitStruct.Pin = GPIO_PIN_6;
    GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;
    GPIO_InitStruct.Pull = GPIO_NOPULL;
    GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
    GPIO_InitStruct.Alternate = GPIO_AF2_TIM3;
    HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);
}
```

### نتیجه‌گیری

PWM یکی از تکنیک‌های پرکاربرد در سیستم‌های توکار است که به کمک آن می‌توان کنترل دقیقی بر روی توان اعمالی به بار داشت. با استفاده از کتابخانه HAL، می‌توان به راحتی تایمرها را برای تولید سیگنال PWM پیکربندی و استفاده کرد. این امکان به شما کمک می‌کند تا در کاربردهای مختلف مانند کنترل سرعت موتور، تنظیم روشنایی LED و تولید سیگنال‌های صوتی از PWM بهره ببرید.