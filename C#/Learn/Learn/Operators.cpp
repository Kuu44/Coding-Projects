#include<iostream>

using namespace std;

class Complex
{
private:
	float real, imag;
public:
	Complex(const float &re=0, const float &im=0) :real(re), imag(im) {}	
	Complex operator+(Complex);
	//Complex operator[]	
	void print();
	string operator<<(Complex);

};
class Polar: public Complex
{
private:
	float rad, angle;
public:
	Polar(float const &r=0, const float &a=0) :Complex(r, a), rad(r), angle(a) {}
	Polar(const Complex c) :Complex(c) {}
	Polar operator-();	
	Polar operator-(Polar);
};

int main()
{
	Polar a(4, 5), b(5.6, 7.8),c;

	c = (a -b);
	c.print();

	return 0;
}
#pragma region Class Functions
string Complex::operator<<(Complex c)
{	
	string s1,s2;
	s1 = c.real;
	s2 = c.imag;
	s1 = strcat(s1, " +i");
	return  
}
void Complex::print()
{
	cout << real << " +i" << imag << endl;
}
Complex Complex::operator+(Complex c)
{
	return Complex(real + c.real, imag + c.imag);
}
Polar Polar::operator-(Polar p)
{
	return Polar(rad - p.rad, angle - p.angle);
}
Polar Polar::operator-()
{
	return Polar(-rad, -angle);
}
#pragma endregion