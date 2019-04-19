#include <stdio.h>
#include <stdlib.h>

#define Max 1024

struct node {
   int data;
   struct node *next;
};

struct node *head = NULL;
struct node *current = NULL;
struct node *prev = NULL;
struct node *preceding = NULL;

//insert link at the first location
void insert(int data) {
   // Allocate memory for new node;
   struct node *link = (struct node*) malloc(sizeof(struct node));

   link->data = data;
   link->next = NULL;

   // If head is empty, create new list
   if(head == NULL) {
      head = link;
      head->next = link;
      return;
   }

   current = head;
   
   // move to the end of the list
   while(current->next != head)
      current = current->next;
   
   // Insert link at the end of the list
   current->next = link;
   
   // Link the last node back to head
   link->next = head;
   
}
/*
void remove_data(int data) {
   
   if(head == NULL) {
      printf("Linked List not initialized");
      return;
   } 
 
   if(head->data == data) {
      if(head->next != head) {
         current = head;
         while(current->next!=head) {
            current = current->next;
         }
         current->next = head->next;
         head = head->next;
         return;
      }else {
         head = NULL;
         printf("List is empty\n");
         exit(0);
      }
   }else if(head->data != data && head->next == NULL) {
      printf("%d not found in the list\n", data);
      return;
   }
        

   current = head;
   
   while(current->next != head && current->data != data) {
      prev = current;
      current = current->next;
   }        

   if(current->data == data) {
      prev->next = prev->next->next;
      free(current);
   }else
      printf("%d not found in the list.", data);
}
*/
//display the list
void printList() {
	struct node *ptr = head;
 //  printf("\n[head] =>");
   
   //start from the beginning
	while(ptr->next != head) 
	{        
	printf("%d ", ptr->data);
	ptr = ptr->next;
	}
   
	printf("%d ", ptr->data);
   printf("\n");
}
void invert()
{
	if(head == NULL)
	{
         printf("List is empty\n");
		return;
	}
	prev = NULL;
	current = head;
	preceding = head->next;
    	while (preceding != 0) 
	{
        current->next = prev;      // 把current->next轉向
        prev = current;            // prev往後挪
        current = preceding;           // current往後挪
        preceding = preceding->next;   // preceding往後挪
    	}                                  // preceding更新成NULL即跳出while loop

    	current->next = prev;          // 此時current位於最後一個node, 將current->next轉向
    	head = current; 			// 更新head為current

//	printList();	
}

int remove_pos(int len, int data)
{
	int pos;
   if(head == NULL) {
      printf("Linked List not initialized");
      return 0;
   }
   current = head;
   while(len != 1)
   {
	for(pos = 1; pos < data - 1; pos++)
	{
		current = current->next;
	}
//	printf("%d\n", current->data);
	prev = current;
	current = current->next;

	prev->next = prev->next->next;
	current = prev->next;
	len = len - 1;
//	printList();
   }	
//	printf("%d\n", current->data);
	return current->data;
}

int main(void) 
{
	int flag = 1;
	int len = 0;

	FILE *fw;
	fw = fopen("result.txt", "a");

	while(flag)
	{
	printf("=======================================\n");
	printf("=                                     =\n");
	printf("= Which items do you want to choose ? =\n");
	printf("= (1) Read numbers from a file.       =\n");
	printf("= (2) Input new numbers               =\n");
	printf("= (0) Quit                            =\n");
	printf("=                                     =\n");
	printf("=======================================\n");
   
	int c1;
	scanf("%d", &c1);

	FILE *fp;

	switch(c1)
	{
		case 1 :
		{
		printf("Please input the file name : \n");
		char filename[Max];
		scanf("%s", filename);
		fp = fopen(filename ,"r");
			if( fp != NULL)
			{
				printf("%s open successful.\n", filename);
				int ch;
				while(fscanf(fp, "%d,", &ch) != EOF)
				{
			//		printf("%d ", ch);
					fprintf(fw, "%d ", ch);
					insert(ch);
					len++;			
				}
  //  printList();
			}
			else printf("File doesn't exist !\n");
		flag = 0;
		fclose(fp);
		break;
		}
		case 2 :
		{
			printf("How many numbers do you want to add ?\n");
			int num;
			int ch2;
			int i;
			scanf("%d", &num);

			for(i = 1; i <= num; i++)
			{
				printf("No.%d : ", i);
				scanf("%d", &ch2);
				fprintf(fw, "%d ", ch2);
				insert(ch2);
				len++;			 
			}
		flag = 0;
		break;
		}
		case 0 :
		{
			return 0;
			flag = 0;
			break;
		}
	}
	}
//	printf("len : %d\n", len);
	int skip;
	printf("\n");
	printf("The persons in circular list are : \n");
	   printList();
	printf("Enter the number of persons to be skipped : ");
	scanf("%d", &skip);

	int c2;
	int suv;
	flag = 1;

	while(flag)
	{
	printf("Which direction do you want to choose ? (1)Left (2)Right\n");
	scanf("%d", &c2);
		switch(c2)
		{
			case 1 :
			{
				invert();
   				suv = remove_pos(len, skip);
			flag = 0;
			break;
			}
			case 2 :
			{
   				suv = remove_pos(len, skip);
			flag = 0;
			break;
			}
		}
	}
	printf("The person to survive is : %d\n", suv);
					fprintf(fw, "\n%d\n\n\n", suv);
		
//	printf("Original List -\n"); 
//   printList();
//   remove_data(1);
   
//   printf("List after removal -\n");
//   printList();
    	
   return 0;
}
