#ifndef EMOTIONDETECTOR_H
#define EMOTIONDETECTOR_H

#include <vector>
#include "HashTable.h"
#include "WordEntry.h"

using namespace std;

/*
*   Core Class
*
*/
class EmotionDetector{

    private:
        HashTable *hashTable;
        vector< pair< string, int > > frases;
        vector< WordEntry* > heap;

        /*
        *   Read dataBase of reviews and insert in the hashTable
        */
        void fileReader(string);
        /*
        *   Builds HeapTreeMAX by rating
        */

        void buildHeapMAX();

        /*
        *   Builds HeapTreeMIN rating
        */

        void buildHeapMIN();

        /*
        *   Executes HeapsTreeMAX's heapify
        */

        void maxHeapify(int i);

        /*
        *Executes HeapsTreeMAX's heapify
        */

        void minHeapify(int i);


    public:

        /*
        *   Constructor
        */
        EmotionDetector(string);

        /*
        *   Calculate emotion score for new reviews
        */
        void calculateReviewEmotion();

        /*
        *  Get average rating of a word
        *  @param word Word to get average rating
        *  @return The word average rating,
        *   Obs: Returns 2.0 if the word is not in the hashTable
        */
        double avgRatingWord(const string word);

        /*
        *  Print all reviews with the given word
        */
        void printAppearances(const string word);

        void printMostPositive(int k);
        void printMostNegative(int k);
        vector<string> radicalsSearch(string rad);

        void printHashTable();
        /*
        *Adds file words to memory
        */
        void addFile(string fileName);



};



#endif
