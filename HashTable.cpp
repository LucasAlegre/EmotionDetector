#include "HashTable.h"
#include "WordEntry.h"


HashTable::HashTable(int s) : hashTable(s), size(s), occupancy(0)
{
}

// x[k-1] + 7(x[k-2] + 7(x[k-3] + ... + 7(x[1] + 7x[0]) ... )
int HashTable::computeHash(string s) {

    const int alfa = 7;
	unsigned long hash = 0;
	unsigned i;
	for(i = 0; i < s.size() - 1; i++){
		hash += s[i];
		hash *= alfa;
	}
	hash += s[i];
	return hash % size;
}

bool HashTable::put(WordEntry entry) {
	int hash = computeHash(entry.getWord());

    for( list<WordEntry>::iterator it = hashTable.at(hash).begin(); it != hashTable.at(hash).end(); it++ ){
		if((*it).getWord() == entry.getWord()){
            (*it).addNewAppearance(entry.getTotalScore(), entry.getReviewIds().front());
			return false;
		}
	}

	hashTable.at(hash).push_back(entry);
	occupancy++;
	return true;

}

double HashTable::getAverage(const string s) {
    int hash = computeHash(s);

    for( WordEntry w : hashTable.at(hash) ){
			if(w.getWord() == s){
			return w.getAverage();
		}
	}

	return 2.0;
}

WordEntry* HashTable::getWordEntry(const string s) {
    int hash = computeHash(s);

    for( list<WordEntry>::iterator it = hashTable.at(hash).begin(); it != hashTable.at(hash).end(); it++ ){
		if((*it).getWord() == s){
			return &(*it);
		}
	}
	return nullptr;
}

bool HashTable::contains(const string s) {

     int hash = computeHash(s);
	 if( !hashTable.at(hash).empty() ){
        for( WordEntry w : hashTable.at(hash) ){
            if(w.getWord() == s){
                return true;
            }
        }
	 }
     return false;
}

void HashTable::print(){
    int s = 0;
    for(unsigned i = 0; i < hashTable.size(); i++){
        cout << hashTable.at(i).size() << endl;
        s += hashTable.at(i).size();
    }
    cout << "Occupancy: " << occupancy << endl;
}
