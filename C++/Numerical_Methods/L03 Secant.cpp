#include<iostream>
#include<cmath>
float fun3(float x)
{
    return cos(x)-4*x+5;
}

int main3()
{
    float a,b,c,e;
    std::cin>>a>>b;  //initial values
    std::cin>>e;     //error
    do{
        c = (a*fun3(b) - b*fun3(a))/(fun3(b)-fun3(a));
        a=b;
        b=c; 
    }while(fabs(fun3(c))>e);
    std::cout<<"The root is : "<<c;
    return 0; 
}
