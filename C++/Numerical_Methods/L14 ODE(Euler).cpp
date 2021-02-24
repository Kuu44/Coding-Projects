#include<iostream>
#include<cmath>
float yprime14(float y, float x)
{
    return (2*x*y+exp(x))/(x*x+x*exp(x));
    // return -y;
}

int main14()
{
    float x0,y0,n;
    std::cin>>x0>>y0; //Initial values of x and y
    float xn; //given value of x;
    std::cin>>xn;
    float h; //stepsize
    std::cin>>n;
    h = (xn - x0) / n;
    float x = x0,y =y0;
    for(int i=0;i<n;i++)
    {
        float k = h * yprime14(y,x);
        y = y+k;
        x+=h;
    }
    std::cout<<x<<","<<y;
   return 0; 
}
