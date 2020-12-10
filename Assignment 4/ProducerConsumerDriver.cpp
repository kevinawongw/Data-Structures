/****************************************************************/
/*                Producer Consumer Driver File                 */
/****************************************************************/
/* TODO: Implement menu options as described in the writeup     */
/****************************************************************/


#include "ProducerConsumer.hpp"
#include <iostream>
// you may include more libraries as needed

using namespace std;

ProducerConsumer :: ProducerConsumer(){
	queueFront=-1;
	queueEnd=-1;
}

bool ProducerConsumer:: isEmpty(){
	if(queueEnd==-1&&queueFront==-1){
		return true;
	}
	else{
		return false;
	}
}

bool ProducerConsumer:: isFull(){
	if (queueFront-1==queueEnd){
		return true;
	}
	else if(queueFront==0&&queueEnd==19){
	    return true;
	}
	else{
		return false;
	}
}

void ProducerConsumer:: enqueue(string item){
	if (!isFull()){
		queueEnd=queueEnd+1;
		if (queueFront==-1){
		    queueFront=0;   
		}
		if (queueEnd==20){
		    queueEnd=0;
		}
		queue[queueEnd]=item;
	}
	else{
		cout << "Queue full, cannot add new item" << endl;
	}
}

void ProducerConsumer:: dequeue(){
	if(queueFront==queueEnd&&queueFront!=-1){
	   queueFront=-1;
	   queueEnd=-1;
	}
	else if (!isEmpty()){
		queueFront=queueFront+1;
		if (queueFront==20){
			queueFront=0;
		}
	}	
	else{
		cout << "Queue empty, cannot dequeue an item" << endl;
    }	    
}

int ProducerConsumer:: queueSize(){
	int sizeCount=0;
	if (queueFront!=-1){
	    sizeCount=queueFront+queueEnd+1;
	}
	return sizeCount;
}

string ProducerConsumer:: peek(){
	if (isEmpty()){
		string a="";
		cout <<"Queue empty, cannot peek"<<endl;
		return a;
	}
	else{
		return queue[queueFront];
	}
}
/*
 * Purpose: displays a menu with options
 * @param none
 * @return none
 */

int main(int argc, char const *argv[])
{
    cout << "*----------------------------------------*"<<endl;
	menu();
	cout << "*----------------------------------------*"<<endl;
	bool a =true;
	string number,item;
	ProducerConsumer pro;
	string option="";
	getline (cin,option);
	while (a){
    	switch (stoi(option)){
    		case 1:
    			cout << "Enter the number of items to be produced:" << endl;
    			getline(cin,number);
    			for (int i=1;i<stoi(number)+1;i++){
    				cout << "Item" << i <<":" <<endl;
    				getline(cin,item);
    				pro.enqueue(item);
    			}
    		break;
    		case 2:	
    			cout << "Enter the number of items to be consumed:" << endl;
    			getline(cin,number);
    			if (stoi(number)>pro.queueSize()){
    				for (int i=0;i<stoi(number)-1;i++){
    					cout << "Consumed: " << pro.peek() <<endl;
    					pro.dequeue();
    				}
    				cout << "No more items to consume from queue" <<endl;
    			}
    			else{
    			    for (int i=0;i<stoi(number);i++){
    					cout << "Consumed: " << pro.peek() <<endl;
    					pro.dequeue();
    				}
                }
    		break;
    		case 3:
    		cout << "Number of items in the queue:" << pro.queueSize();
    		a=false;
    		break;
    	}
    	if (a){
            cout << "*----------------------------------------*"<<endl;
            menu();
            cout << "*----------------------------------------*"<<endl;
            getline(cin,option);
        }    
	}
}
