****************************************************************/
/*                   Assignment 3 Driver File                   */
/****************************************************************/
/* TODO: Implement menu options as described in the writeup     */
/****************************************************************/

#include "CountryNetwork.hpp"
#include <string>
#include <iostream>
// you may include more libraries as needed

using namespace std;

void displayMenu();

int main(int argc, char* argv[])
{
    bool a=true;
    CountryNetwork c;
    string number;
    string country, message, receiver, newcountry;
    while (a) {
        displayMenu();
        getline(cin,number);
        switch (stoi(number)) {
            case 1:
                c.loadDefaultSetup();
                c.printPath();
                break;
            case 2:
                c.printPath();
                break;
            case 3:
            cout << "Enter name of the country to receive the message:"<<endl;
                getline(cin, receiver);
            cout << "Enter the message to send:" << endl << endl; 
                getline(cin,message);
                c.transmitMsg(receiver,message);
                break;
            case 4:
                cout << "Enter a new country name:"<< endl;
                getline(cin,newcountry);
                cout << "Enter the previous country name (or First):"<<endl;
                getline(cin,country);
                while (c.searchNetwork(country) == NULL && country!= "First"){
                    cout << "INVALID country...Please enter a VALID previous country name:" << endl;
                    getline(cin,country);
                    //if (country=="First"){
                        //c.insertCountry(NULL,newcountry);
                        //break;
                    //}
                    
                }
                c.insertCountry(c.searchNetwork(country),newcountry);
                c.printPath();
                break;
            case 5:
                cout << "Enter a country name:" << endl;
                getline(cin,country);
                c.deleteCountry(country);
                c.printPath();

                break;
            case 6:
                c.reverseEntireNetwork();
                c.printPath();
                break;
            case 7:
                c.deleteEntireNetwork();
                break;
            case 8:
                cout << "Quitting... cleaning up path: " << endl;
                c.printPath();
                if(c.isEmpty()==false){
                    c.deleteEntireNetwork();
                }
                if (c.isEmpty()==true){
                    cout << "Path cleaned" << endl;  
                }
                else{
                    cout << "Error: Path NOT cleaned" << endl;
                }
                cout << "Goodbye!" << endl;
                a=false;
                break;    
        }  
    }
    return 0; 
}


/*
 * Purpose: displays a menu with options
 */
void displayMenu()
{
    cout << "Select a numerical option:" << endl;
    cout << "+=====Main Menu=========+" << endl;
    cout << " 1. Build Network " << endl;
    cout << " 2. Print Network Path " << endl;
    cout << " 3. Transmit Message " << endl;
    cout << " 4. Add Country " << endl;
    cout << " 5. Delete Country " << endl;
    cout << " 6. Reverse Network" << endl;
    cout << " 7. Clear Network " << endl;
    cout << " 8. Quit " << endl;
    cout << "+-----------------------+" << endl;
    cout << "#> ";
}