#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "FontionsPop.h"

float getprixFacture(int idf){
  	float som=0;
  	FILE *f = fopen("commande.txt", "r");
  	int idff=0;
  	int q=0;
  	int idp;
  	while(1){
  	idff=atoi(SaisirChainePop(f));
  	idp=atoi(SaisirChainePop(f));
  	q=atoi(SaisirChainePop(f));
  	if(idf==idff){
  		float getprixHproduit(int);
  		som+=getprixHproduit(idp)*q;
  		//printf("%d",idp);

  	}
  	if (feof(f)!=0)
  	break;
  	}
  	return som;
  }


float getprixHproduit(int idp){
	float prixH=0;
	FILE *f = fopen("produit.txt", "r");
	int idpp=0;
	char * desi;
	float prixU;
	float tva;
	while(idpp!=idp){

	idpp=atoi(SaisirChainePop(f));
	desi=SaisirChainePop(f);
	prixU=atof(SaisirChainePop(f));
	tva=atof(SaisirChainePop(f));

	//pour indiquer la fin du fichier
	if (feof(f)!=0)
	break;
    }
	/* a la sortie de la boucle while, on va tetster si on trouver notre produit
		et ce nest pas seulemet car on est a la fin du fichier.
	*/
	if(idpp == idp)
		prixH=prixU*(1+tva);

	return prixH;
}

float getCac(int idc){
	float chiffre=0;
	FILE *f = fopen("facture.txt", "r");
	int idcc;
	int idf;
	char* date;
	while(1){
	idf=atoi(SaisirChainePop(f));
	idcc=atoi(SaisirChainePop(f));
	date=SaisirChainePop(f);
	if(idc==idcc){
		chiffre+=getprixFacture(idf);

	}
	if (feof(f)!=0)
	break;
	}
	return chiffre;
}
