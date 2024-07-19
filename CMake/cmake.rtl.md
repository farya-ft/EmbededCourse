قطعاً، در اینجا توضیح مختصری در مورد نحوه استفاده از CMake به همراه دستورات مفید آن به فارسی آورده شده است.

### معرفی CMake

CMake یک ابزار متن‌باز برای ساختن، آزمایش و بسته‌بندی نرم‌افزار است. با استفاده از فایل‌های پیکربندی (CMakeLists.txt)، شما می‌توانید پروژه‌های چندپلتفرمه را به سادگی مدیریت کنید.

### مراحل استفاده از CMake

1. **ایجاد فایل CMakeLists.txt**
   فایل CMakeLists.txt، حاوی دستوراتی است که به CMake می‌گوید چگونه پروژه شما را بسازد.

2. **اجرای CMake**
   با استفاده از دستور `cmake`، فایل‌های پروژه پیکربندی می‌شوند.

3. **ساخت پروژه**
   پس از پیکربندی، با استفاده از ابزارهای ساخت (مثل make)، پروژه خود را بسازید.

### دستورات مهم CMake

1. `cmake .`  
   **توضیح:** پروژه را از دایرکتوری فعلی پیکربندی می‌کند.

2. `cmake <path/to/source>`  
   **توضیح:** پروژه را از دایرکتوری مشخص شده پیکربندی می‌کند.

3. `cmake -B <build_dir> -S <source_dir>`  
   **توضیح:** پروژه را از دایرکتوری منبع پیکربندی و فایل‌های ساخت را در دایرکتوری ساخت قرار می‌دهد.

4. `cmake --build <build_dir>`  
   **توضیح:** پروژه را از دایرکتوری ساخت مشخص شده می‌سازد.

5. `cmake -DCMAKE_BUILD_TYPE=Release`  
   **توضیح:** پروژه را برای ساخت در حالت انتشار (Release) پیکربندی می‌کند.

6. `cmake -DCMAKE_BUILD_TYPE=Debug`  
   **توضیح:** پروژه را برای ساخت در حالت رفع اشکال (Debug) پیکربندی می‌کند.

7. `cmake --install <build_dir>`  
   **توضیح:** پروژه ساخته شده را نصب می‌کند.

8. `cmake --version`  
   **توضیح:** نسخه نصب شده CMake را نمایش می‌دهد.

### نمونه فایل CMakeLists.txt

در اینجا یک نمونه ساده از فایل CMakeLists.txt آورده شده است:

```cmake
cmake_minimum_required(VERSION 3.10)

# نام پروژه
project(ExampleProject)

# اضافه کردن فایل‌های سورس
add_executable(ExampleExecutable main.cpp)
```

### مراحل کامل برای ساخت پروژه

1. **ایجاد ساختار پروژه:**

   ```plaintext
   ExampleProject/
   ├── CMakeLists.txt
   └── main.cpp
   ```

2. **نوشتن فایل CMakeLists.txt:**

   ```cmake
   cmake_minimum_required(VERSION 3.10)
   project(ExampleProject)
   add_executable(ExampleExecutable main.cpp)
   ```

3. **نوشتن فایل main.cpp:**

   ```cpp
   #include <iostream>
   int main() {
       std::cout << "Hello, CMake!" << std::endl;
       return 0;
   }
   ```

4. **پیکربندی و ساخت پروژه:**

   ```sh
   mkdir build
   cd build
   cmake ..
   cmake --build .
   ```

5. **اجرای برنامه:**

   ```sh
   ./ExampleExecutable
   ```

این مراحل و دستورات، پایه‌ای‌ترین و مفیدترین دستورات و روش‌های استفاده از CMake برای مدیریت و ساخت پروژه‌های نرم‌افزاری هستند.