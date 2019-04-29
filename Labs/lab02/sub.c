/**
* Name: Adam Capdeville
* Lab/task: Lab 2
* Date: 02/04/2019
**/

#include "sub.h"
#include <string.h> // > > 
#include <stdio.h> // can add to sub.h
#include <stdlib.h> // can add to sub.h ....later..
#include <string.h>

#define BUFFSIZE 100

// command input: (may be in any order)
//      sub --a -+x -i src.txt -o dest.txt
// argv   0   1   2  3       4  5        6 
// argc:7

int main(int argc, char** argv){

	FILE* fptr00;
	FILE* fptr01;	

	char* inputFile;
	char* outputFile;

	int inputFlag=0;
	int outputFlag=0;

	char* removeChar;
	char* replaceChar;

	

	if( argv[1][0] == '-' && argv[1][1] == 'h' && argv[1][2] == '\0' ){
	fptr00 = fopen("help.txt", "r");
	int c;	 
	
	while(1){
	c = fgetc(fptr00);
	  if( feof(fptr00) ){
		break;
	  }
	  printf("%c", c);
	}
	fclose(fptr00);
	exit(0);
        }


	for(int i=1; i<argc; i++){
		if( argv[i][0] == '-' ){ // then this must be either -- or -+ or -i or -o
			switch(argv[i][1]){
				case '-': //next char/s is what we want to remove
					removeChar = malloc(sizeof(strlen(argv[i])));
					removeChar = argv[i];
					memmove(removeChar, removeChar+2, strlen(argv[i]));
					break;
				case '+': //replace with:
					replaceChar = malloc(sizeof(strlen(argv[i])));
					replaceChar = argv[i];
					memmove(replaceChar, replaceChar+2, strlen(argv[i]));
					break;
				case 'i': //input file
					inputFlag = 1;
					inputFile = argv[i+1];
					i++;
					break;
				case 'o': //output file
					outputFlag = 1;
					outputFile = argv[i+1];
					i++;
					break;
				default:
					printf("ERROR, argument syntax not valid: %d \n", i);
					exit(0);
			}
		}else {
		printf("ERROR, initial argument invalid: %d \n", i);
		}
	}
	
	char *rmlist = (char *) malloc(strlen(removeChar)+1);
	for(int i = 0; i < strlen(replaceChar); i++){
	rmlist[i] = ' ';
	}
		
	rmlist[strlen(replaceChar)+1] = '\0';

	int pos = 0;	
	for(int index = 0; index<strlen(removeChar) ; index++){
	//     	printf("looking for: %c \n", removeChar[index]);

		if(strchr(rmlist, removeChar[index]) == NULL){
		 rmlist[pos] = removeChar[index];
		 pos++;

	 //	 printf("adding :%c \n",removeChar[index]);
		}
	} 

// example:
//  --aaab
//  -+xy
//  output:
//  a>x
//  b>y
//
// example:
// --aaabbbaa
// -+xy
// ouput:
// a>x
// b>y
//
// hint:
// look up>
// strchr

char* input = malloc(BUFFSIZE);
char ch;

	if(inputFlag == 1){
		fptr00 = fopen(inputFile, "r");	
		if( fptr00 == NULL ){
		printf("Can not open file: %s \n", inputFile);
		exit(0);
		}

	}else{
	printf("Enter input that you want altered. Once done press 'Ctrl-D' \n");

		for(int i =0; ((ch = getchar()) != EOF) ; ++i){
			if( input[i] == '\0'){
				char* temp = (char*) malloc(strlen(input) * 2 + 1);
				strcpy(temp, input);
				free(input);
				input = temp;
			}
			input[i] = ch;
		}		
	}


	if(outputFlag == 1){
		fptr01 = fopen(outputFile, "w");
		if( fptr01 == NULL ){
		printf("can not open file: %s \n", outputFile);
		exit(0);
		}

	for(int index = 0; index < strlen(input); index++){
			for(int pos = 0; pos < strlen(rmlist); pos++){
				if( rmlist[pos] == input[index] ){
					input[index] = replaceChar[pos];
				}
			}
		}
	char max[1000];
	while( fgets(max,1000, fptr00) != NULL ){
	
	for(int index = 0; index < strlen(max); index++){
			for(int pos = 0; pos < strlen(rmlist); pos++){
				if( rmlist[pos] == max[index] ){
					max[index] = replaceChar[pos]; 
				}
			}
		}

		fprintf(fptr01,"%s",max);
	}
		

	}else{
		for(int index = 0; index < strlen(input); index++){
			for(int pos = 0; pos < strlen(rmlist); pos++){
				if( rmlist[pos] == input[index] ){
					input[index] = replaceChar[pos]; // since replaceChar after len of rmlist is ignored
				}
			}
		}
	}

printf("\n %s \n",input);

	fclose(fptr00);
	fclose(fptr01);
	
	return 0;
	}
