/*
 * translate.h
 *
 *  Created on: Feb 13, 2016
 *      Author: David
 */
#include <stdlib.h>
#include <stdio.h>
#include "file.h"

#ifndef TRANSLATE_H_
#define TRANSLATE_H_

#define dnasize 4

int table[dnasize][dnasize][dnasize];

/* DNAword - stores the iterators for the item in the table
 *
 */

struct DNAword {
	int first;
	int second;
	int third;
};

/* DNAset - stores the character order for each column and row of the table
 *
 */

struct DNAset {
	char first;
	char second;
	char third;
	char fourth;
};

/* struct DNAcontent - stores the character that are translated from the placement in the loop
*	 to a particular character
*/
struct DNAcontent {
	struct DNAset * firstOrder;
	struct DNAset * secondOrder;
	struct DNAset * thirdOrder;
};

struct codon {
		char * cod;
		char ** group;
		int numberCon;
};

void initTable();

void intitDNAcontent(struct DNAcontent * order);

void destroyDNAcontent(struct DNAcontent * order);

void printTable();

int getRandomNumber();

void parseInput(struct DNAcontent * order, struct content * con, char * in);

void setDNAset(char r, struct DNAset * order);

void printFirstCharacter(struct DNAcontent * order);

void printAllCharacters(struct DNAset * set, char * str);

void translateCharacter(struct DNAcontent * order, struct content * con, struct DNAword * word, char t);

void findCharacter(char t, struct DNAword * word, char * sentence);

/* translateWord - translates a single word to a
 *
 */

void translateWord(struct DNAcontent * order, struct DNAword * word, char * sentence);

/* printTranslation - prints the translation of a single character
 *
 */
void printTranslation(char * sentence, struct content * con);

void searchTable(int number, struct DNAword * word);

char getLetter(struct DNAset * st, int word);

void setSecondChar(struct DNAword * word);

void setIntron(struct DNAword * word);

void readFromInput(struct content * con, struct DNAcontent * order, struct codon * cd);

void printCharArray(char * str, int sz);

void getCodon(char * text, struct codon * cd);

void printAllCodons(char ** group, int number);

void startDecry(struct codon * cd, struct DNAcontent * order, struct content * con);

void decrypt(char * dna, struct DNAcontent * order, struct content * con);

int getNumber(char temp, struct DNAset * set);

#endif /* TRANSLATE_H_ */
