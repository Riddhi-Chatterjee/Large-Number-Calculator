#pragma once
#include <iostream>
#include <vector>
#include <cmath>
#include "adder.hpp"
#include "divider.hpp"
#include "structs.hpp"
using namespace std;
class baseConverter
{
    private :
    adder *a;
    divider *d;

    public :
    baseConverter();
    ~baseConverter();
    void convertToTen(struct Number &num, int base, int precision);
    void convertFromTen(struct Number &num, int base, int precision);
    void strToVec(string s, vector<int> &v);
    void vecInverter(vector<int> &v);
    void leftshift(vector<int> &num, int B, int multiplyingFactor);
    string DnC_ConverterToTen(vector<int> &nVec, int l, int r, int multiplyingFactor);
    vector<int> DnC_ConverterFromTen(vector<int> &nVec, int l, int r, int multiplyingFactor, int base);
    string vecToStr(vector<int> &v);
};