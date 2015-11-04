
#include <stdio.h>
#include <stdlib.h>
#include "OutilsLib.h"
#include "BmpLib.h"
#include "transfoPixel.h"
#include <string.h>

short int** alloueMatrice(DonneesImageRGB *image)
{
	short int **mat;
	int i;
	mat=(short int **)malloc(sizeof(short int *)*image->hauteurImage);
    
    for(i=0; i<image->hauteurImage; i++) {
        *(mat+i)=(short int *)malloc(sizeof(short int)*image->largeurImage);
        
	} 
	return mat;
}

void cree3matrices(DonneesImageRGB *image, short int **rouge,
                   short int **vert, short int **bleu)
// convertit DonneesImageRGB *image en trois matrices rouge, vert, bleu
{
    int i,j,k=0;
	
    for (i=0; i<image->hauteurImage; i++)
        for (j=0; j<image->largeurImage; j++)
        {
            bleu[i][j]=image->donneesRGB[k];
            k++;
            vert[i][j]=image->donneesRGB[k];
            k++;
            rouge[i][j]=image->donneesRGB[k];
            k++;
        }
}

void matricesVersImage(DonneesImageRGB *image, short int **rouge,
                       short int **vert, short int **bleu)
// convertit trois matrices rouge, vert, bleu en DonneesImageRGB *image
// attention : image doit être correctement alloue pour etre utilise
{
    int i,j,k=0;

    for (i=0; i<image->hauteurImage; i++)
        for (j=0; j<image->largeurImage; j++)
        {
            image->donneesRGB[k]=bleu[i][j];
            k++;
            image->donneesRGB[k]=vert[i][j];
            k++;
            image->donneesRGB[k]=rouge[i][j];
            k++;
        }
}

void sauveImage1composante(char *nom,DonneesImageRGB *image, short int **gris)
// permet de sauvegarder le contenu de la matrice gris dans un fichier BMP code sur 24 bits
// attention : image doit être correctement alloue pour etre utilise
{
    matricesVersImage(image,gris,gris,gris);
    ecrisBMPRGB_Dans(image,nom);
}

//=================================================================================================================================================
	//								TRAITEMENT D'IMAGE
//=================================================================================================================================================

void Gris(short int **rouge, short int **vert, short int **bleu, short int **ImageNiveauDeGris,DonneesImageRGB *image)
{
	int i,j;

	
        
	
	for(i=0; i<image->hauteurImage ;i=i+1)
	{
		for(j=0 ;j<image->largeurImage ;j=j+1)
		{
			ImageNiveauDeGris[i][j]=0.2125*rouge[i][j] + 0.7154*vert[i][j] + 0.0721*bleu[i][j];
		}
	}
	sauveImage1composante("Lvl_Gris.bmp",image,ImageNiveauDeGris);
}


void seuilleNB( short int **ImageNB,short int **ImageSeuille,short int Seuillage,short int H,short int L)
{
	int i,j;
	for(i=0; i<H ;i=i+1)
	{
		for(j=0 ;j<L ;j=j+1)
		{
			if(ImageNB[i][j] < Seuillage) //inf devient noir
			{
				ImageSeuille[i][j]=0;
			}
			else
			{
				ImageSeuille[i][j]=255;
			}
		}
	}
	//Fin parcours image
	//On sauve l'image
	
}

int main(void)
{
    DonneesImageRGB *image;
    
    short int **rouge;
    short int **vert;
    short int **bleu;
    short int **nb;
    short int **ImageNiveauDeGris;
    short int **ImageSeuille;
    short int H,L;
    int i;
    
    
    char nomImage[50];
    char nomFichier[50];
    
    // lecture du nom generique des images
    printf("nom de l'image a traiter : ");
    scanf("%s",nomImage);
    
    // creation d'un duplicata
    strcpy(nomFichier, nomImage);
    strcat(nomFichier,".bmp");
    
    printf("lecture\n");
    image = lisBMPRGB(nomFichier);
    //
    H=image->hauteurImage;
    L=image->largeurImage;
    //===============================
    rouge=alloueMatrice(image);
    vert=alloueMatrice(image);
    bleu=alloueMatrice(image);
    nb=alloueMatrice(image);
    ImageNiveauDeGris=alloueMatrice(image);
    ImageSeuille=alloueMatrice(image);
    //=================================
    printf("j'ai mon fichier \n");
    if (image == NULL)
    {
    	printf("Image NULL");
        return 0;
       }
    cree3matrices(image,rouge,vert,bleu);
    printf("j'ai fait mes matrices");
    strcpy(nomFichier, nomImage);
    strcat(nomFichier, "_duplicatat");
    strcat(nomFichier,".bmp");
    printf("ecriture\n");
    ecrisBMPRGB_Dans(image,nomFichier);
    
    Gris(rouge, vert, bleu, ImageNiveauDeGris,image);
    
    
    printf("cedric je t'ai baisé\n");
    
    seuilleNB( ImageNiveauDeGris,ImageSeuille,120,H,L);
    sauveImage1composante("Seuillage.bmp",image,ImageSeuille);
    
    free (rouge);
    free(vert);
    free(bleu);
    free(nb);

    
    return 0;
}

