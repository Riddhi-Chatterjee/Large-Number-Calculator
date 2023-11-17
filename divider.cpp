#include "divider.hpp"
divider::divider()
{
    apx = new approximator();
}

divider::~divider()
{
    delete apx;
    apx = NULL;
}

struct Number divider::divide(struct Number &num1, struct Number &num2, int base, int precision)
{ //Performs num1/num2 operation
    int i,t;
    int B = base;
    vector<int> a = num1.first; //Dividend
    vector<int> b = num2.first; //Divisor
    vector<int> r; //Stores the remainder
    

    //Modifying the dividend and the divisor to make sure that the final answer has the required precision:
    int numeratorShift = num1.second - num2.second + precision + 1;
    
    for(i=0;i<numeratorShift;i++)
    {
        a.push_back(0);
    }
    if(numeratorShift<0)
    {
        for(i=0;i<((-1)*numeratorShift);i++)
        {
            b.push_back(0);
        }
    }
   

    vecInverter(a);
    vecInverter(b);

    t = normalise(b, a, B); //Normalisation

    int l = b.size() - 1;
    int k = a.size() - 1 - l;
    vector<int> q(k+1,0); //Stores the quotient

    for(i=0;i<a.size();i++)
    {
        r.push_back(a[i]); //Initialising r to a
    }
    r.push_back(0);

    //Running the division algorithm:
    for(i=k;i>=0;i--)
    {

        /*
            ASSERTIONS:
            * r = summation{k=0 to i+l}(r[k]*(B^k))
            * Assuming q[k],...,q[i+1] are already determined correctly:
              r = a - summation{k=i+1 to k}(q[k]*b*(B^k))
            * At the end of the algorithm r will store the remainder, and q will store the quotient
        */

        q[i] = r[i+l]/b[l]; //An good estimate of q[i]
        
        int carry = 0;
        int j;
        for(j=0;j<=l;j++) //Subtraction operation
        {
            int val = r[i+j] - q[i]*b[j] + carry;
            if(val < 0)
            {
                r[i+j] = ((val%B) + B)%B;
                carry = (val - (((val%B) + B)%B))/B;
            }
            else
            {
                r[i+j] = val%B;
                carry = val/B;
            }
        }
        r[i+l+1] = r[i+l+1] + carry;

        while(r[i+l+1] < 0) //If we have subtracted too much, then trying to obtain the exact value of q[i]
        {
            carry = 0;
            for(j=0;j<=l;j++)
            {
                int val = r[i+j] + b[j] + carry;
                r[i+j] = val%B;
                carry = val/B;
            }
            r[i+l+1] = r[i+l+1] + carry;
            q[i] = q[i] - 1;
        }
        //Now we have the exact value of q[i]
        if(i != 0)
        {
            r[i+l-1] = r[i+l]*B + r[i+l-1];
            r.pop_back();
            r.pop_back();
            r.push_back(0);
        }
    }


    rightshift(r, t, B); //Right-shifting the remainder now because of the normalisation that we did earlier
    truncate(q); //Removing useless leading zeros from q
    truncate(r); //Removing useless leading zeros from r


    struct Number result; //Stores the final result of the division
    result.first.clear();
    for(i=q.size()-1;i>=0;i--)
    {
        result.first.push_back(q[i]); //Sets the first field of result to the quotient that we obtained
    }
    result.second = -(precision + 1); //Setting the second field of result
   
    apx->roundOff(result, base, precision); //Rounding off result to the required precision

    return result; //Returning the final result of the division
}

int divider::normalise(vector<int> &b, vector<int> &a, int B) //Performs the normalisation
{
    int t = 0;
    int l = b.size() - 1;
    while((b[l]*b[l]) < B)
    {
        leftshift(b, B);
        leftshift(a, B);
        t++;
    }
    return t;
}

void divider::leftshift(vector<int> &num, int B) //Performs a left shift operation
{
    int i;
    for(i=0;i<num.size();i++)
    {
        num[i] = 2*num[i];
    }
    for(i=0;i<num.size();i++)
    {
        int temp = num[i];
        num[i] = temp%B;
        if(temp/B != 0)
        {
            if(i+1 == num.size())
            {
                num.push_back(0);
            }
            num[i+1]+=(temp/B);
        }
    }
}

void divider::truncate(vector<int> &v) //Used to remove useless leading zeros from a vector
{
    int i=v.size()-1;
    while(i != 0 && v[i] == 0)
    {
        v.pop_back();
        i--;
    }
}

void divider::rightshift(vector<int> &r, int t, int B) //Performs right shift operation t times
{
    int i,d=1;
    for(i=0;i<t;i++)
    {
        d*=2;
    }
    for(i=r.size()-1;i>=0;i--)
    {
        int temp = r[i];
        r[i] = temp/d;
        if(temp%d != 0)
        {
            r[i-1] += (B*(temp%d));
        }
    }
}

void divider::vecInverter(vector<int> &v) //Used to reverse the ordering of elements in the given vector
{
    vector<int> temp = v;
    int i;
    for(i=v.size() - 1;i>=0;i--)
    {
        v[v.size() - 1 - i] = temp[i];
    }
}