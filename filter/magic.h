#ifndef __MAGIC_H__
#define __MAGIC_H__


//data structures
typedef struct data_s{
	double noc_time;
	double linux_time;
	struct data_s *next;
} data_t;

typedef struct progs_s{
	char name[50];
	int lines;
	struct data_s *times, *last;
	struct progs_s *next;
} prog_t;


//functions
double readLinuxTime(char *lins);
void add_time(char *name);
void clear_times();
void print_times();
void writeTable(char *outname);
void writeCell(FILE *out);

#endif