#include<iostream>
#include"Calculator.h"

using namespace std;

int main(){
    double x=0.0;
    double y=0.0;
    double result=0.0;
    char oper='+';

    cout << "Calculator Console Application\n\n" ;
    cout << "Please enter the operation to perform. Format: a+b | a-b | a*b | a/b\n";

    Calculator c;
    //for(;;)
    //{
        cin>> x>>oper>>y;
        result=c.Calculate(x,oper,y);
        cout <<"result is: "<<result<<endl;
    //}

    return 0;
}
