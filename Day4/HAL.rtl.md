### روز چهارم: توابع و چندریختی
#### 1. توابع
توابع بخش‌های قابل استفاده مجدد کد هستند که یک وظیفه خاص را انجام می‌دهند. آنها به سازماندهی کد، کاهش تکرار و بهبود خوانایی کمک می‌کنند.

#### مثال تابع پایه

```cpp
#include <iostream>

// اعلان تابع
int add(int a, int b);

int main() {
    int sum = add(5, 3);

    std::cout << "Sum: " << sum << std::endl;
    return 0;
}

// تعریف تابع
int add(int a, int b) {
    return a + b;
}
```
##### توضیح:
- `int add(int a, int b);`: اعلان تابع.
- `int add(int a, int b) { ... }`: تعریف تابع. این تابع دو عدد صحیح را گرفته و مجموع آنها را برمی‌گرداند.
- `sum = add(5, 3);`: فراخوانی تابع add با آرگومان‌های 5 و 3.

#### بارگذاری تابع (Function Overloading)

بارگذاری تابع به شما امکان می‌دهد تا چندین تابع با نام یکسان ولی با لیست‌های پارامتر متفاوت تعریف کنید.
```cpp
#include <iostream>

// بارگذاری تابع
int add(int a, int b) {
    return a + b;
}

double add(double a, double b) {
    return a + b;
}

int main() {
    int intSum = add(5, 3);
    double doubleSum = add(5.5, 3.3);
    std::cout << "Integer Sum: " << intSum << std::endl;
    std::cout << "Double Sum: " << doubleSum << std::endl;
    return 0;
}
```
##### توضیح:
- دو تابع add، یکی برای اعداد صحیح و یکی برای اعداد اعشاری.
- تابع صحیح براساس نوع آرگومان‌ها فراخوانی می‌شود.

#### 2. مفهوم پیشرفته OOP: چندریختی (Polymorphism)
چندریختی به متدها اجازه می‌دهد که براساس شی‌ای که روی آن عمل می‌کنند، کارهای مختلفی انجام دهند، حتی اگر نام یکسانی داشته باشند.

#### مثال چندریختی

```cpp
#include <iostream>
#include <string>

// کلاس پایه
class Animal {
public:
    virtual void speak() const {
        std::cout << "Animal sound" << std::endl;
    }
};

// کلاس مشتق شده
class Dog : public Animal {
public:
    void speak() const override {
        std::cout << "Woof!" << std::endl;
    }
};

// کلاس مشتق شده
class Cat : public Animal {
public:
    void speak() const override {
        std::cout << "Meow!" << std::endl;
    }
};

void makeAnimalSpeak(const Animal &animal) {
    animal.speak();
}

int main() {
    Dog dog;
    Cat cat;

    makeAnimalSpeak(dog); // خروجی: Woof!
    makeAnimalSpeak(cat); // خروجی: Meow!

    return 0;
}
```
##### توضیح:
- `virtual void speak() const { ... }`: اعلام یک متد مجازی در کلاس پایه.
- `void speak() const override { ... }`: نادیده‌گیری متد کلاس پایه در کلاس‌های مشتق شده.
- `makeAnimalSpeak(const Animal &animal) { ... }`: یک مرجع به کلاس Animal را می‌پذیرد و متد speak را فراخوانی می‌کند. متد صحیح براساس نوع واقعی شی (Dog یا Cat) فراخوانی می‌شود.

#### 3. بینش سیستم‌های تعبیه‌شده
در سیستم‌های تعبیه‌شده، چندریختی می‌تواند برای مدیریت انواع مختلف سنسورها یا دستگاه‌ها به صورت یکنواخت استفاده شود.

