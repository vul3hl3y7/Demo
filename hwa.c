#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(void)
{
	int flag = -1;
	int i = -1;
	FILE *fp;

	int max = 0;	// data's number
	char filename[64];
	struct data{
		int id;
		char name[64];
		int score_Math;
		int score_English;
	} data[512];

	while(flag)
	{
		printf("\n\n=========================\n\nWhat do you want to do ?\n\n1)Read data from file.\n2)Show data.\n3)Write data to file.\n\n0)Exit the program.\n\n=========================\n\n");
		scanf("%d", &flag);
		printf("\n");
		switch(flag)
		{
			case 1: //read
			{	
				int n = 1;
				printf("Enter the file name.\n");
				scanf("%s", filename);
				fp = fopen(filename, "r");
				if(fp == NULL)
				{
					printf("\nNo file.\n");
				}
				else
				{
					printf("\nOpen the file : %s\n\n", filename);
					char buf[1024];	
					while(fgets(buf, 1024, fp) != NULL)
					{
						char *pch;
						pch = strtok(buf, ",");
						while(pch != NULL)
						{
							if (atoi(pch) == 0 && strcmp(pch, "0") != 0) // heading and Name
							{
								if(strcmp(pch, "ID") == 0 || strcmp(pch, "Name") == 0 || strcmp(pch, "Score_Math") == 0 || strcmp(pch, "Score_English") == 0) // heading	
								printf("%s\t", pch);		
								else	// Name
								{
									i++;
									max = i;
									strcpy(data[i].name, pch);
									printf("%s\t", data[i].name);
								}
							}
							else
							{
								switch(n)
								{
									case 1: // ID
									{
										data[i].id = atoi(pch);	
										printf("%d\t", data[i].id);
										n = 2;	
										break;		
									}
									case 2: // Math grade
									{
										data[i].score_Math = atoi(pch);	
										printf("%d\t", data[i].score_Math);
										n = 3;
										break;
									}
									case 3: // English grade
									{
										data[i].score_English = atoi(pch);	
										printf("\t%d", data[i].score_English);
										n = 1;
										break;
									}
								}
							}
							pch = strtok(NULL, ",");
						}
						printf("\n");
					}
				}
				break;
			}
			case 2: //show data
			{
				char showfile[64];
				printf("Enter the file name.\n");
				scanf("%s", showfile);
				fp = fopen(showfile, "r");
				if(fp == NULL)
				{
					printf("\nNo file, please creat first\n");
				}
				else if ((strcmp(showfile, filename) != 0))
				{
					printf("\nThis file doesn't read in the first step, please read it first.\n");		
				}
				else
				{
					printf("\nShow the file : %s\n\n", showfile);
					
					printf("ID\tName\tScore_Math\tScore_English\n\n");
					for(i = 1; i <= max; i++)
					{
						printf("%d\t%s\t%d\t\t%d\n", data[i].id, data[i].name, data[i].score_Math, data[i].score_English);		
					}
				}
				break;
			}
			case 3: // write data		
			{
				char writefile[64];
				FILE *fn;			
				printf("Enter the file name.\n");
				scanf("%s", writefile);
				fn = fopen(writefile, "a+");

				if(fp == NULL)
				{
					printf("\nNo file, it will be created a null one.\n");
				}
				else if ((strcmp(writefile, filename) != 0))
				{
					printf("\nThis file doesn't read in the first step, please read it first, or you just creat new file.\n");		
				}
				else
				{
					printf("\n\nEnter new data.\n\n");
					int c = 0;  // for continue
					char id[32];
					char name[64];
					char ms[32];
					char es[32];

				while (c == 0)
				{
						printf("ID = "); scanf("%s", id);
						while(atoi(id) == 0 && strcmp(id, "0") != 0) // avoid ID not number.
						{
							printf("ID should be number, please enter again !\n");		
							printf("ID = "); scanf("%s", id);
						}
						max = max + 1;
						data[max].id = atoi(id);	// into structure
						printf("Name = "); scanf("%s", name);
						strcpy(data[max].name, name);
						printf("Score_Math = "); scanf("%s", ms);
						while(atoi(ms) > 100 || atoi(ms) < 0 || (atoi(ms) == 0 && strcmp(ms, "0")!= 0)) // avoid grade out of 0-100 and not number.
						{
							printf("Grade should be under to 100 and up to 0, please enter again !\n");		
							printf("Score_Math = "); scanf("%s", ms);
						}
						data[max].score_Math = atoi(ms);
						printf("Score_English = "); scanf("%s", es);
						while(atoi(es) > 100 || atoi(es) < 0 || (atoi(ms) == 0 && strcmp(ms, "0")!= 0))
						{
							printf("Grade should be under to 100 and up to 0, please enter again !\n");		
							printf("Score_English = "); scanf("%s", es);
						}
						data[max].score_English = atoi(es);
						fprintf(fn, "%s,%s,%s,%s\n", id, name, ms, es);
						printf("Continue or not ? y->0/n->1\n");
						scanf("%d", &c);
						printf("\n");
				}
				}
				break;
			}
			case 0: //exit
			{
					return 0;
			}
			default: // wrong instruction
			{
					printf("Wrong instruction, please try again !\n\n");
			}
		}
	}
	return 0;		
}
