#include "EmotionDetector.h"

#include <iostream>
#include <fstream>
#include <cstdlib>
#include <algorithm>
#include <math.h>
#include <sstream>

using namespace std;

EmotionDetector::EmotionDetector(string fileName, int fileType) : hashTable(42589), stopWords(100), maxId(0) // 4001 is a prime number!
{
    if(fileType == 0)
        fileReader(fileName);
    else if(fileType == 1)
        fileReaderKaggle(fileName);

    readStopWordsFile("stopWords.txt");
}

void EmotionDetector::readStopWordsFile(string fileName){

    //open input file
    ifstream myFile (fileName);
    if (myFile.fail())
    {
        cout << "Could not open file " << fileName << endl;
        exit(0);
    }

    int lineId = 0;

    while( !myFile.eof() ){

        string word;
        myFile >> word;

        if(word.size() > 0){
            WordEntry wordEntry(word, -1, lineId++);
            stopWords.put(wordEntry);
        }
    }


}

void EmotionDetector::fileReader(string fileName)
{
    string line;
    int score;

    //open input file
    ifstream myfile (fileName);
    if (myfile.fail())
    {
        cout << "Could not open file " << fileName << endl;
        exit(0);
    }

    int lineId = 0;

    while (! myfile.eof() )
    {
        myfile >> score;  //get score
        myfile.get();    // get blank space
        getline(myfile, line);

        this->frases.push_back( pair< string, int >(line, score) );

        transform(line.begin(), line.end(), line.begin(), ::tolower);

        int len = line.size();
        while(len > 0)    //identify all individual strings
        {
            string sub;
            len = line.find(" ");
            if (len > 0)
            {
                sub = line.substr(0, len);
                line = line.substr(len + 1,line.size());
            }
            else
            {
                sub = line.substr(0, line.size());
            }

            // Add word to Trie
            trie.addWord(sub);

            // Create word entry
            WordEntry heapInput(sub, score, lineId);

            // Insert in the hashTable, updating score if already exists
            // if is a new word, insert it in the heap
            if(hashTable.put(heapInput))
                heap.push_back(hashTable.getWordEntry(sub));   //insert string with the score
        }

        lineId++;
    }
    maxId = lineId;
    myfile.close();
}

void EmotionDetector::fileReaderKaggle(string fileName){

    string line;
    string fullLine;
    int score;
    int lixo;

    //open input file
    ifstream myfile (fileName);
    if (myfile.fail())
    {
        cout << "Could not open file " << fileName << endl;
        exit(0);
    }

    int lineId = 0;

    getline(myfile, line); // ignores header

    while (! myfile.eof() )
    {
        myfile >> lixo;  // phraseId
        myfile.get();    // get blank space
        myfile >> lixo;  // sentenceId
        myfile.get();    // get blank space
        getline(myfile, fullLine);

        line = fullLine.substr(0, fullLine.size() - 1);
        score = fullLine.at(fullLine.size() - 1) - '0';

        this->frases.push_back( pair< string, int >(line, score) );

        transform(line.begin(), line.end(), line.begin(), ::tolower);

        int len = line.size();
        while(len > 0)    //identify all individual strings
        {
            string sub;
            len = line.find(" ");
            if (len > 0)
            {
                sub = line.substr(0, len);
                line = line.substr(len + 1,line.size());
            }
            else
            {
                sub = line.substr(0, line.size());
            }

            // Add word to Trie
            trie.addWord(sub);

            // Create word entry
            WordEntry heapInput(sub, score, lineId);

            // Insert in the hashTable, updating score if already exists
            // if is a new word, insert it in the heap
            if(hashTable.put(heapInput))
                heap.push_back(hashTable.getWordEntry(sub));   //insert string with the score
        }

        lineId++;
    }
    maxId = lineId;
    myfile.close();
}


void EmotionDetector::buildHeapMAXbyRating(){
    for(int i = (heap.size()/2) - 1; i >= 0; i--){
        maxHeapifyByRating(i);
    }
}