#### مثال تعبیه‌شده: چندریختی (کد شبه)
```cpp
#include <iostream>

// کلاس پایه
class Sensor {
public:
    virtual void read() = 0; // تابع مجازی خالص
};

// کلاس مشتق شده برای سنسور دما
class TemperatureSensor : public Sensor {
public:
    void read() override {
        // خواندن مقدار دما
        std::cout << "Reading temperature" << std::endl;
    }
};

// کلاس مشتق شده برای سنسور فشار
class PressureSensor : public Sensor {
public:
    void read() override {
        // خواندن مقدار فشار
        std::cout << "Reading pressure" << std::endl;
    }
};

void readSensor(Sensor &sensor) {
    sensor.read();
}

int main() {
    TemperatureSensor tempSensor;
    PressureSensor pressureSensor;

    readSensor(tempSensor);  // خروجی: Reading temperature
    readSensor(pressureSensor);  // خروجی: Reading pressure

    return 0;
}
```
##### توضیح:
- `virtual void read() = 0;`: اعلام یک تابع مجازی خالص در کلاس پایه Sensor.
- `void read() override { ... }`: پیاده‌سازی متد read در کلاس‌های مشتق شده.
- `readSensor(Sensor &sensor) { ... }`: یک مرجع به کلاس Sensor را می‌پذیرد و متد read را فراخوانی می‌کند، که چندریختی را نشان می‌دهد.

### چالش روزانه:
یک کلاس پایه به نام 
Shape
 با یک متد مجازی خالص به نام 
area
 ایجاد کنید. دو کلاس مشتق شده 
 Circle و Rectangle
 را ایجاد کنید که متد 
 area
  را پیاده‌سازی کنند. برنامه‌ای بنویسید که نمونه‌هایی از 
 Circle و Rectangle
  ایجاد کرده و آنها را در یک آرایه از اشاره‌گرهای 
 Shape
  ذخیره کند و مساحت آنها را چاپ کند.

#### مثال:
```cpp
#include <iostream>
#include <vector>
#include <cmath>

class Shape {
public:
    virtual double area() const = 0; // متد مجازی خالص
};

class Circle : public Shape {
private:
    double radius;
public:
    Circle(double r) : radius(r) {}
    double area() const override {
        return M_PI * radius * radius;
    }
};

class Rectangle : public Shape {
private:
    double width, height;
public:
    Rectangle(double w, double h) : width(w), height(h) {}
    double area() const override {
        return width * height;
    }
};

int main() {
    std::vector<Shape*> shapes;
    shapes.push_back(new Circle(5.0));
    shapes.push_back(new Rectangle(4.0, 6.0));

    for (const Shape* shape : shapes) {
        std::cout << "Area: " << shape->area() << std::endl;
    }

    // آزاد کردن حافظه
    for (Shape* shape : shapes) {
        delete shape;
    }

    return 0;
}
```
##### توضیح:

- `virtual double area() const = 0;`: اعلام یک متد مجازی خالص در کلاس پایه Shape.
- `double area() const override { ... }`: پیاده‌سازی متد area در کلاس‌های مشتق شده Circle و Rectangle.
- استفاده از بردار برای ذخیره‌سازی اشاره‌گرهای 
Shape و چاپ مساحت هر شکل.

اشاره‌گرها می‌توانند به 
null یا آدرس‌های غیر معتبر اشاره کنند، که نیاز به مدیریت دقیق دارند.
ارجاعات همیشه باید به یک شیء معتبر اشاره کنند و نمی‌توانند به 
null باشند.
کارایی:

هر دو روش می‌توانند کارایی مشابهی داشته باشند، اما استفاده از ارجاعات می‌تواند در جلوگیری از کپی غیرضروری داده‌ها موثر باشد.
اشاره‌گرها انعطاف بیشتری دارند، به خصوص در کار با آرایه‌ها و حافظه پویا.

### ابزارهای مورد نیاز:
- کامپایلر C++ (مثل g++, clang)
- IDE (مثل Visual Studio، CLion، یا VS Code)
- کتابخانه‌های استاندارد C++ و iostream

