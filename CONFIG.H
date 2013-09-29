/***********************************************
	MPX: The MultiProgramming eXecutive
	Start Header
	
	Authors: Dakota Kirby
			 Corey Hartley
			 Thomas Blaschak
			 Wisam Al-Malack

	File Name: CONFIG.H
	
	Purpose: This file contains all information on
			version information, date modified, and
			various structures of PCB, and queues
	
	Procedures In This Program
		closing
	
***********************************************/
#ifndef CONFIG_H
#define CONFIG_H

#define VERSION 2.0
#define DATE 10/4/2013

// PCB Structure
typedef struct{
	char name[12]; // name of process
	int classs;
	int priority;
	int states;
	unsigned char *top;
	unsigned char *base;
	struct PCB *next; // next PCB in queue
	struct PCB *prev; // prev PCB in queue
}PCB;

// Queue Structure
typedef struct{
	int count; // number of items
	PCB *head; // start of queue
	PCB *tail; // end of queue
}queue;
// There are four queue is main program ready, blocked, ready_suspended, blocked_suspeneded

#endif