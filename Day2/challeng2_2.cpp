//Write a program that creates multiple Person objects and displays their details.

#include <iostream>
#include <vector>
#include <string>

class Person {
private:
    std::string name;
    int age;

public:
    // Constructor
    Person(std::string n, int a) : name(n), age(a) {}

    // Getter for name
    std::string getName() const {
        return name;
    }

    // Getter for age
    int getAge() const {
        return age;
    }

    // Method to display person details
    void displayDetails() const {
        std::cout << "Name: " << name << ", Age: " << age << std::endl;
    }
};

int main() {
    // Vector to store Person objects
    std::vector<Person> people;     /*ین دستور یک آرایه پویا به نام 
                                      people
                                     ایجاد می‌کند که می‌تواند اشیاء 
                                       Person
                                      را ذخیره کند.*/

    // Creating Person objects
    people.push_back(Person("Alice", 30)); /*این دستور یک شیء 
                                              Person
                                               با نام 
                                             "Alice" 
                                               و سن 
                                               30 
                                             ایجاد کرده و آن را به وکتور  
                                             people
                                              اضافه می‌کند.*/
    people.push_back(Person("Bob", 25));
    people.push_back(Person("Charlie", 20));

    // Displaying details of each person
    /*ین حلقه برای هر شیء 
    Person 
    در وکتور 
    people
     تابع 
     displayDetails
      را صدا می‌زند تا جزئیات آن شخص را نمایش دهد*/
    for (const auto& person : people) {
        person.displayDetails();        
    }

    return 0;
}
/*چرا از وکتور استفاده کرده‌ایم:
افزودن آسان اشیاء: با استفاده از 
push_back
 می‌توانیم به راحتی اشیاء جدیدی را به لیست اضافه کنیم.
مدیریت خودکار حافظه: نیازی به مدیریت دستی حافظه برای ذخیره اشیاء 
Person
 نداریم.
اندازه پویا: اگر نیاز به افزودن یا حذف اشیاء داشته باشیم،
 وکتور به طور خودکار اندازه خود را تنظیم می‌کند.*/

 /*چرا از 
 auto
  استفاده می‌کنیم؟
تشخیص خودکار نوع متغیر:

استفاده از 
auto
 به کامپایلر اجازه می‌دهد تا به طور خودکار نوع مناسب متغیر را تشخیص دهد. 
این کار به ویژه زمانی مفید است که نوع متغیر پیچیده یا طولانی باشد.
در اینجا، 
auto
 نوع متغیر 
person 
را به عنوان یک ارجاع ثابت به شیء 
Person
 (یعنی 
const Person&) 
تشخیص می‌دهد.

استفاده از 
auto
 کد را ساده‌تر و خواناتر می‌کند،
  زیرا نیازی به تعیین دقیق نوع متغیر نیست.
  
  
  // بدون استفاده از 
  auto:
  
for (std::vector<Person>::const_iterator it = people.begin(); it != people.end(); ++it) {
    const Person& person = *it;
    person.displayDetails();
}*/
