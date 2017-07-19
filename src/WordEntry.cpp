#include "WordEntry.h"

WordEntry::WordEntry(string text, int score, int reviewId) : word(text), numAppearances(1), totalScore(score)
{
    reviewsId.push_back(reviewId);
}

void WordEntry::addNewAppearance(int score, int reviewId)
{
	this->totalScore += score;
	this->numAppearances++;

	// if the word already appears in this sentence
	if( this->reviewsId.back() != reviewId )
        this->reviewsId.push_back(reviewId);
}

string WordEntry::getWord()
{
    return this->word;
}

double WordEntry::getAverage()
{
	return (double)totalScore/numAppearances;
}

int WordEntry::getTotalScore(){

    return this->totalScore;
}

int WordEntry::getNumAppearances(){

    return this->numAppearances;
}

list<int>& WordEntry::getReviewIds(){
    return reviewsId;
}
