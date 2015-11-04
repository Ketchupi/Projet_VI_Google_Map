#include <stdio.h>
#include <stdlib.h>
#include "OutilsLib.h"
#include "BmpLib.h"
#include <string.h>

int main (int argc, char *argv[] ) {
	DonneesImageRGB *image;
    int i;     
	//char nomImage[50];
    char nomFichier[50];
    
    strcpy(nomFichier, argv[1]);
    strcat(nomFichier,".bmp");
    
    printf("lecture\n");
    image = lisBMPRGB(nomFichier);
    short int **rouge=malloc(sizeof(short int)*image->largeurImage);
    short int **vert=malloc(sizeof(short int)*image->largeurImage);
    short int **bleu=malloc(sizeof(short int)*image->largeurImage);
    
    for(i=0; i<image->largeurImage; i++) {
        *(rouge+i)=malloc(sizeof(int short)*image->hauteurImage);
        *(vert+i)=malloc(sizeof(int short)*image->hauteurImage);
        *(bleu+i)=malloc(sizeof(int short)*image->hauteurImage);
	}
    printf("j'ai mon fichier\n");
    if (image == NULL)
        return 0;
	printf("La taille de l'image est %d de hauteur par %d de largeur mdr lol xD\n Maillot on te baise \n", image->hauteurImage, image->largeurImage);
//	printf("%d, %d, %d\n", sizeof(rouge), sizeof(vert), sizeof(bleu));
	
	for(i=0; i<image->largeurImage; i++) {
		free(rouge[i]);
//		free(*(vert+i));
	//	free(*(bleu+i));
	}
	free(rouge);
//	free(vert);
//	free(bleu);
//	libereDonneesImageRGB(image);
	
	return 0;
	
	  
}
