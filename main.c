#include<stdio.h>
#include<string.h>
#include <stdlib.h>
struct pageEntry
{
	int valid;
	int dirty;
	int pageNum;
};
// creating a queue to implement FIFO and LRU algorithms
#define MAX_INT_VALUE  10000000
struct address
{
	int value;
	int accessed;
};
struct address mainMemory[16];
struct address disk[32];
int accessedCount = 0;


typedef struct { char* str; char c;} str_char_Map;

str_char_Map caseTable[] = {
	{"read", 'r'}, {"write", 'w'}, {"showmain", 'm'}, 
	{"showdisk", 'd'}, {"showptable", 'p'}
};

char casefromstr(char *key);
#define BADKEY 'x'

int findVictimPage();
void initializeValues();
int findPageinPageTable();
void read(int virtualAddress);
void write (int virtualAddress, int num);
void showMain (int physicalPageNumber);
void showDisk(int diskPageNumber);
void showPageTable();
int findAvailablePage();
void copyPageMemToDisk(int source, int destination);
void copyPageDiskToMem(int source, int destination);

struct pageEntry pageTable[8];
int main()
{
	char input[90];
	char * token;
	char* argv[20];
	const char * str = " \n";
	int argCount = 0;
	int count = 0;

	printf("Hello World\n");
	initializeValues();

	do
	{
		printf("> ");
		fgets(input, 90, stdin);
		// printf("%s", input);
		

		token = strtok(input,str);
		argv[0] = token;
		//printf(token);
		while ( token != NULL){

			token = strtok(NULL, str);
			argv[++argCount] = token;
			
		}
		
		// do{			//prints the arguments of the command
		// 	printf("[%s][%d]\n",argv[count],count);
		// 	count++;
		// }while (argv[count] != NULL);

		switch (casefromstr(argv[0])){
		case 'r':
				if (argCount == 2){
					read(atoi(argv[1]));
				}
			break;
		case 'w':
				if (argCount == 3){
					write(atoi(argv[1]),atoi(argv[2]));
				}
			break;
		case 'm':		//showmain
				if (argCount == 2){
					showMain(atoi(argv[1]));
				}
				
			break;
		case 'd':		//showdisk
				if (argCount == 2){
					showDisk(atoi(argv[1]));
				}
				
			break;
		case 'p':		//showptable
				if (argCount == 1){
					showPageTable();
				}
			break;

		}

		//resets to the start of the argv array
		if (argv[argCount] == NULL){
			argCount = 0;
			count = 0;
		}
		//printf("at the end input is:%s\n", input);
	}while(strcmp(input,"quit") != 0);
}

int findVictimPage()
{
	int smallestValue = MAX_INT_VALUE;
	int page = 0;
	int count = 0;
	while(count < 16)
	{
		if(smallestValue > mainMemory[count].accessed)
		{
			page = count;
			smallestValue = mainMemory[count].accessed;
		}
		count = count + 4;
	}
	if(smallestValue == MAX_INT_VALUE)
		return -1;
	return page/4;
}

void initializeValues()
{
	//initialize values for pageTable, mainMemory, disk
	int countPageTable = 0;
	while( countPageTable <= 7)
	{
		pageTable[countPageTable].pageNum = countPageTable;
		countPageTable++;
	}
	countPageTable = 0;
	while (countPageTable <= 15)
	{
		mainMemory[countPageTable].value = -1;
		mainMemory[countPageTable].accessed = MAX_INT_VALUE;
		countPageTable++;
	}
	countPageTable = 0;
	while(countPageTable <= 31)
	{
		disk[countPageTable].value = -1;
		disk[countPageTable].accessed = MAX_INT_VALUE;
		countPageTable++;
	}
	
}
void copyPageMemToDisk(int source, int destination)
{
	int increment = 0;
	int firstDiskAddress = destination * 4;
	int firstMainMemAddress = source *4;

	while( increment < 4)
	{
		printf("firstDiskAddress: %d, value: %d\n",firstDiskAddress + increment ,  mainMemory[firstMainMemAddress + increment].value);

		disk[firstDiskAddress + increment].value 
			= mainMemory[firstMainMemAddress + increment].value;
			increment++;
	}
	pageTable[destination].valid = 0;
	pageTable[destination].dirty = 0;
}
void copyPageDiskToMem(int source, int destination)
{
	int increment = 0;
	int firstDiskAddress = source * 4;
	int firstMainMemAddress = destination *4;
	while( increment < 4)
	{
		mainMemory[firstMainMemAddress + increment].value = disk[firstDiskAddress + increment].value;
		increment++;
	}
	pageTable[source].pageNum = destination;
	pageTable[source].valid = 1;
	pageTable[source].dirty = 1;
}
int findAvailablePage()
{
	//returns the first avaiable page in main memory that is free [0-3]
	// otherwises return -1 if no space is available.
	int mark[4] = {0,0,0,0}; // all should be initialized to 0;
	int count = 0;
	while(count <= 7)
	{
		if(pageTable[count].valid == 1)
		{
			mark[pageTable[count].pageNum] = -1;
		}
		count++;
	}
	count = 0;
	while(count <= 3)
	{
		if(mark[count] == 0)	
			return count; // returns the physical Page that is empty
		count++;
	}
	//Call either FIFO or LRU replacement algorithm
	printf("calling nulll on findAvailablePage\n");
	return -1;

}