void EmotionDetector::buildHeapMAXbyAppearances(){
    for(int i = (heap.size()/2) - 1; i >= 0; i--){
        maxHeapifyByAppearances(i);
    }
}

void EmotionDetector::buildHeapMINbyRating(){
    for(int i = (heap.size()/2) - 1; i >= 0; i--){
        minHeapifyByRating(i);
    }
}

void EmotionDetector::buildHeapMINbyAppearances(){
    for(int i = (heap.size()/2) - 1; i >= 0; i--){
        minHeapifyByAppearances(i);
    }
}

void EmotionDetector::maxHeapifyByRating(int i){

    int e = i*2 + 1;
    int d = i*2 + 2;
    int maior = i;
    int heapSize = heap.size();

    if(e < heapSize  && heap[e]->getAverage() > heap[maior]->getAverage())
        maior = e;
    if(d < heapSize  && heap[d]->getAverage() > heap[maior]->getAverage())
        maior = d;

    if(maior != i){
         swap(heap[maior], heap[i]);
         maxHeapifyByRating(maior);
    }
}

void EmotionDetector::maxHeapifyByAppearances(int i){

    int e = i*2 + 1;
    int d = i*2 + 2;
    int maior = i;
    int heapSize = heap.size();

    if(e < heapSize  && heap[e]->getNumAppearances() > heap[maior]->getNumAppearances())
        maior = e;
    if(d < heapSize  && heap[d]->getNumAppearances() > heap[maior]->getNumAppearances())
        maior = d;

    if(maior != i){
         swap(heap[maior], heap[i]);
         maxHeapifyByAppearances(maior);
    }
}

void EmotionDetector::minHeapifyByRating(int i){

    int e = i*2 + 1;
    int d = i*2 + 2;
    int menor = i;
    int heapSize = heap.size();

    if(e < heapSize  && heap[e]->getAverage() < heap[menor]->getAverage())
        menor = e;
    if(d < heapSize  && heap[d]->getAverage() < heap[menor]->getAverage())
        menor = d;

    if(menor != i){
         swap(heap[menor], heap[i]);
         minHeapifyByRating(menor);
    }
}

void EmotionDetector::minHeapifyByAppearances(int i){

    int e = i*2 + 1;
    int d = i*2 + 2;
    int menor = i;
    int heapSize = heap.size();

    if(e < heapSize  && heap[e]->getNumAppearances() < heap[menor]->getNumAppearances())
        menor = e;
    if(d < heapSize  && heap[d]->getNumAppearances() < heap[menor]->getNumAppearances())
        menor = d;

    if(menor != i){
         swap(heap[menor], heap[i]);
         minHeapifyByAppearances(menor);
    }
}


void EmotionDetector::calculateReviewEmotion(string message){

    if(message.length() > 0)
    {
        //used for calculating the average
        double sum = 0;
        int count = 0;

        // convert to lowercase
        transform(message.begin(), message.end(), message.begin(), ::tolower);

        unsigned len = message.size();
        //get each individual word from the input
        while(len != std::string::npos)
        {
            string sub;
            len = message.find(" ");
            if (len != string::npos)
            {
                sub = message.substr(0, len);
                message = message.substr(len + 1, message.size());
            }
            else
            {
                sub = message;
            }
            //calculate the score of each word
            if( !stopWords.contains(sub) ){
                sum += hashTable.getAverage(sub);
                count++;
            }
        }

        if (message.size() > 0)
        {
            cout << "The review has an average value of ";
            if(count != 0)
                cout << (double)sum/count << endl;
            else
                cout << 2 << endl;
        }
    }

}

double EmotionDetector::avgRatingWord(const string word){
    return this->hashTable.getAverage(word);
}

void EmotionDetector::printAppearances(const string word){

    WordEntry *w = hashTable.getWordEntry(word);
    if(w != nullptr){
        cout << "Reviews with the word: " << word << endl << endl;
        for(int i : w->getReviewIds()){
            cout << "Line " << i << ": " << frases[i].first << " Rating: " << frases[i].second << endl;
        }
    }
    else{
        cout << "This word never appears!" << endl;
    }
}

