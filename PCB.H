/***********************************************
	MPX: The MultiProgramming eXecutive
	Start Program
	
	Authors: Dakota Kirby
			 Corey Hartley
			 Thomas Blaschak
			 Wisam Al-Malack

	File Name: PCB.H
	
	Purpose: 
	
***********************************************/

#include "mpx_supt.h"
#include "config.h"

#define SYS 0
#define APP 1

/*Function Prototypes*/
void setup(void);
void set_priority(char buffer[]);
void resume_pcb(char buffer[]);
void block_pcb(char buffer[]);
void create_pcb(char buffer[]);
void delete_pcb(char buffer[]);
void show_all(void);
void show_blocked(void);
void show_ready(void);
void suspend_pcb(char buffer[]);
void unblock_pcb(char buffer[]);
void show_pcb(char buffer[]);