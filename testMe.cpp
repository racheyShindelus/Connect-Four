#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <cassert>
#include <thread>
#include <chrono>
#include "ConnectFour.h"
#include "testMe.h"


void testMe(){  

  std::cout << "testMe(): Starting tests..." << std::endl;

  const char * inputFileName = "testMeIn.txt";
  const char * outputFileName = "testMeOut.txt";
  std::ofstream outputFile;
  outputFile.open(outputFileName); // open it to reinitialize it
  outputFile.close(); // close the file


  // redirect i/o
  std::ifstream inFile( inputFileName );
  std::streambuf *cinbuf = std::cin.rdbuf(); //save old buf
  std::cin.rdbuf(inFile.rdbuf()); //redirect std::cin to in.txt!

  std::ofstream out( outputFileName );
  std::streambuf *coutbuf = std::cout.rdbuf(); //save old buf
  std::cout.rdbuf(out.rdbuf()); //redirect std::cout to out.txt!

  float yourScore = 0;
  float bonusScore = 0;
  bool testResults[ 100 ]; // results of our tests - max 100 of them
  bool bonusTestResults[ 100 ]; // result of bonus tests - max 100 of them

  for (int i=0; i<100; i++){
    testResults[i] = false; // init all test results to false
    bonusTestResults[i] = false; // init all test results to false
  }

  int testNum = -1; // start negative: zero will be our first test
  int bonusTestNum = -1; // 
  std::string testName = "";

    { //  0: 
      inFile.clear();                 // reset input stream
      inFile.seekg(0, std::ios::beg); 
      testNum++; // increment to the next test
      testName = "Horizontal Win";
      std::cout << std::endl << "***********************" << std::endl;
      std::cout << "Starting Test #" << testNum << ": " << testName << std::endl;
      char e = '*';
      char x = 'P';
      char y = 'Q';
      // player #0 (x) has won on the board below
      ConnectFour game(e, {x, y},{e,e,e,e,e,e,e, 
                                  e,e,e,e,e,e,e,  
                                  e,e,e,e,e,e,e,  
                                  e,e,e,e,e,e,e,  
                                  e,e,e,e,e,e,e,  
                                  e,x,x,x,x,e,e } );
      game.play();
      if (game.getWinningPlayerId() == 0){
        std::cout << "Passed test #" << testNum << std::endl;
        testResults[testNum] = true;
      }
      else {
        std::cout << "Failed test #" << testNum << std::endl;
        testResults[testNum] = false;
      }
    }

    { // 1: 
      inFile.clear();                 // reset input stream
      inFile.seekg(0, std::ios::beg); 
      testNum++; // increment to the next test
      testName = "Vertical Win";
      std::cout << std::endl << "***********************" << std::endl;
      std::cout << "Starting Test #" << testNum << ": " << testName << std::endl;
      char e = '*';
      char x = 'P';
      char y = 'Q';
      // player #0 (x) has won on the board below
      ConnectFour game(e, {x, y},{e,e,e,e,e,e,e, 
                                  e,e,x,e,e,e,e, 
                                  e,e,x,e,e,e,e, 
                                  e,e,x,e,e,e,e, 
                                  e,e,x,e,e,e,e, 
                                  e,e,e,e,e,e,e});

      if (game.isWin()){
        std::cout << "Passed test #" << testNum << std::endl;
        testResults[testNum] = true;
      }
      else {
        std::cout << "Failed test #" << testNum << std::endl;
        testResults[testNum] = false;
      }
    }

    { // 2: 
      inFile.clear();                 // reset input stream
      inFile.seekg(0, std::ios::beg); 
      testNum++; // increment to the next test
      testName = "Diagonal Down-Right Win";
      std::cout << std::endl << "***********************" << std::endl;
      std::cout << "Starting Test #" << testNum << ": " << testName << std::endl;
      char e = '*';
      char x = 'P';
      char y = 'Q';
      // player #0 (x) has won on the board below
      ConnectFour game(e, {x, y},{e,e,x,e,e,e,e, 
                                  e,e,e,x,e,e,e,
                                  e,e,e,e,x,e,e, 
                                  e,e,e,e,e,x,e, 
                                  e,e,e,e,e,e,e, 
                                  e,e,e,e,e,e,e });
      //game.play();
      if (game.isWin()){
        std::cout << "Passed test #" << testNum << std::endl;
        testResults[testNum] = true;
      }
      else {
        std::cout << "Failed test #" << testNum << std::endl;
        testResults[testNum] = false;
      }
    }

    { // 3: 
      inFile.clear();                 // reset input stream
      inFile.seekg(0, std::ios::beg); 
      testNum++; // increment to the next test
      testName = "Diagonal UP-Right NOT-Win (wrong player)";
      std::cout << std::endl << "***********************" << std::endl;
      std::cout << "Starting Test #" << testNum << ": " << testName << std::endl;
      char e = '*';
      char x = 'P';
      char y = 'Q';
      // player #1 (y) has won on the board below, but it is not Y's turn
      ConnectFour game(e, {x, y},{e,e,e,e,e,e,e,
                                  e,e,e,e,e,e,e,  
                                  e,e,e,e,e,y,e, 
                                  e,e,e,e,y,e,e, 
                                  e,e,e,y,e,e,e, 
                                  e,e,y,e,e,e,e});
      //game.play();
      //game.nextPlayer()
      if (!game.isWin()){ // isWin() should test for the current player only which should be #0, even through #1 has won
        std::cout << "Passed test #" << testNum << std::endl;
        testResults[testNum] = true; // we pass this test if isWin() is false because the current player has not won the game.
      }
      else {
        std::cout << "Failed test #" << testNum << std::endl;
        testResults[testNum] = false;
      }
    }


    { // 4: Bad Move on full board (1st input is always column 1 from testMeiIn.txt)
      inFile.clear();                 // reset input stream
      inFile.seekg(0, std::ios::beg); 
      testNum++; // increment to the next test
      testName = "Bad Move Test (nearly full board)";
      std::cout << std::endl << "***********************" << std::endl;
      std::cout << "Starting Test #" << testNum << ": " << testName << std::endl;
      char e = '*';
      char x = 'P';
      char y = 'Q';
      ConnectFour game(e, {x, y},{x,e,e,e,e,e,e, 
                                  y,x,y,x,y,x,e,
                                  x,y,y,y,x,y,e, 
                                  x,y,y,y,x,y,e, 
                                  x,y,x,y,x,y,e, 
                                  y,x,y,x,y,x,e});
      game.printBoard();
      bool isGoodMove = game.takeTurn(); // current player takes a turn
      game.printBoard();

      if (!isGoodMove){
        std::cout << "Passed test #" << testNum << std::endl;
        testResults[testNum] = true;
      }
      else {
        std::cout << "Failed test #" << testNum << std::endl;
        testResults[testNum] = false;
      }
    }

    { // 5: GOOD Move on nearly board (1st input is always column 1 from testMeiIn.txt)
      inFile.clear();                 // reset input stream
      inFile.seekg(0, std::ios::beg); 
      testNum++; // increment to the next test
      testName = "Good Move Test (nearly full board)";
      std::cout << std::endl << "***********************" << std::endl;
      std::cout << "Starting Test #" << testNum << ": " << testName << std::endl;
      char e = '*';
      char x = 'P';
      char y = 'Q';
      ConnectFour game(e, {x, y},{e,y,x,y,x,y,e, 
                                  y,x,y,x,y,x,e, 
                                  x,y,y,y,x,y,e, 
                                  x,y,y,y,x,y,e, 
                                  x,y,x,y,x,y,e, 
                                  y,x,y,x,y,x,e });
      game.printBoard();
      bool isGoodMove = game.takeTurn(); // current player takes a turn
      game.printBoard();

      if (isGoodMove){
        std::cout << "Passed test #" << testNum << std::endl;
        testResults[testNum] = true;
      }
      else {
        std::cout << "Failed test #" << testNum << std::endl;
        testResults[testNum] = false;
      }
    }

    { // 6: 
      inFile.clear();                 // reset input stream
      inFile.seekg(0, std::ios::beg); 
      testNum++; // increment to the next test
      testName = "Simple Is-A-Tie Test (full board)";
      std::cout << std::endl << "***********************" << std::endl;
      std::cout << "Starting Test #" << testNum << ": " << testName << std::endl;
      char e = '*';
      char x = 'P';
      char y = 'Q';
      ConnectFour game(e, {x, y},{x,x,y,y,x,y,y,
                                  y,y,x,x,y,y,x,
                                  y,x,y,x,x,x,y,
                                  x,y,y,x,y,y,x,
                                  x,y,y,y,x,x,x,
                                  y,x,x,x,y,x,y});


      if (game.isTie()){
        std::cout << "Passed test #" << testNum << std::endl;
        testResults[testNum] = true;
      }
      else {
        std::cout << "Failed test #" << testNum << std::endl;
        testResults[testNum] = false;
      }
    }

    { // 7: Complex: Not tie test
      inFile.clear();                 // reset input stream
      inFile.seekg(0, std::ios::beg); 
      testNum++; // increment to the next test
      testName = "Complex Not-A-Tie Test (nearly full board)";
      std::cout << std::endl << "***********************" << std::endl;
      std::cout << "Starting Test #" << testNum << ": " << testName << std::endl;
      char e = '*';
      char x = 'P';
      char y = 'Q';
      // not a tie below because the empty space enables a win for x
      ConnectFour game(e, {x, y},{x,y,x,y,x,y,y,
                                  e,x,y,x,y,x,x, 
                                  x,y,y,y,x,y,y, 
                                  x,y,y,y,e,y,x, 
                                  y,y,x,y,x,y,y, 
                                  y,x,y,x,y,x,x});
      game.printBoard();

      if (!game.isTie()){
        std::cout << "Passed test #" << testNum << std::endl;
        testResults[testNum] = true;
      }
      else {
        std::cout << "Failed test #" << testNum << std::endl;
        testResults[testNum] = false;
      }
    }

  { // 8: NextPlayer Test
      inFile.clear();                 // reset input stream
      inFile.seekg(0, std::ios::beg); 
      testNum++; // increment to the next test
      testName = "Next Player Test  - inc to 2nd player of 2 players";
      std::cout << std::endl << "***********************" << std::endl;
      std::cout << "Starting Test #" << testNum << ": " << testName << std::endl;
      char e = '*';
      char x = 'P';
      char y = 'Q';
      // 2 players in this game
      ConnectFour game(e, {x, y});
      game.printBoard();
      game.nextPlayer(); // current player takes a turn


      if (game.getCurrentPlayerToken() == y){
        std::cout << "Passed test #" << testNum << std::endl;
        testResults[testNum] = true;
      }
      else {
        std::cout << "Failed test #" << testNum << std::endl;
        testResults[testNum] = false;
      }
    }

    { // 9: NextPlayer Test
      inFile.clear();                 // reset input stream
      inFile.seekg(0, std::ios::beg); 
      testNum++; // increment to the next test
      testName = "Next Player Test  - inc to 1st player of 2 players";
      std::cout << std::endl << "***********************" << std::endl;
      std::cout << "Starting Test #" << testNum << ": " << testName << std::endl;
      char e = '*';
      char x = 'P';
      char y = 'Q';
      // 2 players in this game
      ConnectFour game(e, {x, y});
      game.printBoard();
      game.nextPlayer(); // current player takes a turn
      game.nextPlayer(); // current player takes a turn

      if (game.getCurrentPlayerToken() == x) {
        std::cout << "Passed test #" << testNum << std::endl;
        testResults[testNum] = true;
      }
      else {
        std::cout << "Failed test #" << testNum << std::endl;
        testResults[testNum] = false;
      }
    }

    { // 10: NextPlayer Test
      inFile.clear();                 // reset input stream
      inFile.seekg(0, std::ios::beg); 
      testNum++; // increment to the next test
      testName = "Next Player Test  - inc to 1st player of 3 players";
      std::cout << std::endl << "***********************" << std::endl;
      std::cout << "Starting Test #" << testNum << ": " << testName << std::endl;
      char e = '*';
      char x = 'P';
      char y = 'Q';
      char z = 'R';
      // 3 players in this game
      ConnectFour game(e, {x, y, z});
      game.printBoard();
      game.nextPlayer(); // current player takes a turn
      game.nextPlayer(); // current player takes a turn
      game.nextPlayer(); // current player takes a turn

      if (game.getCurrentPlayerToken() == x) {
        std::cout << "Passed test #" << testNum << std::endl;
        testResults[testNum] = true;
      }
      else {
        std::cout << "Failed test #" << testNum << std::endl;
        testResults[testNum] = false;
      }
    }

  { // 11: getCurrentPlayerToken Test
      inFile.clear();                 // reset input stream
      inFile.seekg(0, std::ios::beg); 
      testNum++; // increment to the next test
      testName = "Get Current Player Token Test  - see if the current player token is the 1st player";
      std::cout << std::endl << "***********************" << std::endl;
      std::cout << "Starting Test #" << testNum << ": " << testName << std::endl;
      char e = '*';
      char x = 'P';
      char y = 'Q';
      char z = 'R';
      // 2 players in this game
      ConnectFour game(e, {x, y, z});
      game.printBoard();

      if (game.getCurrentPlayerToken() == x) {
        std::cout << "Passed test #" << testNum << std::endl;
        testResults[testNum] = true;
      }
      else {
        std::cout << "Failed test #" << testNum << std::endl;
        testResults[testNum] = false;
      }
    }

  { // 12: getCurrentPlayerToken Test using 4th argument of constructor
      inFile.clear();                 // reset input stream
      inFile.seekg(0, std::ios::beg); 
      testNum++; // increment to the next test
      testName = "Get Current Player Token Test  - testing 4th argument of constructor for default starting player";
      std::cout << std::endl << "***********************" << std::endl;
      std::cout << "Starting Test #" << testNum << ": " << testName << std::endl;
      char e = '*';
      char x = 'P';
      char y = 'Q';
      char z = 'R';
      // 2 players in this game
      ConnectFour game(e, {x, y, z}, {}, 2); // FIXED: this constructor originally was setting player #0 to start, but it should hve been #2
      game.printBoard();

      if (game.getCurrentPlayerToken() == z) {
        std::cout << "Passed test #" << testNum << std::endl;
        testResults[testNum] = true;
      }
      else {
        std::cout << "Failed test #" << testNum << std::endl;
        testResults[testNum] = false;
      }
    }

    { // Bonus 0: Hard: Full Board tie test
      inFile.clear();                 // reset input stream
      inFile.seekg(0, std::ios::beg); 
      bonusTestNum++; // increment to the next test
      testName = "BONUS: Complex Is-A-Tie Test (nearly full board)";
      std::cout << std::endl << "***********************" << std::endl;
      std::cout << "Starting Bonus Test #" << bonusTestNum << ": " << testName << std::endl;
      char e = '*';
      char x = 'P';
      char y = 'Q';
      // is a tie below because no one can win
      ConnectFour game(e, {x, y},{x,x,y,y,x,y,e,
                                  y,y,x,x,y,y,x,
                                  y,x,y,x,x,x,y,
                                  x,y,y,x,y,y,x,
                                  x,y,y,y,x,x,x,
                                  y,x,x,x,y,x,y});
      game.printBoard();
      if (game.isTie()){
        std::cout << "Passed bonus test #" << bonusTestNum << std::endl;
        bonusTestResults[bonusTestNum] = true;
        bonusScore += 1;
      }
      else {
        std::cout << "Failed bonus test #" << bonusTestNum << std::endl;
        bonusTestResults[bonusTestNum] = false;
      }
    }

    { // Bonus 1: Hard: Full Board tie test
      inFile.clear();                 // reset input stream
      inFile.seekg(0, std::ios::beg); 
      bonusTestNum++; // increment to the next test
      testName = "BONUS: Complex Is-A-Tie Test (nearly full board)";
      std::cout << std::endl << "***********************" << std::endl;
      std::cout << "Starting Bonus Test #" << bonusTestNum << ": " << testName << std::endl;
      char e = '*';
      char x = 'P';
      char y = 'Q';
      // not a tie below because the empty space enables a win for x
      ConnectFour game(e, {x, y},{x,x,y,y,x,y,e,
                                  y,y,x,x,y,y,e,
                                  y,x,y,x,x,x,y,
                                  x,y,y,x,y,y,x,
                                  x,y,y,y,x,x,x,
                                  y,x,x,x,y,x,y});
      game.printBoard();
      if (game.isTie()){
        std::cout << "Passed bonus test #" << bonusTestNum << std::endl;
        bonusTestResults[bonusTestNum] = true;
        bonusScore += 1;
      }
      else {
        std::cout << "Failed bonus test #" << bonusTestNum << std::endl;
        bonusTestResults[bonusTestNum] = false;
      }
    }

    { // Bonus 2: Hard: Nearly Full Board IS TIE test
      inFile.clear();                 // reset input stream
      inFile.seekg(0, std::ios::beg); 
      bonusTestNum++; // increment to the next test
      testName = "BONUS: Complex Is-A-Tie Test (nearly full board)";
      std::cout << std::endl << "***********************" << std::endl;
      std::cout << "Starting Bonus Test #" << bonusTestNum << ": " << testName << std::endl;
      char e = '*';
      char x = 'P';
      char y = 'Q';
      // not a tie below because the empty space enables a win for x
      ConnectFour game(e, {x, y},{x,x,y,y,x,y,e,
                                  y,y,x,x,y,y,e,
                                  y,x,y,x,x,x,y,
                                  x,e,y,x,y,y,x,
                                  x,y,y,y,x,x,x,
                                  y,x,x,x,y,x,y});
      game.printBoard();
      if (game.isTie()){
        std::cout << "Passed bonus test #" << bonusTestNum << std::endl;
        bonusTestResults[bonusTestNum] = true;
        bonusScore += 1;
      }
      else {
        std::cout << "Failed bonus test #" << bonusTestNum << std::endl;
        bonusTestResults[bonusTestNum] = false;
      }
    }

      { // Bonus 3: Hard: Nearly Full Board NOT TIE test
      inFile.clear();                 // reset input stream
      inFile.seekg(0, std::ios::beg); 
      bonusTestNum++; // increment to the next test
      testName = "BONUS: Complex NOT-A-Tie Test (nearly full board)";
      std::cout << std::endl << "***********************" << std::endl;
      std::cout << "Starting Bonus Test #" << bonusTestNum << ": " << testName << std::endl;
      char e = '*';
      char x = 'P';
      char y = 'Q';
      // not a tie below because the empty space enables a win for x
      ConnectFour game(e, {x, y},{x,x,y,y,x,y,e,
                                  y,y,x,x,y,y,e,
                                  y,x,y,x,x,x,e,
                                  x,e,y,x,y,y,x,
                                  x,y,y,y,x,x,x,
                                  y,x,x,x,y,x,y});
      game.printBoard();
      if (!game.isTie()){
        std::cout << "Passed bonus test #" << bonusTestNum << std::endl;
        bonusTestResults[bonusTestNum] = true;
        bonusScore += 1;
      }
      else {
        std::cout << "Failed bonus test #" << bonusTestNum << std::endl;
        bonusTestResults[bonusTestNum] = false;
      }
    }

{ // Bonus 4: Hard: Nearly Full Board NOT TIE test
      inFile.clear();                 // reset input stream
      inFile.seekg(0, std::ios::beg); 
      bonusTestNum++; // increment to the next test
      testName = "BONUS: Complex NOT-A-Tie Test (nearly full board)";
      std::cout << std::endl << "***********************" << std::endl;
      std::cout << "Starting Bonus Test #" << bonusTestNum << ": " << testName << std::endl;
      char e = '*';
      char x = 'P';
      char y = 'Q';
      // not a tie below because the empty space enables a win for x
      ConnectFour game(e, {x, y},{x,x,y,y,x,y,e,
                                  y,y,x,x,y,y,e,
                                  y,x,y,x,x,x,e,
                                  x,e,y,x,y,y,e,
                                  x,y,y,y,x,x,x,
                                  y,x,x,x,y,x,y});
      game.printBoard();
      if (!game.isTie()){
        std::cout << "Passed bonus test #" << bonusTestNum << std::endl;
        bonusTestResults[bonusTestNum] = true;
        bonusScore += 1;
      }
      else {
        std::cout << "Failed bonus test #" << bonusTestNum << std::endl;
        bonusTestResults[bonusTestNum] = false;
      }
    }

  // reset i/o

  std::cin.rdbuf(cinbuf);   //reset to standard input again
  std::cout.rdbuf(coutbuf); //reset to standard output again

  // test numbers go from zero to testNum (inclusive)

  //this_thread::sleep_for( chrono::seconds(1)); // sleep for 1 seconds


  std::cout << "   Your individual test results are: " << std::endl;
  for(int i=0; i<=testNum; i++){
    std::cout << "       Base Test  #" << i << ": " << (testResults[i] ? " Passed " : " Failed ") << std::endl;
    if (testResults[i])
      yourScore += 90.0 / (testNum+1);
  }

  for(int i=0; i<=bonusTestNum; i++){
    std::cout << "       Bonus Test #" << i << ": " << (bonusTestResults[i] ? " Passed " : " Failed ") << std::endl;
  }

  std::cout << "   Your Base score is " << yourScore << " out of 90 possible points " << std::endl;
  std::cout << "   Your Bonus score is " << bonusScore << std::endl;
  std::cout << "   Your Total score (preliminary) is " << (yourScore + bonusScore) << std::endl;
  std::cout << "   (You may be eligible for up to +10 more base points based on comments and user feedback, to be assessed after submission)" << std::endl;
  std::cout << "   (You may be eligible for up to +10 more BONUS points if you have implemented the takeTurnAI() bonus method, to be assessed after submission)" << std::endl;


  std::cout << std::endl;

  std::cout.flush();

}
