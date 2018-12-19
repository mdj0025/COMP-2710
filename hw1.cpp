// name: Michael Johnson, mdj0025
// partner: none
// filename: hw01.cpp
// due date: 08/31/2018
// collaboration: I did not recieve help from anyone.

// problem: determine how much diet soda it is possible to drink
//    without dying as a result.

#include <iostream>
using namespace std;
const double RATIO = 0.001;


int main () {
   double lethal_amount, mouse_weight, your_weight, threshold;
   cout << "What is the amount of artificial sweetener needed to kill a mouse:";
   cin >>  lethal_amount;
   
   cout << "\nWhat is the weight of the mouse:";
   cin >> mouse_weight;
   
   cout << "\nWhat is the weight of the dieter:";
   cin >> your_weight;
   
   threshold = (lethal_amount * your_weight) / (mouse_weight * RATIO);
   
   cout << ("\nYou can drink ") << threshold << (" diet soda without dying as a result.");
   return 0;
}