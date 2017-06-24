#ifndef HASHTABLE_H
#define HASHTABLE_H

#include <string>
#include <vector>
#include <list>
#include <iostream>
#include "WordEntry.h"

using namespace std;

class HashTable {

    private:
        vector< list<WordEntry> > *hashTable;
        int computeHash(string);
        int size;

    public:
        HashTable(int);
        bool contains(string);
        double getAverage(string);
        WordEntry* getWordEntry(string s);
        void put(string,int);
};

#endif
