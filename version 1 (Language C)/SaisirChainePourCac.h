#include <stdio.h>
#include <stdlib.h>
char * SaisirChaineCac(FILE * fp)
{
	char * str = NULL ;
	unsigned int c, nbc = 0 ;

	while(((c = fgetc(fp)) != ':') && (c != EOF) && (c != '\n'))
	{
		str = realloc(str, (nbc+1)*sizeof(char)) ;
		str[nbc++] = c ;
	}
	str = realloc(str, (nbc+1)*sizeof(char)) ;
	str[nbc] = '\0' ;
	return str ;
}
