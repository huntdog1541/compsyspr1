/*
 * translate.c
 *
 *  Created on: Feb 13, 2016
 *      Author: David
 */

#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include "translate.h"
#include "file.h"

void initTable()
{
	int i, j, k, num = 30;
	for(i = 0; i < 4; i++)
	{
		for(j = 0; j < 4; j++)
		{
			for(k = 0; k < 4; k++)
			{
				table[i][j][k] = num;
				num++;
			}
		}
	}
	table[0][0][0] = 0;
	table[0][0][1] = 1;
	srand(time(NULL));
}

void printTable()
{
	int i, j, k;
		for(i = 0; i < 4; i++)
		{
			for(j = 0; j < 4; j++)
			{
				for(k = 0; k < 4; k++)
				{
					printf("%d: %d: %d:: %d\n", i, j, k, table[i][j][k]);
				}
			}
		}
}

/* int getRandomNumber - gets a random number from the rand function, note* will try to implement Mersenne Twist
*  return - returns a random number
*/
int getRandomNumber()
{
	  int r = rand()%4;
	  printf("random number is %d\n", r);
	  return r;
}

void intitDNAcontent(struct DNAcontent * order)
{
	order->firstOrder = (struct DNAset *)malloc(sizeof(struct DNAset));
	order->secondOrder = (struct DNAset *)malloc(sizeof(struct DNAset));
	order->thirdOrder = (struct DNAset *)malloc(sizeof(struct DNAset));
}

void destroyDNAcontent(struct DNAcontent * order)
{
	free(order->firstOrder);
	free(order->secondOrder);
	free(order->thirdOrder);
}

void setDNAorder(struct DNAcontent * order)
{
	int r = getRandomNumber();
	setDNAset(r, order->firstOrder);
	r = getRandomNumber();
	setDNAset(r, order->secondOrder);
	r = getRandomNumber();
	setDNAset(r, order->thirdOrder);
}

void setDNAset(int r, struct DNAset * order)
{
	r = setLetter(r, 'A', order);
	r = setLetter(r, 'C', order);
	r = setLetter(r, 'G', order);
	r = setLetter(r, 'T', order);
}

int setLetter(int number, char letter, struct DNAset * order)
{
	switch(number)
	{
		case 0:
				order->first = letter; number++; break;
		case 1:
				order->second = letter; number++; break;
		case 2:
				order->third = letter; number++; break;
		case 3:
				order->fourth = letter; number = 0; break;
	}
	return number;
}

void printFirstCharacter(struct DNAcontent * order)
{
	/*printf("First character: %c\n", order->firstOrder->first);
	printf("Second character: %c\n", order->secondOrder->first);
	printf("Third character: %c\n", order->thirdOrder->first);*/
	printAllCharacters(order->firstOrder, "first order");
	printAllCharacters(order->secondOrder, "second order");
	printAllCharacters(order->thirdOrder, "third order");
	printf("%c;", order->firstOrder->first);
	printf("%c;", order->secondOrder->first);
	printf("%c\n", order->thirdOrder->first);
}

void printAllCharacters(struct DNAset * set, char * str)
{
	printf("Print all characters from %s\n", str);
	printf("first: %c\n", set->first);
	printf("second: %c\n", set->second);
	printf("third: %c\n", set->third);
	printf("fourth: %c\n", set->fourth);
	fflush(stdout);
}

void startTranslate(struct content * con, struct DNAcontent * order)
{
	struct DNAword wrd;
	fseek(con->fit, 0L, SEEK_SET);
	char temp = fgetc(con->fit);
	while(temp != EOF)
	{
		translateCharacter(order, con, &wrd, temp);
		temp = fgetc(con->fit);
	}
}


void translateCharacter(struct DNAcontent * order, struct content * con, struct DNAword * word, char t)
{
		char sentence[4];
		findCharacter(t, word, sentence);
		translateWord(order, word, sentence);
		sentence[3] = '\0';
		printTranslation(sentence, con);
}

void findCharacter(char t, struct DNAword * word, char * sentence)
{
	if(t == 0)
		setIntron(word);
	if(t == 1)
		setSecondChar(word);
	if((t < 93) && (t > 32))
		searchTable(t, word);
}

void translateWord(struct DNAcontent * order, struct DNAword * word, char * sentence)
{
	sentence[0] = getLetter(order->firstOrder, word->first);
	sentence[1] = getLetter(order->secondOrder, word->second);
	sentence[2] = getLetter(order->thirdOrder, word->third);
}

void printTranslation(char * sentence, struct content * con)
{
	printf("%s\n", sentence);
	fprintf(con->fout, sentence);
}

char getLetter(struct DNAset * st, int word)
{
	char answer;
	switch(word)
	{
		case 0:
				answer = st->first; break;
		case 1:
				answer = st->second; break;
		case 2:
				answer = st->third; break;
		case 3:
				answer = st->fourth; break;
	}
	return answer;
}

void searchTable(int number, struct DNAword * word)
{
		int i, j, k;
		for(i = 0; i < dnasize; i++)
		{
			for(j = 0; j < dnasize; j++)
			{
				for(k = 0; k < dnasize; k++)
				{
					if(table[i][j][k] == number)
					{
						word->first = i;
						word->second = j;
						word->third = k;
						return;
					}
				}
			}
		}
}

void setIntron(struct DNAword * word)
{
	word->first = 0;
	word->second = 0;
	word->third = 0;
}

void setSecondChar(struct DNAword * word)
{
	word->first = 0;
	word->second = 0;
	word->third = 1;
}
