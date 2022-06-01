typedef struct Scommande commande;
commande * getCommandes(char* );
commande *ajouterCommandeList(commande *, int, int, int);
void AddCommande(int idf,int idp,int qt);
int Commande_existe(int idf,int idp);
int FichierVideC(FILE *file);
void AfficherTousLesCommandes();
int Commande_existe(int,int);
