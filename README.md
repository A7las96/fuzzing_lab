# Лабораторная работа по предмету "Сертификация средств защиты информации"

> Лабораторная работа выполнялась на ОС Ubuntu 22.04.4 LTS

В рамках данной лабораторной работы осуществлялось фаззинг-тестирование библиотеки(далее - проект) с открытым исходным кодом [libxlsxwriter](https://github.com/jmcnamara/libxlsxwriter). Данный проект позволяет создавать Excel XLSX файлы с использованием языка программирования C.
## 1 Сборка проекта
Данный раздел содержит информацию о сборке проекта libxlsxwriter, а также о процедуре контрольного суммирования, необходимой для проведения в рамках данной лабораторной работы.
1. Согласно документации на проект libxlsxwriter, изначально необходимо установить зависимость [zlib](https://www.zlib.net/). Сделать это можно с помощью следующей команды:
```
~/Documents/fuzz$ sudo apt-get install -y zlib1g-dev
```
2. Далее необходимо склонировать репозиторий проекта с помощью команды:
```
~/Documents/fuzz$ git clone https://github.com/jmcnamara/libxlsxwriter.git
```
3. Для вычисления контрольной суммы создадим архив с скаченным проектом. Перейдем в директорию с установленным репозиторием и выполним команду:
```
~/Documents/fuzz$ tar -cf libxlsxwriter.tar libxlsxwriter/
```
4. Вычислим контрольную сумму используя алгоритмы MD5 и SHA256:
```
~/Documents/fuzz$ md5sum libxlsxwriter.tar
b8b44051c76e36853789ddc2942c5d89  libxlsxwriter.tar
~/Documents/fuzz$ sha256sum libxlsxwriter.tar
d023a44119d2d6de625e7177069972acff92c0dfeb1fde060b6af59c4a470e2f  libxlsxwriter.tar
```
## 2 Фаззинг-тестирование
В данном разделе описывается процесс фаззинг-тестирования с помощью ПО AFLplusplus.
1. Склонируем репозиторий с AFLplusplus с помощью команды:
```
~/Documents/fuzz$ git clone https://github.com/AFLplusplus/AFLplusplus.git
```
2. Соберем кастомные компиляторы для AFL:
```
~/Documents/fuzz$ cd AFLplusplus/
~/Documents/fuzz/AFLplusplus$ make
```
3. Соберем проект libxlsxwriter. Использоваться для этого будет CMake. авторами проекта любезно был предоставлен [мануал](https://libxlsxwriter.github.io/getting_started.html#:~:text=cmake%20..%0Acmake%20%2D%2Dbuild%20.-,Build%20the%20examples,-If%20there%20weren%27t) по сборке файлов с примерами работы libxlsxwriter, которые позднее очень пригодятся для самого фаззинга. Для их сборки установим кастомный компилятор afl-gcc для С, afl-g++ для C++ с последующей конфигурацией сборки в директории с нашим проектом. Для этого исполним следующие команды:
```
~/Documents/fuzz/libxlsxwriter$ CC=../AFLplusplus/afl-gcc CXX=../AFLplusplus/afl-g++ cmake ./ -DBUILD_EXAMPLES=ON

~/Documents/fuzz/libxlsxwriter$ CC=../AFLplusplus/afl-gcc CXX=../AFLplusplus/afl-g++ cmake --build .
```
4. В результате в корне проекта появится папка /examples, в которой будут лежать файлы с примерами работы:
![image](https://github.com/user-attachments/assets/ce47364b-2657-4e95-9608-697490ab48e3)
