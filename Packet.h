#ifndef PACKET_H
#define PACKET_H

#include <string>

enum class PacketType { DATA, ACK };

class Packet {
public:
    int senderID;        
    int receiverID;      
    PacketType type;    
    std::string content; // content of packet

    Packet(int sender, int receiver, PacketType type, const std::string& content)
        : senderID(sender), receiverID(receiver), type(type), content(content) {}
};

#endif 
