/*
*	Exercise B : stack
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define max_stack_size 1000000

typedef enum {false, true} bool;
typedef struct
{
	char name[32];
	int age;
//	char sex[16];
	enum {female, male} sex;
} Stack;
	
	int top;
	int cap;

void CreatS();
void push();
void pop();
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
	Stack *s;
	s = (Stack *)malloc(1 * sizeof(Stack));
	cap = 1;
	CreatS(s);
	int e = 0;
	char c;
	char Line[256];
	char Name[32];
	int Age;
	char Sex[16];

	while (e != 1)
	{
		c = getchar();	
		switch(c)
		{
			case 'A':
			{
				fgets(Line, 256, stdin);
				Age = part(Line, Name, Age, Sex);
				push(s, Name, Age, Sex);
				break;
			}
			case 'D':
			{
				pop(s);
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

void CreatS(Stack *s)
{
	top = -1; // initial
	return ;
}

void push(Stack *s, char *Name, int Age, char *Sex)
{
	if(isFull(s))	
	{
		cap = 2 * cap;	
		printf("Stack full, allocate double size %d\n", cap);	
		s = (Stack *)realloc(s, cap * sizeof(Stack));
		if (2 * cap > max_stack_size)
		{
			printf("Stack is more than 100000 ! Please delete to add new one.");
			return ;
		}
	}
		strcpy(s[top].name, Name);
		s[top].age = Age;

		char se[16];

		if(strcasecmp(Sex, "female") != NULL)
		{
			s[top].sex = 0;
			strcpy(se, "female");
		}
		else if(strcasecmp(Sex, "male") != NULL)
		{
			s[top].sex = 1;
			strcpy(se, "male");
		}
		else
		{
			strcpy(se, "Wrong data.");		
		}

		printf("insert record, name = %s, age = %d, sex = %s;\n", s[top].name, s[top].age, se);
		top = top + 1;
	return ;
}

void pop(Stack *s)
{
	if(isEmpty(s))	
	{
		printf("Stack is empty !!\n");	
		return ;
	}
	else
	{	
		top = top - 1;
		char dname[32];
		int dage;
		strcpy(dname,s[top].name);
		dage = s[top].age;
		char se[16];	
		if (s[top].sex == 0)
		{
			strcpy(se, "female");	
		}
		else if(s[top].sex == 1)
		{
			strcpy(se, "male");		
		}
		else
		{
			strcpy(se, "Wrong data.");		
		}
		printf("delete {%s,%d,%s}, %d elements in stack\n", dname, dage, se, top + 1);
	}
	return ;
}

bool isEmpty(Stack *s)
{
	return (top == -1);	
}

bool isFull(Stack *s)
{
	return (top == cap - 1);		
}

