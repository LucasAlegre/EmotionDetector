/* author: (your name here)
*  date: (today's date)
*  description:  provide a brief description of your program
*  proposed points (out of 10): a description of the number
*  of points you believe your assignment is worth
*/

#include "EmotionDetector.h"
#include <iostream>
#include <fstream>
#include <cstdlib>

using namespace std;

int main()
{

    string fileName;
    cout << "Please type the name of the file you want to process:" << endl;
    cin >> fileName;
    int op;

    string options = "Type one of the options ahead:\n1 - Calculate a word's average score;\n2 - Calculate a new Review's score;\n3 - Calculate the extreme occurances;\n4 - Search comments through a word;\n5 - Radical search of words;\n6 - Add another file;\n\n0 - QUIT ";
    
    EmotionDetector emotionDetector(fileName);
    string buff;
    int numOfExtremes;
    
    do{

        cout << options << endl;

        cin >> op;

        switch(op){

            case 1: 
                cout << "Please type the word:" << endl;
                cin >> buff;
                cout << emotionDetector.avgRatingWord(buff) << endl;
                break;

            case 2: 
                emotionDetector.calculateReviewEmotion();
                break;

            case 3: 
                cout << "Please type the number of extreme numbers you want to see:" << endl;
                cin >> numOfExtremes;
                emotionDetector.printMostNegative(numOfExtremes);
                emotionDetector.printMostPositive(numOfExtremes);
                break;

            case 4: 
                cout << "Please type the word you want to get sentences it fits in:" << endl;
                cin >> buff;
                emotionDetector.printAppearances(buff);
                break;

            case 5: 
                cout << "Please type the radical you want to search for:" << endl;
                cin >> buff;
                emotionDetector.radicalsSearch(buff);
                break;

            case 6: 
                cout << "Please type the name of the file ypu want to read:" << endl;
                cin >> buff;
                emotionDetector.addFile(buff);
                break;
            
            default:
                if(op != 0) cout << "Command not recognized!!" << endl;
                break;

        } 

    }while(op!=0);

    return 0;
}
