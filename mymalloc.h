//#ifndef MemEntry_H
//#define MemEntry_H

#include<stdlib.h>

#define malloc( x ) mymalloc((x), __FILE__, __LINE__ ) 
#define free( x ) myfree((x), __FILE__, __LINE__ )


struct MemEntry{ //sizeof MemEntry = 32 bits
	unsigned int capacity;
	int specialcode; 
	struct MemEntry* next;
	char isfree;
};

typedef struct MemEntry* MemE;

#define SIZE sizeof(struct MemEntry)
 
MemE CreateMemE(unsigned int, char*); //create struct MemEntry

void* mymalloc(unsigned int, char* , unsigned int); //insert linked list

void* myfree(void*, char* , unsigned int);//delete linked list
