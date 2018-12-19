// name: Michael Johnson, mdj0025
// partner: none
// filename: hw03.cpp
// due date: 09/14/2018
// collaboration: I recieved help from the TA with my strategy1 and strategy2 method.
// problem: Write a game that simulates who is the greatest puzzle solver of all time.

#include <iostream>
#include <stdlib.h>
#include <assert.h>
#include <ctime>
#include <cstdlib>
using namespace std;

// Constant variables for the program.
const int NUMBER_RUNS = 10000;
const int AARON_PROB_HIT = 33;
const int BOB_PROB_HIT = 50;
const int CHARLIE_PROB_HIT = 100;


// Method headers
/** This method takes in the three shooters and checks to see if at least two of them
   are still alive.  */
bool at_least_two_alive(bool A_alive, bool B_alive, bool C_alive);


// This method implements the 1st scenerio where Aaron shoots.
void Aaron_shoots1(bool& B_alive, bool& C_alive);

// This method implements the scenerio where Bob shoots.
void Bob_shoots(bool& A_alive, bool& C_alive);

// This method implements the scenerio where Charlie shoots.
void Charlie_shoots(bool& A_alive, bool& B_alive);

// This method implements the 2nd scenerio where Aaron intentionally misses his first shot.
void Aaron_shoots2(bool& B_alive, bool& C_alive);

// This test driver tests the at_least_two_alive() method and uses asssert() to check for correctness.
void test_at_least_two_alive(void);

// This test driver tests the Aaron_shoots1() method and uses asssert() to check for correctness.
void test_Aaron_shoots1(void);

// This test driver tests the Bob_shoots() method and uses asssert() to check for correctness.
void test_Bob_shoots(void);

// This test driver tests the Charlie_shoots() method and uses asssert() to check for correctness.
void test_Charlie_shoots(void);

// This test driver tests the Aaron_shoots2() method and uses asssert() to check for correctness.
void test_Aaron_shoots2(void);

// This is the main method for the duel simulation.
int main() {
   srand(time(0));
   cout << "*** Welcome to Puzzlevania's Duel Simulator ***\n";
   
   test_at_least_two_alive();
   cout << "Press any key to continue ...\n";
   cin.ignore().get(); //Pause Command for Linux Terminal
   
   test_Aaron_shoots1();
   cout << "Press any key to continue ...\n";
   cin.ignore().get(); 
   
   test_Bob_shoots();
   cout << "Press any key to continue ...\n";
   cin.ignore().get(); 
   
   test_Charlie_shoots();
   cout << "Press any key to continue ...\n";
   cin.ignore().get(); 
   
   test_Aaron_shoots2();
   cout << "Press any key to continue ...\n";
   cin.ignore().get(); 
   
   cout << "Ready to test strategy 1 (run 10000 times):\n";
   cout << "Press any key to continue ...\n";
   cin.ignore().get();
   
   cout.setf(ios::fixed);
   cout.setf(ios::showpoint);
   cout.precision(2);
      
   int aaron_wins = 0;
   int bob_wins = 0;
   int charlie_wins = 0;
   cout << "...\n";
   cout << "...\n";
   cout << "...\n";
   cout << "\n";
   
   for(int i = 0; i < NUMBER_RUNS; i++){
      bool aaron_alive = true;
      bool bob_alive = true;
      bool charlie_alive = true;
      while (at_least_two_alive(aaron_alive, bob_alive, charlie_alive)){
         if (aaron_alive) {
            Aaron_shoots1(bob_alive, charlie_alive);
         }
         if (bob_alive) {
            Bob_shoots(aaron_alive, charlie_alive);
         }
         if (charlie_alive) {
            Charlie_shoots(aaron_alive, bob_alive);
         }
      }
      if (aaron_alive) {
         aaron_wins++;
      }
      else if (bob_alive){
         bob_wins++;
      }
      else {
         charlie_wins++;
      }  
         
   }    
   
   double aaron_win_percentage = ((double)aaron_wins / NUMBER_RUNS) * 100;
   double bob_win_percentage = ((double)bob_wins / NUMBER_RUNS) * 100;
   double charlie_win_percentage = ((double)charlie_wins / NUMBER_RUNS) * 100;
      
   cout << "Aaron won " << aaron_wins << "/10000 duels or " << aaron_win_percentage << "%\n";
   cout << "Bob won " << bob_wins << "/10000 duels or " << bob_win_percentage << "%\n";
   cout << "Charlie won " << charlie_wins << "/10000 duels or " << charlie_win_percentage << "%\n";
   
   cout << "\nReady to test strategy 2 (run 10000 times):\n";
   cout << "Press any key to continue ...\n";
   cin.ignore().get();
   
   
   aaron_wins = 0;
   bob_wins = 0;
   charlie_wins = 0;
   cout << "...\n";
   cout << "...\n";
   cout << "...\n";
   cout << "\n";
   
   for(int i = 0; i < NUMBER_RUNS; i++){
      bool aaron_alive = true;
      bool bob_alive = true;
      bool charlie_alive = true;
      while (at_least_two_alive(aaron_alive, bob_alive, charlie_alive)) {
         if (aaron_alive) {
            Aaron_shoots2(bob_alive, charlie_alive);
         }
         if (bob_alive) {
            Bob_shoots(aaron_alive, charlie_alive);
         }
         if (charlie_alive) {
            Charlie_shoots(aaron_alive, bob_alive);
         }
      }
      if (aaron_alive) {
         aaron_wins++;
      }
      else if (bob_alive){
         bob_wins++;
      }
      else {
         charlie_wins++;
      }
         
   } 
   double aaron_win_percentage2 = ((double)aaron_wins / NUMBER_RUNS) * 100;
   double bob_win_percentage2 = ((double)bob_wins / NUMBER_RUNS) * 100;
   double charlie_win_percentage2 = ((double)charlie_wins / NUMBER_RUNS) * 100;
      
   cout << "Aaron won " << aaron_wins << "/10000 duels or " << aaron_win_percentage2 << "%\n";
   cout << "Bob won " << bob_wins << "/10000 duels or " << bob_win_percentage2 << "%\n";
   cout << "Charlie won " << charlie_wins << "/10000 duels or " << charlie_win_percentage2 << "%\n";
   
   if (aaron_win_percentage2 > aaron_win_percentage){
      cout << "\nStrategy 2 is better than strategy 1."; 
   }
   
   else if (aaron_win_percentage2 < aaron_win_percentage) {
      cout << "\nStrategy 1 is better than strategy 2.";
   }
   
   else {
      cout << "\nThe strategies have the same outcome.";
   }
   return -1;
}

