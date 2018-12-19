// name: Michael Johnson, mdj0025
// partner: none
// filename: hw02.cpp
// due date: 09/07/18
// collaboration: I did not use any external sources for this assignment.
// problem: Write a program to address how long it will take to 
//    pay off a loan with interest. Specifically, in this case, a car stereo loan.

#include <iostream>
#include <iomanip> //std:setw
using namespace std;

int main() {
   cout.setf(ios::fixed);
   cout.setf(ios::showpoint);
   cout.precision(2);
   
   double loan_amount, annual_interest, monthly_interest_rate, monthly_payment, monthly_interest;
   double monthly_interest_initial, principal, interest_rate_percent, total_interest;
   int month = 0;
   
   cout << "Loan Amount: ";
   cin >> loan_amount;
   
   cout << "Interest Rate (% per year): ";
  

   cin >> annual_interest;
   
   // This conditional statement checks to see if the interest is positive.
   if (annual_interest < 0){
      while(annual_interest < 0) {
         cout << "Please input a positive interest rate (% per year): ";
         cin >> annual_interest;
      }
   }
   
   cout << "Monthly Payments: ";
   cin >> monthly_payment;
   
   monthly_interest_rate = ((annual_interest / 12) / 100);
   interest_rate_percent = annual_interest / 12;
   monthly_interest_initial = monthly_interest_rate * loan_amount;
   
   // This conditional statement checks to see if the payment is larger than the monthly interest.
   if(monthly_payment - monthly_interest_initial < 0){
      while(monthly_payment - monthly_interest_initial < 0) {
         cout << "Please input a larger monthly payment: ";
         cin >> monthly_payment;
      }
   }
   
   cout << "******************************************************" <<
       "\n\t\t  Amortization Table" <<
       "\n******************************************************" <<
       "\nMonth   Balance Payment Rate    Interest Principle";

   
   cout << "\n"<< month <<"       $" << loan_amount << " N/A    N/A     N/A      N/A\n";
  
  // This loop calculates the output for the loan. 
  while(loan_amount > monthly_payment) {
      month++;
      monthly_interest = loan_amount * monthly_interest_rate;
      principal = monthly_payment - monthly_interest;
      
      loan_amount = loan_amount - principal;
      cout << left << setw(8) << month;
      cout << "$" << left << setw(8) << loan_amount;
      cout << "$" << left << setw(6) << monthly_payment; 
      cout << left << setw(8) << interest_rate_percent; 
      cout << "$" << left << setw(8) <<  monthly_interest;
      cout << "$" << principal << "\n";
      total_interest += monthly_interest;
  }
 
  // This section calculates the output for when the monthly payment is larger than the amount owed.
  month++;
  monthly_interest = loan_amount * monthly_interest_rate;
  monthly_payment = loan_amount + monthly_interest;
  principal = loan_amount;
  loan_amount = 0.0;
  total_interest += monthly_interest;
 
  cout << left << setw(8) << month;
  cout << "$" << left << setw(8) << loan_amount;
  cout << "$" << left << setw(6) << monthly_payment; 
  cout << left << setw(8) << interest_rate_percent; 
  cout << "$" << left << setw(8) <<  monthly_interest;
  cout << "$" << principal;
 
 
 
  cout << "\n******************************************************\n";
  cout << "\nIt takes " << month << " months to pay off the loan.\n";
  cout << "Total interest paid is: $" << total_interest; 
  return 0;
} 