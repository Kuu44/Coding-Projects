#include<iostream>
#include<cmath>
float fun13(float x)
{
//    return 3*pow(x,2)+6*x+3;
    return 1/x;
}


int main13()
{
    float a,b; //Limits
    std::cin>>a>>b;
    int n; // No of sub intervals
    std::cin>>n;
    if(n%3!=0)
        return 1;
    float stepsize = (b-a)/n;
    
    float sum = fun13(a)+fun13(b);
    for (int i=1;i<n;i++)
    {
        int k;
        if(i%3==0)
            k=2;
        else
            k=3;
         sum+= k* fun13(a+i*stepsize);
    }
       
    sum *= 3*stepsize/8;
    std::cout<<"The answer is : "<<sum;
    return 0;
}
