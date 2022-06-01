typedef struct Sfacture facture;
facture * getFactures(char* );

void AddFacture(int, char*);
int Facture_existe(int,char*);
int Facture_exist(int);
int FichierVideF(FILE *);
void AfficherTousLesFactures();
void AfficherLesFacturesDunClient(int);

