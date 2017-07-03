#include "HashTable.h"
#include "WordEntry.h"


HashTable::HashTable(int s)
{
	size = s;
    hashTable = new vector< list<WordEntry> >(size);
}

int HashTable::computeHash(string s) {

	unsigned long hash = 0;
	for(unsigned i = 0; i < s.size(); i++){
		hash += s[i];
	}
	return hash % size;
}

void HashTable::put(string s, int score, int reviewId) {
	int hash = computeHash(s);

    for( list<WordEntry>::iterator it = hashTable->at(hash).begin(); it != hashTable->at(hash).end(); it++ ){
		if((*it).getWord() == s){
            (*it).addNewAppearance(score, reviewId);
			return;
		}
	}

	hashTable->at(hash).emplace_back(s, score, reviewId);

}

double HashTable::getAverage(const string s) {
    int hash = computeHash(s);

    for( WordEntry w : hashTable->at(hash) ){
			if(w.getWord() == s){
			return w.getAverage();
		}
	}

	return 2.0;
}

WordEntry* HashTable::getWordEntry(const string s) {
    int hash = computeHash(s);

    for( list<WordEntry>::iterator it = hashTable->at(hash).begin(); it != hashTable->at(hash).end(); it++ ){
		if((*it).getWord() == s){
			return &(*it);
		}
	}
	return nullptr;
}

bool HashTable::contains(const string s) {

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
