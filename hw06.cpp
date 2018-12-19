// name: Michael Johnson, mdj0025
// partner: Jordan Cox, jwc0045
// filename: hw06.cpp
// due date: 10/19/2018
// collaboration:
// My code can be compiled and ran without error using jGRASP.
// problem: We were asked to write a class Doctor that would hold the doctor's patients.
#include <fstream>
#include <iostream>
#include <stdlib.h>
#include <assert.h>
#include <string>

#define UNIT_TESTING
using namespace std;
void getUserValues();
typedef string* patientPointer;
class Doctor {
   
   
   public:
   string name;
   int numPatients;
   patientPointer p;
   Doctor(string name_in, int numPatients_in, string patientList[]) {
      name = name_in;
      numPatients = numPatients_in;
      p = patientList;
   }
      
   string getName() {
      return name;
   }
   int get_numPatients() {
      return numPatients;
   }
   patientPointer getPatientList() {
      return p;
   }
   void setName(string Name_in) {
      name = Name_in;
   }
   void setNumPatients(int NumPatients_in) {
      numPatients = NumPatients_in;
   }
   void resetNumPatients() {
      numPatients = 0;
   }
   void delete_patientList() {
      p = NULL;
   }
   Doctor& operator = (const Doctor &d){
      if (this != &d){
         resetNumPatients();
         delete_patientList();
         name = d.name;
         numPatients = d.numPatients;
         if (numPatients != 0) {
            p = new string[numPatients];
            for (int i = 0; i < numPatients; i++){
               p[i] = d.p[i];
            }
         }
      }
         
      return *this;
   }
};

int main() {
   #ifdef UNIT_TESTING

   int num_patients;
   string name_in;
      
   string* p;
   cout << "Test Case 1.1: Testing normal values."<< endl;
   cout << "Please enter the name of the doctor (Enter \"Nick\"): " << endl;
   cin >> name_in;
   cout << endl;
   
   cout << "How many patients would you like to enter? (Enter 2) "<< endl;
   cin >> num_patients;
   cout << "\n";
      
   p = new string[num_patients];
   for (int i = 0; i < num_patients; i++){
      if (i == 0) {
         cout << "Please enter patient " << (i + 1) << "\'s name. (Patient 1's name \"Bob\")" << endl;
      } else if (i ==1) {
         cout << "Please enter patient " << (i + 1) << "\'s name. (Patient 2's Name \"Dylan\")" << endl;
      }
      cin >> p[i];
      cout << "\n";
   }
   Doctor d1 = Doctor(name_in, num_patients, p);
   assert(d1.name == "Nick");
   assert(d1.numPatients == 2);
   assert(d1.p[0] == "Bob");
   assert(d1.p[1] == "Dylan");
   
   cout << "Case 1.1 Passed.\n" << endl;
   cout << "Unit Test 2.1: set and get medium length name." << endl;
   
   d1.setName("Michael");
   assert(d1.getName() == "Michael");
   
   cout << "Case 2.1 Passed." << endl;
   
   cout << "Unit Test 2.2: set and get very long length name." << endl;
   
   d1.setName("Wolfeschlegelsteinhausenbergerdorff");
   assert(d1.getName() == "Wolfeschlegelsteinhausenbergerdorff");
   
   cout << "Case 2.2 Passed." << endl;
   
   cout << "Unit Test 2.3: set and get empty string name." << endl;
   
   d1.setName("");
   assert(d1.getName() == "");
   
   cout << "Case 2.3 Passed." << endl;
   
   cout << "Unit Test 3.1: Test with zero patients" << endl;
   d1.resetNumPatients();
   d1.delete_patientList();
   assert(d1.numPatients == 0);
   cout << "Case 3.1 Passed." << endl;
   
   cout << "Unit Test 3.2: Test with an empty array" << endl;
   assert(d1.p == NULL);
   cout << "Case 3.2 Passed." << endl;
   
   cout << "Unit Test 4.1: Test the number of patients(zero)" << endl;
   d1.setNumPatients(0);
   assert(d1.numPatients == 0);
   cout << "Case 4.1 Passed." << endl;
   
   cout << "Unit Test 4.2: Test the number of patients(medium value)" << endl;
   d1.setNumPatients(10);
   assert(d1.numPatients == 10);
   cout << "Case 4.2 Passed." << endl;
   
   cout << "Unit Test 4.3: Test the number of patients(high-value)" << endl;
   d1.setNumPatients(100000000);
   assert(d1.numPatients == 100000000);
   cout << "Case 4.3 Passed." << endl;
   return 0;
      
   #else
   inputUserValues(); // Driver version for the assignment.
   return 0;
   #endif
}

void inputUserValues() {
   int num_patients;
   string name_in;
      
   string* p;
   cout << "Please enter the name of the doctor: ";
   cin >> name_in;
   cout << endl;
   
   cout << "How many patients would you like to enter?" << endl;
   cin >> num_patients;
   cout << "\n";
      
   p = new string[num_patients];
   for (int i = 0; i < num_patients; i++){
      cout << "Please enter patient " << (i + 1) << "\'s name." << endl;
      cin >> p[i];
      cout << "\n";
   }
   Doctor d1 = Doctor(name_in, num_patients, p);
   
}