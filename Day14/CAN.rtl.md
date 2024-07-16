### پروتکل CAN (Controller Area Network) با استفاده از HAL

#### تعریف پروتکل CAN
**CAN (Controller Area Network)** یک پروتکل ارتباطی سریال است که برای ارتباطات سریع و قابل اعتماد بین دستگاه‌های مختلف الکترونیکی، به ویژه در صنعت خودروسازی، استفاده می‌شود. این پروتکل از دو خط 
CAN_H و CAN_L
 برای انتقال داده‌ها استفاده می‌کند و قابلیت ارسال و دریافت داده‌ها به صورت همزمان توسط چندین دستگاه را دارد.

#### نحوه استفاده از CAN با HAL

برای استفاده از پروتکل 
CAN
 در میکروکنترلر 
 STM32
  با استفاده از کتابخانه 
  HAL
  ، مراحل زیر را دنبال کنید:

### 1. پیکربندی اولیه

#### 1.1. استفاده از STM32CubeMX

1. **باز کردن STM32CubeMX** و ایجاد یک پروژه جدید.
2. **انتخاب میکروکنترلر STM32F446RE**.
3. **فعال کردن CAN** و تنظیمات پایه (مثل سرعت انتقال).
4. **پیکربندی پایه‌های CAN** (CAN_RX و CAN_TX).
5. **تولید پروژه** و باز کردن آن در STM32CubeIDE.

#### 1.2. پیکربندی 
#### HAL
 برای 
 #### CAN

```c
/* Includes ------------------------------------------------------------------*/
#include "main.h"

/* Private variables ---------------------------------------------------------*/
CAN_HandleTypeDef hcan;

/* Private function prototypes -----------------------------------------------*/
void SystemClock_Config(void);
static void MX_GPIO_Init(void); //تعریف پروتوتایپ توابع برای پیکربندی سیستم، 
// GPIO و CAN.
static void MX_CAN_Init(void);

/* USER CODE BEGIN 0 */
//تعریف ساختارها و آرایه‌ها برای ارسال و دریافت داده‌ها
CAN_TxHeaderTypeDef TxHeader;  
CAN_RxHeaderTypeDef RxHeader;
uint8_t TxData[8];
uint8_t RxData[8];
uint32_t TxMailbox;

/* USER CODE END 0 */

int main(void) {
  /* Reset of all peripherals, Initializes the Flash interface and the Systick. */
  HAL_Init();

  /* Configure the system clock */
  SystemClock_Config();

  /* Initialize all configured peripherals */
  MX_GPIO_Init();
  MX_CAN_Init();

  /* USER CODE BEGIN 2 */
  // CAN Filter Configuration
  CAN_FilterTypeDef sFilterConfig; //// پیکربندی فیلتر CAN
  sFilterConfig.FilterBank = 0;
  sFilterConfig.FilterMode = CAN_FILTERMODE_IDMASK;
  sFilterConfig.FilterScale = CAN_FILTERSCALE_32BIT;
  sFilterConfig.FilterIdHigh = 0x0000;
  sFilterConfig.FilterIdLow = 0x0000;
  sFilterConfig.FilterMaskIdHigh = 0x0000;
  sFilterConfig.FilterMaskIdLow = 0x0000;
  sFilterConfig.FilterFIFOAssignment = CAN_FILTER_FIFO0;
  sFilterConfig.FilterActivation = ENABLE;
  sFilterConfig.SlaveStartFilterBank = 14;

  if (HAL_CAN_ConfigFilter(&hcan, &sFilterConfig) != HAL_OK) {
    Error_Handler();
  }

  // Start CAN
  if (HAL_CAN_Start(&hcan) != HAL_OK) {
    Error_Handler();
  }

  // Activate CAN notification
  if (HAL_CAN_ActivateNotification(&hcan, CAN_IT_RX_FIFO0_MSG_PENDING) != HAL_OK) {
    Error_Handler();
  }

  // Prepare Tx Message
  TxHeader.DLC = 8;
  TxHeader.IDE = CAN_ID_STD;
  TxHeader.RTR = CAN_RTR_DATA;
  TxHeader.StdId = 0x321;

  TxData[0] = 'H';
  TxData[1] = 'e';
  TxData[2] = 'l';
  TxData[3] = 'l';
  TxData[4] = 'o';
  TxData[5] = ' ';
  TxData[6] = 'C';
  TxData[7] = 'A';

  /* Infinite loop */
  while (1) {
    if (HAL_CAN_AddTxMessage(&hcan, &TxHeader, TxData, &TxMailbox) != HAL_OK) {
      Error_Handler();
    }

    HAL_Delay(1000);
  }
  /* USER CODE END 2 */
}

/* CAN Initialization Function */
//تابع پیکربندی CAN
static void MX_CAN_Init(void) {
  hcan.Instance = CAN1;
  hcan.Init.Prescaler = 16;
  hcan.Init.Mode = CAN_MODE_NORMAL;
  hcan.Init.SyncJumpWidth = CAN_SJW_1TQ;
  hcan.Init.TimeSeg1 = CAN_BS1_1TQ;
  hcan.Init.TimeSeg2 = CAN_BS2_1TQ;
  hcan.Init.TimeTriggeredMode = DISABLE;
  hcan.Init.AutoBusOff = DISABLE;
  hcan.Init.AutoWakeUp = DISABLE;
  hcan.Init.AutoRetransmission = DISABLE;
  hcan.Init.ReceiveFifoLocked = DISABLE;
  hcan.Init.TransmitFifoPriority = DISABLE;
  if (HAL_CAN_Init(&hcan) != HAL_OK) {
    Error_Handler();
  }
}

/* GPIO Initialization Function */
//تابع پیکربندی GPIO
static void MX_GPIO_Init(void) {
  GPIO_InitTypeDef GPIO_InitStruct = {0};

  /* GPIO Ports Clock Enable */
  __HAL_RCC_GPIOA_CLK_ENABLE();

  /*Configure GPIO pin : PA0 */
  GPIO_InitStruct.Pin = GPIO_PIN_0;
  GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);
}

/* System Clock Configuration */
//// کد پیکربندی ساعت سیستم
void SystemClock_Config(void) {
  // System clock configuration code
}

/* Error Handler */
void Error_Handler(void) {
  while (1) {
    // Stay here
    // حلقه بی‌نهایت برای باقی ماندن در حالت خطا
  }
}

/* USER CODE BEGIN 4 */
/*این تابع کال‌بک برای پردازش پیام‌های دریافتی در 
FIFO0
 استفاده می‌شود. وقتی یک پیام جدید در 
 FIFO0 
 موجود باشد، این تابع فراخوانی می‌شود.*/
void HAL_CAN_RxFifo0MsgPendingCallback(CAN_HandleTypeDef *hcan) {
  if (HAL_CAN_GetRxMessage(hcan, CAN_RX_FIFO0, &RxHeader, RxData) != HAL_OK) {
    Error_Handler();
  }

  // Process received message
}
/* USER CODE END 4 */
```

