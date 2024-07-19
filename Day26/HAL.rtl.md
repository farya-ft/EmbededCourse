### روز 26: ارتباط با نمایشگرها و ایجاد رابط کاربری برای سیستم‌های تعبیه‌شده

امروز، نحوه ارتباط با انواع نمایشگرها و ایجاد رابط کاربری 
(UI)
 برای سیستم‌های تعبیه‌شده را بررسی خواهیم کرد. ما به نمایشگرهای متنی و گرافیکی می‌پردازیم و کتابخانه‌ها و مثال‌های کد مورد نیاز را برای شروع کار توضیح می‌دهیم.

#### 1. انواع نمایشگرها

**1.1. نمایشگرهای کاراکتری**

نمایشگرهای کاراکتری 
(مثلاً 16x2، 20x4)
 نمایشگرهای ساده‌ای هستند که کاراکترهای الفبایی و عددی را نشان می‌دهند. این نمایشگرها برای رابط‌های کاربری پایه‌ای به کار می‌روند.

**مثال: ارتباط با نمایشگر 16x2 LCD**

```cpp
#include <LiquidCrystal.h>

// کتابخانه را با شماره‌های پین‌های رابط اولیه‌سازی کنید
LiquidCrystal lcd(12, 11, 5, 4, 3, 2);

void setup() {
    lcd.begin(16, 2); // تنظیم تعداد ستون‌ها و ردیف‌های LCD
    lcd.print("Hello, World!"); // نمایش پیام بر روی LCD
}

void loop() {
    // به‌روزرسانی نمایشگر در صورت نیاز
}
```

**توضیح:**
- `LiquidCrystal lcd()`: کتابخانه را با شماره‌های پین‌های مورد استفاده برای اتصال به LCD اولیه‌سازی می‌کند.
- `lcd.begin()`: تعداد ستون‌ها و ردیف‌ها را تنظیم می‌کند.
- `lcd.print()`: متن را روی 
LCD نمایش می‌دهد.

**1.2. نمایشگرهای گرافیکی**

نمایشگرهای گرافیکی 
(مثلاً 128x64)
 می‌توانند متن و گرافیک نمایش دهند و امکان ایجاد رابط‌های کاربری غنی‌تر را فراهم می‌کنند.

**مثال: ارتباط با نمایشگر 128x64 GLCD**

```cpp
#include <U8g2lib.h>

// کتابخانه را برای نمایشگر خاص اولیه‌سازی کنید
U8G2_SSD1306_128X64_NONAME_F_HW_I2C u8g2(U8G2_R0);

void setup() {
    u8g2.begin(); // نمایشگر را اولیه‌سازی کنید
}

void loop() {
    u8g2.clearBuffer(); // حافظه داخلی را پاک کنید
    u8g2.setFont(u8g2_font_ncenB08_tr); // فونت مناسب را انتخاب کنید
    u8g2.drawStr(0, 10, "Hello, World!"); // رشته‌ای را در موقعیت (0,10) رسم کنید
    u8g2.sendBuffer(); // انتقال حافظه داخلی به نمایشگر
    delay(1000); // تاخیر به مدت 1 ثانیه
}
```

**توضیح:**
- `U8G2_SSD1306_128X64_NONAME_F_HW_I2C`: کتابخانه را برای نمایشگر OLED خاص با استفاده از I2C اولیه‌سازی می‌کند.
- `u8g2.clearBuffer()`: بافر نمایشگر را پاک می‌کند.
- `u8g2.setFont()`: فونت متن را تنظیم می‌کند.
- `u8g2.drawStr()`: رشته‌ای را بر روی نمایشگر رسم می‌کند.
- `u8g2.sendBuffer()`: داده‌های بافر را به نمایشگر ارسال می‌کند.

**1.3. نمایشگرهای TFT**

نمایشگرهای 
TFT (Thin Film Transistor) 
نمایشگرهای گرافیکی تمام رنگی با وضوح بالا هستند که برای رابط‌های کاربری پیچیده با قابلیت لمسی مناسب می‌باشند.

**مثال: ارتباط با نمایشگر 320x240 TFT**

```cpp
#include <Adafruit_GFX.h>
#include <Adafruit_ILI9341.h>

#define TFT_CS     10
#define TFT_RST    9
#define TFT_DC     8

Adafruit_ILI9341 tft = Adafruit_ILI9341(TFT_CS, TFT_DC, TFT_RST);

void setup() {
    tft.begin(); // نمایشگر را اولیه‌سازی کنید
    tft.fillScreen(ILI9341_BLACK); // نمایشگر را پاک کنید
    tft.setCursor(0, 0); // موقعیت نشانگر را تنظیم کنید
    tft.setTextColor(ILI9341_WHITE); // رنگ متن را تنظیم کنید
    tft.setTextSize(2); // اندازه متن را تنظیم کنید
    tft.print("Hello, World!"); // پیام را بر روی نمایشگر نمایش دهید
}

void loop() {
    // به‌روزرسانی نمایشگر در صورت نیاز
}
```

