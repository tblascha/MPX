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

#include "mpx_supt.h"
#include "config.h"

void setup(void){
	// set up all the queues before beginning
}
void set_priority(char buffer[]){
	char name[255];
	char priority_string[255];
	int priority;
	int i = 0,j =0 ;
	PCB *change;
	while(buffer[i] != ' ' && buffer[i] != '\n'){ // get name from buffer
		name[i] == buffer[i]
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
	pritority_string = '\0';
	priority = string_to_int(priority_string);
	if(priority <-128 || priority > 127){
		priority = PRIORITY_INVALID;
		// handle error here
		return;
	}
	
	remove(change);
	change.priority = priorirty;
	insert(change);
	// print success message
		
}
void resume_pcb(char buffer[]);
void block_pcb(char buffer[]);
void create_pcb(char buffer[]){
	char name[255];
	char class_string[255];
	char priority_string[255];
	int class
	int priority;
	int i = 0,j =0,k=0;
	PCB *new_PCB;
	while(buffer[i] != ' ' && buffer[i] != '\n'){ // get name from buffer
		name[i] == buffer[i]
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
	pritority_string = '\0';
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
		name[i] == buffer[i]
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

void show_all(void);
void show_blocked(void);
void show_ready(void);
void suspend_pcb(char buffer[]);
void unblock_pcb(char buffer[]);
void show_pcb(char buffer[]);

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