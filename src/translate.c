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
	printf("First character: %c\n", order->firstOrder->first);
	printf("Second character: %c\n", order->secondOrder->first);
	printf("Third character: %c\n", order->thirdOrder->first);
	/*printAllCharacters(order->firstOrder, "first order");
	printAllCharacters(order->secondOrder, "second order");
	printAllCharacters(order->thirdOrder, "third order");*/
}

void printAllCharacters(struct DNAset * set, char * str)
{
	printf("Print all characters from %s\n", str);
	printf("first: %c\n", set->first);
	printf("second: %c\n", set->second);
	printf("third: %c\n", set->third);
	printf("fourth: %c\n", set->fourth);
}

void translateCharacter(struct DNAcontent * order, struct DNAword * word, char t)
{
		char sentence[6];
		findCharacter(t, word, sentence);
		translateWord(order, word, sentence);
		printTranslation(sentence);
}

void findCharacter(char t, struct DNAword * word, char * sentence)
{
	/*if(t == 0)
		setIntron(word);
	if(n == 1)
		setSecondChar(word);*/
	if((t < 93) && (t > 32))
		searchTable(t, word);
	if((t > 93) && (t < 155))
	{
		t = t - 62;
		searchTable(t, word);
	}
	searchTable(t, word);
}

void translateWord(struct DNAcontent * order, struct DNAword * word, char * sentence)
{

}

void printTranslation(char * sentence)
{

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
						break;
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
