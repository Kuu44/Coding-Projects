#include<iostream>
#include<iomanip>
#include<vector>
#include<cmath>

class Matrix7
{
private:
    int n;
    std::vector<float> A;
    std::vector<float> B;
    float e;
public:
    void getOrder()
    {
        std::cout << "Order of matrix: ";
        std::cin >> n;
    }
    void readData()//For matrix
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
    void guessVector()
    {
        for (int i = 0; i < n; i++)
        {
                B.push_back(1);
        }
        std::cout<<"Tolerable error : ";
        std::cin>>e;
    }
    std::vector<float> MatrixMult(std::vector<float> M1,std::vector<float> M2) //M1 is of order n*n M2 of n*1
    {
        std::vector<float> temp;
        for(int i=0;i<n;i++)
        {
            float sum =0;
            for(int j=0;j<n;j++)
            {
                sum += M1.at(i*n+j)*M2.at(j);
            }
            temp.push_back(sum);
        }
        return temp;
    }
    void PowerMethod()
    {
        float Lambda0,Lambda1 = INT_MIN;
        do{
            Lambda0 = Lambda1;
            Lambda1 = INT_MIN;
            B = MatrixMult(A,B);
            for(int i=0;i<n;i++)
                if(B.at(i)>Lambda1)
                    Lambda1 = B.at(i);
            std::cout<<"\nEigenValue : "<<Lambda1<<std::endl<<"EigenVector : "<<std::endl;
            for(int i=0;i<n;i++)
            {
                B.at(i) = B.at(i)/Lambda1;
                std::cout<<std::setw(7)<<B.at(i) << "\t";
            }
        }while(fabs(Lambda0-Lambda1)>e);
    }
};
int main7()
{
    Matrix7 M;
    M.getOrder();
    M.readData();
    M.guessVector();
    M.PowerMethod();
    return 0;
}
