// name: Michael Johnson, mdj0025
// partner: Jordan Cox, jwc0045
// filename: hw05.cpp
// due date: 10/05/2018
// collaboration: I used the given source files for this project. Also used Stack Overflow for info on creating a class.
// My code can be compiled and ran without error using jGRASP.
// problem: 

#include <fstream>
#include <iostream>
#include <stdlib.h>
#include <assert.h>
#include <string>
using namespace std;
#define UNIT_TESTING
int totalPoints = 0;
struct TriviaNode {
   string question;
   string answer;
   int point_value;
};

typedef TriviaNode* node_pointer;

// This is a class to create a linked list.
// It contains methods to access and add nodes to the list.
class LinkedList {
   public:
   LinkedList(){}
   LinkedList(string question, string answer, int points, LinkedList* aLink){
      node.question = question;
      node.answer = answer;
      node.point_value = points;
      link = aLink;   
   }
   LinkedList* getLink() {
      return link;
   }
   string getQuestion() {
      return node.question;
   }
   string getAnswer() {
      return node.answer;
   }
   int getPoints() {
      return node.point_value;
   }
   void setQuestion(string question) {
      node.question = question;
   }
   void setAnswer(string answer) {
      node.answer = answer;
   }
   void setPoints(int points) {
      node.point_value = points;
   }
   void setLink(LinkedList* aLink) {
      link = aLink;
   }
            
   private:
   TriviaNode node;
   LinkedList* link;
};
// Linked List pointer
typedef LinkedList* link_pointer;

/*****************                   Method Headers                  ***********************/
link_pointer insertNode(node_pointer& root, string question, string answer, int points);
link_pointer init();
int askQuestion(link_pointer root, int trivia);
void test_Questions();
void product_Version();
link_pointer getTriviaQuestion(link_pointer link);


// The main driver for the project.
int main() {
   #ifdef UNIT_TESTING
   test_Questions();
      
   #else
      link_pointer root = NULL;
      cout << "*** Welcome to Michael & Jordan's trivia quiz game ***\n";
      cout << "Would you like to enter your own trivia? (Yes/No): ";
      string answer;
      getline(cin, answer);
      while (answer != "Yes" && answer != "No"){
         cout << "Please enter a valid input. Only accepts \"Yes\" or \"No\": ";
         getline(cin, answer);
      }
      if (answer == "Yes") {
         string proceed;
         do {
            root = getTriviaQuestion(root);
            
            cout << "Continue? (Yes/No): ";
            getline(cin, proceed);
            while (proceed != "Yes" && proceed != "No"){
               cout << "Please enter a valid input. Only accepts \"Yes\" or \"No\": ";
               getline(cin, proceed);  
            }
         }while(proceed == "Yes");
         
      }
      else {
         root = init();
      }
      cout << endl;
      cout << "How many questions would you like to answer? ";
      int amount;
      cin >> amount;
      int proof;
      proof = askQuestion(root, amount);
      
      while(proof == 1) {
         cout << "Enter a valid number: ";
         cin >> amount;
         proof = askQuestion(root, amount);
      }
      
      cout << "\n*** Thank you for playing the trivia quiz game. Goodbye! ***\n";
      
   #endif
   return 0; 
}

// This is a method to insert a new node into the linked list.
link_pointer insertNode(link_pointer root, string question_in, string answer_in, int points) {
   link_pointer next = new LinkedList(question_in, answer_in, points, root);
   return next;
}

// This method initalizes the linked list with 3 hard coded questions.
link_pointer init() {
   link_pointer root;
   string question1 = "How long was the shortest war on record? (Hint: how many minutes)";
   string answer1 = "38";
   int points1 = 100;
   root = new LinkedList(question1, answer1, points1, NULL);
   
   
   string question2 = "What was Bank of America's original name? (Hint: Bank of Italy or Bank of Germany)";
   string answer2 = "Bank of Italy";
   int points2 = 50;
   root = new LinkedList(question2, answer2, points2, root);
   
   
   string question3 = "What is the best-selling video game of all time? (Hint: Call of Duty or Wii Sports)";
   string answer3 = "Wii Sports";
   int points3 = 20;
   root = new LinkedList(question3, answer3, points3, root);
   
   return root;
}

