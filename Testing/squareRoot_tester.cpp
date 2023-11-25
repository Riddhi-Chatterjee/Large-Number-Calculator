#include "../squareRoot.hpp"
#include "../structs.hpp"
#include <string>

using namespace std;

void strToVecInplace(string s, vector<int> &v);
void strToNum(struct Number &num, string s);
string numToStr(struct Number &num);
vector<int> strToVec(string s);
string vecToStr(vector<int> &v);

int main(int argc, char* argv[])
{ //argument format: ./squareRoot_test <func_to_test> <1_arg_of_func> <2_arg_of_func> ... <expected_result>

    squareRoot *sqt = new squareRoot();

    vector<string> args(argc);
    int i;
    for(i=0;i<argc;i++)
    {
        args[i] = argv[i];
    }

    if(args[1] == "sqRootOf")
    {
        //args[2] -> number
        //args[3] -> base
        //args[4] -> precision
        //args[5] -> expected result

        struct Number num;
        strToNum(num, args[2]);

        int base = stoi(args[3]);
        int precision = stoi(args[4]);

        struct Number result;
        result = sqt->sqRootOf(num, base, precision);

        if(numToStr(result) == args[5])
        {
            cout<<"SUCCESS_"<<numToStr(result);
        }
        else
        {
            cout<<"FAILURE_"<<numToStr(result);
        }

    }
    else if(args[1] == "precisionConverter")
    {
        int Bi = stoi(args[2]);
        int P_Bi = stoi(args[3]);
        int Bf = stoi(args[4]);

        string result = to_string(sqt->precisionConverter(Bi, P_Bi, Bf));

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
    delete sqt;
    sqt = NULL;
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