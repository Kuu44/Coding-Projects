#include<iostream>
#include<iomanip>
#include<vector>
#define GGMU 20

using namespace std;

class Matrix {
private:
	int n;
	vector<vector<float>> A, L, U;
	vector<float> B, Y;
public:
	void InputOrder() {
		cout << "\nEnter the order of matrix";
		cin >> n;
	}
	void InputData() {
		/*float x;
		for (int i = 0; i < n; i++) {
			vector<float> temp;
			for (int j = 0; j < n; j++) {
				cout << "Enter the value of A[" << i << "][" << j << "]:";
				cin >> x;
				temp.push_back(x);
			}
			A.push_back(temp);
		}
		for (int i = 0; i < n; i++) {
			cout << "Enter the value of B[" << i << "]:";
			cin >> x;
			B.push_back(x);
		}*/
		vector<float> Aa, Ab, Ac, Ad;
		Aa.push_back(1);
		Aa.push_back(1);
		Aa.push_back(1);
		Aa.push_back(1);
		Ab.push_back(1);
		Ab.push_back(2);
		Ab.push_back(3);
		Ab.push_back(-4);
		Ac.push_back(3);
		Ac.push_back(1);
		Ac.push_back(1);
		Ac.push_back(-1);
		Ad.push_back(1);
		Ad.push_back(3);
		Ad.push_back(-3);
		Ad.push_back(-2);

		A.push_back(Aa);
		A.push_back(Ab);
		A.push_back(Ac);
		A.push_back(Ad);

		B.push_back(10);
		B.push_back(-5);
		B.push_back(6);
		B.push_back(0);
	}
	void Print(vector<vector<float>> vector) {
		for (int i = 0; i < vector.size(); i++) {
			for (int j = 0; j < vector.at(i).size(); j++)
				cout << setw(10) << vector.at(i).at(j) << "\t";
			cout << endl;
		}
	}
	void Print(vector<float> vector) {
		for (int i = 0; i < vector.size(); i++)
			cout << setw(10) << vector.at(i) << "\n";
		cout << endl;
	}
	void CheckPivot() {
		for (int i = 0; i < n; i++) {
			int max = i;
			for (int k = i + 1; k < n; k++)
				if (A.at(k).at(i) > A.at(max).at(i))
					max = k;
			if (max != i) {
				for (int j = 0; j < n; j++) {
					float temp = A.at(i).at(j);
					A.at(i).at(j) = A.at(max).at(j);
					A.at(max).at(j) = temp;
				}
				float temp = B.at(i);
				B.at(i) = B.at(max);
				B.at(max) = temp;
			}
		}
	}
	void MakeL() {
		int count1 = 0, count2 = 0;
		for (int i = 0; i < n; i++) {
			vector<float> tempU, tempL;
			for (int j = 0; j < n; j++) {
				if (i <= j) {
					float sum = 0;
					for (int k = 0; k < i; k++) 
						if ((i < L.size()) && (k < U.size())) 
							sum += L.at(i).at(k) * U.at(k).at(j);
					tempU.push_back(A.at(i).at(j) - sum);
					if (i == j) tempL.push_back(1);
					else tempL.push_back(0);
				}
				else {
					float sum = 0;
					for (int k = 0; k < j; k++) 
						if ((i < L.size()) && (k < U.size())) 
							sum += L.at(i).at(k) * U.at(k).at(j);
					tempL.push_back((A.at(i).at(j) - sum) / U.at(j).at(j));
					tempU.push_back(0);
				}
			}
			U.push_back(tempU);
			L.push_back(tempL);
		}
	}
	void ForwardSubstitution() {
		cout << "If UX=Y then,\nLY=B\n";
		for (int i = 0; i < n; i++) {
			float sum = 0;
			for (int j = 0; j < i; j++)
				if (i < L.size())
					sum += L.at(i).at(j) * Y.at(j);
			Y.push_back(B.at(i) - sum);
		}
		cout << "From forward substitution, Matrix becomes:\n";
		Print(Y);
	}
	void ReverseSubstitution() {
		cout << "Here, UX=Y then,\n";
		for (int i = n; i > 0; i--) {
			for (int j = i + 1; j < n; j++)
				if (i < U.size())
					Y.at(i) = Y.at(i) - Y.at(j) * U.at(i).at(j);
			if (i < U.size())
				Y.at(i) = Y.at(i) / U.at(i).at(i);
		}
		cout << "From backward substituion, Matrix X becomes:\n";
		Print(Y);
	}
	friend void FactorisationSolve(Matrix M);
};
void FactorisationSolve(Matrix M) {
	//Input
	cout << "Matrix A becomes :\n";
	M.Print(M.A);
	cout << "Matrix B becomes:\n";
	M.Print(M.B);
	//Swap pivot elements
	M.CheckPivot();
	//Decompose LU
	cout << "If A=LU then\n";
	M.MakeL();
	cout << "Matrix L becomes:\n";
	M.Print(M.L);
	cout << "Matrix U becomes:\n";
	M.Print(M.U);
	/*Substitution for Y*/ M.ForwardSubstitution();
	/*Substitution for X*/ M.ReverseSubstitution();
	//Print Output
	cout << "\n\nThe result is:\n";
	for (int i = 0; i < M.n; i++)
		cout << setw(10) << "X[" << i << "]=" << M.Y.at(i) << endl;
}
int main34() {
	Matrix K;
	K.InputOrder();
	K.InputData();
	FactorisationSolve(K);
	return GGMU;
}
