#include<iostream>
using namespace std;
class sent
{
public:
    sent(char* b, int a):sz(a),store(new char[a]) //here char[sz] will give an error because maybe initialization is started from the right i.e. new char[sz] is executed before sz(a)
    {
        //store=new char[sz];
        for(int i=0;i!=a;i++)
            store[i]=b[i];
    }
    sent join(sent b){
        int x=sz+b.sz;
        char *p=new char[x];
        for(int i=0;i!=sz;i++)
            p[i]=store[i];
        for(int i=sz;i!=x;i++)
            p[i]=b.store[i-sz];
        return sent(p,x);
    }
    ~sent()
    {
        delete[] store;
    }
    void print(){
        for(int i=0;i!=sz;i++)
            cout<<store[i];
    }
private:
    char* store;
    int sz;
};
int main(){
    sent pre("Engineers are ",14);
    sent post("Creatures of logic.",19);
    cout<<endl;
    (pre.join(post)).print();
    return 0;
}
