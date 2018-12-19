// name: Michael Johnson, mdj0025
// partner: Jordan Cox, jwc0045
// filename: project1.cpp
// due date: 11/09/17
// collaboration:
// My code can be compiled and ran without error using jGRASP.
// The purpose of this project is to design a text based game.
#include <fstream>
#include <iostream>
#include <stdlib.h>
#include <assert.h>
using namespace std;
class Character{
   public:
   Character();
   Character(string name_in, int intel_in, int money_in, int time_in);
   void printStats();
   void setMoney(int money_in);
   void setIntel(int intel_in);
   void setTime(int time_in);
   int getMoney();
   int getTime();
   int getIntel();
   void sub_Intel(int amount);
   void sub_Money(int amount);
   void sub_Time(int amount);
   void add_Time(int amount);
   void add_Money(int amount);
   void add_Intel(int amount);
   string name;
   int intel;
   int money;
   int time;
  
   private:
   static const int DEFAULT_TIME = 25;
   static const int DEFAULT_INTELLIGENCE = 15;
   static const int DEFAULT_MONEY = 10;
   
};

class GameSystem{
   friend class Character;
   public:
   void newGame();
   void setSubTime(int time);
   void setStartTime(int min, int max);
   void setStartIntel(int min, int max);
   void setStartMoney(int min, int max);
   void setHallLength(int length);
   void readPapers();
   void findChange();
   int showScore();
   void saveToHighScore();
   void endGame();
   void showHighscores();
   int getHallLength();
   int hall_length;
   private:
   string name;
   int start_intel;
   int start_time;
   int start_money;
};

class Encounter {
   friend class Character;
   public:
   Encounter(Character* player_in);
   Encounter();
   void generate();
   private:
   Character* player;
   void puzzle();
   void student();
   void professor();
   void homework();
   void grade_hw();
   void nap();
   void nothing();
};

class Menu {
   friend class GameSystem;
   public:
      void runMain();
      void runGame();
      int choice;
      int choice2;
};

Character* bob;
Menu start;
GameSystem game;


void GameSystem::newGame(){
   srand(time(0));
   setStartTime(50, 60);
   setStartIntel(10, 50);
   setStartMoney(15, 30);
   int randHallLength = (rand() % 6) + 20;
   setHallLength(randHallLength);
   bob = new Character(name, start_intel, start_money, start_time); 
   if(start_time < hall_length){
      cout << "WARNING: The game may be impossible because the starting time is less than the hall length." << endl;
   }
}

void GameSystem::setStartTime(int min, int max) {
   this->start_time = rand() % (max-min + 1) + min;
}

void GameSystem::setStartIntel(int min, int max) {
   this->start_intel = rand() % (max-min + 1) + min;
}

void GameSystem::setStartMoney(int min, int max) {
   this->start_money = rand() % (max-min + 1) + min;
}

void GameSystem::setHallLength(int length) {
   this->hall_length = length;
}

void GameSystem::readPapers() {
   
   bob->sub_Time(2);
   bob->add_Intel(2);
}

void GameSystem::findChange() {
   
   bob->sub_Time(2);
   bob->add_Money(1);
}

int GameSystem::showScore() {
   int score = bob->getMoney() * bob->getIntel() * bob->getTime();
   return score;
}

void GameSystem::saveToHighScore() {
   int scores[10];
   int n = 0;
   int score = bob->getMoney() * bob->getIntel() * bob->getTime();
   ifstream ins;
   ins.open("scores.txt");
   while (!ins.eof())
   {
      ins >> scores[n];
      n++;
   }
   
   ins.close();
   int newscores[10];
   
   for (int i = 0; i<10; i++) {
      if (scores[i] < score) {
         newscores[i] = score;
         if (i<9) {
            newscores[i+1] = scores[i];
         }
         n = i+1;
         break;
      }
      newscores[i] = scores[i];
   }
   
   if (n < 10) {
      for (int i = n; i<10; i++) {
         newscores[i] = scores[i-1];
      }
   }
   
   ofstream outfile ("scores.txt");
   
   for (int i = 0; i<10; i++) {
      outfile << newscores[i] << endl;
   }
   
}

void GameSystem::showHighscores(){
   int scores[10];
   int n = 0;
   ifstream ins;
   ins.open("scores.txt");
   while (!ins.eof())
   {
      ins >> scores[n];
      n++;
   }
   
   ins.close();
   n = 1;
   for (int i = 0; i < 10; i++) {
      cout << n << ": " << scores[i] << endl;
      n++;
   }
}

