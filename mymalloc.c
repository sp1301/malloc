#include<stdlib.h>
#include<stdio.h>
#include "mymalloc.h" 
#include<string.h>

MemE head = NULL;
MemE tail = NULL;

static char AllMemory[5000];
static int THRESHOLD = 18; //threshold considered for small items <= 18

int FindCapacity(int x){ //finds total capacity of left (if input is 1) and right side otherwise
  MemE temp = NULL;
  if(x == 1){
    temp = head;
  }
  else{
    temp = tail;
  }
  int counter;
  while(temp->next != NULL){
    counter += SIZE + temp->capacity;
    temp = temp->next;
  }
  return counter;
}


MemE CreateMemE(unsigned int input, char* ptr){ //create struct MemEntry
  struct MemEntry* temp = (struct MemEntry*)ptr;
  temp->capacity = input;
  temp->specialcode = 1234567890;
  temp->next = NULL;
  temp->isfree = '0';
  return temp;
}

MemE RemainingMem = NULL;

char test(int input){
  return(AllMemory[input]);
}
//We used a 4 round system to efficiently places input based on space. 4 rounds for each head and tail (small or large). 
//If the space is full and a large was freed and they malloc a small. The small will be put in the large block and vise versa.
void* mymalloc(unsigned int input, char* fileName, unsigned int lineNum){ //insert linked list
  if(RemainingMem == NULL){//if first run of program 
    RemainingMem = CreateMemE(5000-SIZE, &AllMemory[0]);
    RemainingMem->isfree = '1';
  }
  MemE temp = NULL;
  MemE temp2 = NULL;
  MemE prev = NULL;
  char* memPtr = NULL;
  int counter = 0;
  int round = 0, addsubtract = 0, start = 0;
  if(input < 0)
    input = input * -1;
  if(input <= THRESHOLD){ //if the number is small then start from head
    start = 2;
    addsubtract = -1;
  }
  else{ //if the number is large start from tail
    start = 1;
    addsubtract = 1;
  }
  while(start > 0 && start < 3){
    if(start == 2){ //input on left
      if(head == NULL){//if first item on left side
		  if(RemainingMem -> capacity == input + SIZE){//if remaining mem is exactly equal to input capacity
			memPtr = &AllMemory[input + SIZE];
			RemainingMem = CreateMemE(0,memPtr);
			RemainingMem -> isfree = '1';
			temp = tail;//makes sure tail points to RemainingMem
			if(temp != NULL)
			{		
				while(temp ->next->next != NULL)
				{
					temp = temp -> next;
				}
				temp -> next = RemainingMem;
			}
			memPtr = &AllMemory[0];
			head = CreateMemE(input , memPtr);
			head -> next = RemainingMem;
			memPtr = &AllMemory[SIZE];
			return (void*)memPtr;
		}
	if(RemainingMem->capacity > input + SIZE){ //head will begin on the left
	  memPtr = &AllMemory[input + SIZE];
	  RemainingMem = CreateMemE(RemainingMem->capacity - input - SIZE, memPtr);
	  RemainingMem->isfree = '1';
	  temp = tail;// makes sure tail points to RemainingMem
	  if(temp != NULL)
	  {		
		while(temp ->next->next != NULL)
		{
			temp = temp -> next;
		}
		temp -> next = RemainingMem;
	  }
	  memPtr = &(AllMemory[0]);
      head = CreateMemE(input, memPtr);
	  head->next = RemainingMem;
	  memPtr = &AllMemory[SIZE];
	  return((void*)memPtr);
	}
	else{
	  return NULL; //not enough room - taken by tail
	}
      }
      else{
	temp = head;
	temp2 = temp->next;
	counter = 0;
	round = 1;
	while(round < 5 && temp != NULL){//rounds to efficiently place input
	  if(round == 1){//check if any slots EXACTLY match the input
	    if(temp->isfree == '1' && temp->capacity == input){ 
	      temp->isfree = '0';
	      memPtr = &AllMemory[counter + SIZE];
	      return((void*)memPtr);
	    }
	    else if(temp->next->next == NULL){ // check for end of list;
	      round = 2;
	      temp = head;
	      temp2 = head->next; 
	      counter = 0;
	    }
	    else{ // increment
	      counter += SIZE + temp->capacity;
	      temp = temp->next;
	      temp2 = temp->next;
	    }
	  }
	  if(round == 2){ //check if any slots can fit in the input and have room for a pointer to free memory
	    if(temp->isfree == '1' && temp->capacity > input + SIZE){
	      temp->isfree = '0';
	      memPtr = &AllMemory[counter+SIZE+input];
	      temp->next = CreateMemE(temp->capacity-input - SIZE, memPtr);
		  temp->next->isfree = '1';
	      temp->capacity = input;
	      temp->next->next = temp2;
	      memPtr = &AllMemory[counter + SIZE];
	      return((void*)memPtr);
	    }
	    else if(temp->next->next == NULL){ // check for end of list;
	      round = 3;
	      temp = head;
	      temp2 = head->next; 
	      counter = 0;
	    }
	    else{ // increment
	      counter += SIZE + temp->capacity;
	      temp = temp->next;
	      temp2 = temp->next;
	    }
	  }
	  if(round == 3){ //put data into free memory if it has room
	    if(RemainingMem->isfree == '1' && RemainingMem->capacity > input){
	      counter = 0;
	      while(temp->next->next != NULL){
		counter += temp->capacity + SIZE;
		temp = temp->next;
	      }
	      if(RemainingMem -> capacity <= input + SIZE + SIZE){
			RemainingMem -> isfree = '0';
			memPtr = &AllMemory[counter + SIZE + temp->capacity + SIZE];
			return (void*)memPtr;
		  }
	      memPtr = &AllMemory[counter + SIZE + temp->capacity + SIZE + input];
	      RemainingMem = CreateMemE(RemainingMem->capacity - input - SIZE, memPtr);
	      RemainingMem->isfree = '1';
		  memPtr = &AllMemory[counter + SIZE + temp->capacity];
	      temp->next = CreateMemE(input, memPtr);
	      temp->next->next = RemainingMem;
	      memPtr = &AllMemory[counter + SIZE + temp->capacity + SIZE];
	      return((void*)memPtr);
	    }
		else{ // check for end of list;
	      round = 4;
	      temp = head;
	      temp2 = head->next; 
	      counter = 0;
	    }
	  }
	  if(round == 4){ //check if any slots can fit in the input but does not have room for a pointer to free memory afterwards (including remaining mem)
	    if(temp->isfree == '1' && temp->capacity > input){ 
	      temp->isfree = '0';
	      memPtr = &AllMemory[counter + SIZE];
	      return((void*)memPtr);
	    }
	    else if(temp->next == NULL){ // check for end of list;
	      round = 5;
	      temp = head;
	      temp2 = head->next; 
	      counter = 0;
	    }
	    else{ // increment
	      counter += SIZE + temp->capacity;
	      temp = temp->next;
	      temp2 = temp->next;
	    }
	  }
	}
      }
      start += addsubtract;
    }
    if(start == 1){ //input on right
      if(tail == NULL){
		if(RemainingMem -> capacity == input + SIZE){
			memPtr = &AllMemory[FindCapacity(1)+SIZE];
			tail = CreateMemE(input , memPtr);
			RemainingMem -> capacity = 0;
			tail -> next = RemainingMem;
			memPtr = &AllMemory[FindCapacity(1) + SIZE + SIZE];
			return (void*)memPtr;
		}
	if(RemainingMem->capacity > input + SIZE){ //tail will begin on the right
	  memPtr = &AllMemory[5000 - input - SIZE - 1];
	  tail = CreateMemE(input, memPtr);
	  RemainingMem->capacity -= (tail->capacity + SIZE);
	  tail->next = RemainingMem;
	  memPtr = &AllMemory[5000 - tail->capacity - 1];
	  return((void*)memPtr);
	}
	else{
	  return NULL; //not enough room - taken by tail
	}
      }
      else{
	temp = tail;
	temp2 = temp->next;
	counter = 4999;
	round = 1;
	while(round < 4 && temp != NULL){
	  if(round == 1){//check if any slots EXACTLY match the input
	    if(temp->isfree == '1' && temp->capacity == input){ 
	      temp->isfree = '0';
	      RemainingMem->capacity -= input;
	      memPtr = &AllMemory[counter - temp->capacity]; 
	      return((void*)memPtr);
	    }
	    else if(temp->next->next == NULL){ // check for end of list;
	      round = 2;
	      temp = tail;
	      temp2 = tail->next; 
	      counter = 4999;
	    }
	    else{ // decrement
	      counter -= (SIZE + temp->capacity);
	      temp = temp->next;
	      temp2 = temp->next;
	    }
	  }
	  if(round == 2){ //check if any slots can fit in the input and have room for a pointer to free memory
	    if(temp->isfree == '1' && temp->capacity > input + SIZE){
	      memPtr = &AllMemory[counter-SIZE-input];
	      prev->next = CreateMemE(input, memPtr);
		  prev -> next -> next = temp;
	      temp->capacity -= (input + SIZE);
	      memPtr = &AllMemory[counter - SIZE - input];
	      return((void*)memPtr);
	    }
	    else if(temp->next->next == NULL){ // check for end of list;
	      round = 3;
		  prev = NULL;
	      temp = tail;
	      temp2 = tail->next; 
	      counter = 4999;
	    }
	    else{ // increment
	      counter -= (SIZE + temp->capacity);
	      prev = temp;
		  temp = temp->next;
	      temp2 = temp->next;
		  
	    }
	  }
	  if(round == 3){ //put data into free memory if it has room
	    if(RemainingMem->isfree == '1' && RemainingMem->capacity > input + SIZE){
	      counter = 4999;
	      while(temp->next->next != NULL){
		counter -= (temp->capacity + SIZE);
		temp = temp->next;
	      }
		  if(RemainingMem -> capacity <= input + SIZE + SIZE){
			RemainingMem -> isfree = '0';
			memPtr = &AllMemory[counter - SIZE - temp->capacity - RemainingMem -> capacity];
			return (void*)memPtr;
		  }
	      memPtr = &AllMemory[counter - SIZE - temp->capacity - SIZE - input];
	      temp->next = CreateMemE(input, memPtr);
	      temp->next->next = RemainingMem;
	      memPtr = &AllMemory[counter - SIZE - temp->capacity - input];
		  RemainingMem -> capacity -= (input + SIZE);
	      return((void*)memPtr);
	    }
		else{ // check for end of list;
	      round = 4;
	      temp = tail;
	      temp2 = tail->next; 
	      counter = 4999;
	    }
	  }
	  if(round == 4){ //check if any slots can fit in the input but does not have room for a pointer to free memory afterwards (including remaining mem)
	    if(temp->isfree == '1' && temp->capacity > input){ 
	      temp->isfree = '0';
	      memPtr = &AllMemory[counter - SIZE - temp->capacity];
	      return((void*)memPtr);
	    }
	    else if(temp->next == NULL){ // check for end of list;
	      round = 5;
	      temp = tail;
	      temp2 = tail->next; 
	      counter = 4999;
	    }
	    else{ // increment
	      counter += SIZE + temp->capacity;
	      temp = temp->next;
	      temp2 = temp->next;
	    }
	  } 
	} 
      } 
      start += addsubtract;
    }
  }
  return(NULL);
}


