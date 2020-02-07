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

	printf("> ");
	fgets(input, 90, stdin);
	printf("%s", input);
	
	
	}while(strcmp(input,"quit\n") != 0);


	return 0;

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

void showPageTable(){
	//print out the 8 pageEntry Objects
}