#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define max 1024

int str(char s[], int a[])
{
    int i = 0;
    char *pch;
    pch = strtok(s, "+-=\n");
    while(pch != NULL)
    {
        a[i] = atoi(pch);
        pch = strtok(NULL, "+-=\n");
        i++;
    }
    return i;
}

void ari(char s[],int a[], int num)
{
    int len = strlen(s);
    int i;
    int result ;
    int j = 0;
    result = a[0];
    for(i = 0; i<len; i++)
    {
        if(s[i] == '+')
        {
        result += a[j+1];
        j++;
        }
        else if(s[i] == '-')
        {
            result -= a[j+1];
            j++;
        }
    }
    printf("%d", result);

    return;
}


int main()
{
    int n;
    char line[max];
    int a[max];
    int num = 0;
    char line2[max];

    scanf("%d", &n);

    while(n != 0)
    {
        scanf("%s", line);
        strcpy(line2,line);
        num = str(line, a);
    //    for(i = 0; i < num; i++)
    //    printf("%d ", a[i]);
   //     printf("%s", line2);
       ari(line2,a, num);
        printf("\n");
        n--;
    }

    return 0;
}
