### توضیح جامع درباره ساختارهای کنترلی و وراثت در ++C

### 1. ساختارهای کنترلی: If-Else و حلقه‌ها

ساختارهای کنترلی به شما اجازه می‌دهند تا جریان برنامه را بر اساس شرایط مختلف کنترل کنید.

#### If-Else Statement
کد زیر را در نظر بگیرید:

```cpp
#include <iostream>

int main() {
    int x = 10;

    if (x > 0) {
        std::cout << "x is positive" << std::endl;
    } else if (x == 0) {
        std::cout << "x is zero" << std::endl;
    } else {
        std::cout << "x is negative" << std::endl;
    }

    return 0;
}
```
##### توضیح:
- `if (x > 0) { ... }`: اگر شرط درست باشد، بلوک اجرا می‌شود.
- `else if (x == 0) { ... }`: اگر شرایط قبلی غلط باشند و این شرط درست باشد، بلوک اجرا می‌شود.
- `else { ... }`: اگر همه شرایط قبلی غلط باشند، بلوک اجرا می‌شود.

#### For Loop:
کد زیر را در نظر بگیرید:

```cpp
#include <iostream>

int main() {
    for (int i = 0; i < 5; i++) {
        std::cout << "i: " << i << std::endl;
    }

    return 0;
}
```
##### توضیح:
- `for (int i = 0; i < 5; i++) { ... }`: بلوک را ۵ بار تکرار می‌کند، با `i` از ۰ تا ۴.

#### While Loop:
کد زیر را در نظر بگیرید:

```cpp
#include <iostream>

int main() {
    int i = 0;

    while (i < 5) {
        std::cout << "i: " << i << std::endl;
        i++;
    }

    return 0;
}
```
##### توضیح:
- `while (i < 5) { ... }`: بلوک را تا زمانی که شرط درست باشد تکرار می‌کند.

### 2. مفهوم پیشرفته شی‌گرایی: وراثت
وراثت به شما اجازه می‌دهد تا کلاس‌های جدید را بر اساس کلاس‌های موجود ایجاد کنید. این امر باعث بازاستفاده از کد و برقراری رابطه بین کلاس‌ها می‌شود.

#### مثال وراثت:
کد زیر را در نظر بگیرید:

```cpp
#include <iostream>
#include <string>

// کلاس پایه
class Animal {
public:
    Animal(const std::string &name) : name(name) {}

    void speak() const {
        std::cout << "Animal sound" << std::endl;
    }

protected:
    std::string name;
};

// کلاس مشتق
class Dog : public Animal {
public:
    Dog(const std::string &name) : Animal(name) {}

    void speak() const {
        std::cout << name << " says: Woof!" << std::endl;
    }
};

int main() {
    Animal animal("Generic Animal");
    Dog dog("Buddy");

    animal.speak(); // فراخوانی متد کلاس پایه
    dog.speak();    // فراخوانی متد کلاس مشتق

    return 0;
}
```
##### توضیح:
- `class Animal { ... };`: کلاس پایه با یک سازنده و یک متد `speak`.
- `class Dog : public Animal { ... };`: کلاس مشتق که از 
`Animal`
 وراثت می‌برد و متد 
`speak`
 را بازنویسی می‌کند.
- `Dog(const std::string &name) : Animal(name) {}`: فراخوانی سازنده کلاس پایه از کلاس مشتق.

### 3. بینش سیستم‌های نهفته
در سیستم‌های نهفته، وراثت می‌تواند برای ایجاد درایورها یا هندلرهای خاص بر اساس رابط‌های عمومی استفاده شود. برای مثال، ممکن است یک کلاس عمومی 
`Sensor`
 و کلاس‌های خاص برای انواع مختلف سنسورها داشته باشید.

#### مثال نهفته: وراثت سنسور (کد شبه)

```cpp
#include <iostream>

// کد شبه برای محیط نهفته
class Sensor {
public:
    virtual void read() = 0; // تابع مجازی خالص
};

class TemperatureSensor : public Sensor {
public:
    void read() override {
        // خواندن مقدار دما
        std::cout << "Reading temperature" << std::endl;
    }
};

class PressureSensor : public Sensor {
public:
    void read() override {
        // خواندن مقدار فشار
        std::cout << "Reading pressure" << std::endl;
    }
};

int main() {
    TemperatureSensor tempSensor;
    PressureSensor pressureSensor;

    tempSensor.read();
    pressureSensor.read();

    return 0;
}
```
##### توضیح:
- `class Sensor { ... };`: کلاس پایه انتزاعی با یک تابع مجازی خالص `read`.
- `class TemperatureSensor : public Sensor { ... };` و `class PressureSensor : public Sensor { ... };`: کلاس‌های مشتق که تابع `read` را پیاده‌سازی می‌کنند.

