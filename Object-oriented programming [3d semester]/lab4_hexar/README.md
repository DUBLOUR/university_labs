### Почти-многопользовательская игра с управлением мышью и захватом территории на гексагональной сетке.

![Screenshot_20201216_082921](https://user-images.githubusercontent.com/20306702/102313675-c003cf80-3f79-11eb-981b-11c9d5f84d42.png)

Запуск однопользовательского режима (Linux):
`g++ main.cpp -pthread -lsfml-graphics -lsfml-window -lsfml-system -lsfml-network -w && ./a.out`

Запуск сервера (пока работает не оч классно):
`./s.out 27900` (порт на котором работает приложение)

Запуск клиента:
`./c.out 127.0.0.1 27900 27901` (адресс и порт сервера, предпочтительный порт для ответов (опцинально))
