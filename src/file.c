/*
*  File.c
*/

#include <stdio.h>
#include <stdlib.h>
#include "file.h"

void processFile(char * fileName)
{
  struct content con;
  initFiles(&con);
  openFile(fileName, &con);
}

void initFiles(struct content * con)
{
	con->fin = NULL;
	con->fout = NULL;
	con->size = 0;
}

void openFile(char * fileName, struct content * con)
{
	con->fin = fopen(fileName, "r");
  fileName = renameFile(fileName);
  con->fout = fopen(fileName, "w");
}

char * renameFile(char * fileName)
{
	int size = strlen(fileName);
	int t = size--;
	char temp = fileName[t];
	while(temp != '.')
	{
		fileName[t--] == '/0';
		temp = fileName[t];
	}
	printf("File name is %s\n", fileName);
	//strcat(fileName, "wi");
	return fileName;
}
