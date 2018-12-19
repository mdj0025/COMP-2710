// name: Michael Johnson, mdj0025
// partner: Jordan Cox, jwc0045
// filename: project2.cpp
// due date: 12/09/17
// collaboration:
// My code can be compiled and ran without error using jGRASP.
// The purpose of this project is to design a text based game.
#include <fstream>
#include <iostream>
#include <stdlib.h>
#include <assert.h>
#include <vector>
using namespace std;


class EmployeeControl{
   public:
   EmployeeControl(string filename);
   EmployeeControl();
   bool verify(string username);
   bool verify(string username, string password);
   bool verifyAdmin(string username);
   bool verifyAdmin(string username, string password);
   bool addEmployee(string username, string password, bool admin);
   bool deleteEmployee(string username);
   bool changePassword(string username, string prev_password, string new_password);
   void display();
   void load();
   void save();
   private:
   struct Employee{
      Employee(string username, string password_in, bool is_admin){
         userName = username;
         password = password_in;
         admin = is_admin;
      }
      string userName;
      string password;
      bool admin;
   };
 
   vector<Employee> employeeList;
   static const string DEFAULT;
   string staffFile;
   
};

class ClientControl{
     public:
   ClientControl(string file);
   ClientControl();
   void loadClients();
   void saveClients();
   bool add_client(string name_in, string address_in, string employer_in, string ssn_in, string income_in);
   bool edit_client(string name_in, string address_in, string employer_in, string ssn_in, string income_in);
   bool print_client(string name_in);
   bool isClient(string name_in);
     private:
   struct Client{
      string name;
      string address;
      string ssn;
      string employer;
      string income;
         
      Client(string name_in, string address_in, string employer_in, string ssn_in, string income_in){
         name = name_in;
         address = address_in;
         ssn = ssn_in;
         employer = employer_in;
         income = income_in;
      }
      };
   vector<Client> clients;
   string clientFile;
   static const string DEFAULT_FILE;
      
};


class AccountManager{
   public:
   AccountManager(string file_in);
   AccountManager();
   bool manageAcc(int acc_num_in);
   bool addAcc(string name, int acc_num, int acc_type, int balance);
   bool displayAcc(int acc_num_in);
   void loadAccounts();
   void saveAccounts();
   private:
   struct Account{
      string name;
      int acc_num;
      int acc_type; // The account type will be 0 for checking and 1 for savings.
      int balance;
      Account(string name_in, int acc_num_in, int acc_type_in, int balance_in){
         name = name_in;
         acc_num = acc_num_in;
         acc_type = acc_type_in;
         balance = balance_in;
      } 
      };
      
   string accountFile;
   vector<Account> accounts;
   static const string DEFAULT;
};

class System{
   public:
   System();
   void standby();
   void branchScreen();
   void adminScreen(string username_in, string password_in);
   void clientManager();
   void quit();                                  
   private:
   EmployeeControl employeeController;
   ClientControl clientController;
   AccountManager accountController;
   static const string ACCOUNT_FILE;
   static const string EMPLOYEE_FILE;
   static const string CLIENT_FILE;
   bool idle;
   string choice;
   string current;
      
};

const string EmployeeControl::DEFAULT = "employee.txt";
EmployeeControl::EmployeeControl(string filename){
   staffFile = filename;
   load();
}

EmployeeControl::EmployeeControl(){
   staffFile = DEFAULT;
   load();
}

bool EmployeeControl::verify(string username) {
   for(int i = 0; i < employeeList.size(); i++){
      if(username == employeeList[i].userName){
         return true;
      }
   }
   return false;
}

bool EmployeeControl::verify(string username, string password){
   for(int i = 0; i < employeeList.size(); i++){
      if(username == employeeList[i].userName){
         if(password == employeeList[i].password){
            return true;
         }
      }
   }
   return false;
}

bool EmployeeControl::verifyAdmin(string username){
   for(int i = 0; i < employeeList.size(); i++){
      if(username == employeeList[i].userName){
         if(employeeList[i].admin == true){
            return true;
         }
      }
   }
   return false;
}

bool EmployeeControl::verifyAdmin(string username, string password){
   for(int i = 0; i < employeeList.size(); i++){
      if(username == employeeList[i].userName){
         if(password == employeeList[i].password){
         
            if(employeeList[i].admin == true){
               return true;
            }
         }
      }
   }
   return false;
}

