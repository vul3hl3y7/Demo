/*
*	Exercise C : expression
*/

#include <stdio.h>
#include <stdlib.h>

#define Max_stack_size 1024
#define Max_expr_size 1024

typedef enum {lparen, rparen, plus, minus, time, divide, mod, eos, operand} precedence;

int stack[Max_stack_size];
char expr[Max_expr_size];

int eval(void)
{
	precedence token;
	char symbol;
	int op1, op2;
	int n = 0;
	int top = -1;

	token = get_token(&symbol. &n);

	while(token != eos)
	{
		if(token == operand)
			add(&top, symbol-'0');
		else
		{
			op2 = delete(&top);
			op1 = delete(&top);

			switch(token)
			{
				case plus:add(&top, op1 + op2);break;	
				case minus:add(&top, op1 - op2);break;	
				case times:add(&top, op1 * op2);break;	
				case divide:add(&top, op1 / op2);break;	
				case mod:add(&top, op1 % op2);break;	
			}
		}
		token = get_token(&symbol, &n);
	}
	return delete(&top);
}

void get_token(char *symbol. int *n)
{
	*symbol = expr[(*n)++];

	switch(*symbol)
	{
		case '(': return lparen;		
		case ')': return rparen;		
		case '+': return plus;		
		case '-': return minus;		
		case '/': return divide;		
		case '*': return times;		
		case '%': return mod;		
		case '\0': return eos;		
		default: return operand;		
	}
}

void postfix()
{
	char symbol;
	precedence token;
	int n = 0;
	int top = 0;
	stack[0] = eos;
	
	for(token = get_token(&symbol. &n); token != eos; token = get_token(&symbol, &n))
	{
		if(token == operand)
		{
			printf("%c", symbol);		
		}
		else if(token == rparen)
		{
			while(stack[top] != lparen)
				print_token(delete(&top));
			delete(&top);
		}
		else
		{
				
		}
	}
}

int main()
{
	int line[1024];
	int n = 0;
	char c;

	while(1)
	{
		c = getchar();
		get_token(c, 0)
	}



	return 0;		
}
