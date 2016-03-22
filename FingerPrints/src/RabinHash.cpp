#include "RabinHash.h"

RabinHash::RabinHash(string str_InDoc)
{
    //ctor
    this->m_strInDoc = str_InDoc;
    int n_SeparatorIndex = str_InDoc.find_last_of("/");
    this->m_strOutHash = "./tmp/hash_"+str_InDoc.substr(n_SeparatorIndex+1);
}

string RabinHash::CalcHashValue()
{
    ifstream ifs_InDoc;
    ifs_InDoc.open(this->m_strInDoc.c_str(),ios_base::in);
    ofstream ofs_OutHash;
    ofs_OutHash.open(this->m_strOutHash.c_str(),ios_base::out);
    if(!ifs_InDoc.is_open())
    {
        cout<<"open file "+this->m_strInDoc+" error"<<endl;
        exit(-1);
    }
    int n_mul=1; //the value of n_mul would be "pow(BASE, K) % MODNUM"
    for(int i = 0; i < K; i++)
    {
        n_mul = ( n_mul * BASE ) % MODNUM;
    }
    int n_kcount = 0;
    char* pch_NowStr;
    char* pch_LastStr; //保存上一个字符串
    pch_LastStr = (char*)malloc(sizeof(char)*(K+1));
    pch_NowStr = (char*)malloc(sizeof(char)*(K+1));
    int n_HashNow=0; //当前字符串的哈希值
    while(!ifs_InDoc.eof())
    {
        char c;
        c=ifs_InDoc.get();
        if((c >= 'A' && c <= 'Z') || (c >= 'a' && c <= 'z'))
        {
            if(c>='A'&&c<='Z')
            {
                c=c+32;
            }
            //H(k1 .. kn) = k1*b^k + k2*b^k-1 +...+ kn*b
            if(n_kcount<K)
            {
                pch_NowStr[n_kcount] = c;
                pch_LastStr[n_kcount] = c;
                n_HashNow = ( BASE * n_HashNow + c*BASE) % MODNUM;
                n_kcount++;
            }
            else
            {
                pch_NowStr[K] = '\0';
                pch_LastStr[K] = '\0';
                // write k-gram string and hash value to ofs_OutHash
                ofs_OutHash<<pch_NowStr<<"	"<<n_HashNow<<endl;
                // update kstr_now, kstr_now and hv_now
                strncpy(pch_NowStr,pch_LastStr+1,K-1);
                pch_NowStr[K-1] = c;
                pch_NowStr[K] = '\0';
                n_HashNow = ((n_HashNow - pch_NowStr[0]*n_mul + pch_NowStr[K-1])*BASE)%MODNUM;
                if(n_HashNow<0)
                {
                    n_HashNow += MODNUM;
                }
                strcpy(pch_LastStr,pch_NowStr);
            }
        }
    }
    ofs_OutHash<<pch_NowStr<<"	"<<n_HashNow;
    ifs_InDoc.close();
    ofs_OutHash.close();
    return this->m_strOutHash;
}


RabinHash::~RabinHash()
{
    //dtor
}
