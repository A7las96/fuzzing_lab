# Лабораторная работа по предмету "Сертификация средств защиты информации"
---
> Лабораторная работа выполнялась на ОС Ubuntu 22.04.4 LTS
В рамках данной лабораторной работы осуществлялось фаззинг-тестирование библиотеки(далее - проект) с открытым исходным кодом [libxlsxwriter](https://github.com/jmcnamara/libxlsxwriter). Данный проект позволяет создавать Excel XLSX файлы с использованием языка программирования C.
## 1 Сборка проекта
---
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
5. Соберем проект libxlsxwriter с использованием команды *make*:
```
~/Documents/fuzz$ cd libxlsxwriter
~/Documents/fuzz/libxlsxwriter$ make
```
В результате этого будет создана директория /lib внутри директории /libxlsxwriter со следующим содержанием:
```
~/Documents/fuzz/libxlsxwriter$ ls lib
libxlsxwriter.a  libxlsxwriter.so  libxlsxwriter.so.7
```
