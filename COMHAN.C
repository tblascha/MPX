/***********************************************
	MPX: The MultiProgramming eXecutive
	Command Handler Program
	
	Authors: Dakota Kirby
			 Corey Hartley
			 Thomas Blaschak
			 Wisam Al-Malack

	File Name: COMHAN.C
	
	Purpose: Handles commands input at the terminal
	
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

// Program Includes
#include <stdlib.h>
#include <string.h>
#include "mpx_supt.h"
#include "comhan.h"

/*
	Procedure: comhan
	Purpose: handle commands input at the terminal
	Parameters: see prototype  
	Return value: void
	Calls: sys_req
		   ignore_case
		   strcmp
		   sizeof
		   closing
*/
void comhan(void){
	// initialize
	int done = FALSE;
	char opening_message[17] = "Welcome to MPX\n\n ";
	int opening_size = sizeof(opening_message) - 1;
	char closing_message[24] = "\nThanks for using MPX\n";
	int closing_size = sizeof(closing_message);
	char prompt[2] = "$ ";
	int prompt_size = sizeof(prompt);
	char input_buffer[255] = "";
	int input_buffer_size = 255;
	char temp[255];
	char command[255];
	char rem_buffer[255] = "";
	int i, j,skip;

	// display opening message
	sys_req(WRITE, TERMINAL, opening_message, &opening_size);

	// while not done
	while(!done){
		prompt_size = sizeof(prompt);
		sys_req(WRITE, TERMINAL, prompt, &prompt_size);
		input_buffer_size = 255;
		sys_req(READ, TERMINAL, input_buffer, &input_buffer_size); // read line in
		i=0;
		j=0;
		skip = FALSE;

		// see if blank input
		if (input_buffer[0] == '\n'){
			temp[0] = 'n';
			temp[1] = 'u';
			temp[2] = 'l';
			temp[3] = 'l';
			skip = TRUE;
			i=4;
		}
		// get command from input
		while(input_buffer[i] != ' ' && input_buffer[i] != '\n'&& !skip){
			temp[i] = input_buffer[i];
			i++;
		}
		temp[i] = '\0';
		ignore_case(temp,&command); // convert to lower case
		i++;

		while(i < sizeof(rem_buffer)){ // put rest in another buffer
			rem_buffer[j] = input_buffer[i];
			i++;
			j++;
		}
		rem_buffer[j] = '\0';
		if(strcmp(command,"ver")==0){ // version command
			disp_version();
		}
		else if(strcmp(command,"dir")==0){ // directory command
			look_dir(rem_buffer);
		}
		else if(strcmp(command,"exit")==0){ // exit command
			done=comhan_exit();
		}
		else if(strcmp(command,"help")==0){ // help command
			help(rem_buffer);
		}
		else if(strcmp(command,"ddate")==0){ // display date
			disp_date();
		}
		else if(strcmp(command,"sdate")==0){ // set date
			set_date(rem_buffer);
		}
		else if(strcmp(command,"null")==0){
			continue;
		}
		else { // command not found
			char message[] = "Command not found\n";
			int size = sizeof(message)-1;
			sys_req(WRITE,TERMINAL,message, &size);
		}

	}
	// show closing message
	sys_req(WRITE,TERMINAL, closing_message, &closing_size);

	// cleanup
	closing();

	// return to host system
	return;
}

/*
	Procedure: comhan_exit
	Purpose: confirms exit of comhan
	Parameters: see prototype
	Return value: 1 for conitnue with exit, 0 for halt exit
	Calls: sys_req
		   ignore_case
		   strcmp
		   sizeof
*/
int comhan_exit(void){
	// initialize
	int exit_status = FALSE;
	while(1){
		char exit_message[] = "Are you sure you want to terminate MPX? (y/n)";
		int exit_size = sizeof(exit_message);
		char temp[255];
		char temp2[255];
		char confirm[255];
		int temp_size,i=0,skip;

		// get confirmation of exit from user
		sys_req(WRITE, TERMINAL, exit_message, &exit_size);
		temp_size = sizeof(temp);
		sys_req(READ, TERMINAL, temp, &temp_size);
		skip = FALSE;
		// get y/n from input from user
		if (temp[0] == '\n'){
			temp[0] = 'n';
			skip = TRUE;
			i++;
		}
		while(temp[i] != ' ' && temp[i] != '\n' && !skip){
			temp2[i] = temp[i];
			i++;
		}

		temp2[i] = '\0';
		ignore_case(temp2, &confirm);

		if (strcmp(confirm,"y")==0){ // exit confirmed
			exit_status = TRUE;
			break;
		}
		else if(strcmp(confirm,"n")==0) { // exit cancelled
			exit_status = FALSE;
			break;
		}
		else{
			continue;
		}
	}
	return exit_status;
}

