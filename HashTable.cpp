#include "HashTable.h"
#include "WordEntry.h"

/* HashTable constructor
*  input s is the size of the array
*  set s to be size
*  initialize array of lists of WordEntry
*/
HashTable::HashTable (int s)
{
	size = s;
    hashTable = new vector< list<WordEntry> >(size);
}


/* computeHash
*  return an integer based on the input string
*  used for index into the array in hash table
*  be sure to use the size of the array to
*  ensure array index doesn't go out of bounds
*/
int HashTable::computeHash(string s) {

	unsigned long hash = 0;
	for(unsigned i = 0; i < s.size(); i++){
		hash += s[i];
	}
	return hash % size;
}


/* put
*  input: string word and int score to be inserted
*  First, look to see if word already exists in hash table
*   if so, addNewAppearence with the score to the WordEntry
*   if not, create a new Entry and push it on the list at the
*   appropriate array index
*/
void HashTable::put(string s, int score) {
	int hash = computeHash(s);

    for( list<WordEntry>::iterator it = hashTable->at(hash).begin(); it != hashTable->at(hash).end(); it++ ){
		if((*it).getWord() == s){
            (*it).addNewAppearance(score);
			return;
		}
	}

	hashTable->at(hash).emplace_back(s,score);

}

/* getAverage
*  input: string word
*  output: the result of a call to getAverage()
*          from the WordEntry
*  Must first find the WordEntry in the hash table
*  then return the average
*  If not found, return the value 2.0 (neutral result)
*/

double HashTable::getAverage(string s) {
    int hash = computeHash(s);

    for( WordEntry w : hashTable->at(hash) ){
		if(w.getWord() == s){
			return w.getAverage();
		}
	}

	return 2.0;
}

WordEntry* HashTable::getWordEntry(string s) {
    int hash = computeHash(s);

    for( list<WordEntry>::iterator it = hashTable->at(hash).begin(); it != hashTable->at(hash).end(); it++ ){
		if((*it).getWord() == s){
			return &(*it);
		}
	}
	return nullptr;
}

/* contains
* input: string word
* output: true if word is in the hash table
*         false if word is not in the hash table
*/
bool HashTable::contains(string s) {

     int hash = computeHash(s);
	 if( !hashTable->at(hash).empty() ){
        for( WordEntry w : hashTable->at(hash) ){
            if(w.getWord() == s){
                return true;
            }
        }
	 }
     return false;
}

