using namespace std;

#include "RabinHash.h"
#include "WinNowing.h"
#include <stdlib.h>
#include <string>

int main()
{
    string str_InDoc = "./in/in.txt";
    RabinHash* p_RH = new RabinHash(str_InDoc);
    string str_OutHash = p_RH->CalcHashValue();
    WinNowing* p_WN = new WinNowing(str_OutHash);
    int n_WindowSize = 30;
    string str_FingerPrints = p_WN->PickFingerPrints(n_WindowSize);
    return 0;
}
