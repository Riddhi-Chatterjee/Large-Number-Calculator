/*
    Group members: 
    * Riddhi Chatterjee (IMT2020094)
    * Asmita Zjigyasu (IMT2020507)
*/

#include <iostream>
#include <cmath>
#include <chrono>
#include "adder.hpp"
#include "divider.hpp"
#include "multiplier.hpp"
#include "squareRoot.hpp"
#include "baseConverter.hpp"

using namespace std;

int precisionConverter(int Bi, int P_Bi, int Bf);
void printNum(struct Number &num, baseConverter *bConv);
void printVec(vector<int> &v);
void strToNum(struct Number &num, string s, baseConverter *bConv);

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
    cout<<"Choose what you want to compute: [1]: sqrt(n), [2]: PI"<<endl;
    cin>>choice;
    cout<<endl;
    if(choice == 1) //Computing sqrt(n):
    {
        string n;
        int P_10;
        int P_B;
        cout<<"Enter the number 'n' as a decimal string:"<<endl;
        cin>>n;
        cout<<endl;
        cout<<"Enter the number of digits of precision required:"<<endl;
        cin>>P_10;
        cout<<endl;
        chrono::steady_clock::time_point begin = chrono::steady_clock::now(); //Used to calculate the computation time
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
        printNum(result, bConv); //Printing the final result of square root
        
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
    else //Calculating the value of PI:
    {
        int P_10;
        int P_B;
        cout<<"Enter the number of digits of precision required:"<<endl;
        cin>>P_10;
        cout<<endl;
        chrono::steady_clock::time_point begin = chrono::steady_clock::now(); //Used to calculate the computation time
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
        printNum(p2, bConv); //Printing the value of PI

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

void printNum(struct Number &num, baseConverter *bConv) //Used to print a struct Number
{
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