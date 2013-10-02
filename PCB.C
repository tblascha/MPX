/***********************************************
	MPX: The MultiProgramming eXecutive
	Start Program

	Authors: Dakota Kirby
			 Corey Hartley
			 Thomas Blaschak
			 Wisam Al-Malack

	File Name: PCB.C

	Purpose:

***********************************************/


// Program Includes
#include "mpx_supt.h"
#include "pcb.h"

void setup(void){
	//ready queue
	ready.count = 0;
	ready.head = NULL;
	ready.tail = NULL;
	sys_alloc_mem(&ready);	

	//blocked queue
	blocked.count = 0;
	blocked.head = NULL;
	blocked.tail = NULL;
	sys_alloc_mem(&blocked);
	
	//ready suspended queue
	ready_suspended.count = 0;
	ready_suspended.head = NULL;
	ready_suspended_tail = NULL;
	sys_alloc_mem(&ready_suspended);

	//blocked suspended queue
	blocked_suspended.count = 0;
	blocked_suspended.head = NULL;
	blocked_suspended.tail = NULL;
	sys_alloc_mem(&blocked_suspended);
}

void destroy_PCB(){}
PCB* setup_PCB(char name[], int cls, int pri){}
void free_PCB(char name[]){}
int remove_PCB(char name[]){}
PCB* find_PCB(char name[]){}
void insert_PCB(char name[]){}
void insert(char name[]){}
void set_priority(char buffer[]){
	char name[255];
	char priority_string[255];
	int priority;
	int i = 0,j =0 ;
	PCB *change;
	while(buffer[i] != ' ' && buffer[i] != '\n'){ // get name from buffer
		name[i] = buffer[i];
		i++;
	}
	name[i] = '\0';
	change = find_PCB(name);
	if(change == NULL){
		// handle error here
		return;
	}
	i++;
	while(buffer[i] != ' ' && buffer[i] != '\n'){ // get priority from buffer
		priority_string[j] = buffer[i];
		i++;
		j++;
	}
	priority_string[j] = '\0';
	priority = string_to_int(priority_string);
	if(priority <-128 || priority > 127){
		priority = PRIORITY_INVALID;
		// handle error here
		return;
	}

	remove(change);
	change->priority = priority;
	insert(change);
	// print success message

}
void resume_pcb(char buffer[]){}
void block_pcb(char buffer[]){}
void create_pcb(char buffer[]){
	char name[255];
	char class_string[255];
	char priority_string[255];
	int class;
	int priority;
	PCB *change;
	int i = 0,j =0,k=0;
	PCB *new_PCB;
	while(buffer[i] != ' ' && buffer[i] != '\n'){ // get name from buffer
		name[i] = buffer[i];
		i++;
	}
	name[i] = '\0';
	change = find_PCB(name);
	if(change != NULL && strlen(name) < 8){
		// handle error here
		return;
	}
	i++;
	while(buffer[i] != ' ' && buffer[i] != '\n'){ // get class from buffer
		class_string[j] = buffer[i];
		i++;
		k++;
	}
	class_string[i] = '\0';
	class = string_to_int(class_string);
	if (class != SYS || class != APP){
		class = CLASS_INVALID;
		// handle error here
		return;
	}
	while(buffer[i] != ' ' && buffer[i] != '\n'){ // get priority from buffer
		priority_string[k] = buffer[i];
		i++;
		k++;
	}
	priority_string[k] = '\0';
	priority = string_to_int(priority_string);
	if(priority <-128 || priority > 127){
		priority = PRIORITY_INVALID;
		// handle error here
		return;
	}

	new_PCB = setup_PCB(name,class,priority);
	if (new_PCB == NULL){
		// handle error
		return;
	}
	insert_PCB(new_PCB);
}

void delete_pcb(char buffer[]){
	char name[255];
	int i = 0;
	int error;
	PCB *remove;
	while(buffer[i] != ' ' && buffer[i] != '\n'){ // get name from buffer
		name[i] = buffer[i];
		i++;
	}
	name[i] = '\0';
	remove = find_PCB(name);
	if (remove == NULL){
		// handle error
		return;
	}
	error = remove_PCB(remove);
	if(error != OK){
		// handle error here
		return;
	}
	error = free_pcb(remove);
	if(error != OK){
		// handle error here
		return;
	}
}

void show_all(void){}
void show_blocked(void){
	int i; 
	buffer_size = 255;
	char ready[15] = "Blocked Queue:\n\n";
	char value[buffersize] = null;
	sys_req(WRITE, TERMINAL, , &buffer_size);
	for(i=blocked->front; i<blocked->back; i++){
		value = blocked->store[j];
		sys_req(WRITE, TERMINAL, value, &buffer_size);	
	}
}
void show_ready(void){
	int i; 
	buffer_size = 255;
	char ready[15] = "Ready Queue:\n\n";
	char value[buffersize] = null;
	sys_req(WRITE, TERMINAL, , &buffer_size);
	for(i=ready->front; i<ready->back; i++){
		value = ready->store[j];
		sys_req(WRITE, TERMINAL, value, &buffer_size);	
	}
}
void suspend_pcb(char buffer[]){}
void unblock_pcb(char buffer[]){}
void show_pcb(char buffer[]){}

int string_to_int(char string[]){
	int i=0, sum = 0, mult = 1;
	if(string[i] == 45){
			mult = -1;
	}
	else if(string[i] == '\0'){
		return -1000;
	}
	i++;
	while(string[i] != '\0'){
		if(string[i] <48 || string[i] >57){
			sum = -1000;
			return sum;
		}
		else{
			sum = sum *10 + (string[i] - 48);
			i++;
		}
	}
	return mult*sum;
}
