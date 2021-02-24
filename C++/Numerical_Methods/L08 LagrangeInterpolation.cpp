#include<iostream>
#include<vector>
int main8()
{
    int n;
    std::cout<<"Enter number of data : ";
    std::cin>>n;
    std::vector<float> Y,X;
    float y=0,x;
    for(int i=0;i<n;i++)
    {
        float temp1,temp2;
        std::cout<<"Enter x["<<i<<"] and y["<<i<<"] : ";
        std::cin>>temp1>>temp2;
        X.push_back(temp1);
        Y.push_back(temp2);
    }
    std::cout<<"Valoe of x for which value of y should be determined : ";
    std::cin>>x;
    
    for(int i=0;i<n;i++)
    {
        float prod =1;
        for(int j=0;j<n;j++)
        {
            if(i!=j)
                prod *= (x-X.at(j))/(X.at(i)-X.at(j));
        }
        y += prod*Y.at(i); 
    }
    std::cout<<"The value of y corresponding to "<<x<<" is :"<<y;
    return 0;
}
