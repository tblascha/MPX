/***********************************************
	MPX: The MultiProgramming eXecutive
	Start Program
	
	Authors: Dakota Kirby
			 Corey Hartley
			 Thomas Blaschak
			 Wisam Al-Malack

	File Name: HELP.C
	
	Purpose: Handles import help text files such that
			 it can be used to display to the
			 terminal window
	
***********************************************/
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#includ "config.h"

/*
	Procedure: help
	Purpose: displays help summary or specific function help
	Parameters: see prototype
	Return value: void
	Calls: ignore_case
		   sizeof
		   sys_req
*/
void help(char function_name[]){
	if (function_name[0] != NULL && function_name[0] !='\n'){ // if command is input after help
		char temp[255];
		char command[255];
		int i = 0;

		while (function_name[i] != '\n'){ // get command
			temp[i] = function_name[i];
			i++;
		}

		temp[i] = '\0';
		ignore_case(temp,&command); // convert to lower case

		if(strcmp(temp,"sdate")==0){ // help for set date
			char message[] = "sdate - Allows the user to set the date\n";
			char message2[]= "by enterting the mm/dd/yyyy after the sdate\n";
			char message3[] = "command and then hitting enter\n";

			int s1 = sizeof(message)-1;
			int s2 = sizeof(message2)-1;
			int s3 = sizeof(message3)-1;

			sys_req(WRITE,TERMINAL,message,&s1);
			sys_req(WRITE,TERMINAL,message2,&s2);
			sys_req(WRITE,TERMINAL,message3,&s3);
		}
		else if(strcmp(temp,"ddate")==0){ // help for display date
			char message[] = "ddate - Allows the user to display the date\n";
			char message2[]= "of the system in mm/dd/yyyy format\n";

			int s1 = sizeof(message)-1;
			int s2 = sizeof(message2)-1;

			sys_req(WRITE,TERMINAL,message,&s1);
			sys_req(WRITE,TERMINAL,message2,&s2);
		}
		else if(strcmp(temp,"ver")==0){ // help for version display
			char message[] = "ver - Allows the user to see the current\n";
			char message2[]= "system version being used\n";

			int s1 = sizeof(message)-1;
			int s2 = sizeof(message2)-1;

			sys_req(WRITE,TERMINAL,message,&s1);
			sys_req(WRITE,TERMINAL,message2,&s2);
		}
		else if(strcmp(temp,"dir")==0){ // help for look at directory
			char message[] = "dir - Allows the user to view .mpx files in\n";
			char message2[]= "a directory. The user must specfiy a path following\n";
			char message3[] = "the command if not current directory is used\n";

			int s1 = sizeof(message)-1;
			int s2 = sizeof(message2)-1;
			int s3 = sizeof(message3)-1;

			sys_req(WRITE,TERMINAL,message,&s1);
			sys_req(WRITE,TERMINAL,message2,&s2);
			sys_req(WRITE,TERMINAL,message3,&s3);
		}
		else if(strcmp(temp,"exit")==0){ // help for exit
			char message[] = "exit - Allos the user to terminate MPX\n";
			char message2[]= "on their own. Upon using exit user will\n";
			char message3[] = "be prompted if they want to continue\n";

			int s1 = sizeof(message)-1;
			int s2 = sizeof(message2)-1;
			int s3 = sizeof(message3)-1;

			sys_req(WRITE,TERMINAL,message,&s1);
			sys_req(WRITE,TERMINAL,message2,&s2);
			sys_req(WRITE,TERMINAL,message3,&s3);
		}
		else{ // cant find help command
			char message[] = "Help cannot find that command\n";

			int s = sizeof(message)-1;

			sys_req(WRITE,TERMINAL,message,&s);
		}

	}
	else{ // display help summary
		FILE *fp;
		fp = open_file("\Help Files\summary.txt");
		print(fp);
	}

}

FILE* open_file(char file_name[]){
	FILE *file_pointer = fopen(file_name, "r");
	if(file_pointer == NULL){
		error_handle(FILE_OPEN_FAIL);
	}
	return file_pointer;
}

void print(FILE *file){
	char buffer[50];
	int count = 0;
	int error = fscanf(file_pointer, "%s", buffer);
	buffer[48]='\n';
	buffer[49]='\0';
	while(error != EOF){
		int size = sizeof(buffer)-1;
		sys_req(WRTIE,TERMINAL,buffer,&size);
		error = fscanf(file_pointer,"%s",buffer);
		count++;
		if(count%5 == 0){
			page();
		}
	}
}

/*
	Procedure: page
	Purpose: to help create in pages when they may be longer than the screen
	Parameters: see prototype  
	Return value: void
	Calls: sizeof
		   sys_req
*/
void page(void){
	char message[] = "\nPress ANY KEY(s) then ENTER to continue. \n";
	char buffer [255];
	int msize = sizeof(message)-1;
	int bsize = sizeof(buffer);
	
	sys_req(WRITE,TERMINAL,message, &msize);
	sys_req(READ,TERMINAL,buffer, &bsize);
}

/*
	Procedure: ignore_case
	Purpose: converts input to all lower case
	Parameters: see prototype  
	Return value: void
	Calls: strlen
		   tolower
*/
void ignore_case(char input[], char *output){
	int i, length = strlen(input);
	for (i=0; i < length; i++){
		output[i] = tolower(input[i]); // convert char to lower case
	}
	output[length] = '\0';
}
