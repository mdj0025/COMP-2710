// name: Michael Johnson, mdj0025
// partner: none
// filename: hw04.cpp
// due date: 09/21/2018
// collaboration: I did not use any external sources for this project.
// My code can be compiled and ran without error using jGRASP.
// problem: Write a program that reads files by user input and sorts + combines them into a new file.

// Imported Libraries
#include <fstream>
#include <iostream>
#include <stdlib.h>
#include <assert.h>

using namespace std;

// Constants
const int MAX_SIZE = 100;

// Method Headers
int readFile(int inputArray[], ifstream& instream);

int sort(int input_Array1[], int Array1_size, int input_Array2[], int Array2_size, int outputArray[]);

void writeFile(int outputArray[], int outputArray_size, string fileName);

void test_readFile(void);

void test_sortFile(void);

void test_writeFile(void);


// Main Unit Driver
int main() {
   test_readFile();
   test_sortFile();
   test_writeFile();
   
   cout << "Welcome to Michael Johnson's sorting program ***\n";
   
   int iArray1[MAX_SIZE];
   int iArray1_size;
   int iArray2[MAX_SIZE];
   int iArray2_size;
   int oArray[MAX_SIZE];
   int oArray_size;
   
   
   string fileName;
   ifstream inStream;
   
   cout << ("Enter the first input file name: ");
   cin >> fileName;
   cout << endl;
  
   inStream.open((char*)fileName.c_str());
   
   if (inStream.fail()) {
      cout << "The program failed to properly open the file.";
      exit(1);
   }
  
   iArray1_size = readFile(iArray1, inStream);
   inStream.close();
  
   cout << "The list of " << iArray1_size << " numbers in file ";
   cout << fileName << " is:\n";
  
   for (int i = 0; i < iArray1_size; i++) {
      cout << iArray1[i] << endl;
   }
   
   string fileName2;
   ifstream inStream2;
   cout << "Enter the second input file name: ";
   cin >> fileName2;
   cout << endl;
   
   inStream2.open((char*)fileName2.c_str());
   
   if (inStream2.fail()) {
      cout << "The program failed to properly open the file.";
      exit(1);
   }
   
   iArray2_size = readFile(iArray2, inStream2);
   inStream2.close();
   cout << "The list of " << iArray2_size << " numbers in file ";
   cout << fileName2 << " is:" << endl;
   for(int i = 0; i < iArray2_size; i++) {
      cout << iArray2[i] << endl;
   }
   
   oArray_size = sort(iArray1, iArray1_size, iArray2, iArray2_size, oArray);
   
   cout << "The sorted list of " << oArray_size << " numbers is ";
   for (int i = 0; i < oArray_size; i++) {
      cout << oArray[i] << " ";
   }
   cout << "\nEnter the output file name: ";
   string file;
   
   cin >> file;
   writeFile(oArray, oArray_size, file);
   
   cout << "*** Please check the new file - " << file << " ***";
   cout << "\n*** Goodbye. ***";
   
   return 0;
}

// This method reads a file from user input.
int readFile(int inputArray[], ifstream& inStream){
   
   int index = 0;
   inStream >> inputArray[index];
   while(! inStream.eof()) {
      if(index >= MAX_SIZE - 1) {
         return -1;
      }
      index++;
      inStream >> inputArray[index];
   }
   
   return index + 1;
}

// This method takes in two arrays and sorts + combines them into a new array.
int sort(int input_Array1[], int Array1_size, int input_Array2[], int Array2_size, int outputArray[]) {
  
   bool complete = false;
   int i = 0;
   int j = 0;
   int k = 0;
   while (!complete) {
      if (i < Array1_size && j < Array2_size) {
         if (input_Array1[i] < input_Array2[j]) {
            outputArray[k] = input_Array1[i];
            i++;
         }
         
         else if (input_Array1[i] > input_Array2[j]) {
            outputArray[k] = input_Array2[j];
            j++;
         }
         //If they are equal
         else {
            outputArray[k] = input_Array1[i];
            i++;
         }
      }
      
      else if(i < Array1_size) {
         outputArray[k] = input_Array1[i];
         i++;
      }
      
      else if(j < Array2_size) {
         outputArray[k] = input_Array2[j];
         j++;
      }
      else {
         complete = true;
         return k;
      }
      k++;
   }
   return -1;
}

// This method writes the sorted array into a new file.
void writeFile(int outputArray[], int outputArray_size, string fileName) {
   
   ofstream out;
   out.open((char*)fileName.c_str());
   if (out.fail()) {
      cout << "Error: could not write file";
   }
   else{
      for (int i = 0; i < outputArray_size; i++) {
         if (i == outputArray_size - 1){
            out << outputArray[i];
         }
         else {
         out << outputArray[i] << endl;
         }
      }
   }
   out.close();
}

