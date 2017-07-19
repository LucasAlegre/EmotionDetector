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
        vector< list<WordEntry> > hashTable;
        size_t size;
        unsigned long occupancy;

        /*
        *   Computes hash of a word
        */
        int computeHash(string);

    public:
        /* HashTable constructor
        *  Set s to be size
        *  Initialize array of lists of WordEntry
        *  @param int Input s is the size of the array
        */
        HashTable(int);

        /*
        *  Check if a word is in the hashTable
        *  @return True if contained, false otherwise
        */
        bool contains(const string);

        /* Get AverageScore of a word
        *  @param string Word
        *  @return The average score
        */
        double getAverage(const string);

        /*
        *  Returns a pointer to the word given
        */
        WordEntry* getWordEntry(const string s);

        /*
        *   If it is a new word, insert in the hashtable,
        *   otherwise add a new appearance to the word
        */
        bool put(WordEntry entry);

        void print();
};

#endif
