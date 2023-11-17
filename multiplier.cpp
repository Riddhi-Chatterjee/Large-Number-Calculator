#include "multiplier.hpp"

multiplier::multiplier()
{
    apx = new approximator();
    a = new adder();
    s = new subtractor();
}

multiplier::~multiplier()
{
    delete apx;
    apx = NULL;

    delete a;
    a = NULL;

    delete s;
    s = NULL;
}

struct Number multiplier::multiply(struct Number &num1, struct Number &num2, int base, int precision)
{   //Performs num1*num2 operation
    
    int tot_precision = num1.second+num2.second;
    
    struct Number result;
    result = karatsuba(num1.first, num2.first, base, 0);
    result.second += tot_precision;

    apx->roundOff(result, base, precision); //Rounding off the final result to the required precision
    
    truncate(result.first); //Removing useless leading zeros from the final result
    return result;
}

struct Number multiplier::karatsuba(vector<int> &num1, vector<int> &num2, int base, int precision)
{ 
    //1.Take the numbers in the input
    //2.Compare the number of digits in them
    //3.Make the number of digits equal in both the numbers and make them even :
    //  by reversing the numbers, and then padding zeroes to them and then re-reversing them
    //4.Split each of the two numbers into two halves.
    //5.Make recursive calls to the karatsuba function
    //6.Appropriately combine the results obtained to get the final result of the multiplication
    
    if(num1.size() == 1 && num2.size() == 1) //Handles the base case
    {
        vector<int> result(2);
        struct Number res;
        int val = num1[0]*num2[0];
        result[0] = val/base;
        result[1] = val%base;
        truncate(result);
        res.first = result;
        res.second = 0;
        return res;
    }

    int size = max(num1.size(), num2.size());
    if(size%2 == 1)
    {
        size++;
    }

    vecInverter(num1);
    vecInverter(num2);

    int i;
    int sz1 = num1.size();
    for(i=0;i<(size - sz1);i++)
    {
        num1.push_back(0);
    }


    int sz2 = num2.size();
    for(i=0;i<(size - sz2);i++)
    {
        num2.push_back(0);
    }


    vecInverter(num1);
    vecInverter(num2);

    struct Number a0, a1;
    struct Number b0, b1;

    copy(num1.begin() + size/2, num1.begin() + size, back_inserter(a0.first));
    copy(num1.begin(), num1.begin() + size/2, back_inserter(a1.first));
    copy(num2.begin() + size/2, num2.begin() + size, back_inserter(b0.first));
    copy(num2.begin(), num2.begin() + size/2, back_inserter(b1.first));

    a0.second = 0;
    a1.second = 0;
    b0.second = 0;
    b1.second = 0;


    struct Number c0,c1,c2;

    c0 = a->add(a0, a1, base, 0);
    c2 = a->add(b0, b1, base, 0);


    c1 = karatsuba(c0.first, c2.first, base, 0);

    c0 = karatsuba(a0.first, b0.first, base, 0);
  
    c2 = karatsuba(a1.first, b1.first, base, 0);

    c1 = s->subtract(c1, c0, base, 0);
   
    c1 = s->subtract(c1, c2, base, 0);
    

    int m = size/2;

    leftshift(c2, 2*m);
    
    leftshift(c1, m);
    
    c1 = a->add(c1, c0, base, 0);
    c2 = a->add(c2, c1, base, 0);

    return c2;
}

void multiplier::truncate(vector<int> &v) //Accepts numbers in "LSB at size-1" form
{
    vecInverter(v);
    int i=v.size()-1;
    while(i != 0 && v[i] == 0)
    {
        v.pop_back();
        i--;
    }
    vecInverter(v);
}

void multiplier::vecInverter(vector<int> &v)
{
    vector<int> temp = v;
    int i;
    for(i=v.size() - 1;i>=0;i--)
    {
        v[v.size() - 1 - i] = temp[i];
    }
}

//Let base = B
//1 left shift = number*B
//2 left shifts = number*(B^2)... and so on
void multiplier::leftshift(struct Number &num, int t) //Left shifts num t times
{
    int i;
    for(i=0;i<t;i++)
    {
        num.first.push_back(0);
    }
}
