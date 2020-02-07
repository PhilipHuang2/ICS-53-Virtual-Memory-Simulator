#include<stdio.h>
#include<string.h>

struct pageEntry
{
	int valid;
	int dirty;
	int pageNum;
};


void showPageTable(struct pageEntry pageTable[]);
void showMem(int array[], int length);
void showMainMemory(int array[]);
void showDisk(int array[]);

int main()
{
	struct pageEntry pageTable[8];
	int count = 0;
	while(count < 8)
	{
		pageTable[count].valid = 0;
		pageTable[count].dirty = 0;
		pageTable[count].pageNum = 0;
		count++;
	}
	showPageTable(pageTable);
	int mainMemory[16]= {0};
	int disk[32] = {0};	
	showMainMemory(mainMemory);
	char input[90];
	printf("Hello World\n");
	do
	{
		fgets(input, 90, stdin);
		printf("%s", input);
	}while(strcmp(input,"quit\n") != 0);
	return 0;
}

void showPageTable(struct pageEntry pageTable[]){
	int count = 0;
	while(count < 8)
	{
		printf("%d:%d:%d:%d\n",count,pageTable[count].valid,pageTable[count].dirty,pageTable[count].pageNum);
		count++;
	}
}

void showMem(int array[], int length){
	int count = 0;
	while(count < length)
	{
		printf("%d:%d\n",count,array[count]);
		count++;
	}
}

void showMainMemory(int array[]){
	showMem(array, 16);
}
void showDisk(int array[])
{
	showMem(array,32);
}
