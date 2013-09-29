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
		page

***********************************************/

// Program Includes
#include "config.h"
#include "mpx_supt.h"
#include "comhan.h"
#include "pcb.h"
#include "help.h"
#include "error.h"

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
		else if(strcmp(command,"sprio")==0){ // set priority
			set_priority(rem_buffer);
		}
		else if(strcmp(command,"resum")==0){ // resume process
			resume_pcb(rem_buffer);
		}
		else if(strcmp(command,"block")==0){ // block process
			block_pcb(rem_buffer);
		}
		else if(strcmp(command,"cpcb")==0){ // create PCB
			create_pcb(rem_buffer);
		}
		else if(strcmp(command,"dpcb")==0){ // delete PCB
			delete_pcb(rem_buffer);
		}
		else if(strcmp(command,"sall")==0){ // show all
			show_all();
		}
		else if(strcmp(command,"sblock")==0){ // show blocked
			show_blocked();
		}
		else if(strcmp(command,"sready")==0){ // show ready
			show_ready();
		}
		else if(strcmp(command,"suspd")==0){ // suspend process
			suspend_pcb(rem_buffer);
		}
		else if(strcmp(command,"ublock")==0){ // unblock process
			unblock_pcb(rem_buffer);
		}
		else if(strcmp(command,"spcb")==0){ // show PCB
			show_pcb(rem_buffer);
		}
		else if(strcmp(command,"null")==0){
			continue;
		}
		else { // command not found
			error_handle(CMD_NOT_FOUND);
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
		char header[] = "File Name\tSize(Bytes)\n";
		char directory[255];
		int header_size = sizeof(header)-1;
		int i=0,j=0,count =0;

		// get directory from input
		if(input != NULL && input[0] != '\n'&& input[0] !='\0'){
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
			error_handle(ERR_SUP_INVDIR);
		}
		else if(err == ERR_SUP_DIROPN){
			error_handle(ERR_SUP_DIROPN);
		}
		else if(err != OK){
			error_handle(ERROR);
		}
		// if directory opened display header
		if(err == OK){
			sys_req(WRITE,TERMINAL,header, &header_size);
		}
		// if directory opened try to find first record
		while(1 && err == OK){
			// initialize buffers for entries
			char buffer[255];
			char size[255];
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
			count++;
			if (count % 10 == 0){
				page();
			}
		}
		// try to close the directory
		err = sys_close_dir();
		// if fail display message
		if(err == ERR_SUP_DIRCLS){
			error_handle(ERR_SUP_DIRCLS);
		}
		else if (err != OK){
			error_handle(ERROR);
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
	char version_message[] = "MPX Version 2.0 - Last Modified On 10/4/2013\n";
	int version_size = strlen(version_message);
	sys_req(WRITE,TERMINAL, version_message, &version_size);
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