// Function Definitions

bool at_least_two_alive(bool A_alive, bool B_alive, bool C_alive) {
   if (A_alive && B_alive) {
      return true;
   }
   if (A_alive && C_alive) {
      return true;
   }
  
   if (B_alive && C_alive) {
      return true;
   }
   return false;
}

void Aaron_shoots1(bool& B_alive, bool& C_alive) {
   int shoot_target_result = rand()%100;
   if (shoot_target_result <= AARON_PROB_HIT){
      if (C_alive){
         C_alive = false;
      }
      else{
         B_alive = false;
      }
   }
   
}

void Bob_shoots(bool& A_alive, bool& C_alive) {
   int shoot_target_result = rand()%100;
   if (shoot_target_result <= BOB_PROB_HIT) {
      if (C_alive) {
         C_alive = false;
      }
      else {
         A_alive = false;
      }
   }
}

void Charlie_shoots(bool& A_alive, bool& B_alive) {
   if(B_alive) {
      B_alive = false;
   }
   else {
      A_alive = false;
   }
}

void Aaron_shoots2(bool& B_alive, bool& C_alive) {
   if (B_alive && C_alive) {
      return;
   } 
   else {
      int shoot_target_result = rand()%100;
      if (shoot_target_result <= AARON_PROB_HIT){
         if (C_alive){
            C_alive = false;
         }
         else{
            B_alive = false;
         }
      }
   }
}

void test_at_least_two_alive(void){
   cout << "Unit Testing 1: Function - at_least_two_alive()\n";
   
   cout << "\tCase 1: Aaron alive, Bob alive, Charlie alive\n";
   assert(true == at_least_two_alive(true, true, true));
   cout << "\tCase passed ...\n";
   
   cout << "\tCase 2: Aaron dead, Bob alive, Charlie alive\n";
   assert(true == at_least_two_alive(false, true, true));
   cout << "\tCase passed ...\n";
   
   cout << "\tCase 3: Aaron alive, Bob dead, Charlie alive\n";
   assert(true == at_least_two_alive(true, false, true));
   cout << "\tCase passed ...\n";
   
   cout << "\tCase 4: Aaron alive, Bob alive, Charlie dead\n";
   assert(true == at_least_two_alive(true, true, false));
   cout << "\tCase passed ...\n";
   
   cout << "\tCase 5: Aaron dead, Bob dead, Charlie alive\n";
   assert(false == at_least_two_alive(false, false, true));
   cout << "\tCase passed ...\n";
   
   cout << "\tCase 6: Aaron dead, Bob alive, Charlie dead\n";
   assert(false == at_least_two_alive(false, true, false));
   cout << "\tCase passed ...\n";
   
   cout << "\tCase 7: Aaron alive, Bob dead, Charlie dead\n";
   assert(false == at_least_two_alive(true, false, false));
   cout << "\tCase passed ...\n";
   
   cout << "\tCase 8: Aaron dead, Bob dead, Charlie dead\n";
   assert(false == at_least_two_alive(false, false, false));
   cout << "\tCase passed ...\n";
}

