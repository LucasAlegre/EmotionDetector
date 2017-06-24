#include "WordEntry.h"

/* WordEntry contructor
* input: the string text (word) and the intial score the
*         word should be assigned to
*  note that numAppearances should be set to 1 here
*/
WordEntry::WordEntry(string text, int score) : word(text), numAppearances(1), totalScore(score)
{

}

/* addNewAppearance
* input integer that is a new score for a word that is
* already in the hash table
* function should increase total score by s
* also should increase numAppearances
*/
void WordEntry::addNewAppearance(int score)
{
	this->totalScore += score;
	this->numAppearances++;
}

/*getWord
* this accessor function is needed
* particularly in the HashTable code to get the word to be
* used for the hash value
* simple accessor function
*/
string WordEntry::getWord()
{
    return this->word;
}

/* getAverage
*  returns the average score of the word
*  based on totalScore and numAppearances
*  note that typecasting -- turning one of the integers
*  to a double will be necessary to avoid integer division
*/
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
