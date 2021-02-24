#include<iostream>
#include<cmath>
float yprime16(float y, float x)
{
    //return pow(y,2)+1;
    //return 9*pow(x,2);
    return cos(x)+sin(y);
    //return (y*y-x*x)/(y*y+x*x);
}

int main16()
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
        float k1 = h * yprime16(y,x);
        float k2 = h * yprime16(y+k1/2,x+h/2);
        float k3 = h * yprime16(y+k2/2,x+h/2);
        float k4 = h * yprime16(y+k3,x+h);
        float k = (k1+2*k2+2*k3+k4)/6;
        y = y+k;
        x= x+h;
    }
    std::cout<<x<<","<<y;
   return 0; 
}
