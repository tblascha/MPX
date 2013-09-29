/***********************************************
	MPX: The MultiProgramming eXecutive
	Start Program
	
	Authors: Dakota Kirby
			 Corey Hartley
			 Thomas Blaschak
			 Wisam Al-Malack

	File Name: ERROR.C
	
	Purpose: Handles errors and displaying the
			 messages to the terminal window
	
***********************************************/

#include <string.h>
#include "mpx_supt.h"
#include "config.h"
#include "error.h"

void error_handle(int error_no){
	if(error_no == CMD_NOT_FOUND){
		char message[] = "Command was not found\n";
		int size = strlen(message);
		sys_req(WRITE,TERMINAL,message,&size);
	}
	else if(error_no == CMD_NOT_FOUND){
		char message[] = "Command was not found\n";
		int size = strlen(message);
		sys_req(WRITE,TERMINAL,message,&size);
	}
	else if(error_no == CMD_NOT_FOUND){
		char message[] = "Command was not found\n";
		int size = strlen(message);
		sys_req(WRITE,TERMINAL,message,&size);
	}
	else if(error_no == CMD_NOT_FOUND){
		char message[] = "Command was not found\n";
		int size = strlen(message);
		sys_req(WRITE,TERMINAL,message,&size);
	}
	else if(error_no == CMD_NOT_FOUND){
		char message[] = "Command was not found\n";
		int size = strlen(message);
		sys_req(WRITE,TERMINAL,message,&size);
	}
	else if(error_no == CMD_NOT_FOUND){
		char message[] = "Command was not found\n";
		int size = strlen(message);
		sys_req(WRITE,TERMINAL,message,&size);
	}
	else if(error_no == CMD_NOT_FOUND){
		char message[] = "Command was not found\n";
		int size = strlen(message);
		sys_req(WRITE,TERMINAL,message,&size);
	}
	else if(error_no == CMD_NOT_FOUND){
		char message[] = "Command was not found\n";
		int size = strlen(message);
		sys_req(WRITE,TERMINAL,message,&size);
	}
	else if(error_no == CMD_NOT_FOUND){
		char message[] = "Command was not found\n";
		int size = strlen(message);
		sys_req(WRITE,TERMINAL,message,&size);
	}
	else if(error_no == CMD_NOT_FOUND){
		char message[] = "Command was not found\n";
		int size = strlen(message);
		sys_req(WRITE,TERMINAL,message,&size);
	}
	else if(error_no == CMD_NOT_FOUND){
		char message[] = "Command was not found\n";
		int size = strlen(message);
		sys_req(WRITE,TERMINAL,message,&size);
	}
	else if(error_no == CMD_NOT_FOUND){
		char message[] = "Command was not found\n";
		int size = strlen(message);
		sys_req(WRITE,TERMINAL,message,&size);
	}
}