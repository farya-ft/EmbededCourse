### روز ۲۳: ملاحظات امنیتی در سیستم‌های تعبیه‌شده

امنیت یک جنبه حیاتی در توسعه سیستم‌های تعبیه‌شده است. اطمینان از اینکه سیستم‌های تعبیه‌شده شما امن هستند، آنها را از دسترسی غیرمجاز، دستکاری و تهدیدات سایبری محافظت می‌کند. امروز به بررسی اقدامات امنیتی و بهترین شیوه‌ها برای حفاظت از سیستم‌های تعبیه‌شده می‌پردازیم.

#### 1. اهمیت امنیت در سیستم‌های تعبیه‌شده

سیستم‌های تعبیه‌شده اغلب داده‌های حساس و عملیات‌های حیاتی را در حوزه‌های مختلف مانند خودرو، بهداشت و درمان، کنترل صنعتی و IoT کنترل می‌کنند. نقض‌های امنیتی می‌توانند منجر به عواقب جدی مانند سرقت داده‌ها، نقص سیستم و خطرات ایمنی شوند.

#### 2. تهدیدات امنیتی رایج

- **دسترسی غیرمجاز:** دسترسی به سیستم بدون اجازه.
- **تزریق کد:** تزریق کد مخرب برای تغییر رفتار سیستم.
- **استراق سمع داده‌ها:** شنود داده‌های در حال انتقال.
- **دستکاری میان‌افزار:** تغییر میان‌افزار برای به خطر انداختن یکپارچگی سیستم.

#### 3. اقدامات امنیتی و بهترین شیوه‌ها

**3.1. بوت امن**

بوت امن اطمینان می‌دهد که سیستم فقط از میان‌افزار تأیید شده و معتبر برای بوت استفاده می‌کند. این کار از اجرای کد غیرمجاز یا مخرب در حین راه‌اندازی جلوگیری می‌کند.

**مثال: پیاده‌سازی بوت امن**

- استفاده از امضاهای رمزنگاری برای تأیید میان‌افزار.
- پیاده‌سازی یک بوت‌لودر امن که میان‌افزار را قبل از اجرا تأیید می‌کند.

**3.2. رمزنگاری**

داده‌های حساس را برای محافظت در برابر دسترسی غیرمجاز و استراق سمع رمزنگاری کنید. از الگوریتم‌های رمزنگاری قوی برای داده‌های ذخیره شده و داده‌های در حال انتقال استفاده کنید.

**مثال: رمزنگاری داده‌ها با AES**

در اینجا یک مثال ساده از نحوه استفاده از کتابخانه AES در STM32 با HAL ارائه شده است:

```c
#include "main.h"
#include "aes.h"

AES_HandleTypeDef haes;

void SystemClock_Config(void);
static void MX_GPIO_Init(void);
static void MX_AES_Init(void);

uint8_t clearText[] = "Sensitive Data";
uint8_t cipherText[16];
uint8_t key[16] = "YourEncryptionKey";

int main(void)
{
    HAL_Init();
    SystemClock_Config();
    MX_GPIO_Init();
    MX_AES_Init();

    // AES encryption
    HAL_AES_Encrypt(&haes, clearText, 16, cipherText, 10);

    // AES decryption
    uint8_t decryptedText[16];
    HAL_AES_Decrypt(&haes, cipherText, 16, decryptedText, 10);

    while (1)
    {
    }
}

static void MX_AES_Init(void)
{
    haes.Instance = AES;
    haes.Init.DataType = AES_DATATYPE_8B;
    haes.Init.KeySize = AES_KEYSIZE_128B;
    haes.Init.pKey = key;
    if (HAL_AES_Init(&haes) != HAL_OK)
    {
        Error_Handler();
    }
}
```

**توضیح:**
- `HAL_AES_Encrypt()`: داده‌های روشن را با استفاده از رمزنگاری AES رمزنگاری می‌کند.
- `HAL_AES_Decrypt()`: داده‌های رمزنگاری شده را به متن روشن باز می‌گرداند.

**3.3. کنترل دسترسی**

