#include <time.h>
#include <stdlib.h>
#include <stdio.h>
#include <ctype.h>
#include <string.h>
#include "magic.h"
#include "template.h"


//locals
prog_t *measures = NULL;
data_t *now = NULL;
int total_rows = -1;
int total_cols = -1;


/**
 *Reads the output of linux time command, and returns its time value in seconds.
 */
double readLinuxTime(char *line){
	
	double time = 0.0;
	double t;
	char c, s[50];
	int i;

	line = &line[16];								//eats up the meaningless chars

	while(1){
		i = 0;				
		while(isdigit(line[0]) || line[0] == '.'){	//keep scanning for double value
			s[i++] = line[0];
			line++;
		}
		s[i] = '\0';
		t = atof(s);								//string to double
		c = line[0];
		switch(c){									//correct time to seconds
			case 'h':
				time += 3600*t;
				break;
			
			case 'm':
				time += 60*t;
				break;
			
			case 's':
				time += t;
				break;

			default:								//in case of some unexpected time unit
				printf("error: unrecognized character %c on line '%s'\n", c, line);
				exit(1);
		}
		line++;
		if(line[0] == ' ')							//eats meaningless space
			line++;
		if(line[0] == '\0' || line[0] == '\n')		//check for end of string
			break;
	}


	return time;
}

/**
 *Create a new program entry or find its entry, allocates a new data storage and updates
 *the now pointer to the current working data structure, for reading the times.
 */
void add_time(char *name){

	prog_t *aux;

	if(measures == NULL){											//first entry
		measures = (prog_t*)malloc(sizeof(prog_t));
		strcpy(measures->name, name);								//setting name
		measures->next = NULL;
		measures->times = (data_t*)malloc(sizeof(data_t));
		measures->last = measures->times;							//updates last pointer to last entry
		now = measures->times;										//updates now pointer to current data to be updated
		now->next = NULL;
		measures->lines = 0;
		total_rows = 0;
		total_cols = 0;
	}
	else{															//not first entry
		for(aux = measures; aux->next != NULL; aux = aux->next){	//search for specified name
			if(strcmp(aux->name, name) == 0) break;
		}
		if(strcmp(aux->name, name) == 0){							//name was found
			now = aux->last;
			now->next = (data_t*)malloc(sizeof(data_t));			//new data entry
			now = now->next;										//updates now pointer to last entry
			now->next = NULL;
			aux->last = now;										//updates last pointer to last entry
			aux->lines++;
			//if(aux->lines > total_rows) total_rows = aux->lines;
			if(aux->lines > total_cols) total_cols = aux->lines;
		}
		else{														//name was not found
			aux->next = (prog_t*)malloc(sizeof(prog_t));
			aux = aux->next;										//new program entry
			strcpy(aux->name, name);								//setting name
			aux->next = NULL;
			aux->times = (data_t*)malloc(sizeof(data_t));			//new data entry
			aux->last = aux->times;									//updates last pointer to last entry
			now = aux->times;										//updates now pointer to last entry
			now->next = NULL;
			aux->lines = 0;
			//total_cols++;
			total_rows++;
		}
	}

	//initialize the time to 0.0 s, to avoid cases where one of the times weren't found
	now->linux_time = -1.0;
	now->noc_time = -1.0;
}

/**
 *Run over the data structures and clears it all
 */
void clear_times(){

	prog_t *i, *i_aux;
	data_t *j, *j_aux;

	i = measures;
	while(i != NULL){		//outer loop, runs over the programs
		i_aux = i;
		j = i->times;
		while(j != NULL){	//inner loop, runs over the data of a given program
			j_aux = j;
			j = j->next;	//updates base data pointer
			free(j_aux);	//free current data structure
		}
		i = i->next;		//updates base program pointer
		free(i_aux);		//free current program structure
	}
}

/**
 *Run over the data structures printing its times
 */
void print_times(){

	prog_t *i;
	data_t *j;

	for(i = measures; i != NULL; i = i->next){					//outer loop, runs over the programs
		printf("## %s - %d lines ##\n", i->name, i->lines);		//print program ID
		for(j = i->times; j != NULL; j = j->next){				//inner loop, runs over the data of a given program
			//prints the current data stored values.
			if(j->linux_time > -1.0)printf("linux \t%.2lf s\n", j->linux_time);
			if(j->noc_time > -1.0)printf("noc \t%.2lf s\n", j->noc_time);
			printf("###################\n");
		}
	}
	printf("maxRow: %d\nmaxCol: %d\n", total_rows, total_cols);
}

void writeTable(char *outname){

	FILE *outfile = NULL;
	time_t t;
	struct tm tm;

	outfile = fopen(outname, "w");
	if(outfile == NULL){
		printf("cant open file '%s': %s\n", outname, strerror(errno));
		exit(3);
	}

	fprintf(outfile, header);
	t = time(NULL);
	tm = *localtime(&t);
	fprintf(outfile, date, tm.tm_year + 1900, tm.tm_mon + 1, tm.tm_mday, tm.tm_hour, tm.tm_min, tm.tm_sec,
			tm.tm_year + 1900, tm.tm_mon + 1, tm.tm_mday, tm.tm_hour, tm.tm_min, tm.tm_sec);
	fprintf(outfile, end_header);
	//numero de linhas soma um pois a primeira linha conta a medida
	//numero de colunas soma 2 pois a primeira coluna eh o nome do programa, e a ultima a sua media
	fprintf(outfile, sheet_dim, total_cols+2, total_rows+1);
	fprintf(outfile, sheet_info);
	fprintf(outfile, "      <gnm:Cells>\n");
	writeCell(outfile);
	fprintf(outfile, "      </gnm:Cells>\n");
	fprintf(outfile, sheet_end);
}

void writeCell(FILE *out){

	prog_t *i;
	data_t *j;
	int k;
	int row = 0;
	int col = 0;

	for(k = 1; k < total_cols+2; k++){
		fprintf(out, "        <gnm:Cell Row=\"0\" Col=\"%d\" ValueType=\"60\">#%d</gnm:Cell>\n",
				k, k);
	}
	fprintf(out, "        <gnm:Cell Row=\"0\" Col=\"%d\" ValueType=\"60\">media</gnm:Cell>\n",
				total_cols+2);
	row++;

	for(i = measures; i != NULL; i = i->next, row++){				//outer loop, runs over the programs
		fprintf(out, "        <gnm:Cell Row=\"%d\" Col=\"%d\" ValueType=\"60\">%s</gnm:Cell>\n",
				row, col++, i->name);
		for(j = i->times, col = 1; j != NULL; j = j->next, col++){	//inner loop, runs over the data of a given program
			if(j->linux_time > -1.0){
				fprintf(out, "        <gnm:Cell Row=\"%d\" Col=\"%d\" ValueType=\"40\">%lf</gnm:Cell>\n",
						row, col, j->linux_time);
			}
			if(j->noc_time > -1.0){
				fprintf(out, "        <gnm:Cell Row=\"%d\" Col=\"%d\" ValueType=\"60\">%lf</gnm:Cell>\n",
						row, col, j->noc_time);
			}
		}
		fprintf(out, "        <gnm:Cell Row=\"%d\" Col=\"%d\">=average(%c%d:%c%d)</gnm:Cell>\n",
				row, col, 'B', row+1, 'B'+col-2, row+1);
		col = 0;
	}

}