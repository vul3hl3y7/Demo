/*
*	Exercise A0 : Basic sorting alg.
*	
*				Implement the following sorting algorithms : Insertion sort, Bubble sort, Quick sort, Merge sort.
*
*					For each data instance and each method, count the number of comparisons.
*
*	Writer : Meng Tsang Tasi
*
*	Date : 2013/9/29
*/

#include<stdio.h>
#include<stdlib.h>
#include<time.h>

#define min 50
#define max 10001

int bubble_sort(int N, int data[], int count);
int insertion_sort(int N, int data[], int count);
int merge_sort(int N, int data[] ,int count);
int merge(int l_max, int r_max, int left[], int right[], int data[], int count);
int q_sort(int data[], int low, int high, int count);

int main(int argc, char *argv[])
{
	FILE *fp;
	char name[min];
	int n = 0;
	int o = 0;
	int number;
	int *num;
	int i = 0;
	long long int count = 0;
	int c = 0;
	int p = 0;
	int *B;
		B = malloc(max * sizeof(int));
	int *I;
		I = malloc(max * sizeof(int));
	int *M;
		M = malloc(max * sizeof(int));
	int *Q;
		Q = malloc(max * sizeof(int));

	num = malloc(max * sizeof(int));

	if(argc == 2) // read command line argvment
	{
		fp = fopen(argv[1], "r");
		if (fp == NULL)
		{
			printf("%s not found !\n", argv[1]);
			return 0;
		}		
	}
	else
	{
		printf("Which file do you want to read ?\n");
		scanf("%s", name);

		fp = fopen(name, "r");
		if (fp == NULL)
		{
			printf("%s not found !\n", argv[1]);
			return 0;
		}
	}
		
		while (fscanf(fp, "%d", &number) != EOF)
		{
			if(o == 0)
			{
				n = number;
				for (i = 0; i < n; i++)
				{
					num[i] = 0;		
				}
				printf("\n\nWhen n = %d, ", n);
				o = n;
				i = 0;
				if ( n <= 30)
					p = 1;
				else p = 0;
			}
			else
			{
				if (o > 0)
				{
					num[i] = number;
					i++;
					o--;
					if (o == 0)
					{
	
	printf("compare numbers :\n");

/*	if (p == 1)
	{
		for(i = 0; i < n; i++)
		{
			printf("%d ", num[i]);		
		}
	}
*/
	for(i = 0; i < n; i++)
	{
		B[i] = num[i];	// copy original array
		I[i] = num[i];
		M[i] = num[i];
		Q[i] = num[i];
	}

	/* Bubble sort */

	count = 0;
		double start1 = (double) clock();
	count = bubble_sort(n, B, count);
		double end1 = (double) clock();
	printf("Bubble sort : %lld\n", count);
//		printf ("Bubble sort => sorted, elapsed time : %f sec\n", (end1 - start1) / 100);

	/* Insertion sort */

	count = 0;
		 start1 = (double) clock();
	count = insertion_sort(n, I, count);
		 end1 = (double) clock();
	printf("Insertion sort : %lld\n", count);
//		printf ("Bubble sort => sorted, elapsed time : %f sec\n", (end1 - start1) / 100);

	/* Merge sort */

	count = 0;
		 start1 = (double) clock();
	count = merge_sort(n, M, count);
		 end1 = (double) clock();
	printf("Merge sort : %lld\n", count);
//		printf ("Bubble sort => sorted, elapsed time : %f sec\n", (end1 - start1) / 100);
	
	/* Quick sort */

	count = 0;
		 start1 = (double) clock();
	count = q_sort(Q, 0, n, count);
		 end1 = (double) clock();
	printf("Quick sort : %lld\n", count);
//		printf ("Bubble sort => sorted, elapsed time : %f sec\n", (end1 - start1) / 100);
	
		if (p == 1)
		{
			for(i = 0; i < n; i++)
			{
				printf("%d ", B[i]);		
			}
		}		
			}
		}
	}
		}

	return 0;
}

int bubble_sort(int N, int data[], int count)
{
	int i;
	int j;

			for (i = N - 1; i > 0; i--){
					for (j = 0; j <= i - 1; j++){
						// ¦¸§Ç¤£¹ï¡A¶i¦æ¥æ´« //
						if (data[j] > data[j + 1]){
								count++; // compare time
								int temp = data[j];
								data[j] = data[j + 1];
								data[j + 1] = temp;
								}
						}
			}
	return count;		
}

int insertion_sort(int N, int data[], int count)
{
	int i;
	int j;

		for (i = 1; i < N; i++){
				int tmp = data[i];
				// ¶i¦æ´`§Ç·j´M¡A¦P®É·h²¾¸ê®Æ¡A¥HªÅ¥X¦ì¸m //
				for (j = i - 1; j >= 0 && data[j] > tmp; j--){
								data[j + 1] = data[j];
								count++;
						}
						data[j + 1] = tmp;
				}
	return count;	
}

int merge_sort(int N, int data[], int count)
{

	if (N <= 1)
		return count;

	int index = 0;
	int r = 0;
	int l = 0;
	int left[N / 2], right[N / 2 + N % 2];

	while(index < (N / 2))
	{
		left[l++] = data[index++];
		count++;
	}
	while(index < N)
	{
		right[r++] = data[index++];
		count++;
	}
	
	merge_sort(l, left, count);
	merge_sort(r, right, count);
	count = merge(l, r, left, right, data, count);

	return count;
}

int merge(int l_max, int r_max, int left[], int right[], int data[], int count)
{
	int index = 0;
	int l = 0;
	int r = 0;

	while(l < l_max && r < r_max)
	{
		count = count + 2;	
		if(left[l] < right[r])
		{				
				data[index++] = left[l++];
				count++;
		}
		else
		{
			data[index++] = right[r++];
			count++;
		}
	}

	while(l < l_max)
	{
		data[index++] = left[l++];
		count++;
	}

	while(r < r_max)
	{
		data[index++] = right[r++];
		count++;
	}

	return count;
}

int q_sort(int data[], int low, int high, int count)
{
	int	pivot_point, pivot_item, i, j, temp;

	if (high <= low)
			return count;

	pivot_item = data[low];
	j = low;

	// §ä¤ñitem¤pªº //
	for(i = low + 1; i <= high; i++)
	{
		if(data[i] >= pivot_item) //¸ ¸õ¹L¤j©ó©Îµ¥©óªº¼Æ
		{
			count++;
			continue;
		}
		j++;
		
		temp = data[i];
		data[i] = data[j];
		data[j] = temp;
	}

	// ±Nitem¦ì§}²¾¨ì¤¤¶¡ //
	pivot_point = j;

	temp = data[low];
	data[low] = data[pivot_point];
	data[pivot_point] = temp;

	q_sort(data, low, pivot_point - 1, count);
	q_sort(data, pivot_point + 1, high, count);

	return count;
}
