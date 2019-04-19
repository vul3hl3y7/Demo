/*
*	Exercise B : Quene
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define max_quene_size 1000000

typedef enum {false, true} bool;
typedef struct
{
	char name[16];
	int age;
	enum {female, male} sex;
} Quene;

int rear;
int front;
int cap;

void CreateQ();
void AddQ();
void DeleteQ();
bool isEmpty();
bool isFull();

int part(char *L, char *Name, int Age, char *Sex)
{
	char *test;

	test = strtok(L, "{,}");
	strcpy(Name, test);
	test = strtok(NULL, "{,}");
	Age = atoi(test);
	test = strtok(NULL, "{,}");
	strcpy(Sex, test);

	return Age;
}

int main(void)
{
	Quene *q;
	q = (Quene *)malloc(1 * sizeof(Quene));
	cap = 1;
	CreateQ(q);
	int e = 0;
	char c;
	char Line[256];
	char Name[32];
	int Age;
	char Sex[16];

	while (e != 1)
	{
	//	menu();
		c = getchar();
		switch(c)
		{
			case 'A':
			{
				fgets(Line, 256, stdin);
				Age = part(Line, Name, Age, Sex);
				AddQ(q, Name, Age, Sex);
				break;
			}
			case 'D':
			{
				DeleteQ(q);
				break;
			}
			case 'E':
			{
				e = 1;
				printf("quit\n");
				return 0;
				break;
			}
		}
	}		
	return 0;		
}

void CreateQ(Quene *q)
{
	rear = -1;
	front = -1;
	return ;
}

void AddQ(Quene *q, char *Name, int Age, char *Sex)
{
	if(isFull(q))
	{
			cap = 2 * cap;
			printf("Quene full, allocate double size %d\n", cap);	
			q = (Quene *)realloc(q, cap * sizeof(Quene));
			if(2 * cap > max_quene_size)
			{
				printf("Quene is too big, please delete data to add new one.\n");	
				return ;
			}
	}
		strcpy(q[rear].name, Name);
		q[rear].age = Age;

		char se[16];

		if(strcasestr(Sex, "female") != NULL)
		{
			q[rear].sex = 0;
			strcpy(se, "female");
		}
		else if(strcasestr(Sex, "male") != NULL)
		{
			q[rear].sex = 1;
			strcpy(se, "male");
		}
		else
		{
			strcpy(se, "Wrong data.");		
		}

		printf("insert record, name = %s, age = %d, sex = %s;\n", q[rear].name, q[rear].age, se);
		rear = rear + 1;
	return ;
}

void DeleteQ(Quene *q)
{
	if(isEmpty(q))
	{
		printf("Quene is empty !!\n");	
		return ;		
	}
	else
	{
		char dname[32];
		int dage;
		strcpy(dname, q[front].name);
		dage = q[front].age;

		char se[16];
		if (q[front].sex == 0)
		{
			strcpy(se, "female");	
		}
		else if(q[front].sex == 1)
		{
			strcpy(se, "male");		
		}
		else
		{
			strcpy(se, "Wrong data.");	
		}

		front = front + 1;	
		printf("delete {%s,%d,%s},%d elements in quene\n", dname, dage, se, rear - front);
		return ;
	}	
}

bool isEmpty(Quene *q)
{
	return (rear == front);	
}

bool isFull(Quene *q)
{
	return (rear == cap - 1);		
}
