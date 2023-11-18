/*
    Group members: 
    * Riddhi Chatterjee (IMT2020094)
    * Ankrutee Arora (IMT2020034)
*/

#include <iostream>
#include <cmath>
#include <chrono>
#include <string>
#include "adder.hpp"
#include "subtractor.hpp"
#include "divider.hpp"
#include "multiplier.hpp"
#include "squareRoot.hpp"
#include "baseConverter.hpp"

using namespace std;

int precisionConverter(int Bi, int P_Bi, int Bf);
void printNum(struct Number &num, baseConverter *bConv, bool neg_res);
void printVec(vector<int> &v);
void strToNum(struct Number &num, string s, baseConverter *bConv);
struct Number addPosNum(struct Number &num1, struct Number &num2, int iBase, int precision);
struct Number subPosNum(struct Number &num1, struct Number &num2, int iBase, int precision);
struct Number mulPosNum(struct Number &num1, struct Number &num2, int iBase, int precision);
struct Number divPosNum(struct Number &num1, struct Number &num2, int iBase, int precision);
string ABS(string s);
bool validateStrNum(string &s);
bool validateStrPrec(string &s);
bool absGeq(string a, string b);

int main()
{
    int INTERNAL_BASE_POWER; //Base = 2^(INTERNAL_BASE_POWER) for internal computations
    //cout<<"For internal computations, the base is 2^m. Enter the value of m:"<<endl;
    //cin>>INTERNAL_BASE_POWER;
    INTERNAL_BASE_POWER = 10; //Setting INTERNAL_BASE_POWER to 10 for optimal performance
    //cout<<endl;

    int PRECISION_PAD_DIGITS = 6; //Padding extra 6 digits of precision as compared to the required precision.

    int iBase;
    iBase = (int)pow(2, INTERNAL_BASE_POWER); //The base for internal computations

    int choice;
    cout<<endl;
    cout<<"Choose an operation:"<<endl;
    cout<<"[1]: Add two numbers"<<endl;
    cout<<"[2]: Subtract two numbers"<<endl;
    cout<<"[3]: Multiply two numbers"<<endl;
    cout<<"[4]: Divide two numbers"<<endl;
    cout<<"[5]: Compute square root of a number"<<endl;
    cout<<"[6]: Compute the value of PI"<<endl;
    cout<<endl;
    cin>>choice;
    cout<<endl;

    if(choice == 1) //(a+b)
    {
        string a;
        string b;
        int P_10;
        int P_B;
        cout<<"Computing a+b..."<<endl<<endl;
        cout<<"Enter the number 'a' as a decimal string:"<<endl;
        cin>>a;
        cout<<endl;

        if(validateStrNum(a))
        {
            cout<<"Enter the number 'b' as a decimal string:"<<endl;
            cin>>b;
            cout<<endl;

            if(validateStrNum(b))
            {
                string str_P_10;
                cout<<"Enter the number of digits of precision required:"<<endl;
                cin>>str_P_10;
                cout<<endl;

                if(validateStrPrec(str_P_10))
                {
                    chrono::steady_clock::time_point begin = chrono::steady_clock::now(); //Used to calculate the computation time
                    
                    P_10 = stoi(str_P_10);
                    bool neg_a = (a[0] == '-');
                    bool neg_b = (b[0] == '-');
                    a = ABS(a);
                    b = ABS(b);

                    P_10 = P_10 + PRECISION_PAD_DIGITS;
                    P_B = precisionConverter(10, P_10, iBase); //Finding out the equivalent precision in iBase

                    baseConverter *bConv = new baseConverter();

                    struct Number num1;
                    strToNum(num1, a, bConv);
                    int inputPrecision = precisionConverter(10, ((-1)*num1.second) + PRECISION_PAD_DIGITS, iBase);
                    bConv->convertFromTen(num1, iBase, inputPrecision); //Converting the base of the input number from 10 to iBase

                    struct Number num2;
                    strToNum(num2, b, bConv);
                    inputPrecision = precisionConverter(10, ((-1)*num2.second) + PRECISION_PAD_DIGITS, iBase);
                    bConv->convertFromTen(num2, iBase, inputPrecision); //Converting the base of the input number from 10 to iBase
                    
                    struct Number result;
                    bool neg_res;

                    if((neg_a && neg_b) || (!neg_a && !neg_b)) //Add the magnitudes
                    {
                        neg_res = (neg_a && neg_b);
                        
                        result = addPosNum(num1, num2, iBase, P_B);

                        bConv->convertToTen(result, iBase, P_10 - PRECISION_PAD_DIGITS); //Converting the base of the final result from iBase to 10
                    }
                    else
                    {
                        if(absGeq(a, b)) //abs(a)>=abs(b)
                        {
                            if(neg_a) //-ve a and +ve b
                            {
                                neg_res = true;
                            }
                            else //+ve a and -ve b
                            {
                                neg_res = false;
                            }
                            result = subPosNum(num1, num2, iBase, P_B);
                        }
                        else //abs(a)<abs(b)
                        {
                            if(neg_a) //-ve a and +ve b
                            {
                                neg_res = false;
                            }
                            else //+ve a and -ve b
                            {
                                neg_res = true;
                            }
                            result = subPosNum(num2, num1, iBase, P_B);
                        }
                    }

                    chrono::steady_clock::time_point end = chrono::steady_clock::now(); //Used to calculate the computation time
                    cout<<"a+b = ";
                    printNum(result, bConv, neg_res); //Printing the final result of the addition operation
                    
                    long long int sec = chrono::duration_cast<chrono::microseconds>(end - begin).count()/1000000;
                    long long int min = sec/60;
                    sec = sec % 60;
                    long long int hr = min/60;
                    min = min % 60;
                    cout<<endl;
                    cout<<"Completed in: "<<hr<<" Hours, "<<min<<" Minutes, "<<sec<<" Seconds"<<endl<<endl; //Printing the computation time

                    //Freeing memory:
                    delete bConv;
                    bConv = NULL;
                }
            }
        }
    }

    else if(choice == 2) //(a-b)
    {
        string a;
        string b;
        int P_10;
        int P_B;
        cout<<"Computing a-b..."<<endl<<endl;
        cout<<"Enter the number 'a' as a decimal string:"<<endl;
        cin>>a;
        cout<<endl;

        if(validateStrNum(a))
        {
            cout<<"Enter the number 'b' as a decimal string:"<<endl;
            cin>>b;
            cout<<endl;

            if(validateStrNum(b))
            {
                string str_P_10;
                cout<<"Enter the number of digits of precision required:"<<endl;
                cin>>str_P_10;
                cout<<endl;

                if(validateStrPrec(str_P_10))
                {
                    chrono::steady_clock::time_point begin = chrono::steady_clock::now(); //Used to calculate the computation time
                    
                    P_10 = stoi(str_P_10);
                    bool neg_a = (a[0] == '-');
                    bool neg_b = (b[0] == '-');
                    a = ABS(a);
                    b = ABS(b);

                    P_10 = P_10 + PRECISION_PAD_DIGITS;
                    P_B = precisionConverter(10, P_10, iBase); //Finding out the equivalent precision in iBase

                    baseConverter *bConv = new baseConverter();

                    struct Number num1;
                    strToNum(num1, a, bConv);
                    int inputPrecision = precisionConverter(10, ((-1)*num1.second) + PRECISION_PAD_DIGITS, iBase);
                    bConv->convertFromTen(num1, iBase, inputPrecision); //Converting the base of the input number from 10 to iBase

                    struct Number num2;
                    strToNum(num2, b, bConv);
                    inputPrecision = precisionConverter(10, ((-1)*num2.second) + PRECISION_PAD_DIGITS, iBase);
                    bConv->convertFromTen(num2, iBase, inputPrecision); //Converting the base of the input number from 10 to iBase
                    
                    struct Number result;
                    bool neg_res;

                    if(!((neg_a && neg_b) || (!neg_a && !neg_b))) //Add the magnitudes
                    {
                        neg_res = (!neg_b);
                        
                        result = addPosNum(num1, num2, iBase, P_B);

                        bConv->convertToTen(result, iBase, P_10 - PRECISION_PAD_DIGITS); //Converting the base of the final result from iBase to 10
                    }
                    else
                    {
                        if(absGeq(a, b)) //abs(a)>=abs(b)
                        {
                            if(neg_a) //-ve a and -ve b
                            {
                                neg_res = true;
                            }
                            else //+ve a and +ve b
                            {
                                neg_res = false;
                            }
                            result = subPosNum(num1, num2, iBase, P_B);
                        }
                        else //abs(a)<abs(b)
                        {
                            if(neg_a) //-ve a and -ve b
                            {
                                neg_res = false;
                            }
                            else //+ve a and +ve b
                            {
                                neg_res = true;
                            }
                            result = subPosNum(num2, num1, iBase, P_B);
                        }
                    }

                    chrono::steady_clock::time_point end = chrono::steady_clock::now(); //Used to calculate the computation time
                    cout<<"a-b = ";
                    printNum(result, bConv, neg_res); //Printing the final result of the subtraction operation
                    
                    long long int sec = chrono::duration_cast<chrono::microseconds>(end - begin).count()/1000000;
                    long long int min = sec/60;
                    sec = sec % 60;
                    long long int hr = min/60;
                    min = min % 60;
                    cout<<endl;
                    cout<<"Completed in: "<<hr<<" Hours, "<<min<<" Minutes, "<<sec<<" Seconds"<<endl<<endl; //Printing the computation time

                    //Freeing memory:
                    delete bConv;
                    bConv = NULL;
                }
            }
        }
    }

    else if(choice == 3) //(a*b)
    {
        string a;
        string b;
        int P_10;
        int P_B;
        cout<<"Computing axb..."<<endl<<endl;
        cout<<"Enter the number 'a' as a decimal string:"<<endl;
        cin>>a;
        cout<<endl;

        if(validateStrNum(a))
        {
            cout<<"Enter the number 'b' as a decimal string:"<<endl;
            cin>>b;
            cout<<endl;

            if(validateStrNum(b))
            {
                string str_P_10;
                cout<<"Enter the number of digits of precision required:"<<endl;
                cin>>str_P_10;
                cout<<endl;

                if(validateStrPrec(str_P_10))
                {
                    chrono::steady_clock::time_point begin = chrono::steady_clock::now(); //Used to calculate the computation time
                    
                    P_10 = stoi(str_P_10);
                    bool neg_a = (a[0] == '-');
                    bool neg_b = (b[0] == '-');
                    a = ABS(a);
                    b = ABS(b);

                    P_10 = P_10 + PRECISION_PAD_DIGITS;
                    P_B = precisionConverter(10, P_10, iBase); //Finding out the equivalent precision in iBase

                    baseConverter *bConv = new baseConverter();

                    struct Number num1;
                    strToNum(num1, a, bConv);
                    int inputPrecision = precisionConverter(10, ((-1)*num1.second) + PRECISION_PAD_DIGITS, iBase);
                    bConv->convertFromTen(num1, iBase, inputPrecision); //Converting the base of the input number from 10 to iBase

                    struct Number num2;
                    strToNum(num2, b, bConv);
                    inputPrecision = precisionConverter(10, ((-1)*num2.second) + PRECISION_PAD_DIGITS, iBase);
                    bConv->convertFromTen(num2, iBase, inputPrecision); //Converting the base of the input number from 10 to iBase
                    
                    struct Number result;
                    bool neg_res;

                    neg_res = (!((neg_a && neg_b) || (!neg_a && !neg_b)));
                    result = mulPosNum(num1, num2, iBase, P_B);

                    chrono::steady_clock::time_point end = chrono::steady_clock::now(); //Used to calculate the computation time
                    cout<<"axb = ";
                    printNum(result, bConv, neg_res); //Printing the final result of the subtraction operation
                    
                    long long int sec = chrono::duration_cast<chrono::microseconds>(end - begin).count()/1000000;
                    long long int min = sec/60;
                    sec = sec % 60;
                    long long int hr = min/60;
                    min = min % 60;
                    cout<<endl;
                    cout<<"Completed in: "<<hr<<" Hours, "<<min<<" Minutes, "<<sec<<" Seconds"<<endl<<endl; //Printing the computation time

                    //Freeing memory:
                    delete bConv;
                    bConv = NULL;
                }
            }
        }
    }

    else if(choice == 4) //(a/b)
    {
        string a;
        string b;
        int P_10;
        int P_B;
        cout<<"Computing a/b..."<<endl<<endl;
        cout<<"Enter the number 'a' as a decimal string:"<<endl;
        cin>>a;
        cout<<endl;

        if(validateStrNum(a))
        {
            cout<<"Enter the number 'b' as a decimal string:"<<endl;
            cin>>b;
            cout<<endl;

            if(validateStrNum(b))
            {
                string str_P_10;
                cout<<"Enter the number of digits of precision required:"<<endl;
                cin>>str_P_10;
                cout<<endl;

                if(validateStrPrec(str_P_10))
                {
                    chrono::steady_clock::time_point begin = chrono::steady_clock::now(); //Used to calculate the computation time
                    
                    P_10 = stoi(str_P_10);
                    bool neg_a = (a[0] == '-');
                    bool neg_b = (b[0] == '-');
                    a = ABS(a);
                    b = ABS(b);

                    P_10 = P_10 + PRECISION_PAD_DIGITS;
                    P_B = precisionConverter(10, P_10, iBase); //Finding out the equivalent precision in iBase

                    baseConverter *bConv = new baseConverter();

                    struct Number num1;
                    strToNum(num1, a, bConv);
                    int inputPrecision = precisionConverter(10, ((-1)*num1.second) + PRECISION_PAD_DIGITS, iBase);
                    bConv->convertFromTen(num1, iBase, inputPrecision); //Converting the base of the input number from 10 to iBase

                    struct Number num2;
                    strToNum(num2, b, bConv);
                    inputPrecision = precisionConverter(10, ((-1)*num2.second) + PRECISION_PAD_DIGITS, iBase);
                    bConv->convertFromTen(num2, iBase, inputPrecision); //Converting the base of the input number from 10 to iBase
                    
                    struct Number result;
                    bool neg_res;

                    neg_res = (!((neg_a && neg_b) || (!neg_a && !neg_b)));
                    result = divPosNum(num1, num2, iBase, P_B);

                    chrono::steady_clock::time_point end = chrono::steady_clock::now(); //Used to calculate the computation time
                    cout<<"a/b = ";
                    printNum(result, bConv, neg_res); //Printing the final result of the subtraction operation
                    
                    long long int sec = chrono::duration_cast<chrono::microseconds>(end - begin).count()/1000000;
                    long long int min = sec/60;
                    sec = sec % 60;
                    long long int hr = min/60;
                    min = min % 60;
                    cout<<endl;
                    cout<<"Completed in: "<<hr<<" Hours, "<<min<<" Minutes, "<<sec<<" Seconds"<<endl<<endl; //Printing the computation time

                    //Freeing memory:
                    delete bConv;
                    bConv = NULL;
                }
            }
        }
    }

    else if(choice == 5) //sqrt(n):
    {
        string n;
        int P_10;
        int P_B;
        cout<<"Computing sqrt(n)..."<<endl<<endl;
        cout<<"Enter the number 'n' as a decimal string:"<<endl;
        cin>>n;
        cout<<endl;

        if(validateStrNum(n))
        {
            if(n[0] == '-')
            {
                cout<<"ERROR: Can't compute square root of a negative number!!"<<endl<<endl;
            }
            else
            {
                string str_P_10;
                cout<<"Enter the number of digits of precision required:"<<endl;
                cin>>str_P_10;
                cout<<endl;

                if(validateStrPrec(str_P_10))
                {
                    chrono::steady_clock::time_point begin = chrono::steady_clock::now(); //Used to calculate the computation time

                    P_10 = stoi(str_P_10);
                    P_10 = P_10 + PRECISION_PAD_DIGITS;
                    P_B = precisionConverter(10, P_10, iBase); //Finding out the equivalent precision in iBase

                    struct Number num;
                    baseConverter *bConv = new baseConverter();
                    strToNum(num, n, bConv);
                    int inputPrecision = precisionConverter(10, ((-1)*num.second) + PRECISION_PAD_DIGITS, iBase);
                    bConv->convertFromTen(num, iBase, inputPrecision); //Converting the base of the input number from 10 to iBase

                    struct Number result;
                    squareRoot *r = new squareRoot();
                    r->setPrintFlag(true);
                    result = r->sqRootOf(num, iBase, P_B); //Calculating the square root

                    bConv->convertToTen(result, iBase, P_10 - PRECISION_PAD_DIGITS); //Converting the base of the final result from iBase to 10

                    chrono::steady_clock::time_point end = chrono::steady_clock::now(); //Used to calculate the computation time
                    cout<<"sqrt(n) = ";
                    printNum(result, bConv, false); //Printing the final result of square root
                    
                    long long int sec = chrono::duration_cast<chrono::microseconds>(end - begin).count()/1000000;
                    long long int min = sec/60;
                    sec = sec % 60;
                    long long int hr = min/60;
                    min = min % 60;
                    cout<<endl;
                    cout<<"Completed in: "<<hr<<" Hours, "<<min<<" Minutes, "<<sec<<" Seconds"<<endl<<endl; //Printing the computation time

                    //Freeing memory:
                    delete bConv;
                    bConv = NULL;

                    delete r;
                    r = NULL;
                }
            }
        }
    }

    else if(choice == 6) //Calculating the value of PI:
    {
        int P_10;
        int P_B;

        string str_P_10;
        cout<<"Enter the number of digits of precision required:"<<endl;
        cin>>str_P_10;
        cout<<endl;

        if(validateStrPrec(str_P_10))
        {
            chrono::steady_clock::time_point begin = chrono::steady_clock::now(); //Used to calculate the computation time

            P_10 = stoi(str_P_10);
            P_10 = P_10 + PRECISION_PAD_DIGITS;
            P_B = precisionConverter(10, P_10, iBase); //Finding out the equivalent precision in iBase

            struct Number a1;
            struct Number a2;
            struct Number b1;
            struct Number b2;
            struct Number p1;
            struct Number p2;

            struct Number two;
            two.first.push_back(2);
            two.second = 0;
            baseConverter *bConv = new baseConverter();
            bConv->convertFromTen(two, iBase, 0);

            struct Number one;
            one.first.push_back(1);
            one.second = 0;
            bConv->convertFromTen(one, iBase, 0);

            adder *adr = new adder();
            divider *dvdr = new divider();
            multiplier *mtlr = new multiplier();
            squareRoot *r = new squareRoot();

            //Applying the Borwein’s exp-2 Algorithm:

            //Initialising variables:
            a1 = r->sqRootOf(two, iBase, P_B);
            p1 = adr->add(two, a1, iBase, P_B);
            p2 = p1;
            b1.first.push_back(0);
            b1.second = 0;
            a2 = a1;
            b2 = b1;
            
            struct Number temp1, temp2, temp3, temp4;

            int c = 8; //Asymptotic constant
            int limit = ceil(c*log10(P_B));
            int it_count = 0;
            while(it_count <= limit)
            {
                int obtainedPrecision = (int)pow(10, (1.0*it_count)/c);
                obtainedPrecision = precisionConverter(iBase, obtainedPrecision, 10);
                cout<<"Iterations: "<<it_count<<" / "<<limit<<", Current Precision: ~"<<obtainedPrecision<<" Digits"<<flush;
                if(it_count+1 <= limit)
                {
                    cout<<'\r';
                }

                it_count++;

                //Internal steps of the algorithm:
                a1 = a2;
                b1 = b2;
                p1 = p2;

                temp1 = r->sqRootOf(a1, iBase, P_B);
                temp2 = dvdr->divide(one, temp1, iBase, P_B);
                temp3 = adr->add(temp1, temp2, iBase, P_B);
                a2 = dvdr->divide(temp3, two, iBase, P_B);

                temp2 = adr->add(one, b1, iBase, P_B);
                temp3 = adr->add(a1, b1, iBase, P_B);
                temp4 = mtlr->multiply(temp2, temp1, iBase, P_B);
                b2 = dvdr->divide(temp4, temp3, iBase, P_B);

                temp1 = adr->add(one, a2, iBase, P_B);
                temp2 = mtlr->multiply(temp1, p1, iBase, P_B);
                temp3 = mtlr->multiply(temp2, b2, iBase, P_B);
                temp4 = adr->add(one, b2, iBase, P_B);
                p2 = dvdr->divide(temp3, temp4, iBase, P_B);

                /*
                    ASSERTION:
                    * p2 will give closer and closer approximations to PI as the algorithm runs
                */
            }
            cout<<endl;
            bConv->convertToTen(p2, iBase, P_10 - PRECISION_PAD_DIGITS); //Converting the base of the final result from iBase to 10
            chrono::steady_clock::time_point end = chrono::steady_clock::now(); //Used to calculate the computation time
            cout<<endl;
            cout<<"PI = ";
            printNum(p2, bConv, false); //Printing the value of PI

            long long int sec = chrono::duration_cast<chrono::microseconds>(end - begin).count()/1000000;
            long long int min = sec/60;
            sec = sec % 60;
            long long int hr = min/60;
            min = min % 60;
            cout<<endl;
            cout<<"Completed in: "<<hr<<" Hours, "<<min<<" Minutes, "<<sec<<" Seconds"<<endl<<endl; //Printing the computation time

            //Freeing memory:
            delete bConv;
            bConv = NULL;

            delete adr;
            adr = NULL;

            delete dvdr;
            dvdr = NULL;

            delete mtlr;
            mtlr = NULL;

            delete r;
            r = NULL; 
        }    
    }

    else
    {
        cout<<"Wrong choice!!"<<endl<<endl;
    }

    cout<<"Process finished with exit code 0"<<endl;
    return 0;
}

