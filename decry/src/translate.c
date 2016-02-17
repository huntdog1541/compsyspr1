/*
 * translate.c
 *
 *  Created on: Feb 13, 2016
 *      Author: David
 */

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
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

void parseInput(struct DNAcontent * order, struct content * con, char * in)
{
	int i = 0;
	char temp = in[i];
	setDNAset(temp, order->firstOrder);
	i = i + 2;
	temp = in[i];
	setDNAset(temp, order->secondOrder);
	i = i + 2;
	temp = in[i];
	setDNAset(temp, order->thirdOrder);
}

void setDNAset(char r, struct DNAset * order)
{
	switch(r)
	{
		case 'A':
				order->first = 'A';
				order->second = 'C';
				order->third = 'G';
				order->fourth = 'T'; break;
		case 'C':
				order->first = 'C';
				order->second = 'G';
				order->third = 'T';
				order->fourth = 'A'; break;
		case 'G':
				order->first = 'G';
				order->second = 'T';
				order->third = 'A';
				order->fourth = 'C'; break;
		case 'T':
				order->first = 'T';
				order->second = 'A';
				order->third = 'C';
				order->fourth = 'G'; break;
	}
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

void readFromInput(struct content * con, struct DNAcontent * order, struct codon * cd)
{
  fseek(con->fin, 0L, SEEK_END);
  con->size = ftell(con->fin);
  fseek(con->fin, 0L, SEEK_SET);
  int error = 0;
  if((con->size) % 3)
  {
    fprintf(stderr, "Error: error getting content from source\n");
    exit(1);
  }
  printf("Size of file is %ld\n", con->size);
  char * text = (char *)malloc(sizeof(char) * (con->size));
  error = fread(text, sizeof(char), (con->size), con->fin);
  if(error != con->size)
  {
	  fprintf(stderr, "error getting all content from file");
	  exit(1);
  }
  text[con->size] = '\0';
  printf("%s\n", text);
  getCodon(text, cd);
  free(text);
}

void printCharArray(char * str, int sz)
{
	int i, size = sz;
	for(i = 0; i < size; i++)
	{
		printf("%c : %d\n", str[i], str[i]);
	}
}

void getCodon(char * text, struct codon * cd)
{
	int size = strlen(text);
	int i = 0, j = 0, count = 0, k = 0;
	cd->numberCon = size/3;
	printf("The number of codon's is %d\n", cd->numberCon);
	cd->cod = (char *)malloc(sizeof(char) * (size + cd->numberCon));
	cd->group = (char **)malloc(sizeof(char *) * cd->numberCon);
	while(i < size)
	{
		cd->group[k++] = &cd->cod[count];
		for(j = 0; j < 3; j++)
		{
			cd->cod[count++] = text[i++];
		}
		cd->cod[count++] = '\0';
	}
	//printCharArray(codon, (size + numCodon));
	//printAllCodons(cd->group, cd->numberCon);
}

void printAllCodons(char ** group, int number)
{
	int i = 0;
	for(i = 0; i < number; i++)
	{
		printf("Codon #%d is %s\n", (i+1), group[i]);
	}
}

void startDecry(struct codon * cd, struct DNAcontent * order, struct content * con)
{
	int i;
	for(i = 0; i < cd->numberCon; i++)
	{
		printf("Codon #%d is %s: ", (i+1), cd->group[i]);
		decrypt(cd->group[i], order, con);
	}
}

void decrypt(char * dna, struct DNAcontent * order, struct content * con)
{
	int fcol = getNumber(dna[0], order->firstOrder);
	int scol = getNumber(dna[1], order->secondOrder);
	int tcol = getNumber(dna[2], order->thirdOrder);
	fprintf(con->fit, "%c", table[fcol][scol][tcol]);
	printf("%c : %d\n", table[fcol][scol][tcol], table[fcol][scol][tcol]);
}

int getNumber(char temp, struct DNAset * set)
{
	int answer = 0;
	if(temp == set->first)
		answer = 0;
	else if(temp == set->second)
		answer = 1;
	else if(temp == set->third)
		answer = 2;
	else
		answer = 3;

	return answer;
}