/*
	Procedure: disp_date
	Purpose: displays the current system date
	Parameters: see prototype
	Return value: void
	Calls: sys_get_date
		   sizeof
		   sys_req

*/
void disp_date(){

	//  initialize
	date_rec new_date;
	char out[11];
	int size = sizeof(out);
	int year;

	sys_get_date(&new_date); // get date

	// convert month to char
	if(new_date.month<10){
		out[0] = '0';
		out[1] = (char)(new_date.month+48);
	}else{
		out[0] = '1';
		out[1] = (char)(new_date.month+48-10);
	}

	out[2] = '/';

	// convert day to char
	if(new_date.day>=30){
		out[3] = '3';
		out[4] = (char)(new_date.day - 30 + 48);
	}else if(new_date.day>=20){
		out[3] = '2';
		out[4] = (char)(new_date.day - 20 + 48);
	}else if(new_date.day>=10){
		out[3] = '1';
		out[4] = (char)(new_date.day - 10 + 48);
	}else{
		out[3] = '0';
		out[4] = (char)(new_date.day + 48);
	}

	out[5] = '/';

	// convert year to char
	year = new_date.year;

	while(year > 10){
		int thousands = 0;
		int hundreds = 0;
		int tens = 0;
		while (year>=1000){
			year = year-1000;
			thousands++;
		}
		out[6] = (char)(thousands + 48);

		while (year>=100){
			year = year-100;
			hundreds++;
		}
		out[7] = (char)(hundreds + 48);

		while (year>=10){
			year = year-10;
			tens++;
		}
		out[8] = (char)(tens + 48);
		out[9] = (char)(year + 48);
	}

	out[10] = '\n';

	sys_req(WRITE, TERMINAL, out, &size);

}

/*
	Procedure: set_date
	Purpose: sets the system date
	Parameters: see prototype
	Return value: void
	Calls: stringToDate
		   strlen
		   sizeof
		   sys_req
		   sys_get_date
*/
void set_date(char date[]){

	// initialize
    date_rec replace_date;
    int err;
    char new_date[255];
    int i = 0;

	// get date string out of buffer in
    while(date[i]!=NULL && date[i]!='\n'){
	new_date[i] = date[i];
	i++;
    }

    new_date[i] = '\0'; // add null terminator

	// check to make sure date has right number of inputs
    if(strlen(new_date) != 10){
		char message[] = "Date isn't valid, check size\n";
		int size = sizeof(message)-1;
		sys_req(WRITE,TERMINAL,message,&size);
    }
    else{ // continue with date conversion
		if(stringToDate(&replace_date, new_date)!= 0){ // invalid date
			char message[] = "Date isn't valid, check values\n";
			int size = sizeof(message)-1;
			sys_req(WRITE,TERMINAL,message,&size);
		}
		else{
			err = sys_set_date(&replace_date); // set date
			if(err == OK){ // successful set date
				char message [] = "Date was changed succesfully\n";
				int size = sizeof(message)-1;
				sys_req(WRITE,TERMINAL,message,&size);
			}else{ // unsuccessful set date
				char message [] = "There was an error changing the date\n";
				int size = sizeof(message)-1;
				sys_req(WRITE,TERMINAL,message,&size);
			}
		}
    }
}