//goes on two rounds, the first round makes the input's block isfree to being '1' which means that block is now free. else returns error. 
//second round will go through both list head and tail and cheack if there are any consecutive isfree = '1' so that they can merge as one block. 
void* myfree(void* index, char* fileName, unsigned int lineNum){ //delete linked list
  if(RemainingMem == NULL){
    RemainingMem = CreateMemE(5000-SIZE, &AllMemory[0]);
    RemainingMem->isfree = '1';
  }
  MemE temp = head;
  MemE prev = NULL;
  MemE prev2 = NULL;
  int counter = 0;
  int output = -1;
  //looks through from the left and right side to see if the input pointer is valid
  while(temp != NULL && temp->next != NULL){ //clean from left
    if(temp+1 == index){
		if(temp->isfree == '1'){
			printf("Fatal error in malloc call from line %d in file %s: already freed memory\n", lineNum, fileName);
			return NULL;
		}
      temp->isfree = '1';  
      output = counter + SIZE;
    }
    counter += SIZE + temp->capacity;
    temp = temp->next;
  }
  temp = tail;
  while(temp != NULL && temp->next != NULL){ //clean from right
    if(temp+1 == index){
      if(temp->isfree == '1'){
	printf("Fatal error in malloc call from line %d in file %s: already freed memory\n", lineNum, fileName);
	return NULL;
      }
      temp->isfree = '1';
      output = counter + SIZE; 
    }
    counter += SIZE + temp->capacity;
    temp = temp->next;
  }
  if(output == -1){// if the input was never found error
    printf("Fatal error in malloc call from line %d in file %s: non-allocated memory\n", lineNum, fileName);
    return NULL;
  }
  temp = head; 
  counter = 0;
  //look is any node next to each other and merges them accordingly
  while(temp != NULL){//connect adjacent free nodes
  // this is the head check
    if(prev != NULL){
      if(temp->next == NULL && prev->isfree == '1' && temp->isfree == '1'){ //if last node before RemainingMem is free
        output = counter - prev->capacity;
	prev->capacity += RemainingMem->capacity + SIZE;
        prev->next = NULL;
	RemainingMem = prev;
	temp = NULL;
	if(tail != NULL){
	  temp = tail;
	  if(temp->next->next != NULL){
	    while(temp->next->next != NULL){
	      temp= temp->next;
	    }
	  }
	  temp->next = RemainingMem;
	}
	if(prev2 == NULL)
          head = NULL;
	temp = NULL;
      }
      else if(temp->isfree == '1' && prev->isfree == '1'){ //if current and previous nodes are free
	output = counter - prev->capacity; 
	prev->capacity += SIZE + temp->capacity;
	prev->next = temp->next;
	temp = NULL;
	temp = prev->next;
      }
      else{ 
	counter += SIZE + temp->capacity;
	if(prev != NULL)
	  prev2 = prev;
	prev = temp;
	temp = temp->next;
      }
    }
    else{
      counter += SIZE + temp->capacity;
      if(prev != NULL)
	prev2 = prev;
      prev = temp;
      temp = temp->next;
    }
  }
  //this is the tail cheack
  temp = tail;
  prev2 = NULL;
  prev = NULL;
  counter = 4999;
  while(temp != NULL){//connect adjacent free nodes
    if(prev != NULL){
      if(temp->next == NULL && prev->isfree == '1' && temp->isfree == '1'){ //if last node before RemainingMem is free
	RemainingMem->capacity += prev->capacity + SIZE;
	if(prev2 != NULL){
	  prev2->next = RemainingMem;
	}
	else{
	  tail = NULL;
	}
	temp = NULL;
      }
      else if(temp->isfree == '1' && prev->isfree == '1'){ //if current and previous nodes are free
        output = counter + SIZE ;
        temp->capacity += SIZE + prev->capacity;
        if(prev2 != NULL){
	  prev2->next = temp;
	}
	else{
	  tail = temp;
	}
        prev = NULL;
      }
      else{
        counter += SIZE + temp->capacity;
	if(prev != NULL){
	  prev2 = prev;
	}
        prev = temp;
        temp = temp->next;
      }
    }
    else{
      counter -= (SIZE + temp->capacity);
      if(prev != NULL){
	prev2 = prev;
      }
      prev = temp;
      temp = temp->next;
    }
  }
  return((void*)&AllMemory[output]); 
}

/*int main(int argc, char** argv){
  return 0;
  }*/

/*error check
else{
		printf("Fatal error in malloc call from line %zu in file %s\n", linenum, filename)'
}

