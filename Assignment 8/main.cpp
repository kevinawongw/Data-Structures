#include <string>
#include <fstream>
#include <iostream>
#include <sstream>
#include "PriorityQueue.hpp"

using namespace std;

void printMenu(){
	cout << "============Main Menu============" << endl;
	cout << "1. Get group information from file" << endl;
	cout << "2. Add a group to Priority Queue" << endl;
	cout << "3. Show next group in the queue" << endl;
	cout << "4. Serve Next group" << endl;
	cout << "5. Serve Entire Queue" << endl;
	cout << "6. Quit" << endl;
}

int main (int argc, char** argv){
	PriorityQueue pq(stoi(argv[1]));
	bool a = true;
	int totalTime=0;
	string number="";
	string file="";
	string nameIn="";
	string groupSizeIn="";
	string timeIn="";
	//int totalCookTime += pq.peek().cookingTime;
	string lineE="";
	ifstream stream(file);
	while (a){
		printMenu();
		getline(cin,number);
		switch(stoi(number)){
			case 1:
				cout << "Enter filename: " << endl;
				getline (cin, file);
				while (getline(stream,lineE)){
					stringstream ss;
					ss << lineE;
					string section="";

					getline (ss,section,' ');
					string name=section;
					getline (ss,section,' ');
					int groupSize=stoi(section);
					getline (ss,section,' ');
					int cookingTime=stoi(section);

					if(!pq.isFull()){
						pq.enqueue(name,groupSize,cookingTime);
					}
					else{
						cout << "Heap full, cannot enqueue" << endl;
					}	
				}
				break;
			case 2:
				cout << "Enter Group Name: " <<endl ;
				getline(cin, nameIn);
				cout << "Enter Group Size: " << endl;
				getline(cin,groupSizeIn);
				cout << "Enter Estimated Cooking Time: " << endl;
				getline(cin,timeIn);

				if (!pq.isFull()){
					pq.enqueue(nameIn,stoi(groupSizeIn),stoi(timeIn));
				}
				else{
					cout << "Heap full, cannot enqueue" << endl;
				}
				break;
			case 3:
				if (pq.isEmpty()){
					cout << "Heap empty, nothing to peek" << endl;
				}
				else{
					cout << "Group Name: " << pq.peek().groupName << endl;
					cout << "Group Size: " << pq.peek().groupSize << endl;
					cout << "Group Time: " << pq.peek().cookingTime << endl;
				}

				break;
			case 4:
				if (pq.isEmpty()){
					cout << "Heap empty, cannot dequeue" << endl;
				}
				else{
					pq.dequeue();
					//TODO Define totalCookTime 
					cout << "Group Name: " << pq.peek().groupName << " - Total Cook Time for the Group: "<< pq.peek().cookingTime << endl;
				}
				break;
			case 5:
				if (pq.isEmpty()){
					cout << "Heap empty, cannot dequeue" << endl;
				}
				else{
					while(!pq.isEmpty()){
					    totalTime+=pq.peek().cookingTime;
						cout << "Group Name: " << pq.peek().groupName << " - Total Cook Time for the Group: " << totalTime << endl;	
						pq.dequeue();
					}
				}
				break;
			case 6:
				cout << "Goodbye!" << endl;
				a=false;
				break;

		}
	}
}