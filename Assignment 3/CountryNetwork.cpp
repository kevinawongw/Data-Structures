/****************************************************************/
/*                CountryNetwork Implementation                 */
/****************************************************************/
/* TODO: Implement the member functions of class CountryNetwork */
/*     This class uses a linked-list of Country structs to      */
/*     represet communication paths between nations             */
/****************************************************************/

#include "CountryNetwork.hpp"
#include <string>

using namespace std;

/*
 * Purpose: Constructer for empty linked list
 * @param none
 * @return none
 */
CountryNetwork::CountryNetwork()
{
	head =NULL;
}


/*
 * Purpose: Check if list is empty
 * @return true if empty; else false
 */
bool CountryNetwork::isEmpty()
{
	if (head==NULL){
		return true;
	}
	else{
		return false;
	}
}


/*
 * Purpose: Add a new Country to the network
 *   between the Country *previous and the Country that follows it in the network.
 * @param previous name of the Country that comes before the new Country
 * @param countryName name of the new Country
 * @return none
 */
void CountryNetwork::insertCountry(Country* previous, string countryName)
{
	if (head==NULL){
		//add country to the beginning of the list
		Country *temp = new Country;
		temp ->name = countryName;
		temp->next=NULL;
		head = temp;
		cout << "adding: " << countryName << " (HEAD)" << endl;
	}
	else if(previous==NULL){
	    Country *temp = new Country;
		temp ->name = countryName;
		temp->next=head;
		head = temp;
		cout << "adding: " << countryName << " (HEAD)" << endl;
	}
	else{
		//Add after the previous country
		Country *temp = new Country;
		temp -> name = countryName;
		temp -> next= previous->next;
		cout << "adding: " << countryName << " (prev: " << previous->name <<
")" << endl;
		previous->next=temp;
	}
}

/*
 * Purpose: delete the country in the network with the specified name.
 * @param countryName name of the country to delete in the network
 * @return none
 */
void CountryNetwork::deleteCountry(string countryName)
{
    bool exists=false;
	if (head==NULL){
		cout << "Network is empty." << endl;
	}
	else if (head->name==countryName){
	    Country*a = head->next;
	    delete head;
	    head=a;
	}
	else{
		Country *temp =head;
		Country *two = NULL;
		while (temp!=NULL){
        	if (temp->name==countryName){
        	    two->next=temp->next;
        		delete temp;
        		exists=true;
        		break;
        	}	
        two=temp;	
        temp=temp->next;	
    	}	
		if (exists==false){
		    cout << "Country does not exist. " << endl;
		}
	}	
	
}




/*
 * Purpose: populates the network with the predetermined countries
 * @param none
 * @return none
 */
void CountryNetwork::loadDefaultSetup()
{

	if(head != NULL)
    cout << "HI WHALE I LOVE YOU" <<endl;

    	// deleteEntireNetwork();

    head = new Country;
    head->name="United States";
	Country* a= new Country;
	 a-> name = "Canada";
	Country* b= new Country;
	 b-> name = "Brazil";
	Country* c= new Country;
	 c-> name = "India";
	Country* d= new Country;
	 d-> name = "China";
	Country* e= new Country;
	 e-> name= "Australia";
	 
	 head->next=a;
	 a->next=b;
	 b->next=c;
	 c->next=d;
	 d->next=e;
	 e->next=NULL;
	 
	 
	//call deleteEntireNetwork
	//call insertCountry to add ("United States", "Canada", "Brazil", "India", "China", "Austraila")
	cout << "adding: United States (HEAD) \nadding: Canada (prev: United States) \nadding: Brazil (prev: Canada) \nadding: India (prev: Brazil) \nadding: China (prev: India) \nadding: Australia (prev: China) \n";
}

/*
 * Purpose: Search the network for the specified country and return a pointer to that node
 * @param countryName name of the country to look for in network
 * @return pointer to node of countryName, or NULL if not found
 * @see insertCountry, deletecountry
 */
Country* CountryNetwork::searchNetwork(string countryName)
{
    if (head==NULL){
        return NULL;
    }
    else{    
        Country*temp=head;
        while (temp!=NULL){
            if (temp->name==countryName){
                return temp; 
            }
            temp=temp->next;
        }
    return NULL;    
    }    
}

/*
 * Purpose: deletes all countries in the network starting at the head country.
 * @param none
 * @return none
 */
void CountryNetwork::deleteEntireNetwork()
{
	Country* temp=head;
    while (temp!=NULL){
        cout << "deleting: " << temp->name << endl;
        deleteCountry(temp->name);
        temp=temp->next;
        
    }
    head=NULL;
	
	//When the entire list is deleted 
    cout << "Deleted network" << endl;	


}


/*
 * Purpose: Transmit a message across the network to the
 *   receiver. Msg should be stored in each country it arrives
 *   at, and should increment that country's count.
 * @param receiver name of the country to receive the message
 * @param message the message to send to the receiver
 * @return none
 */
void CountryNetwork::transmitMsg(string receiver, string message)
{
    if (head==NULL){
        cout <<"Empty List" << endl;
        return;
    }
    else{
        Country*temp=head;
        if (head->name==receiver){
            head->numberMessages++;
            head->message=message;
            cout << head->name << " [# messages received: " <<
                head->numberMessages << "] received: " << head->message << endl;  
        }
        else{
            while(temp->name!=receiver){
                temp->numberMessages++;
                temp->message=message;
                cout << temp->name << " [# messages received: " <<
                temp->numberMessages << "] received: " << temp->message << endl;
        
                temp=temp->next; 
            }    
            if (temp->name==receiver){
                temp->numberMessages++;
                temp->message=message;
                cout << temp->name << " [# messages received: " <<
                temp->numberMessages << "] received: " << temp->message << endl << endl;
        
            }
        }
    }    
}


/*
 * Purpose: prints the current list nicely
 * @param ptr head of list
 */
void CountryNetwork::printPath()
{
	cout << "== CURRENT PATH ==" << endl;
	if(head==NULL){
		cout << "nothing in path"<< endl;
	}
	else{
		Country* temp=head;
	    while (temp!=NULL){
	    	cout << temp->name << " -> ";
	    	temp=temp->next;
	    }
	    cout << "NULL\n";
	} 
	cout<< "===" << endl ; 	
}


/*
 * Purpose: reverse the entire network t
 * @param ptr head of list
 */
void CountryNetwork::reverseEntireNetwork()
{
    if(head==NULL){
        return;
    }
    else {
    	Country* previous=NULL;;
    	Country* current=head;
    	Country* following=head->next;
    
    	while (current!=NULL){
           following=current->next;
           current->next=previous;
           previous=current;
           current=following;
    	}
    	head=previous;
    }	
}