void test_Aaron_shoots1(void) {
   bool charlie_alive;
   bool bob_alive;
   cout << "Unit Testing 2: Function Aaron_shoots1(Bob_alive, Charlie_alive)\n";
   
   cout << "\tCase 1: Bob alive, Charlie alive\n";
   cout << "\t\tAaron is shooting at Charlie\n";
   charlie_alive = true;
   bob_alive = true;
   Aaron_shoots1(bob_alive, charlie_alive);
   assert(bob_alive == true);
   if(charlie_alive){
      cout << "\t\tAaron misses.\n";
   }
   else {
      cout << "\t\tCharlie is dead.\n";
   }
   
   
   cout << "\tCase 2: Bob dead, Charlie alive\n";
   cout << "\t\tAaron is shooting at Charlie\n";
   bob_alive = false;
   charlie_alive = true;
   Aaron_shoots1(bob_alive, charlie_alive);
   assert(false == bob_alive);
   if (charlie_alive){
      cout << "\t\tAaron misses.\n";
   }
   else {
      cout << "\t\tCharlie is dead.\n";
   }
   
   cout << "\tCase 3: Bob alive, Charlie dead\n";
   cout << "\t\tAaron is shooting at Bob\n";
   bob_alive = true;
   charlie_alive = false;
   Aaron_shoots1(bob_alive, charlie_alive);
   assert(false == charlie_alive);
   if (bob_alive) {
      cout << "\t\tAaron misses.\n";
   }
   else {
      cout << "\t\tBob is dead.\n";
   }
   
}


void test_Bob_shoots(void){
   bool aaron_alive, charlie_alive;
   cout << "Unit Testing 3: function Bob_shoots(Aaron_alive, Charlie_alive)\n";
   
   cout << "\tCase 1: Aaron alive, Charlie alive\n";
   cout << "\t\tBob is shooting at Charlie\n";
   aaron_alive = true;
   charlie_alive = true;
   Bob_shoots(aaron_alive, charlie_alive);
   assert(aaron_alive == true);
   if (charlie_alive){
      cout << "\t\tBob missed.\n";
   }
   else {
      cout << "\t\tCharlie is dead.\n";
   }
   
   cout << "\tCase 2: Aaron dead, Charlie alive\n";
   cout << "\t\tBob is shooting at Charlie\n";
   aaron_alive = false;
   charlie_alive = true;
   Bob_shoots(aaron_alive, charlie_alive);
   assert(aaron_alive == false);
   if (charlie_alive){
      cout << "\t\tBob missed.\n";
   }
   else {
      cout << "\t\tCharlie is dead.\n";
   }
   
   cout << "\tCase 3: Aaron alive, Charlie dead\n";
   cout << "\t\tBob is shooting at Aaron\n";
   aaron_alive = true;
   charlie_alive = false;
   Bob_shoots(aaron_alive, charlie_alive);
   assert(charlie_alive == false);
   if (aaron_alive){
      cout << "\t\tBob missed.\n";
   }
   else {
      cout << "\t\tAaron is dead.\n";
   }
}

void test_Charlie_shoots(void) {
   bool aaron_alive, bob_alive;
   
   cout << "Unit Testing 4: Function Charlie_shoots(Aaron_alive, Bob_alive)\n";
   cout << "\tCase 1: Aaron alive, Bob alive\n";
   cout << "\t\tCharlie is shooting at Bob\n";
   aaron_alive = true;
   bob_alive = true;
   Charlie_shoots(aaron_alive, bob_alive);
   assert(bob_alive == false);
   cout << "\t\tBob is dead.\n";
   
   cout << "\tCase 2: Aaron dead, Bob alive\n";
   cout << "\t\tCharlie is shooting at Bob\n";
   aaron_alive = false;
   bob_alive = true;
   Charlie_shoots(aaron_alive, bob_alive);
   assert(bob_alive == false);
   cout << "\t\tBob is dead.\n";
   
   cout << "\tCase 2: Aaron alive, Bob dead\n";
   cout << "\t\tCharlie is shooting at Aaron\n";
   aaron_alive = true;
   bob_alive = false;
   Charlie_shoots(aaron_alive, bob_alive);
   assert(aaron_alive == false);
   cout << "\t\tAaron is dead.\n";   
}

void test_Aaron_shoots2(void) {
   cout << "Unit Testing 5: Function Aaron_shoots2(Bob_alive, Charlie_alive)\n";
  
   bool bob_alive = true;
   bool charlie_alive = true;
   cout << "\tCase 1: Bob alive, Charlie alive\n";
   Aaron_shoots2(bob_alive, charlie_alive);
   assert((bob_alive == true) && (charlie_alive == true));
   cout << "\t\tAaron intentionally misses his first shot\n";
   cout << "\t\tBoth Bob and Charlie are alive.\n";
   
   bob_alive = false;
   charlie_alive = true;
   cout << "\tCase 2: Bob dead, Charlie alive\n";
   cout << "\t\tAaron is shooting at Charlie\n";
   Aaron_shoots2(bob_alive, charlie_alive);
   assert((bob_alive == false));
   if(charlie_alive){
      cout << "\t\tAaron misses.\n";
   }
   else {
      cout << "\t\tCharlie is dead.\n";
   }
   
   bob_alive = true;
   charlie_alive = false;
   cout << "\tCase 3: Bob alive, Charlie dead\n";
   cout << "\t\tAaron is shooting at Bob\n";
   Aaron_shoots2(bob_alive, charlie_alive);
   assert((charlie_alive == false));
   if(bob_alive){
      cout << "\t\tAaron misses.\n";
   }
   else {
      cout << "\t\tBob is dead.\n";
   }   
}