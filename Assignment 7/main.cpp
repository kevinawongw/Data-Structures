#include <string>
#include <fstream>
#include <iostream>
#include <sstream>
#include "HashTable.hpp"

using namespace std;

int main(int argc, char** argv){

    HashTable h(50);
    getStopWords(argv[3],h);
    HashTable wordTablee(stoi(argv[4]));
    string word;
  
    ifstream file(argv[2]);
    string line = "";
    while(getline(file,word)){
        line += word + " ";
    }
   
    stringstream ss;
    ss<<line;
    
    while(getline(ss,word,' ')){
        if(word == ""){
            continue;
        }
        if(!isStopWord(word,h)){
            if(wordTablee.isInTable(word)){
                wordTablee.incrementCount(word);
            }
            else{
                wordTablee.addWord(word);
            }
        }
    }
    file.close();
    
    cout << "help" << endl;
    wordTablee.printTopN(stoi(argv[1]));
    cout << "#" << endl;
    cout << "Number of collisions: " << wordTablee.getNumCollisions() << endl;
    cout << "#" << endl;
    cout << "Unique non-stop words: " << wordTablee.getNumItems()<<endl;
    cout << "#" << endl;
    cout << "Total non-stop words: " << wordTablee.getTotalNumWords()<<endl;
}