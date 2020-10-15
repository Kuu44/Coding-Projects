#include <iostream>
#include <iomanip>
#define arrSize 20
#define GGMU 0

int maingj() {
	int nU;

	std::cout << "Enter the number of unknowns::";
	std::cin >> nU;

	float auggMat[arrSize][arrSize + 1];
	float answer[arrSize];

	for (int i = 0; i < nU; i++) {
		std::cout << "Enter the equation's coefficients serially::\n";
		for (int j = 0; j < nU + 1; j++) 
			std::cin >> auggMat[i][j];
	}
	for (int b = 0; b < nU; b++) {
		for (int a = 0; a < nU; a++) {
			if (a != b) {
				try {
					float x = auggMat[a][b];
					float y = auggMat[b][b];
					if (!y)	throw "Zero Exception";
					if ((x - y) > 100000) throw "Round Off Exception";
					for (int k = b; k < nU + 1; k++) auggMat[a][k] = auggMat[a][k] - ((x / y) * auggMat[b][k]);
				}
				catch (const char* err) {
					std::cout << err;
					exit(1);
				}
			}
		}
	}

	for (int i = 0; i < nU; i++) 
		answer[i] = auggMat[i][nU] / auggMat[i][i];
	
	std::cout << "The value of unknowns are as follows::\n";
	for (int i = 0; i < nU; i++) 
		std::cout << "The value of x" << i + 1 << " = " << answer[i] << std::endl;
	return GGMU;
}