bool EmployeeControl::addEmployee(string username, string password, bool admin){
   if(username == "" || password == ""){
      cout << "The info you have entered is not valid. The user cannot be added at this time.\n";
      return false;
   }
   
   for(int i = 0; i < employeeList.size(); i++) {
      if(username == employeeList[i].userName) {
         cout << "The username you have entered already exists. The user will not be added.\n";
         return false;
      }
   }

   employeeList.push_back(Employee(username, password, admin));
   save();
   cout << "The employee has been added and saved to the file.\n";   
   return true;
}

bool EmployeeControl::deleteEmployee(string username){
   if(username == ""){
      cout << "The username you have entered is not valid.\n";
      return false;
   }
   
   for(int i = 0; i < employeeList.size(); i++){
      if(username == employeeList[i].userName){
         employeeList.erase(employeeList.begin() + i);
         save();
         cout << "Deletion sucessful.\n";
         return true;
      }
   }
   cout << "The username you have entered does not exist.\n";
   return false;
}

bool EmployeeControl::changePassword(string username, string prev_password, string new_password){
   if(username == "" || prev_password == "" || new_password == ""){
      cout << "The information you entered is not valid. Password change aborted.\n";
      return false;
   }
   
   for(int i = 0; i < employeeList.size(); i++){
      if(username == employeeList[i].userName){
         if(prev_password == employeeList[i].password){
            employeeList[i].password = new_password;
            save();
            return true;
         }
         else{
            cout << "The password you entered does not match the old password for this user.\n";
            return false;
         }
      }
   }
   
   // if we reach this far then the username does not exist.
   cout << "The username you entered does not exist. Password change aborted.\n";
   return false;
}


void EmployeeControl::display(){
   for(int i = 0; i < employeeList.size(); i++){
      cout << "User Name: " + employeeList[i].userName + " Role: ";
      if(employeeList[i].admin) {
         cout << "System admin.\n";
      }
      else {
         cout << "Branch member.\n";
      }
      
   }
}

void EmployeeControl::save(){
   ofstream out;
   out.open((char*)staffFile.c_str());
   if(out.fail()){
      cout << "The file could not be opened. Progress not saved.\n";
      out.close();
   }
   else {
      for(int i = 0; i < employeeList.size(); i++){
         out << employeeList[i].userName << endl;
         out << employeeList[i].password << endl;
         if(employeeList[i].admin){
            out << "1" << endl;
         }
         
         else {
            out << "0" << endl;
         }
      }
   }
   out.close();
}

void EmployeeControl::load(){
   ifstream in;
   in.open((char*)staffFile.c_str());
   string username;
   string password;
   int admin;
   
   if(in.fail()){
      cout << "The file could not be opened. Loading employees failed.";
   }
   
   else{
      while(in >> username >> password >> admin){
         employeeList.push_back(Employee(username, password, admin));
      }
   }
   in.close();
   if(employeeList.empty()){
      employeeList.push_back(Employee("default", "1234", "1"));
   }
}
const string ClientControl::DEFAULT_FILE = "client.txt";
ClientControl::ClientControl(string file){
   clientFile = file;
   loadClients();
}

ClientControl::ClientControl(){
   clientFile = DEFAULT_FILE;
   loadClients();
}

void ClientControl::loadClients(){
   ifstream in;
   in.open((char*)clientFile.c_str());
   string name_in;
   string address_in;
   string ssn_in;
   string employer_in;
   string income_in;
   if(in.fail()){
      cout << "The file cannot be opened. The client file is not loaded.\n";
      return;
   }
   
   else{
      while(in >> name_in >> address_in >> employer_in >> ssn_in >> income_in){
         clients.push_back(Client(name_in, address_in, employer_in, ssn_in, income_in)); 
      }
      in.close();
      if(clients.empty()){
         clients.push_back(Client("default", "default", "default", "default", "default"));
      }
   }
}

void ClientControl::saveClients(){
   ofstream out;
   out.open((char*)clientFile.c_str());
   
   if(out.fail()){
      cout << "The file could not be opened. The list of clients has not been saved.\n";
   }
   
   else{
      for(int i = 0; i < clients.size(); i++){
         out << clients[i].name << endl;
         out << clients[i].address << endl;
         out << clients[i].employer << endl;
         out << clients[i].ssn << endl;
         out << clients[i].income << endl;
      }
   }
   out.close();
}

