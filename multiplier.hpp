#pragma once
#include <iostream>
#include <vector>
#include <cmath>
#include "approximator.hpp"
#include "adder.hpp"
#include "subtractor.hpp"
#include "structs.hpp"
using namespace std;
class multiplier //Use an approximator object for performing rounding off operations
{
    private :
    approximator *apx;
    adder *a;
    subtractor *s;

    public :
    multiplier();
    ~multiplier();
    void truncate(vector<int> &v);
    void vecInverter(vector<int> &v);
    void leftshift(struct Number &num, int t);
    struct Number karatsuba(vector<int> &num1, vector<int> &num2, int base, int precision);
    struct Number multiply(struct Number &num1, struct Number &num2, int base, int precision);
    
};