// This method is for taking input from the user and adding it to the linked list.
int askQuestion(link_pointer list, int trivia) {
   if (trivia <= 0) {
      cout << "Warning - The number of trivia to be asked must be equal to or larger than 1." << endl;
      return 1;
   }
   
   
   else if(list == NULL) {
      cout << "Invalid List";
      return 1;
   }
   else {
      link_pointer root = list;
      link_pointer next = root -> getLink();
      int count = 1;
      while (next != NULL) {
         next = next -> getLink();
         count++;
      }
      if (count < trivia) {
         cout << "Warning - there are only " << count << " trivia questions.\n";
         return 1;
      } 
      else {
         next = root;
         string answer;
         int index = 0;
         
         do {
            cout << "Question: " << next->getQuestion() << endl;
            cout << "Answer: ";
            getline(cin, answer);
            if(answer == "") {
               getline(cin, answer);
            }
            if (answer.compare(next -> getAnswer()) == 0) {
               cout << "Your answer is correct. You recieve " << next -> getPoints() << " points.\n";
               totalPoints += next -> getPoints();
            }
            
            else {
               cout << "Your answer is wrong. The correct answer is: " << next -> getAnswer() << endl;
            }
            
            cout << "Your total points: " << totalPoints << "\n\n";
            next = next -> getLink();
            index++;
         
         }while(next != NULL && index < trivia);
         return 0;
         
      }
   
   }
   
}
   

// The test driver for checking the program.
void test_Questions() {
   cout << "*** This is a debugging version ***" << endl;
   cout << "Unit Test Case 1: Ask no question. The program should give a warning message." << endl;
   link_pointer list = init();
   totalPoints = 0;
   int call_askQuestion = askQuestion(list, 0);
   assert(call_askQuestion == 1);
   cout << "Case 1 passed.\n\n";
   
   cout << "Unit Test Case 2.1: Ask 1 question in the linked list. The tester enters an incorrect answer." << endl;
   call_askQuestion = askQuestion(list, 1);
   assert(totalPoints == 0);
   cout << "Case 2.1 passed.\n" << endl;
   
   cout << "Unit Test Case 2.2: Ask 1 question in the linked list. The tester enters a correct answer." << endl;
   call_askQuestion = askQuestion(list, 1);
   assert(call_askQuestion == 0);
   cout << endl;  
   cout << "Case 2.2 passed.\n" << endl;
   
   totalPoints = 0;
   cout << "Unit Test Case 3.1: Ask all the questions of the last trivia in the linked list. (Enter incorrect answers)." << endl;
   call_askQuestion = askQuestion(list, 3);
   assert(totalPoints == 0);
   cout << "Case 3.2 passed.\n" << endl;
   
   cout << "Unit Test Case 3.2: Ask all the questions of the last trivia in the linked list. (Enter correct answers)." << endl;
   call_askQuestion = askQuestion(list, 3);
   assert(totalPoints == 170);
   cout << "Case 3.2 passed.\n" << endl;
   
   cout << "Unit Test Case 4: Ask five questions in the linked list.\n";
   int test4 = askQuestion(list, 5);
   assert(test4 == 1);
   
   cout << "**** End of Debugging Version ****";
   
   
}

// This method gets the current triva question.
link_pointer getTriviaQuestion(link_pointer link) {
   link_pointer root = link;
   string question;
   string answer;
   int points;
   cout << "Enter a question: ";
   getline(cin, question);
   cout << "Enter a answer: ";
   getline(cin, answer);
   
   cout << "Enter the awarded point value for this question: ";
   
   while (!(cin >> points) || points <=0) {
      cout << "Points must be a number greater than 0. Try again.";
      cin.clear();
      cin.ignore(1000, '\n');
   }
   
   root = insertNode(root, question, answer, points);
   cin.clear();
   cin.ignore(1000, '\n');
   return root;
}