مکانیزم‌های کنترل دسترسی را برای محدود کردن دسترسی به بخش‌های حساس سیستم بر اساس نقش‌ها و مجوزها پیاده‌سازی کنید.

**مثال: کنترل دسترسی ساده**

```c
typedef enum { ADMIN, USER, GUEST } Role;
Role currentUserRole = GUEST;

void accessRestrictedFunction()
{
    if (currentUserRole == ADMIN)
    {
        // اجازه دسترسی
    }
    else
    {
        // عدم اجازه دسترسی
    }
}
```

**توضیح:**
- `accessRestrictedFunction()`: نقش کاربر جاری را بررسی کرده و دسترسی را براساس نقش مجاز یا غیرمجاز می‌کند.

**3.4. پروتکل‌های ارتباطی امن**

از پروتکل‌های ارتباطی امن (مانند 
HTTPS، SSL/TLS)
 برای محافظت از انتقال داده‌ها در برابر استراق سمع و دستکاری استفاده کنید.

**مثال: ارتباط امن با HTTPS (ESP8266/ESP32)**

```cpp
#include <WiFiClientSecure.h>

const char* ssid = "YourSSID";
const char* password = "YourPassword";
const char* host = "example.com";
const int httpsPort = 443;

WiFiClientSecure client;

void setup() {
    Serial.begin(115200);
    WiFi.begin(ssid, password);
    while (WiFi.status() != WL_CONNECTED) {
        delay(1000);
        Serial.println("Connecting to WiFi...");
    }

    if (!client.connect(host, httpsPort)) {
        Serial.println("Connection failed!");
        return;
    }
    Serial.println("Connected to server");

    // Send HTTPS request
    client.print("GET /path HTTP/1.1\r\nHost: ");
    client.print(host);
    client.print("\r\nConnection: close\r\n\r\n");

    // Read response
    while (client.connected()) {
        String line = client.readStringUntil('\n');
        Serial.println(line);
    }
}

void loop() {
    // Main loop
}
```

**توضیح:**
- `WiFiClientSecure`: برقراری یک ارتباط امن با استفاده از 
SSL/TLS.
- ارسال درخواست HTTPS GET و خواندن پاسخ سرور.

**3.5. به‌روزرسانی‌ها و پچ‌های منظم**

نگهداری میان‌افزار و اجزای نرم‌افزاری با آخرین پچ‌های امنیتی برای محافظت در برابر آسیب‌پذیری‌های شناخته شده.

#### 4. تست امنیتی

**4.1. تست نفوذ**

شبیه‌سازی حملات برای شناسایی و رفع آسیب‌پذیری‌های امنیتی.

**4.2. تحلیل استاتیک و دینامیک**

از ابزارهای تحلیل استاتیک برای شناسایی نقص‌های امنیتی در کد منبع و از ابزارهای تحلیل دینامیک برای نظارت بر رفتار اجرایی به‌منظور شناسایی ناهنجاری‌ها استفاده کنید.



### درک SSL/TLS

SSL (لایه سوکت‌های امن) و TLS (امنیت لایه حمل و نقل) پروتکل‌های رمزنگاری هستند که برای ارائه ارتباط امن بر روی یک شبکه کامپیوتری طراحی شده‌اند. TLS جانشین SSL است و امنیت و کارایی بیشتری دارد. با هم، آنها اطمینان حاصل می‌کنند که داده‌های مبادله شده بین برنامه‌ها بر روی یک شبکه خصوصی، صحیح و معتبر هستند.

#### 1. هدف SSL/TLS

- **محرمانگی:** SSL/TLS داده‌های مبادله شده بین کلاینت و سرور را رمزنگاری می‌کند و از خوانده شدن داده‌ها توسط شنود کنندگان جلوگیری می‌کند.
- **یکپارچگی:** اطمینان حاصل می‌شود که داده‌ها در طول انتقال تغییر نمی‌کنند.
- **احراز هویت:** اطمینان حاصل می‌شود که طرفین در ارتباط همان کسانی هستند که ادعا می‌کنند.

