@echo off
chcp 65001
rem Перевірка, чи передано каталог як параметр
if "%~1"=="" (
    echo Потрібно вказати шлях до каталогу як параметр.
    goto :eof
)

rem Перехід до вказаного каталогу
cd /d "%~1" 2>nul
if errorlevel 1 (
    echo Каталог "%~1" не знайдено.
    goto :eof
)

rem Лічильник підкаталогів
set /a count=0

rem Запускаємо цикл для кожного підкаталогу у вказаному каталозі
for /d %%i in (*) do (
    rem Збільшуємо лічильник на 1
    set /a count+=1
)

rem Виводимо результат
echo Кількість підкаталогів у каталозі "%cd%": %count%
pause >nul
