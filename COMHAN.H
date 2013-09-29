/***********************************************
	MPX: The MultiProgramming eXecutive
	Command Handler Header File
	
	Authors: Dakota Kirby
			 Corey Hartley
			 Thomas Blaschak
			 Wisam Al-Malack

	File Name: COMHAN.H
	
	Purpose: Header file for comhan.c
	
	Procedures In This Program
		comhan
		comhan_exit
		disp_date
		set_date
		help
		look_dir
		disp_version
		ignore_case
	
***********************************************/

/* ANSI C Include Files */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/* Function Prototypes*/
void comhan(void /* no parameters */);
int comhan_exit(void /* no parameters */);
void disp_date(void /* no parameters */);
void set_date(char date [] /* date string form input */);
int stringToDate(date_rec *newDate /* date being returned */, char date[] /*date being converted */);
void help(char function_name [] /* function name from input*/);
void look_dir(char directory[] /* directory name from input*/);
void disp_version(/* no parameters */ );
void ignore_case(char a[] /*initial string*/, char *b /*new string in lower case*/);
void page(void);