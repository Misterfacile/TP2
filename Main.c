#include <stdio.h>
#include <stdlib.h>

#include "cheminCourt.h"

int main(){
	printf("Tapez le nombre de noeud dans le graphe : ");
			int ordre;
			scanf("%d",&ordre);
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
					    scanf("%d",&noeud1);
					    if(noeud1 > ordre || noeud1< 0){
					    	printf("Le noeud n'existe pas \n");
					    }
					}while(noeud1>ordre || noeud1 < 0);
					do{
						printf("Avec quel noeud ? : ");
					    scanf("%d",&noeud2);
					    if(noeud2>ordre || noeud2 < 0){
					    printf("Le noeud n'existe pas \n");
					    }else if(noeud1 == noeud2){
					    	printf("Un noeud ne peut être voisin de lui-même \n");
					    }
					}while(noeud2>ordre || noeud2 < 0 || noeud1 == noeud2);
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


			int *pred,*l;
			pred = (int*) malloc(ordre*sizeof(int));
			l = (int*) malloc(ordre*sizeof(int));
			plusCourtChemin(adjacence,ordre,1,l,pred);
			for(int i = 0; i<ordre ; i++){
				if(pred[i] !=0){
					printf("(%d) est prédecesseur de (%d) avec une longueur entre (%d) et (%d) de : %d \n",pred[i],i+1,ref,i+1,l[i]);
				}

			}

}


