
#include <stdlib.h>
#include <string.h>
#include <stdio.h>

// 
// Made by: Vladimir Gribanov
// Group:	717
//

// ~~~~~~~~~~~~~~~~~~~~~~~~~~ DEFINES ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ //

#define MAX_ARG_LEN 100

#define ERROR_CHECK( _cond_ , ...)									\
								do{									\
									if(_cond_)						\
									{								\
										printf(__VA_ARGS__);		\
										exit(0);					\
									}								\
								}while(0)

#define LOG(...) 		//

#ifdef TEST
#undef LOG
#define LOG(...) 		printf(__VA_ARGS__);
#endif

// ~~~~~~~~~~~~~~~~~~~~~~ FUNCTIONS DECLARE ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ //

int getLongestLen(char** strs, int amount);
int buffUpdate(char *buff, int size);
int partStrCmp(char *buff, int size, char *str);
int starBuffFill(int strsAmount, char** strs, char* buff, int size, unsigned int *starBuff);
unsigned int starBuffUpdate(unsigned int *starBuff, int size);

//
//	MAIN
//
int main(int argc, char** argv)
{
	int buffSize = 0;

	if(argc == 1)
	{
		LOG("No args!\n");
	}
	else
	{
		buffSize = getLongestLen(argv, argc) + 1;
	}
	LOG("\n! LOG ! buffSize = %d\n", buffSize);

	char *buff = (char*) calloc(buffSize, sizeof(char));
	unsigned int *starBuff = (unsigned int*) calloc(buffSize - 1, sizeof(unsigned int));
	unsigned int curSymbol = 0;
	int ret = 0;
	int starsAmount = 0;

	ret = buffUpdate(buff, buffSize - 1);

	while(ret != -1)
	{
		LOG("\n! LOG ! readed \"%s\"\n", &buff[ret]);
		if(ret == 0)
		{
			starBuffFill(argc, argv, buff, buffSize, starBuff);
			printf("%c", buff[0]);
			starsAmount = starBuffUpdate(starBuff, buffSize - 1);
			
			while(starsAmount != 0)
			{
				printf("*");
				starsAmount--;
			}

			LOG("%d", starsAmount);
		}

		ret = buffUpdate(buff, buffSize - 1);
	}
	printf("\n");

	free(starBuff);
	free(buff);
	return 0;
}

//------------------------------------------------------------------------//
//! Move all elements in starbuff left on one point, placing 0 at the end //
//! Return old first symbol                                               //
//------------------------------------------------------------------------//
unsigned int starBuffUpdate(unsigned int *starBuff, int size)
{
	unsigned int ret = starBuff[0];
	int i = 0;

	while(i < size - 1)
	{
		starBuff[i] = starBuff[i + 1];
		i++;
	}

	starBuff[size - 1] = 0;
	
	return ret;
}


//--------------------------------------------------//
//! This function write new information in starbuff //
//--------------------------------------------------//
int starBuffFill(int strsAmount, char** strs, char* buff, int size, unsigned int *starBuff)
{
	int i = 0;
	int len = 0;

	while(i < strsAmount)
	{
		len = partStrCmp(buff, size, strs[i]);

		if(len != -1)
			starBuff[len - 1]++;

		i++;
	}

	return 0;
}


//---------------------------------------------------------------//
//!	This function return the longest length of str in arguments  //
//---------------------------------------------------------------//
int getLongestLen(char** strs, int amount)
{
	int maxLen = 0;
	int len = 0;
	int curStr = 1;

	while(curStr < amount)
	{
		len = strnlen(strs[curStr], MAX_ARG_LEN);
		
		ERROR_CHECK((len == MAX_ARG_LEN), "\n\n<!> ERROR <!> Argument \"%s\" is longer then current MAX_ARG_LEN = %d \n", strs[curStr], MAX_ARG_LEN);

		if(len > maxLen)
			maxLen = len;

		curStr++;
	}

	return maxLen;
}


//--------------------------------------------------//
//! This function check, Is *str included in buff	//
//! if yes, return len of *str						//
//! if no, return -1								//
//--------------------------------------------------//
int partStrCmp(char *buff, int size, char *str)
{
	int i = 0;

	while(i < size)
	{
		if(str[i] == '\0')
			return i;

		if(buff[i] != str[i])
			return -1;

		i++;
	}

	return i;
}


//---------------------------------------------------------//
//! This function read new element & update buffer with it //
//---------------------------------------------------------//
int buffUpdate(char *buff, int size)
{
	char symbol = 0;
	int i = 0;
	int read = 0;

	if(buff[0] != '\0' && buff[size - 1] == '\0') 
	{
		while(i != size && buff[i] == '\0')
		{
			i++;
		}

		if(i == size)
			symbol = '\0';
		else
			read = fread(&symbol, sizeof(char), 1, stdin);
	}
	else
	{
		read = fread(&symbol, sizeof(char), 1, stdin);
	}

	if(symbol == '\n')
		symbol = '\0';

	i = 0;
	while(i != size - 1)
	{
		buff[i] = buff[i + 1];
		i++;
	}

	if(read == 1)
	{
		buff[size - 1] = symbol;
	}
	else
	{
		buff[size - 1] = '\0';

		i = 0;
		while(i != size && buff[i] == '\0')
		{
			i++;
		}

		if(i == size)
			return -1;
	}

	i = 0;
	while(buff[i] == '\0')
		i++;

	return i;
}






