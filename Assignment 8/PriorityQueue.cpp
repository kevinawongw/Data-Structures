#include<iostream>
#include <string>
#include <cstring>
#include "PriorityQueue.hpp"

using namespace std;

//Public Functions/////////////////////////////////////////////////////////////////////////////////

//Constructor
PriorityQueue::PriorityQueue(int queueSize){
	maxQueueSize=queueSize;
	currentQueueSize=0;
	priorityQueue=new GroupNode[queueSize];
	for (int i=0;i<queueSize;i++){
		priorityQueue[i].groupName="";
		priorityQueue[i].groupSize=0;
		priorityQueue[i].cookingTime=0;
	}
}

//Destructor
PriorityQueue::~PriorityQueue(){
    for (int i=0;i<currentQueueSize;i++){
        dequeue();
    }
     delete []priorityQueue;
}

int parent (int index){
    return (index-1)/2;
}

void swap(GroupNode* a, GroupNode* b){
	GroupNode temp = *a;
	*a=*b;
	*b = temp;
}

//Enqueue

void PriorityQueue::enqueue(string _groupName, int _groupSize, int _cookingTime){
	if (currentQueueSize==maxQueueSize){
		cout << "Heap full, cannot enqueue" << endl;
		return;
	}
	currentQueueSize=currentQueueSize + 1 ;
	int i = currentQueueSize -1;
	priorityQueue[i].groupName=_groupName;
	priorityQueue[i].groupSize=_groupSize;
	priorityQueue[i].cookingTime=_cookingTime;	
	
	while (i!=0 && priorityQueue[parent(i)].groupSize >= priorityQueue[i].groupSize){
	    swap (&priorityQueue[i], &priorityQueue[parent(i)]);
	    if (priorityQueue[parent(i)].groupSize==priorityQueue[i].groupSize){
	        if (priorityQueue[parent(i)].cookingTime > priorityQueue[i].cookingTime){
	            swap (&priorityQueue[i], &priorityQueue[parent(i)]);
	        }
	    }
	    i=parent(i);
	}
}

//Deqeue
void PriorityQueue::dequeue(){
	if (isEmpty()){
		cout << "Heap Empty, cannot dequeue" << endl;
		return;
	}
	priorityQueue[0]=priorityQueue[currentQueueSize-1];
	currentQueueSize--;
	
	repairDownward(0);
}

//Peek
GroupNode PriorityQueue::peek(){
	if (isEmpty()){
		cout << "Heap empty, nothing to peek" << endl;
	}
	return priorityQueue[0];
}

//IsFull
bool PriorityQueue::isFull(){
	if (currentQueueSize==maxQueueSize){
		return true;
	}
	else{
		return false;
	}

}

//IsEmpty
bool PriorityQueue::isEmpty(){
	if (currentQueueSize==0){
		return true;
	}
	else{
		return false;
	}
}

//Private Functions ///////////////////////////////////////////////////////////////////////////////

void PriorityQueue::repairUpward(int nodeIndex){
	while (nodeIndex!=1){
		if (priorityQueue[nodeIndex].groupSize == priorityQueue[parent(nodeIndex)].groupSize){
			if (priorityQueue[nodeIndex].cookingTime > priorityQueue[parent(nodeIndex)].cookingTime){
				swap(&priorityQueue[nodeIndex],&priorityQueue[parent(nodeIndex)]);
				nodeIndex=parent(nodeIndex);
				repairUpward(nodeIndex);	
			}	
		}
		else if (priorityQueue[nodeIndex].groupSize > priorityQueue[parent(nodeIndex)].groupSize){
			swap(&priorityQueue[parent(nodeIndex)],&priorityQueue[nodeIndex]);
			nodeIndex=parent(nodeIndex);
			repairUpward(parent(nodeIndex));
		}	
		else{
			nodeIndex=parent(nodeIndex);
		}
	}	
}

int left (int index){
    return ((2*index)+1);
}

int right (int index){
    return ((2*index)+2);
}

void PriorityQueue::repairDownward (int nodeIndex){
    int l=left(nodeIndex);
    int r=right(nodeIndex);
    int smallest=nodeIndex;
    
    if (l<currentQueueSize && priorityQueue[l].groupSize < priorityQueue[nodeIndex].groupSize){
        smallest=l;
    }
    else if (l<currentQueueSize && priorityQueue[l].groupSize==priorityQueue[nodeIndex].groupSize){
        if (l<currentQueueSize && priorityQueue[l].cookingTime < priorityQueue[smallest].cookingTime){
            smallest=l;
        }
    }
    if (r<currentQueueSize && priorityQueue[r].groupSize < priorityQueue[smallest].groupSize){
        smallest=r;
    }
    else if (r<currentQueueSize && priorityQueue[r].groupSize==priorityQueue[smallest].groupSize){
        if (r<currentQueueSize && priorityQueue[r].cookingTime < priorityQueue[smallest].cookingTime){
            smallest=r;
        }
    }
    
    if (smallest!=nodeIndex){
        swap(&priorityQueue[nodeIndex], &priorityQueue[smallest]);
        repairDownward(smallest);
    }
}