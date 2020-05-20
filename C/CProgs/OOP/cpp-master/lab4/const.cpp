/*********
 * 
 * Sujit Maharjan
 *
 * lab4
 * problem 5
 *
 * Write a program that illustrate the following relationship and comment the relationships. 
 i) const_object.non_const_mem_function
 ii) const_object.const_mem_function
 iii) non_const_object.non_const_mem_function
 iv) non_const_object.const_mem_function
  *
  */
 #include <iostream>

 #define SUCCESS 0

 using namespace std;
 class Class 
 {
 private:
   const int id; 
 public:
   Class(int i):id(i){};

   int const_get()const
   {
    return id;
  }
  int get()
  {
    return id;
  }
};
int main()
{
  Class a(1);
  cout <<"non const object calling non const mem func "<< a.get()<<endl; // non const object. non const mem func
  cout << "non const object calling const mem func "<<a.const_get()<<endl; // non const object. const mem
  const Class c(2);
  cout << "const object calling const mem func "<<c.const_get(); // const object.cont mem func
  //  cout << c.get(); cannot be called
  return SUCCESS;
}
