#include<iostream>
#include<iomanip>
#include<vector>

class Matrix4
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

        void GaussJordan()
        {

            for(int i=0;i<n;i++)
            {
                float temp = A.at(i*n+i);
                for(int j=0;j<n;j++)
                    A.at(i*n+j) /=  temp;
                B.at(i) /= temp;
                for(int j=0;j<n;j++)
                {
                    float temp2 = A.at(n*j+i);
                    if(i!=j)
                    {
                        for(int k=0;k<n;k++)
                        {
                            A.at(n*j+k) -= A.at(i*n+k)*temp2;
                        }
                        B.at(j) -= B.at(i)*temp2;
                    }
                    
                } 
            }
        }
        
        void printOutput()
        {
                std::cout<<"The result is : "<<std::endl;
                for(int i=0;i<n;i++)
                    std::cout<<std::setw(10)<<"x["<<i<<"] ="<<B.at(i)<<std::endl;
        } 
};
int main4() 
{
    Matrix4 M;
    M.getOrder();
    M.readData();
    M.GaussJordan();
    M.printOutput();
   return 0;
}