### چالش روزانه:
یک کلاس پایه 
`Vehicle`
 با ویژگی‌های 
 `make` و `model`
  و یک متد برای نمایش آنها ایجاد کنید. کلاس 
  `Car` را از 
  `Vehicle`
   مشتق کنید که ویژگی 
   `numberOfDoors`
    را اضافه کند و یک متد برای نمایش همه جزئیات داشته باشد. برنامه‌ای بنویسید که چندین شیء 
    `Car`
     ایجاد کرده و جزئیات آنها را نمایش دهد.

#### مثال:

```cpp
#include <iostream>
#include <string>

// کلاس پایه
class Vehicle {
public:
    Vehicle(const std::string &make, const std::string &model) : make(make), model(model) {}

    virtual void display() const {
        std::cout << "Make: " << make << ", Model: " << model << std::endl;
    }

protected:
    std::string make;
    std::string model;
};

// کلاس مشتق
class Car : public Vehicle {
public:
    Car(const std::string &make, const std::string &model, int numberOfDoors)
        : Vehicle(make, model), numberOfDoors(numberOfDoors) {}

    void display() const override {
        Vehicle::display();
        std::cout << "Number of Doors: " << numberOfDoors << std::endl;
    }

private:
    int numberOfDoors;
};

int main() {
    Car car1("Toyota", "Corolla", 4);
    Car car2("Honda", "Civic", 2);

    car1.display();
    car2.display();

    return 0;
}
```
##### توضیح:
- `class Vehicle { ... };`: کلاس پایه با ویژگی‌های 
`make` و `model`
 و یک متد `display`.
- `class Car : public Vehicle { ... };`: کلاس مشتق که ویژگی 
`numberOfDoors`
 را اضافه کرده و متد 
 `display`
  را بازنویسی می‌کند.

### پیاده‌سازی HAL برای این مثال
در سیستم‌های نهفته، می‌توانید از کتابخانه 
HAL (Hardware Abstraction Layer)
 برای مدیریت سخت‌افزار استفاده کنید. در اینجا یک مثال از پیاده‌سازی 
 HAL
  برای یک کلاس 
 `Vehicle`
  و یک کلاس 
 `Car`
  آورده شده است. فرض کنیم که ما با یک میکروکنترلر 
  ARM
   کار می‌کنیم و از 
   HAL
    ارائه شده توسط 
    STMicroelectronics
     استفاده می‌کنیم.

```cpp
#include "stm32f4xx_hal.h"

// فرض کنید این فایل‌ها به درستی تنظیم شده‌اند
#include "main.h"
using namespace std;
// کلاس پایه
class Vehicle {
public:
    Vehicle(const string &make, const string &model) : make(make), model(model) {}

    virtual void display() const {
        printf("Make: %s, Model: %s\n", make.c_str(), model.c_str());
    }

protected:
    std::string make;
    std::string model;
};

// کلاس مشتق
class Car : public Vehicle {
public:
    Car(const std::string &make, const std::string &model, int numberOfDoors)
        : Vehicle(make, model), numberOfDoors(numberOfDoors) {}

    void display() const override {
        Vehicle::display();
        printf("Number of Doors: %d\n", numberOfDoors);
    }

private:
    int numberOfDoors;
};

int main(void) {
    HAL_Init(); // Initialization of HAL library

    Car car1("Toyota", "Corolla", 4);
    Car car2("Honda", "Civic", 2);

    car1.display();
    car2.display();

    while (1) {
        // Loop forever
    }
}
```
##### توضیح:
- `HAL_Init();`: راه‌اندازی اولیه کتابخانه 
HAL
- استفاده از 
`printf`
 برای نمایش جزئیات به جای 
 `std::cout`
 ، چرا که در محیط‌های نهفته معمولاً از روش‌های ساده‌تری برای خروجی‌گیری استفاده می‌شود.

این مثال‌ها به شما کمک می‌کنند تا با مفاهیم پایه‌ای و پیشرفته برنامه‌نویسی شی‌گرا در 
++C
 و همچنین پیاده‌سازی آنها در سیستم‌های نهفته آشنا شوید.