#ifndef CALCULATOR_H
#define CALCULATOR_H


class Calculator
{
    public:
       double Calculate(double x, char oper, double y)
       {
           switch(oper)
    {
    case '+':
        return x+y;
    case '-':
        return x-y;
    case '*':
        return x*y;
    case '/':
        return x/y;
    default:
        return 0.0;
    }
       };

    protected:

    private:
};

#endif // CALCULATOR_H
