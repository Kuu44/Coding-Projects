#include<iostream>
using namespace std;
class ntc{
public:
    ntc(char* v):id(Size++){
        //ntc::Size=1;
        //cout<<"Constructor Size="<<Size;
        for(int i=0;i!=10;i++)
            val[i]=v[i];
    }
    static void showSize(){
        cout<<"ntc has "<<ntc::Size<<((Size>1)?(" sims that are operational."):(" sim that is operational"));
    }
private:
    const int id;
    char val[10];
    static int Size;
};
int ntc::Size=0;
int main(){
//    int ntc::Size=0;
    ntc I("9866471976");
    ntc::showSize();

    //N9841829080.Size();
return 0;
}
