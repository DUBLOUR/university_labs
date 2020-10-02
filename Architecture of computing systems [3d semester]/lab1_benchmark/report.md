# Отчёт по лабораторной работе №1
##### Никитенко Максим Вадимович
##### ФКНК, К-22

### Постановка задачи
Лабораторная работа предусматривает создание системы тестирование и проведение замера скорости работы некоторых типов в C++ и визуализации результатов.

### Результаты

На всех запусках использовался 11-й стандарт языка и опция компиляции `-w`.

##### Запуск 1
![запуск1](https://user-images.githubusercontent.com/20306702/94895611-77696980-0494-11eb-9739-025d840003f0.png)

Машина:
- OS: Arch Linux x86_64 (Kernel: 5.8.12)
- CPU: Intel Pentium B960 (4 cores) @ 2.20 GHz 
- RAM: 3824MiB 

##### Запуск 2
![запуск2](https://user-images.githubusercontent.com/20306702/94895693-949e3800-0494-11eb-9239-fc612260ded5.png)

Docker 19.03.13 (на базе [gcc Image](https://hub.docker.com/_/gcc), Ubuntu) на той же машине

##### Запуск 3
![запуск3](https://user-images.githubusercontent.com/20306702/94894682-83ecc280-0492-11eb-92b8-65cca32fda05.png)

Docker 19.03.13 на машине:
- OS: Windows 10 Pro, 2019
- CPU: Intel Core i7-9750H (6 cores) @ 2.60 GHz 
- RAM: 16 GB

##### Запуск 4
![запуск4](https://user-images.githubusercontent.com/20306702/94897774-fd87af00-0498-11eb-8f86-ab36be577696.png)

Условия аналогичные запуску 2


### Наблюдения и выводы
- При использовании Docker поверх системы производительность может падать на 5-9% для всех операций.
- Использование модификатора типа [register](https://en.cppreference.com/w/cpp/language/storage_duration) позволяет получить значительный прирост производительности на лёгких операциях (`+`, '-`, `^`). Когда же время обработки операции играет большую роль, чем скорость доступа к памяти, то выигриш невилируется.
- Разница в скорости между знаковыми и беззнаковыми целочисленными типами практически отсутствует.



## Методология и технические подробности

Для каждого тестируемого случая (тип + операции) была создана пара функций, отличающиеся одной строчкой: в одной мы производим операцию, в другой -- нет. Каждая функция вызывается с некоторым большим количеством операций (по умолчанию `1е7`), а время работы операции определяется разницей во времени работы этих функций. Например:
```c++
int Test_longlong_xor(int count_of_iterations) {
    long long mask = (1<<12)-1;
    long long hash = 0, now = 1;
    for (int i=0; i<count_of_iterations; ++i) {
        hash = hash ^ now;
        now += 1;
        hash &= mask;
    }
    return (int) hash + mask;
}

int Test_longlong_xor_empty(int count_of_iterations) {
    long long mask = (1<<12)-1;
    long long hash = 0, now = 1;
    for (int i=0; i<count_of_iterations; ++i) {
        hash = hash; // ^ now;
        now += 1;
        hash &= mask;
    }
    return (int) hash + mask;
}
```

Обрезание по последним битам в (`mask = (1<<12)-1; hash &= mask;`) используется для того, чтобы избежать переполнения, если например, используется операция `*`, или `+`. Для вещественных чисел применяется следующий шаблон. Как легко убедиться, он позволяет избежать денормализации `hash`, ведь благодаря `(hash+1)` и делению на большее его значение постоянно будет находится около 1:
```c++
int Test_registerfloat_mult_div(int count_of_iterations) {
    register float hash = 1, now = 1, a = 173, b = 9973;
    for (int i=0; i<count_of_iterations; ++i) {
        hash = ((hash+1) * a) / b;
        now += 1;
    }
    return (int) hash;
}

int Test_registerfloat_mult_div_empty(int count_of_iterations) {
    register float hash = 1, now = 1, a = 173, b = 9973;
    for (int i=0; i<count_of_iterations; ++i) {
        hash = ((hash+1)); // * a) / b;
        now += 1;
    }
    return (int) hash;
}
```

Функции генерируются файлом `codegen.cpp` по нескольким шаблонам и записываются в `tests.cpp`. В качестве источника тестовых случаев используется перечисление из `drafts.h`, которое задаётся следующим образом:

```c++
vector<MeasureDraft>{
    MeasureDraft(1, "unsigned int", "+", "plus"),
    MeasureDraft(1, "long long", "^", "xor"),
    MeasureDraft(1, "long long", "%", "mod"),
    MeasureDraft(2, "__int128", "*", "mult", "%", "mod"),
    MeasureDraft(3, "register float", "+", "plus", "*", "mult"),
    ...
}
```

В дальнейшем сгенерированные функции обрабатываются, с помощью библиотеки [chrono](https://cplusplus.com/reference/chrono/) проводится замер времени работы (файл      `measure.cpp`). 
Все замеры запускаются из `main.cpp`, там же и визуализируются.

Была настроена автоматическая сборка проекта с помощью `Makefile` и создан docker образ. Об этом также написано [здесь](https://github.com/DUBLOUR/university_labs/tree/master/Architecture%20of%20computing%20systems%20%5B3d%20semester%5D/lab1_benchmark).

