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
#includ "config.h"

/* function prototypes*/
void help(char function_name [] /* function name from input*/);
void ignore_case(char a[] /*initial string*/, char *b /*new string in lower case*/);
void page(void /* no parameters */);