bool ClientControl::add_client(string name_in, string address_in, string employer_in, string ssn_in, string income_in){
   if(name_in == "" || address_in == "" || employer_in == "" || ssn_in == "" || income_in == ""){
      cout << "The input for the new client is invalid. The client cannot be added at this time.\n";
      return false;
   }
   
   else{
      clients.push_back(Client(name_in, address_in, employer_in, ssn_in, income_in));
      saveClients();
      return true;
   }
}

bool ClientControl::edit_client(string name_in, string address_in, string employer_in, string ssn_in, string income_in){
   if(ssn_in == "" || name_in == "" || address_in == "" || employer_in == "" || income_in == ""){
      cout << "The information you entered is not valid.\n";
      return false;
   }
   else{
      for(int i = 0; i < clients.size(); i++){
         if(clients[i].name == name_in){
            clients[i].address = address_in;
            clients[i].employer = employer_in;
            clients[i].ssn = ssn_in;
            clients[i].income = income_in;
            saveClients();
            return true;
         }
      }
      
      cout << "The client's name you entered does not exist\n";
      return false;
   }
}

bool ClientControl::print_client(string name_in){
   if(name_in == ""){
      cout << "The name you entered is not valid.\n";
      return false;
   }
   
   else {
      for(int i = 0; i < clients.size(); i++){
         if(clients[i].name == name_in){
            cout << "Client info:" << endl;
            cout << "\tName: " << clients[i].name << endl;
            cout << "\tAddress: " << clients[i].address << endl;
            cout << "\tEmployer: " << clients[i].employer << endl;
            cout << "\tSocial Security Number: " << clients[i].ssn << endl;
            cout << "\tIncome: " << clients[i].income << endl;
            return true;
         }
      }
      return false;
   }
}

bool ClientControl::isClient(string name_in){
   if(name_in == ""){
      cout << "The name you entered is not valid.\n";
      return false;
   }
   
   else{
      for(int i = 0; i < clients.size(); i++){
         if(clients[i].name == name_in){
            return true;
         }
      }
      // if we reach here the ssn does not exist.
      cout << "The name you entered does not exist.\n";
      return false;
   }

}

AccountManager::AccountManager(string file_in){
   accountFile = file_in;
   loadAccounts();
}
const string AccountManager::DEFAULT = "account.txt";

AccountManager::AccountManager(){
   accountFile = DEFAULT;
   loadAccounts();
}

bool AccountManager::manageAcc(int acc_num_in){
   int ans;
   int amount;
   for(int i = 0; i < accounts.size(); i++){
      if(accounts[i].acc_num == acc_num_in){
         cout << "Would you like to deposit or withdraw from the account?\n";
         cout << "Please enter \"0\" to deposit, \"1\" to withdraw, or \"2\" to cancel.\n";
         cin.clear();
         cin >> ans;
         cout << endl;
         while(ans != 0 && ans!= 1 && ans != 2){
            cout << "The input is invalid. Please try again.\n";
            cout << "Please enter \"0\" to deposit, \"1\" to withdraw, or \"2\" to cancel.\n";
            cin.clear();
            cin >> ans;
            cout << endl;
         }
         if(ans == 0){ // deposit
            cout << "Please enter the amount you would like to deposit.\n";
            cin.clear();
            cin >> amount;
            cout << endl;
            while(amount < 0 || amount > 100000){
               cout << "The deposit amount must be between 0 and $100,000. Please try again.\n";
               cin.clear();
               cin >> amount;
               cout << endl;
            }
            accounts[i].balance = accounts[i].balance + amount;
            cout << "Your balance has been updated. Your new balance is: $" << accounts[i].balance << endl;
            saveAccounts();
            return true;
         }
         
         else if (ans == 1){ // withdraw
            cout << "Please enter the amount you would like to withdraw.\n";
            cin >> amount;
            while(accounts[i].balance - amount < 0){
               cout << "You cannot withdraw that much. Your balance is $" << accounts[i].balance << "Please enter a smaller amount: ";
               cin.clear();
               cin >> amount;
               cout << endl;
            }
            accounts[i].balance = accounts[i].balance - amount;
            cout << "Your balance has been updated. Your new balance is $" << accounts[i].balance << endl;
            saveAccounts();
            return true;
         }
         else{
            return true;
         }
      }
      
   }

   return false;
}

