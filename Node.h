#ifndef NODE_H
#define NODE_H

#include <iostream>
#include <thread>
#include "Queue.h"
#include "Packet.h"

class Node {
private:
    int id;                 // Node identification
    Queue& messageQueue;    // Queue reference
    bool isRunning;         // Node status

public:
    Node(int nodeID, Queue& queue)
        : id(nodeID), messageQueue(queue), isRunning(true) {}

    void sendPacket(int receiverID, const std::string& content) {
        Packet pkt(id, receiverID, PacketType::DATA, content);
        messageQueue.enqueue(pkt);
        std::cout << "Node " << id << " sent: " << content << " to Node " << receiverID << std::endl;
    }

    
    void receivePacket() {
        while (isRunning) {
            Packet pkt = messageQueue.dequeue();
            if (pkt.receiverID == id) {
                std::cout << "Node " << id << " received: " << pkt.content << std::endl;
            }
        }
    }
    void stop() {
        isRunning = false;
    }
    void start() {
        std::thread receiveThread(&Node::receivePacket, this);
        receiveThread.detach();
    }
};

#endif 
