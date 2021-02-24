#include<iostream>
#include<vector>
#include<cmath>
float vecsum10(std::vector<float> V)
{
    float sum =0;
    for (int i=0;i<V.size();i++)
        sum+= V.at(i);
    return sum;
}

int main10()
{
    int n;
    std::cin>>n; //No of data
    std::vector<float> X,Y,XY,Xsq;
    for(int i=0;i<n;i++)
    {
        float x,y;
        std::cin>>x>>y;
        y = log(y);
        X.push_back(x);
        Y.push_back(y);
        XY.push_back(x*y);
        Xsq.push_back(x*x);
    }
    float xsum = vecsum10(X);
    float ysum = vecsum10(Y);
    
    float xmean = xsum/n;
    float ymean = ysum/n;
    
    float m = (n*vecsum10(XY)-xsum*ysum)/(n*vecsum10(Xsq)-xsum*xsum);
    float c = ymean - m * xmean;
    std::cout<<"The curve is :y = "<<exp(c)<<"e^ ("<<m<<"x)";
    return 0;
}
