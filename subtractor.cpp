#include "subtractor.hpp"

subtractor::subtractor()
{
    apx_subtractor = new approximator();
}

subtractor::~subtractor()
{
    delete apx_subtractor;
    apx_subtractor = NULL;
}

struct Number subtractor::subtract(struct Number &n1, struct Number &n2, int base, int precision)
{   //Performs n1-n2 operation
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

    //Applying the subtraction algorithm
    //This is almost similar to the addition algorithm, just the a[i]+b[i] part has been replaced by a[i]-b[i]

    //ASSERTION : carry = -1 or 0
    int carry = 0;
    struct Number result;
    result.first.resize(max(s1,s2)+1);
    if(s1>=s2)
    {
        for(int k = 0; k<s2; k++)
        {
            int val = num1.first[k] - num2.first[k] + carry;
            if(val>=0)
            {
                result.first[k] = val%base;
                carry = val/base;
            }
            else
            {
                result.first[k] = ((val%base) + base)%base;
                carry = -1;
            }
        }
        for(int j = s2; j<s1; j++)
        {
            int val = num1.first[j] + carry;
            if(val>=0)
            {
                result.first[j] = val%base;
                carry = val/base;
            }
            else
            {
                result.first[j] = ((val%base) + base)%base;
                carry = -1;
            }
        }
    }
    else
    {
        for(int k = 0; k<s1; k++)
        {
            int val = num1.first[k] - num2.first[k] + carry;
            if(val>=0)
            {
                result.first[k] = val%base;
                carry = val/base;
            }
            else
            {
                result.first[k] = ((val%base) + base)%base;
                carry = -1;
            }
        }
        for(int j = s1; j<s2; j++)
        {
            int val = num2.first[j] + carry;
            if(val>=0)
            {
                result.first[j] = val%base;
                carry = val/base;
            }
            else
            {
                result.first[j] = ((val%base) + base)%base;
                carry = -1;
            }
        }
    }
    /*if(carry != 0)
    {
        result.first[max(s1,s2)] = carry; 
    }*/
    //No need of carry as the numbers will always be num1>num2
    
    //The precision of both the numbers had been set to be same earlier, hence we can choose any of the precisions.
    result.second = num1.second; 
    vecInverter(result.first);
    
    apx_subtractor->roundOff(result, base, precision);
    truncate(result.first);
    return result;
}

void subtractor::vecInverter(vector<int> &v)
{
    vector<int> temp = v;
    int i;
    for(i=v.size() - 1;i>=0;i--)
    {
        v[v.size() - 1 - i] = temp[i];
    }
}

void subtractor::truncate(vector<int> &v) //Accepts numbers in "LSB at size-1" form
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
