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
    EmotionDetector emotionDetector("movieReviews.txt");

    emotionDetector.calculateReviewEmotion();

    emotionDetector.printAppearances("love");

    return 0;
}
