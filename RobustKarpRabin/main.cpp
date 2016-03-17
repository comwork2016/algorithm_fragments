#include <stdio.h>
#include <math.h>
#include <string.h>
#include <stdlib.h>
#define d 12// number of characters in the alphabet


void RABIN_KARP_MATCHER( char *T, char *P, int q)
{
    if(!T || !P || q<=0)
    {
        return;
    }
    int M = strlen( P );
    int N = strlen( T );
    int i, j;
    int p = 0;//hash value for pattern
    int t = 0;//hash value for txt
    int h = 1;

    //the value of h would be "pow(d, M) % q "
    for( i = 0; i < M ; i++)
    {
        h = ( h * d ) % q;
    }

    // calculate the hashvalue of pattern and first M-len of T
    //H(c 1 . . . ck ) = c1 ∗ b^k + c2 ∗ b^k−1 ∗ . . . + ck−1 ∗ b^2 + ck*b
    for( i = 0; i < M; i++)
    {
        p = ( d * p + P[i]*d ) % q;
        t = ( d * t + T[i]*d ) % q;
    }

    //Slide the pattern over text one by one
    for( i = 0; i <= N - M; i++)
    {
        // hashvalue is equal
        if( p == t)
        {
            for( j = 0; j < M; j++)
            {
                if(T[i+j] != P[j])
                {
                    break;
                }
            }
            if( j == M )
            {
                printf("Pattern occurs with shifts: %d\n", i);
            }
        }
        //Caluate hash value for next window of test:Remove leading digit,
        //add trailling digit
        if( i < N - M )
        {
            // H'(c2 . . . ck+1 ) = (H'(c1 . . . ck ) − c1 ∗ b^k + ck+1) ∗ b
            t = ( d * ( t - T[i] * h  + T[i + M] )) % q;
            if( t < 0 )
            {
                t += q;//adjust t to avoid the situation that t is less than 0
            }
        }
    }
}

int main(int argc, char* argv[])
{
    char txt[] = "GEEKS FOR GEEKS";
    char pat[] = "GEE";
    int q = 256; // q is the number that would be moded by hashvalue
    RABIN_KARP_MATCHER( txt, pat, q);
    return 0;
}