int GameSystem::getHallLength() {
   return hall_length;
}

Encounter::Encounter() {
   srand(time(0));
}
Encounter::Encounter(Character* player_in){
   player = player_in;
   generate();
}
void Encounter::generate(){
   int chance = rand() % 100 + 1;
   if (chance <=15) {
      nothing();
   }
   else if (chance <= 45) {
      puzzle();
   }
   else if (chance <= 55) {
      professor();
   }
   else if (chance <= 65) {
      student();
   }
   else if (chance <= 80) {
      homework();
   }
   else if (chance <= 90){
      grade_hw();
   }
   else {
      nap();
   }
}

void Encounter::puzzle(){
   int puzzle_choice = rand() % 7 + 1;
   int user_answer;
   bob->sub_Time(1);
   cout << "You have encountered a puzzle! Answer wisely to raise intelligence!!!" << endl;
   switch(puzzle_choice) {
      case 1: 
         cout << "David's father has three sons: Snap, Crackle, and ____?" << endl;
         cout << "1.)Pop 2.)Michael Jordan 3.)David 4.)Josiah" << endl;
         cout << "Please enter a single digit for your answer." << endl;
         cin.clear();
         cin >> user_answer;
         cout << endl;
         while(user_answer != 1 && user_answer != 2 && user_answer != 3 && user_answer != 4) {
            cout << "You must only enter a single digit as your answer. Please try again." << endl;
            cin.clear();
            cin.ignore();
            cin >> user_answer;
         }
         if (user_answer == 3){
            cout << "Correct! You gain +2 intelligence." << endl;
            player->add_Intel(2);
         }
         else {
            cout << "WRONG! You lose 2 intelligence." << endl;
            player->sub_Intel(2);
         }
         break;
      case 2:
         cout << "What's a lifegaurd's favorite game?" << endl;
         cout << "1.)Swimming 2.)Watching kids drown 3.)Chess 4.)Pool" << endl;
         cout << "Please enter a single digit for your answer." << endl;
         cin.clear();
         cin.ignore();
         cin >> user_answer;
         cout << endl;
         while(user_answer != 1 && user_answer != 2 && user_answer != 3 && user_answer != 4) {
            cout << "You must only enter a single digit as your answer. Please try again." << endl;
            cin.clear();
            cin >> user_answer;
         }
         if (user_answer == 4) {
            cout << "Correct! You gain +2 intelligence." << endl;
            player->add_Intel(2);
         }
         else {
            cout << "WRONG! You lose 2 intelligence." << endl;
            player->sub_Intel(2);
         }
         break;
      case 3:
         cout << "Why do hamburger's fly south for the winter?" << endl;
         cout << "1.)To go to Miami 2.)So they don't freeze their buns 3.)To see the Beatles in concert" << endl;
         cout << "Please enter a single digit for your answer." << endl;
         cin.clear();
         cin.ignore();
         cin >> user_answer;
         cout << endl;
         while(user_answer != 1 && user_answer != 2 && user_answer != 3) {
            cout << "You must only enter a single digit as your answer. Please try again." << endl;
            cin.clear();
            cin >> user_answer;
         }
         if (user_answer == 2) {
            cout << "Correct! You gain +2 intelligence." << endl;
            player->add_Intel(2);
         }
         else {
            cout << "WRONG! You lose 2 intelligence."<< endl;
            player->sub_Intel(2);
         }
         break;
         
      case 4:
         cout << "What did the chearleaders say to the ghost?" << endl;
         cout << "1.)Show your spirit! 2.)BOO 3.)Happy Halloween!" << endl;
         cout << "Please enter a single digit for your answer." << endl;
         cin.clear();
         cin.ignore();
         cin >> user_answer;
         cout << endl;
         while(user_answer != 1 && user_answer != 2 && user_answer != 3) {
            cout << "You must only enter a single digit as your answer. Please try again." << endl;
            cin.clear();
            cin >> user_answer;
         }
        
         if (user_answer == 1){
            cout << "Correct! You gain +2 intelligence." << endl;
            player->add_Intel(2);
         }
         
         else {
            cout << "WRONG! You lose 2 intelligence." << endl;
            player->sub_Intel(2);
         }
         break;
      case 5:
         cout << "What do you get when you have a cat that eats lemons?" << endl;
         cout << "1.)A weird cat 2.)A sour puss 3.)Nothing. Cats don't eat lemons" << endl;
         cout << "Please enter a single digit for your answer." << endl;
         cin.clear();
         cin.ignore();
         cin >> user_answer;
         cout << endl;
         while(user_answer != 1 && user_answer != 2 && user_answer != 3) {
            cout << "You must only enter a single digit as your answer. Please try again." << endl;
            cin.clear();
            cin >> user_answer;
         }
        
         if (user_answer == 2){
            cout << "Correct! You gain +2 intelligence." << endl;
            player->add_Intel(2);
         }
         
         else {
            cout << "WRONG! You lose 2 intelligence."<< endl;
            player->sub_Intel(2);
         }
         break;
      case 6:
         cout << "Why is a bad joke like a bad pencil?" << endl;
         cout << "1.)It's not very sharp 2.)Because it has no point" << endl;
         cout << "Please enter a single digit for your answer." << endl;
         cin.clear();
         cin.ignore();
         cin >> user_answer;
         cout << endl;
         while(user_answer != 1 && user_answer != 2) {
            cout << "You must only enter a single digit as your answer. Please try again." << endl;
            cin.clear();
            cin >> user_answer;
         }
         if (user_answer == 2){
            cout << "Correct! You gain +2 intelligence." << endl;
            player->add_Intel(2);
         }
         
         else {
            cout << "WRONG! You lose 2 intelligence."<< endl;
            player->sub_Intel(2);
         }
         break;
      case 7:
         cout << "How do you get a baby alien to sleep?" << endl;
         cout << "1.)Tuck it in bed 2.)You feed it 3.)Sing to it 4.)You rocket" << endl;
         cout << "Please enter a single digit for your answer." << endl;
         cin.clear();
         cin.ignore();
         cin >> user_answer;
         cout << endl;
         while(user_answer != 1 && user_answer != 2 && user_answer != 3 && user_answer != 4) {
            cout << "You must only enter a single digit as your answer. Please try again." << endl;
            cin.clear();
            cin >> user_answer;
         }
         
         if (user_answer == 4){
            cout << "Correct! You gain +2 intelligence." << endl;
            player->add_Intel(2);
         }
         
         else {
            cout << "WRONG! You lose 2 intelligence."<< endl;
            player->sub_Intel(2);
         }
         break;
       default:
         cout << "ERROR with random number in puzzle." << endl;
   }
   
}

