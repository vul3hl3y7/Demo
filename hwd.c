#include <stdio.h>
#include <stdlib.h>

#define max 1024

typedef struct treeNode
{
	int data;
	struct treeNode *left;
	struct treeNode *right;
} treeNode;


treeNode  * insertNode(treeNode *node, int value, int level)
{

	if(node == NULL)
	{
		level = level + 1;	
		treeNode *temp;	
		temp = (treeNode *)malloc(sizeof(treeNode));
		temp->data = value;
		temp->left = temp->right = NULL;
		return temp;
	}
	else
	{	
			if(value > node->data) // bigger
			{
		level = level + 1;	
				node->right = insertNode(node->right ,value, level);
			}
			else if(value < node->data) // smaller
			{
		level = level + 1;	
				node->left = insertNode(node->left, value, level);
			}
			else
			{
				printf("Value is existed !\n");		
			}
			return node;
	}
}

int inOrder(treeNode *node, treeNode **nodelist, int i)
{
	if (node == NULL)
	{
		return i;		
	}

	i = inOrder(node->left, nodelist, i);

		nodelist[i] = node;
		i++;

	i = inOrder(node->right, nodelist, i);

	return i;
}

void searchNode(treeNode **nodelist, int index, int value)
{
	int f = 0; // not find
	int i = 0;

	for(i = 0; i < index; i++)
	{
		if(nodelist[i]->data != value)	
		{
			f = 0;		
		}
		else
		{
			printf("Find value %d. \n", nodelist[i]->data);	
			f = 1;
			return ;
		}
	}

	if (f == 0)
	{
		printf("Value doesn't exist !\n");		
	}
}

int delete(treeNode **nodelist, int index, int value)
{
	int i;
	int f = 0;

	for(i = 0; i <index; i++)
	{
		if(nodelist[i]->data != value)
		{
			f = 0;		
		}
		else
		{
			int j = i + 1;
			for(; i < index; i++)
			{
				nodelist[i] = nodelist[j];
				j++;
			}
			f = 1;
			index = index - 1;
			return index;
		}
	}
	if (f == 0)
	{
		printf("Value doesn't exist !\n");		
	}
			return index;
}

void print_infix(treeNode **nodelist, int index)
{
	int i;
	
	for (i = 0; i < index; i++)
	{
		printf("%d ", nodelist[i]->data);		
	}
}

int main()
{
	int c = 0;
	int level = 0;
		int value = 0;
		int i = 0;
		treeNode *root = NULL;
		treeNode **nodelist;
					nodelist = (treeNode **)malloc(max * sizeof(treeNode *));
					for(i = 0; i < max; i++)
					{
					nodelist[i] = (treeNode *)malloc(sizeof(treeNode));
					}
		int index = 0;
		i = 0;
	while(c != 6)
	{
		printf("\n---------------\n");
		printf("(1)Insert\n");
		printf("(2)Delete\n");
		printf("(3)Search\n");
		printf("(4)Print infix order\n");
		printf("(5)Level\n");
		printf("(6)Exit\n");
		printf("---------------\n");

		scanf("%d", &c);
		switch(c)
		{
			case 1:
				{
	//				int con = 1;
	//				while(con == 1)
	//				{
						printf("Input value : "); scanf("%d", &value);
	//					printf("More ? (1)Y/(2)N \n"); scanf("%d", &con);
					root = insertNode(root, value, level);
					index = inOrder(root, nodelist, i);
	//				printf("index : %d, i = %d\n", index, i);
	//				print_infix(root);	
	//				print_infix(nodelist, index);	
	//				}
					break;		
				}
			case 2:
				{
						printf("Input value : "); scanf("%d", &value);
						index = delete(nodelist, index, value);
					break;		
				}
			case 3:
				{		
						printf("Input search value : "); scanf("%d", &value);
						searchNode(nodelist, index, value);
					break;		
				}
			case 4:
				{
					print_infix(nodelist, index);	
					break;		
				}
			case 5:
				{
					printf("%d\n", level);
					break;
				}
			case 6:
				{
					return 0;		
				}
		}

	}
	return 0;		
}
