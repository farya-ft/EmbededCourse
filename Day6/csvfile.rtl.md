فایل 
CSV (Comma-Separated Values)
 نوعی فایل متنی است که برای ذخیره‌سازی داده‌ها به شکل جدول‌بندی شده به کار می‌رود. در این فایل، هر خط از فایل نمایانگر یک رکورد است و هر ستون از آن رکورد با یک کاما (,) از سایر ستون‌ها جدا می‌شود. این فرمت به دلیل سادگی و قابلیت خواندن توسط اکثر نرم‌افزارهای تجزیه و تحلیل داده‌ها بسیار محبوب است.

### مثال یک فایل CSV
فرض کنید می‌خواهید اطلاعات دانشجویان را ذخیره کنید. فایل 
CSV
 می‌تواند به صورت زیر باشد:

```
id,name,age
1,Ali Rezaei,23
2,Sara Ahmadi,21
3,Hossein Karimi,25
```

در این مثال:
- سطر اول 
(id,name,age)
 نشان‌دهنده نام ستون‌ها یا عنوان‌ها است.
- هر سطر بعدی نشان‌دهنده یک رکورد است که در آن داده‌های هر ستون با کاما از هم جدا شده‌اند.

### ویژگی‌های فایل CSV
1. **ساده و قابل خواندن:** فایل‌های 
CSV
 به راحتی با نرم‌افزارهای ویرایش متن مثل 
 Notepad
  قابل مشاهده و ویرایش هستند.
2. **قابلیت واردات و صادرات:** اکثر برنامه‌های مدیریت داده مثل 
Excel، Google Sheets
 و پایگاه‌های داده می‌توانند فایل‌های 
 CSV
  را وارد و صادر کنند.
3. **کاربردی برای انتقال داده:** به دلیل فرمت ساده و متنی، 
CSV
‌ها برای انتقال داده‌ها بین سیستم‌های مختلف بسیار مناسب هستند.

### مثال در کد
در این مثال یک برنامه ساده به زبان 
C++
 برای خواندن و نوشتن در یک فایل 
 CSV
  توضیح داده شده است. فایل 
  CSV
   شامل اطلاعاتی مثل شناسه 
   (id)، نام (name) و سن (age)
    است که با کاما از هم جدا شده‌اند.

```cpp
#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>

struct Record {
    int id;
    std::string name;
    int age;
};

std::vector<Record> readCSV(const std::string& filename) {
    std::vector<Record> records;
    std::ifstream file(filename);
    std::string line;

    if (file.is_open()) {
        std::getline(file, line); // خواندن خط اول که شامل عنوان ستون‌ها است

        while (std::getline(file, line)) {
            std::istringstream ss(line);
            std::string token;
            Record record;

            std::getline(ss, token, ',');
            record.id = std::stoi(token);
            std::getline(ss, token, ',');
            record.name = token;
            std::getline(ss, token, ',');
            record.age = std::stoi(token);

            records.push_back(record);
        }
        file.close();
    }
    return records;
}

void writeCSV(const std::string& filename, const std::vector<Record>& records) {
    std::ofstream file(filename);

    if (file.is_open()) {
        file << "id,name,age\n"; // نوشتن عنوان ستون‌ها

        for (const auto& record : records) {
            file << record.id << ',' << record.name << ',' << record.age << '\n';
        }
        file.close();
    }
}

int main() {
    std::vector<Record> records = {
        {1, "Ali Rezaei", 23},
        {2, "Sara Ahmadi", 21},
        {3, "Hossein Karimi", 25}
    };

    std::string filename = "students.csv";
    writeCSV(filename, records);

    std::vector<Record> readRecords = readCSV(filename);

    for (const auto& record : readRecords) {
        std::cout << "ID: " << record.id << ", Name: " << record.name << ", Age: " << record.age << '\n';
    }

    return 0;
}
```

در این کد:
- `readCSV`:
 داده‌ها را از فایل 
 CSV
  می‌خواند و به یک لیست از رکوردها تبدیل می‌کند.
- `writeCSV`:
 داده‌های لیست رکوردها را به فایل 
 CSV
  می‌نویسد.
- `main`:
 برنامه اصلی که یک لیست از رکوردها را ایجاد کرده و سپس آن را در فایل 
 CSV
  ذخیره و از فایل می‌خواند.

این مثال نشان‌دهنده‌ی نحوه استفاده از فایل‌های 
CSV
 برای ذخیره‌سازی و خواندن داده‌ها به زبان 
 C++
  است.