int precisionConverter(int Bi, int P_Bi, int Bf)
{ //Used to find out the equivalent precision in Bf(target base), given Bi and the precision in Bi
    int P_Bf = ceil(P_Bi*(log(Bi)/log(Bf)));
    return P_Bf;
}

void strToNum(struct Number &num, string s, baseConverter *bConv)
{  //Converts a number in decimal string notation to struct Number notation
   //For example: "123.45" converted to {[1,2,3,4,5], -2}
    string left = "", right = "";
    int i, leftLen, rightLen;
    for(i=0;i<s.length();i++)
    {
        if(s[i] == '.')
        {
            break;
        }
    }

    leftLen = i;
    if(i == s.length())
    {
        rightLen = 0;
    }
    else
    {
        rightLen = s.length() - 1 - i;
    }

    if(leftLen != 0)
    {
        left = s.substr(0, leftLen);
    }
    if(rightLen != 0)
    {
        right = s.substr(i+1, rightLen);
    }

    num.second = (-1)*rightLen;
    bConv->strToVec(left+right, num.first);
}

void printNum(struct Number &num, baseConverter *bConv, bool neg_res) //Used to print a struct Number
{
    if(neg_res)
    {
        cout<<"-";
    }

    int i;
    int index = num.first.size() + num.second - 1;
    bConv->vecInverter(num.first);
    while(index<0)
    {
        num.first.push_back(0);
        index++;
    }
    bConv->vecInverter(num.first);

    for(i=0;i<=index;i++)
    {
        cout<<num.first[i];
    }
    cout<<".";

    int aft_flag = 0;
    for(i=index+1;i<num.first.size();i++)
    {
        aft_flag = 1;
        cout<<num.first[i];
    }
    if(aft_flag == 0)
    {
        cout<<'\b';
        cout<<' ';
    }
    cout<<endl;
}

