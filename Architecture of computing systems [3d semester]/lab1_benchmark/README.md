# Сравнение производительности типов данных С++
[Теория и условия](https://sites.google.com/site/byvkyiv1/arhiteom_stac/arhiteom_lab_01)

![пример работы](https://user-images.githubusercontent.com/20306702/94889018-8693eb80-0483-11eb-8cb5-1d9c0978cbbb.png)

#### [Отчёт о лабораторной](https://github.com/DUBLOUR/university_labs/blob/master/Architecture%20of%20computing%20systems%20%5B3d%20semester%5D/lab1_benchmark/report.md)

### Запуск проекта с dockerhub
`docker pull karasicklab0/type_benchmarking`

### Сборка проекта
Ручная компиляция:
- `cd src && g++ main.cpp && ./a.out` (`a.exe` вместо `a.out` на Windows)

Сборка через CMake:
- `cd build`
- `cmake -G"Unix Makefiles" ..`
- `make`
- `./../bin/benchmarking` для запуска

Создание и запуск Docker-образа:
- `docker build . -t type_benchmarking:1.0.0`
- `docker run --rm -it type_benchmarking:1.0.0`

Для изменения списка тестируемых функций:
- `cd src/`
- Внесите свои конфигурации в файл `drafts.h` 
- Запустите `g++ codegen.cpp && ./a.out` (`a.exe` вместо `a.out` на Windows)
- Скомпилируйте проект по инструкцям выше