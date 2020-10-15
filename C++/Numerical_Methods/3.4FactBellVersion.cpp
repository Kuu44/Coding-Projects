#include<iostream>
#include<iomanip>
#include<vector>
class Matrix
{
private:
	int n;
	std::vector<float> A, B, L, U, Y;
public:
	void getOrder()
	{
		std::cout << "\nEnter the order of matrix: ";
		std::cin >> n;
	}
	void readData()
	{
		/*float x;
		for (int i = 0; i < n; i++)
		{
			for (int j = 0; j < n; j++)
			{
				std::cout << "Enter the value of a[" << i << "][" << j << "] : ";
				std::cin >> x;
				A.push_back(x);
			}
			std::cout << "Enter the value of b[" << i << "] : ";
			std::cin >> x;
			B.push_back(x);
		}*/
		A.push_back(1);
		A.push_back(1);
		A.push_back(1);
		A.push_back(1);
		A.push_back(1);
		A.push_back(2);
		A.push_back(3);
		A.push_back(-4);
		A.push_back(3);
		A.push_back(1);
		A.push_back(1);
		A.push_back(-1);
		A.push_back(1);
		A.push_back(3);
		A.push_back(-3);
		A.push_back(-2);

		B.push_back(10);
		B.push_back(-5);
		B.push_back(6);
		B.push_back(0);
	}
	void printMatrix(std::vector<float> V, int cols)
	{
		std::cout << std::endl;
		for (int i = 0; i < V.size(); i++)
		{
			std::cout << std::setw(10) << V.at(i) << "\t";
			if ((i + 1) % cols == 0)
			{
				std::cout << std::endl;
			}
		}

	}
	void checkPivot()
	{

		for (int i = 0; i < n; i++)
		{
			int max = i;
			for (int k = i + 1; k < n; k++)
			{
				if (A.at(n * k + i) > A.at(n * max + i))
					max = k;
			}
			if (max != i)
			{
				for (int j = 0; j < n; j++)
				{
					float temp = A.at(i * n + j);
					A.at(i * n + j) = A.at(max * n + j);
					A.at(max * n + j) = temp;
				}
				float temp = B.at(i);
				B.at(i) = B.at(max);
				B.at(max) = temp;
			}
		}
	}
	void DoLittle()
	{

		for (int i = 0; i < n; i++)
		{
			for (int j = 0; j < n; j++)
			{
				if (i <= j)
				{
					float sum = 0;
					for (int k = 0; k < i; k++)
					{
						sum = sum + L.at(n * i + k) * U.at(n * k + j);
					}
					U.push_back(A.at(n * i + j) - sum);
					if (i == j)
						L.push_back(1);
					else
						L.push_back(0);

				}
				else
				{
					float sum = 0;
					for (int k = 0; k <= j - 1; k++)
					{
						sum = sum + L.at(n * i + k) * U.at(n * k + j);
					}
					L.push_back((A.at(n * i + j) - sum) / U.at(j * n + j));
					U.push_back(0);
				}

			}
		}

	}
	void fwdSub()
	{
		std::cout << "If UX = Y then," << std::endl << "LY = B " << std::endl;
		for (int i = 0; i < n; i++)
		{
			float sum = 0;
			for (int j = 0; j < i; j++)
			{
				sum = sum + L.at(i * n + j) * Y.at(j);
			}
			Y.push_back(B.at(i) - sum);
		}
		std::cout << "From forward substitution, Matrix Y becomes : ";
		printMatrix(Y, 1);
	}
	void backSub()
	{
		std::cout << "Now UX = Y then," << std::endl;
		for (int i = n - 1; i >= 0; i--)
		{
			for (int j = i + 1; j < n; j++)
			{
				Y.at(i) = Y.at(i) - Y.at(j) * U.at(n * i + j);
			}
			Y.at(i) = Y.at(i) / U.at(i * n + i);
		}

		std::cout << "From backward substitution, Matrix X becomes : ";
		printMatrix(Y, 1);
	}
	void LUDecomposition()
	{
		//Input Matrix
		std::cout << "Matrix A becomes : ";
		printMatrix(A, n);
		std::cout << "Matrix B becomes : ";
		printMatrix(B, 1);
		//Swap for pivot elements
		checkPivot();
		//LU decomposition
		std::cout << "If A = LU then," << std::endl;
		DoLittle();
		std::cout << "Matrix L becomes : ";
		printMatrix(L, n);
		std::cout << "Matrix U becomes : ";
		printMatrix(U, n);

		//Sub for Y
		fwdSub();
		//Sub for X
		backSub();
	}
	void printOutput()
	{
		std::cout << "The result is : " << std::endl;
		for (int i = 0; i < n; i++)
			std::cout << std::setw(10) << "x[" << i << "] =" << Y.at(i) << std::endl;
	}
};
int main()
{
	Matrix M;
	M.getOrder();
	M.readData();
	M.LUDecomposition();

	M.printOutput();
	int x;
	std::cin >> x;
	return 0;
}