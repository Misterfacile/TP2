#include <stdio.h>
#include <stdlib.h>

#include "cheminCourt.h"



file new_file(){
	return NULL;
}
Bool empty(file file){
	if(file == NULL){
		return true;
	}else{
		return false;
	}
}


int file_length(file f){
	if(empty(f)){
		printf("File vide");
		exit(1);
	}else{
		return f->length;
	}
}
int element_first(file f){
	if(empty(f)){
		printf("Pas d'element retrouvé");
		exit(1);
	}else{
		return f->begin->value;
	}
}


int element_last(file f){
	if(empty(f)){
		printf("Pas d'element retrouvé");
		exit(1);
	}else{
		return f->end->value;
	}
}

// Ajout en dernier
file push(file file, int x){
	felement *element;
	element = malloc(sizeof(*element));
	if(element==NULL){
		printf("NON ALLOUEE");
		exit(0);
	}

	element->value = x;
	element->après = NULL;
	element->avant = NULL;
	if(empty(file)){
		file = malloc(sizeof(*file));
		if(file ==NULL){
			printf("NON ALLOUEE");
			exit(EXIT_FAILURE);
		}
		file -> length = 0;
		file -> begin = element;
		file -> end = element;
	}else{
		file->end->après = element;
		element->avant = file->end;
		file -> end = element;
	}
	file->length ++;
	return file;


}
/*// Ajout en premier
void push_front(file file, int x){
	felement *element;
	element = malloc(sizeof(*element));
	if(element==NULL){
		printf("NON ALLOUEE");
		exit(0);
	}

	element->value = x;
	element->après = NULL;
	element->avant = NULL;
	if(empty(file)){
		file = malloc(sizeof(*file));
		if(file ==NULL){
			printf("NON ALLOUEE");
			exit(0);
		}
		file -> length = 0;
		file -> begin = element;
		file -> end = element;
	}else{
		file->begin ->avant = element;
		element->après = file->begin;
		file -> begin = element;
	}
	file->length ++;

}
*/
// Renvoie la valeur du premier element de la file et le supprime de la liste
file pop(file file){
	if( empty(file)){
		printf("RIEN DANS LA LISTE \n");
		exit(EXIT_FAILURE);
	}

	if(file -> begin == file -> end){
		free(file);
		file = NULL;
		return new_file();

	}
	felement *temp = file->begin;

	file->begin = file->begin->après;
	file->begin->avant = NULL;
	temp->après = NULL;
	temp->avant = NULL;
	free(temp);
	temp = NULL;
	file->length--;
	return file;

}
void afficheFile(file f){
	if(empty(f)){
		printf("RIEN DANS LA LISTE");
		printf("\n");
		return;
	}

	felement *temp = f->begin;
	printf("FILE : ");

	do{
		printf("%d ",temp->value);
		temp = temp->après;
	}while(temp!= NULL);
	printf("\n");
}

// Utilisation de file FIFO
void plusCourtChemin(int **adjacence, int ordre, int s, int *l, int *pred){
	int *marques;
	int x,y;
	file t_file = new_file();

	marques = (int*) malloc(ordre * sizeof(int));
	for(x=0;x<ordre;x++){
		marques[x] = 0;
		l[x] = 0;
	}
	marques[s-1]= 1;
	t_file =push(t_file,s);

	while(!empty(t_file)){
		// Ajout de element dans x
		x = element_first(t_file)-1;

		// Enleve l'element dans la file
		t_file = pop(t_file);
		for(y=0; y<ordre ; y++){
				if(adjacence[x][y] && !marques[y]){

					marques[y] = 1;
					// Ajout du sommet dans la file
					t_file = push(t_file,y+1);


					//Prédecesseur du sommet y est sommet x+1 car on commence un tableau à indice 0
					pred[y] = x+1;
					l[y] = l[x]+1;
				}
			}
	}


}

/* Code du TP01
*
*
*
*
*
*
*
*
*
*
*
*
*
*
*/

