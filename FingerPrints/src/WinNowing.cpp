#include "WinNowing.h"

WinNowing::WinNowing(string str_InHash)
{
    this->m_strInHash = str_InHash;
    int n_SeparatorIndex = str_InHash.find_last_of("/");
    this->m_strOutFingerPrints = "./out/fingerprints_"+str_InHash.substr(n_SeparatorIndex+6);
}

string WinNowing::PickFingerPrints(int n_WindowSize)
{
    ifstream ifs_InHash;
    ifs_InHash.open(this->m_strInHash.c_str(),ios_base::in);
    ofstream ofs_OutFingerPrints;
    ofs_OutFingerPrints.open(this->m_strOutFingerPrints.c_str(),ios_base::out);
    if(!ifs_InHash.is_open())
    {
        cout<<"open file "+this->m_strInHash+" error"<<endl;
        exit(-1);
    }
    int *pn_Window=new int[n_WindowSize];  //��Ź�ϣֵ�Ĵ��ڣ�������ѭ��ʹ�õ�
    int n_MIN=0;     //��¼��ǰ��Сֵ�ڴ����е�λ��
    int n_POS=n_MIN;     //��¼��Сֵ��ԭ�����г��ֵ�λ��
    // init pn_Window array
    for(int i=0; i<n_WindowSize && !ifs_InHash.eof(); i++)
    {
        string str_Words;
        ifs_InHash>>str_Words;
        ifs_InHash>>pn_Window[i];
        if(pn_Window[n_MIN] > pn_Window[i])
        {
            n_MIN = i;
            n_POS = n_MIN;
        }
    }
    if(ifs_InHash.eof())        //������ֵ����ָ������ʱִ��
    {
        ofs_OutFingerPrints<<"["<<pn_Window[n_MIN]<<","<<(n_POS+1)<<"]"<<endl;
        delete pn_Window;
        return this->m_strOutFingerPrints;
    }
    ofs_OutFingerPrints<<"["<<pn_Window[n_MIN]<<","<<(n_POS+1)<<"]"<<endl;

    int n_RightIndex=n_WindowSize-1;     //ѭ����������h����˳��ԭ���еĹ�ϣֵ��ӵ�������
    int n_HashValue = 0; // temp hash value that read from hash.txt
    while(!ifs_InHash.eof())
    {
        string str_Words;
        ifs_InHash>>str_Words;
        ifs_InHash>>n_HashValue;
        n_RightIndex=(n_RightIndex+1)%n_WindowSize; // ��������һ������
        pn_Window[n_RightIndex]=n_HashValue;   //�����һ����ϣֵ
        if(n_MIN==n_RightIndex) //�������������˵��ǰһ�����ڵ���Сֵ�����Ƴ�����
        {
            n_POS+=n_WindowSize;
            for(int i=(n_RightIndex-1+n_WindowSize)%n_WindowSize; i!=n_RightIndex; i=(i-1+n_WindowSize)%n_WindowSize)   //���ѭ��������Сֵ��ѡȡ��������С�����ҵĹ�ϣֵ
            {
                if(pn_Window[i]<pn_Window[n_MIN])
                {
                    n_POS-=(n_MIN+n_WindowSize-i)%n_WindowSize;
                    n_MIN=i;
                }
            }
            ofs_OutFingerPrints<<"["<<pn_Window[n_MIN]<<","<<(n_POS+1)<<"]"<<endl;
        }
        else //min!=r��˵����ǰ��С�Ĺ�ϣֵ��Ȼ�����ڴ�����
        {
            if(pn_Window[n_RightIndex]<pn_Window[n_MIN]) //��ôֻ��Ҫ�Ƚ�����ӽ��Ĺ�ϣֵ���ɣ������в��ܺ��е��ںţ������ǽ�׳��winnowing������
            {
                n_POS+=(n_RightIndex+n_WindowSize-n_MIN)%n_WindowSize;
                n_MIN=n_RightIndex;
                ofs_OutFingerPrints<<"["<<pn_Window[n_MIN]<<","<<(n_POS+1)<<"]"<<endl;
            }
        }
    }
    delete pn_Window;
    ifs_InHash.close();
    ofs_OutFingerPrints.close();
    return this->m_strOutFingerPrints;
}

WinNowing::~WinNowing()
{
    //dtor
}