**توضیح:**
- `Adafruit_ILI9341`: کتابخانه را برای نمایشگر 
ILI9341-based TFT
 اولیه‌سازی می‌کند.
- `tft.begin()`: نمایشگر را اولیه‌سازی می‌کند.
- `tft.fillScreen()`: صفحه نمایش را با یک رنگ پر می‌کند.
- `tft.setCursor()`: موقعیت نشانگر را تنظیم می‌کند.
- `tft.setTextColor()`: رنگ متن را تنظیم می‌کند.
- `tft.setTextSize()`: اندازه متن را تنظیم می‌کند.
- `tft.print()`: متن را بر روی صفحه نمایش نشان می‌دهد.

#### 2. ایجاد رابط‌های کاربری

ایجاد یک رابط کاربری کاربر پسند شامل طراحی چیدمان‌های شهودی، کنترل‌های واکنش‌گرا و مکانیزم‌های بازخورد واضح است. برای نمایشگرهای گرافیکی، کتابخانه‌هایی مانند 
Adafruit GFX و LVGL (Light and Versatile Graphics Library) 
به کار می‌روند.

**2.1. رابط کاربری پایه با Adafruit GFX**

```cpp
#include <Adafruit_GFX.h>
#include <Adafruit_ILI9341.h>

#define TFT_CS     10
#define TFT_RST    9
#define TFT_DC     8

Adafruit_ILI9341 tft = Adafruit_ILI9341(TFT_CS, TFT_DC, TFT_RST);

void setup() {
    tft.begin();
    tft.fillScreen(ILI9341_BLACK);
    drawButton(50, 50, 100, 40, "Click Me!");
}

void loop() {
    // مدیریت ورودی کاربر و به‌روزرسانی UI
}

void drawButton(int x, int y, int w, int h, const char* label) {
    tft.fillRect(x, y, w, h, ILI9341_BLUE);
    tft.setCursor(x + 10, y + 10);
    tft.setTextColor(ILI9341_WHITE);
    tft.setTextSize(2);
    tft.print(label);
}
```

**توضیح:**
- `drawButton()`: دکمه‌ای را با ابعاد و برچسب مشخص رسم می‌کند.

**2.2. رابط کاربری پیشرفته با LVGL**

LVGL
 یک کتابخانه قدرتمند برای ایجاد رابط‌های کاربری پیچیده و تعاملی است.

**مثال: رابط کاربری پایه با LVGL**

```cpp
#include <lvgl.h>
#include <TFT_eSPI.h>

TFT_eSPI tft = TFT_eSPI(); /* نمونه TFT */
static lv_disp_buf_t disp_buf;
static lv_color_t buf[LV_HOR_RES_MAX * 10];

void my_disp_flush(lv_disp_drv_t *disp, const lv_area_t *area, lv_color_t *color_p) {
    tft.pushImage(area->x1, area->y1, area->x2 - area->x1 + 1, area->y2 - area->y1 + 1, (uint16_t*)&color_p->full);
    lv_disp_flush_ready(disp);
}

void setup() {
    lv_init();
    tft.begin();
    tft.setRotation(1);

    lv_disp_buf_init(&disp_buf, buf, NULL, LV_HOR_RES_MAX * 10);
    lv_disp_drv_t disp_drv;
    lv_disp_drv_init(&disp_drv);
    disp_drv.flush_cb = my_disp_flush;
    disp_drv.buffer = &disp_buf;
    lv_disp_drv_register(&disp_drv);

    lv_obj_t *label = lv_label_create(lv_scr_act(), NULL);
    lv_label_set_text(label, "Hello, World!");
    lv_obj_align(label, NULL, LV_ALIGN_CENTER, 0, 0);
}

void loop() {
    lv_task_handler(); // مدیریت وظایف LVGL
    delay(5);
}
```

**توضیح:**
- `lv_label_create()`: ایجاد ویجت برچسب.
- `lv_label_set_text()`: تنظیم متن برچسب.
- `lv_obj_align()`: تنظیم موقعیت برچسب در مرکز صفحه.
- `lv_task_handler()`: مدیریت وظایف 
LVGL برای به‌روزرسانی نمایشگر.

