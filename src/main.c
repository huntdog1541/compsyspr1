#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "translate.h"


int main(int argc, char ** argv)
{
	printf("Hello World!\n");
	if(argc == 2)
	{
		printf("File name %s\n", argv[1]);

	}
	else
	{

	}
	initTable();
	//printTable();
	struct DNAcontent con;
	intitDNAcontent(&con);
	setDNAorder(&con);
	printFirstCharacter(&con);
	destroyDNAcontent(&con);
	return 0;
}
