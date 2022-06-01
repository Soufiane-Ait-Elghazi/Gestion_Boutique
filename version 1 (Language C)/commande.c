#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "FonctionsC.h"


typedef struct Scommande
{
	unsigned int idFacture;
	unsigned int idProduit;
	unsigned int Qt;
    struct Scommande *suivant;
}commande;


commande * getCommandes(char* );

// Generer une liste chainee d'apres le ficher commande.txt

commande * getCommandes(char* File)
{
	unsigned int idf,idp;
	int Qt;
	commande *ListCommande=NULL;
	FILE *f = fopen(File , "r");
	while(!feof(f))
	{
		idf = atoi(SaisirChaineC(f));
		idp = atoi(SaisirChaineC(f));
		Qt = atoi(SaisirChaineC(f));
		commande *ajouterCommandeList(commande*, int, int,int);
		ListCommande = ajouterCommandeList(ListCommande,idf,idp,Qt);
	}
	fclose(f);
	return ListCommande;
}
//ajouter une facture a la liste

commande *ajouterCommandeList(commande *List, int idf, int idp, int Qt){

	commande * com = malloc(sizeof(commande));

	// constructeur d'objet facture

	com->idFacture = idf;
	com->idProduit = idp;
	com->Qt=Qt;
	com->suivant= NULL;

	// ajouter a la fin de liste
	int estVideC(commande *com);
	if(estVideC(List) == 1){
		List = com;
		return List;
	}
	else{
		commande *pt;
		commande *pos;

		pt = List;
		while(pt->suivant != NULL)
		{
			pos = pt;
			pt = pt->suivant;
		}
		pt->suivant = com;
		return List;
}
}

void AddCommande(int idf,int idp,int qt){
	FILE *f = fopen("commande.txt", "a+");
	commande *com;
	com = malloc(sizeof(commande));
	com->idFacture=idf;
	com->idProduit=idp;
	com->Qt=qt;
	int FichierVideC(FILE *file);
	if(FichierVideC(f) == 1)
			{
				fprintf(f,"\n%d:%d:%d", com->idFacture,com->idProduit,com->Qt);
				printf("\n la commande est ajoute\n");
				fclose(f);
				return;
			}
		else
			{
			    int Commande_existe(int,int);
				if(Commande_existe(com->idFacture,com->idProduit) == 0)
				{
					fprintf(f,"\n%d:%d:%d", com->idFacture,com->idProduit,com->Qt);
					printf("\n la commande est ajoute\n");
					fclose(f);
					return;

				}
				else {
					printf("\nLa commande deja existe.\n");
					return;
				}
			}
}
int Commande_existe(int idf,int idp)
{
	commande *All = getCommandes("commande.txt");
	commande *com;
	com = All;

	while(com != NULL)
	{
		if( com->idFacture == idf  && com->idProduit == idp )
		{
			return 1;
		}
		com = com->suivant;
	}
	return 0;
}
int FichierVideC(FILE *file)

  {
      long savedOffset = ftell(file);
      fseek(file, 0, SEEK_END);

      if (ftell(file) == 0){
          return 1;
      }
      fseek(file, savedOffset, SEEK_SET);
      return 0;
  }

//Verifier si la liste des commande est vide
 int estVideC(commande *com)
 {
 	if(com == NULL)
 		return 1;
 	return 0;

 }
 // aficher toutes les commandes
 void AfficherTousLesCommandes()
  {
  	int i=0;
  	printf("L\'affichage de tous les Commandes :\n\n");
  	// remplissage de liste appartir du fichier texte;
  	commande *AllCommande = getCommandes("commande.txt");
  	commande *com;
  	com = AllCommande;
  	if(com == NULL){
  		printf("Il n\'y a pas des commandes\n");
  		return;
  	}
  	else{
  		while(com != NULL)
  		{
  			if(com->idFacture == 0 || com->idProduit == 0)
  			{
  				printf("\nIl n\'y a pas des commandes:\n");
  				return;
  			}
  			else
  			{

  			printf("+----------- commande n : %d ---------+\n",++i);
  			printf("+	 			     +\n");
  			printf("+  IdFacture:\t%i\t\t     +\n", com->idFacture);
  			printf("+  IdProduit:\t%i\t\t     +\n", com->idProduit);
  			printf("+  quantite: \t%i\t\t     +\n", com->Qt);
  			printf("+  				     +\n");

  			}

  			com = com->suivant;

  		}
  			printf("+-----------------fin----------------+\n");
  	}

  }


/*int main(){
	getCommandes("commande.txt");
 	int  quantite = 3;
 	int idp=2;
 	int idf=1;
 	AddCommande(idf,idp,quantite);
 	AfficherTousLesCommandes();

 	return 0;
 }
*/
