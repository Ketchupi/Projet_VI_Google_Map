#include <stdio.h>
#include <stdlib.h>
#include <string.h>


short int** alloue_matrice(short int Hauteur, short int Longueur)
{
	short int** matrice = malloc(Hauteur * sizeof(short int*));
	int i;
	for(i=0;i<Hauteur;i++)
	{
		matrice = malloc(sizeof(short int) * Longueur);
	}
	
	return matrice; 
} 
