#include <iostream>
#include <iomanip>
#include <fstream>
using namespace std;

struct wordItem {
string word;
int count;
};

void getStopWords(const char *ignoreWordFileName, string ignoreWords[])
{
    string line;
    int count =0;
    ifstream file (ignoreWordFileName);
    if (file.is_open()){
    	while (getline(file,line)){
    		ignoreWords[count]=line;
    		count++;
    	}
    }
    else{
    	cout << "Failed to open " << ignoreWordFileName <<endl;
    } 
}

bool isStopWord(string word, string ignoreWords[])
{
	int count=0;
    for (int i=0;i<50;i++){
    	if (word==ignoreWords[i]){
    		count++;
    	}
    }
    if (count == 0){
    	return false;
    }
    else{
    	return true;
    }
}

int getTotalNumberNonStopWords(wordItem uniqueWords[], int length)
{
	int num=0;
    for (int i =0;i<length;i++){
        num += uniqueWords[i].count;
    }
    return num;
}

void arraySort(wordItem uniqueWords[], int length)
{
    for (int i =0;i<length;i++){
        for (int k=i;k!=0;k--){    
            if (uniqueWords[k-1].count<uniqueWords[k].count){
                wordItem word = uniqueWords[k];
                uniqueWords[k] = uniqueWords[k-1];
                uniqueWords[k-1] = word;
            }
       } 
    }
}

void printTopN(wordItem uniqueWords[], int topN, int totalNumWords)
{
    for (int i=0;i<topN;i++){
        float probability = ((float)uniqueWords[i].count)/totalNumWords;
        cout << fixed << setprecision(4)<< probability << " - " << uniqueWords[i].word << endl;
    }
}


int main(int argc, char*argv[]){
 	wordItem* uniqueWords = new wordItem [100];
 	string ignoreWords[50];

 	getStopWords(argv[3],ignoreWords);

 	int doublesize=100;
	int number=0;
	int arraydbl=0;
	string word;
	ifstream file (argv[2]);
	if (file.is_open()){
		while (getline(file,word,' ')){
			if (!isStopWord(word,ignoreWords)){
				if (number==doublesize){
					//double array
					int newsize = doublesize*2;
					wordItem* newArray = new wordItem[newsize];
					for (int i=0;i<doublesize;i++){
						newArray[i]=uniqueWords[i];
					}
					delete[] uniqueWords;
					uniqueWords=newArray;
					doublesize=doublesize*2;
					arraydbl++;
				}

				bool isAdded = false;
				for(int i = 0; i < number; i++){
					if(word == uniqueWords[i].word){
						uniqueWords[i].count++;
						isAdded = true;
					}
				}
				if(!isAdded){
					uniqueWords[number].word=word;
					uniqueWords[number].count = 1;
					number++;
				}
			}
		}
	}
	file.close();

	arraySort(uniqueWords,number);
	cout << "Array doubled: " << arraydbl << "\n#\n" << "Unique non-common words: " << number << "\n#\n" << "Total non-common words: " << getTotalNumberNonStopWords(uniqueWords,number) << "\n#\n";
	cout << "Probabilities of top " << argv[1]<< " most frequent words \n" << "---------------------------------------\n";
	printTopN(uniqueWords,stoi(argv[1]),getTotalNumberNonStopWords(uniqueWords,number));

}
