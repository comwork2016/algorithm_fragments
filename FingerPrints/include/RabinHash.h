#ifndef RABINHASH_H
#define RABINHASH_H
#define LEN_MAX_FILENAME 20
#define BASE 12
#define MODNUM 65535
#define K 20 // 20-gram

#include <string.h>
#include <fstream>
#include <iostream>
#include <stdlib.h>

using namespace std;

class RabinHash
{
    public:
        RabinHash(string str_InDoc);
        virtual ~RabinHash();
        string GetstrInDoc() { return m_strInDoc; }
        void SetstrInDoc(string val) { m_strInDoc = val; }
        string GetstrOutHash() { return m_strOutHash; }
        void SetstrOutHash(string val) { m_strOutHash = val; }

        string CalcHashValue();
    protected:
    private:
        string m_strInDoc;
        string m_strOutHash;
};

#endif // RABINHASH_H
