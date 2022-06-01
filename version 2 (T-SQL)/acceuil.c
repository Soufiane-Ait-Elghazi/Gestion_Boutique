#include<stdio.h>
#include<stdlib.h>
#include"produit.h"
#include"commande.h"
#include"client.h"
#include"facture.h"

//void menu2();
void menu()
{
	unsigned int choix = 20;  // choix de l'opperation a effectuer;
	unsigned int choix1 = 0;  // choix de confirmation de l'opperation;
	unsigned int choix2 = 0;  // choix de retoutne au menu au de quiter le programme;
	//unsigned int choix3 = 0;
	//unsigned int choix4 = 20;
	int id;
	char Nom[30];
	char prenom[30];
	char Adresse[40];
	char codePostal[30];
	char ville[20];

	printf("\n ce projet est realise par : \n");
	printf("\n HNA MUSTAPHA / BENDIR MOHAMMED / AIT HSSAINE MOHAMED\n");
	printf("\n");

	printf("\n                                              ******************************\n");
	printf("                                              *     gestion de boutique    *\n");
	printf("                                              ******************************\n");
	printf("\n  Menu 1:\n");
	printf("   _______________________________________________________________________________________________________________\n");
	printf("  | Les clients             | Les Factures                | Les Commandes	       | Les produits		  |\n");
	printf("  |_________________________|_____________________________|____________________________|__________________________|\n");
	printf("  |                         |                             |                            |			  |\n");
	printf("  |  1) Afficher les Clients| 6) Afficher Les factures    | 8) Ajouter une commande    |10) Ajouter un produit	  |\n");
	printf("  |                         |                             |                            |			  |\n");
	printf("  |  2) Ajouter un Client   | 7) Ajouter une facture      | 9) afficher les commandes  |11) afficher les produits |\n");
	printf("  |                         |                             |                            |		          |\n");
	printf("  |  3) Chercher un Client  |                             |        	               |	                  |\n");
	printf("  |                         |                             |                            |		          |\n");
	printf("  |  4) Modifier un Client  |   			  |                            |		          |\n");
	printf("  |                         |                             |                            |			  |\n");
	printf("  |  5) Supprimer un Client | 		               	  |  			       |		          |\n");
	printf("  |                         |                             |                            |			  |\n");
	printf("  |_________________________|_____________________________|____________________________|__________________________|\n");


	do{
		printf("\nVeuillez choisir le numero de la fonction que vous souhaitez (Inserer \"0\" pour arreter) : ");
		scanf("%d", &choix);
	}while(choix != 0 &&choix != 1 && choix != 2 && choix != 3 && choix != 4 && choix != 5 && choix != 6 && choix != 7 && choix != 8 && choix != 9 && choix != 10 && choix != 11 && choix != 12) ;

	switch (choix)
	{
		case 0:
			printf("\nvous avez choisi le numero 0 L\'operation va arreter, Merci!\n");
			return;
		case 1:
			printf("\nvous avez choisi le numero 1 \n");
			do{
				printf("Veuillez confirmer votre choix (1: oui | 0: Non) :");
				scanf("%d", &choix1);
				getchar();
			}while(choix1 != 0 && choix1 != 1);

			if(choix1 == 0)
				menu();
			else if(choix1 == 1)
			{
				AfficherTousLesClients();
				do{
				printf("\n1) Retour au menu | 0) Arreter le programme ");
				scanf("%d", &choix2);
				getchar();
				}while(choix2 !=0 && choix2 != 1);
				if(choix2 == 1)
					menu();
				else if(choix2 == 0)
					exit(0);
			}
			break;
		case 2:
			printf("\nvous avez choisi le numero 2 \n");
			do{
				printf("Veuillez confirmer votre choix (1: oui | 0: Non) :");
				scanf("%d", &choix1);
			}while(choix1 != 0 && choix1 != 1);
				if(choix1 == 0)
				menu();
			else if(choix1 == 1)
			{
				char temp[20];
				float cac=0;
				printf("\nPour Ajouter un Client inserer les information suivants:\n");
				printf("Nom: ");
				scanf("%c",&temp);// temp statement to clear buffer
				scanf("%[^\n]",Nom);

				printf("\nPrenom: ");
				scanf("%c",&temp);
				scanf("%[^\n]",prenom);

				printf("\nAdresse: ");
				scanf("%c",&temp);
				scanf("%[^\n]",Adresse);

				printf("\nCodePostal: ");
				scanf("%c",&temp);
				scanf("%[^\n]",codePostal);

				printf("\nVille: ");
				scanf("%c",&temp);
				scanf("%[^\n]",ville);

				printf("\nchiffre d'affaire: ");
				scanf("%f",&cac);

				AddClient(Nom, prenom, Adresse, codePostal,ville,cac);

				do{
				printf("\n1) Retour au menu | 0) Arreter le programme ");
				scanf("%d", &choix2);
				}while(choix2 !=0 && choix2 != 1);
				if(choix2 == 1)
					menu();
				else if(choix2 == 0)
				{
					exit(0);
				}
			}
				break;
		case 3:
			// chercher un client;
			printf("\nvous avez choisi le numero 3 \n");
			do{
				printf("Veuillez confirmer votre choix (1: oui | 0: Non) :");
				scanf("%d", &choix1);
			}while(choix1 != 0 && choix1 != 1);

			if(choix1 == 0)
				menu();
			else if(choix1 == 1)
			{

				ChercherCient();
				do{
				printf("\n1) Retour au menu | 0) Arreter le programme ");
				scanf("%d", &choix2);
				}while(choix2 !=0 && choix2 != 1);
				if(choix2 == 1)
					menu();
				else if(choix2 == 0)
					exit(0);
			}
				break;

		case 4:
			// modifier un client
			printf("\nvous avez choisi le numero 4 \n");
			do{
				printf("Veuillez confirmer votre choix (1: oui | 0: Non) :");
				scanf("%d", &choix1);
			}while(choix1 != 0 && choix1 != 1);

			if(choix1 == 0)
				menu();
			else if(choix1 == 1)
			{
				printf("\nPour modifier les informations d\'un Client inserer son ID:");
				scanf("%d", &id);
				changerInfoClient(id);
				do{
				printf("\n1) Retour au menu | 0) Arreter le programme ");
				scanf("%d", &choix2);
				}while(choix2 !=0 && choix2 != 1);
				if(choix2 == 1)
					menu();
				else if(choix2 == 0)
					exit(0);
			}
				break;
		case 5:
			// supprimer un Client;
			printf("\nvous avez choisi le numero 5 \n");
			do{
				printf("Veuillez confirmer votre choix (1: oui | 0: Non) :");
				scanf("%d", &choix1);
			}while(choix1 != 0 && choix1 != 1);

			if(choix1 == 0)
				menu();
			else if(choix1 == 1)
			{
				printf("\nPour supprimer un Client inserer son ID:");
				scanf("%d", &id);
				deleteClient(id);
				do{
				printf("\n1) Retour au menu | 0) Arreter le programme ");
				scanf("%d", &choix2);
				}while(choix2 !=0 && choix2 != 1);
				if(choix2 == 1)
					menu();
				else if(choix2 == 0)
					exit(0);
			}
				break;

		case 6:
			// afficher les factures;
			printf("\nvous avez choisi le numero 6 \n");
				do{
					printf("Veuillez confirmer votre choix (1: oui | 0: Non) :");
					scanf("%d", &choix1);
					getchar();
			      }while(choix1 != 0 && choix1 != 1);

						if(choix1 == 0)
							menu();
						else if(choix1 == 1)
						{
							AfficherTousLesFactures();
							do{
							printf("\n1) Retour au menu | 0) Arreter le programme ");
							scanf("%d", &choix2);
							getchar();
							}while(choix2 !=0 && choix2 != 1);
							if(choix2 == 1)
								menu();
							else if(choix2 == 0)
								exit(0);
						}
			break;
		case 7:
			// ajouter une facture;
			printf("\nvous avez choisi le numero 7 \n");
			do{
				printf("Veuillez confirmer votre choix (1: oui | 0: Non) :");
				scanf("%d", &choix1);
			}
			while(choix1 != 0 && choix1 != 1);
				if(choix1 == 0)
					menu();
				else if(choix1 == 1)
				{
					int idc;
					char date[20];
					printf("\nPour Ajouter une facture inserer les information suivants:\n");
					printf("idClient: ");
					scanf("%d",&idc);
					printf("\ndate de facture sous forme jj/mm/aaaa: ");
					scanf("%s",date);
					AddFacture(idc,date);

				do{
					printf("\n1) Retour au menu | 0) Arreter le programme ");
					scanf("%d", &choix2);
				}while(choix2 !=0 && choix2 != 1);
					if(choix2 == 1)
						menu();
					else if(choix2 == 0)
					{
						exit(0);
					}
				}
							break;
		case 8:
			//Ajouter une commande;
			printf("\nvous avez choisi le numero 8 \n");
			do{
				printf("Veuillez confirmer votre choix (1: oui | 0: Non) :");
				scanf("%d", &choix1);
		   	   }
			while(choix1 != 0 && choix1 != 1);
				if(choix1 == 0)
					menu();
				else if(choix1 == 1)
					{
						int idf,idp,qte;
						printf("\nPour Ajouter une commande inserer les information suivants:\n");
						printf("idFacture: ");
						scanf("%d",&idf);

						printf("\nidProduit: ");
						scanf("%d",&idp);

						printf("\nQuantite: ");
						scanf("%d",&qte);
						AddCommande(idf,idp,qte);


							do{
								printf("\n1) Retour au menu | 0) Arreter le programme ");
								scanf("%d", &choix2);
							}while(choix2 !=0 && choix2 != 1);
								if(choix2 == 1)
									menu();
								else if(choix2 == 0)
								{
									exit(0);
								}
							}
										break;
		case 9:
			// aficher les commandes;
			printf("\nvous avez choisi le numero 9 \n");
							do{
								printf("Veuillez confirmer votre choix (1: oui | 0: Non) :");
								scanf("%d", &choix1);
								getchar();
						      }while(choix1 != 0 && choix1 != 1);

									if(choix1 == 0)
										menu();
									else if(choix1 == 1)
									{
										AfficherTousLesCommandes();
										do{
										printf("\n1) Retour au menu | 0) Arreter le programme ");
										scanf("%d", &choix2);
										getchar();
										}while(choix2 !=0 && choix2 != 1);
										if(choix2 == 1)
											menu();
										else if(choix2 == 0)
											exit(0);
									}
			break;
		case 10:
			//ajouter un produit
			printf("\nvous avez choisi le numero 10 \n");
				do{
							printf("Veuillez confirmer votre choix (1: oui | 0: Non) :");
							scanf("%d", &choix1);
					   	   }
						while(choix1 != 0 && choix1 != 1);
							if(choix1 == 0)
								menu();
							else if(choix1 == 1)
								{
									int prix;
									char desi[20];
									float tva;
									printf("\nPour Ajouter une commande inserer les information suivants:\n");
									printf("PrixUnitaire produit : ");
									scanf("%d",&prix);

									printf("\nDesignation: ");
									scanf("%s",desi);
									getchar();

									printf("\nTVA-produit: ");
									scanf("%f",&tva);
									AddProduit(desi,prix,tva);


										do{
											printf("\n1) Retour au menu | 0) Arreter le programme ");
											scanf("%d", &choix2);
										}while(choix2 !=0 && choix2 != 1);
											if(choix2 == 1)
												menu();
											else if(choix2 == 0)
											{
												exit(0);
											}
										}
													break;

		case 11 :
			// aficher les produits
			printf("\nvous avez choisi le numero 11 \n");
				do{
					printf("Veuillez confirmer votre choix (1: oui | 0: Non) :");
					scanf("%d", &choix1);
					getchar();
					}
				while(choix1 != 0 && choix1 != 1);
					if(choix1 == 0)
						menu();
					else if(choix1 == 1)
					{
						AfficherTousLesProduits();
						do{
							printf("\n1) Retour au menu | 0) Arreter le programme ");
							scanf("%d", &choix2);
							getchar();

						}
						while(choix2 !=0 && choix2 != 1);
								if(choix2 == 1)
									menu();
									else if(choix2 == 0)
										exit(0);
					}
					break;



	}
}
