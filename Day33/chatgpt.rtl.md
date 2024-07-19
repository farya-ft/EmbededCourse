### تایمرها و تایمرهای واچ‌داگ در سیستم‌های توکار

تایمرها و تایمرهای واچ‌داگ اجزای مهمی در سیستم‌های توکار هستند که برای مدیریت زمان‌بندی و نظارت بر عملکرد سیستم استفاده می‌شوند. در اینجا توضیحاتی درباره هرکدام از این اجزا و نحوه استفاده از آن‌ها با استفاده از کتابخانه 
HAL
 آورده شده است.

### تایمرها (Timers)

تایمرها در میکروکنترلرها برای اجرای عملیات‌های دوره‌ای و اندازه‌گیری زمان استفاده می‌شوند. این تایمرها معمولاً دارای رجیسترهای شمارنده و مقایسه‌ای هستند که می‌توانند برای تولید وقفه‌های دوره‌ای و یا اندازه‌گیری زمان بین دو رویداد استفاده شوند.

#### استفاده از تایمر با HAL

در اینجا مثالی از پیکربندی یک تایمر ساده برای تولید وقفه‌های دوره‌ای آورده شده است:

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

    /* Start Timer Interrupt */
    HAL_TIM_Base_Start_IT(&htim2);

    /* Infinite loop */
    while (1) {
        // Main loop
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
    htim2.Init.Prescaler = 8399;
    htim2.Init.CounterMode = TIM_COUNTERMODE_UP;
    htim2.Init.Period = 9999;
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

/* Timer Interrupt Callback */
void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef *htim) {
    if (htim->Instance == TIM2) {
        // Timer interrupt code
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
- `HAL_TIM_Base_Start_IT()`: تایمر را با وقفه شروع می‌کند.
- `HAL_TIM_PeriodElapsedCallback()`: تابع کال‌بک برای وقفه تایمر.

### تایمر واچ‌داگ (Watchdog Timer)

تایمر واچ‌داگ برای جلوگیری از هنگ کردن سیستم به کار می‌رود. این تایمر به طور مداوم شمارش می‌کند و اگر در یک بازه زمانی مشخص ریست نشود، سیستم را ریست می‌کند.

#### استفاده از تایمر واچ‌داگ با HAL

در اینجا مثالی از پیکربندی تایمر واچ‌داگ آورده شده است:

```cpp
#include "main.h"

/* Private variables ---------------------------------------------------------*/
IWDG_HandleTypeDef hiwdg;

/* Private function prototypes -----------------------------------------------*/
void SystemClock_Config(void);
static void MX_GPIO_Init(void);
static void MX_IWDG_Init(void);

int main(void) {
    /* Reset of all peripherals, Initializes the Flash interface and the Systick. */
    HAL_Init();

    /* Configure the system clock */
    SystemClock_Config();

    /* Initialize all configured peripherals */
    MX_GPIO_Init();
    MX_IWDG_Init();

    /* Infinite loop */
    while (1) {
        // Main loop

        // Refresh the watchdog timer to prevent system reset
        HAL_IWDG_Refresh(&hiwdg);

        HAL_Delay(1000); // Delay for 1 second
    }
}

void SystemClock_Config(void) {
    // System clock configuration code
}

static void MX_GPIO_Init(void) {
    // GPIO initialization code
}

static void MX_IWDG_Init(void) {
    hiwdg.Instance = IWDG;
    hiwdg.Init.Prescaler = IWDG_PRESCALER_32;
    hiwdg.Init.Reload = 4095; // Set the reload value
    if (HAL_IWDG_Init(&hiwdg) != HAL_OK) {
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

- `HAL_IWDG_Init()`: تایمر واچ‌داگ را مقداردهی اولیه می‌کند.
- `HAL_IWDG_Refresh()`: تایمر واچ‌داگ را تازه‌سازی می‌کند تا سیستم ریست نشود.

### نتیجه‌گیری

تایمرها و تایمرهای واچ‌داگ از اجزای حیاتی در سیستم‌های توکار هستند که برای مدیریت زمان‌بندی دقیق و جلوگیری از هنگ کردن سیستم به کار می‌روند. با استفاده از کتابخانه 
HAL
، می‌توان این تایمرها را به راحتی پیکربندی و استفاده کرد.