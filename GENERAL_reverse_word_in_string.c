#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_STR_SIZE	100

char* reverse_string(char*, int);

char* reverse_string(char* str, int strlen)
{
	char temp='\0';
	int i=0; 
	int j=0;
	for(i=0, j=strlen-1; i<strlen/2; i++, j--)
	{
		temp = str[i];
		str[i] = str[j];
		str[j] = temp;
	}
	return str;
}

int main()
{
	char *inputStr, *headOfWord, *tailOfWord, *outputStr;
	int wordLen=0;
	inputStr = malloc(MAX_STR_SIZE);
	fgets(inputStr, MAX_STR_SIZE, stdin);
	headOfWord = tailOfWord = outputStr = inputStr;	
	
	while(*tailOfWord != '\0')
	{
		while(*tailOfWord != ' ' && *tailOfWord != '\0')
		{
			tailOfWord++;
		}
		wordLen = tailOfWord - headOfWord;
		outputStr = reverse_string(headOfWord, wordLen);
		outputStr = outputStr + wordLen; // +1 is to leave space
	
        if(*tailOfWord != '\0')
		{
	       //Next word now
		tailOfWord++;
		headOfWord = tailOfWord;
		}
	}

	outputStr = reverse_string(inputStr, strlen(inputStr));

	printf("outputStr = %s\n", outputStr);
	return 0;
}
