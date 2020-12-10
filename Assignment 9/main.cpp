#include <string>
#include <fstream>
#include <iostream>
#include <sstream>
#include "Graph.hpp"
#include<stdio.h> 
#include<stdlib.h> 

using namespace std;

int main(int argc, char** argv){
	Graph g;
	string cities [50];
	string city="";
	int cityCount=0;
	int distance=0;
	int k=0;
	int number=0;
	int count=0;
	ifstream stream (argv[1]);
	string line="";
	while (getline(stream,line)){
		number=0;
		stringstream ss;
		ss<<line;
		string section="";
		if (k==0){
			while (getline (ss,section,',')){
				city=section;
				if (city!="cities"){
					g.addVertex(city);
					cities[count]=city;
					count++;
					cityCount=0;
			}
				k++;
			}
		}	
		else{
			city=cities[cityCount];
			while (getline (ss,section,',')){
				if(isdigit(section[1]) || section == "-1"){
					distance=stoi(section);
					if (distance>0){
		                if (number!=0){
    					    g.addEdge(city,cities[number-1],distance);
    						cout << " ... Reading in " << city << " -- " << cities[number-1] << " -- " << distance << endl;
    					}	
					}
	
				}
				number++;
			}
		cityCount++;	
		}
	}	
	cout << "------------------------------ " << endl;
	cout << "Breadth First Traversal" << endl;
	cout << "------------------------------" << endl;
	g.printBFT();
	cout << "------------------------------ " << endl;
	cout << "Depth First Traversal" << endl;
	cout << "------------------------------"<< endl;
	g.printDFT();
	cout << "------------------------------ " << endl;
	cout << "Display Edges" << endl;
	cout << "------------------------------"<< endl;
	g.displayEdges();
}

