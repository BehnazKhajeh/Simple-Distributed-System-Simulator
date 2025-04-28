#include <iostream>
#include <thread>
#include <vector>
#include "Node.h"
#include "Queue.h"

int main() {
    // Queue for collaborating between nodes
    Queue queue;

    // create nodesا
    Node node1(1, queue);
    Node node2(2, queue);
    Node node3(3, queue);

    // Node begins at one thread 
    node1.start();
    node2.start();
    node3.start();

    // Send pockets to nodes
    node1.sendPacket(2, "can you hear me? (from Node 1)");
    node2.sendPacket(3, "Hello there! (from Node 2)");
    node3.sendPacket(1, "Hi (from Node 3)");

    // wait 3ms to recieve pockets
    std::this_thread::sleep_for(std::chrono::seconds(3));

    // stop nodes
    node1.stop();
    node2.stop();
    node3.stop();

    return 0;
}
