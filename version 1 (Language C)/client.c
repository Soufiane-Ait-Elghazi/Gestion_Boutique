#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "Fonctions.h"
#include "CAC.h";

typedef struct Sclient
{
	unsigned int idClient;
    char *nomClient;
    char *prenomClient;
    char *adresseClient;
    char *codepostalClient;
    char *villeClient;
    float CAC;
    struct Sclient *suivant;
}client;

client * getClients(char* );

// Generer une liste chainee d'apres le ficher client.txt

client * getClients(char* File)
{
	unsigned int id;
	char *Nom, *Prenom, *Adresse, *codepostal,*ville;
	float cac;
	client *ListClient=NULL;
	FILE *f = fopen(File , "r");
	while(!feof(f))
	{
		id = atoi(SaisirChaine(f));
		Nom = SaisirChaine(f);
		Prenom = SaisirChaine(f);
		Adresse = SaisirChaine(f);
		codepostal = SaisirChaine(f);
		ville = SaisirChaine(f);
		cac = atof(SaisirChaine(f));
		client *ajouterClientauList(client*, int, char*, char*, char *, char*, char *,float);
		ListClient = ajouterClientauList(ListClient,id, Nom, Prenom, Adresse, codepostal,ville,cac);

	}
	fclose(f);
	return ListClient;

 }

// update CAC en liste
void updateCac(){
	client *AllClient = getClients("client.txt");
	client *cl;
	cl = AllClient;

		while(cl != NULL)
			{
				cl->CAC = getCaclient(cl->idClient);
				cl = cl->suivant;
			}
		void RefrechClients(client*,char *);
		RefrechClients(AllClient,"client.txt");

}

 //Verifier si la liste est vide
 int estVide(client *cl)
 {
 	if(cl == NULL)
 		return 1;
 	return 0;
 }
 // Verifier si le ficher Client est vide
 int FichierVide(FILE *file)

 {
     long savedOffset = ftell(file);
     fseek(file, 0, SEEK_END);

     if (ftell(file) == 0){
         return 1;
     }
     fseek(file, savedOffset, SEEK_SET);
     return 0;
 }
// existance d'un client par ses informations

int Client_existe(char* Nom, char* Prenom, char * Adresse, char *code,char *ville)
{
	client *All = getClients("client.txt");
	client *cl;
	cl = All;

	while(cl != NULL)
	{
		if(strcmp(cl->nomClient,Nom) == 0 && strcmp(cl->prenomClient, Prenom) == 0 && strcmp(cl->adresseClient, Adresse)==0
		&& strcmp(cl->codepostalClient, code)==0)
		{
			return 1;
		}
		cl = cl->suivant;
	}
	return 0;
}
// ajouter un Client au fichier client.txt

void AddClient(char* Nom, char* Prenom, char* Adresse, char* code, char *ville,float cac)
{
	FILE *f = fopen("client.txt", "a+");
	client *cl;
	cl = malloc(sizeof(client));
	cl->idClient = getId("client.txt") + 1;
	cl->nomClient = Nom;
	cl->prenomClient = Prenom;
	cl->adresseClient = Adresse;
	cl->codepostalClient = code;
	cl->villeClient=ville;
	cl->CAC=cac;
	cl->suivant = NULL;

	if(FichierVide(f) == 1)
			{
				fprintf(f,"\n%d:%s:%s:%s:%s:%s:%f", cl->idClient,cl->nomClient,
				cl->prenomClient,cl->adresseClient, cl->codepostalClient,cl->villeClient,cl->CAC);
				printf("\n Mr. %s %s est devenu un client",cl->nomClient,cl->prenomClient);
				fclose(f);
				return;
			}
		else
			{
				if(Client_existe(cl->nomClient, cl->prenomClient, cl->adresseClient, cl->codepostalClient,cl->villeClient) == 0)
				{
					fprintf(f,"\n%d:%s:%s:%s:%s:%s:%f", cl->idClient,cl->nomClient,
						cl->prenomClient,cl->adresseClient, cl->codepostalClient,cl->villeClient,cl->CAC);
					printf("\n Mr. %s %s est devenu un client",cl->nomClient,cl->prenomClient);
					fclose(f);
					return;

				}
				else {
					printf("\nLe client MR. %s %s deja existe.\n",cl->nomClient,cl->prenomClient);
					return;
				}
			}
}

// existance d'un client par son ID

