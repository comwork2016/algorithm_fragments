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
    int *pn_Window=new int[n_WindowSize];  //存放哈希值的窗口，窗口是循环使用的
    int n_MIN=0;     //记录当前最小值在窗口中的位置
    int n_POS=n_MIN;     //记录最小值在原序列中出现的位置
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
    if(ifs_InHash.eof())        //当窗口值大于指纹总数时执行
    {
        ofs_OutFingerPrints<<"["<<pn_Window[n_MIN]<<","<<(n_POS+1)<<"]"<<endl;
        delete pn_Window;
        return this->m_strOutFingerPrints;
    }
    ofs_OutFingerPrints<<"["<<pn_Window[n_MIN]<<","<<(n_POS+1)<<"]"<<endl;

    int n_RightIndex=n_WindowSize-1;     //循环遍历数组h，按顺序将原序列的哈希值添加到数组中
    int n_HashValue = 0; // temp hash value that read from hash.txt
    while(!ifs_InHash.eof())
    {
        string str_Words;
        ifs_InHash>>str_Words;
        ifs_InHash>>n_HashValue;
        n_RightIndex=(n_RightIndex+1)%n_WindowSize; // 滑动到下一个窗口
        pn_Window[n_RightIndex]=n_HashValue;   //添加下一个哈希值
        if(n_MIN==n_RightIndex) //如果条件成立，说明前一个窗口的最小值将被移除窗口
        {
            n_POS+=n_WindowSize;
            for(int i=(n_RightIndex-1+n_WindowSize)%n_WindowSize; i!=n_RightIndex; i=(i-1+n_WindowSize)%n_WindowSize)   //向后循环查找最小值，选取窗口中最小且最右的哈希值
            {
                if(pn_Window[i]<pn_Window[n_MIN])
                {
                    n_POS-=(n_MIN+n_WindowSize-i)%n_WindowSize;
                    n_MIN=i;
                }
            }
            ofs_OutFingerPrints<<"["<<pn_Window[n_MIN]<<","<<(n_POS+1)<<"]"<<endl;
        }
        else //min!=r就说明当前最小的哈希值依然包含在窗口中
        {
            if(pn_Window[n_RightIndex]<pn_Window[n_MIN]) //那么只需要比较新添加进的哈希值即可，条件中不能含有等于号，否则不是健壮的winnowing方法。
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