#### 2. نحوه عملکرد SSL/TLS

**2.1. فرایند دست‌دهی (Handshake)**

فرایند دست‌دهی SSL/TLS شامل چندین مرحله است که در زیر توضیح داده شده‌اند:

- **ابتدا، کلاینت به سرور متصل می‌شود.** کلاینت یک درخواست به سرور می‌فرستد که حاوی اطلاعاتی درباره توانایی‌های رمزنگاری‌اش است.
- **سرور پاسخ می‌دهد.** سرور گواهی دیجیتال خود را ارسال می‌کند که شامل کلید عمومی آن است و با کلید خصوصی سرور امضا شده است.
- **کلاینت گواهی را تأیید می‌کند.** کلاینت گواهی سرور را با استفاده از کلید عمومی صادر کننده گواهی بررسی می‌کند.
- **ایجاد کلید جلسه.** کلاینت یک کلید جلسه تولید می‌کند و آن را با استفاده از کلید عمومی سرور رمزنگاری می‌کند و به سرور ارسال می‌کند.
- **شروع ارتباط رمزنگاری شده.** هم کلاینت و هم سرور از کلید جلسه برای رمزنگاری و رمزگشایی داده‌های ارسال شده استفاده می‌کنند.

#### 3. اهمیت SSL/TLS

- **حفاظت از داده‌های حساس:** SSL/TLS از داده‌های حساس مانند اطلاعات کارت اعتباری، رمزهای عبور و اطلاعات شخصی در برابر سرقت محافظت می‌کند.
- **اعتماد به خدمات آنلاین:** استفاده از SSL/TLS باعث ایجاد اعتماد در کاربران می‌شود که ارتباط آنها با سرور امن است.
- **الزامات قانونی:** برخی از قوانین و مقررات امنیتی استفاده از SSL/TLS را برای حفاظت از داده‌ها الزامی می‌کنند.

#### 4. پیاده‌سازی SSL/TLS در سیستم‌های تعبیه‌شده

برای پیاده‌سازی SSL/TLS در سیستم‌های تعبیه‌شده می‌توان از کتابخانه‌های مختلفی استفاده کرد. یکی از کتابخانه‌های محبوب برای میکروکنترلرها، mbedTLS است.

**مثال: پیاده‌سازی TLS با استفاده از mbedTLS در STM32**

در اینجا یک مثال ساده از نحوه استفاده از کتابخانه mbedTLS برای برقراری یک ارتباط امن با استفاده از TLS ارائه شده است:

