#include "SimHash.h"

SimHash::SimHash()
{
    //ctor
}

long CalcHash(string str)
{
    long l_Hash = 0;
    for(int i=str.length()-1; i>=0; i--)
    {
        char c = str.at(i);
        l_Hash = ( BASE * l_Hash +  int(c)*BASE) % MODNUM;
    }
    return l_Hash;
}

#include <iostream>
#include <string>
#include <vector>

using namespace std;

//splitString函数的参数说明：
//返回值是分割后字符串数组大小
//strSrc 原始字符串
//strDelims 自定义的分割字符串的分割数组
//strDest 分割后的字符串数组，引用传递

list<string> splitString(const string strSource, const string strDelims)
{
    string delims = strDelims;
    string str;
    list<string> strSplited;
    if(delims.empty())
    {
        delims = "/n/r";
    }
    string::size_type pos=0, length = strSource.size();
    while(pos < length )
    {
        str="";
        //pos指到第一个不是delims中的字符的位置
        while( (delims.find(strSource[pos]) != string::npos) && (pos < length) )
        {
            ++pos;
        }
        if(pos==length)
        {
            return strSplited;
        }
        //pos指到下一个是delims中的字符的位置
        while( (delims.find(strSource[pos]) == string::npos) && (pos < length) )
        {
            str += strSource[pos++];
        }
        if(!str.empty() )
        {
            strSplited.push_back(str);
        }
    }
    return strSplited;
}

long SimHash::CalcSimHash(string str_Contents)
{
    int v[SIMHASHBITS];
    for(int i=0; i<SIMHASHBITS; i++)
    {
        v[i] = 0;
    }
    string str_delim=" .!?";
    list<string> strlist_sentence = splitString(str_Contents,str_delim);
    for(list<string>::iterator it = strlist_sentence.begin();it!=strlist_sentence.end();it++)
    {
        string str_temp = *it;
        long l_Hash = CalcHash(str_temp);
        for (int j = 0; j < SIMHASHBITS; j++)
        {
            long bitmask = 1 << j; //位的掩码:向左移j位
            int bit = l_Hash&bitmask;
            if (bit != 0)
            {
                v[j] += 1;
            }
            else
            {
                v[j] -= 1;
            }
        }
    }
    long l_FingerPrints = 0;
    for (int i = 0; i < SIMHASHBITS; i++)
    {
        if (v[i] > 0)
        {
            int n_IBit = 1<<i;
            l_FingerPrints += n_IBit;
        }
    }
    return l_FingerPrints;
}

//计算海明距离
int SimHash::CalcHammingDistance(long l_num1, long l_num2)
{
    int hd = 0;
    int x = l_num1^l_num2;
    while (x)
    {
        hd += 1;
        x = x&(x-1);//减一之后二进制的数字里面会减少一个1
    }
    return hd;
}

SimHash::~SimHash()
{
    //dtor
}
