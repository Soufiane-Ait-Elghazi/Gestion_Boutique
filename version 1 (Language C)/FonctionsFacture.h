#include <stdio.h>
#include <stdlib.h>
char * SaisirChaineF(FILE * fp)
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
int getIdF(char * File) // Genere l'id de nouveau Client
{
	char Number[100];
	char * pch;
	FILE *f = fopen(File, "r");
	if(f == NULL){
		printf("Can\'t open the file");
		//return;
	}
	while(!feof(f))
	{
		fgets(Number, 100, f);
		pch = strtok(Number, ":");
	}
	char * N = pch;
	fclose(f);
	return atoi(N);
}