void printVec(vector<int> &v) //Used to print a vector
{
    int i;
    cout<<"[";
    for(i=0;i<v.size();i++)
    {
        if(i!=v.size()-1)
        {
            cout<<v[i]<<",";
        }
        else
        {
            cout<<v[i]<<"]"<<endl;
        }
    }
}

struct Number addPosNum(struct Number &num1, struct Number &num2, int iBase, int precision)
{
    adder *adr = new adder();

    struct Number result;
    result = adr->add(num1, num2, iBase, precision);

    //Freeing memory:
    delete adr;
    adr = NULL;

    return result;
}

struct Number subPosNum(struct Number &num1, struct Number &num2, int iBase, int precision) //Works only if num1 >= num2
{
    subtractor *sbtr = new subtractor();

    struct Number result;
    result = sbtr->subtract(num1, num2, iBase, precision);

    //Freeing memory:
    delete sbtr;
    sbtr = NULL;

    return result;
}

struct Number mulPosNum(struct Number &num1, struct Number &num2, int iBase, int precision)
{
    multiplier *mtlr = new multiplier();

    struct Number result;
    result = mtlr-> multiply(num1, num2, iBase, precision);

    //Freeing memory:
    delete mtlr;
    mtlr = NULL;

    return result;
}

struct Number divPosNum(struct Number &num1, struct Number &num2, int iBase, int precision)
{
    divider *dvdr = new divider();

