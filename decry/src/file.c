/*
*  File.c
*/

#include <stdio.h>
#include <stdlib.h>
#include "file.h"

void processFile(char * fileName, struct content * con)
{
  initFiles(con);
  openFile(fileName, con);
}

void initFiles(struct content * con)
{
	con->fin = NULL;
	con->fit = NULL;
	con->fout = NULL;
	con->size = 0;
}

void openFile(char * fileName, struct content * con)
{
  con->fin = fopen(fileName, "r");
  renameFile(fileName);
  con->fit = fopen(fileName, "w+");
  con->fout = fopen("out.txt", "w+");
}

void closeFile(struct content * con)
{
  fclose(con->fin);
  fclose(con->fit);
  fclose(con->fout);
}

void renameFile(char * fileName)
{
	int size = strlen(fileName);
	int t = size--;
	while(fileName[t--] != '.')
	{
		fileName[t--] = '\0';
	}
	strcat(fileName, "wi");
	printf("File name is %s\n", fileName);
}

void processing(struct content * con)
{
  fseek(con->fin, 0L, SEEK_END);
  con->size = ftell(con->fin);
  fseek(con->fin, 0L, SEEK_SET);
  char temp = fgetc(con->fin);
  char second = 1;
  while(temp != EOF)
  {
    if((temp > 31) && (temp < 94))
    {
      fputc(temp, con->fit);
      //printf("%d - ", temp);
    }
    else if(temp >= 94)
    {
      fputc(second, con->fit);
      //printf("%d - ", second);
      temp = temp - 62;
      fputc(temp, con->fit);
      //printf("%d - ", temp);
    }
    temp = fgetc(con->fin);
  }
  printf("reading file\n");
  fflush(stdout);
  //readOutFile(con);
}

void readOutFile(struct content * con)
{
	fseek(con->fit, 0L, SEEK_SET);
	char temp = fgetc(con->fit);
	while(temp != EOF)
	{
		printf("%d\n", temp);
		temp = fgetc(con->fit);
	}
}

void postProcessing(struct content * con)
{
  char temp = fgetc(con->fit);
  while(temp != EOF)
  {
    if(temp == 1)
    {
      temp = fgetc(con->fit);
      temp = temp + 62;
    }
    fprintf(con->fout, "%c", temp);
    temp = fgetc(con->fit);
  }
}
