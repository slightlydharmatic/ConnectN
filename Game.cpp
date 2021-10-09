// Game.cpp

#include "provided.h"

class GameImpl
{
  public:
    GameImpl(int nColumns, int nLevels, int N, Player* red, Player* black);
    bool completed(int& winner) const;
    bool takeTurn();
    void play();
    int checkerAt(int c, int r) const;
    int findHorizontal(Scaffold &theGame, int startVec, int startLevel, int color) const ;
    int findVertical(Scaffold &theGame, int startVec, int startLevel, int color) const;
    int findDiagonalRight(Scaffold &theGame, int startVec, int startLevel, int color) const;
    int findDiagonalLeft(Scaffold &theGame, int startVec, int startLevel, int color) const;
    ~GameImpl();
    
private:
    Scaffold* theGame;
    int winner;
    Player* redP;
    Player* blackP;
    int* whosTurnP;
    int whosTurn;
    int numToWin;

};

GameImpl::GameImpl(int nColumns, int nLevels, int N, Player* red, Player* black)
{
    // create a private member scaffold of the correct size
    //
    theGame = new Scaffold(nColumns,nLevels);
    redP = red;
    blackP = black;
    winner = VACANT;
    whosTurn = 0;
    whosTurnP = &whosTurn;
    numToWin = N;
}


int GameImpl::findHorizontal(Scaffold &theGame, int startVec, int startLevel, int color) const{
    // checker at startVec and StartLevel to find out what color
    // check if that next horizontal number has that same color if so add one and recursively call and add one
    // if it's not the same then it's not consecutive and you need to return that number immediately
    int numCols = theGame.cols();
    if (startVec == numCols)         // can not check anything further or else bad access
        return 1;
    else if (color == theGame.checkerAt(startVec + 1, startLevel) && color != VACANT)
        return findHorizontal(theGame, startVec + 1, startLevel, color) + 1;
    else
        return 1;
}

int GameImpl::findVertical(Scaffold &theGame, int startVec, int startLevel, int color) const{
    int numLevels = theGame.levels();
    if (startLevel == numLevels)
        return 1;
    else if (color == theGame.checkerAt(startVec, startLevel + 1) && color != VACANT)
        return findVertical(theGame, startVec, startLevel + 1, color) + 1;
    else
        return 1;
}

int GameImpl::findDiagonalRight(Scaffold &theGame, int startVec, int startLevel, int color) const{
    if(startVec == theGame.cols())          // at the end of the columns, nothing is to the right
        return 1;
    if (color == theGame.checkerAt(startVec + 1, startLevel + 1) && color != VACANT)
        return findDiagonalRight(theGame, startVec + 1, startLevel + 1, color) + 1;
    else
        return 1;
}

int GameImpl::findDiagonalLeft(Scaffold &theGame, int startVec, int startLevel, int color) const{
    if (startVec == 1)
        return 1;
    else if (color == theGame.checkerAt(startVec - 1, startLevel + 1) && color != VACANT)
        return findDiagonalLeft(theGame, startVec - 1, startLevel + 1, color) + 1;
    else
        return 1;
}

bool GameImpl::completed(int& winner) const
{
    // game is completed if N of one color in a column, N of one color in a row
    // N of color in a diagonal

    for (int i = 1; i <= theGame->cols(); i++){         // go thru each column to check if matched
        int startVec = i;
        
        for (int j = 1; j <= theGame->levels(); j++){           // go through each level
            int startLevel = j;
        int color = checkerAt(startVec, startLevel);
     
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
        if (theGame->numberEmpty() == 0){
            winner = TIE_GAME;
            return true;
        }
    }
    // when each move is added check if the one before it is same color -> recursive function
    // when each move is added check if the stack one over on either side is the same color
    // if it is than continue to call that function
    // check if the stack one over and the row below has the same color -> if so contine to call it

    return false;


// go thru the col, nlevel - 1 -> push the first on the stack.. if it's the same push it on the stack
// if it's not... pop the stack till it's empty and then add that next value
// if the stack size == N then return true
// base case

}


bool GameImpl::takeTurn()
{
    if (this->completed(winner) == true)
        return false;
    else{
        if (whosTurn % 2 == 0){  // even mean it's red's turn
            int chooseCol = redP->chooseMove(*theGame, numToWin, RED);
            theGame->makeMove(chooseCol, RED);
            theGame->display();
            whosTurn++;
            return true;
        }
        else {
            int chooseCol = blackP->chooseMove(*theGame, numToWin, BLACK);
            theGame->makeMove(chooseCol, BLACK);
            theGame->display();
            whosTurn++;
            return true;
    }
}

}

void GameImpl::play()
{
    
    while (this->completed(winner) == false)      {      // game not completed
    if ((redP->isInteractive() && (whosTurn % 2 == 0))|| (blackP->isInteractive() && (whosTurn % 2 == 1))){  // if the player is interactive and it's their turn
        takeTurn();
    }
    else {
        takeTurn();
        if(theGame->numberEmpty() % 5 == 0){            // every fifth turn prompt for enter
            std::cout << "Press enter to continue: " << std::endl;
            std::cin.ignore();
        }
    }
    }
    theGame->display();
    if (winner == RED)
    std::cout << "The winner is red." << std::endl;
    
    if (winner == BLACK)
        std::cout << "The winner is black." << std::endl;
    
    else if (winner == TIE_GAME)
        std:: cout << "Tie game." << std::endl;
    // display the progress
    // if neither is interactive -> make the viewer press enter to continue
    // announce the winner

}

int GameImpl::checkerAt(int c, int r) const
{
    if (theGame->checkerAt(c, r) == RED)
        return RED;
    else if (theGame->checkerAt(c,r) == BLACK)
        return BLACK;
    return VACANT;
        
}

GameImpl:: ~GameImpl()
{
    delete theGame;
}

//******************** Game functions *******************************

//  These functions simply delegate to GameImpl's functions.

Game::Game(int nColumns, int nLevels, int N, Player* red, Player* black)
{
    m_impl = new GameImpl(nColumns, nLevels, N, red, black);
}
 
Game::~Game()
{
    delete m_impl;
}
 
bool Game::completed(int& winner) const
{
    return m_impl->completed(winner);
}

bool Game::takeTurn()
{
    return m_impl->takeTurn();
}

void Game::play()
{
    m_impl->play();
}
 
int Game::checkerAt(int c, int r) const
{
    return m_impl->checkerAt(c, r);
}