int Client_exist(int id)
{
	client *All = getClients("client.txt");
	client *cl ;
	cl = All;
	if(cl == NULL)
	{
		printf("\nLa liste est vide\n");
		return 0;
	}
	while(cl != NULL)
	{
		if(cl->idClient == id)
		{
			return 1;
		}
		cl = cl->suivant;
	}
	return 0;
}

// Ajouter un Client au list des clients

client *ajouterClientauList(client *List, int id, char* Nom, char* Prenom, char * Adresse, char* code, char *ville,float cac){

	client * cl = malloc(sizeof(client));
	// constructeur d'objet client

	cl->idClient = id;
	cl->nomClient = Nom;
	cl->prenomClient = Prenom;
	cl->adresseClient = Adresse;
	cl->codepostalClient = code;
	cl->villeClient = ville;
	cl->CAC=cac;
	cl->suivant= NULL;

	// ajouter a la fin de liste

	if(estVide(List) == 1){
		List = cl;
		return List;
	}
	else{
		client *pt;
		client *pos;

		pt = List;
		while(pt->suivant != NULL)
		{
			pos = pt;
			pt = pt->suivant;
		}
		pt->suivant = cl;
		return List;
	}
}
// Afficher Tous les clients select * from client;
void AfficherTousLesClients()
{
	int i=0;
	printf("L\'affichage de tous les clients :\n\n");
	// remplissage de liste appartir du fichier texte;
	client *AllClient = getClients("client.txt");
	client *cl;
	cl = AllClient;
	if(cl == NULL){
		printf("Il n\'y a pas des clients");
		return;
	}
	else{
		while(cl != NULL)
		{
			if(cl->idClient== 0)
			{
				printf("\nIl n\'y a pas des clients:");
				return;
			}
			else
			{
			printf("+----------client n : %d ----------------+\n+",++i);
			printf("\n+\tIdClient:\t%i\t\t+\n", cl->idClient);
			printf("+\tNom:\t\t%s\t\t\n", cl->nomClient);
			printf("+\tPrenom: \t%s\t+\n", cl->prenomClient);
			printf("+\tAdresse:\t%s\t+\n", cl->adresseClient);
			printf("+\tCode postal:\t%s\t\t+\n", cl->codepostalClient);
			printf("+\tville:\t\t%s\t\t\n", cl->villeClient);
			printf("+\tcac:\t\t%f\t+\n", getCaclient(cl->idClient));
			}
			cl = cl->suivant;

		}
		printf("+-----------------fin-------------------+\n");
	}

}
// modifier les infos un client dapres son ID
void changerInfoClient(int id)
{
	client *AllClient = getClients("client.txt");
	int choix;
	client *Cl;
	Cl = AllClient;
		if(Cl == NULL){
		printf("Il n\'y a pas des clients");
		return  ;
	}
	else{
		while(Cl != NULL)
		{
			if(Cl->idClient == id)
			{
				printf("\nChoisissez ce que vous voulez changer pour le client %s %s :\n1 - Le nom\n2 - Le prenom\n3 - L\'adresse\n4 - Codepostal\n5 - la ville\n",Cl->nomClient,Cl->prenomClient);
				scanf("%i", &choix);
				getchar();
				switch(choix)
				{
					case 1 ://si jamais on fait des erreure au niveau de la saisir du nom
						printf("Inserer le nouveau nom: ");
						Cl->nomClient =SaisirChaine(stdin);

						break;
					case 2 ://si jamais on fait des erreure au niveau de la saisir du prenom
						printf("Inserer le nouveau Prenom: ");
						Cl->prenomClient = SaisirChaine(stdin);
						break;
					case 3 :
						printf("Inserer la nouvelle Adresse: ");
						Cl->adresseClient = SaisirChaine(stdin);

						break;
					case 4 :
						printf("Inserer le nauveau code postal: ");
						Cl->codepostalClient = SaisirChaine(stdin);

						break;
					case 5 :
						printf("Inserer la nouvelle villel: ");
						Cl->villeClient = SaisirChaine(stdin);

						break;
				}
				printf("\nLe nouveau profil est : \n");
				printf("\nId:\t\t%i\n", Cl->idClient);
				printf("\nNom:\t\t%s\n", Cl->nomClient);
				printf("\nPrenom \t\t%s\n", Cl->prenomClient);
				printf("\nAdresse:\t%s\n", Cl->adresseClient);
				printf("\ncode postal:\t%s\n", Cl->codepostalClient);
				printf("\nville:\t%s\n", Cl->villeClient);
				do{
				printf("voulez vous sauvgarder les changements ? \n");
				printf("entez 1 pour valider ou 0 sinon : ");
				scanf("%d",&choix);
			    }while((choix != 0) && (choix != 1));
				if(choix == 1){
					void RefrechClients(client*,char *);
			    	RefrechClients(AllClient,"Client.txt");
			    	printf("vous avez sauvgarder.\n");
			    	return ;
		        }
		        else if (choix == 0){
		         printf("vous n'avez pas sauvgarder.\n");
		         return ;
		        }
			}
			Cl = Cl->suivant;
		}
		printf("Ce Client n\'existe pas");
		return ;
	}
}
// met a jour le ficher client.txt
void RefrechClients(client* list,char * file)
{
	if(list == NULL)
	{
		printf("la list est vide");
		FILE * f = fopen(file , "w");
		fclose(f);
		return;
	}
	FILE * f = fopen(file , "w");
	if(f == NULL)
	{
		printf("Can\'t open the file");
		return;
	}
	client *curent;
	curent = list;
	while(curent != NULL){
		fprintf(f, "%d:", curent->idClient);
		fprintf(f, "%s:",  curent->nomClient);
		fprintf(f, "%s:",  curent->prenomClient);;
		fprintf(f, "%s:",  curent->adresseClient);
		fprintf(f, "%s:",  curent->codepostalClient);
		fprintf(f, "%s:",  curent->villeClient);
		if(curent->suivant != NULL)
		{
			fprintf(f, "%f\n",  curent->CAC);
		}
		else if (curent->suivant== NULL)
		{
			fprintf(f, "%f",  curent->CAC);
	}
		curent = curent->suivant;
	}
	fclose(f);
}
// CHERCHER UN CLIENT DANS LA LISTE DES CLIENTS avec ses attributs;
void ChercherCient()
{
	client *All;
	client *C;
	int id, choix = 0;
	char *nom;
	char *prenom;
	int res=0;

	All = getClients("client.txt");
	C = All;
	if(C == NULL)
	{
		printf("\nLa liste est vide\n");
		return;
	}

	printf("\nRecherche par id : 1\n");
	printf("Recherche par Nom : 2\n");
	printf("Recherche par Prenom : 3\n");
	do{
	printf("Votre choix :");
	scanf("%d",&choix);
	getchar();
	}while(choix != 1 && choix != 2 && choix != 3);
	switch(choix){
		case 1:
			printf("\nDonner id du Client que vous cherchez :");
			scanf("%d",&id);
			getchar();
			while(C != NULL)
			{
				if(C->idClient == id)
				{
					res=1;
					printf("\n--------------------------------\n");
					printf("Id:\t\t%i\n", C->idClient);
					printf("Nom:\t\t%s\n", C->nomClient);
					printf("Prenom \t\t%s\n", C->prenomClient);
					printf("Adresse:\t%s\n", C->adresseClient);
					printf("code postal:\t%s\n", C->codepostalClient);
					printf("ville:\t\t%s\n", C->villeClient);
					printf("cac:\t\t%f\n", C->CAC);
					printf("--------------------------------\n");
					return;
				}
				C = C->suivant;
			}
			if(res == 0)
				printf("\nCette id n\'existe pas\n");
			printf("Recherche termine\n");
			return;
		case 2:
			printf("\nDonner le nom du Client que vous cherchez :");
			nom=SaisirChaine(stdin);
			while(C != NULL)
			{
				if(strcmp(C->nomClient, nom) == 0)
				{
					res=1;
					printf("\n--------------------------------\n");
					printf("Id:\t\t%i\n", C->idClient);
					printf("Nom:\t\t%s\n", C->nomClient);
					printf("Prenom \t\t%s\n", C->prenomClient);
					printf("Adresse:\t%s\n", C->adresseClient);
					printf("code postal:\t%s\n", C->codepostalClient);
					printf("ville:\t\t%s\n", C->villeClient);
					printf("cac:\t\t%f\n", C->CAC);
					printf("--------------------------------\n");

				}
				C = C->suivant;
			}
			if(res == 0)
				printf("\nCette nom n\'existe pas\n");
			printf("Recherche termine\n");
			return;
		case 3:
			printf("\nDonner le prenom du Client que vous cherchez :");
             prenom=SaisirChaine(stdin);
			while(C != NULL)
			{
				if(strcmp(C->prenomClient, prenom)== 0)
				{
					res=1;
					printf("\n--------------------------------\n");
					printf("Id:\t\t%i\n", C->idClient);
					printf("Nom:\t\t%s\n", C->nomClient);
					printf("Prenom \t\t%s\n", C->prenomClient);
					printf("Adresse:\t%s\n", C->adresseClient);
					printf("code postal:\t%s\n", C->codepostalClient);
					printf("ville:\t\t%s\n", C->villeClient);
					printf("cac:\t\t%f\n", C->CAC);
					printf("--------------------------------\n");

				}
				C = C->suivant;
			}
			if(res == 0)
				printf("\nCette prenom n\'existe pas\n");
			printf("Recherche termine\n");
			return;
	}
}
// Supprimer un client avec son ID
void deleteClient(int id)
{
	int choix = 3; // different de 1 et de 0;

	client *liste = getClients("client.txt");
	client *CClient; // Client courant
	client *PClient = NULL; // Client precedent

	if(liste == NULL){
	printf("Il n\'y a pas des clients");
	return  ;
	}
	else
	{

		CClient = liste;
		while(CClient != NULL)
		{
			if(CClient->idClient == id)
			{
				// cas ou ul y a un seul client:

				if(PClient == NULL && CClient->suivant == NULL)
				{
					liste = NULL;
					do{
						printf("voulez vous sauvgarder les changements ? \n");
						printf("entez 1 pour valider ou 0 sinon : ");
						scanf("%d",&choix);
					    }while((choix != 0) && (choix != 1));
						if(choix == 1)
						{
					    	RefrechClients(liste,"client.txt");
					    	printf("\nvous avez sauvgarder.\n");
							return;
						}
						else if (choix == 0)
						{
							printf("\nvous n'avez pas sauvgarder.\n");
							return;
						}
				}
				// cas dans le client est le premier element de la liste

				else if(PClient == NULL)
				{
					liste = CClient->suivant;
						do{
						printf("voulez vous sauvgarder les changements ? \n");
						printf("entez 1 pour valider ou 0 sinon : ");
						scanf("%d",&choix);
					    }while((choix != 0) && (choix != 1));
						if(choix == 1){
					    	RefrechClients(liste,"client.txt");
					    	printf("vous avez sauvgarder.\n");
					    	return;
				        }
				        else if (choix == 0){
				         printf("vous n'avez pas sauvgarder.\n");
				         return ;
				        }
				}
				else
				{
					// cas ou notre element n'est pas au debut de la liste;
					if(CClient->suivant== NULL)
						// si notre element est e dernier de la liste;
					{
						PClient->suivant= NULL;
						do{
						printf("voulez vous sauvgarder les changements ? \n");
						printf("entez 1 pour valider ou 0 sinon : ");
						scanf("%d",&choix);
					    }while((choix != 0) && (choix != 1));
						if(choix == 1){
					    	RefrechClients(liste,"client.txt");
					    	printf("vous avez sauvgarder.\n");
					    	return ;
				        }
				        else if (choix == 0){
				         printf("vous n'avez pas sauvgarder.\n");
				         return ;
				        }
					}
					else
					{
						// le cas ou notre element est au milieux de la liste;

						PClient->suivant= CClient->suivant;
						do{
						printf("voulez vous sauvgarder les changements ? \n");
						printf("entez 1 pour valider ou 0 sinon : ");
						scanf("%d",&choix);
					    }while((choix != 0) && (choix != 1));
						if(choix == 1){
					    	RefrechClients(liste,"Client.txt");
					    	printf("vous avez sauvgarder.\n");
					    	return ;
				        }
				        else if (choix == 0){
				         printf("vous n'avez pas sauvgarder.\n");
				         return ;
				        }

					}
				}
			}
			PClient = CClient;
			CClient = CClient->suivant;
		}
		printf("Ce Client n\'existe pas");
		return ;
	}
}


/*int main(){
	//getClients("client.txt");
	//char NOM[20]="HADOUDI",PRENOM[20]="KARIM",ADRESSE[20]="ADRESE4",CODE[20]="CODE4",ville[20]="TINGHIR";
	//float cac=0.0;
	//AddClient(NOM,PRENOM,ADRESSE,CODE,ville,cac);
	//getClients("client.txt");
	//AfficherTousLesClients();
	//changerInfoClient(3);
	AfficherTousLesClients();
	//ChercherCient();
	//deleteClient(4);

	return 0;
}


*/














