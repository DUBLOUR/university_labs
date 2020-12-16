#include<SFML/Network.hpp>
#include<iostream>
#include<string>
#include<thread>

using namespace std;
using namespace sf;

sf::IpAddress recipient_ip;
int recipient_port;
int listener_port;

void Send() //Функция отправитель.
{
    // while (true)
    if (1)
    {
        //Создать соккет отправителя.
        UdpSocket socket;

        char message[250]; Packet packet;

        cin.getline(message, 250); //Передать массив символов. Получатель увидит готовые строки.
        packet << message;
        socket.send(packet, recipient_ip, recipient_port);
    }
}
void Receive() //Функция получатель
{
    // while (true)
    if (1)
    {
        //Создать соккет получателя и привязать его к своему порту.
        UdpSocket socket; socket.bind(listener_port);

        // Получить от кого-нибудь сообщение.
        IpAddress sender; unsigned short port; string message; Packet packet;

        socket.receive(packet, sender, port);
        packet >> message;
        cout << ">>> " << message << endl;
    }
}
//------- Протокол Udp  ----------------+
int main(int argc, char** argv)
{
    listener_port = atoi(argv[1]); 
    recipient_ip = sf::IpAddress(argv[2]);
    recipient_port = atoi(argv[3]); 

    cout << " " << endl; cout << "-----" << endl;

    if (0) {
        thread receive(Receive); 
        thread send(Send); 

        receive.join(); 
        send.join(); 
        size_t z; std::cin >> z; return 0;
    } else
        while (true) {
            Send();
            Receive();
        }
}

/*#include<SFML/Network.hpp>
#include<iostream>
#include<string>
#include<thread>

using namespace std;
using namespace sf;

void Send() //Функция отправитель.
{
    while (true)
    {
        //Создать соккет отправителя.
        TcpSocket socket;
        //Установить связь с получателем.
        socket.connect("192.168.43.142", 2001);

        char message[250]; Packet packet;

        cin.getline(message, 250); //Передать массив символов. Получатель увидит готовые строки.
        packet << message;
        socket.send(packet);
        packet.clear();
    }
}
void Receive() //Функция получатель
{
    while (true)
    {
        //Создать соккет получателя.
        TcpSocket socket;
        //Создать соккет слушателя, присвоить ему свой порт и перейти в режим ожидания.
        TcpListener listener; listener.listen(2002);
        // Установить связь с абонентом, если он отправил запрос.
        listener.accept(socket);
        // Получить сообщение от абонента.
        string message; Packet packet;

        socket.receive(packet);
        packet >> message;
        cout << message << endl;
    }
}
//------- Протокол Tcp  ----------------+
int main()
{
    cout << "Vladimir Kuznetcov" << endl; cout << "--------------------" << endl;

    thread receive(Receive); thread send(Send);


    receive.join(); send.join();
    size_t z; std::cin >> z; return 0;
}*/