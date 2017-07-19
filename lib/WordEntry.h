#ifndef WORDENTRY_H
#define WORDENTRY_H

#include <string>
#include <vector>
#include <list>
#include <iostream>

using namespace std;

class WordEntry {

    private:
        string word;
        int numAppearances;
        int totalScore;
        list<int> reviewsId;

    public:

        /*
        *   Constructor
        *   @param string The word
        *   @param int The initial score of the word
        */
        WordEntry(string, int, int);

        /*
        *   Add new appearance to the word
        *   @param int Score to be added
        */
        void addNewAppearance(int score, int reviewId);

        /*
        *   Gets the word
        *   @return word
        */
        string getWord();

        /*
        *   Gets the average rating of the word
        *   @return the total score divided by the num of appearances
        */
        double getAverage();

        /*
        *   Gets the num of appearances
        *   @return word
        */
        int getNumAppearances();

        /*
        *   Gets the total score
        *   @return total score
        */
        int getTotalScore();

        /*
        *  Returns a reference to the list of reviewIds
        */
        list<int>& getReviewIds();
};
#endif
