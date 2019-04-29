#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <strings.h>

#define USAGE "usage: mynice [-num] command\n"

int main(int argc, char *argv[])
{
	int incr, cmdarg;
	char *cmdname, *cmdpath;
	
	if (argc < 2) {
		fprintf(stderr, USAGE);
		exit(EXIT_FAILURE);
	}
	if (argv[1][0] == '-') {
		incr = atoi(&argv[1][1]);
		cmdarg = 2;
	}
	else {
		incr = 10;
		cmdarg = 1;
	}
	if (cmdarg >= argc) {
		fprintf(stderr, USAGE);
		exit(EXIT_FAILURE);
	}
   
	(void)nice(incr);
	cmdname = strchr(argv[cmdarg], '/');
	if (cmdname == NULL)
		cmdname = argv[cmdarg];
	else
		cmdname++;
	cmdpath = argv[cmdarg];
	argv[cmdarg] = cmdname;
	execvp(cmdpath, &argv[cmdarg]);
	exit(EXIT_FAILURE);
}
