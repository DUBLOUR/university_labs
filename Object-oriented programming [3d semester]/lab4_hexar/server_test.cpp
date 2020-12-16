#include <bits/stdc++.h>
#include <SFML/Network.hpp>
using namespace std;
using namespace sf;

struct MyMovePack {
    sf::Uint8 id;
    double x,y;

    MyMovePack(int _id=0, double _x=0, double _y=0) {
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

    sf::IpAddress senderAddress = "127.0.0.1";
    unsigned short senderPort = 54500;
    sf::UdpSocket socket;

    
    while (true) {
        sf::Packet packet;
        MyMovePack p;
        if (socket.receive(packet, senderAddress, senderPort) == sf::Socket::Done) {
            packet >> p;
            cout << ">>> " << p.id << ' ' << p.x << ' ' << p.y << '\n';
        } 
        
        sf::sleep(sf::milliseconds(50));
        
    }
    
    
}