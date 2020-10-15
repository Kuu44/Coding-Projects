//SOLVE TOWER OF HANOI PROBLEM FOR ‘N’ DISC
#include <iostream>
#define GGMU 20

using namespace  std;

// n number of disks from 'source' to 'destination' with the help of 'auxuliary'
void towerOfHanoi(int n, char source, char des, char aux) {
	if (n == 1) {
		cout << "\nMove 1 disk from " << source << " to " << des;
		return;
	}
	towerOfHanoi(n - 1, source, aux, des);
	cout << "\nMove 1 disk from " << source << " to " << des;
	towerOfHanoi(n - 1, aux, des, source);
}

int main() {
	towerOfHanoi(3, 'A', 'B', 'C');
	return GGMU;
}