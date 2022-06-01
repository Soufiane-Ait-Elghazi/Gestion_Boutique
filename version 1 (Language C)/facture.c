#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "FonctionsFacture.h"
#include "FonctionsCac.h"

typedef struct Sfacture
{
	unsigned int idFacture;
	unsigned int idClient;
	char * DateFacturation;
    struct Sfacture *suivant;
}facture;

facture * getFactures(char* );

// Generer une liste chainee d'apres le ficher client.txt

facture * getFactures(char* File)
{
	unsigned int idf,idc;
	char *date;
	facture *ListFacture=NULL;
	FILE *f = fopen(File , "r");
	while(!feof(f))
	{
		idf = atoi(SaisirChaineF(f));
		idc = atoi(SaisirChaineF(f));
		date = SaisirChaineF(f);
		facture *ajouterFactureList(facture*, int, int,char*);
		ListFacture = ajouterFactureList(ListFacture,idf,idc,date);
	}
	fclose(f);
	return ListFacture;
}

// Ajouter une facture au list des factures

facture *ajouterFactureList(facture *List, int idf, int idc, char* date){

	facture * fac = malloc(sizeof(facture));

	// constructeur d'objet facture

	fac->idFacture = idf;
	fac->idClient = idc;
	fac->DateFacturation=date;
	fac->suivant= NULL;

	// ajouter a la fin de liste
	int estVideF(facture *fac);
	if(estVideF(List) == 1){
		List = fac;
		return List;
	}
	else{
		facture *pt;
		facture *pos;

		pt = List;
		while(pt->suivant != NULL)
		{
			pos = pt;
			pt = pt->suivant;
		}
		pt->suivant = fac;
		return List;
}
}
// ajouter ue facture au fichier;

void AddFacture(int idc, char* date){
	FILE *f = fopen("facture.txt", "a+");
	facture *fac;
	fac = malloc(sizeof(facture));
	fac->idFacture = getIdF("facture.txt") + 1; // auto increment idf
	fac->idClient=idc;
	fac->DateFacturation=date;
	fac->suivant = NULL;
	int FichierVideF(FILE *);
	if(FichierVideF(f) == 1)
			{
				fprintf(f,"\n%d:%d:%s", fac->idFacture,fac->idClient,fac->DateFacturation);
				printf("\n la facture d'IDfacture %d est ajoute\n",fac->idFacture);
				fclose(f);
				return;
			}
		else
			{
			    int Facture_existe(int,char*);
				if(Facture_existe(fac->idClient,fac->DateFacturation) == 0)
				{
					fprintf(f,"\n%d:%d:%s", fac->idFacture,fac->idClient,fac->DateFacturation);
					printf("\n la facture d'IDfacture %d est ajoute",fac->idFacture);
					fclose(f);
					return;

				}
				else {
					printf("\nLa facture d'id %i deja existe.\n",fac->idFacture);
					return;
				}
			}
}
//Verifier si la liste des factures est vide
 int estVideF(facture *fac)
 {
 	if(fac == NULL)
 		return 1;
 	return 0;

 }
 // existance d'une facture par ses informations

 int Facture_existe(int idc,char*date)
 {
 	facture *All = getFactures("facture.txt");
 	facture *fac;
 	fac = All;

 	while(fac != NULL)
 	{
 		if( fac->idClient == idc  && strcmp(fac->DateFacturation, date) == 0 )
 		{
 			return 1;
 		}
 		fac = fac->suivant;
 	}
 	return 0;
 }

 // existenxe d'une facture par id

 int Facture_exist(int idf)
 {
 	facture *All = getFactures("facture.txt");
 	facture *fac ;
 	fac = All;
 	if(fac == NULL)
 	{
 		printf("\nLa liste est vide\n");
 		return 0;
 	}
 	while(fac != NULL)
 	{
 		if(fac->idFacture == idf)
 		{
 			return 1;
 		}
 		fac = fac->suivant;
 	}
 	return 0;
 }
 // Verifier si le ficher facture est vide
  int FichierVideF(FILE *file)

  {
      long savedOffset = ftell(file);
      fseek(file, 0, SEEK_END);

      if (ftell(file) == 0){
          return 1;
      }
      fseek(file, savedOffset, SEEK_SET);
      return 0;
  }
  void AfficherTousLesFactures()
  {
  	int i=0;
  	printf("L\'affichage de tous les factures :\n\n");
  	// remplissage de liste appartir du fichier texte;
  	facture *AllFacture = getFactures("facture.txt");
  	facture *fac;
  	fac = AllFacture;
  	if(fac == NULL){
  		printf("Il n\'y a pas des factures\n");
  		return;
  	}
  	else{
  		while(fac != NULL)
  		{
  			if(fac->idFacture == 0)
  			{
  				printf("\nIl n\'y a pas des factures:\n");
  				return;
  			}
  			else
  			{

  			printf("+----------- facture n : %d ----------+\n",++i);
  			printf("+	 			     +\n");
  			printf("+  IdFacture:\t%i\t\t     +\n", fac->idFacture);
  			printf("+  IdClient:\t%i\t\t     +\n", fac->idClient);
  			printf("+  date: \t%s\t     +\n", fac->DateFacturation);
  			printf("+  prixTot:\t%f DHs\t     +\n",getprixFacture(fac->idFacture));
  			printf("+  				     +\n");

  			}

  			fac = fac->suivant;

  		}
  			printf("+-----------------fin----------------+\n");
  	}

  }
  // les factures d'un client donner
  void AfficherLesFacturesDunClient( int id){
	  int i=0,idt=0;
	    printf("L\'affichage de tous les factures de client de l'id %d  :\n\n",id);
	    // remplissage de liste appartir du fichier texte;
	    facture *AllFacture = getFactures("facture.txt");
	      	facture *fac;

	      	fac = AllFacture;
	      	if(fac == NULL){
	      		printf("Il n\'y a pas des factures\n");
	      		return;
	      	}
	      	else{
	      	  		while(fac != NULL)
	      	  		{
	      	  			if(fac->idFacture == 0)
	      	  			{
	      	  				printf("\nIl n\'y a pas des factures:\n");
	      	  				return;
	      	  			}
	      	  			else if(fac->idClient == id)
	      	  			{
	      	  				idt=id;

	      	  			printf("+----------- facture n : %d ----------+\n",++i);
	      	  			printf("+	 			     +\n");
	      	  			printf("+  IdFacture:\t%i\t\t     +\n", fac->idFacture);
	      	  			printf("+  IdClient:\t%i\t\t     +\n", fac->idClient);
	      	  			printf("+  date: \t%s\t     +\n", fac->DateFacturation);
	      	  			printf("+  prixTot:\t%f DHs\t     +\n",getprixFacture(fac->idFacture));
	      	  			printf("+  				     +\n");

	      	  			}

	      	  			fac = fac->suivant;

	      	  		}
	      	  		if(idt ==0){
	      	  			printf(" pas du factures pour le client d'id %d .\n",id);
	      	  		}
	      	  			printf("+-----------------fin----------------+\n");
	      	  	}

  }

  /* void dessinerFacture(){

  } */

 /*int main(){
  *
	//getFactures("facture.txt");
 	//char DATE[20] = "30/03/2021";
 	//int idc=3;
 	//AddFacture(idc,DATE);

 	//getFactures("facture.txt");

 	AfficherTousLesFactures();
	//AfficherLesFacturesDunClient(3);
	//AfficherTousLesClients();
 	return 0;
 }
 */



