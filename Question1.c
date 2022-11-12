#include <stdio.h>
#include <stdlib.h>

#include "Questions.h"



char *my_strcat(const char * const str1, const char * const str2){

	/* this is the pointer holding the string to return */
	char *z = NULL;

	int x,y;
	
		//allocates memory for the new string
		z = (char*) calloc((strlen(str1) + strlen(str2) + 1), sizeof(char));

		//reads through first string then adds it to a new string
		for(x = 0; x < strlen(str1); x++)
		{
			z[x] = str1[x];
		}
		//reads through second string then adds it to the ending of a new string
		for(y = 0; y < strlen(str2); y++)
		{
			z[x + y] = str2[y];
		}

		//adding /0 at the end of the string
		z[x + y] = '\0';

	return z;
	
}
