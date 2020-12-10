#include <iostream>
using namespace std;

struct node
{
    int key;
    node *next;
};

int LinkedListFindMinimim (node*head){
    int min=0;
    if (head==NULL){
        return 0;
    }
    else {
        node* temp= head;
            while (temp!=NULL){
                if (head==temp){
                    min=head->key;
                }
                else{
                    if (temp->key<min){
                        min=temp->key;
                    }    
                    else{
                        min=min;
                    }    
                }
            temp=temp->next;
            }
    }
return min;    
}


int main(){
    node* head= new node;
    head->key=5;
    node* a= new node;
    a->key=2;
    node* b= new node;
    b->key=1;
    
    head->next=a;
    a->next=b;
    b->next=NULL;
    
    cout << LinkedListFindMinimim(head);
}