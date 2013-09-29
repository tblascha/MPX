/***********************************************
	MPX: The MultiProgramming eXecutive
	Start Program
	
	Authors: Dakota Kirby
			 Corey Hartley
			 Thomas Blaschak
			 Wisam Al-Malack

	File Name: HELP.H
	
	Purpose: Contains function prototypes for
			 help.c and contains codes for different 
			 help calls
			 
***********************************************/
#include <string.h>
#include <stdlib.h>
#include "config.h"
#include "comhan.h"

/* function prototypes*/
void help(char function_name[]);
FILE* open_file(char filename[]);
void print(FILE* fp);
void page_wait(void);
