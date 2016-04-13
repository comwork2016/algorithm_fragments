#include <iostream>
#include <string>
#include <vector>

using namespace std;

//splitString�����Ĳ���˵����
//����ֵ�Ƿָ���ַ��������С
//strSrc ԭʼ�ַ���
//strDelims �Զ���ķָ��ַ����ķָ�����
//strDest �ָ����ַ������飬���ô���

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
    string testStr = "�ṩ����_����ҵ ��,���ҵ�磬-�ƶ�ҵ�磬�Ƽ���ҵ���Ȩ��������Ϊҵ��� Ʒ����ҵ�翪�� �ߣ�";
    string delims = ",- _ ����"; //����ָ����飬���Զ������ָ�������" ,./r"��
    vector<string> splitStrs; //�ѷָ����ַ�������vector����
    splitString(testStr,delims, splitStrs); //�����Զ���ķָ��


    //��ʾ�ָ����ַ�������(��vector�洢)
    vector<string>::iterator iter;
    for (iter = splitStrs.begin(); iter != splitStrs.end(); ++iter)
    {
        cout << *iter << endl;
    }
    splitStrs.clear();
}
