#include "EmotionDetector.h"
#include <iostream>
#include <fstream>
#include <cstdlib>

using namespace std;

int main()
{

    string fileName = "movieReviews.txt";
    cout << "Please type the name of the file you want to process:" << endl;
    cin >> fileName;
    int op;

    string options = "Type one of the options ahead:\n";
           options += "1 - Calculate a word's average score\n";
           options += "2 - Calculate a new Review's score\n";
           options += "3 - Calculate Review's score from a file\n";
           options += "4 - Calculate the K most positive words\n";
           options += "5 - Calculate the K most negative words\n";
           options += "6 - Calculate the K words with more appearances\n";
           options += "7 - Calculate the K words with less appearances\n";
           options += "8 - Generate cvs file with comments of a word\n";
           options += "9 - Radical search of words\n";
           options += "10 - Add another file\n";
           options += "0 - QUIT \n";
    string cursor = "> ";

    EmotionDetector emotionDetector(fileName, 1);
    emotionDetector.calculateReviewsFromFileKaggle("test.tsv");

    string buff;
    int numOfExtremes;

    do{

        cout << options;
        cout << cursor;
        cin >> op;

        switch(op){

            case 1:
                cout << "Please type the word:" << endl << cursor;
                cin >> buff;
                cout << emotionDetector.avgRatingWord(buff) << endl;
                break;

            case 2:
                cout << "Please type the new Review:" << endl << cursor;
                cin.ignore(); // Ignore \n from enter
                getline(cin, buff);
                emotionDetector.calculateReviewEmotion(buff);
                break;

            case 3:
                cout << "Please type name of the file:" << endl << cursor;
                cin >> buff;
                emotionDetector.calculateReviewsFromFile(buff);
                break;

            case 4:
                cout << "Please type the K:" << endl << cursor;
                cin >> numOfExtremes;
                emotionDetector.printMostPositive(numOfExtremes);
                break;

            case 5:
                cout << "Please type the K:" << endl << cursor;
                cin >> numOfExtremes;
                emotionDetector.printMostNegative(numOfExtremes);
                break;

            case 6:
                cout << "Please type the K:" << endl << cursor;
                cin >> numOfExtremes;
                emotionDetector.printMostAppearances(numOfExtremes);
                break;

            case 7:
                cout << "Please type the K:" << endl << cursor;
                cin >> numOfExtremes;
                emotionDetector.printLessAppearances(numOfExtremes);
                break;

            case 8:
                cout << "Please type the word you want to generate cvs with the reviews it appears in:" << endl;
                cin >> buff;
                cout << "Please type the mininum and maximun rating of the reviews" << endl << cursor;
                double min, max;
                cin >> min;
                cin >> max;
                emotionDetector.generateCVS(buff, min, max);
                break;

            case 9:
                cout << "Please type the radical you want to search for:" << endl << cursor;
                cin >> buff;
                emotionDetector.radicalsSearch(buff);
                break;

            case 10:
                cout << "Please type the name of the file you want to read:" << endl << cursor;
                cin >> buff;
                emotionDetector.addFile(buff);
                break;

            default:
                if(op != 0)
                    cout << "Command not recognized!" << endl;
                break;

        }
        cout << endl;

    }while(op != 0);

    return 0;
}
