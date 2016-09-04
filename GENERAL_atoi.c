/*
 * atoi: "321" converts in 321
 *
 * */

#include <stdio.h>
#include <ctype.h>

int hisatoi(char *pointer){

	int mul=1; 	//multiplier to cal number with base 10
	int result=0; // final number
	char *current = pointer;

	while(*current != '\0')
	{
		// if "321", we want to multiply 3 with 100
	    if(*current >= '0' && *current <= '9')
	        mul = mul * 10;

	    current++;
	}

	mul = mul/10;


	current = pointer;
	while(*pointer != '\0')
	{
		// CRITICAL piece
		// ASCII of '0' is 48, so from char to int, %48
	    result = result + ( (*pointer%48)  * mul);
	    mul = mul / 10;

	    pointer++;
	}

	return result;
}

int myatoi(char *str){
	int value;
	char *current  = str;

	while(isdigit(*current))
	{
		value = value * 10;
		value = value + (*current - '0');
		current++;
	}

	return value;
}

int main(){

	char *str = "321";
	printf("Result = %d\n", hisatoi(str));

	return 0;
}
