#include<iostream>
using namespace std;
class animal{
    char species[15];
    char name[15];
    char feet;
    char hands;
public:
    animal(char* s,char f, char h){
        for(int i=0;i!=15;i++)
            species[i]=s[i];
        feet=f;
        hands=h;
    }
    void setName(char* n){
        for(int i=0;i!=15;i++)
            name[i]=n[i];
    }
    void print()const{
        //feet=8; //error assignment of member 'animal::feet' in read-only object
        cout<<"[ Species : "<<species<<" | ";
        cout<<"Feet : "<<feet<<" | ";
        cout<<"Hands : "<<hands<<" | ";
        cout<<"Name : "<<name<<" ]"<<endl;
    }
};
int main(){
    const animal hum("Homo sapien",'2','2');
    //hum.setName("Gopal"); //gives error " passing 'const animal' as 'this' argument discards qualifiers ..."
    hum.print();cout<<endl;
    animal ram(hum);
    ram.print();cout<<endl;
    ram.setName("Ram");
    ram.print();
return 0;
}
