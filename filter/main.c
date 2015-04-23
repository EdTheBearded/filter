#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>
#include "magic.h"


//display debug info
#define DEBUG 1


//globals
extern data_t *now;

int main(int argc, char* argv[]){

	FILE *input = NULL, *output = NULL;
	int out_size;
	double t1, t2, t3;
	char outname[50];
	char line[100];
	
	if(argc != 2 && argc != 3){		//check usage
		printf("Usage:\n%s <input> [output]\n", argv[0]);
		exit(1);
	}
	if(argc == 2){	//if output name not specified, use standard output name
		strcpy(outname, "data.gnumeric");
	}
	else{			//output name specified
		strcpy(outname, argv[2]);
		out_size = strlen(outname);
		//check if it can (and ends) with '.gnumeric'. if not, concatenate it
		if(out_size <= 9 || (out_size > 9 && (strcmp(&outname[out_size - 9], ".gnumeric") != 0)) ){
			strcat(outname, ".gnumeric");
		}
	}

	input = fopen(argv[1], "r");	//open input file
	if(input == NULL){
		printf("cant open file '%s': %s\n", argv[1], strerror(errno));
		exit(2);
	}

	while(fgets(line, 100, input) != NULL){
		if(!strncmp(line, "[term1]    BEGIN DATA", 21)){							//find enclosed data to be filtered
			while(fgets(line, 100, input) != NULL){
				if(!strncmp(line, "[term1]    END DATA", 19)){						//find end of data space and go back
					break;															//to outside loop to check for more data regions
				}
				else if(strncmp(line, "[term1]    *", 12) == 0){					//found implementation name
					line[strlen(line) - 1] = '\0';									//deletes ending '\n'
					add_time(&line[12]);											//a way to avoid first character '*'
				}
				else if(strncmp(line, "[term1]    time", 15) == 0){					//found noc printed time
					sscanf(line, "[term1]    time %lf", &t1);
					now->noc_time = t1/1000000;										//divide it to be read in seconds
				}
				else if(strncmp(line, "[term1]    real", 15) == 0){					//found time printed by linux
					now->linux_time = readLinuxTime(line);							//convert to seconds
				}
				else{
					continue;														//to be disconsidered
				}
			}
		}
	}

//prints the info stored in the lists for debugging
#	ifdef DEBUG
	print_times();
#	endif

	writeTable(outname);
	
	fclose(input);	//close input file
	clear_times();	//free allocated data structure

	return 0;
}
