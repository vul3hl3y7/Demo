#include<stdio.h>
#include<stdlib.h>
#include<memory.h>
#include<math.h>

int FNT[203][3] ;
int SLG[203][203] ;

int main(void)
{
    int N = 0 ;
    int A = 0 ;
    int B = 0 ;
    int nCounts = 0 ;
    int nT = 0 ;
    int i = 0 ;
    int j = 0 ;
    int n = 0 ;
    int fCanFind = 0 ;
    int fUnfinish = 1 ;

    while(scanf("%d%d%d",&N,&A,&B) != EOF)
    {
        memset(FNT,0,sizeof(FNT)) ;
        memset(SLG,0,sizeof(SLG)) ;

        for(i = 1 ; i <= N ; i++)
        {
            scanf("%d",&FNT[i][0]) ;
        }

        nCounts = 1 ;
        SLG[0][0] = B ;
        fCanFind = 1 ;
        fUnfinish = 1 ;

        for(nT = 0 ; nT <= N ; nT++)
        {
            n = nCounts ;
            nCounts = 0 ;
            if(1 == fCanFind)
            {
                fCanFind = 0 ;

                for(i = 1 ; i <= N ; i++)
                {
                    for(j = 0 ; j < n ; j++)
                    {
                        if(0 == FNT[i][2] && abs(i - SLG[nT][j]) == FNT[i][0])
                        {
                            FNT[i][2] = 1 ;
                            SLG[nT+1][nCounts] = i ;
                            FNT[i][1] = nT + 1 ;
                            nCounts++ ;
                            if(i == A)
                            {
                                fUnfinish = 0 ;
                            }
                            fCanFind = fUnfinish ;
                        }
                    }
                }
            }
        }

        if(A == B)
        {
            printf("%d\n",0) ;
        }
        else if(0 == FNT[A][1])
        {
            printf("%d\n",-1) ;
        }
        else
        {
            printf("%d\n",FNT[A][1]) ;
        }
    }
    return 0 ;
}
