#include<iostream>
#include<cmath>
float fun1(float x)
{
    return x*x+sin(x)-1;
}
int main1()
{
    float a,b,c,e;
    std::cin>>a>>b;  //interval
    std::cin>>e;     //error
    if(fun1(a)*fun1(b)>0)
    {
        std::cout<<"No solution"<<std::endl;
        return 1;
    }
    if(fun1(b)<0)
    {
        float temp = a;
        a=b;
        b=temp;
    }
    do{
        c = (a+b)/2;
        if(fun1(c)<0)
            a=c;
        else
            b=c;
    }while(fabs(fun1(c))>e);
    std::cout<<"The root is : "<<c;
    return 0; 
}
