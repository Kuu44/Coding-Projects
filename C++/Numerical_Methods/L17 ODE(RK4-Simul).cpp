#include<iostream>
#include<cmath>

//y''-xy'+4y=0 , y(0)=3,y'(0)=0

float zprime17(float x, float y,float z)  // z = y'
{
    return x+y;
}
float yprime17(float x, float y,float z)  // z = y'
{
    return x-y*y;
}
int main17()
{
    float x0,y0,z0,n;
    std::cin>>x0>>y0>>z0; //Initial values of x and y
    float xn; //given value of x;
    std::cin>>xn;
    float h; //stepsize
    std::cin>>n;
    h = (xn - x0) / n;
    float x = x0,y =y0,z=z0;
    while(x!=xn)
    {
        float k1 = h * yprime17(x,y,z);
        float l1 = h * zprime17(x,y,z);
        
        float k2 = h * yprime17(x+h/2,y+k1/2,z+l1/2);
        float l2 = h * zprime17(x+h/2,y+k1/2,z+l1/2);
        
        float k3 = h * yprime17(x+h/2,y+k2/2,z+l2/2);
        float l3 = h * zprime17(x+h/2,y+k2/2,z+l2/2);
        
        float k4 = h * yprime17(x+h,y+k3,z+l3);
        float l4 = h * zprime17(x+h,y+k3,z+l3);
        
        float k = (k1+2*k2+2*k3+k4)/6;
        float l = (l1+2*l2+2*l3+l4)/6;
        
        z = z+l;
        y = y+k;
        x= x+h;
    }
    std::cout<<x<<","<<y<<","<<z;
   return 0; 
}

/*
0 3 0
0.2
0.05
*/
