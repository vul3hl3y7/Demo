/*
*	Execrise A : The d-neighbors serch
*
*		Give some POI ( points of interest) and query-set, analysis their relationship.
*
*	Date : 2013/10/10
*
*	Writer : Meng Tseng Tsai
*
*/

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define d_max 60000
#define min 0
#define max 1000000

typedef struct point	// POI(x,y)
{	
	int x;
	int y;
} point;

typedef struct query	// query set(x,y)
{	
	int x;
	int y;
} query;


void grid(point *P, int n, query *Q, int m, int d);	// find d-neighbor

int main(int argc, char *argv[])
{
	FILE *fp;
	char filename[20];

	if(argc == 2)
	{
		fp = fopen(argv[1], "r");		
	}
	else
	{
		printf("Read file name ?\n");
		scanf("%s", filename);
		fp = fopen(filename, "r");
	}

	if(fp == NULL)
	{
		printf("File no found !\n");
		return 0;
	}

	int number;
	int n = 0; //  number of POI
	int m = 0; //  number of query set 
	int d = 0; //  distance of query set
	int i = 0;

	double start = (double)clock();

	fscanf(fp, "%d", &number);
	
			n = number; // number of POI
			point *P;
			query *Q;
			P = (point *)malloc(n * sizeof(point));

			for(i = 0; i < n; i++)
			{
				fscanf(fp, "%d %d", &P[i].x, &P[i].y);	// POI (x,y)	
			}

			fscanf(fp, "%d %d", &m, &d);
			Q = (query *)malloc(m * sizeof(point));

			while( m != 0 || d != 0)	// end point
			{
				for(i = 0; i < m; i++)
				{
					fscanf(fp, "%d %d", &Q[i].x, &Q[i].y);		
				}
				grid(P, n, Q, m, d);	// find d-neighbor
				free(Q);				// free query set for next set
				fscanf(fp, "%d %d", &m, &d);	// number and distance of next query set
				Q = (query *)malloc(m * sizeof(point));	// next query set
			}
		double end = (double) clock();
		printf("%f\n", (end - start)/CLOCKS_PER_SEC);
	return 0;
}

void grid(point *P, int n, query *Q, int m, int d)
{
	int i;
	int j;
	int x1;
	int y1;
	int x2;
	int y2;
	int count = 0;


	for(i = 0; i < m; i++)
	{	
		x1 = Q[i].x;
		y1 = Q[i].y;
//		printf("Px : %d, Py: %d\n", x1, y1);

		for(j = 0; j < n; j++)
		{
			x2 = P[j].x;
			y2 = P[j].y;
//		printf("Qx : %d, Qy: %d\n", x2, y2);

			if (x1 - x2 <= d && y1 - y2 <= d )	// grid |x2 - x1| <= d && |y2 - y1| <= d
			{
				if (x1 - x2 >= -d && y1 - y2 >= -d)
				{
					int a;
					int b;

					a = Q[i].x - P[j].x;
					b = Q[i].y - P[j].y;

					if((a * a) + (b * b) <= (d * d))	// real distance
					{
						count++;
					}
				}
			}
		}
	}	
		printf("%d\n", count);
		count = 0;
}
