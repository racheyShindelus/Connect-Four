
#include <iostream>
#include <vector>
#include "ConnectFour.h"

// Class Constructor: "ConnectFour"
  /*
    should initialize all private member variables
  */
ConnectFour::ConnectFour(char _emptyToken, std::vector<char> _playerTokens, std::vector<char> initTokens, int _startingPlayerId):
emptyToken(_emptyToken), playerTokens(_playerTokens), currentPlayerId(_startingPlayerId)
{ 
  std::cout << "There are " << playerTokens.size() << " players." << std::endl;
  emptyToken = _emptyToken;
  for(int row = 0; row < numRows; row++)
    { 
      board.push_back( { } );
        for(int column = 0; column < numCols; column++)
          { 
            board[row].push_back(emptyToken);
          }
    }
} // END Class Constructor: "ConnectFour"

// Void Function: "printInstructions()"
  /*
    should print out a brief description about how to play the game.
  */
void ConnectFour::printInstructions()
  { 
    std::cout << std::endl;
    std::cout << "HOW TO PLAY: " << std::endl;
    std::cout << " During each player's turn, the player must " << std::endl;
    std::cout << "decide which column they would like to drop " << std::endl;
    std::cout << "their token in. Players will alternate turns " << std::endl;
    std::cout << "until one player has four of their tokens " << std::endl;
    std::cout << "placed in a line. The line may be horizontal, " << std::endl;
    std::cout << "vertical, or diagonal. Whoever is first to " << std::endl;
    std::cout << "to have four of their tokens in a line wins. " << std::endl;
    std::cout << "If the board fills up without any four like " << std::endl;
    std::cout << "tokens in alignment, the game is over. " << std::endl;
    std::cout << "SELECTING A COLUMN: " << std::endl;
    std::cout << "Enter column number like \"3\" for column 3." << std::endl;
    std::cout << std::endl;
  }; // END Void Function: "printInstructions()"

  // Void Function: "printBoard()"
    /*
      should print out the current state of the game board
    */
  void ConnectFour::printBoard()
    { 
      for(int oX = 1; oX <= numCols; oX++)  // Prints top of game board numbers
        { 
          std::cout << oX << " ";
        }
      std::cout << std::endl;
      for(int row = 0; row < numRows; row++)
        { 
          for(int column = 0; column < numCols; column++)
            { 
              std::cout << board[row][column] << " ";
            }
          std::cout << std::endl;
        }
    }; // END Void Function: "printBoard()"

  // Void Function: "nextPlayer()"
    /*
      should increment the private currentPlayerId member of the class (from zero to playerTokens.size() ) , but should start over at 0, after the last player has had a turn. (connect four is usually played with 2 players, but it should support an arbitrary number of players as long as you use the size of the playerTokens vector to help you determine the total number of players in the game.
    */
    void ConnectFour::nextPlayer()
      { 
        if(currentPlayerId == playerTokens.size() - 1)
          { 
            currentPlayerId = 0;
          }
        else
          { 
            currentPlayerId++;
          }
      }; // END Void Function: "nextPlayer()"

    // Char Return Function: "getCurrentPlayerToken()"
      /*
      should simply return the character that represents the currentPlayerId from within the private playerTokens vector
      */
    char ConnectFour::getCurrentPlayerToken()
      { 
          return playerTokens[currentPlayerId];
      } // END Char Return Function: "getCurrentPlayerToken()"

  // Bool Function: "takeTurn()"
    /* 
      responsible for communicating who's turn it is, and for collecting input from the current player
    */
  bool ConnectFour::takeTurn()
    { 
      int userInput;
      std::cout << this->getCurrentPlayerToken() << "'s Turn: ";
      std::cin >> userInput;
      if(userInput > numCols || userInput <= 0) // Out of range input
        { 
          return false;
        }
      else
        {
          userInput = userInput - 1;
          if(board[0][userInput] != emptyToken) // Full column
           { 
            std::cout << "Column " << userInput + 1 << "is Full" << std::endl;
            return false;
           }
          for(int row = 0; row < numRows; row++)
            {
              if(board[row][userInput] != emptyToken) // Proper turn
                { 
                  board[row - 1][userInput] = this->getCurrentPlayerToken();
                    return true;
                }
            }
          return false;
        }
    } // END Bool Function: "takeTurn()"
  
  // Bool Function: "isWin()"
    /*
      will check ONLY if the CURRENT player has won the game
    */
  bool ConnectFour::isWin()
    { 
      char tempCurrentPlayerToken = this->getCurrentPlayerToken();
      for(int row = 0; row < numRows; row++)
        { 
          for(int column = 0; column < numCols; column++)
            { 
              if(board[row][column] == tempCurrentPlayerToken)
                { 
                  if(column <= 3) // Row Win
                    {
                      if(board[row][column + 1] == tempCurrentPlayerToken && board[row][column + 2] == tempCurrentPlayerToken && board[row][column + 3] == tempCurrentPlayerToken)
                        { 
                          winningPlayerId = currentPlayerId;
                            return true;
                        }
                    }
                  if(row <= 2)  // Vertical Win
                    { 
                      if(board[row + 1][column] == tempCurrentPlayerToken && board[row + 2][column] == tempCurrentPlayerToken && board[row + 3][column] == tempCurrentPlayerToken)
                        {
                          winningPlayerId = currentPlayerId;
                            return true;
                        }
                    }
                  if(column <= 3 && row <= 2) // Diagonal Win "/" (sloping up)
                    { 
                      if(board[row + 1][column + 1] == tempCurrentPlayerToken && board[row + 2][column + 2] == tempCurrentPlayerToken && board[row + 3][column + 3] == tempCurrentPlayerToken)
                        { 
                          winningPlayerId = currentPlayerId;
                            return true;
                        }
                    }
                  if(row <= 2 && column >= 3 && column <= numCols)  // Diagonal Win "\" (sloping down)
                    {
                      if(board[row + 1][column - 1] == tempCurrentPlayerToken && board[row + 2][column - 2] == tempCurrentPlayerToken && board[row + 3][column - 3] == tempCurrentPlayerToken)
                        { 
                          winningPlayerId = currentPlayerId;
                            return true;
                        }
                    }
                }
              else {  }
            }
        }
      return false;
    } // END Bool Function: "isWin()"

  // Bool Function: "isTie()"
    /*
      should determine if the game cannot be won by either player regardless of the number of moves.
    */
  bool ConnectFour::isTie()
    {
      for(int row = 0; row < numRows; row++)
        { 
          for(int column = 0; column < numCols; column++)
            { 
              if(board[row][column] == emptyToken)
                { 
                  return false;
                }
              else
                {
                  return true;
                }
            }
        }
      return true;
    } // END Bool Function: "isTie()"

  // Int Function: "getWinningPlayerId()"
    /*
      Set and return the integer value for the winningPlayerId if the current player has won the game (otherwise it should not change the winningPlayerId).
    */
  int ConnectFour::getWinningPlayerId()
    {
       return winningPlayerId;
    } // END Int Function: "getWinningPlayerId()"

// play() is written for you - you must implement all missing methods and the class constructor
void ConnectFour::play() { 
	bool isGoodMove = false; // assume that the last move was illegal (takeTurn() will reset this)
	this->printInstructions(); // print instructions
	this->printBoard(); // print the board

	while (!this->isWin() && !this->isTie()) { // keep playing as long as the game is not won or tied

		isGoodMove = this->takeTurn(); // current player takes a turn

		if (isGoodMove) {
			this->printBoard(); // print the board if that was a good move

			if (this->isWin()) // if that was a winning move, quit the game
				break;

			if (this->isTie()) // else if the game is tied, quit the game
				break;

			this->nextPlayer(); // else, advance to the next player in the game.
		}
		// else that was an illegal move
	} // end while: game over

	if (this->getWinningPlayerId() == -1)
		std::cout << "          Sorry - It looks like the game was a tie." << std::endl;
	else
		std::cout << "          Congratulations: Player '" << this->getCurrentPlayerToken() << "' has won the game!" << std::endl;

	std::cout << "          Goodbye!" << std::endl;
}
