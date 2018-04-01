#ifndef MATRICE_H_INCLUDED
#define MATRICE_H_INCLUDED

#include "type.h"
#define maxl 100



/*************************************************************************************************************/
/*----------------------------lecture d'une matrice plainne--------------------------------------------------*/

void lect2D(float t[maxl][maxl],int *l,int *c);



/************************************************************************************************************/
/*--------------------------------------afficher une matrice 2D----------------------------------------------*/

void affich_mat(float M[maxl][maxl],int l,int c);




/***************************************************************************************************************/
/*-----------------convertir une matrice creuse donnée à une matrice plainne----------------------------------*/

void initial(float M[maxl][maxl],int l,int c);      ///--initialisé une matrice à 0

void convert_m(type_tab t[maxl],float M[maxl][maxl],int l,int c);








//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/****************                              Début des procédures                               ********************/
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////





/*************************************************************************************************************/
/*----------------------------lecture d'une matrice plainne--------------------------------------------------*/

void lect2D(float t[maxl][maxl],int *l,int *c)
{
    int i,j;

    printf("\n\n- Donner le nombre de lignes : ");scanf("%d",l);
    printf("\n\n- Donner le nombre de colonnes : ");scanf("%d",c);

    for (i=0;i<*l;i++)
    {
        for(j=0;j<*c;j++)
        {
            printf("\n\tM [%d][%d] = ",i,j);
            scanf("%f",&t[i][j]);
        }
        printf("\n");
    }
}
//////////////////////////////////////////////////////////////////////////////////////////////////////////////




/************************************************************************************************************/
/*--------------------------------------afficher une matrice 2D----------------------------------------------*/

void affich_mat(float M[maxl][maxl],int l,int c)
{
    int i,j;
    for (i=0;i<l;i++)
    {
        printf("\n\n\t\t");
        for (j=0;j<c;j++)
        {
            printf(" | %.2f |",M[i][j]);
        }
    }
    printf("\n\n");
}
////////////////////////////////////////////////////////////////////////////////////////////////////////////////




/***************************************************************************************************************/
/*-----------------convertir une matrice creuse donnée à une matrice plainne----------------------------------*/

///--initialisé une matrice à 0
void initial(float M[maxl][maxl],int l,int c)
{
    int i,j;
    for (i=0;i<maxl;i++)
    {
        for(j=0;j<maxl;j++)
        {
            M[i][j]=0;
        }
    }
}


void convert_m(type_tab t[maxl],float M[maxl][maxl],int l,int c)
{
    int i;
    maillon *p;
    initial(M,l,c);

    for(i=0;i<l;i++)
    {
        p=t[i].llc;
        while(p!=NULL)   ///--affecter les valeurs de llc dans la matrice selon la collonne
        {
            M[i][colonne(p)-1]=valeur(p);
            p=suivant(p);
        }
    }
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////




#endif // MATRICE_H_INCLUDED
