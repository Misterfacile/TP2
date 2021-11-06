#ifndef CHEMINCOURT_H_
#define CHEMINCOURT_H_


typedef enum{
	false,
	true,
}Bool;

// Un element de la file
typedef struct felement{
	int value;
	struct felement *avant;
	struct felement *après;
}felement;

// File
typedef struct file{
	int length;
	struct felement *begin;
	struct felement *end;
}*file;
file new_file();
Bool empty(file d);
int file_length(file f);
int element_first(file f);
int element_last(file f);
file push(file file, int x);
file pop(file file);
void afficheFile(file file);
void plusCourtChemin(int **adjacence, int ordre, int s, int *l, int *pred);



// Code du TP01

void marquerVoisin(int **adjacence , int ordre, int s);
void afficheVoisinMarque(int *t, int ordre, int s);
void allouerTableau2(int** t, int n);
void afficherMatrice(int *t, int n);
void afficherMatrice2D(int **t, int l);
void adjacence(int* t,int noeud2);
void adjacence2D(int **t,int noeud1, int noeud2);
void afficheVoisin(int *t, int n);
void chargeGraphe(int **t, int ordre);
void chargeExercice();
#endif /* CHEMINCOURT_H_ */
