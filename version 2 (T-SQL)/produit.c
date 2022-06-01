#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "FonctionsP.h"


typedef struct Sproduit
{
	unsigned int idProduit;
	char * designation;
	int	 prixUnitaire;
	float TvaProduit;
    struct Sproduit *suivant;
}produit;

produit * getProduits(char*);

// Generer une liste chainee d'apres le ficher client.txt

produit * getProduits(char* File)
{
	char *designation;
	float Tva;
	int prixU,idp;

	produit *ListProduit=NULL;
	FILE *f = fopen(File , "r");
	while(!feof(f))
	{
		idp = atoi(SaisirChaineP(f));
		designation = SaisirChaineP(f);
		prixU = atoi(SaisirChaineP(f));
		Tva = atof(SaisirChaineP(f));

		produit *ajouterProduitList(produit*, int,char *,int,float);
		ListProduit = ajouterProduitList(ListProduit,idp,designation,prixU,Tva);
	}
	fclose(f);
	return ListProduit;
}

// Ajouter une produit au list des produits

produit *ajouterProduitList(produit *List,int idp,char*desi, int prixU, float Tva){

	produit * pro = malloc(sizeof(produit));

	// constructeur d'objet produit

	pro->idProduit=idp;
	pro->designation = desi;
	pro->prixUnitaire = prixU;
	pro->TvaProduit=Tva;
	pro->suivant= NULL;

	// ajouter a la fin de liste
	int estVideP(produit  *pro);
	if(estVideP(List) == 1){
		List = pro;
		return List;
	}
	else{
		produit *pt;
		produit *pos;

		pt = List;
		while(pt->suivant != NULL)
		{
			pos = pt;
			pt = pt->suivant;
		}
		pt->suivant = pro;
		return List;
}
}
int estVideP(produit  *pro)
 {
 	if(pro == NULL)
 		return 1;
 	return 0;

 }
 // Verifier si le ficher produit est vide

 int FichierVideP(FILE *file)

 {
     long savedOffset = ftell(file);
     fseek(file, 0, SEEK_END);

     if (ftell(file) == 0){
         return 1;
     }
     fseek(file, savedOffset, SEEK_SET);
     return 0;
 }

 // existance d'un produit  par ses informations

 int Produit_existe(char* desi, int prixU, float Tva)
 {
 	produit *All = getProduits("produit.txt");
 	produit *pro;
 	pro = All;

 	while(pro != NULL)
 	{
 		if(strcmp(pro->designation,desi) == 0 && pro->prixUnitaire == prixU &&  pro->TvaProduit == Tva)
 		{
 			return 1;
 		}
 		pro = pro->suivant;
 	}
 	return 0;
 }

 // existance d'un produit par son ID

 int Produit_exist(int id)
 {
 	produit *All = getProduits("produit.txt");
 	produit *pro ;
 	pro = All;
 	if(pro == NULL)
 	{
 		printf("\nLa liste est vide\n");
 		return 0;
 	}
 	while(pro != NULL)
 	{
 		if(pro->idProduit== id)
 		{
 			return 1;
 		}
 		pro = pro->suivant;
 	}
 	return 0;
 }
// ajouter un produit
 void AddProduit(char* desi,int prixU, float Tva)
 {
 	FILE *f = fopen("produit.txt", "a+");
 	produit *pro;
 	pro = malloc(sizeof(produit));
 	pro->idProduit = getIdP("produit.txt") + 1;
 	pro->designation=desi;
 	pro->prixUnitaire=prixU;
 	pro->TvaProduit=Tva;
 	pro->suivant = NULL;

 	if(FichierVideP(f) == 1)
 			{
 				fprintf(f,"\n%d:%s:%d:%f", pro->idProduit,pro->designation,pro->prixUnitaire,pro->TvaProduit);
 				printf("\n le produit %s est ajoute ",pro->designation);
 				fclose(f);
 				return;
 			}
 		else
 			{
 				if(Produit_existe(pro->designation,pro->prixUnitaire,pro->TvaProduit) == 0)
 				{
 					fprintf(f,"\n%d:%s:%d:%f", pro->idProduit,pro->designation,pro->prixUnitaire,pro->TvaProduit);
 					printf("\n le produit %s est ajoute ",pro->designation);
 					fclose(f);
 					return;

 				}
 				else {
 					printf("\nLe produit %s deja existe.\n",pro->designation);
 					return;
 				}
 			}
 }

// Afficher Tous les produits :  select * from client;
 void AfficherTousLesProduits()
 {
 	int i=0;
 	printf("L\'affichage de tous les produits :\n\n");
 	// remplissage de liste appartir du fichier texte;
 	produit *AllProduit = getProduits("produit.txt");
 	produit *pro;
 	pro = AllProduit;
 	if(pro == NULL){
 		printf("Il n\'y a pas des produits\n");
 		return;
 	}
 	else{
 		while(pro != NULL)
 		{
 			if(pro->idProduit== 0)
 			{
 				printf("\nIl n\'y a pas des produits:");
 				return;
 			}
 			else
 			{
 			printf("-----------produit n : %d ------------+\n",++i);
 			printf("+	 			     +\n");
 			printf("+  IdProduit:\t\t%i\t     +\n", pro->idProduit);
 			printf("+  Desgnation:\t\t%s\t     \n", pro->designation);
 			printf("+  prixUnitaire: \t%d\t     +\n", pro->prixUnitaire);
 			printf("+  TvaProduit: \t\t%f     +\n", pro->TvaProduit);
 			printf("+  				     +\n");
 			}
 			pro = pro->suivant;

 		}
 		printf("+-----------------fin----------------+\n\n");
 	}

 }

/*int main(){
 	getProduits("produit.txt");

  	char Desi[20] = "T-SHIRT";
  	float prixU = 145,Tva=0.25;
  	AddProduit(Desi,prixU,Tva);

  	getProduits("produit.txt");

  	AfficherTousLesProduits();
 	//AfficherLesFacturesDunClient(3);
  	return 0;
  }
  */

