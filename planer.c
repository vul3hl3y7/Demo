#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define max 1024

typedef struct point
{
    int id;
    double x;
    double y;
}point;

typedef struct line
{
    int num;

    int p1;
    int p2;

    float len;
} line;

typedef struct point *pline;
typedef struct line *lline;

float calculate_length(float x1, float x2, float y1, float y2)
{
    float len = 0;

    len = sqrt(pow((x1 - x2), 2) + pow((y1 - y2), 2));

    return len;
}

int line_num(pline p,lline l, int data) // line numbers
{
    int l_num = 0;
    double len = 0;


    int i,j,k;
    k = 0;

    for(i = 0; i < data; i++)
    {
        for(j = i; j < data; j++)
        {
            len = calculate_length(p[i].x,p[j].x,p[i].y,p[j].y);  // between two nodes distance
            if(len <= 1)  // distence must be smaller than 1
            {
                    if(i != j)  // point not equal to itself
                    {
                        l[k].num = k;
                        l[k].p1 = j;
                        l[k].p2 = i;
                        l[k].len = len;
                        k++;
                    }
            }
        }
    }

    l_num = k;

/*
        for(i = 0; i < l_num; i++)
    {
        printf("%d %d %d\n" , l[i].num, l[i].p2, l[i].p1);
    }
*/
    return l_num;
}

void printLine(lline l, int n)
{
    int i;
    FILE *fw;
    fw = fopen("link.txt", "a+");

    fprintf(fw,"%d\n" , n);

    for(i = 0; i < n; i++)
    {
        fprintf(fw,"%d %d %d\n" , l[i].num, l[i].p2, l[i].p1);
    }
    fprintf(fw,"\n");
}


int In_Circle(float x, float y, float radius, float xt, float yt)
{
    int ci = -1;  // 0 is inside the circle
    float len = -1;

    len = calculate_length(x,xt,y,yt);

 //   printf("test node(%lf, %lf), r = %lf, len = %lf\n", xt, yt, radius, len);

    if((len < radius) && (len != 0))
    {
        ci = 0;
    }
    else ci = 1;

    return ci;
}

int line_cut(pline p, lline l, lline N, int n, int data)
{
    int remain = 0;

    int i,j,k;
    int s_id;
    int t_id;

    lline V = (lline)malloc(max * sizeof(struct line));

    for(i = 0; i < n; i++)   // fixed line and make circle to test wheather is node inside circle or not
    {
        s_id = l[i].p2;
        t_id = l[i].p1;

        float mid_x = (p[s_id].x + p[t_id].x) / 2;
        float mid_y = (p[s_id].y + p[t_id].y) / 2;

        float radius = calculate_length(p[s_id].x,mid_x,p[s_id].y,mid_y);

        for(j = 0; j < data; j++)
        {
            if((p[j].id != s_id) && (p[j].id != t_id))
            {
            int c = In_Circle(mid_x, mid_y, radius, p[j].x, p[j].y);

  //         printf("line %d & point %d compare %d\n", l[i].num, p[j].id, c);

            if (c == 0) //  in Circle, must be delete
            {
                V[remain].num = l[i].num;
                V[remain].p1 = l[i].p1;
                V[remain].p2 = l[i].p2;
                remain++;
            }

            }
        }

    }
 //   printLine(V, remain);

    k = 0;
    int cost = 0;
    for(i = 0; i < n; i++)
    {
        cost = 0;
        for(j = 0; j < remain; j++)
        {

            if(l[i].num != V[j].num)
            {
                cost++;
                if(cost == remain)
                {
                N[k].num = l[i].num;
                N[k].p1 = l[i].p1;
                N[k].p2 = l[i].p2;
                k++;


                }
            }
        }
    }

 //   printf("\nk = %d\n", k);
    return k;
}

int main()  // open file & get data
{
    FILE *fp;
    FILE *fw;
    char filename[max];

    printf("Please input the filename : ");

    scanf("%s", filename);
    fp = fopen(filename, "r");

    char buf[20];
    int i;

    pline p = (pline)malloc(max * sizeof(struct point));

    if(fp == NULL) printf("Error opening file.\n");
    else
    {
        fgets(buf, 20, fp);    // first line
    }
    int data = atoi(buf);
//   printf("%s\n", buf);

    for(i = 0; i < data; i++)
    {
        fscanf(fp, "%d\t%lf\t%lf\n", &p[i].id, &p[i].x, &p[i].y);
    }
/*    for(i = 0; i < data; i++)
    {
        printf("%d\t%lf\t%lf\n", p[i].id, p[i].x, p[i].y);
    }
*/
    fclose(fp);

    fw = fopen("link.txt", "a+");

    lline l = (lline)malloc(max * sizeof(struct line));

    int l_id = line_num(p,l,data);
    printf("\nPart 1 . Show distence of all lines which is smaller then one :\n");

    printLine(l, l_id);
    printf("\n");
    lline N = (lline)malloc(max * sizeof(struct line));

    int after_cut_id = line_cut(p,l,N,l_id,data);
    printf("\nPart 2 . Part 2 . Remove the line where exist other nodes in the closed disc :\n");

   printLine(N, after_cut_id);


    return 0;
}