bool AccountManager::addAcc(string name_in, int acc_num_in, int acc_type_in, int balance_in){
   if(name_in == ""){
      cout << "The name you entered is not valid. Account not added.\n";
      return false;
   }
   
   else if(acc_type_in !=1 && acc_type_in != 0){
      cout << "The account type must be either 0 or 1. Account not added.\n";
      return false;
   }
   else if(balance_in < 0){
      cout << "You cannot start an account with a negative balance. Account not added.\n";
      return false;
   }
   
   else{
      accounts.push_back(Account(name_in, acc_num_in, acc_type_in, balance_in));
      saveAccounts();
      return true;
   }

   return false;
} 

bool AccountManager::displayAcc(int acc_num_in){
   for(int i = 0; i < accounts.size(); i++){
      if(accounts[i].acc_num == acc_num_in){
         cout << "Account name: " << accounts[i].name;
         if (accounts[i].acc_type == 0){
            cout << "Checking Account\n";
            cout << "\tBalance: " << accounts[i].balance << endl;
         }
         else {
            cout << "Savings Account\n";
            cout << "\tBalance: " << accounts[i].balance << endl;
         }
      }
   }
   cout << "The account number you entered does not exist in our records.\n";
   return false;
}

void AccountManager::loadAccounts(){
   ifstream in;
   in.open((char*)accountFile.c_str());
   string name_in;
   string acc_num_str;
   string acc_type_str;
   string balance_str;
   int acc_num_in;
   int acc_type_in;
   int balance_in;
   if(in.fail()){
      cout << "The file could not be opened. The accounts have not been loaded.\n";
      return;
   }
   
   else{
      while(getline(in, name_in)){
         getline(in, acc_num_str);
         getline(in, acc_type_str);
         getline(in, balance_str);
         
         acc_num_in = atoi(acc_num_str.c_str());
         acc_type_in = atoi(acc_type_str.c_str());
         balance_in = atoi(balance_str.c_str());
         
         accounts.push_back(Account(name_in, acc_num_in, acc_type_in, balance_in));
         //cout << "Account successfully added.\n";
         return;
      }
   }
   
   in.close();
}

void AccountManager::saveAccounts(){
   ofstream out;
   out.open((char*)accountFile.c_str());
   
   if(out.fail()){
      cout << "The file cannot be opened. The acccounts have not been saved.\n";
      return;
   }
   
   else{
      for(int i = 0; i < accounts.size(); i++){
         out << accounts[i].name << endl;
         out << accounts[i].acc_num << endl;
         out << accounts[i].acc_type << endl;
         out << accounts[i].balance << endl;
      }
   }
   out.close();
}
System::System(){
   choice = "0";
   current = "";
   idle = true;
   standby();
}
void System::standby(){
   string username, password;
   while(idle){
      
      cout << "===========================================================\n";
      cout << "|        Welcome to the Auburn Branch of Tiger Bank!      |\n";
      cout << "===========================================================\n";
      cout << "1.) Login\n";
      cout << "2.) Quit\n";
      cout << "\tPlease choose an option: ";
      cin.clear();
      cin >> choice;
      cout << endl;
      while (choice != "1" && choice != "2"){
         cout << "Invalid input. Please try again.\n";
         cout << "1.) Login\n";
         cout << "2.) Quit\n";
         cout << "\tPlease choose an option: ";
         cin.clear();
         cin >> choice;
         cout << endl;
      }
      if (choice == "1"){
         cout << "===========================================================\n";
         cout << "|        Login to Access the Teller Terminal System       |\n";
         cout << "===========================================================\n";
         cout << "User Name: ";
         cin.clear();
         cin >> username;
         cout << endl;
         cout << "Password: ";
         cin.clear();
         cin >> password;
         cout << endl;
         if(username == "" || password == ""){
            cout << "The username or password is blank. Login falied.\n";
         }
         
         else if (employeeController.verify(username, password)){
            current = username;
            idle = false;
         }
         
         else {
            cout << "The username or password is incorrect.\n";
         }
      }
      
      else {
         cout << "Are you sure you want to quit?\n";
         cout << "1.) Yes\n";
         cout << "2.) No\n";
         cout << "\tPlease select an option: ";
         cin.clear();
         cin >> choice;
         while(choice != "1" && choice != "2"){
            cout << "Please enter valid input only.";
            cout << "Are you sure you want to quit?\n";
            cout << "1.) Yes\n";
            cout << "2.) No\n";
            cout << "\tPlease select an option: ";
            cin.clear();
            cin >> choice;
         }
         if (choice == "1"){
            idle = false;
            return;
         }  
      }
   }
   
   if(employeeController.verifyAdmin(current)){
      adminScreen(current, password);
   }
   else if(employeeController.verify(current)){
      branchScreen();
   }
   else{
      idle = true;
      standby();
   }
}

