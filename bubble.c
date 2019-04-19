#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define max 1024

int main()
{

    int i;
    int j;
    int n = 0;
    int tmp;
    char d[max];
    char *pch;

    int data[max];

    while(fgets(d,max,stdin) != NULL )
    {
        pch = strtok(d," \n");
        while(pch != NULL)
        {
            data[n] = atoi(pch);
            n++;
            pch = strtok(NULL," \n");
        }
        int k = 0;

        for(i = 0; i < n - 1;i++)
        {
            for(k = 0;  k < n - i - 1; k++)
            {
                if(data[k] > data[k+1])
                {
                    tmp = data[k+1];
                    data[k+1] = data[k];
                    data[k] = tmp;
                }

            }
                            for(j = 0; j < n; j++)
                printf("%d ", data[j]);

                printf("\n", data[j]);
        }

    }



    return 0;
}
