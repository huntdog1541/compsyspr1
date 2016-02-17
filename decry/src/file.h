/*
*  File.h
*/

#ifndef FILE_H_
#define FILE_H_

struct content {
		FILE * fin;
		FILE * fit;
		FILE * fout;
		long int size;
};

void processFile(char * fileName, struct content * con);

void initFiles(struct content * con);

void openFile(char * fileName, struct content * con);

void closeFile(struct content * con);

void renameFile(char * fileName);

void readOutFile(struct content * con);

#endif /* FILE_H_ */
