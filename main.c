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

struct pageEntry pageTable[8];
int mainMemory[16]= {0};
int disk[32] = {0};	
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

void read(int virtualAddress){

	//prints content of the Memory address
	printf("reading function, read this address %d \n",virtualAddress);
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