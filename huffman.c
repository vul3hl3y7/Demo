#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define Max 128

int total = 0;
int calculate[Max];
int l = -1;

struct Min_heap_node {

	char character;
	int arr[Max];
	int frequency;

	struct Min_heap_node *left;
	struct Min_heap_node *right;
};

struct tree_list {

	char character;
	int size;
	int code[Max];

	struct tree_list *next;
};

struct tree_list *head = NULL;
struct tree_list *current = NULL;

struct Min_heap {

	int size;
	unsigned capacity;

	struct Min_heap_node** array;
};

struct Min_heap_node* newNode(char character, unsigned frequency)
{
	struct Min_heap_node* temp = (struct Min_heap_node*)malloc(sizeof(struct Min_heap_node));

	temp->left = temp->right = NULL;
	temp->character = character;
	temp->frequency = frequency;

	return temp;
}

void nextNode(char character, int size, int arr[])
{
    int i;
        struct tree_list* temp = (struct tree_list*)malloc(sizeof(struct tree_list));
        temp->next = NULL;
        temp->character = character;
  //      printf("%c", current->character);
        temp->size = size;
        for(i = 0; i < size; i++)
        {
            temp->code[i] = arr[i];
        }
        if(head == NULL)
        {
        head = temp;
        head->next = temp;
        return;
        }

        current = head;

        while(current->next != head) current = current->next;

        current->next = temp;

        temp->next = head;
}
void printlist(struct tree_list *head)
{
    printf("in\n");
    int i;
    struct tree_list *node = head;
    while(node->next != head)
    {
        printf("symbol %c ", node->character);
        for(i = 0; i < node->size; i++)
        printf("%d", node->code[i]);

        node = node->next;
    }

}

struct Min_heap* createMin_heap(unsigned capacity)
{
	struct Min_heap* Min_heap = (struct Min_heap*)malloc(sizeof(struct Min_heap));

	Min_heap->size = 0;
	Min_heap->capacity = capacity;

	Min_heap->array = (struct Min_heap_node**)malloc(Min_heap->capacity * sizeof(struct Min_heap_node*));
	return Min_heap;
}

void swapMin_heap_node(struct Min_heap_node** a, struct Min_heap_node** b)
{
	struct Min_heap_node* t = *a;
	*a = *b;
	*b = t;
}

void Min_heapify(struct Min_heap* Min_heap, int idx)
{
	int smallest = idx;
	int left = 2 * idx + 1;
	int right = 2 * idx + 2;

	if (left < Min_heap->size && Min_heap->array[left]->frequency < Min_heap->array[smallest]->frequency)
		smallest = left;

	if (right < Min_heap->size && Min_heap->array[right]->frequency < Min_heap->array[smallest]->frequency)
		smallest = right;

	if (smallest != idx) {
		swapMin_heap_node(&Min_heap->array[smallest], &Min_heap->array[idx]);
		Min_heapify(Min_heap, smallest);
	}
}

int isSizeOne(struct Min_heap* Min_heap)
{
	return (Min_heap->size == 1);
}

//  extract minimum value node from heap
struct Min_heap_node* extractMin(struct Min_heap* Min_heap)
{
	struct Min_heap_node* temp = Min_heap->array[0];
	Min_heap->array[0] = Min_heap->array[Min_heap->size - 1];

	--Min_heap->size;
	Min_heapify(Min_heap, 0);

	return temp;
}

void insertMin_heap(struct Min_heap* Min_heap,	struct Min_heap_node* Min_heap_node)
{
	++Min_heap->size;
	int i = Min_heap->size - 1;

	while (i && Min_heap_node->frequency < Min_heap->array[(i - 1) / 2]->frequency)
	{
		Min_heap->array[i] = Min_heap->array[(i - 1) / 2];
		i = (i - 1) / 2;
	}

	Min_heap->array[i] = Min_heap_node;
}

void buildMin_heap(struct Min_heap* Min_heap)
{
	int n = Min_heap->size - 1;
	int i;

	for (i = (n - 1) / 2; i >= 0; --i)
		Min_heapify(Min_heap, i);
}

int isLeaf(struct Min_heap_node* root)
{

	return !(root->left) && !(root->right);
}

struct Min_heap* createAndBuildMin_heap(char character[], int frequency[], int size)
{
	struct Min_heap* Min_heap = createMin_heap(size);

    int i;
	for (i = 0; i < size; ++i) Min_heap->array[i] = newNode(character[i], frequency[i]);

	Min_heap->size = size;
	buildMin_heap(Min_heap);

	return Min_heap;
}

// The main function that builds Huffman tree
struct Min_heap_node* buildHuffmanTree(char character[], int frequency[], int size)
{
	struct Min_heap_node *left, *right, *top;

	struct Min_heap* Min_heap = createAndBuildMin_heap(character, frequency, size);

	while (!isSizeOne(Min_heap))
	{
		left = extractMin(Min_heap);
		right = extractMin(Min_heap);

		top = newNode('$', left->frequency + right->frequency);

		top->left = left;
		top->right = right;

		insertMin_heap(Min_heap, top);
	}