void afficheVoisinMarque(int *t, int ordre, int s){
	printf("Sommet marqué selon le sommet %d : ",s);
	for(int i =0 ; i < ordre ; i++){
		if(t[i]==1){
			printf("(%d) ", i+1);
		}
	}
	printf("\n");
}
void marquerVoisin(int **adjacence , int ordre, int s){
	int *marques;
	int x,y;

	marques = (int*) malloc(ordre * sizeof(int));
	/*
	for(x=0;x<ordre;x++){
		marques[x] =  (int*) malloc(sizeof(int));

	}
	*/
	for(x=0;x<ordre;x++){
			marques[x] = 0;
		}
	marques[s-1] = 1;
	for(x=0;x<ordre;x++){
		if(marques[x]){
			for(y=0;y<ordre;y++){
				if(adjacence[x][y] && !marques[y]){
					marques[y] = 1;
				}
			}
		}
	}
	afficheVoisinMarque(marques,ordre,s);
}

void allouerTableau2(int** t, int n) {
	*t = (int*) malloc(n * sizeof(int));
}



void afficherMatrice(int *t, int n){
	int i = 0;
	for(i = 0; i<n; i++ ){
		printf("%d\t ", t[i]);
	}
}
void afficherMatrice2D(int **t, int l){
	int i;
	for(i = 0; i<l ; i++){
		afficherMatrice(t[i], l);
		printf("\n");
	}
}

void adjacence(int* t,int noeud2){
	t[noeud2-1] = 1;
}

void adjacence2D(int **t,int noeud1, int noeud2){
	adjacence(t[noeud1-1],noeud2);
	adjacence(t[noeud2-1],noeud1);
}

void afficheVoisin(int *t, int n){
	int i = 0;
	for(i = 0; i<n; i++ ){
		if(t[i]== 1){
			printf("(%d) ", i+1);
		}
	}
	printf("\n");
}
void chargeGraphe(int **t, int ordre){
	for(int i =0; i<ordre; i++){
		printf("(%d) : ",i+1);
		afficheVoisin(t[i],ordre);
	}
}

void chargeExercice(){
	printf("Tapez le nombre de noeud dans le graphe (le graphe commence au noeud 1) : ");
			int ordre;
			scanf("%d",&ordre);
			if(ordre == 0){
				return;
			}
			int **adjacence = NULL ;
			// Alloue les lignes de la matrice
			adjacence = (int**) malloc(ordre * sizeof(int*));

			// Alloue les colonnes de la matrice
			for(int i=0;i < ordre; i++){
				allouerTableau2(&(adjacence[i]), ordre);
			}

			int choix;
			int noeud1;
			int noeud2;
			do{
				printf("---Menu---\n");
				printf("1- Ajouter un voisin \n");
				printf("0- Initialisation de la matrice \n");
				printf("Votre choix : ");
				scanf("%d",&choix);
				if(choix == 1){

					do{
						printf("Quel noeud a un voisin ? : ");
						fflush(stdin);
					    scanf("%d",&noeud1);
					    if(noeud1 > ordre || noeud1<=0){
					    	fflush(stdout);
					    	printf("Le noeud n'existe pas \n");
					    }
					}while(noeud1>ordre || noeud1 <=0);
					do{
						printf("Avec quel noeud ? : ");
						fflush(stdin);
					    scanf("%d",&noeud2);
					    if(noeud2>ordre || noeud2 <= 0){
					    	fflush(stdout);
					    	printf("Le noeud n'existe pas \n");
					    }else if(noeud1 == noeud2){
					    	printf("Un noeud ne peut être voisin de lui-même \n");
					    }
					}while(noeud2>ordre || noeud2 <= 0 || noeud1 == noeud2);
					adjacence2D(adjacence,noeud1,noeud2);

				}else if(choix != 0){
					printf("\nChoix incorrecte \n");
				}
			}while(choix !=0);
			afficherMatrice2D(adjacence,ordre);
			printf("---------- Affichage Graphe format (Sommet) : (voisin1)  (voisin2) ---------- \n");
			chargeGraphe(adjacence,ordre);

			int ref;
			do{
				printf("Donner un sommet de référence pour le marquage des voisin : ");
				scanf("%d",&ref);
				if(ref > ordre || ref < 0){
					printf("Ce sommet n'est pas dans le graphe !! ");
				}
			}while(ref > ordre || ref < 0);
			marquerVoisin(adjacence,ordre,ref);
}















