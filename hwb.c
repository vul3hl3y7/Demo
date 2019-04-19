#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define Max 11

int main()
{
	FILE *fp;

	fp = fopen("maze.txt", "r");

	int i = 0;
	int j;
	char maze[Max][Max];
		while(fgets(maze[i], Max, fp) != NULL) // read maze.txt
		{
			i++;
			fgets(maze[i], Max, fp);
		}
	
	for(i = 0; i < Max; i++)   // print maze
	{
			printf("%s\n", maze[i]);			
	}

	int x1 = 1, y1 = 1;	// rat A init
	int x2 = 99, y2 = 99;// rat B init
	int ratA[Max][Max]; // rat A path
	int ratB[Max][Max]; // rat B path
	
	for(i = 0; i < Max; i++) // init
	{
		for(j = 0; j < Max; j++)
		{
			ratA[i][j] = 0;
			ratB[i][j] = 0;
		}
	}

	visitA(maze, x1, y1);

}

int visitA(char maze[][], int i, int j)
{		
	int top = 0;
	int fin = 0;
		if(maze[i][j] != 'X')
		{
			top++;
			fin = 1;
			return fin;
		}
		else if(visit(maze, i++, j) == 1)// right
		{
			ratA[x1++][y1];
		}
		else if(visit(maze, i, j--) == 1)	// down
		{
			ratA[x1][y1--];
		}
		else if(visit(maze, i, j++) == 1)	// up
		{
			ratA[x1][y1++];
		}
		else if(visit(maze, i--, j) == 1)	// left
		{
			ratA[x1--][y1];
		} else top--;
}

	return 0;		
}
