#include "ARX.h"

int main() {
	ARX x(1, 1, 1);
	x.wypiszStopnie();
	//x.wpiszParametry();
	std::vector<double> wektorA = { 1, 0.8 };
	std::vector<double> wektorB = { 0.5, -0.7 };
	x.wpiszParametry(&wektorA, &wektorB);
	
	std::vector<std::vector<double>> parametry;
	parametry = x.wypiszParametry();

	x.wypiszWielomiany();
	std::cout << "Symulacja: \n";
	x.symuluj(1);
	x.symuluj(1);
	x.symuluj(1);
	x.symuluj(1);

	return 0;
}