    struct Number result;
    result = dvdr->divide(num1, num2, iBase, precision);

    //Freeing memory:
    delete dvdr;
    dvdr = NULL;

    return result;
}

string ABS(string s)
{
    if(s[0] == '-')
    {
        return s.substr(1);
    }
    else if(s[0] == '+')
    {
        return s.substr(1);
    }
    else
    {
        return s;
    }
}

bool validateStrNum(string &s)
{
    //Not an empty string:
    if(s == "")
    {
        cout<<"ERROR: Input number can't be null"<<endl<<endl;
        return false;
    }

    //Contains atmost one '+' or '-' at the leftmost position:
    int p_count = 0;
    int m_count = 0;
    int i;
    for(i=0;i<s.length();i++)
    {
        if(s[i] == '+')
        {
            p_count++;
            if(p_count >= 2)
            {
                cout<<"ERROR: Input number can't contain more than one + symbols"<<endl<<endl;
                return false;
            }
        }
        if(s[i] == '-')
        {
            m_count++;
            if(m_count >= 2)
            {
                cout<<"ERROR: Input number can't contain more than one - symbols"<<endl<<endl;
                return false;
            }
        }
    }
    if(p_count == 1 && m_count == 1)
    {
        cout<<"ERROR: Input number can't contain both + and - symbols"<<endl<<endl;
        return false;
    }
    if(p_count == 1 && s[0] != '+')
    {
        cout<<"ERROR: + symbol must be present at the leftmost position of the input number"<<endl<<endl;
        return false;
    }
    if(m_count == 1 && s[0] != '-')
    {
        cout<<"ERROR: - symbol must be present at the leftmost position of the input number"<<endl<<endl;
        return false;
    }

    //Contains atmost one decimal point:
    int d_count = 0;
    for(i=0;i<s.length();i++)
    {
        if(s[i] == '.')
        {
            d_count++;
            if(d_count >= 2)
            {
                cout<<"ERROR: Input number can't contain more than one decimal point"<<endl<<endl;
                return false;
            }
        }
    }

    //Contains digits from 0 to 9 (i.e. no illegal characters):
    for(i=0;i<s.length();i++)
    {
        if(!(s[i] == '.' || s[i] == '+' || s[i] == '-' || (s[i] >= '0' && s[i] <= '9')))
        {
            cout<<"ERROR: Input number contains illegal characters"<<endl<<endl;
            return false;
        }
    }

    //Performing standard operations:
    char sign = '+';
    if(s[0] == '+' || s[0] == '-')
    {
        if(s[0] == '-')
        {
            sign = '-';
        }
        s = s.substr(1);
    }

    int l = 0;
    while(l<s.length() && s[l]=='0')
    {
        l++;
    }
    s = s.substr(l);

    if(d_count == 1)
    {
        int r = ((int)(s.length()))-1;
        while(r>=0 && s[r]=='0')
        {
            r--;
        }
        s = s.substr(0, r+1);
    }
        
    if(s == "" || s == ".")
    {
        s = "0";
    }
    else if(s[0] == '.')
    {
        s = '0'+s;
    }
    else if(s[s.length()-1] == '.')
    {
        s = s.substr(0, s.length()-1);
    }

    if(s != "0" && sign == '-')
    {
        s = '-'+s;
    }

    return true;
}

bool validateStrPrec(string &s)
{
    if(!validateStrNum(s))
    {
        return false;
    }

    if(s[0] == '-')
    {
        cout<<"ERROR: Input number must be non-negative"<<endl<<endl;
        return false;
    }
    int i;
    for(i=0;i<s.length();i++)
    {
        if(s[i] == '.')
        {
            cout<<"ERROR: Input number can't be fractional"<<endl<<endl;
            return false;
        }
    }

    return true;
}

bool absGeq(string a, string b)
{
    a = ABS(a);
    b = ABS(b);

    int i;
    for(i=0;i<min(a.size(), b.size()); i++)
    {
        if(a[i] == '.' && b[i] != '.')
        {
            return false;
        }
        else if(b[i] == '.' && a[i] != '.')
        {
            return true;
        }
        
        if(a[i] != b[i])
        {
            return (a[i] >= b[i]);
        }
    }

    return (a.size() >= b.size());
}