#ifndef SIMHASH_H
#define SIMHASH_H

#include <iostream>
#include <string>
#include <list>
#include <string.h>

#define SIMHASHBITS 32
#define MODNUM 65535
#define BASE 12

using namespace std;

class SimHash
{
    public:
        SimHash();
        virtual ~SimHash();

        static long CalcSimHash(string str_Contents);
        static int CalcHammingDistance(long l_num1, long l_num2);
    protected:
    private:
};

#endif // SIMHASH_H
