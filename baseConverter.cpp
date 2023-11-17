#include "baseConverter.hpp"
baseConverter::baseConverter()
{
    a = new adder();
    d = new divider();
}

baseConverter::~baseConverter()
{
    delete a;
    a = NULL;
    delete d;
    d = NULL;
}

void baseConverter::convertToTen(struct Number &num, int base, int precision)
{ //Converts the base of the given number to 10
    int basePower = (-1*num.second); //Stores the exponent separately
    string strTen = DnC_ConverterToTen(num.first, 0, num.first.size() - 1, base); //Modifies num.first by converting its base to 10
    struct Number numerator; //Stores the base 10 representation of num.first
    strToVec(strTen, numerator.first);
    numerator.second = 0;

    struct Number divisor; //Stores the base 10 representation of the exponent portion
    divisor.first.push_back(1);
    int i;
    for(i=0;i<basePower;i++)
    {
        leftshift(divisor.first, 10, base);
    }
    vecInverter(divisor.first);
    divisor.second = 0;

    num = d->divide(numerator, divisor, 10, precision); //Gives us the final base 10 representation of num
}

string baseConverter::DnC_ConverterToTen(vector<int> &nVec, int l, int r, int multiplyingFactor)
{ //Uses a divide and conquer algorithm to convert the base of nVec to 10
    int mid = (l+r)/2;
    string left, right;

    if(l == r) //Handles the base case
    {
        return to_string(nVec[l]);
    }

    left = DnC_ConverterToTen(nVec, l, mid, multiplyingFactor); //Finds out base 10 representation of left half
    right = DnC_ConverterToTen(nVec, mid+1, r, multiplyingFactor); //Finds out base 10 representation of right half

    struct Number numLeft;
    struct Number numRight;
    numLeft.second = 0;
    numRight.second = 0;

    strToVec(left, numLeft.first);
    strToVec(right, numRight.first);

    vecInverter(numLeft.first);

    int i;
    for(i=0;i<(r - mid);i++)
    {
        leftshift(numLeft.first, 10, multiplyingFactor); //Left-shifting the left part appropriate number of times
    }
    vecInverter(numLeft.first);

    struct Number result = a->add(numLeft, numRight, 10, 0); //Combining left and right halves to get the final result

    return vecToStr(result.first);
}

void baseConverter::strToVec(string s, vector<int> &v) //Converts a string to vector<int>
{
    int i;
    v.clear();
    for(i=0;i<s.length();i++)
    {
        v.push_back(s[i]-'0');
    }
}

string baseConverter::vecToStr(vector<int> &v) //Converts a vector<int> to string
{
    string s = "";
    int i;
    for(i=0;i<v.size();i++)
    {
        s += to_string(v[i]);
    }
    return s;
}

void baseConverter::vecInverter(vector<int> &v) //Used to reverse the ordering of elements of the given vector
{
    vector<int> temp = v;
    int i;
    for(i=v.size() - 1;i>=0;i--)
    {
        v[v.size() - 1 - i] = temp[i];
    }
}

void baseConverter::leftshift(vector<int> &num, int B, int multiplyingFactor)
{ //Used to multiply num (which can be considered as a Number with zero exponent) with multiplyingFactor
  //All the operations are performed with B as the underlying base
    int i;
    for(i=0;i<num.size();i++)
    {
        num[i] = multiplyingFactor*num[i]; //Multiplying each element of num with multiplyingFactor
    }
    for(i=0;i<num.size();i++) //Adjusting the digits of num appropriately as per the base B
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

void baseConverter::convertFromTen(struct Number &num, int base, int precision)
{ //Converts the base of the given number from 10 to the given base
    int tenPower = (-1*num.second); //Stores the exponent separately
    struct Number numerator; //Stores num.first with the given base as the underlying base
    numerator.first = DnC_ConverterFromTen(num.first, 0, num.first.size() - 1, 10, base); //Modifies num.first by converting its base from 10 to the given base
    numerator.second = 0;

    struct Number divisor; //Stores the exponent portion with the given base as the underlying base
    divisor.first.push_back(1);
    int i;
    for(i=0;i<tenPower;i++)
    {
        leftshift(divisor.first, base, 10);
    }
    vecInverter(divisor.first);
    divisor.second = 0;

    num = d->divide(numerator, divisor, base, precision); //Gives us the final value of num in which the given base is the underlying base
}

vector<int> baseConverter::DnC_ConverterFromTen(vector<int> &nVec, int l, int r, int multiplyingFactor, int base)
{ //Uses a divide and conquer algorithm to convert the base of nVec from 10 to the given base
    int mid = (l+r)/2;
    vector<int> left, right;

    if(l == r) //Handles the base case
    {
        int i;
        int val = nVec[l];
        vector<int> retVal(1);
        retVal[0] = val;
        for(i=0;i<retVal.size();i++)
        {
            int temp = retVal[i];
            retVal[i] = temp%base;
            if(temp/base != 0)
            {
                if(i+1 == retVal.size())
                {
                    retVal.push_back(0);
                }
                retVal[i+1]+=(temp/base);
            }
        }
        vecInverter(retVal);
        return retVal; //Returning the vector representation of nVec[l] where the given base is the underlying base
    }

    left = DnC_ConverterFromTen(nVec, l, mid, multiplyingFactor, base); //Converts the base of the left half from 10 to the given base
    right = DnC_ConverterFromTen(nVec, mid+1, r, multiplyingFactor, base); //Converts the base of the right half from 10 to the given base

    struct Number numLeft;
    struct Number numRight;
    numLeft.second = 0;
    numRight.second = 0;

    numLeft.first = left;
    numRight.first = right;

    vecInverter(numLeft.first);

    int i;
    for(i=0;i<(r - mid);i++)
    {
        leftshift(numLeft.first, base, multiplyingFactor); //Left-shifting the left part appropriate number of times
    }
    vecInverter(numLeft.first);

    struct Number result = a->add(numLeft, numRight, base, 0); //Combining left and right halves to get the final result

    return result.first;
}