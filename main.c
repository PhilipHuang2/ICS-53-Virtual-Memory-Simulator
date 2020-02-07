#include<stdio.h>
#include<string.h>

struct pageEntry
{
	int valid;
	int dirty;
	int pageNum;
};


void showMem(int array[], int length);
void showMainMemory(int array[]);
void showDisk(int array[]);
void read(int virtualAddress);
void write (int virtualAddress, int num);
void showMain (int physicalPageNumber);
void showDisk(int diskPageNumber);
void showPageTable(struct pageEntry pageTable[]);

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

	printf("> ");
	fgets(input, 90, stdin);
	printf("%s", input);
	
	
	}while(strcmp(input,"quit\n") != 0);
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


void read(int virtualAddress){

	//prints contente of the Memory address

	// if (){ //if page fault occurss print
	// 	printf("An Page Fault Has Ocurred\n");
	// }

}

void write (int virtualAddress, int num){

	//writes data to a memory location

	// if (){ //if page fault occurss print
	// 	printf("An Page Fault Has Ocurred\n");
	// }
}

void showMain (int physicalPageNumber){

	//prints out the 4 address and data associated with the main memory page

}

void showDisk(int diskPageNumber){

	//prints out the 4 addresses and data associated with the disk page

}

void showPageTable(struct pageEntry pageTable[]){
	//print out the 8 pageEntry Objects
	int count = 0;
	while(count < 8)
	{
		printf("%d:%d:%d:%d\n",count,pageTable[count].valid,pageTable[count].dirty,pageTable[count].pageNum);
		count++;
	}
}
