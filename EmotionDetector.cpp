#include "EmotionDetector.h"

#include <iostream>
#include <fstream>
#include <cstdlib>

using namespace std;


EmotionDetector::EmotionDetector(string fileName)
{
    maxId = 0;
    hashTable = new HashTable(1000);
    fileReader(fileName);
}


void EmotionDetector::fileReader(string fileName)
{
    string line;
    int score;

    //open input file
    ifstream myfile (fileName);
    if (myfile.fail())
    {
        cout << "could not open file" <<endl;
        exit(0);
    }

    int lineId = 0;

    while (! myfile.eof() )
    {
        myfile >> score;  //get score
        myfile.get();    // get blank space
        getline(myfile, line);

        this->frases.push_back(line.substr(0, line.size()));

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
            WordEntry heapInput(sub, score, lineId);
            
            if(hashTable->put(heapInput))
                heap.push_back(hashTable->getWordEntry(sub));   //insert string with the score
        }

        lineId++;
    }
    maxId = lineId;
}


void EmotionDetector::buildHeapMAX(){
    for(int i=(heap.size())/2 - 1; i>=0; i--){
        maxHeapify(i);
    }
}


void EmotionDetector::buildHeapMIN(){
    for(int i=(heap.size())/2 - 1; i>=0; i--){
        minHeapify(i);
    }
}

        
void EmotionDetector::maxHeapify(int i){
    int e = i*2 + 1;
    int d = i*2 + 2;
    int maior = i;
    int heapSize = heap.size();
    if(e < heapSize  && heap[e]->getAverage() > heap[maior]->getAverage()) maior = e;
    if(d < heapSize  && heap[d]->getAverage() > heap[maior]->getAverage()) maior = d;
    if(maior != i){
         swap(heap[maior], heap[i]);
         maxHeapify(maior);
    }
}

void EmotionDetector::minHeapify(int i){
    int e = i*2 + 1;
    int d = i*2 + 2;
    int menor = i;
    int heapSize = heap.size();
    if(e < heapSize  && heap[e]->getAverage() < heap[menor]->getAverage()) menor = e;
    if(d < heapSize  && heap[d]->getAverage() < heap[menor]->getAverage()) menor = d;
    if(menor != i){
         swap(heap[menor], heap[i]);
         minHeapify(menor);
    }
}


void EmotionDetector::calculateReviewEmotion(){
    string message = " ";

    while(message.length() > 0)
    {
        cout << "Enter a review -- Press return to exit: " <<  endl;
        getline(cin, message);

        //used for calculating the average
        double sum = 0;
        int count = 0;

        int len = message.size();
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
            sum += hashTable->getAverage(sub);
            count++;
        }

        if (message.size() > 0)
        {
            cout << "The review has an average value of " << (double)sum/count << endl;
        }
    }

}

double EmotionDetector::avgRatingWord(const string word){
    return this->hashTable->getAverage(word);
}

void EmotionDetector::printAppearances(const string word){

    WordEntry *w = hashTable->getWordEntry(word);
    if(w != nullptr){
        cout << "Reviews with the word: " << word << endl << endl;
        for(int i : w->getReviewIds()){
            cout << "Line " << i << ": " << frases[i] << endl;
        }
    }
    else{
        cout << "This word never appears!" << endl;
    }
}

void EmotionDetector::printMostPositive(int k){
    buildHeapMAX();
    cout<<"MOST POSITIVE:" <<endl;
    if(k > heap.size()) k = heap.size();

    vector<int> trees;
    trees.push_back(1);
    trees.push_back(2);
    int buffer;
    int counter = 1;

    cout << "1 : " << heap[0]->getWord() << " -> " << heap[0]->getAverage() << endl; 

    while(counter!=k){              // Enquanto n tiver o num certo de palavras, fazer o loop de achara a prox

    int removal = 0;
        buffer = trees.at(0);
        for(int i = 0; i < trees.size(); i++){      //percorre a lista de indexes para ver qua que é a maior para retirar e colocar os filhos
            if(heap[trees[i]]->getAverage() > heap[buffer]->getAverage()){
                buffer = trees[i];
                removal = i;
            }
        }
        trees.erase(trees.begin() + removal);       //retira a maior delas e coloca os filhos para comparar com os que sobraram
        
        if(heap.size() > 2*buffer+1) trees.push_back(2*buffer + 1);              /// TODO: ISSO AQUI TA DANDO ERRADO PQ ELE SAI DO HEAP, MAS SE BOTAR UM INRANGE ELE PULA FILHOS QUE EXISTEM (?) 
        
        if(heap.size() > 2*buffer+2)trees.push_back(2*buffer + 2);
        

         cout << ++counter << " : " << heap[buffer]->getWord() << " -> " << heap[buffer]->getAverage() << endl; 
        
    }


}

void EmotionDetector::printMostNegative(int k){
    buildHeapMIN();
    cout<<"MOST NEGATIVE:" <<endl;
    if(k > heap.size()) k = heap.size();

    vector<int> trees;
    trees.push_back(1);
    trees.push_back(2);
    int buffer;
    int counter = 1;

    cout << "1 : " << heap[0]->getWord() << " -> " << heap[0]->getAverage() << endl; 

    while(counter!=k){              // Enquanto n tiver o num certo de palavras, fazer o loop de achara a prox

    int removal = 0;
        buffer = trees.at(0);
        for(int i = 0; i < trees.size(); i++){      //percorre a lista de indexes para ver qua que é a maior para retirar e colocar os filhos
            if(heap[trees[i]]->getAverage() < heap[buffer]->getAverage()){
                buffer = trees[i];
                removal = i;
            }
        }
        trees.erase(trees.begin() + removal);       //retira a maior delas e coloca os filhos para comparar com os que sobraram
        
        if(heap.size() > 2*buffer+1) trees.push_back(2*buffer + 1);              /// TODO: ISSO AQUI TA DANDO ERRADO PQ ELE SAI DO HEAP, MAS SE BOTAR UM INRANGE ELE PULA FILHOS QUE EXISTEM (?) 
        
        if(heap.size() > 2*buffer+2)trees.push_back(2*buffer + 2);
        

         cout << ++counter << " : " << heap[buffer]->getWord() << " -> " << heap[buffer]->getAverage() << endl; 
        
    }


}

vector<string> EmotionDetector::radicalsSearch(string rad){   
    
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

            this->frases.push_back(line.substr(0, line.size()));

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
                WordEntry heapInput(sub, score, maxId);

                if(hashTable->put(heapInput))
                    heap.push_back(hashTable->getWordEntry(sub));   //insert string with the score
            }

            maxId++;
        }


}
