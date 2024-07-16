###  : سیستم‌های عامل بی‌درنگ 
### (RTOS)
 در سیستم‌های تعبیه شده

### مزایای RTOS

یک سیستم عامل بی‌درنگ 
(RTOS)
 یک سیستم عامل است که تضمین می‌کند عملیات‌های خاصی در زمان‌های دقیق و قابل پیش‌بینی انجام می‌شوند. استفاده از 
 RTOS
  در سیستم‌های تعبیه شده مزایای زیادی دارد، از جمله:

- **پاسخگویی سریع:** RTOS
 می‌تواند تضمین کند که وظایف بحرانی در زمان‌های مشخصی اجرا می‌شوند.
- **مدیریت ساده وظایف:** RTOS
 امکان مدیریت وظایف مختلف را به صورت موازی فراهم می‌کند.
- **قابلیت پیش‌بینی:** RTOS
 قابلیت پیش‌بینی دقیق زمان‌بندی اجرای وظایف را دارد که برای کاربردهای بی‌درنگ بسیار مهم است.

### Mutex، Semaphore و Queue در RTOS

#### Mutex (قفل متقابل)

Mutex
 یا قفل متقابل یک مکانیسم همزمانی است که برای جلوگیری از دسترسی همزمان چندین وظیفه به منابع مشترک استفاده می‌شود. Mutex
ها برای جلوگیری از وضعیت‌های رقابتی 
(race conditions)
 استفاده می‌شوند.

#### Semaphore (سمافور)

Semaphore
 یک سیگنالینگ مکانیزم است که برای کنترل دسترسی به منابع مشترک در بین وظایف مختلف استفاده می‌شود. دو نوع 
semaphore وجود دارد:

- **باینری سمافور:** فقط دو حالت دارد (۰ یا ۱) و مشابه 
mutex
 عمل می‌کند.
- **شمارشی سمافور:** می‌تواند بیش از دو حالت داشته باشد و برای مدیریت تعداد محدودی از منابع مشترک استفاده می‌شود.

#### Queue (صف)

Queue
 یک ساختار داده است که برای انتقال داده‌ها بین وظایف مختلف استفاده می‌شود. صف‌ها به وظایف اجازه می‌دهند که داده‌ها را به صورت منظم و صفی منتقل کنند.

### پیاده‌سازی با HAL و FreeRTOS

برای پیاده‌سازی مفاهیم بالا با استفاده از 
HAL و FreeRTOS،
 ابتدا باید 
 RTOS 
 را پیکربندی کنید و سپس از توابع مناسب برای ایجاد و استفاده از 
 mutex، semaphore و queue 
 استفاده کنید.

#### پیکربندی FreeRTOS

برای پیکربندی 
FreeRTOS در STM32
، از 
CubeMX
 استفاده می‌شود. در 
 CubeMX
  می‌توانید 
  FreeRTOS
   را فعال کرده و وظایف 
   (tasks)، mutex، semaphore و queue 
   ها را پیکربندی کنید.

#### مثال پیاده‌سازی

در اینجا یک مثال ساده برای استفاده از 
mutex، semaphore و queue
 با 
 FreeRTOS و HAL
  آمده است.

##### ایجاد وظایف و منابع

```c
 /*فایل‌های هدر  ضروری برای استفاده از 
 FreeRTOS*/
#include "FreeRTOS.h"
#include "task.h"
#include "semphr.h"
#include "queue.h"
/*در اینجا، دستگیره‌های 
(Handles)
 سمفور دودویی، صف پیام و تسک‌ها تعریف شده‌اند*/
SemaphoreHandle_t binarySemaphore;
QueueHandle_t messageQueue;
TaskHandle_t task1Handle, task2Handle;

/* Function Prototypes */
void Task1(void *pvParameters);
void Task2(void *pvParameters);

int main(void) {
  HAL_Init();
  SystemClock_Config();
  MX_GPIO_Init();
  MX_USART2_UART_Init();

//در اینجا، سمفور دودویی و صف پیام ایجاد می‌شوند. سمفور دودویی برای همزمانی و صف پیام برای تبادل داده‌ها بین تسک‌ها استفاده می‌شوند.
  binarySemaphore = xSemaphoreCreateBinary();
  messageQueue = xQueueCreate(10, sizeof(uint8_t));
/*این بلوک کد بررسی می‌کند که آیا سمفور و صف پیام با موفقیت ایجاد شده‌اند یا خیر. اگر ایجاد شده باشند، تسک‌های 
Task1 و Task2
 با اندازه پشته 
 128
  بایت و اولویت 
 1 ایجاد می‌شوند و زمان‌بند 
 FreeRTOS
  شروع به کار می‌کند.*/
  if (binarySemaphore != NULL && messageQueue != NULL) {
    xTaskCreate(Task1, "Task 1", 128, NULL, 1, &task1Handle);
    xTaskCreate(Task2, "Task 2", 128, NULL, 1, &task2Handle);
    vTaskStartScheduler();
  }

//یک حلقه بی‌نهایت که در صورتی که زمان‌بند متوقف شود (که نباید شود) برنامه را در حالت بی‌نهایت نگه می‌دارد.
  while (1) {
  }
}
/*این تسک یک داده 
8 بیتی 
(dataToSend)
 را ارسال می‌کند. ابتدا منتظر می‌ماند تا سمفور آزاد شود 
 (xSemaphoreTake)،
  سپس داده را به صف پیام ارسال می‌کند 
  (xQueueSend)
   و مقدار داده را افزایش می‌دهد.*/
void Task1(void *pvParameters) {
  uint8_t dataToSend = 0;
  while (1) {
    if (xSemaphoreTake(binarySemaphore, portMAX_DELAY) == pdTRUE) {
      // Send data to queue
      xQueueSend(messageQueue, &dataToSend, portMAX_DELAY);
      dataToSend++;
    }
  }
}
/*این تسک داده 8 
بیتی را از صف پیام دریافت می‌کند
(xQueueReceive)
 و سپس آن را از طریق 
 UART2
  ارسال می‌کند 
  (HAL_UART_Transmit)
   و در نهایت سمفور را آزاد می‌کند 
   (xSemaphoreGive)
    تا تسک دیگر بتواند از آن استفاده کند.*/
void Task2(void *pvParameters) {
  uint8_t receivedData;
  while (1) {
    if (xQueueReceive(messageQueue, &receivedData, portMAX_DELAY) == pdTRUE) {
      // Process received data
      HAL_UART_Transmit(&huart2, &receivedData, 1, HAL_MAX_DELAY);
      xSemaphoreGive(binarySemaphore);
    }
  }
}
```