void EmotionDetector::generateCVS(const string word, double min, double max){

    WordEntry *w = hashTable.getWordEntry(word);
    if(w != nullptr){
        ofstream cvs(word + ".cvs");
        for(int i : w->getReviewIds()){
            if(frases[i].second >= min && frases[i].second <= max)
               cvs << frases[i].second << " " << frases[i].first << endl;
        }
        cvs.close();
    }
    else{
        cout << "This word never appears!" << endl;
    }
}

void EmotionDetector::printMostPositive(int k){

    buildHeapMAXbyRating();

    if(k > heap.size())
        k = heap.size();

    vector<int> trees;

    if(heap[1]->getAverage() > heap[2]->getAverage()){
        trees.push_back(1);
        trees.push_back(2);
    }
    else{
        trees.push_back(2);
        trees.push_back(1);
    }

    int biggest;
    int counter = 1;

    cout << "1 - " << heap[0]->getWord() << " Rating: " << heap[0]->getAverage() << endl;

    while(counter != k){              // Enquanto n tiver o num certo de palavras, fazer o loop de achara a prox

        biggest = trees.at(0);

        trees.erase(trees.begin());      //retira a maior delas e coloca os filhos para comparar com os que sobraram

        int leftChild = 2 * biggest + 1;
        int righChild = 2 * biggest + 2;

        if(heap.size() > leftChild){
            int i = trees.size() - 1;
            bool inserted = false;
            while(!inserted && i >= 0){
                if(heap[leftChild]->getAverage() <= heap[trees[i]]->getAverage()){
                    trees.insert(trees.begin() + i + 1, leftChild);
                    inserted = true;
                }
                else
                    i--;
            }
            if(!inserted)
                trees.insert(trees.begin(), leftChild);
        }

        if(heap.size() > righChild){
            int i = trees.size() - 1;
            bool inserted = false;
            while(!inserted && i >= 0){
                if(heap[righChild]->getAverage() <= heap[trees[i]]->getAverage()){
                    trees.insert(trees.begin() + i + 1, righChild);
                    inserted = true;
                }
                else
                    i--;
            }
            if(!inserted)
                trees.insert(trees.begin(), righChild);
        }

        cout << ++counter << " - " << heap[biggest]->getWord() << " Rating: " << heap[biggest]->getAverage() << endl;

    }


}

void EmotionDetector::printMostAppearances(int k){

    buildHeapMAXbyAppearances();

    if(k > heap.size())
        k = heap.size();

    vector<int> trees;

    if(heap[1]->getNumAppearances() > heap[2]->getNumAppearances()){
        trees.push_back(1);
        trees.push_back(2);
    }
    else{
        trees.push_back(2);
        trees.push_back(1);
    }

    int biggest;
    int counter = 1;

    cout << "1 - " << heap[0]->getWord() << " Appearances: " << heap[0]->getNumAppearances() << endl;

    while(counter != k){              // Enquanto n tiver o num certo de palavras, fazer o loop de achara a prox

        biggest = trees.at(0);

        trees.erase(trees.begin());      //retira a maior delas e coloca os filhos para comparar com os que sobraram

        int leftChild = 2 * biggest + 1;
        int righChild = 2 * biggest + 2;

        if(heap.size() > leftChild){
            int i = trees.size() - 1;
            bool inserted = false;
            while(!inserted && i >= 0){
                if(heap[leftChild]->getNumAppearances() <= heap[trees[i]]->getNumAppearances()){
                    trees.insert(trees.begin() + i + 1, leftChild);
                    inserted = true;
                }
                else
                    i--;
            }
            if(!inserted)
                trees.insert(trees.begin(), leftChild);
        }

        if(heap.size() > righChild){
            int i = trees.size() - 1;
            bool inserted = false;
            while(!inserted && i >= 0){
                if(heap[righChild]->getNumAppearances() <= heap[trees[i]]->getNumAppearances()){
                    trees.insert(trees.begin() + i + 1, righChild);
                    inserted = true;
                }
                else
                    i--;
            }
            if(!inserted)
                trees.insert(trees.begin(), righChild);
        }

        cout << ++counter << " - " << heap[biggest]->getWord() << " Appearances: " << heap[biggest]->getNumAppearances() << endl;

    }

}