	return extractMin(Min_heap);
}

// build huffman code
void printCodes(struct Min_heap_node* root, int arr[], int top, FILE *fw)
{
    int i;
	//  left = 0;
	if (root->left)
	{
		arr[top] = 0;
		printCodes(root->left, arr, top + 1, fw);
	}

	// right = 1;
	if (root->right)
	{
		arr[top] = 1;
		printCodes(root->right, arr, top + 1, fw);
	}

	if (isLeaf(root)) {

        if(root->character == ' ')  // ' ' = space
        {
        printf("space: %d ", root->frequency);
        fprintf(fw,"space: %d ", root->frequency);
        total += top * root->frequency;
        if (top != 0)
        {
            calculate[++l] = root->frequency;
            calculate[++l] = top;
            for(i = 0; i < top; i++)
            {
                root->arr[i] = arr[i];
            }
            for(i = 0; i < top; i++)
            {
                printf("%d", root->arr[i]);
                fprintf(fw,"%d", root->arr[i]);
            }
            nextNode( root->character,top, arr);
   //         printlist(head);
            printf("\n");
            fprintf(fw,"\n");
        }
//		printArr(arr, top);
        }
        else
        {
		printf("%c: %d ", root->character, root->frequency);
		fprintf(fw,"%c: %d ", root->character, root->frequency);
		total += top * root->frequency;
        if (top != 0)
        {
            calculate[++l] = root->frequency;
            calculate[++l] = top;
            for(i = 0; i < top; i++)
            {
                root->arr[i] = arr[i];
            }
            for(i = 0; i < top; i++)
            {
                printf("%d", root->arr[i]);
                fprintf(fw,"%d", root->arr[i]);
            }
            nextNode( root->character,top, arr);
      //      printlist(head);
            printf("\n");
            fprintf(fw,"\n");
        }
//		printArr(arr, top);
		}
	}
}

void HuffmanCodes(char character[], int frequency[], int size, FILE *fw)
{
	struct Min_heap_node* root = buildHuffmanTree(character, frequency, size);
	int arr[Max], top = 0;

	printCodes(root, arr, top, fw);
}

void encode(char s[], FILE *fw)
{
    int i;
    int j;
    int len = strlen(s);
    struct tree_list *node;

    for(i = 0; i < len; i++)
    {
        node = head;
        while(node->next != head)
        {
            if(s[i] == node->character)
            {
                for(j = 0; j < node->size; j++)
                {
                printf("%d", node->code[j]);
                fprintf(fw,"%d", node->code[j]);
                }
            }
            node = node->next;
        }
    }

}

int countStrfrequency(const char *s, char character[], int frequencyuency[])
{
    int frequency[128] = {0};
    while (*s)
    {
        frequency[(int)*s++]++;
 //       printf("%c",*s);
    }

    int c = 0;
    int i;
    for (i = 0; i < 128; i++)
    {
        if (frequency[i] != 0)
        {
            character[c] = (char)i;
            frequencyuency[c] = frequency[i];
            c++;
        }
    }
    return c;
}

// Driver program to test above functions
int main()
{
    FILE *fp;
    FILE *fw;
    char filename[Max];

    printf("Please input the filename : \n");

    scanf("%s", filename);
    fp = fopen(filename, "r");
    fw = fopen("code.txt", "w");
 //   char *str = "Eerie eyes seen near lake.";
 //    printf("Test sentence : %s\n\n", str);

    char sentence[Max];

    if(fp == NULL) printf("Error opening file.\n");

    while(fgets(sentence, Max, fp) != NULL)
    {
    printf("\nTest sentence : %s\n\n", sentence);
    fprintf(fw,"\nTest sentence : %s\n\n", sentence);
    char cha[128];
    int frequency[128]={0};

    int val;
    val = countStrfrequency(sentence,cha,frequency);

    printf("%d\n", val);
    fprintf(fw,"%d\n", val);

    int i;
/*    for(i = 0; i < val; i++)
    {
    printf("%c %d\n", cha[i], frequency[i]);
    }
*/
	HuffmanCodes(cha, frequency, val, fw);
	printf("\nTotal bits : ");
	fprintf(fw,"\nTotal bits : ");

	for(i = 0 ; i < sizeof(calculate); i = i+2)
	{

        if(calculate[i] != 0)
        {
        if(i == 0)
        {
        printf("%d *" , calculate[i]);
        fprintf(fw,"%d *" , calculate[i]);
        printf(" %d " , calculate[++i]);
        fprintf(fw," %d " , calculate[++i]);
        }
        else
        {
        printf("+ %d *" , calculate[i]);
        fprintf(fw,"+ %d *" , calculate[i]);
        printf(" %d " , calculate[++i]);
        fprintf(fw," %d " , calculate[++i]);
        }
        }

	}

    printf("= %d bits\n\n", total);
    fprintf(fw,"= %d bits\n\n", total);
    printf("Encrypted code : ");
    fprintf(fw,"Encrypted code : ");
        encode(sentence,fw);

    }


	return 0;
}
