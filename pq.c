#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define max 1000000

int *heap;
int sz = -1;

void insert(int node)
{
	int now = sz++, p, x;

	heap[sz] = node;
	while(now >= 1)
	{
		p = now / 2;
		if(heap[now] > heap[p]) break;

		x = heap[now];
		heap[now] = heap[p];
		heap[p] = x;;
		
		now = p;
	}
}

void array_init(int A[], int num)
{
		int i;		
				srand(time(NULL));
				for (i = 0; i < num; i++)
				{
						 A[i] = ( rand() % (600001)) + (-300000);
						 insert(A[i]);
				}			
}

int delete()
{
	int v = heap[0], now, change, x;
	heap[0] = heap[sz--];
	now = 1;

	while(now * 2 <= sz)
	{
		int fb = 1;
		if(heap[now * 2] < heap[now])
				fb = 0;
		else if((now * 2 + 1 <= sz) && (heap[now * 2 + 1] < heap[now]))
				fb = 0;
		if(fb) break;
		change = now * 2;

		if((now * 2 + 1) <= sz && (heap[now * 2 + 1] < heap[now * 2]))
				change = now * 2 + 1;
		x = heap[change];
		heap[change] = heap[now];
		heap[now] = x;
	}
	return v;
}

int main()
{
	int num = 0;
	int *data;
	char ch;
	int i;
	
	while(1)
	{
		ch = getchar();

		switch(ch)
		{
			case 'N': // initial
			{
				scanf("%d", &num);
				data = (int *)malloc(num * sizeof(int));
				heap = (int *)malloc(max * sizeof(int));
				array_init(data, num);
					printf("Initial priority queue : ");
				for(i = 0; i < num; i++)
					printf("%d ", data[i]);
					printf("\n");
				break;
			}
			
			case 'I': // insert
			{
				int new = 0;
				scanf("%d", &new);
				insert(new);
				printf("Insert element : %d", new);
					printf("\n");
				break;		
			}

			case 'D': //delete
			{
				if(sz >= 0) printf("Delete element : %d", delete());
				else printf("Empty !\n"); 
						printf("\n");
				break;		
			}

			case 'M': // print min = heap
			{
				int size;	
				size = sz;	
				sz = -1;
				printf("Min heap : ");
				for(i = 0; i <= size; i++)
				{
					insert(heap[i]);
				}
				for(i = 0; i <= size; i++)
				{
					printf("%d ", heap[i]);
				}
				printf("\n");
				break;		
			}

			case 'P': // heap sort & print prionity quene
			{
					printf("\n");
				break;		
			}

			case 'E': // quit
			{
				printf("End\n");	
				return 0;			
			}
	
			case 'T': // find min prionity element
			{
				printf("Min priority element : %d\n", heap[0]);	
				break;		
			}
				
			case 'S': // number of prionity element
			{
				printf("Size of prionrity quene : %d\n", sz);	
				break;		
			}

			default : break;
		}
	}
	return 0;		
}
