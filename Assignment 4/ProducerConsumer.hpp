/****************************************************************/
/*                    ProducerConsumer Class                    */
/****************************************************************/
/* LEAVE THIS FILE AS IS! DO NOT MODIFY ANYTHING! =]            */
/****************************************************************/

#pragma once
#include <string>

const int SIZE = 20; // max size of queue

class ProducerConsumer
{
  public:
    ProducerConsumer();
    bool isEmpty();
    bool isFull();
    
    void dequeue();
    int queueSize();
    int getQueueFront() { return queueFront; } // no need to implement this
    int getQueueEnd() { return queueEnd; } // no need to implement this
    std::string* getQueue() { return queue; } // no need to implement this
    std::string peek();

  private:
    int queueFront;             // the index in queue[] that will be dequeued next
    int queueEnd;               // the index in queue[] that was most recently enqueued
    std::string queue[SIZE];    // the queue in the form of an array
};
