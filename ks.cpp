// Functions for interpreting the normalized KS statistic
// Based on code from Ch 6.14.12 of NR 3rd edition.
#include <iostream>
#include <cmath>
#include <iomanip>
using namespace std;

double pks(double z) {
// cdf of the normalized KS distribution (see Ch. 6.14.12 of NR)
		if (z < 0.0) throw("bad z in KSdist");
		if (z == 0.0) return 0.0;
		if (z < 1.18) {
			double y = exp(-1.23370055013616983/(z*z));
			return 2.25675833419102515*sqrt(-log(y))
				*(y + pow(y,9) + pow(y,25) + pow(y,49));
		} else {
			double x = exp(-2.0*z*z);
			return 1.0 - 2.0*(x - pow(x,4) + pow(x,9));
		}
}
double qks(double z) {
// complementary cdf of the normalized 
// KS distribution (see Ch. 6.14.12 of NR)
		if (z < 0.0) throw("bad z in KSdist");
		if (z == 0.0) return 1.0;
		if (z < 1.18) return 1.0-pks(z);
		double x = exp(-2.0*z*z);
		return 2.0*(x - pow(x,4) + pow(x,9));
}

int main(){

// Here we evaluate the p-values for z values in the range [0.0,3.0]
// (Small p-value = null hypothesis disfavored)

   double z;
   for (int i=0;i<=30;i++){
      z = double(i)*0.1;
      cout << "z = " << setw(3) << z << ", Qks(z) = " << qks(z) << endl;
   }

}
