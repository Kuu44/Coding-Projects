#include<iostream>
using namespace std;
class gadi{
public:
    gadi(char* n,int ns,float rt): rate(rt)
    {
        int k=(ns<=15)?ns:15;
        for(int j=0;j!=k;j++)
            name[j]=n[j];
        name[k]='\0';
    }
    gadi(const gadi& a)
    {
        for(int i=0;i!=15;i++)
            name[i]=a.name[i];
            rate=a.rate;
    }
    void bill(float hr)
    {
        cout<<"name:"<<name<<" | Rate: Rs"<<rate<<"/hr | Hours: "<<hr<<"hrs | Total fee to be paid: Rs"<<rate*hr;
    }
private:
    char name[15];
    float rate;
};
int main(){
    gadi bike1("Yatri",5,2.5);
    bike1.bill(1.5);cout<<endl;
    gadi bike2(bike1);
    bike2.bill(2.5);
return 0;
}
