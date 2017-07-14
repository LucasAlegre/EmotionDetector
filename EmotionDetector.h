#ifndef EMOTIONDETECTOR_H
#define EMOTIONDETECTOR_H

#include <vector>
#include "HashTable.h"
#include "WordEntry.h"
#include "Trie.h"

using namespace std;

/*
*   Core Class
*/
class EmotionDetector{

    private:
        HashTable hashTable; // HashTable with WordEntries
        HashTable stopWords;
        vector< pair< string, int > > frases; // All sentences read from the file
        vector< WordEntry* > heap; // Heap used to get extremes occurrences
        Trie trie; // Trie tree to find words by radicals

        int maxId; // Id of the last sentence

        /*
        *   Read dataBase of reviews and insert in the hashTable
        *   Format:
        *   <sentiment> <sentence>
        *   @param txt file
        */
        void fileReader(string);

        /*
        *   Read tsv Kaggle's file
        *   Format:
        *   PhraseId	SentenceId	Phrase	Sentiment
        *   <phraseid>	<senteceId>	 <phrase>	<sentiment>
        *   @param tsv file
        */
        void fileReaderKaggle(string);

        /*
        *  Generate hashTable of stopWords from the file
        */
        void readStopWordsFile(string);

        /*
        *   Builds HeapTreeMAX by rating
        */
        void buildHeapMAXbyRating();

        /*
        *   Builds HeapTreeMIN rating
        */

        void buildHeapMINbyRating();

        /*
        *   Executes HeapsTreeMAX's heapify
        */

        void maxHeapifyByRating(int i);

        /*
        * Executes HeapsTreeMAX's heapify
        */
        void minHeapifyByRating(int i);

                /*
        *   Builds HeapTreeMAX by rating
        */
        void buildHeapMAXbyAppearances();

        /*
        *   Builds HeapTreeMIN rating
        */

        void buildHeapMINbyAppearances();

        /*
        *   Executes HeapsTreeMAX's heapify
        */

        void maxHeapifyByAppearances(int i);

        /*
        * Executes HeapsTreeMAX's heapify
        */
        void minHeapifyByAppearances(int i);


    public:

        /*
        *   Constructor
        *   @param string The file with the reviews
        *   @param 0 - txt 1 - tsv
        */
        EmotionDetector(string, int);

        /*
        *   Calculate emotion score for new reviews
        */
        void calculateReviewEmotion(string message);

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

        /*
        *   Generate a .cvs file with all reviews of the word given
        *   with rating in the interval [min, max]
        *   @param word Word that will be searched
        *   @param min Lowest rating of the interval
        *   @param max Biggest rating of the interval
        */
        void generateCVS(const string word, double min, double max);

        /*
        *  Prints the K most positive words
        */
        void printMostPositive(int k);

        /*
        *  Prints the K most negative words
        */
        void printMostNegative(int k);

        /*
        *  Prints the K words with more appearances
        */
        void printMostAppearances(int k);

        /*
        *  Prints the K words with less appearances
        */
        void printLessAppearances(int k);

        /*
        *   Prints all the words with the radical given
        *   @param rad Radical
        */
        void radicalsSearch(string rad);

        /*
        *  Adds file words to memory
        */
        void addFile(string fileName);

        /*
        *  Given a .txt with new Movie Reviews,
        *  generates a new .txt with the rating of each review.
        *  @param file File with new reviews
        */
        void calculateReviewsFromFile(string fileName);

        /*
        *  Given a .tsv with new Movie Reviews,
        *  generates a new .csv with the rating of each review.
        *  @param file File with new reviews
        */
        void calculateReviewsFromFileKaggle(string fileName);

        void printHashTable();

};



#endif
