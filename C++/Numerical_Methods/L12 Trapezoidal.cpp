#include<iostream>
#include<cmath>
float fun12(float x)
{
    return (1/x);
}


int main12()
{
    float a,b; //Limits
    std::cin>>a>>b;
    int n; // No of sub intervals
    std::cin>>n;
    float stepsize = (b-a)/n;
    float sum = fun12(a)+fun12(b);
    for (int i=1;i<n;i++)
        sum+= 2* fun12(a+i*stepsize);
    sum *= stepsize/2;
    std::cout<<"The answer is : "<<sum;
    return 0;
}
