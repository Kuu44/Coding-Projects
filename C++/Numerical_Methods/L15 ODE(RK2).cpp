#include<iostream>
#include<cmath>
float yprime15(float y, float x)
{
    return sin(x)-cos(y);
    // return -y;
}

int main15()
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
        float k1 = h * yprime15(y,x);
        float k2 = h * yprime15(y+k1,x+h);
        float k = (k1+k2)/2;
        y = y+k;
        x= x+h;
    }
    std::cout<<x<<","<<y;
   return 0; 
}
