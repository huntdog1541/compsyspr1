/*
 * translate.h
 *
 *  Created on: Feb 13, 2016
 *      Author: David
 */
#include <stdlib.h>
#include <stdio.h>

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

void initTable();

void intitDNAcontent(struct DNAcontent * order);

void destroyDNAcontent(struct DNAcontent * order);

void printTable();

int getRandomNumber();

void setDNAorder(struct DNAcontent * order);

void setDNAset(int r, struct DNAset * order);

int setLetter(int number, char letter, struct DNAset * order);

void printFirstCharacter(struct DNAcontent * order);



#endif /* TRANSLATE_H_ */
