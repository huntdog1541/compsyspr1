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

void processFile(char * fileName);

void initFiles(struct content * con);

void openFile(char * fileName, struct content * con);

char * renameFile(char * fileName);

#endif /* FILE_H_ */
