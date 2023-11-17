#pragma once
#include <vector>
using namespace std;
struct Number //General structure of a number
{
    vector<int> first; //Stores the digits of the number
    int second; //Stores the exponent
    //For example: 123.4567 will have [1,2,3,4,5,6,7] as first field, and -4 as second field
};