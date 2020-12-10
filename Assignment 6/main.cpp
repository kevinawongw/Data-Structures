#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include "MovieTree.hpp"
using namespace std;

void menu(){
	cout << "======Main Menu======" << endl;
	cout << "1. Print the inventory" << endl;
	cout << "2. Delete a movie" << endl;
	cout << "3. Quit" << endl;
}

int main (int argc, char** argv){
	MovieTree m;
	ifstream stream(argv[1]);
	string line="";
	while (getline(stream,line)){
		stringstream ss;
		ss << line;
		string sec = "";

		getline (ss,sec,',');
		int ranking = stoi(sec);
		getline (ss,sec,',');
		string title = sec;
		getline (ss,sec,',');
		int year= stoi(sec);
		getline (ss,sec,',');
		float rating = stof(sec);

		m.addMovie(ranking, title, year, rating);
	} 
	string title = "";
	string number= "";
	bool a = true;
	while (a){
		menu();
		getline (cin, number);
		switch(stoi(number)){
			case 1:
				m.printMovieInventory();
				break;
			case 2:
				cout << "Enter a movie title:" << endl;
				getline (cin,title);
				m.deleteMovie(title);
				break;
			case 3:
				cout << "Goodbye!" << endl;
				a= false;
				break;
		}
	}
}