void System::adminScreen(string username, string password){
   char choice;
   char role;
   string new_pass;
   while(!idle){
      cout << "===========================================================\n";
      cout << "|      Teller Terminal System - System Administration     |\n";
      cout << "===========================================================\n";
      cout << "1.) Client and Account Management\n";
      cout << "2.) Add a branch staff member\n";
      cout << "3.) Delete a branch staff member\n";
      cout << "4.) Display branch staff\n";
      cout << "5.) Change Password\n";
      cout << "6.) Quit\n";
      cout << "\tPlease choose an option: ";
      cin.clear();
      cin >> choice;
      while(choice != '1' && choice != '2' && choice != '3' && choice != '4' && choice != '5' && choice != '6') {
         cout << "Please enter a valid choice.\n";
         cout << "1.) Client and Account Management\n";
         cout << "2.) Add a branch staff member\n";
         cout << "3.) Delete a branch staff member\n";
         cout << "4.) Display branh staff\n";
         cout << "5.) Change Password\n";
         cout << "6.) Quit\n";
         cout << "\tPlease choose an option: ";
         cin.clear();
         cin >> choice; 
         cout << endl;  
      } 
      switch (choice) {
         case '1':
            clientManager();
            break;
         
         case '2':
            cout << "User Name: ";
            cin.clear();
            cin >> username;
            cout << endl;
            cout << "Password: ";
            cin.clear();
            cin >> password;
            cout << endl;
            cout << "Role(1 - Administrator; 2 - Branch Staff): ";
            cin.clear();
            cin >> role;
            cout << endl;
            while (role != '1' && role != '2'){
               cout << "Invalid input. Please try again.\n";
               cout << "Role(1 - Administrator; 2 - Branch Staff): ";
               cin.clear();
               cin >> role;
               cout << endl;
            }
            if(role == '1'){
               if(employeeController.addEmployee(username, password, true)){
                  cout << "A new branch employee has been added successfully.\n";
                  cout << "User Name: " << username << "    Role: System Administrator\n";
               }
               else {
                  cout << "Failed to add employee.\n";
               }
            }
            else {
               if(employeeController.addEmployee(username, password, false)){
                  cout << "A new branch employee has been added successfully.\n";
                  cout << "User Name: " << username << "    Role: Branch Staff\n";
               }
               else {
                  cout << "Failed to add employee.\n";
               }
            }
            cout << "Press any key to continue...";
            cin.ignore().get();
            cout << endl;
            break;  
         case '3': //Deleting a member
            char confirm;
            cout << "Delete a user - User Name: ";
            cin.clear();
            cin >> username;
            cout << endl;
            cout << "1.) Confirm\n";
            cout << "2.) Cancel\n";
            cin.ignore();
            cin >> confirm;
            cout << endl;
            while(confirm != '1' && confirm != '2'){
               cout << "Invalid input. Please try again.\n";
               cout << "1.) Confirm\n";
               cout << "2.) Cancel\n";
               cin.ignore();
               cin >> confirm;
               cout << endl;
            }
            if(confirm == '1'){
               if(employeeController.verify(username)){
                  if(employeeController.deleteEmployee(username)){
                     cout << "User " << username << " was deleted successfully.\n";
                  }
                  else {
                     cout << "The deletion was unsuccessful.\n";
                  }
               }
               else {
                  cout << "The user: " << username << " does not exist in our current records.\n";
               }  
            }
            cout << "Press any key to continue...";
            cin.ignore().get();
            cout << endl;
            break;
         case '4': // Display branch staff
            employeeController.display();
            cout << "Press any key to continue...";
            cin.ignore().get();
            cout << endl;
            break;
         case '5': // change password
            cout << "New Password: ";
            cin.clear();
            cin >> new_pass;
            cout << endl;
            while(new_pass == password){
               cout << "Error! Your new password must be different from your current passsword.\n";
               cout << "New Password: ";
               cin.clear();
               cin >> new_pass;
               cout << endl;
            }
            if(employeeController.changePassword(username, password, new_pass)){
               cout << "Password successfully changed.\n";
            }
            else {
               cout << "Password change failed.\n";
            }
            cout << "Press any key to continue...";
            cin.ignore().get();
            cout << endl;
            break;
         case '6': // exit
            current = "";
            idle = true;
            break;
         
         default:
            cout << "Invalid input.\n"; // Should never get here....
         
      }
   }
   standby();
}

