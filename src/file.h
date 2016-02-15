/*
*  File.h
*/

#ifndef FILE_H_
#define FILE_H_

struct content {
		FILE * fin;
		FILE * fout;
		long int size;
};

void initFiles(struct content * con)
{
	con->fin = NULL;
	con->fout = NULL;
	con->size = 0;
}

void openFile(char * fileName, struct content * con)
{
	con->fin = fopen(fileName, "r");

}

void renameFile(char * fileName)
{
	int size = 0;
	while(fileName[--size] != '.')
	{
		fileName[size] == '/0';
	}
	strcat(fileName, "wi");
}

#endif /* FILE_H_ */
