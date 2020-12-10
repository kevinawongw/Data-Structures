#include <iostream>
#include <string>
#include <vector>
#include <iomanip>
#include <fstream>
#include <sstream>

#include "HashTable.hpp"

using namespace std;

void HashTable::printTopN(int n)
{
    wordItem *whale[numItems];
    int c = 0;
    for (int l = 0; l < hashTableSize; l++)
    {
        wordItem *dehh = hashTable[l];
        while (dehh != NULL)
        {
            whale[c] = dehh;
            dehh = dehh->next;
            c++;
        }
    }

    cout << c << endl;

    for (int i = 0; i < numItems; i++)
    {
        if (whale[i] == NULL)
        {
            //cout << i << endl;
            continue;
        }

        for (int k = i; k != 0; k--)
        {
            if (whale[k - 1]->count < whale[k]->count)
            {
                wordItem *word = whale[k];
                whale[k] = whale[k - 1];
                whale[k - 1] = word;
            }
        }
    }
    cout << "deh" << endl;
    for (int i = 0; i < n; i++)
    {
        cout << fixed << setprecision(4) << ((float)whale[i]->count / (float)getTotalNumWords()) << " - " << whale[i]->word << endl;
    }
}

HashTable::HashTable(int hashTableSize)
{
    hashTable = new wordItem *[hashTableSize];
    for (int i = 0; i < hashTableSize; i++)
    {
        hashTable[i] = NULL;
    }
    this->hashTableSize = hashTableSize;
    numItems = 0;
    numCollisions = 0;
}

HashTable::~HashTable()
{
    for (int i = 0; i < hashTableSize; i++)
    {
        wordItem *dehh = hashTable[i];
        while (dehh != NULL)
        {
            wordItem *whaleDeh = dehh;
            dehh = dehh->next;
            delete whaleDeh;
        }
    }
    delete hashTable;
}

wordItem *createNode(string word, wordItem *next)
{
    wordItem *a = new wordItem;
    a->word = word;
    a->next = next;
    a->count = 1;
    return a;
}

void HashTable::addWord(string word)
{
    if (!searchTable(word))
    {
        int index = getHash(word);
        if (hashTable[index] == NULL)
        {
            wordItem *whale = createNode(word, NULL);
            hashTable[index] = whale;
            numItems++;
        }
        else
        {
            wordItem *whale = createNode(word, hashTable[index]);
            hashTable[index] = whale;
            numItems++;
            numCollisions++;
        }
    }
    else
    {
        int index = getHash(word);
        hashTable[index]->count++;
    }
}

bool HashTable::isInTable(std::string word)
{
    int index = getHash(word);
    wordItem *a = hashTable[index];
    while (a != NULL)
    {
        if (a->word == word)
        {
            return true;
        }
        a = a->next;
    }
    return false;
}

void HashTable::incrementCount(std::string word)
{
    wordItem *whale = searchTable(word);
    whale->count++;
}

bool compare(wordItem *whale, wordItem *seal)
{

    return whale->count > seal->count;
}

void sortArray(wordItem *whale[], int size)
{
}

int HashTable::getNumCollisions()
{
    return numCollisions;
}

int HashTable::getNumItems()
{
    return numItems;
}

int HashTable::getTotalNumWords()
{
    int number = 0;
    for (int i = 0; i < hashTableSize; i++)
    {
        wordItem *dehh = hashTable[i];
        while (dehh != NULL)
        {
            number += dehh->count;
            dehh = dehh->next;
        }
    }
    return number;
}

void getStopWords(char *ignoreWordFileName, HashTable &stopWordsTable)
{
    string line;
    int count = 0;
    ifstream file(ignoreWordFileName);
    if (file.is_open())
    {
        while (getline(file, line))
        {
            stopWordsTable.addWord(line);
            count++;
        }
    }
    else
    {
        cout << "Failed to open " << ignoreWordFileName << endl;
    }
}

unsigned int HashTable::getHash(string word)
{
    unsigned int hashValue = 5381;
    int length = word.length();
    for (int i = 0; i < length; i++)
    {
        hashValue = ((hashValue << 5) + hashValue) + word[i];
    }
    hashValue %= hashTableSize;
    return hashValue;
}

wordItem *HashTable::searchTable(string word)
{
    int index = getHash(word);
    wordItem *a = hashTable[index];
    while (a != NULL)
    {
        if (a->word == word)
        {
            return a;
        }
         a = a->next;
    }
    return NULL;
}

bool isStopWord(string word, HashTable &a)
{
    return a.isInTable(word);
}