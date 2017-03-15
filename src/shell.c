#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <signal.h>
#include "shell.h"

//function to handle ctrl+c
static void handleCtrlC(int sig) {
	signal(SIGINT, handleCtrlC);
	printf("\n");
	printCurrentTime();
	printf(" # ");
	fflush(stdout);
}

//function to parse the input string when the user includes the '>' character
output parseInput(char * input){
	//struct to store and return data
	output o;

	int c=0;
	int i=0;

	char **output = malloc(sizeof(char*));

	//split input if '>' is present
	char * temp = strtok(input, ">");
	while(temp != NULL){
		output[c]=temp;
		c++;
		output=realloc(output, (c+1)*sizeof(char*));
		temp=strtok(NULL, "/0");
	}

	output[c]=NULL;
	
	//store command name in phrase field in struct
	o.phrase=(char*)malloc(strlen(output[0]));
	strcpy(o.phrase,output[0]);
	
	//store output file name in filename field of struct
	o.filename=(char*)malloc(strlen(output[1]));
	strcpy(o.filename,output[1]);

	//return struct
	return o;
}

//function to print current time
void printCurrentTime(){
	time_t currenttime;
	time(&currenttime);

	struct tm *data;
	char timestring[50];
	
	data = localtime(&currenttime);
	
	//assign time to string timestring with format dd/mm hh:mm
	strftime(timestring, 50,"%d/%m %H:%M", data);

	//print out contents of timestring
	printf("[%s]", timestring);
}

//Name: Francis Lawlor
//Student Number: 14461158
//Email: francis.lawlor@ucdconnect.ie


