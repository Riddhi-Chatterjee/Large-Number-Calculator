#include "approximator.hpp"
void approximator::roundOff(struct Number &num, int base, int precision)
{
    //index = number of digits that are required when the decimal point is removed -1
    //This would be the index of the last digit of the number in its vector as the indexing of the vector starts from 0
    int index = num.first.size() + num.second + precision - 1;
    int i;
    
    //To make the index >= 0
    //Like in the case, where the number is [[1], -5] = 0.00001 and required precision is 2, the value of index will be -ve.
    //So we make such an index positive by padding zeroes to the left of the number.
    vecInverter(num.first);
    for(i=0;i<((-1)*index);i++)
    {
        num.first.push_back(0);
    }
    vecInverter(num.first);

    //123.456 = [[1,2,3,4,5,6], -3]
    //If the requested precision is 2, then the vector gets converted to [[1,2,3,4,5], -2] i.e. 123.45
    if(index >= 0 && index <= num.first.size() - 2)
    {
        vector<int> v;
        copy(num.first.begin(), num.first.begin() + index + 1, back_inserter(v));
        num.first = v;
        num.second = -precision;
    }
}

//Used to reverse the ordering of elements in the given vector
void approximator::vecInverter(vector<int> &v) 
{
    vector<int> temp = v;
    int i;
    for(i=v.size() - 1;i>=0;i--)
    {
        v[v.size() - 1 - i] = temp[i];
    }
}
