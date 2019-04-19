#include <stdio.h>
#include <stdlib.h>

typedef struct Link
{
	float coef;
	int exp;
	struct Link *pNext;
};

typedef struct Link *Poly;
typedef struct Link *pLink;

void PrintPoly(Poly p)
{
	Poly tmp = p;

	while(tmp->exp > 0)
	{
		printf("%0.2fx^%d", tmp->coef, tmp->exp);
		tmp = tmp->pNext;
		if(tmp->coef > 0) // if coefficient is postive
		printf("+");
	}
	if(tmp->coef != 0) //constant
		printf("%0.2f", tmp->coef);

	printf("\n");
}

void Attach(FILE *fp, Poly p)
{
	// p => first, tmp => current	
	Poly tmp = p;
	Poly new = NULL;
	tmp->pNext = NULL;
	fscanf(fp, "%f %d", &p->coef, &p->exp);

	while(tmp->exp > 0)
	{
		new = (pLink)malloc(sizeof(struct Link));
		new->pNext = NULL;
		tmp->pNext = new;
		tmp = tmp->pNext;
		fscanf(fp, "%f %d", &tmp->coef, &tmp->exp);
	}
	PrintPoly(p);	
}

void PolyAdd(Poly a, Poly b, Poly c) // a + b = c
{
	Poly tmp = c;
	Poly new = NULL;
	tmp->pNext = NULL;

	while(a->exp > 0 || b->exp > 0)
	{
		if(a->exp == b->exp) // compare	power equal
		{
			tmp->coef = a->coef + b->coef;
			tmp->exp = a->exp;
			a = a->pNext;
			b = b->pNext;
		}
		else if(a->exp > b->exp)	// c equal a
		{
			tmp->coef = a->coef;
			tmp->exp = a->exp;
			a = a->pNext;
		}
		else if(a->exp < b->exp)	// c equal b
		{
			tmp->coef = b->coef;
			tmp->exp = b->exp;
			b = b->pNext;
		}

		new = (pLink)malloc(sizeof(struct Link));
		new->pNext = NULL;
		tmp->pNext = new;
		tmp = tmp->pNext;
	}
		if (a->coef != 0 || b->coef != 0)	// constant
		tmp->coef = a->coef + b->coef;

//	PrintPoly(c);
}

void PolySub(Poly a, Poly b, Poly c) // a - b = c
{
	Poly tmp = c;
	Poly new = NULL;
	tmp->pNext = NULL;

	while(a->exp > 0 || b->exp > 0)
	{
		if(a->exp == b->exp) // compare	power equal
		{
			tmp->coef = a->coef - b->coef;
			tmp->exp = a->exp;
			a = a->pNext;
			b = b->pNext;
		}
		else if(a->exp > b->exp)	// c equal a
		{
			tmp->coef = a->coef;
			tmp->exp = a->exp;
			a = a->pNext;
		}
		else if(a->exp < b->exp)	// c equal b
		{
			tmp->coef = - (b->coef);
			tmp->exp = b->exp;
			b = b->pNext;
		}

		new = (pLink)malloc(sizeof(struct Link));
		new->pNext = NULL;
		tmp->pNext = new;
		tmp = tmp->pNext;
	}
		if (a->coef != 0 || b->coef != 0)	// constant
		tmp->coef = a->coef - b->coef;

	PrintPoly(c);
}

void PolyMul(Poly a, Poly b, Poly c) // a * b = c
{
	Poly T;
	T = (pLink)malloc(sizeof(struct Link));
	Poly tmp = T;
	Poly tmpA = a;
	Poly tmpB = b;
	Poly tmpC = c;

	Poly m1; // a x b line
	m1 = (pLink)malloc(sizeof(struct Link));
	Poly temp1 = m1;
	Poly new = NULL;
	Poly new1 = NULL;
	tmp->pNext = NULL;

	while(tmpA != NULL)	// first line
	{
		while(tmpB != NULL)	// second line
		{
			temp1->coef = tmpA->coef * tmpB->coef;
			temp1->exp = tmpA->exp * tmpB->exp;

			new1 = (pLink)malloc(sizeof(struct Link));
			new1->pNext = NULL;
			temp1->pNext = new1;
			temp1 = temp1->pNext;
			tmpB = tmpB->pNext;
		}
		tmpB = b; // tmpB return to first node
		temp1 = m1; // temp1 return to first node
		
		if(tmpA == a)	// first mul take max exp
		{
			while(temp1 != NULL)
			{
				tmp->coef = temp1->coef;
				tmp->exp = temp1->exp;
				new = (pLink)malloc(sizeof(struct Link));
				new->pNext = NULL;
				tmp->pNext = new;
				tmp = tmp->pNext;
				temp1 = temp1->pNext;
			}
			tmp = T; //return to the first node
			temp1 = m1; // temp1 return to first node
		}
		else // cumulative
		{
			PolyAdd(T, m1, c);	// c will be the final answer be thr sum of the cumulative answer(T) and the temp answer(m1) 
			while(tmpC != NULL)	// T should be the cumulative answer for the next time
			{
				tmp->coef = tmpC->coef;
				tmp->exp = tmpC->exp;
				new = (pLink)malloc(sizeof(struct Link));
				new->pNext = NULL;
				tmp->pNext = new;
				tmp = tmp->pNext;
				tmpC = tmpC->pNext;
			}
			tmp = T; //return to the first node
			tmpC = c; // tmpC return to first node
		}
		tmpA = tmpA->pNext;
	}
	PrintPoly(c);
}

int main(void)
{
	FILE *f1;	
	FILE *f2;
	char file1[64];
	char file2[64];

	printf("Please enter the file of polynomial data.\n");
	printf("Polynomial 1 : "); scanf("%s", file1);
	printf("Polynomial 2 : "); scanf("%s", file2);

	f1 = fopen(file1, "r");
	f2 = fopen(file2, "r");

	while(f1 == NULL || f2 == NULL)
	{
		printf("No file error, please enter again.");	
		printf("Polynomial 1 : "); scanf("%s", file1);
		printf("Polynomial 2 : "); scanf("%s", file2);
	}
	printf("\n");	
	Poly A, B, ADD_C, SUB_D, MUL_E;
	A = (pLink)malloc(sizeof(struct Link));
	B = (pLink)malloc(sizeof(struct Link));
	ADD_C = (pLink)malloc(sizeof(struct Link));
	SUB_D = (pLink)malloc(sizeof(struct Link));
	MUL_E = (pLink)malloc(sizeof(struct Link));

	printf("A(x) = "); Attach(f1, A);	// p1
	printf("B(x) = "); Attach(f2, B);	// p2
	printf("C(x) = "); PolyAdd(A, B, ADD_C);	PrintPoly(ADD_C);	// p1 + p2
	printf("D(x) = "); PolySub(A, B, SUB_D);	// p1 - p2
	printf("E(x) = "); PolyMul(A, B, MUL_E);	// p1 * p2
	printf("\n");	

	return 0;		
}
