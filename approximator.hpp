#pragma once
#include <iostream>
#include <vector>
#include <algorithm> // for copy()
#include <iterator> // for back_inserter
#include "structs.hpp"
using namespace std;
class approximator
{
    public :
    void roundOff(struct Number &num, int base, int precision);
    void vecInverter(vector<int> &v);
    
};