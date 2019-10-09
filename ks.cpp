// Functions for interpreting the normalized KS statistic
// Based on code from Ch 6.14.12 of NR 3rd edition.
#include <iostream>
#include <cmath>
#include <iomanip>
#include "ks.h"
using namespace std;

int main(){

// Here we evaluate the p-values for z values in the range [0.0,3.0]
// (Small p-value = null hypothesis disfavored)

   double z;
   for (int i=0;i<=30;i++){
      z = double(i)*0.1;
      cout << "z = " << setw(3) << z << ", Qks(z) = " << qks(z) << endl;
   }

}