void Encounter::student(){
   cout << "YOU HAVE RAN INTO ANOTHER STUDENT" << endl;
   cout << "You lose 2 time and 3 money because you both need coffee." << endl;
   player->sub_Time(2);
   player->sub_Money(3);
}

void Encounter::professor(){
   cout << "YOU HAVE RUN INTO A PROFESSOR" << endl;
   cout << "You lose 2 time listening to this weeks classwork, but you gain 3 intelligence." << endl;
   player->sub_Time(2);
   player->add_Intel(3);
} 

void Encounter::homework(){
   cout << "BIG SURPRISE... You become swamped with homework." << endl;
   cout << "As a result of braindeaditis you lose 3 time and 4 intelligence." << endl;
   player->sub_Time(3);
   player->add_Intel(4);
}

void Encounter::grade_hw(){
   cout << "YAY! You get to grade programs..." << endl;
   cout << "As a result of grading programs, you lose 2 time but you gain 10 money." << endl;
   player->sub_Time(2);
   player->add_Money(10);
}

void Encounter::nap(){
   cout << "Wow.. falling asleep in the hallway? You have to go take a nap." << endl;
   cout << "As a result of taking a nap, you lose 3 time and gain 5 intelligence." << endl;
   player->sub_Time(3);
   player->add_Intel(5);
}

void Encounter::nothing(){
   cout << "NOTHING HAPPENS..." << endl;
   player->sub_Time(1);
}

Character::Character(){
   name = "";
   intel = DEFAULT_INTELLIGENCE;
   money = DEFAULT_MONEY;
   time = DEFAULT_TIME;
}

Character::Character(string name_in, int intel_in, int money_in, int time_in) {
   this->name = name_in;
   this->intel = intel_in;
   this->money = money_in;
   this->time = time_in;
} 
void Character::printStats() {
   cout << "These are the current stats for " << this->name  << ":" << endl;
   cout << "Intelligence: " << this->intel << endl;
   cout << "Money: " << this->money << endl;
   cout << "Time: " << this->time << endl;
}

void Character::setMoney(int money_in) {
   this->money = money_in;
}

void Character::setIntel(int intel_in) {
   this->intel = intel_in;
}

void Character::setTime(int time_in) {
   this->time = time_in;
}

int Character::getMoney() {
   return this->money;
}

int Character::getTime() {
   return this->time;
}