void EmotionDetector::printMostNegative(int k){

    buildHeapMINbyRating();

    if(k > heap.size())
        k = heap.size();

    vector<int> trees;

    if(heap[1]->getAverage() < heap[2]->getAverage()){
        trees.push_back(1);
        trees.push_back(2);
    }
    else{
        trees.push_back(2);
        trees.push_back(1);
    }

    int lowest;
    int counter = 1;

    cout << "1 - " << heap[0]->getWord() << " Rating: " << heap[0]->getAverage() << endl;

    while(counter != k){              // Enquanto n tiver o num certo de palavras, fazer o loop de achara a prox

        lowest = trees.at(0);

        trees.erase(trees.begin());      //retira a maior delas e coloca os filhos para comparar com os que sobraram

        int leftChild = 2 * lowest + 1;
        int righChild = 2 * lowest + 2;

        if(heap.size() > leftChild){
            int i = trees.size() - 1;
            bool inserted = false;
            while(!inserted && i >= 0){
                if(heap[leftChild]->getAverage() >= heap[trees[i]]->getAverage()){
                    trees.insert(trees.begin() + i + 1, leftChild);
                    inserted = true;
                }
                else
                    i--;
            }
            if(!inserted)
                trees.insert(trees.begin(), leftChild);
        }

        if(heap.size() > righChild){
            int i = trees.size() - 1;
            bool inserted = false;
            while(!inserted && i >= 0){
                if(heap[righChild]->getAverage() >= heap[trees[i]]->getAverage()){
                    trees.insert(trees.begin() + i + 1, righChild);
                    inserted = true;
                }
                else
                    i--;
            }
            if(!inserted)
                trees.insert(trees.begin(), righChild);
        }

        cout << ++counter << " - " << heap[lowest]->getWord() << " Rating: " << heap[lowest]->getAverage() << endl;

    }


}

void EmotionDetector::printLessAppearances(int k){

    buildHeapMINbyAppearances();

    if(k > heap.size())
        k = heap.size();

    vector<int> trees;

    if(heap[1]->getNumAppearances() < heap[2]->getNumAppearances()){
        trees.push_back(1);
        trees.push_back(2);
    }
    else{
        trees.push_back(2);
        trees.push_back(1);
    }

    int lowest;
    int counter = 1;

    cout << "1 - " << heap[0]->getWord() << " Appearances: " << heap[0]->getNumAppearances() << endl;

    while(counter != k){              // Enquanto n tiver o num certo de palavras, fazer o loop de achara a prox

        lowest = trees.at(0);

        trees.erase(trees.begin());      //retira a maior delas e coloca os filhos para comparar com os que sobraram

        int leftChild = 2 * lowest + 1;
        int righChild = 2 * lowest + 2;

        if(heap.size() > leftChild){
            int i = trees.size() - 1;
            bool inserted = false;
            while(!inserted && i >= 0){
                if(heap[leftChild]->getNumAppearances() >= heap[trees[i]]->getNumAppearances()){
                    trees.insert(trees.begin() + i + 1, leftChild);
                    inserted = true;
                }
                else
                    i--;
            }
            if(!inserted)
                trees.insert(trees.begin(), leftChild);
        }

        if(heap.size() > righChild){
            int i = trees.size() - 1;
            bool inserted = false;
            while(!inserted && i >= 0){
                if(heap[righChild]->getNumAppearances() >= heap[trees[i]]->getNumAppearances()){
                    trees.insert(trees.begin() + i + 1, righChild);
                    inserted = true;
                }
                else
                    i--;
            }
            if(!inserted)
                trees.insert(trees.begin(), righChild);
        }

        cout << ++counter << " - " << heap[lowest]->getWord() << " Appearances: " << heap[lowest]->getNumAppearances() << endl;

    }


}

