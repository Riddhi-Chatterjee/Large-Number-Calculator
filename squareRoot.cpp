#include "squareRoot.hpp"

squareRoot::squareRoot()
{
    a = new adder();
    d = new divider();
    bConv = new baseConverter();
    apx = new approximator();
    print_flag = false;
}

squareRoot::~squareRoot()
{
    delete a;
    a = NULL;

    delete d;
    d = NULL;

    delete bConv;
    bConv = NULL;

    delete apx;
    apx = NULL;
}

struct Number squareRoot::sqRootOf(struct Number &num, int base, int precision)
{
    /*
        ASSERTIONS in the square root algorithm (Newton's approximation to find root(R)):
        * x0>x1>...>xn>root(R)
        * xn - root(R) <= (1/(2^n))*(((x0-root(R))^2)/x0)
    */

    struct Number p;
    struct Number q;
    struct Number divNum;
    struct Number addNum;
    struct Number two;

    two.first.clear();
    two.first.push_back(2);
    two.second = 0;
    bConv->convertFromTen(two, base, 0);

    p = num;
    q = num;

    int c1=5,c2=5,c3=5; //Asymptotic constants
    
    int limit = ceil((c1*log10(precision))+(c2*num.first.size())+c3);
    int it_count = 0;

    //Calculates the precision of the digits obtained so far.
    //Makes use of the Newton-Raphson iterative method for finding the square root.
    while(it_count <= limit)
    {
        if(print_flag)
        {
            int val1 = (it_count - c3 - (c2*num.first.size()));
            float val2 = (1.0*val1)/c1;
            int obtainedPrecision = (int)pow(10, val2);
            obtainedPrecision = precisionConverter(base, obtainedPrecision, 10);
            cout<<"Iterations: "<<it_count<<" / "<<limit<<", Current Precision: ~"<<obtainedPrecision<<" Digits"<<flush;
            if(it_count+1 <= limit)
            {
                cout<<'\r';
            }
        }
        it_count++;
        q = p;
        divNum = d->divide(num, p, base, precision);
        addNum = a->add(p, divNum, base, precision);
        p = d->divide(addNum, two, base, precision);
    }
    if(print_flag)
    {
        cout<<endl;
        cout<<endl;
    }
    
    //Rounds off the precision obtained to the desired precision.
    apx->roundOff(p, base, precision);
    return p;
}

bool squareRoot::precisionObtained(struct Number &num1, struct Number &num2, int base, int precision)
{ //NOTE : THIS FUNCTION HAS ONLY BEEN USED WHILE TESTING/EXPERIMENTING
    struct Number p;
    struct Number q;
    p = num1;
    q = num2;
    apx->roundOff(p, base, precision);
    apx->roundOff(q, base, precision);
    if(p.second == ((-1)*precision) && q.second == ((-1)*precision) && p.first == q.first)
    {
        return true;
    }
    return false;
}

bool squareRoot::getPrintFlag()
{
    return print_flag;
}

void squareRoot::setPrintFlag(bool printFlag)
{
    print_flag = printFlag;
}

int squareRoot::precisionConverter(int Bi, int P_Bi, int Bf)
{ //Used to find out the equivalent precision in Bf(target base), given Bi and the precision in Bi
    int P_Bf = ceil(P_Bi*(log(Bi)/log(Bf)));
    return P_Bf;
}