در این کد:

این کد با استفاده از 
FreeRTOS
 در یک سیستم تعبیه‌شده 
 (embedded system)
  نوشته شده است. هدف اصلی آن مدیریت همزمانی دو تسک 
  (Task)
   با استفاده از یک 
   Semaphore
    دودویی و یک صف پیام 
    (Queue)
     است
- **Semaphore**: یک 
semaphore
 باینری ایجاد شده و برای همزمانی بین 
 Task1 و Task2
  استفاده می‌شود.
- **Queue**: یک صف برای ارسال و دریافت داده‌ها بین وظایف ایجاد شده است.
- **Task1**: وقتی 
semaphore
 گرفته شود، داده‌ها را به صف ارسال می‌کند.
- **Task2**: داده‌ها را از صف دریافت می‌کند و از طریق 
UART
 ارسال می‌کند، سپس 
 semaphore
  را آزاد می‌کند.


تابع 
#### `xQueueReceive`
 بخشی از 
 FreeRTOS
  است که برای دریافت داده‌ها از یک صف 
  (queue) 
  استفاده می‌شود. در اینجا توضیح دقیق خط 
#### `(xQueueReceive(messageQueue, &receivedData, portMAX_DELAY) == pdTRUE)`
 آورده شده است:

```c
if (xQueueReceive(messageQueue, &receivedData, portMAX_DELAY) == pdTRUE) {
```

این خط شامل چند بخش است که هر کدام معنای خاص خود را دارند:

1. **xQueueReceive(messageQueue, &receivedData, portMAX_DELAY)**:
   - **messageQueue**: این آرگومان صفی است که می‌خواهیم از آن داده دریافت کنیم.
   - **&receivedData**: این آرگومان اشاره‌گری به محلی در حافظه است که داده دریافتی در آن ذخیره خواهد شد. در اینجا 
   `receivedData`
    یک متغیر از نوع 
    `uint8_t`
     است.
   - **portMAX_DELAY**: این آرگومان مشخص می‌کند که تابع چقدر باید صبر کند تا داده‌ای در صف موجود شود. 
   `portMAX_DELAY`
    به معنای صبر کردن بی‌نهایت تا زمانی که داده‌ای در صف قرار گیرد.

2. **== pdTRUE**:
   - تابع 
   `xQueueReceive`
    یک مقدار بولین برمی‌گرداند که نشان می‌دهد آیا دریافت داده موفقیت‌آمیز بوده است یا خیر.
   - `pdTRUE`
    به معنای موفقیت‌آمیز بودن عملیات است.

بنابراین، خط 
`(xQueueReceive(messageQueue, &receivedData, portMAX_DELAY) == pdTRUE)`
 به این معناست:

- تلاش می‌کند داده‌ای را از صف 
`messageQueue` 
دریافت کند.
- در صورت موفقیت‌آمیز بودن دریافت داده (برگشتن 
`pdTRUE`)
، شرط 
`if`
 برقرار خواهد بود و کد داخل بلوک 
 `if`
  اجرا می‌شود.
- اگر داده‌ای در صف موجود نباشد، تسک به صورت بی‌نهایت منتظر می‌ماند (به دلیل استفاده از `portMAX_DELAY`)
 تا داده‌ای در صف قرار گیرد و سپس دریافت کند.

به طور خلاصه، این خط بررسی می‌کند که آیا داده‌ای از صف پیام با موفقیت دریافت شده است یا خیر و در صورت موفقیت‌آمیز بودن، کد داخل بلوک 
`if`
 اجرا خواهد شد.