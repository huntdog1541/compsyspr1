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
}
