#include<iostream>
#include<vector>

float vecsum9(std::vector<float> V)
{
    float sum =0;
    for (int i=0;i<V.size();i++)
        sum+= V.at(i);
    return sum;
}

int main9()
{
    int n;
    std::cin>>n; //No of data
    std::vector<float> X,Y,XY,Xsq;
    for(int i=0;i<n;i++)
    {
        float x,y;
        std::cin>>x>>y;
        X.push_back(x);
        Y.push_back(y);
        XY.push_back(x*y);
        Xsq.push_back(x*x);
    }
    float xsum = vecsum9(X);
    float ysum = vecsum9(Y);
    
    float xmean = xsum/n;
    float ymean = ysum/n;
    
    float m = (n*vecsum9(XY)-xsum*ysum)/(n*vecsum9(Xsq)-xsum*xsum);
    float c = ymean - m * xmean;
    std::cout<<"The curve is :y = "<<m<<"x + ("<<c<<")";
        
    
    return 0;
}
