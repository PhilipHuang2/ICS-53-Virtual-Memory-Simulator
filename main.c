#include<stdio.h>
#include<string.h>

struct address
{
	int address;
	int data;
};

struct pageEntry
{
	int valid;
	int dirty;
	int pageNum;
};

int main()
{
	struct pageEntry pageTable[8];
	struct address mainMemory[16];
	struct address disk[32];	
	char input[90];
	printf("Hello World\n");
	do
{
	fgets(input, 90, stdin);
	printf("%s", input);
	
	
}while(strcmp(input,"quit\n") != 0);


	return 0;

}