void System::branchScreen(){
   while(!idle){
      char choice, choice2;
      string new_pass;
      string old_pass;
      cout << "===========================================================\n";
      cout << "|            Teller Terminal System - Branch Staff        |\n";
      cout << "===========================================================\n";
      cout << "1.) Client and Account Management\n";
      cout << "2.) Change Password\n";
      cout << "3.) Exit\n";
      cin.clear();
      cin >> choice;
      cout << endl;
      while(choice != '1' && choice != '2' && choice != '3'){
         cout << "Invalid input. Please try again.\n";
         cout << "1.) Client and Account Management\n";
         cout << "2.) Change Password\n";
         cout << "3.) Exit\n";
         cin.clear();
         cin >> choice;
         cout << endl;
      }
      if(choice == '1'){
         clientManager();
      }
      else if(choice == '2'){
         cout << "Current Password: ";
         cin.clear();
         cin >> old_pass;
         cout << "New Password: ";
         cin.clear();
         cin >> new_pass;
         cout << endl;
         while(new_pass == old_pass){
            cout << "Error! Your new password must be different from your current passsword.\n";
            cout << "New Password: ";
            cin.clear();
            cin >> new_pass;
            cout << endl;
         }
         if(employeeController.changePassword(current, old_pass, new_pass)){
            cout << "Password successfully changed.\n";
         }
         else {
            cout << "Password change failed.\n";
         }
         cout << "Press any key to continue...";
         cin.ignore().get();
         cout << endl; 
      }
      else {
         cout << "Are you sure you want to log out?\n";
         cout << "1.) Yes\n";
         cout << "2.) Cancel\n";
         cin.clear();
         cin >> choice2;
         cout << endl;
         while(choice2 != '1' && choice2 != '2'){
            cout << "Invalid input. Please try again.\n";
            cout << "Are you sure you want to log out?\n";
            cout << "1.) Yes\n";
            cout << "2.) Cancel\n";
            cin.clear();
            cin >> choice2;
            cout << endl;
         }
         if(choice2 == '1'){
            current = "";
            idle = true;
         }
      }
   }
   standby();
}

