#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define max 1000000

typedef struct treeNode
{
	int num;
	int count;
	struct treeNode *left;
	struct treeNode *right;
} treeNode;

    treeNode *root = NULL;
	treeNode *nodelist;
    treeNode *pre = NULL;

treeNode * insert(treeNode *node, int new)
{

	if(node == NULL)
	{
		treeNode *temp;
		temp = (treeNode *)malloc(sizeof(treeNode));
		temp->num = new;
		temp->left = temp->right = NULL;
		return temp;
	}

	if(new < (node->num))
	{
		node->left = insert(node->left, new);
	}
	else if(new > (node->num))
	{
		node->right = insert(node->right, new);
	}
	return node;
}

void inOrder(treeNode *node)
{
	if (node == NULL)
	{
		return;
	}
		inOrder(node->left);
			printf(" %d ", node->num);
		inOrder(node->right);

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

treeNode * search(treeNode *node, int key,int count)
{
    treeNode *q = node;
	while(q != NULL)
	{
        if(q->num == key)
        {
            count++;
            return q; // find
        }
        else
        {
            pre = q;
            if(q->num > key)
                q = q->left;
            else
                q = q->right;
        }
	}
    return NULL;
}
treeNode * delete(treeNode *node, int del)
{
    treeNode *cur, *next, *son;
    int c = 0;
    cur = search(root, del, c);
    if(cur == NULL)
    {
	    printf("delete %d : Not-found\n", del);
	    return root;
    }
    else
    {
        if(cur->right == NULL)
            next = cur->left;
        else if(cur->left == NULL)
            next = cur->right;
        else
        {
            pre = cur;
            son = cur->left;
            while(son->right != NULL)
            {
                pre = son;
                son = son->right;
            }
            cur->num = son->num;
            cur = son;
            next = son->left;
        }

        if(pre == NULL)
            root = NULL;
        else if(cur == pre->right)
            pre->right = next;
        else pre->left = next;

        printf("delete %d\n", del);
        return root;
    }

}

int main()
{
	char ch;
	int i;
	int count;

	while(1)
	{
		ch = getchar();

		switch(ch)
		{
			case 'I': // insert
			{
				int new = 0;
				scanf("%d", &new);
				root = insert(root, new);
				break;
			}

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
				count = 1;
				root = search(root, key, count);
				if(root != NULL)
				{
                    printf("search %d : found,search times: %d\n", key, count);
				}
				else
				{
				    printf("search %d : Not-found\n", key);
				}
				break;
			}

			case 'P': // print pre-order & in-order
			{	
			    printf("P-order : ");
			    		inOrder(root);
					printf("\n");

                printf("I-order : ");
			    		preOrder(root);
					printf("\n");
				break;
			}

			case 'E': // quit
			{
				printf("End\n");
				return 0;
			}
			default : break;
		}
	}
	return 0;
}
