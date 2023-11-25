#include "../baseConverter.hpp"
#include "../structs.hpp"
#include <string>

using namespace std;

void strToVecInplace(string s, vector<int> &v);
void strToNum(struct Number &num, string s);
string numToStr(struct Number &num);
vector<int> strToVec(string s);
string vecToStr(vector<int> &v);

int main(int argc, char* argv[])
{ //argument format: ./baseConverter_test <func_to_test> <1_arg_of_func> <2_arg_of_func> ... <expected_result>

    baseConverter *bConv = new baseConverter();

    vector<string> args(argc);
    int i;
    for(i=0;i<argc;i++)
    {
        args[i] = argv[i];
    }

    if(args[1] == "convertToTen")
    {
        //args[2] -> number
        //args[3] -> base
        //args[4] -> precision
        //args[5] -> expected result

        struct Number num;
        strToNum(num, args[2]);

        int base = stoi(args[3]);
        int precision = stoi(args[4]);

        bConv->convertToTen(num, base, precision);

        if(numToStr(num) == args[5])
        {
            cout<<"SUCCESS_"<<numToStr(num);
        }
        else
        {
            cout<<"FAILURE_"<<numToStr(num);
        }

    }
    else if(args[1] == "convertFromTen")
    {
        //args[2] -> number
        //args[3] -> base
        //args[4] -> precision
        //args[5] -> expected result

        struct Number num;
        strToNum(num, args[2]);

        int base = stoi(args[3]);
        int precision = stoi(args[4]);

        bConv->convertFromTen(num, base, precision);

        if(numToStr(num) == args[5])
        {
            cout<<"SUCCESS_"<<numToStr(num);
        }
        else
        {
            cout<<"FAILURE_"<<numToStr(num);
        }

    }
    else if(args[1] == "vecInverter")
    {
        vector<int> v = strToVec(args[2]);

        bConv->vecInverter(v);

        string result = vecToStr(v);

        if(result == args[3])
        {
            cout<<"SUCCESS_"<<result;
        }
        else
        {
            cout<<"FAILURE_"<<result;
        }
    }
    else if(args[1] == "leftshift")
    {
        vector<int> num = strToVec(args[2]);
        int B = stoi(args[3]);
        int multiplyingFactor = stoi(args[4]);

        bConv->leftshift(num, B, multiplyingFactor);

        string result = vecToStr(num);

        if(result == args[5])
        {
            cout<<"SUCCESS_"<<result;
        }
        else
        {
            cout<<"FAILURE_"<<result;
        }
    }
    else if(args[1] == "DnC_ConverterToTen")
    {
        vector<int> nVec = strToVec(args[2]);
        int l = stoi(args[3]);
        int r = stoi(args[4]);
        int multiplyingFactor = stoi(args[5]);

        string result = bConv->DnC_ConverterToTen(nVec, l, r, multiplyingFactor);

        if(result == args[6])
        {
            cout<<"SUCCESS_"<<result;
        }
        else
        {
            cout<<"FAILURE_"<<result;
        }
    }
    else if(args[1] == "DnC_ConverterFromTen")
    {
        vector<int> nVec = strToVec(args[2]);
        int l = stoi(args[3]);
        int r = stoi(args[4]);
        int multiplyingFactor = stoi(args[5]);
        int base = stoi(args[6]);

        vector<int> ret = bConv->DnC_ConverterFromTen(nVec, l, r, multiplyingFactor, base);
        string result = vecToStr(ret);

        if(result == args[7])
        {
            cout<<"SUCCESS_"<<result;
        }
        else
        {
            cout<<"FAILURE_"<<result;
        }
    }

    //Freeing memory:
    delete bConv;
    bConv = NULL;
}

void strToVecInplace(string s, vector<int> &v) //Converts a string to vector<int>
{
    int i;
    v.clear();
    for(i=0;i<s.length();i++)
    {
        v.push_back(s[i]-'0');
    }
}

void strToNum(struct Number &num, string s)
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
    strToVecInplace(left+right, num.first);
}

string numToStr(struct Number &num)
{
    string result = "";

    int i;
    for(i=0;i<num.first.size();i++)
    {
        result += ((char)('0'+num.first[i]));
        if(i == num.first.size()+num.second-1)
        {
            result += ".";
        }
    }

    return result;
}

vector<int> strToVec(string s)
{
    vector<int> result;
    string num="";
    int i;
    for(i=0;i<s.length();i++)
    {
        if(s[i] == ',')
        {
            if(num != "")
            {
                result.push_back(stoi(num));
            }
            num="";
            continue;
        }

        num += s[i];
    }

    if(num != "")
    {
        result.push_back(stoi(num));
    }

    return result;
}

string vecToStr(vector<int> &v)
{
    string result = "";
    int i;
    for(i=0;i<v.size();i++)
    {
        if(i == 0)
        {
            result += to_string(v[i]);
        }
        else
        {
            result += (','+to_string(v[i]));
        }
    }

    return result;
}