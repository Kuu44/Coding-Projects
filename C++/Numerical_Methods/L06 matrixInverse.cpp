#include<iostream>
#include<iomanip>
#include<vector>

class Matrix6
{
private:
    int n;
    std::vector<float> A;
    std::vector<float> B;
public:
    void getOrder()
    {
        std::cout << "Order of matrix: ";
        std::cin >> n;
    }
    void readData()
    {
        float x;
        for (int i = 0; i < n; i++)
        {
            for (int j = 0; j < n; j++)
            {
                std::cout << "Value of a[" << i << "][" << j << "] : ";
                std::cin >> x;
                A.push_back(x);
            }
        }
    }
    void setData()
    {
        for (int i = 0; i < n; i++)
        {
            for (int j = 0; j < n; j++)
            {
                if (i == j)
                    B.push_back(1);
                else
                    B.push_back(0);
            }
        }
    }
    void GaussJordan()
    {
        for (int i = 0; i < n; i++)
        {
            float temp = A.at(i * n + i);
            int k = 1;

            while (temp == 0) {
                if (i + k >= n && temp == 0)
                {
                    std::cout << "Determinant = 0";
                    exit(0);
                }
                temp = A.at((i + k) * n + i);
                k++;
            }
            if (k-- > 1) {
                
                for (int x = 0; x < n; x++)
                {
                    //Swap rows in A from k steps ahead
                    float val = A.at(i * n + x);
                    A.at(i * n + x) = A.at((i + k) * n + x);
                    A.at((i + k) * n + x) = val;

                    //Swap rows in B from k steps ahead
                    float val2 = B.at(i * n + x);
                    B.at(i * n + x) = B.at((i + k) * n + x);
                    B.at((i + k) * n + x) = val2;

                    //Update value of temp
                    temp = A.at(i * n + i);
                }
            }

            for (int j = 0; j < n; j++)
            {
                A.at(i * n + j) /= temp;
                B.at(i * n + j) /= temp;
            }

            for (int j = 0; j < n; j++)
            {
                float temp2 = A.at(n * j + i);
                if (i != j)
                {
                    for (int k = 0; k < n; k++)
                    {
                        A.at(n * j + k) -= A.at(i * n + k) * temp2;
                        B.at(n * j + k) -= B.at(i * n + k) * temp2;
                    }
                }

            }
        }

    }
    void printOutput()
    {
        std::cout << "The Output is :" << std::endl;
        int j = 0;
        for (int i = 0; i < B.size(); i++)
        {
            std::cout << std::setw(7)<<B.at(i) << "\t";
            j++;
            if (j == n)
            {
                std::cout << std::endl;
                j = 0;
            }

        }
    }
};
int main6()
{
    Matrix6 M;
    M.getOrder();
    M.readData();
    M.setData();
    M.GaussJordan();
    M.printOutput();
    return 0;
}