```c
#include "mbedtls/net_sockets.h"
#include "mbedtls/ssl.h"
#include "mbedtls/ssl_internal.h"
#include "mbedtls/error.h"
#include "mbedtls/certs.h"
#include "mbedtls/pk.h"

int main(void) {
    int ret;
    mbedtls_net_context server_fd;
    mbedtls_ssl_context ssl;
    mbedtls_ssl_config conf;
    mbedtls_x509_crt cacert;
    mbedtls_ctr_drbg_context ctr_drbg;
    mbedtls_entropy_context entropy;
    const char *pers = "ssl_client";

    // Initialize the RNG and the session data
    mbedtls_net_init(&server_fd);
    mbedtls_ssl_init(&ssl);
    mbedtls_ssl_config_init(&conf);
    mbedtls_x509_crt_init(&cacert);
    mbedtls_ctr_drbg_init(&ctr_drbg);
    mbedtls_entropy_init(&entropy);

    // Load the trusted CA
    ret = mbedtls_x509_crt_parse(&cacert, (const unsigned char *) mbedtls_test_cas_pem, mbedtls_test_cas_pem_len);
    if (ret != 0) {
        printf(" failed\n  !  mbedtls_x509_crt_parse returned -0x%x\n\n", -ret);
        return 1;
    }

    // Setup the SSL configuration
    ret = mbedtls_ssl_config_defaults(&conf,
                                      MBEDTLS_SSL_IS_CLIENT,
                                      MBEDTLS_SSL_TRANSPORT_STREAM,
                                      MBEDTLS_SSL_PRESET_DEFAULT);
    if (ret != 0) {
        printf(" failed\n  ! mbedtls_ssl_config_defaults returned -0x%x\n\n", -ret);
        return 1;
    }

    mbedtls_ssl_conf_authmode(&conf, MBEDTLS_SSL_VERIFY_OPTIONAL);
    mbedtls_ssl_conf_ca_chain(&conf, &cacert, NULL);
    mbedtls_ssl_conf_rng(&conf, mbedtls_ctr_drbg_random, &ctr_drbg);

    // Setup the SSL/TLS structure
    ret = mbedtls_ssl_setup(&ssl, &conf);
    if (ret != 0) {
        printf(" failed\n  ! mbedtls_ssl_setup returned -0x%x\n\n", -ret);
        return 1;
    }

    // Connect to the server
    ret = mbedtls_net_connect(&server_fd, "example.com", "443", MBEDTLS_NET_PROTO_TCP);
    if (ret != 0) {
        printf(" failed\n  ! mbedtls_net_connect returned -0x%x\n\n", -ret);
        return 1;
    }

    mbedtls_ssl_set_bio(&ssl, &server_fd, mbedtls_net_send, mbedtls_net_recv, NULL);

    // Perform the SSL/TLS handshake
    while ((ret = mbedtls_ssl_handshake(&ssl)) != 0) {
        if (ret != MBEDTLS_ERR_SSL_WANT_READ && ret != MBEDTLS_ERR_SSL_WANT_WRITE) {
            printf(" failed\n  ! mbedtls_ssl_handshake returned -0x%x\n\n", -ret);
            return 1;
        }
    }

    // Send a simple HTTP request
    const char *request = "GET / HTTP/1.1\r\nHost: example.com\r\n\r\n";
    ret = mbedtls_ssl_write(&ssl, (const unsigned char *) request, strlen(request));
    if (ret <= 0) {
        printf(" failed\n  ! mbedtls_ssl_write returned -0x%x\n\n", -ret);
        return 1;
    }

    // Read the HTTP response
    unsigned char buffer[1024];
    ret = mbedtls_ssl_read(&ssl, buffer, sizeof(buffer) - 1);
    if (ret <= 0) {
        printf(" failed\n  ! mbedtls_ssl_read returned -0x%x\n\n", -ret);
        return 1;
    }

    buffer[ret] = '\0';
    printf(" %s\n", buffer);

    // Cleanup
    mbedtls_ssl_close_notify(&ssl);
    mbedtls_net_free(&server_fd);
    mbedtls_ssl_free(&ssl);
    mbedtls_ssl_config_free(&conf);
    mbedtls_x509_crt_free(&cacert);
    mbedtls_ctr_drbg_free(&ctr_drbg);
    mbedtls_entropy_free(&entropy);

    return 0;
}
```

**توضیح:**
- **mbedtls_net_connect**: اتصال به سرور.
- **mbedtls_ssl_handshake**: اجرای فرایند دست‌دهی SSL/TLS.
- **mbedtls_ssl_write**: ارسال درخواست HTTP امن.
- **mbedtls_ssl_read**: خواندن پاسخ سرور.

این مثال نشان می‌دهد که چگونه می‌توان با استفاده از کتابخانه mbedTLS یک ارتباط امن با استفاده از TLS را بر روی STM32 برقرار کرد.
#### چالش روزانه:
1. پیاده‌سازی بوت امن و تأیید میان‌افزار در پروژه تعبیه‌شده خود.
2. رمزنگاری داده‌های حساس ذخیره شده در سیستم تعبیه‌شده خود با استفاده از یک الگوریتم رمزنگاری قوی.
3. مکانیزم‌های کنترل دسترسی را برای محدود کردن دسترسی بر اساس نقش‌های کاربر تنظیم کنید.
4. برقراری یک کانال ارتباطی امن (مانند HTTPS) برای انتقال داده‌ها.
5. یک ممیزی امنیتی از پروژه خود انجام داده و آسیب‌پذیری‌های بالقوه را شناسایی و رفع کنید.