### توضیحات کد:

1. **پیکربندی فیلتر CAN**: برای تنظیم فیلترهای پیام‌های دریافتی.
2. **شروع CAN**: برای شروع پروتکل  
CAN.
3. **فعالسازی اعلان‌های CAN**: برای دریافت پیام‌های جدید در 
FIFO.
4. **ارسال پیام CAN**: با استفاده از 
`HAL_CAN_AddTxMessage`.
5. **کال‌بک دریافت پیام**: برای پردازش پیام‌های دریافتی در 
FIFO.

### 2. استفاده از پروتکل CAN

#### کجا استفاده کنیم؟

- **خودروسازی**: برای ارتباطات بین 
ECU
‌ها (واحدهای کنترل الکترونیکی) در خودروها.
- **اتوماسیون صنعتی**: برای ارتباط بین کنترلرها و سنسورها.
- **سیستم‌های پزشکی**: برای ارتباط بین دستگاه‌های پزشکی مختلف.

#### مزایا و معایب

**مزایا:**
- **سرعت بالا**: توانایی انتقال داده‌ها با سرعت بالا.
- **اعتمادپذیری**: دارای مکانیزم‌های کشف خطا.
- **پشتیبانی از چندین دستگاه**: امکان ارتباط بین چندین دستگاه بدون تداخل.

**معایب:**
- **پیچیدگی**: نیاز به تنظیمات دقیق و پیچیده.
- **هزینه**: پیاده‌سازی و استفاده از 
CAN
 ممکن است هزینه بیشتری نسبت به پروتکل‌های ساده‌تر داشته باشد.

### نتیجه‌گیری

پروتکل 
CAN
 یک راه‌حل بسیار قدرتمند برای ارتباطات سریال در سیستم‌های تعبیه‌شده است که نیاز به سرعت و اعتمادپذیری بالا دارند. با استفاده از 
 HAL
 می‌توان به سادگی این پروتکل را در پروژه‌های خود پیاده‌سازی کرد.