void System::clientManager(){
   bool cont = true;
   char choice;
   string name_in, address_in, employer_in, ssn_in, income_in;
   int account_in;
   int acc_type_in;
   int balance_in;
   int choice3;
   while(cont){
      cout << "=============================================================\n";
      cout << "|   Teller Terminal System - Client and Account Management  |\n";
      cout << "=============================================================\n";
      cout << "1.) Add a client\n";
      cout << "2.) Add an account\n";
      cout << "3.) Edit Client Information\n";
      cout << "4.) Manage an account\n";
      cout << "5.) Save Client and Account Information\n";
      cout << "6.) Exit\n";
      cout << "Please choose an option: ";
      cin.clear();
      cin >> choice;
      cout << endl;
      while(choice != '1' && choice != '2' && choice != '3' && choice != '4' && choice != '5' && choice != '6'){
         cout << "Invalid input. Please try again.";
         cout << "1.) Add a client\n";
         cout << "2.) Add an account\n";
         cout << "3.) Edit Client Information\n";
         cout << "4.) Manage an account\n";
         cout << "5.) Save Client and Account Information\n";
         cout << "6.) Exit\n";
         cin.clear();
         cin >> choice;
         cout << endl;
      }
      switch (choice){
         case '1': //add a client
            cout << "A new client will be added.\n";
            cout << "Client Name: ";
            cin.ignore();
            getline(cin, name_in);
            cout << endl;
            cout << "Address: ";
            cin.clear();
            getline(cin, address_in);
            cout << endl;
            cout << "Social Security Number: ";
            cin.clear();
            getline(cin, ssn_in);
            cout << endl;
            cout << "Employer: ";
            cin.clear();
            getline(cin, employer_in);
            cout << endl;
            cout << "Annual Income: ";
            cin.clear();
            cin >> income_in;
            cout << endl;
            if(clientController.add_client(name_in, address_in, employer_in, ssn_in, income_in)){
               cout << "The client was successfully added!\n";
            } // else case covered in the function.
            cout << "Press any key to continue...";
            cin.ignore().get();
            cout << endl;
            break;
            
         case '2'://add an account
            
            cout << "Choose a client: ";
            cin.ignore();
            getline(cin, name_in);
            cout << endl;
            if(clientController.isClient(name_in)){
               cout << "A new account will be created for " << name_in << endl;
               cout << "Account number: ";
               cin.clear();
               cin >> account_in;
               cout << endl;
               cout << "Account Type (0 for checking and 1 for savings): ";
               cin.clear();
               cin >> acc_type_in;
               cout << endl;
               while(acc_type_in != 0 && acc_type_in != 1){
                  cout << "Invalid input. Please try again.\n";
                  cout << "Account Type (0 for checking and 1 for savings): ";
                  cin.clear();
                  cin >> acc_type_in;
                  cout << endl;
               }
               cout << "Balance: ";
               cin.ignore();
               cin >> balance_in;
               cout << endl;
               while(balance_in < 0){
                  cout << "You cannot have an account with a negative balance. Please try again.\n";
                  cout << "Balance: ";
                  cin.ignore();
                  cin >> balance_in;
                  cout << endl;
               }
               if(accountController.addAcc(name_in, account_in, acc_type_in, balance_in)){
                  cout << "Account successfully created for " << name_in << endl;
               }
            }
            else {
               cout << name_in << " does not exist.\n";
            }
            cout << "Press any key to continue...";
            cin.ignore().get();
            cout << endl;
            break; 
            
         case '3': //edit client information
            
            cout << "Chose a client: ";
            cin.ignore();
            getline(cin, name_in);
            cout << endl;
            if(clientController.isClient(name_in)){
               if(clientController.print_client(name_in)){
                  cout << "Client " << name_in << "\'s information will be updated...\n";
                  cout << "1.) Confirm\n";
                  cout << "2.) Cancel\n";
                  cout << "Please choose an option: ";
                  cin.clear();
                  cin >> choice3;
                  cout << endl;
                  while(choice3 != 1 && choice3 != 2){
                     cout << "Invalid input. Please try again.\n";
                     cout << "1.) Confirm\n";
                     cout << "2.) Cancel\n";
                     cout << "Please choose an option: ";
                     cin.clear();
                     cin >> choice3;
                     cout << endl;
                  }
                  if(choice3 == 1){
                     cout << "Address: ";
                     cin.ignore();
                     getline(cin, address_in);
                     cout << endl;
                     cout << "Social Security Number: ";
                     cin.clear();
                     cin >> ssn_in;
                     cout << endl;
                     cout << "Employer: ";
                     cin.ignore();
                     getline(cin, employer_in);
                     cout << endl;
                     cout << "Annual Income: ";
                     cin.clear();
                     cin >> income_in;
                     cout << endl;
                     if(clientController.edit_client(name_in, address_in, employer_in, ssn_in, income_in)){
                        cout << "Client " << name_in << "\'s information was updated!\n";
                     }
                     
                  }
                  
               }
            }
            cout << "Press any key to continue...\n";
            cin.ignore().get();
            cout << endl;
            break;
          
         case '4': // manage an account.
            
            cout << "Which account will be managed? ";
            cin.clear();
            cin >> account_in;
            cout << endl;
            if(accountController.manageAcc(account_in)){
               cout << "Account balance updated.\n";
            }
            else{
               cout << "The account number you entered does not exist.\n";
            }
              
            cout << "Press any key to continue...\n";
            cin.ignore().get();
            cout << endl;
            break; 
            
         case '5':
            clientController.saveClients();
            accountController.saveAccounts();
            cout << "Client information has been saved in the client - info file\n";
            cout << "Account information has been saved in the account - info file\n";
            cout << "Press any key to continue...";
            cin.ignore().get();
            cout << endl;
            break;
         case '6':
            cont = false;
            break;
        
      }
   }
   standby();
}

int main(){
   System run;
   run.standby();
   return 0;
}