//
//  support.cpp
//  Project 3
//
//  Created by Dharma on 5/12/21.
//

#include "support.h"
#include "provided.h"
#include <iostream>
#include <string>
using namespace std;



string Value(int val){
    if (val == VACANT){
        return "_";
    }
    else if (val == RED){
        return "R";
    }
    else {
        return "B";
    }
}



int findHorizontal(Scaffold &theGame, int startVec, int startLevel, int color) {
    // checker at startVec and StartLevel to find out what color
    // check if that next horizontal number has that same color if so add one and recursively call
    // and add one
    // if it's not the same then it's not consecutive and you need to return that number immediately
    
    int numCols = theGame.cols();
    if (startVec == numCols)     // can not check anything further or else bad access
        return 1;
    else if (color == theGame.checkerAt(startVec + 1, startLevel) && color != VACANT)
        return findHorizontal(theGame, startVec + 1, startLevel, color) + 1;
    else
        return 1;
}

int findVertical(Scaffold &theGame, int startVec, int startLevel, int color) {
    int numLevels = theGame.levels();
    if (startLevel == numLevels)
        return 1;
    else if (color == theGame.checkerAt(startVec, startLevel + 1) && color != VACANT)
        return findVertical(theGame, startVec, startLevel + 1, color) + 1;
    else
        return 1;
}

int findDiagonalRight(Scaffold &theGame, int startVec, int startLevel, int color) {
    if(startVec == theGame.cols())          // at the end of the columns, nothing is to the right
        return 1;
    if (color == theGame.checkerAt(startVec + 1, startLevel + 1) && color != VACANT)
        return findDiagonalRight(theGame, startVec + 1, startLevel + 1, color) + 1;
    else
        return 1;
}

int findDiagonalLeft(Scaffold &theGame, int startVec, int startLevel, int color) {
    if (startVec == 1)
        return 1;
    else if (color == theGame.checkerAt(startVec - 1, startLevel + 1) && color != VACANT)
        return findDiagonalLeft(theGame, startVec - 1, startLevel + 1, color) + 1;
    else
        return 1;
}


bool completed(Scaffold* theGame, int numToWin, int &winner) {
// game is completed if N of one color in a column, N of one color in a row
// N of color in a diagonal

    if (theGame->numberEmpty() == 0){
    winner = TIE_GAME;
    return true;
}


for (int i = 1; i <= theGame->cols(); i++){         // go thru each column to check if matched
    int startVec = i;
    
    for (int j = 1; j <= theGame->levels(); j++){           // go through each level
        int startLevel = j;
    int color = theGame->checkerAt(startVec, startLevel);
 
if (color == VACANT)                // if the color is vacant, that spot will not have connect N, cycle through
    continue;
    
if (numToWin <= findHorizontal(*theGame, startVec, startLevel, color)) {
    winner = color;
    return true;
}
if (numToWin <= findVertical(*theGame, startVec,startLevel, color)){
    winner = color;
    return true;
        }
if (numToWin <= findDiagonalRight(*theGame, startVec, startLevel, color)){
    winner = color;
    return true;
        }
if (numToWin <= findDiagonalLeft(*theGame, startVec, startLevel, color)){
    winner = color;
    return true;
                }
    
}
    
}

return false;

};
