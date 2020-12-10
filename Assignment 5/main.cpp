#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include "MovieTree.hpp"

using namespace std;

void print (MovieNode* whale){
    if (whale!=NULL){
        print (whale->leftChild);
        cout << "Movie: " << whale->title << " " << whale->rating << endl;
        print (whale->rightChild);
    }    
}

MovieNode* find(MovieNode* a,string titlea){
    if (a == NULL){
        return NULL;
    }
    else if (a->title==titlea){
        return a;
    }
    else{
        MovieNode* left = find(a->leftChild,titlea);
        MovieNode* right = find (a->rightChild,titlea);
        if (left!=NULL || right!=NULL){
            if (right==NULL){
                return left;
            }
            else if (left==NULL){
                return right;
            }
        }
        else{
            return NULL;
        }
    }    
}

float count=0;
float averageTotal(MovieNode*root){
    float sum=0;
    if (root==NULL){
        return 0;
    }
    else{
        sum=(root->rating+averageTotal(root->leftChild)+averageTotal(root->rightChild));
        count++;
    }
    return sum;
}



void menu(){
	cout << "======Main Menu======" << endl;
	cout << "1. Find a movie" << endl;
	cout << "2. Query movies" << endl;
	cout << "3. Print the inventory" << endl;
	cout << "4. Average Rating of movies" << endl;
	cout << "5. Quit" << endl;
}

int main(int argc, char** argv){
    MovieTree mt;
    string line="";
    ifstream doc(argv[1]);
    while (getline (doc,line)){
        stringstream ss;
        ss<<line;
        string sec="";
        getline (ss,sec,',');
        int ranking = stoi(sec);
        getline (ss,sec,',');
        string title=sec;
        getline (ss,sec,',');
        int year=stoi(sec);
        getline (ss,sec,',');
        float rating=stof(sec);
        
        mt.addMovieNode(ranking,title,year,rating);
    }
    string number="";
    string year,rating,title="";
    bool a=true;
    while (a){
        menu();
        getline (cin,number);
        switch(stoi(number)){
            case 1:
                cout << "Enter title:" << endl;
                getline (cin, title);
                mt.findMovie(title);
                break;
            case 2:
                cout << "Enter minimum rating:" << endl;
                getline (cin,rating);
                cout << "Enter minimum year:" << endl;
                getline (cin,year);
                mt.queryMovies(stof(rating),stoi(year));
                break;
            case 3:
                mt.printMovieInventory();
                break;
            case 4:
                mt.averageRating();
                break;
            case 5:
                cout << "Goodbye!" << endl;
                a=false;
                break;
        }
    }
}    