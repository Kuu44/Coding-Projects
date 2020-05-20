#include<iostream>
using namespace std;
class time{
    public:
        static int n;
        time():id(++n){
            Hr=Min=Sec=0;
            cout<<"\nCreated <"<<id;cout<<"> ";display();cout<<"\n";
        }
        time(int h, int m,int s):id(++n){
            Hr=h;Min=m;Sec=s;
            cout<<"\nCreated <"<<id;cout<<"> ";display();cout<<"\n";
        }
        ~time(){
            //n++;
            cout<<"\ndestroyed <"<<id;cout<<"> ";display();cout<<"\n";
        };
        void display(){
            cout<<"Display says: ";
           cout<<Hr<<" : "<<Min<<" : "<<Sec;
        }
        void setH(int z){Hr=z;}
        time add(time a){
            time b=time(Hr+a.Hr,Min+a.Min,Sec+a.Sec);
            cout<<"in add";
            a.setH(77);
            return b;
        }
    private:
        int Hr;
        int Min;
        int Sec;
        const int id;
};
int time::n=0;
int main(){
    time A(2,1,0);
    time B(0,1,2);
    time C=B.add(A);cout<<"jhjh"<<endl;
    //C.setH(7);
    C.display();
    //B.~time();

}
