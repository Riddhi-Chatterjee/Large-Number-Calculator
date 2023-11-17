#include "adder.hpp"
adder::adder()
{
    apx_adder = new approximator();
}

adder::~adder()
{
    delete apx_adder;
    apx_adder = NULL;
}

struct Number adder::add(struct Number &n1, struct Number &n2, int base, int precision)
{ //Performs n1+n2 operation
    struct Number num1 = n1;
    struct Number num2 = n2;
    int p1 = -num1.second;
    int p2 = -num2.second;
    int s1 = num1.first.size(); 
    int s2 = num2.first.size();
    
    //padding zeroes and making the precision of both the numbers same.
    if(p1>p2)
    {
        for(int i = 0; i<(p1-p2); i++)
        {
            num2.first.push_back(0);
        }
        num2.second = -p1;
    }
    else if(p1<p2)
    {
        for(int i = 0; i<(p2-p1); i++)
        {
            num1.first.push_back(0);
        }
        num1.second = -p2;
    }

    s1 = num1.first.size(); 
    s2 = num2.first.size();
    vecInverter(num1.first);
    vecInverter(num2.first);

    //Applying the addition algorithm (Karatsuba)
    //a = a1 + a0
    //b = b1 + b0

    //ASSERTION : carry = 0 or 1
    int carry = 0;
    struct Number result;
    result.first.resize(max(s1,s2)+1);
    if(s1>=s2)
    {
        for(int k = 0; k<s2; k++)
        {
            result.first[k] = (num1.first[k] + num2.first[k] + carry)%base;
            carry = (num1.first[k] + num2.first[k] + carry)/base;
        }
        for(int j = s2; j<s1; j++)
        {
            result.first[j] = (num1.first[j] + carry)%base;
            carry = (num1.first[j] + carry)/base;
        }
    }
    else
    {
        for(int k = 0; k<s1; k++)
        {
            result.first[k] = (num1.first[k] + num2.first[k] + carry)%base;
            carry = (num1.first[k] + num2.first[k] + carry)/base;
        }
        for(int j = s1; j<s2; j++)
        {
            result.first[j] = (num2.first[j] + carry)%base;
            carry = (num2.first[j] + carry)/base;
        }
    }

    if(carry != 0) 
    //Now, since there might be a carry left at the end, add it as the last digit of the result.
    {
        result.first[max(s1,s2)] = carry; 
    }
    //the precision of both the numbers had been set to be same earlier, hence we can choose any of the precisions.
    result.second = num1.second; 
    vecInverter(result.first);
  
    //Now, roundoff the result to the precision given
    apx_adder->roundOff(result, base, precision);
    truncate(result.first);
   
    return result;
}

void adder::vecInverter(vector<int> &v)
//Inverts the vector
{
    vector<int> temp = v;
    int i;
    for(i=v.size() - 1;i>=0;i--)
    {
        v[v.size() - 1 - i] = temp[i];
    }
}

void adder::truncate(vector<int> &v) //Accepts numbers in "LSB at size-1" form
//Remove the excess zeroes from the left
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

