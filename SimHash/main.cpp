#include "SimHash.h"

#include <string>
#include <iostream>

using namespace std;
int main()
{
    string str1 = "This is sim hash test";
    string str2 = "This is sim hash test also";
    string str3 = "This is temp sim hash";
    string str4 = "xia xie de ce shi shu ju asdfasdfjasd asd;fja;sdkljf";
    long sh1 = SimHash::CalcSimHash(str1);
    long sh2 = SimHash::CalcSimHash(str2);
    long sh3 = SimHash::CalcSimHash(str3);
    long sh4 = SimHash::CalcSimHash(str4);
    cout<<"simhash of str1:"<<sh1<<endl;
    cout<<"simhash of str2:"<<sh2<<endl;
    cout<<"simhash of str3:"<<sh3<<endl;
    cout<<"simhash of str4:"<<sh4<<endl;
    cout<<"hamming distance between str1 and str2:"<<SimHash::CalcHammingDistance(sh1,sh2)<<endl;
    cout<<"hamming distance between str1 and str3:"<<SimHash::CalcHammingDistance(sh1,sh3)<<endl;
    cout<<"hamming distance between str1 and str4:"<<SimHash::CalcHammingDistance(sh1,sh4)<<endl;
}
