// Demonstrate use of KS test
#include <iostream> 
#include <algorithm> //std::sort
#include <cmath>
#include <TRandom3.h>
#include <vector>
//using namespace std;

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

   const unsigned int N = 100;

   TRandom3 *rg = new TRandom3(4369);
   std::vector<double> v;
   double xi;
   for (int i=0;i<N;i++){
      xi = rg->Rndm();
      v.push_back(xi);
      std::cout << i << " " << xi << " " << v[i] << std::endl;
   }

// Use std::sort algorithm on vector
   std::sort(v.begin(),v.end());

   std::cout << "and after sorting " << std::endl;

   for (int i=0;i<N;i++){
      std::cout << i << " " << v[i] << std::endl;
   }

// Now calculate KS test D value
   double datacdf = 0.0;
   double modelcdf;
   double Dmax = 0.0;
   for (int i=0;i<N;i++){
      modelcdf = v[i];             // For Uniform(0,1), F(x) = x
      datacdf += 1.0/double(N);
      double Dtest = fabs(datacdf-modelcdf);
      if(Dtest>Dmax)Dmax = Dtest;
      std::cout << i << " " << datacdf << " " << modelcdf << " " << Dtest << std::endl;
   }
   std::cout << "Dmax of " << Dmax << std::endl;
// Normalized value, z.  
   double z = (sqrt(double(N)) + 0.12 + (0.11/sqrt(double(N))))*Dmax;
   std::cout << "z = " << z << std::endl;
// Calculate "p-value". Small number = bad fit.
   std::cout << "qks(z) = " << qks(z) << std::endl;

}
