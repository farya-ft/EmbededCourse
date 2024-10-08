حتما، در اینجا فهرستی از دستورات مهم گیت و گیت‌هاب با توضیحات کوتاه برای هر دستور آورده شده است:

### دستورات گیت (Git Commands):

1. `git init`  
   **توضیح:** مخزن گیت جدیدی در دایرکتوری فعلی ایجاد می‌کند.
   
2. `git clone <repository>`  
   **توضیح:** یک مخزن را از راه دور دانلود و کپی می‌کند.

3. `git add <file>`  
   **توضیح:** فایل یا فایل‌های مشخص شده را به منطقه مرحله‌بندی (staging area) اضافه می‌کند.

4. `git commit -m "message"`  
   **توضیح:** تغییرات مرحله‌بندی شده را با یک پیام توضیحی در مخزن محلی ثبت می‌کند.

5. `git status`  
   **توضیح:** وضعیت فایل‌های پروژه را نشان می‌دهد (تغییرات، فایل‌های مرحله‌بندی شده، و غیره).

6. `git log`  
   **توضیح:** تاریخچه کامل کامیت‌های مخزن را نمایش می‌دهد.

7. `git pull`  
   **توضیح:** آخرین تغییرات را از مخزن راه دور دانلود و با شاخه فعلی ادغام می‌کند.

8. `git push`  
   **توضیح:** تغییرات محلی را به مخزن راه دور ارسال می‌کند.

9. `git branch`  
   **توضیح:** لیستی از شاخه‌های موجود در مخزن را نمایش می‌دهد.

10. `git branch <branch-name>`  
    **توضیح:** شاخه جدیدی با نام مشخص شده ایجاد می‌کند.

11. `git checkout <branch-name>`  
    **توضیح:** به شاخه مشخص شده تغییر مکان می‌دهد.

12. `git merge <branch-name>`  
    **توضیح:** شاخه مشخص شده را با شاخه فعلی ادغام می‌کند.

13. `git remote`  
    **توضیح:** لیستی از مخازن راه دور مرتبط با مخزن فعلی را نمایش می‌دهد.

14. `git remote add <name> <url>`  
    **توضیح:** یک مخزن راه دور جدید اضافه می‌کند.

15. `git fetch`  
    **توضیح:** تمام شاخه‌های جدید را از مخزن راه دور دانلود می‌کند.

16. `git reset --hard <commit>`  
    **توضیح:** مخزن را به حالت یک کامیت قبلی برمی‌گرداند.

17. `git stash`  
    **توضیح:** تغییرات کاری فعلی را به طور موقت ذخیره می‌کند.

18. `git stash pop`  
    **توضیح:** تغییرات ذخیره شده را از stash بازیابی می‌کند و به شاخه فعلی اعمال می‌کند.

### دستورات گیت‌هاب (GitHub Commands):

1. `gh auth login`  
   **توضیح:** برای ورود به حساب کاربری گیت‌هاب از ترمینال استفاده می‌شود.

2. `gh repo create`  
   **توضیح:** یک مخزن جدید در گیت‌هاب ایجاد می‌کند.

3. `git clone <repository-url>`
`git clone https://github.com/username/repository.git`
   
   **توضیح:** یک مخزن گیت‌هاب را کلون می‌کند.

4. `gh repo fork <repository>`  
   **توضیح:** یک مخزن گیت‌هاب را فوروارد (کپی) می‌کند.

5. `gh issue list`  
   **توضیح:** لیستی از مشکلات (issues) مخزن را نمایش می‌دهد.

6. `gh issue create`  
   **توضیح:** یک مشکل (issue) جدید در مخزن ایجاد می‌کند.

7. `gh pr list`  
   **توضیح:** لیستی از درخواست‌های کشش (pull requests) مخزن را نمایش می‌دهد.

8. `gh pr create`  
   **توضیح:** یک درخواست کشش (pull request) جدید ایجاد می‌کند.

9. `gh pr merge`  
   **توضیح:** یک درخواست کشش (pull request) را ادغام می‌کند.

این دستورات مهم‌ترین و پایه‌ای‌ترین دستورات گیت و گیت‌هاب هستند که برای مدیریت پروژه‌ها و مخازن استفاده می‌شوند.