/***********************************************
	MPX: The MultiProgramming eXecutive
	Start Program
	
	Authors: Dakota Kirby
			 Corey Hartley
			 Thomas Blaschak
			 Wisam Al-Malack

	File Name: ERROR.H
	
	Purpose: This file is to set-up function 
			 prototypes and declare different 
			 error codes to produce error statements
	
***********************************************/

/*Error Codes*/
#define OK 0
#define PCB_DOESNT_EXIST 130
#define PRIORITY_INVALID 131
#define NAME_INVALID 132
#define CLASS_INVALID 133
#define PCB_NOT_FOUND 134

/*Function Prototypes*/
void error_handle(int error/* integer error code*/);