#include "EmotionDetector.h"

#include <iostream>
#include <fstream>
#include <cstdlib>

using namespace std;


EmotionDetector::EmotionDetector(string fileName)
{
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
                sub = line.substr(0,len);
                line = line.substr(len+1,line.size());
            }
            else
            {
                sub = line.substr(0, line.size());
            }
            hashTable->put(sub, score, lineId); //insert string with the score
        }

        lineId++;
    }

}

void EmotionDetector::calculateReviewEmotion()
{
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

double EmotionDetector::avgRatingWord(const string word)
{
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

void EmotionDetector::printMostPositive(int k)
{


}

void EmotionDetector::printMostNegative(int k)
{

}

vector<string> EmotionDetector::radicalsSearch(string rad)
{

}
