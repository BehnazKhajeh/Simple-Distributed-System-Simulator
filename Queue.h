#ifndef QUEUE_H
#define QUEUE_H

#include <queue>
#include <mutex>
#include <condition_variable>
#include "Packet.h"

class Queue {
private:
    std::queue<Packet> queue;             // save packets
    std::mutex mtx;                       // Locking to synchronize sending or receiving packets
    std::condition_variable cv;          
public:
    // add packet
    void enqueue(const Packet& pkt) {
        std::lock_guard<std::mutex> lock(mtx);  
        queue.push(pkt);
        cv.notify_one();  // notification for new packet
    }

    // recieve packet
    Packet dequeue() {
        std::unique_lock<std::mutex> lock(mtx);
        cv.wait(lock, [this](){ return !queue.empty(); });  
        Packet pkt = queue.front();
        queue.pop();
        return pkt;
    }

    bool isEmpty() {
        std::lock_guard<std::mutex> lock(mtx);
        return queue.empty();
    }
};

#endif 
