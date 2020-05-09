#include<iostream>

#define GGMU 0
using namespace std;

class theGrandDad
{
public:
	float h;
public:
	theGrandDad():h(0) { cout << "Default Grandad\n"; }
	theGrandDad(int n):h(n) {cout << "Power GranDad :" + n << "\n"; }

	virtual void theFunction()
	{
		cout << "Generation Power:"  << cout.width(5) << h<<endl;
	}
	void theRepeater(){theFunction();}
	void theAlternate()
	{
		cout<<"I'm in theGrandDad\n";
	}
};
class theDad:virtual public theGrandDad
{
public: 
	theDad(){h = 100; cout << "Default Dad\n"; }
	theDad(int n) { h=n;  cout << "Power Dad: " << n << "\n"; }
	
	void theAlternate()
	{
		cout << "I'm in theDad\n";
	}
	virtual void theFunction()
	{
		cout << "Dad\n";
	}
};

class theMom :virtual public theGrandDad
{
public:
	theMom() { h = 1; cout << "Default Mom\n"; }
	theMom(int n) { h = n; cout << "Power Mom: " << n << "\n"; }	
};
class theChild : public theMom, public theDad
{
private:
public:
	theChild()
	{
		cout << "Default Child\n";
	}
	theChild(int n) :theDad(n), theMom(n) { cout << "Child Power: " << theDad::h + theMom::h<<endl; }
	void theFunction(){	cout << "grandChild\n";}
	void theAlternate()
	{
		cout << "I'm in theChild\n";
	}
};
//int main()
//{
//	theGrandDad* gdad;
//	theMom* dad;
//	
//	theChild obj;
//	cout << endl;
//	theChild obj2(5);
//	
//	dad = &obj;
//	gdad = dad;	
//
//	cout << endl;
//	//obj.theGrandDad::theFunction();
//	(*gdad).theFunction();
//	gdad->theAlternate();
//	cout << endl;
//
//	gdad = &obj;
//	(*gdad).theFunction();
//	gdad->theAlternate();
//	cout << endl;
//	theGrandDad* gdad2;
//	theMom dad2;
//
//	gdad2 = &dad2;
//	
//	gdad2->theGrandDad::theFunction();
//	dad2.theRepeater();
//	
//	return GGMU;
//}