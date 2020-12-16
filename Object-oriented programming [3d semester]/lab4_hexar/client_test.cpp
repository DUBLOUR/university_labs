#include <bits/stdc++.h>
#include <SFML/Network.hpp>
using namespace std;
using namespace sf;

struct MyMovePack {
    sf::Uint8 id;
    double x,y;

    MyMovePack(int _id, double _x, double _y) {
        id = _id;
        x = _x;
        y = _y;   
    }
};

sf::Packet& operator <<(sf::Packet& packet, const MyMovePack& p) {
    return packet << p.id << p.x << p.y;
}

sf::Packet& operator >>(sf::Packet& packet, MyMovePack& p) {
    return packet >> p.id >> p.x >> p.y;
}




int main()
{

    sf::IpAddress recipientAddress = "127.0.0.1";
    unsigned short recipientPort = 54500;
    sf::UdpSocket socket;

    while (true) {
        int id;
        cin >> id;
        for (int i=0; i<10; ++i) {
            cout << "<<< " << i << '\n';
            MyMovePack info(id, rand(), rand());

            sf::Packet p;
            p << info;
            socket.send(p, recipientAddress, recipientPort);
            sf::sleep(sf::milliseconds(100));
        }
    }
    
    
}






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

    while (true) {
        Receive();
        Send();
    }
}