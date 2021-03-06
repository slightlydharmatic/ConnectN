// Player.cpp

#include "provided.h"
#include <string>
#include <iostream>
#include "support.h"
#include <map>

using namespace std;


// find the column of the row last dropped into and subtract m=by one

// remove the last move and find out which column


int rating(Scaffold* scaffold, int numToWin, int& color){
    // take in the color that
    int computerColor = color;
    if (completed(scaffold, numToWin, color) == false){     // check if the game is over
        return 5;
    }
    else {       // check if the computer color is the same as the winner
        if (color == computerColor)         // computer won
            return (100 + scaffold->numberEmpty());
        else if(color == -1)            // this means there was a TIE GAME
            return 0;
        else
            return (-100 - scaffold->numberEmpty());     // the computer didn't win and it's not a tie
        }
    }


pair<int,int> maxRating(vector<pair<int,int>> posMoves){
    
    // take the map and go thru each one and find the maximum rating bc that will have the highest number empty and result in a win

    pair<int,int> maxMove = *posMoves.begin();
    auto it = posMoves.begin();
    int comparision = maxMove.second;
    for (it = posMoves.begin(); it != posMoves.end(); it++){
        
    // take the iterated thing if it is greater store it as the comparison .. if the comparison if less than the other one then store it
        
        if (comparision < it->first){                 // if the rating is positive that color is computer color
            maxMove = *it;
            comparision = it->first;
        }

    }
    return maxMove;          // will return the maximum value from the function
}


pair<int,int> minRating(vector<pair<int,int>> posMoves){
   
    pair<int,int> minMove = *posMoves.begin();
    auto it = posMoves.begin();
    int comparision = it->first;
    // the lowest rating will show how the human wins in least number of moves
    for(it = posMoves.begin(); it != posMoves.end(); it++){
        if(comparision > it->first){
            comparision = it->first;
            minMove = *it;
        }
    }
    return minMove;
}


pair<int,int> determineBestComputerMove(int N, int depth, Scaffold scaffold, int& color, int computer_color){
    // vector should store possible moves
    // rate each move
    // if it's ur move respond to  the by finding the maximum -> if not find the minimum
    vector<pair<int,int>> posMoves;
    Scaffold copy = scaffold;

    if (scaffold.numberEmpty() == 0)
        return make_pair(-1,-1);
    
    for (int i = 1; i <= copy.cols(); i++){
        
        if(copy.checkerAt(i, scaffold.levels()) == VACANT){
            // this means that there is an option to place in this column
            copy.makeMove(i, color);
            int curr_rating = rating(&copy, N, color);
                // is there an immediate winner or not
            
            if (color == RED)
                color = BLACK;
            else
                color = RED;
            // check if the game was actually completed .. if so record in a vector
            if (curr_rating == 5){
                curr_rating = (determineBestComputerMove(N, depth + 1, copy, color,computer_color)).first;
               posMoves.push_back(make_pair(curr_rating, i));
            }
            
            // there was a completion and someone won the game
            else if (curr_rating == 0){
                posMoves.push_back(make_pair(curr_rating, i));
    
                // records the rating and the column
            }
            else if (curr_rating >= 100){
                posMoves.push_back(make_pair(curr_rating, i));
 
                // record computer_game win
            }
            else if (curr_rating <= -100) {          // means human_player won
                posMoves.push_back(make_pair(curr_rating, i));
 
                // record a human_player win
            }
            else{
            }
            copy.undoMove();

        }
        else{               // the move is not able to be made -> then record it as
            continue;
        }
  
    }

    // iterate through all possible steps
    //      make the move -> check the rating function
                // if they won or tie -> record result
                // else determineBestHumanmove -> record result
            // undo the move
        // if (computer move ) chose the highest value
        // if (human move) chose the lowest value
        // make the move and return the row number
    
    // all possible steps : every possible row you can go on  check if the top is vacat
    // use the checkerAt move to find the non-vacant spot where u can move to
    // use the rating function for that move and record the rating
                // add one to show that it is human move but call the same function
    
    
    // keep recursively calling until it says that there is there is a winner
    // store in a map saying the winner and how many steps possible it took to to win.
        
        // things i want to store::: how many moves it took, who won
    if (computer_color == color)
        return maxRating(posMoves);
    else
        return minRating(posMoves);
}

class HumanPlayerImpl
{
  public:
    int chooseMove(const Scaffold& s, int N, int color);
};

class BadPlayerImpl
{
  public:
    int chooseMove(const Scaffold& s, int N, int color);
};

class SmartPlayerImpl
{
  public:
    int chooseMove(const Scaffold& s, int N, int color);
    
};

int HumanPlayerImpl::chooseMove(const Scaffold& s, int N, int color)
{
    if (s.numberEmpty() == 0)
        return 0;
    cout << "Choose a column number" << endl;
    cin >> N;
    // make sure the column is valid or else ask again
    if (N < 1 || N > s.cols())
        return chooseMove(s, N, color);
    // if the columns are good check if there is space
    int num_levels = s.levels();
    
    
    // go through bottom level up and if there's a Vacant then return the column
    // if there's not a vacant, continue through loop, if you reach end of the loop, return the call
    for(int i = 1; i <= num_levels; i++){
        if (s.checkerAt(N, i) == VACANT)
            return N;
        else // either a RED or BLACK there
            continue;
    }
    return chooseMove(s, N, color);
}

int BadPlayerImpl::chooseMove(const Scaffold& s, int N, int color)
{
    if (s.numberEmpty() == 0)
        return 0;
    //  choose the left most column that still has vacant spots
    // go through the columns on a for loop and if there a vacant spot then return the column
    for (int i = 1; i <= s.cols(); i++){
        for (int j = 1; j <= s.levels(); j++){
            if (s.checkerAt(i,j) == VACANT)     // check if that level is vacant
                return i;
            else
                continue;
        }                                       // no vacant spots in that column
    }
    return 0;
}

int SmartPlayerImpl::chooseMove(const Scaffold& s, int N, int color)
{
    return determineBestComputerMove(N, 0, s, color, color).second;
    
    
}

//******************** Player derived class functions *************************

//  These functions simply delegate to the Impl classes' functions.

HumanPlayer::HumanPlayer(string nm)
 : Player(nm)
{
    m_impl = new HumanPlayerImpl;
}
 
HumanPlayer::~HumanPlayer()
{
    delete m_impl;
}
 
int HumanPlayer::chooseMove(const Scaffold& s, int N, int color)
{
    return m_impl->chooseMove(s, N, color);
}

BadPlayer::BadPlayer(string nm)
 : Player(nm)
{
    m_impl = new BadPlayerImpl;
}
 
BadPlayer::~BadPlayer()
{
    delete m_impl;
}
 
int BadPlayer::chooseMove(const Scaffold& s, int N, int color)
{
    return m_impl->chooseMove(s, N, color);
}

SmartPlayer::SmartPlayer(string nm)
 : Player(nm)
{
    m_impl = new SmartPlayerImpl;
}
 
SmartPlayer::~SmartPlayer()
{
    delete m_impl;
}
 
int SmartPlayer::chooseMove(const Scaffold& s, int N, int color)
{
    return m_impl->chooseMove(s, N, color);
}

