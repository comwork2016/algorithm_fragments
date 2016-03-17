#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define BASE 12
#define MODNUM 65536
#define K 10 // 10-gram

using namespace std;

int main()
{
    FILE* fp1,*fp2;
    char ch;

    fp2=fopen("out.txt","w+");
    if((fp1=fopen("in.txt","r")) != NULL)
    {
        int kc = 0;
        char *kstr_last;
        char *kstr_now;
        int hv_now=0;
        kstr_last = (char*)malloc(sizeof(char)*K);
        kstr_now = (char*)malloc(sizeof(char)*K);

        int i;
        int h; //the value of h would be "pow(d, M) % q "
        for( i = 0; i < K; i++)
        {
            h = ( h * BASE ) % MODNUM;
        }


        while((ch=fgetc(fp1))!=EOF)
        {
            if((ch >= 'A' && ch <= 'Z') || (ch >= 'a' && ch <= 'z'))
            {
                if(ch>='A'&&ch<='Z')
                {
                    ch=ch+32;
                }
                // calculate the hashvalue of pattern and first M-len of T
                //H(c 1 . . . ck ) = c1 * b^k−1 + c2 * b^k−2  . . . + ck−1 * b + ck
                if(kc<K)
                {
                    kstr_now[kc] = ch;
                    kstr_last[kc] = ch;
                    hv_now = ( BASE * hv_now + ch*BASE) % MODNUM;
                    kc++;
                }
                else
                {
                    fwrite(kstr_now,strlen(kstr_now),1,fp2);
                    fprintf(fp2,"  %d",hv_now);
                    fputc('\r',fp2);
                    strncpy(kstr_now,kstr_last+1,K-1);
                    kstr_now[K-1] = ch;
                    hv_now = ((hv_now - kstr_now[0]*h + kstr_now[K-1])*BASE)%MODNUM;
                    strcpy(kstr_last,kstr_now);
                }
            }
        }
        fwrite(kstr_now,strlen(kstr_now),1,fp2);
        fprintf(fp2,"\b%d",hv_now);
    }
    fclose(fp1);
    fclose(fp2);
}
