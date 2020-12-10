#ifndef PRIORITYQUEUE_HPP
#define PRIORITYQUEUE_HPP

#include <string>
#include <cstring>

// a struct to store customers group information
struct GroupNode
{
  std::string groupName;
  int groupSize;
  int cookingTime;
};


class PriorityQueue
{
    public:

    //Purpose: perform all operations necessary to instantiate a class object
    PriorityQueue(int queueSize);

    // Purpose: free all resources that the object has acquired
    ~PriorityQueue();

    // Purpose: enqueue new group into priority queue; call other
    void enqueue (std::string _groupName, int _groupSize, int _cookingTime);

    //Purpose: remove the group (allocate the table) at the front of the priority queue from
    void dequeue();

    // return: groupID of the group at the front of the priority queue
    GroupNode peek();

    //return: true if queue is full, false otherwise
    bool isFull();

    // return: true if queue is empty, false otherwise
    bool isEmpty();

    private:
    //Purpose: maintain heap properties by swapping node with parent if necessary
    void repairUpward(int nodeIndex);

    // Purpose: maintain heap properties by swapping node with child if necessary
    void repairDownward(int nodeIndex);

    GroupNode* priorityQueue; //pointer to the array used to implement priority queue
    int currentQueueSize; //number of group currently in the priority queue
    int maxQueueSize; //maximum capacity of priority queue
};

#endif