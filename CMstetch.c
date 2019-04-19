#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <limits.h>

#define Max 1024


int myhash(int key, int count, int col, int prime, int *a, int *b)
{
    return (a[count] * key + b[count]) % prime % col;
}

int query(int key, int **map, int row, int col, int prime, int *a, int *b)
{
    int small = INT_MAX;
    int i;

    for(i = 0; i < row; i++)
    {
        int pos = myhash(key, i, col, prime, a, b);
        if (map[i][pos] <= small) // find min count in this row
        {
            small = map[i][pos];
        //    printf("New small count : %d\n", map[r][i]);
        }
    }
    return small;
}

void insert(int key, int **map, int row, int col, int prime, int *a, int *b)   // key for map position
{
    int i;
    int small = prime;
    int pos = -1;

            small = query(key, map, row, col, prime, a, b);     // in row[count] , col[0]~col[col] have min count
      //      printf("small count : %d\n", small);

    for(i = 0; i < row; i++)
    {
            pos = myhash(key, i, col, prime, a, b);
       //     printf("Key will locate at map : row[%d] , col[%d].\n", i, pos);   // locate at map(row , col)
            if(map[i][pos] == small)     // in row[count] , col[0]~col[col] have min count
            {
    //            for(j = 0; j < row; j++)
                map[i][pos]++;
            }
    }

/*
    for(i = 0; i < row; i++)

    {
        for(j = 0; j < col; j++)
        {
            printf("%d ", map[i][j]);
        }
        printf("\n");
    }
*/
}

int get_word_value(char t[], int **map, int row, int col, int prime, int *a, int *b)   // key for map position
{
    int sum = 0;
    int i;

    for(i = 0; i < strlen(t); i++)
    {
        if(t[i] >= 'A' && t[i]<='Z')
        t[i] += 32;

        sum += t[i];
    }
//    printf("change str '%s' into key '%d'\n", t, sum);    // str to integer ASCI code sum
    return sum;
}


void get_word(char s[], int **map, int row, int col, int prime, int *a, int *b)
{
    char *test = strtok(s, "\n ,.?!\t");
    int key = 0;
    while(test != NULL)
    {
    //    printf("%s\n", test);
        key = get_word_value(test, map, row, col, prime, a, b);
        insert(key, map, row, col, prime, a, b);

        test = strtok(NULL, " ,.?!");
    }
}


int main()
{
    FILE *fp;
    char filename[Max];
    int **map;
    int row;
    int col;
    int prime = 2;

    scanf("%s", filename);

    fp = fopen(filename, "r");

    fscanf(fp, "%d %d %d", &row, &col, &prime);
//    row = col = 10;
//    prime = 1019;
//    printf("row = %d, col = %d, prime = %d\n", row, col, prime);

    int i, j;
    map = (int **)malloc(row * sizeof(int *));
    for(i = 0; i < row; i++)
    {
        map[i] = (int *)malloc(col * sizeof(int));
        memset(map[i], 0, sizeof(int) * row);
    }
/*
    for(i = 0; i < row; i++)
    {
        for(j = 0; j < col; j++)
        {
            printf("%d ", map[i][j]);
        }
        printf("\n");
    }
*/
    int *a = (int *)malloc(row * sizeof(int));
    int *b = (int *)malloc(row * sizeof(int));
    for(i = 0; i < row; i++)
    {
        a[i] =  prime * (i + 1) / 10;
        b[i] = a[i] - 50;
    }
/*
    for(i = 0; i < row; i++)
    {
        printf("a[%d] = %d, b[%d] = %d\n", i, a[i], i, b[i]);
    }
*/
    char line[Max];
//    get_word(line, map, row, col, prime, a, b);
    while(fgets(line, Max, fp) != NULL)
    {
  //      printf("%s", line);
        if(strlen(line) > Max + 1)
        {
            printf("This line is too long may fault !\n");
        }
        get_word(line, map, row, col, prime, a, b);
    }

/*
    for(i = 0; i < row; i++)
    {
        for(j = 0; j < col; j++)
        {
            printf("%d ", map[i][j]);
        }
        printf("\n");
    }
*/

    char test[Max];
    int index = -2;
    int min_count = -1;

    while((scanf("%s", test)) != EOF)
    {
        index = get_word_value(test, map, row, col, prime, a, b);

            min_count = query(index, map, row, col, prime, a, b);     // in row[count] , col[0]~col[col] have min count
            printf("%d\n", min_count);
    }

    return 0;
}