/*
	Procedure: stringToDate
	Purpose: converts date string to date type
	Parameters: see prototype
	Return value: 0 for correct data entered, 1 if not
	Calls: strtok
		   atoi
*/
int stringToDate(date_rec *newDate, char date[]) {
	// initialize
    char *input,*month, *day, *year;
    int intYear, intDay, intMonth, correct = 0 ;

	// get values in string form
    month = strtok(date, "-\/");
    day = strtok(NULL, "-\/");
    year = strtok(NULL, "-\/");

	// convert to int
    intYear = atoi(year);
    intMonth = atoi (month);
    intDay = atoi (day);

    if (intYear>0){ //if valid year{
		//validate day depending upon month
		if ((intMonth == 10 || intMonth == 4 || intMonth == 6 || intMonth== 11) && (intDay>=1 && intDay<=30)){ //if mth w/ 30 days
			//printf("valid month and days of 30");}
			correct=1;
		}

		// if febuary
		else if (intMonth == 2){
			//test for leap year
			if((intYear % 4 == 0 && intYear % 100 != 0)|| intYear % 400 == 0){ //leap year
				if(intDay>=1 && intDay<=29){ //date within leap year
					//valid day for leap year
					correct=1;
				}
			} //end leap year
			else {	//if not leap year
				if(intDay>=1 && intDay<=28){
					correct=1; //valid day for not leap year
				}
				else {
				}
			}
		}
		else if ((intMonth >=1 && intMonth<=12)&& (intDay>=1 && intDay<=31)){ //if month with 31 days
			correct=1;
		}
	}

	// date is legal set date values
	if(correct){
	    newDate->day = intDay;
	    newDate->month = intMonth;
	    newDate->year = intYear;
	    return 0;
	}
	return 1;

}

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
		else if(strcmp(temp,"ddate")==0){ // help for dsiplay date
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
		char sdate [] = "sdate mm/dd/yyyy - Sets the system date\n";
		char ddate[] = "ddate - Dsiplays the current system date\n";
		char vers[] = "ver - Displays the current version of MPX\n";
		char dir[] = "dir path - Display all files in path\n";
		char exit[] = "exit - Terminates MPX\n";

		int size_sdate = sizeof(sdate)-1;
		int size_ddate = sizeof(ddate)-1;
		int size_vers = sizeof(vers)-1;
		int size_dir = sizeof(dir)-1;
		int size_exit = sizeof(exit)-1;

		sys_req(WRITE,TERMINAL,sdate,&size_sdate);
		sys_req(WRITE,TERMINAL,ddate,&size_ddate);
		sys_req(WRITE,TERMINAL,vers,&size_vers);
		sys_req(WRITE,TERMINAL,dir,&size_dir);
		sys_req(WRITE,TERMINAL,exit,&size_exit);
	}

}

/*
	Procedure: look_dir
	Purpose: displays mpx files in directory defualt is current directory
	Parameters: see prototype
	Return value: void
	Calls: sys_req
		   sys_alloc_mem
		   sys_open_dir
		   sys_get_entry
		   sys_close_dir
		   sys_free_mem
		   sizeof
		   strcpy
		   strcat
		   sprintf
*/
void look_dir(char input[]){
		// initialize
		int err;

		char invdir[] = "Invalid directory\n";
		char diropn[] = "Error opening directory\n";
		char dircls[] = "Error closing directory\n";
		char other[] = "An unknown error occurred\n";
		char header[] = "File Name\tSize(Bytes)\n";
		char directory[255];

		int invdir_size = sizeof(invdir)-1;
		int diropn_size = sizeof(diropn)-1;
		int dircls_size = sizeof(dircls)-1;
		int other_size = sizeof(other)-1;
		int header_size = sizeof(header)-1;
		int i=0,j=0;

		// get directory from input
		if(input != NULL && input != "\n"){
			while(input[j] != '\n'){
				directory[j] = input[j];
				j++;
			}
			directory[j] = '\0';
			err = sys_open_dir(directory);
		}
		else{
			err = sys_open_dir(NULL);
		}

		// if fail display error messages
		if (err == ERR_SUP_INVDIR){
			sys_req(WRITE,TERMINAL,invdir,&invdir_size);
		}
		else if(err == ERR_SUP_DIROPN){
			sys_req(WRITE,TERMINAL,diropn,&diropn_size);
		}
		else if(err != OK){
			sys_req(WRITE,TERMINAL,other,&other_size);
		}
		// if directory opened display header
		if(err == OK){
			sys_req(WRITE,TERMINAL,header, &header_size);
		}
		// if directory opened try to find first record
		while(1 && err == OK){
			// initialize buffers for entries
			char buffer[20];
			char size[10];
			char output[30]="";

			int buf_size = sizeof(buffer);
			int output_size = sizeof(output);
			long file_size;
			// try to read the next .mpx file
			err = sys_get_entry(buffer,buf_size,&file_size);
			// if not entries the then break the loop and return
			if (err == ERR_SUP_NOENTR){
				break;
			}
			// Form output string for display
			strcpy(output,buffer);
			strcat(output,"\t\t  ");
			sprintf(size,"%d",file_size);
			strcat(output,size);
			output[29] = '\n';
			// Wirte output to the screen
			sys_req(WRITE,TERMINAL,output,&output_size);
		}
		// try to close the directory
		err = sys_close_dir();
		// if fail display message
		if(err == ERR_SUP_DIRCLS){
			sys_req(WRITE,TERMINAL,dircls,&dircls_size);
		}
		else if (err != OK){
			sys_req(WRITE,TERMINAL,other,&other_size);
		}
		sys_free_mem(directory);

}

/*
	Procedure: disp_version
	Purpose: displays the current system version
	Parameters: see prototype  
	Return value: void
	Calls: sys_req
		   sizeof
*/
void disp_version(void){
	char version_message[39] = "MPX Version 1.0 Last Modified 9/9/2013\n";
	int version_size = sizeof(version_message);
	sys_req(WRITE,TERMINAL, version_message, &version_size);
	// version message error handling
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