int Character::getIntel() {
   return this->intel;
}

void Character::sub_Intel(int amount) {
   int final_intel = this->intel - amount;
   this->intel = final_intel;
}

void Character::sub_Money(int amount) {
   int money_final = this->money - amount;
   this->money = money_final;
}

void Character::sub_Time(int amount) {
   int time_final = this->time - amount;
   this->time = time_final;
}

void Character::add_Time(int amount) {
   int time_final = this->time + amount;
   this->time = time_final;
}

void Character::add_Money(int amount) {
   int money_final = this->money + amount;
   this->money = money_final;
}

void Character::add_Intel(int amount) {
   int intel_final = this->intel + amount;
   this->intel = intel_final;
}

void Menu::runMain() {
   string name;
   cout << "What is your name?" << endl;
   cin.clear();
   cin >> name;
   cout << endl;
   choice = 0;
   cout << "======================================================" << endl;
   cout << "                   Welcome " << name << endl;
   cout << "======================================================" << endl;
   while (choice != 3 && choice != 1) {

   cout << "\n";
   cout << "1) Start a new game." << endl;
   cout << "2) View top 10 High Scores" << endl;
   cout << "3) Quit" << endl;
   cout << "\tPlease choose an option: ";
   cin.clear();
   cin.ignore();
   cin >> choice;
   cout << "\n";
   
   switch (choice){
      case 1:
         cout << "Entering game..." << endl;
         start.runGame();
         break;
      case 2:
         game.showHighscores();
         break;
      case 3:
         break;
      default: 
         cout << "Not a valid choice.";  
   }
   }

}

void Menu::runGame(){
   cout << "You have: " << endl;
   cout << "\n";
   cout << "Intelligence: " << bob->getIntel() << endl;
   cout << "Time: " << bob->getTime() << endl;
   cout << "Money: $" << bob->getMoney() << endl;
   cout << "\n";
   
   while ((choice2 != 5) && (game.getHallLength() > 0) && (bob->getTime() > 0)) {
      cout << "\n";
      cout << "You are " << game.getHallLength() << " steps from the goal. Time left: " << bob->getTime() << endl;
      cout << "\t\t1) Move forward and see what happens..." << endl;
      cout << "\t\t2) Search for loose change. (A dollar's a dollar. Amirite?)" << endl;
      cout << "\t\t3) Read technical papers. (Get that intel!)" << endl;
      cout << "\t\t4) View your stats and progress!" << endl;
      cout << "\t\t5) Quit game. (Don't do it, punk!)" << endl;
      cout << "\n";
      cout << "\tPlease choose an action: ";
      cin.clear();
      cin.ignore();
      cin >> choice2;
      cout << "\n";
      
      switch(choice2) {
         case 1:
         {
            cout << "You move forward one step, and... " << endl;
            Encounter obj(bob);
            game.hall_length -= 1;
            break;
         }
         case 2:
         {
            cout << "You search for change and find a dollar." << endl;
            game.findChange();
            break;
         }   
         case 3:
         {
            cout << "You read some technical papers and gain two intel." << endl;
            game.readPapers();
            break;
         }
         case 4:
         {
            cout << "You have: " << endl;
            cout << "\n";
            cout << "Intelligence: " << bob->getIntel() << endl;
            cout << "Time: " << bob->getTime() << endl;
            cout << "Money: $" << bob->getMoney() << endl;
            cout << "\n";
            break;
         }
         case 5:
         {
            cout << "You lose... loser"<< endl;
            start.runMain();
            break;
         }
         default:
         {
            cout << "Not a valid choice..." << endl;
            break;
         }
      }
   }
   if ((bob->getTime() <= 0) && (game.getHallLength() > 0)) {
         cout << "You ran out of time..." << endl;
         cout << "You lose." << endl;
      } 
      else if ((bob->getIntel() <= 0) && (game.getHallLength() > 0)) {
         cout << "You're out of intelligence..(dummy)" << endl;
         cout << "You lose." << endl;
      } 
      else if ((bob->getMoney() <= 0) && (game.getHallLength() > 0)) {
         cout << "You are now broke!" << endl;
         cout << "You lose." << endl;
      } 
      else if (game.getHallLength() <= 0){
         cout << "You win." << endl;
         cout << "Your final score: " << game.showScore() << endl;
      }
    game.saveToHighScore();

}



int main(){ 
   game.newGame();
   start.runMain();
   cout << game.showScore() << endl;
   cout << "Top 10 Highscores:" << endl;
   game.showHighscores();
   return 0;
}