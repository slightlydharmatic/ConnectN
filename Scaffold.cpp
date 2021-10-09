//
//  Scaffold.cpp
//  Project 3
//
//  Created by Dharma on 5/12/21.
//
// Scaffold.cpp

#include "provided.h"
#include <utility>
#include <iostream>
#include <map>
#include <algorithm>
#include <stack>
#include <vector>
#include "support.h"
using namespace std;


class ScaffoldImpl
{
  public:
    ScaffoldImpl(int nColumns, int nLevels);
    int cols() const;
    int levels() const;
    int numberEmpty() const;
    int checkerAt(int column, int level) const;
    void display() const;
    bool makeMove(int column, int color);
    int undoMove();
    
private:
    int ncolumns;
    int nlevels;
    
    vector <vector<int>> scaffold;
    stack <int> pastMoves;
    
};

ScaffoldImpl::ScaffoldImpl(int nColumns, int nLevels)
// Create vector of vectors -> The size will be the size of my columns
// Each spot in the vector will be one of my column vectors -> size of my levels
// Initialize each vector to -1
// Store private variables
: ncolumns(nColumns), nlevels(nLevels)
{
   // check that conditions are valid
    
    if(ncolumns < 0 || nlevels < 0){
        cerr << "Invalid parameters for scaffold.";
        exit(1);
    }
    
    // create a vector initialized to -1 (vacant)

    // create a vector holding the other int vectors
    
    // scaffold is a vector holding each column vector
    for (int i = 0; i < ncolumns; i++){
        vector <int> vect(nlevels, VACANT);
        scaffold.push_back(vect);
    }
}

int ScaffoldImpl::cols() const
// Return the number of columns created
{
    return ncolumns;
}

int ScaffoldImpl::levels() const
{
    return nlevels;
}

int ScaffoldImpl::numberEmpty() const
// how many -1 are in the list
{
    int count = 0;
    for (int i = (nlevels - 1); i > -1; i--){
    // go through each column
        
    for (int j = 0; j < ncolumns; j++){
        int curr_value = scaffold[j][i];
        if (curr_value == -1)
            count++;
    }
    }
        return count;
}

int ScaffoldImpl::checkerAt(int column, int level) const
{
    int curr_value = scaffold[column - 1][level - 1];
    if (curr_value == RED)
        return RED;
    else if (curr_value == BLACK)
        return BLACK;
    else
        return VACANT;
}

void ScaffoldImpl::display() const
{
    // go thru each column -> cout << | & value of last
    // add a final "|" repeat for the amount of levels
    // last row cout << + - for num of columns
    // add a final +
    
    // look at top level for each column
    for (int i = (nlevels - 1); i > -1; i--){
    // go through each column
        
    for (int j = 0; j < ncolumns; j++){
        int curr_value = scaffold[j][i];
        // decide what to write based upon value
        cout << "|" + Value(curr_value);
        }
        cout << "|" << endl;   // to finish the line and create new line
    }
    
    // create the ending line
    for (int k = 0; k != ncolumns; k++){
        cout << "+-";
    }
    cout << "+" << endl;    // finish out the last line
}

bool ScaffoldImpl::makeMove(int column, int color)
{
    // check parameter is valid w/ vacant spot
    // check if color is valid
    // if valid drop a checker
    // else return false
 
    if (column > 0 && column <= ncolumns ){      // check that it's a valid column
        if (find(scaffold[column - 1].begin(), scaffold[column - 1].end(), VACANT) == scaffold[column - 1].end() )      // check if there's a vacant in the column
            return false;

        
        else {
            for (int i = 1; i <= scaffold[column - 1].size(); i++){
                if (checkerAt(column, i) != VACANT)
                    continue;
                else{
                    scaffold[column-1][i - 1] = color;
                    pastMoves.push(column - 1);
                    return true;
                }
            }
    }
    }
    return false;
}
int ScaffoldImpl::undoMove()
{
    // create a stack and push onto it each move
    if (pastMoves.empty())              // no moves have been made, nothing to undo
        return 0;
    int rem_col = pastMoves.top();
    pastMoves.pop();
    // go through that column and the amount of rows and find the last value thats not -1
    
    for (int i = nlevels - 1; i >= 0; i--){
        if (scaffold[rem_col][i] == -1)
            continue;
        else{
            scaffold[rem_col][i] = -1;
            return rem_col + 1;             // return the name of the column
        }
    }
    return 0;               // if the entire column is empty
}

//******************** Scaffold functions *******************************

//  These functions simply delegate to ScaffoldImpl's functions.

Scaffold::Scaffold(int nColumns, int nLevels)
{
    m_impl = new ScaffoldImpl(nColumns, nLevels);
}
 
Scaffold::~Scaffold()
{
    delete m_impl;
}
 
Scaffold::Scaffold(const Scaffold& other)
{
    m_impl = new ScaffoldImpl(*other.m_impl);
}
 
Scaffold& Scaffold::operator=(const Scaffold& rhs)
{
    if (this != &rhs)
    {
        Scaffold temp(rhs);
        swap(m_impl, temp.m_impl);
    }
    return *this;
}
 
int Scaffold::cols() const
{
    return m_impl->cols();
}

int Scaffold::levels() const
{
    return m_impl->levels();
}

int Scaffold::numberEmpty() const
{
    return m_impl->numberEmpty();
}

int Scaffold::checkerAt(int column, int level) const
{
    return m_impl->checkerAt(column, level);
}
 
void Scaffold::display() const
{
    m_impl->display();
}
 
bool Scaffold::makeMove(int column, int color)
{
    return m_impl->makeMove(column, color);
}
 
int Scaffold::undoMove()
{
    return m_impl->undoMove();
}
