#ifndef WINNOWING_H
#define WINNOWING_H

#include <fstream>
#include <iostream>
#include <stdlib.h>

using namespace std;


class WinNowing
{
    public:
        WinNowing(string str_InHash);
        virtual ~WinNowing();
        string GetstrInHash() { return m_strInHash; }
        void SetstrInHash(string val) { m_strInHash = val; }
        string GetstrOutFingerPrints() { return m_strOutFingerPrints; }
        void SetstrOutFingerPrints(string val) { m_strOutFingerPrints = val; }
        string PickFingerPrints(int n_WindowSize);
    protected:
    private:
        string m_strInHash;
        string m_strOutFingerPrints;
};

#endif // WINNOWING_H
