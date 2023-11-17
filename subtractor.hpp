#pragma once
#include <iostream>
#include <vector>
#include "approximator.hpp"
#include "structs.hpp"
using namespace std;
class subtractor //Use an approximator object for performing rounding off operations
{
    private :
    approximator *apx_subtractor;
    

    public :
    subtractor();
    ~subtractor();
    void vecInverter(vector<int> &v);
    void truncate(vector<int> &v);
    struct Number subtract(struct Number &n1, struct Number &n2, int base, int precision);
};