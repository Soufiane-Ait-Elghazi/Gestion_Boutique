#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "SaisirChainePourCac.h"

float getprixFactureCac(int idf){
  	float som=0;
  	FILE *f = fopen("commande.txt", "r");
  	int idff=0;
  	int q=0;
  	int idp;
  	while(1){
  	idff=atoi(SaisirChaineCac(f));
  	idp=atoi(SaisirChaineCac(f));
  	q=atoi(SaisirChaineCac(f));
  	if(idf==idff){
  		float getprixHproduitCAC(int);
  		som+=getprixHproduitCAC(idp)*q;
  		//printf("%d",idp);

  	}
  	if (feof(f)!=0)
  	break;
  	}
  	return som;
  }


float getprixHproduitCAC(int idp){
	float prixH=0;
	FILE *f = fopen("produit.txt", "r");
	int idpp=0;
	char * desi;
	float prixU;
	float tva;
	while(idpp!=idp){

	idpp=atoi(SaisirChaineCac(f));
	desi=SaisirChaineCac(f);
	prixU=atof(SaisirChaineCac(f));
	tva=atof(SaisirChaineCac(f));

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

float getCaclient(int idc){
	float chiffre=0;
	FILE *f = fopen("facture.txt", "r");
	int idcc;
	int idf;
	char* date;
	while(1){
	idf=atoi(SaisirChaineCac(f));
	idcc=atoi(SaisirChaineCac(f));
	date=SaisirChaineCac(f);
	if(idc==idcc){
		chiffre+=getprixFactureCac(idf);

	}
	if (feof(f)!=0)
	break;
	}
	return chiffre;
}
