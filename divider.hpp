#pragma once
#include <iostream>
#include <vector>
#include "approximator.hpp"
#include "structs.hpp"
using namespace std;
class divider
{
    private :
    approximator *apx; //Approximator object for performing round off operations
    int normalise(vector<int> &b, vector<int> &a, int B);
    void leftshift(vector<int> &num, int B);
    void truncate(vector<int> &v);
    void rightshift(vector<int> &r, int t, int B);
    void vecInverter(vector<int> &v);

    public :
    divider();
    ~divider();
    struct Number divide(struct Number &num1, struct Number &num2, int base, int precision);
};