#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define max 1000000

typedef struct treeNode
{
	int num;
	int coin;
	struct treeNode *left;
	struct treeNode *right;
} treeNode;

    treeNode *root = NULL;
	treeNode *nodelist;
    treeNode *pre = NULL;

int score(treeNode *node, int hunter, int sum)
{
	FILE *fw;
	if(node == NULL) return sum;
	else if (hunter > (node->num))
	{
	fw = fopen("result.txt", "a");
		fprintf(fw, "node:%d collect %d coins\n", node->num, node->coin); 
		printf("node:%d collect %d coins\n", node->num, node->coin); 
	fclose(fw);
		sum +=  node->coin;
		sum = score(node->right, hunter, sum);
	}
	else if (hunter < (node->num))
	{ 
	fw = fopen("result.txt", "a");
		fprintf(fw, "node:%d collect %d coins\n", node->num, node->coin); 
		printf("node:%d collect %d coins\n", node->num, node->coin); 
	fclose(fw);
		sum +=  node->coin;
		sum = score(node->left, hunter, sum);
	}
	return sum;
}

treeNode * insert(treeNode *node, int num, int coin)
{

	if(node == NULL)
	{
		treeNode *temp;
		temp = (treeNode *)malloc(sizeof(treeNode));
		temp->num = num;
		temp->coin = coin;
		temp->left = temp->right = NULL;
		return temp;
	}

	if(num < (node->num))
	{
		node->left = insert(node->left, num, coin);
	}
	else if(num > (node->num))
	{
		node->right = insert(node->right, num, coin);
	}
	return node;
}
/*
treeNode * min_vnode(treeNode *node)
{
	treeNode *cur = node;

	while(cur->left != NULL)
		cur = cur->left;

	return cur;
}
*/
void printInfixOrder(treeNode *node)
{
	if (node == NULL)
	{
		return;
	}
		printInfixOrder(node->left);
			printf(" %d-%d ", node->num, node->coin);
		printInfixOrder(node->right);

	return;
}

void preOrder(treeNode *node)
{
	if (node == NULL)
	{
		return;
	}
			printf(" %d ", node->num);
		preOrder(node->left);
		preOrder(node->right);

	return;
}

int height(treeNode *node)
{
	if(node == NULL) return 0;
	else
	{
		int h_left = height(node->left);
		int h_right = height(node->right);

		if(h_left > h_right) return(h_left + 1);
		else return(h_right + 1);
	}
}

void print_glevel(treeNode *node, int level)
{
	if(node == NULL) return;
	if(level == 1) printf("%d-%d ", node->num, node->coin);
	else if(level > 1)
	{
		print_glevel(node->left, level - 1);
		print_glevel(node->right, level - 1);
	}
}