void EmotionDetector::radicalsSearch(string rad){

    this->trie.findRadOccurances(rad);

}

void EmotionDetector::addFile(string fileName){
    string line;
        int score;

        //open input file
        ifstream myfile (fileName);
        if (myfile.fail())
        {
            cout << "could not open file" <<endl;
            exit(0);
        }

        while (! myfile.eof() )
        {
            myfile >> score;  //get score
            myfile.get();    // get blank space
            getline(myfile, line);

            this->frases.push_back( pair< string, int >(line.substr(0, line.size()), score) );

            transform(line.begin(), line.end(), line.begin(), ::tolower);

            int len = line.size();
            while(len > 0)    //identify all individual strings
            {
                string sub;
                len = line.find(" ");
                if (len > 0)
                {
                    sub = line.substr(0, len);
                    line = line.substr(len + 1,line.size());
                }
                else
                {
                    sub = line.substr(0, line.size());
                }

                trie.addWord(sub);

                WordEntry heapInput(sub, score, maxId);

                if(hashTable.put(heapInput))
                    heap.push_back(hashTable.getWordEntry(sub));   //insert string with the score
            }

            maxId++;
        }


}

void EmotionDetector::calculateReviewsFromFile(string fileName){

    string line;
    string wholeLine;
    double score;
    int count;

    //open input file
    ifstream myfile (fileName);
    if (myfile.fail())
    {
        cout << "could not open file" <<endl;
        exit(0);
    }

    ofstream out(fileName.substr(0, fileName.find(".txt")) + "Out" + ".txt");

    while (! myfile.eof() )
    {
        score = 0;
        count = 0;

        getline(myfile, line);
        wholeLine = line;

        transform(line.begin(), line.end(), line.begin(), ::tolower);

        int len = line.size();

        if(len > 0){
            while(len > 0)    //identify all individual strings
            {
                string sub;
                len = line.find(" ");
                if (len > 0)
                {
                    sub = line.substr(0, len);
                    line = line.substr(len + 1, line.size());
                }
                else
                {
                    sub = line.substr(0, line.size());
                }

                if( !stopWords.contains(sub) ){
                    count++;
                    score += hashTable.getAverage(sub);
                }

            }
            if(count != 0)
                out << score/count << " " << wholeLine << endl;
            else
                out << 2 << " " << wholeLine << endl;
        }

    }

    myfile.close();
    out.close();

}

void EmotionDetector::calculateReviewsFromFileKaggle(string fileName){

    string line;
    string fullLine;
    double score;
    int phraseId;
    int lixo;
    int count;

    //open input file
    ifstream myfile (fileName);
    if (myfile.fail())
    {
        cout << "could not open file" <<endl;
        exit(0);
    }

    ofstream out(fileName.substr(0, fileName.find(".tsv")) + "Out" + ".csv");
    out << "PhraseId,Sentiment" << endl;

    getline(myfile, fullLine); // ignores header

    while (! myfile.eof() )
    {
        score = 0;
        count = 0;

        myfile >> phraseId;
        myfile.get(); // blank space
        myfile >> lixo;
        myfile.get();

        getline(myfile, line);
        fullLine = line;

        transform(line.begin(), line.end(), line.begin(), ::tolower);

        int len = line.size();

        if(len > 0){
            while(len > 0)    //identify all individual strings
            {
                string sub;
                len = line.find(" ");
                if (len > 0)
                {
                    sub = line.substr(0, len);
                    line = line.substr(len + 1, line.size());
                }
                else
                {
                    sub = line.substr(0, line.size());
                }
                if( !stopWords.contains(sub) ){
                    count++;
                    score += hashTable.getAverage(sub);
                }

            }
            if(count != 0)
                out << phraseId << "," << (int) round(score/count) << endl;
            else
                out << phraseId << "," << 2 << endl;
        }

    }

    myfile.close();
    out.close();

}

void EmotionDetector::printHashTable(){
    hashTable.print();
}
