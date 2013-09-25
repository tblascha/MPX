/***********************************************
	MPX: The MultiProgramming eXecutive
	Start Program
	
	Authors: Dakota Kirby
			 Corey Hartley
			 Thomas Blaschak
			 Wisam Al-Malack

	File Name: START.C
	
	Purpose: Allows comhan to run and initializes and closes program
	
	Procedures In This Program
		main
		closing
	
***********************************************/

// Program Includes
#include "mpx_supt.h"
#include "comhan.h"
#include "start.h"
#include "config.h"

/*
	Procedure: main
	Purpose: runs all commands 
	Return value: void
	Calls: sys_init
		   comhan
		   sys_exit
*/
int main(void){
	int system_init = sys_init(MODULE_R2);
	comhan();
	return 0;
	sys_exit();
}

/*
	Procedure: closing
	Purpose: closing routines
	Parameters: see prototype  
	Return value: void
	Calls: none
*/
int closing(void){
	// closing routines
	return 0;
}
