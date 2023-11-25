#include "../divider.hpp"
#include "../structs.hpp"
#include <string>

using namespace std;

void strToVecInplace(string s, vector<int> &v);
void strToNum(struct Number &num, string s);
string numToStr(struct Number &num);
vector<int> strToVec(string s);
string vecToStr(vector<int> &v);

int main(int argc, char* argv[])
{ //argument format: ./divider_test <func_to_test> <1_arg_of_func> <2_arg_of_func> ... <expected_result>

    divider *dvdr = new divider();

    vector<string> args(argc);
    int i;
    for(i=0;i<argc;i++)
    {
        args[i] = argv[i];
    }

    if(args[1] == "divide")
    {
        //args[2] -> number 1
        //args[3] -> number 2
        //args[4] -> base
        //args[5] -> precision
        //args[6] -> expected result

        struct Number num1;
        strToNum(num1, args[2]);

        struct Number num2;
        strToNum(num2, args[3]);

        int base = stoi(args[4]);
        int precision = stoi(args[5]);

        struct Number result;
        result = dvdr->divide(num1, num2, base, precision);

        if(numToStr(result) == args[6])
        {
            cout<<"SUCCESS_"<<numToStr(result);
        }
        else
        {
            cout<<"FAILURE_"<<numToStr(result);
        }

    }
    else if(args[1] == "normalise")
    {
        vector<int> b = strToVec(args[2]);
        vector<int> a = strToVec(args[3]);
        int B = stoi(args[4]);

        string result = to_string(dvdr->normalise(b, a, B));

        if(result == args[5])
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

        dvdr->leftshift(num, B);

        string result = vecToStr(num);

        if(result == args[4])
        {
            cout<<"SUCCESS_"<<result;
        }
        else
        {
            cout<<"FAILURE_"<<result;
        }        
    }
    else if(args[1] == "truncate")
    {
        vector<int> v = strToVec(args[2]);

        dvdr->truncate(v);

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
    else if(args[1] == "vecInverter")
    {
        vector<int> v = strToVec(args[2]);

        dvdr->vecInverter(v);

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
    else if(args[1] == "rightshift")
    { //void rightshift(vector<int> &r, int t, int B);
        vector<int> r = strToVec(args[2]);
        int t = stoi(args[3]);
        int B = stoi(args[4]);

        dvdr->rightshift(r, t, B);

        string result = vecToStr(r);

        if(result == args[5])
        {
            cout<<"SUCCESS_"<<result;
        }
        else
        {
            cout<<"FAILURE_"<<result;
        }
    }

    //Freeing memory:
    delete dvdr;
    dvdr = NULL;
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