void read(int virtualAddress){
	//prints content of the Memory address
	int virtualPage = virtualAddress/4;
	int offset = virtualAddress % 4;
	//update accessedCount if in LRU mode
	if(pageTable[virtualPage].valid != 1)
	{
		printf("An Page Fault Has Ocurred\n");
		int availablePage = findAvailablePage(); //return 0-7 or -1
		if(availablePage == -1)
		{
			availablePage = findVictimPage();
			if(pageTable[availablePage].dirty == 1)
				copyPageMemToDisk(availablePage,pageTable[availablePage].pageNum);
		}
		copyPageDiskToMem(virtualPage,availablePage);//
		if(0)//LRU enabled
		{
			mainMemory[pageTable[availablePage].pageNum * 4].accessed = accessedCount;
			accessedCount++;
		}
		printf("%d\n",mainMemory[pageTable[availablePage].pageNum * 4 + offset].value);
		return;
	}
	if(0)//LRU enabled TODO
	{
		mainMemory[pageTable[virtualPage].pageNum * 4].accessed = accessedCount;
		accessedCount++;
	}
	printf("%d\n", mainMemory[pageTable[virtualPage].pageNum * 4 + offset].value);
	
}

void write (int virtualAddress, int num){
	int virtualPage = virtualAddress/4;
	int offset = virtualAddress % 4;
	// checking if virtual page is in main memory
	if(pageTable[virtualPage].valid != 1)
	{
		printf("An Page Fault Has Ocurred\n");
		// finding an empty main memory page
		int availablePage = findAvailablePage();
		printf("findAvaiablePage: %d\n", availablePage);
		if(availablePage == -1)
		{
			// finding the least used page to kill
			availablePage =  findVictimPage();
			printf("findVictimPage: %d\n", availablePage);
			pageTable[availablePage].valid = 0;
			// if page is dirty, copy it to disk
			if(pageTable[availablePage].dirty == 1)
			{
				copyPageMemToDisk(availablePage,pageTable[availablePage].pageNum);
			}

			
		}
		// copy page from disk to main memory
		copyPageDiskToMem(virtualPage,availablePage);
		printf("copyPageDiskToMem\n");
		// increment count for that particular page
		mainMemory[pageTable[virtualPage].pageNum * 4].accessed = accessedCount;
		accessedCount++;
		// setting page value
		mainMemory[availablePage*4 + offset].value = num;
		return;
	}
	//increment count when writing to page
	mainMemory[pageTable[virtualPage].pageNum * 4].accessed = accessedCount;
	accessedCount++;
	// changing page in main memory
	mainMemory[pageTable[virtualPage].pageNum + offset].value = num;
	// dirtying page
	pageTable[virtualPage].dirty = 1;
}

void showMain (int physicalPageNumber){
	//prints out the 4 address and data associated with the main memory page
	int count = physicalPageNumber * 4;
	int final = count + 4;
	while(count < final)
	{
		printf("%d:%d\n",count,mainMemory[count].value);
		count++;
	}	
}

void showDisk(int diskPageNumber){
	//prints out the 4 addresses and data associated with the disk page
	if(diskPageNumber < 0 || diskPageNumber > 7)
	{
		printf("Page %d does not exist in Main Memory, Trying searching pages 0-7.\n", diskPageNumber);
		return;
	}
	int count = diskPageNumber * 4;
	int final = count + 4;
	while(count < final)
	{
		printf("%d:%d\n",count, disk[count].value);
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

char casefromstr(char *key)
{
    int i;
    for (i=0; i < 5; i++) {
        //str_char_Map *map = caseTable[i];
        if (strcmp(caseTable[i].str, key) == 0)
            return caseTable[i].c;
    }
    return BADKEY;
}