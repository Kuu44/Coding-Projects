#include<iostream>
using namespace std;
class dep{
    public:
        dep(char *i, char* n,int ns){
            cout<<"\nConstructor says hell0\n"<<endl;
            for(int j=0;j<3;j++)
                id[j]=i[j];
            id[3]='\0';
            int k=(ns<=15)?ns:15;
            for(int j=0;j!=k;j++)
                name[j]=n[j];
            name[k]='\0';
        }
        ~dep(){
            cout<<"\nObject ->(";print();cout<<") has gone out of scope."<<endl;
        }
        void print(){
            cout<<"Department's name:"<<name;
            cout<<" | Id:"<<id;
        }
    private:
        char id[4];
        char name[15];
};
int main(){
    dep phy("001","Physics",7);
    phy.print();cout<<endl;
}
