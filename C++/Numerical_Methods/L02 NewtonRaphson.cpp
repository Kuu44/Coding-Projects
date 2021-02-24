#include<iostream>
#include<cmath>

float fun2(float x)
{
    return tan(x)+cosh(x);
}
float derv2(float x)
{
    return (1/(cos(x)*cos(x)))+sinh(x);
}
int main2()
{
    float a,e;
    std::cin>>a;  //initial estimate
    std::cin>>e;     //error
    do
    {
        a=a-fun2(a)/derv2(a);
    }while(fabs(fun2(a))>e);
    std::cout<<"The root is : "<<a;
    return 0; 
}
