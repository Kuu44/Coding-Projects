#include<iostream>
#include<cmath>
#include<vector>
class Matrix11
{
    private:
        int n;
        std::vector<float> A,B;
    public:
        Matrix11(int x){n=x+1;}
        
        void readData (std::vector<float> V1, std::vector<float> V2)
        {
           for(int i=0; i<n; i++) 
                for(int j=0;j<n;j++)
                    A.push_back(V1.at(i+j));
           B=V2;
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
                std::cout<<"The curve is : "<<std::endl<<"y = ";
                for(int i=0;i<n;i++)
                {
                    std::cout<<"("<<B.at(i)<<")x^"<<i;
                    if(i!=n-1)
                        std::cout<<"+";
                }
                    
        } 
};


int main11()
{
    int m; //Order of polynomial
    std::cin>>m;
    
    int n; //No of data pairs
    std::cin>>n;
    
    //read data
    std::vector<float> X,Y;
    for(int i=0;i<n;i++)
    {
        float x,y;
        std::cin>>x>>y;
        X.push_back(x);
        Y.push_back(y);
    }
    //generate matrix
    
    std::vector<float> Xn,YXn;
    for(int i=0;i<=2*m;i++)
    {
        float sum = 0;
        for(int j=0;j<n;j++)
            sum+= pow(X.at(j),i);
        Xn.push_back(sum);
        
    }
    for(int i=0;i<=m;i++)
    {
        float sum = 0;
        for(int j=0;j<n;j++)
            sum+=Y.at(j) * pow(X.at(j),i);
        YXn.push_back(sum);
    }
    
    Matrix11 M(m);
    M.readData(Xn,YXn);
    M.GaussJordan();
    M.printOutput();   
    return 0;
}



/*
2
4
1 0.63
3 2.05
4 4.08
6 10.78
*/
