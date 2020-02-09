#include<stdio.h>
#include<string.h>
#include <stdlib.h>
struct pageEntry
{
	int valid;
	int dirty;
	int pageNum;
};

typedef struct { char* str; char c;} str_char_Map;

str_char_Map caseTable[] = {
	{"read", 'r'}, {"write", 'w'}, {"showmain", 'm'}, 
	{"showdisk", 'd'}, {"showptable", 'p'}
};

char casefromstr(char *key);
#define BADKEY 'x'

void read(int virtualAddress);
void write (int virtualAddress, int num);
void showMain (int physicalPageNumber);
void showDisk(int diskPageNumber);
void showPageTable();
int findAvailablePage();
void copyPageMemToDisk(int source, int destination);
void copyPageDiskToMem(int source, int destination);

struct pageEntry pageTable[8];
int mainMemory[16]= {-1}; // need to initialize all values to negative 1
int disk[32] = {-1};	// same here
int main()
{
	char input[90];
	char * token;
	char* argv[20];
	const char * str = " \n";
	int argCount = 0;
	int count = 0;

	printf("Hello World\n");

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
				read(atoi(argv[1]));
			break;
		case 'w':
				write(atoi(argv[1]),atoi(argv[2]));
			break;
		case 'm':		//showmain
				showMain(atoi(argv[1]));
			break;
		case 'd':		//showdisk
				showDisk(atoi(argv[1]));
			break;
		case 'p':		//showptable
				showPageTable();
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

void copyPageMemToDisk(int source, int destination)
{
	int increment = 0;
	int firstDiskAddress = destination * 4;
	int firstMainMemAddress = source *4;
	while( increment < 4)
	{
		disk[firstDiskAddress + increment] 
			= mainMemory[firstMainMemAddress + increment];
	}
}
void copyPageDiskToMem(int source, int destination)
{
	int increment = 0;
	int firstDiskAddress = source * 4;
	int firstMainMemAddress = destination *4;
	while( increment < 4)
	{
		mainMemory[firstMainMemAddress + increment] =
			disk[firstDiskAddress + increment];
	}
}


int findAvailablePage()
{
	//returns the first avaiable page in main memory that is free [0-3]
	// otherwises return -1 if no space is available.
	int mark[4]; // all should be initialized to 0;
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
			return count;
		count++;
	}
	return -1;

}

void read(int virtualAddress){
	//prints content of the Memory address
	int virtualPage = virtualAddress/4;
	printf("reading function, read this address %d\n",virtualPage);
	if(pageTable[virtualPage].valid != 1)
	{
		printf("An Page Fault Has Ocurred\n");
		showPageTable();
		// printf("Virtual Page %d is not in main memory\n", virtualPage);
		// printf("Physical Page %d in Main Memory is open.\n", findAvailablePage());
		int availablePage = findAvailablePage();
		if(availablePage == -1)
		{
			//FindVictimPage
			//CopyPage if dirty
			//CopyPage
		}
		copyPageDiskToMem(virtualPage,availablePage);
		return;
	}
		
	// pageTable[virtualPage].pageNum = page in Memory
	// virtualAddress % 4 =  offset from the 0th address in page;
	printf("This is the physical Address: %d\n", pageTable[virtualPage].pageNum + virtualAddress % 4);
	
	// if (){ //if page fault occurss print
	// 	printf("An Page Fault Has Ocurred\n");
	// }

}

void write (int virtualAddress, int num){

	//writes data to a memory location
printf("writing function, write in this address %d, this num %d\n",virtualAddress,num);
	// if (){ //if page fault occurss print
	// 	printf("An Page Fault Has Ocurred\n");
	// }
}

void showMain (int physicalPageNumber){
	//prints out the 4 address and data associated with the main memory page
	if(physicalPageNumber < 0 || physicalPageNumber > 3)
	{
		printf("Page %d does not exist in Main Memory, Trying searching pages 0-3.\n", physicalPageNumber);
		return;
	}
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
	if(diskPageNumber < 0 || diskPageNumber > 7)
	{
		printf("Page %d does not exist in Main Memory, Trying searching pages 0-7.\n", diskPageNumber);
		return;
	}
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