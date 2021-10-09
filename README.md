# ConnectN
ConnectN is a multiplayer game that allows interactive or non-interactive users to play connect 4 with a variable number of consecutive tiles to win. The interface prompts users to enter the # of tiles necessary to be consecutive to win the game. The user can play against another player or versus the computer. If they play against the computer, there is an option for an AI SmartPlayer function that utilizes complex algorithms to calculate the perfect move in that situation. 
How to Play
The interface will direct you through the directions of how to play the game and will prompt the user for how many columns they wish their scaffold to hold. Then it will ask the user what column number they wish to drop their token within, if the column is not a possible value, it will inform the user and prompt them again for a column number. It will then print a visual of the game and which columns have tiles placed in them and the color of those tiles. After someone wins the game, the computer will inform the user and state who has won the game.


Design of My Classes

Game: 
Play function : My game uses a play function that checks if the game is completed and then checks if the player whos turn it is is an interactive player or not. If it is an interactive player it will take the turn and then immediately display the screen. Iti s not interactive and it notices that it has been five turns then it will prompt the user to press enter to continue. 

Completed function: My completed function goes through each column and starting at the lowest level of that column will find out what color is at that point and then call each of my functions (findHorizontal, findVertical, findDiagonalRight, findDiagonalLeft) to determine whether a certain number of that color are in a row in each direction. Each of those functions are created outside of the completed function, and use recursion. Essentially, for each of those functions if it finds out if the next step in that direction is that same color, then it recursively calls itself and checks if the next one is the same color as well. It keeps a tally and returns how many in a row in each direction. If that many in a row is equal to or greater than the amount needed to win then that color is set to winner and the completed function returns true. Otherwise returns false. 

My taketurn function finds out if it is completed and if it is then it returns false. Otherwise it chooses a move, makes that move and then displays. It the increments a passed by reference variable that signifies who’s turn it is. 

