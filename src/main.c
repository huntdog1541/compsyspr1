#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "translate.h"
#include "file.h"


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
	struct content con;
	char str[256];
	strcpy(str, "test.txt");
	processFile(str, &con);
	initTable();
	//printTable();
	struct DNAcontent st;
	intitDNAcontent(&st);
	setDNAorder(&st);
	printFirstCharacter(&st);
	startTranslate(&con, &st);
	destroyDNAcontent(&st);
	closeFile(&con);

	return 0;
}
