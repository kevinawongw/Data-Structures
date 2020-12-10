#include <iostream>
#include<iomanip>
#include "MovieTree.hpp"
using namespace std;

MovieTree::MovieTree(){
    root=NULL;
}

MovieTree::~MovieTree(){
    free(root);
}

MovieNode* MovieTree:: search(string title){
    MovieNode*a=root;
    if (a == NULL){
        return NULL;
    }
    search(a->leftChild->title);
    if (a->leftChild->title==title){
        return a->leftChild;
    }
    search(a->rightChild->title);
    if (a->rightChild->title==title){
        return a->rightChild;
    }
}

void print (MovieNode* whale){
    if (whale!=NULL){
        print (whale->leftChild);
        cout << "Movie: " << whale->title << " " << whale->rating << endl;
        print (whale->rightChild);
    }    
}
void MovieTree::printMovieInventory()
{
    if (root==NULL){
        return;
    }
    else{
        print(root);
    }
}    

void MovieTree:: addMovieNode (int ranking, std::string title, int year, float rating){
    if (root==NULL){
        root=new MovieNode(ranking,title,year,rating);
        return;
    }
    MovieNode*a=root;
    while (true){
        if (title<a->title){
            if (a->leftChild==NULL){
                a->leftChild=new MovieNode(ranking,title,year,rating);
                break;
            }
            else{
                a=a->leftChild;
            }
        }
        else{
            if (a->rightChild==NULL){
                a->rightChild=new MovieNode(ranking,title,year,rating);
                break;
            }
            else{
                a=a->rightChild;
            }
        }
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


void MovieTree:: findMovie(string title){
    MovieNode* node= find (root,title);
    if (node!=NULL){
        cout << "Movie Info:" << endl;
        cout << "==================" << endl;
        cout << "Ranking:" << node->ranking << endl;
        cout << "Title  :" << node->title << endl;
        cout << "Year   :" << node->year << endl;
        cout << "rating :" << node->rating << endl;
    }
    else{
        cout<<"Movie not found." << endl;
    }
}

void printpre(MovieNode* m,float rating, int year){
    if (m==NULL){
        return;
    }
    if (m->rating>=rating && m->year>=year){
        cout << m->title << "(" << m->year << ") " << m->rating << endl;
    }
    printpre(m->leftChild,rating,year);
    printpre(m->rightChild,rating,year);
}   

void MovieTree:: queryMovies(float rating, int year){
    cout << "Movies that came out after " << year << " with rating at least " << rating << ":" << endl;
    if (root!=NULL){    
        printpre(root,rating,year);
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

void MovieTree :: averageRating(){
    if (root==NULL){
        cout << "Average rating:0" << endl;
    }    
    else{
        float avg=averageTotal(root)/count;
        cout << "Average rating:" << setprecision (6) <<avg << endl;
        }
    }