void printLevelOrder(treeNode *node)
{
	int h = height(node);
//	printf("Hight: %d\n", h);
	int i;
	for(i = 1; i <= h; i++) print_glevel(node, i);
}
/*
treeNode * search(treeNode *node, int key)
{
    if(node == NULL)
    {
	    printf("Search %d Not-found\n", key);
	    return node;
    }
    if(key < node->num) node->left = search(node->left, key);
    else if(key > node->num) node->right = search(node->right, key);
    else if(key == node->num) 
    {
	printf("Search %d Found\n", key);
	return node;
    }
}
treeNode * delete(treeNode *node, int del)
{
   //  int c = 0;
   // cur = search(root, del, c);
    if(node == NULL)
    {
	    printf("delete %d : Not-found\n", del);
	    return node;
    }
    if(del < node->num) node->left = delete(node->left, del);
    else if(del > node->num) node->right = delete(node->right, del);
    else if(del == node->num)
    {
	    printf("delete %d\n", node->num);
       // delete node with only one child or no child
	if(node->left == NULL)
	{
		treeNode *temp = node->right;
		free(node);
		return temp;
	}
	else if(node->right == NULL)
	{
		treeNode *temp = node->left;
		free(node);
		return temp;
	}

       // delete node with two children, inorder succressor
	treeNode *temp = min_vnode(node->right);
	node->num = temp->num;

	node->right = delete(node->right, temp->num);
    }
//	printInfixOrder(root);
        return node;
}
*/
int main()
{
	char ch;
	int i = 1;

		printf("2.Treasure Hunter\n");
		printf("==================================\n");
		printf("=                                =\n");
		printf("= Please choose the instruction. =\n");
		printf("= (I)Import file                 =\n");
		printf("= (C)Input hunter numbering      =\n");
		printf("= (E)end                         =\n");
		printf("=                                =\n");
		printf("==================================\n");
	while(i)
	{
		scanf("%c", &ch);

		FILE *fp;
			FILE *fw;

		switch(ch)
		{
			case 'I': // import
			{
				printf("Please input the filename : ");
				char filename[48];
				scanf("%s", filename);
				fp = fopen(filename, "r");
					if(fp != NULL)
					{
						printf("%s open successful.\n", filename);
						int n, c;
						while(fscanf(fp, "%d,%d\n", &n, &c) != EOF)
						{
							printf("%d,%d\n", n, c);
							root = insert(root, n, c);
						}
			    //		printLevelOrder(root);
					printf("\n");
					}
					else printf("File doesn't exist !\n");
				fclose(fp);
		/*		int new = 0;
				scanf("%d", &new);
				root = insert(root, new);*/
				break;
			}
/*
			case 'D': //delete
			{
				int del = 0;
				scanf("%d", &del);
				root = delete(root, del);
				break;
			}

			case 'S': // search
			{
				int key = 0;
				scanf("%d", &key);

				root = search(root, key);
				break;
			}
*/
			case 'C': // hunter
			{
				int hunter1, hunter2;
			    	printf("Hunter 1 : #");
				scanf("%d", &hunter1);
			    	printf("Hunter 2 : #");
				scanf("%d", &hunter2);
				printf("\n");	
			
				int s1 = 0;
				int s2 = 0;
				fw = fopen("result.txt", "a");
				fprintf(fw, "\n#%d hunter's walking trajectory\n", hunter1);
				printf("#%d hunter's walking trajectory\n", hunter1);
				fclose(fw);
				s1 = score(root, hunter1, s1);
				fw = fopen("result.txt", "a");
				fprintf(fw, "Totally collected %d coins\n", s1);
				printf("Totally collected %d coins\n", s1);
				fclose(fw);
				printf("\n");	
				fw = fopen("result.txt", "a");
				fprintf(fw, "\n#%d hunter's walking trajectory\n", hunter2);
				printf("#%d hunter's walking trajectory\n", hunter2);
				fclose(fw);
				s2 = score(root, hunter2, s2);
				fw = fopen("result.txt", "a");
				fprintf(fw, "Totally collected %d coins\n\n", s2);
				printf("Totally collected %d coins\n", s2);
			//	printf("s1 :%d, s2 : %d\n", s1, s2);
			//	root = search(root, key);
				printf("\n");	
				if(s1 > s2)
				{
					fprintf(fw, "#%d hunter win the game !\n", hunter1);
					printf("#%d hunter win the game !\n", hunter1);
				}
				else if(s1 < s2)
				{
					fprintf(fw, "#%d hunter win the game !\n", hunter2);
					printf("#%d hunter win the game !\n", hunter2);
				}
				else
				{
					fprintf(fw, "#d hunter and %d hunter tie !\n", hunter1, hunter2);
					printf("#d hunter and %d hunter tie !\n", hunter1, hunter2);
				}
				fclose(fw);
				break;
			}
/*			case 'P': // print pre-order & in-order & level-order
			{	
			    	printf("P-order : ");
			    	preOrder(root);
				printf("\n");

                		printf("I-order : ");
			    		printInfixOrder(root);
					printf("\n");
                		printf("L-order : ");
			    		printLevelOrder(root);
					printf("\n");
				break;
			}
*/
			case 'E': // quit
			{
				printf("End\n");
				return 0;
			}
			default :
			{
		printf("==================================\n");
		printf("=                                =\n");
		printf("= Please choose the instruction. =\n");
		printf("= (I)Import file                 =\n");
		printf("= (C)Input hunter numbering      =\n");
		printf("= (E)end                         =\n");
		printf("=                                =\n");
		printf("==================================\n");
			
			}
		}
	}
	return 0;
}
