#pragma once
#include <iostream>
#include <vector>
#include <cmath>
#include "adder.hpp"
#include "divider.hpp"
#include "multiplier.hpp"
#include "baseConverter.hpp"
#include "approximator.hpp"
#include "structs.hpp"
using namespace std;
class squareRoot
{
    private :
    adder *a;
    divider *d;
    baseConverter *bConv;
    approximator *apx;
    bool print_flag;

    public :
    squareRoot();
    ~squareRoot();
    struct Number sqRootOf(struct Number &num, int base, int precision);
    bool precisionObtained(struct Number &p, struct Number &q, int base, int precision);  //NOTE : THIS FUNCTION HAS ONLY BEEN USED WHILE TESTING/EXPERIMENTING
    bool getPrintFlag();
    void setPrintFlag(bool printFlag);
    int precisionConverter(int Bi, int P_Bi, int Bf);
};