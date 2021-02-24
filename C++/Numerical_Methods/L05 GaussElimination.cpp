#include<iostream>
#include<iomanip>
#include<vector>

class Matrix5
{
    private:
        int n;
        std::vector<float> A; 
        std::vector<float> B;
    public:
        void getOrder()
        {
            std::cout<<"Order of matrix: ";
            std::cin>>n;
        }
        void readData()
        {
            float x;
            for(int i=0; i<n; i++) 
            {
                for(int j=0;j<n;j++)
                { 
                    std::cout<<"Value of a["<<i<<"]["<<j<<"] : ";
                    std::cin>>x;
                    A.push_back(x);
                }  
                std::cout<<"Value of b["<<i<<"] : ";
                std::cin>>x;
                B.push_back(x);
            }
        }
        void GaussElimination()
        {

            for (int i = 0; i < n; i++)
            {
                float temp = A.at(i * n + i);
                int k = 1;

                while (temp == 0) 
                {
                    if (i + k >= n && temp == 0)
                    {
                        std::cout << "Determinant = 0";
                        exit(0);
                    }
                    temp = A.at((i + k) * n + i);
                    k++;
                }

                if (k-- > 1) 
                {
                    for (int x = 0; x < n; x++)
                    {
                        //Swap rows in A from k steps ahead
                        float val = A.at(i * n + x);
                        A.at(i * n + x) = A.at((i + k) * n + x);
                        A.at((i + k) * n + x) = val;
                        //Update value of temp
                        temp = A.at(i * n + i);
                    }
                    //Swap rows in B from k steps ahead
                    float val2 = B.at(i);
                    B.at(i) = B.at(i + k);
                    B.at(i + k) = val2;
            }
            for (int j = 0; j < n; j++)
            {
                A.at(i * n + j) /= temp;
            }
            B.at(i) /= temp;

            for (int j = i; j < n; j++)
            {
                float temp2 = A.at(n * j + i);
                if (i != j)
                {
                    for (int k = 0; k < n; k++)
                    {
                        A.at(n * j + k) -= A.at(i * n + k) * temp2;
                    }
                    B.at(j) -= B.at(i) * temp2;
                    
                }

            }
        }
                
    } 
        void backSubs()
        {
	        for(int i=n-1;i>=0;i--)
            {
                for(int j=i+1;j<n;j++)
                {
                    B.at(i)-=B.at(j)*A.at(n*i+j);
                }
                    
            }
        }
        
        void printOutput()
        {
            for(int i=0;i<n;i++)
            {
                std::cout<<"x["<<i<<"]:"<<B.at(i)<<std::endl;
                    
            }
        }
        
};
int main5() 
{
    Matrix5 M;
    M.getOrder();
    M.readData();
    M.GaussElimination();
    M.backSubs();
    M.printOutput();
    return 0;
}
