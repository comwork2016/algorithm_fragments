#include <iostream>
#include <string>
#include <vector>

using namespace std;

//splitString函数的参数说明：
//返回值是分割后字符串数组大小
//strSrc 原始字符串
//strDelims 自定义的分割字符串的分割数组
//strDest 分割后的字符串数组，引用传递

int  splitString(const string & strSrc, const string& strDelims, vector<string>& strDest)
{
    typedef string::size_type ST;
    string delims = strDelims;
    string STR;
    if(delims.empty())
    {
        delims = "/n/r";
    }
    ST pos=0, LEN = strSrc.size();
    while(pos < LEN )
    {
        STR="";
        while( (delims.find(strSrc[pos]) != string::npos) && (pos < LEN) )
        {
            ++pos;
        }
        if(pos==LEN)
        {
            return strDest.size();
        }
        while( (delims.find(strSrc[pos]) == string::npos) && (pos < LEN) )
        {
            STR += strSrc[pos++];
        }
        if( ! STR.empty() )
        {
            strDest.push_back(STR);
        }
    }
    return strDest.size();
}


int main()
{
    string testStr = "提供关于_开发业 界,软件业界，-移动业界，云计算业界的权威报道，为业界产 品经理，业界开发 者，";
    string delims = ",- _ ，，"; //定义分割数组，可以定义多个分隔符，如" ,./r"等
    vector<string> splitStrs; //把分割后的字符串存在vector里面
    splitString(testStr,delims, splitStrs); //调用自定义的分割函数


    //显示分割后的字符串数组(用vector存储)
    vector<string>::iterator iter;
    for (iter = splitStrs.begin(); iter != splitStrs.end(); ++iter)
    {
        cout << *iter << endl;
    }
    splitStrs.clear();
}