// *************** Test drivers *************** 
void test_readFile(void) {
  
   // Normal Read File Test
   cout << "*** Unit Test Cases ***\n";
   cout << "Unit Test Case 1: Function Name - readFile()\n";
   cout << "\t\tCase 1.1: This case tests the readFile() method with a normal file.\n";
   string fileName = "sample1.txt";
   int inputArray1[MAX_SIZE];
   ifstream inputStream;
   inputStream.open((char*)fileName.c_str());
   assert(!inputStream.fail());
   
   int size = readFile(inputArray1, inputStream);
   inputStream.close();
   assert(size == 8);
   assert(inputArray1[0] == 10);
   assert(inputArray1[1] == 11);
   assert(inputArray1[2] == 12);
   assert(inputArray1[3] == 13);
   assert(inputArray1[4] == 30);
   assert(inputArray1[5] == 55);
   assert(inputArray1[6] == 62);
   assert(inputArray1[7] == 69);
   cout << "\t\tCase 1.1 passed.\n";
   
   //Non-existing File
   cout << "\t\tCase 1.2: This test case tests the readFlie() method with a file that does not exist.\n";
   string falseFile = "1234.txt";
   int inputArray2[MAX_SIZE];
   ifstream inputStream2;
   inputStream2.open((char*)falseFile.c_str());
   assert(inputStream2.fail());
   inputStream2.close();
   cout << "\t\tCase 1.2 passed\n";
   
   //File too large
   cout << "\t\tCase 1.3: This test case tests the readFile() method with a file that is";
   cout << " larger than the allowed size.\n";
   string largeFile = "large.txt";
   int inputArray3[MAX_SIZE];
   ifstream inputStream3;
   inputStream3.open((char*)largeFile.c_str());
   int inputArray3_size = readFile(inputArray3, inputStream3);
   inputStream3.close();
   assert(inputArray3_size == -1);
   cout << "\t\tCase 1.3 passed\n";
   cout << "\t\t...\n";
   
   cout << "Press any key to continue ...\n";
   cin.ignore().get(); //Pause Command for Linux Terminal
}

void test_sortFile(void) {
  
   // Tests the sort file and asserts its correctness.
   cout << "Unit Test Case 2: Function Name - sort()\n";
   cout << "\t\tCase 2.1: Tests the sort() method and asserts that it properly sorts two arrays.\n";
   int inputArray1[MAX_SIZE] = {1, 2, 3, 12, 33, 56, 78, 92, 101, 400};
   int inputArray2[MAX_SIZE] = {3, 6, 9, 53, 76, 92, 100, 200};
   int inputArray1_size = 10;
   int inputArray2_size = 8;
   int outputArray[MAX_SIZE];
   int oArray_Size = sort(inputArray1, inputArray1_size, inputArray2, inputArray2_size, outputArray);
  
   assert(oArray_Size == 18);
   assert(outputArray[0] == 1);
   assert(outputArray[1] == 2);
   assert(outputArray[2] == 3);
   assert(outputArray[3] == 3);
   assert(outputArray[4] == 6);
   assert(outputArray[5] == 9);
   assert(outputArray[6] == 12);
   assert(outputArray[7] == 33);
   assert(outputArray[8] == 53);
   assert(outputArray[9] == 56);
   assert(outputArray[10] == 76);
   assert(outputArray[11] == 78);
   assert(outputArray[12] == 92);
   assert(outputArray[13] == 92);
   assert(outputArray[14] == 100);
   assert(outputArray[15] == 101);
   assert(outputArray[16] == 200);
   assert(outputArray[17] == 400);
   cout << "\t\tCase 2.1 passed.\n";
   
   // Tests sort with one empty array
   cout << "\t\tCase 2.2: This test passes in an empty array and a normal array.\n";
   int inputArray3[MAX_SIZE] = {};
   int inputArray3_size = 0;
   int inputArray4[MAX_SIZE] = {1, 2, 3, 4, 5, 6};
   int inputArray4_size = 6;
   int oArray2[MAX_SIZE];
   
   int oArray_size2 = sort(inputArray3, inputArray3_size, inputArray4, inputArray4_size, oArray2);
   assert(oArray_size2 == 6);
   assert(oArray2[0] == 1);
   assert(oArray2[1] == 2);
   assert(oArray2[2] == 3);
   assert(oArray2[3] == 4);
   assert(oArray2[4] == 5);
   assert(oArray2[5] == 6);
   
   cout << "\t\tCase 2.2 passed\n";
   cout << "\t\t...\n";
   cout << "Press any key to continue ...\n";
   cin.ignore().get(); //Pause Command for Linux Terminal  
}

void test_writeFile(void){
  
   //Ensures the file is written correctly
   cout << "Unit Test Case 3: Function - writeFile()\n";
   cout << "\t\tCase 3.1: ensures the write file properly writes the data to a new file.\n";
   int outputArray1[MAX_SIZE] = {1, 3, 5, 7, 9};
   int outputArray1_size = 5;
   string outputFile_name = "output.txt";
   writeFile(outputArray1, outputArray1_size, outputFile_name);
   
   string fileName = "output.txt";
   int inputArray2[MAX_SIZE];
   ifstream inStream;
   inStream.open((char*)fileName.c_str());
   assert(!inStream.fail());
   int size = readFile(inputArray2, inStream);
   inStream.close();
   
   assert(size == 5);
   assert(inputArray2[0] == 1);
   assert(inputArray2[1] == 3);
   assert(inputArray2[2] == 5);
   assert(inputArray2[3] == 7);
   assert(inputArray2[4] == 9);
   cout << "\t\tCase 3.1 passed.\n";
   cout << "\t\t...\n";
   
   cout << "Press any key to continue ...\n";
   cin.ignore().get(); //Pause Command for Linux Terminal
}