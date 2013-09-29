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

#include "mpx_supt.h"
#include "config.h"

// all swole team six error coeds
#define OK 				(0000)
#define CMD_NOT_FOUND 	(-200)
#define HELP_NOT_FOUND 	(-201)
#define NAME_INVLD		(-202)
#define PRIO_IVNLD		(-203)
#define PCB_EXIST		(-204)
#define MONTH_INVLD		(-205)
#define YEAR_INVLD		(-206)
#define DATE_IVNLD		(-207)
#define ERROR 			(-999)
// other defines as needed

void error_handle(int error_no/* corresponds to error number defined above*/);