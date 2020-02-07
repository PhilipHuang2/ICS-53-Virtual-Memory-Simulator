#include<stdio.h>
#include<string.h>

struct pageEntry
{
	int valid;
	int dirty;
	int pageNum;
};


void read(int virtualAddress);
void write (int virtualAddress, int num);
void showMain (int physicalPageNumber);
void showDisk(int diskPageNumber);
void showPageTable();

struct pageEntry pageTable[8];
int mainMemory[16]= {0};
int disk[32] = {0};	
int main()
{
	char input[90];
	printf("Hello World\n");
	do
	{

	printf("> ");
	fgets(input, 90, stdin);
	printf("%s", input);
	
	
	}while(strcmp(input,"quit\n") != 0);
}

void read(int virtualAddress){

	//prints content of the Memory address

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
	int count = physicalPageNumber * 4;
	int final = count + 4;
	while(count < final)
	{
		printf("%d:%d\n",count,mainMemory[count]);
		count++;
	}	
}

void showDisk(int diskPageNumber){
	//prints out the 4 addresses and data associated with the disk page
	int count = diskPageNumber * 4;
	int final = count + 4;
	while(count < final)
	{
		printf("%d:%d\n",count,mainMemory[count]);
		count++;
	}	
}

void showPageTable(){
	//print out the 8 pageEntry Objects
	int count = 0;
	while(count < 8)
	{
		printf("%d:%d:%d:%d\n",count,pageTable[count].valid,pageTable[count].dirty,pageTable[count].pageNum);
		count++;
	}
}
