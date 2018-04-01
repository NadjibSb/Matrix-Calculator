#include <stdio.h>
#include <stdlib.h>
#include <windows.h>
#include <string.h>

#include "type.h"
#include "LLC.h"
#include "matrice.h"
#include "graphic.h"

#define maxl 100



int main()
{

/*************************************//*declaration des variables *//********************************************/

    int choix=1,choi=0,i,j;
    char name_file[20]="";
    int lign1=0,col1=0,lign2=0,col2=0,lignA=0,colA=0,lignB=0,colB=0,lignC=0,colC=0;
    float N;
    type_tab A[maxl],B[maxl],C[maxl],T1[maxl],T2[maxl],T3[maxl];
    float M[maxl][maxl];
    FILE *file;



/*****************************************//* DEBUT DU PROGRAMME *//***********************************************/

    debut();
    while(choix!=0)
    {

        MENU(&choix);      ///CHOIX PARMIS LE MENU

        switch (choix)
        {

/****************************************************** EXIT **************************************************************/
        case 0:

            EXIT();



        break;

/****************************************************************************************************************************/
///----------------------------------initialiser une matrice-----------------------------------------------------------------

        case 1:  case1:

            printf("Voullez vous entrer :\n\n         1.Matrice plainne.\n\n         2.Matrice creuse.\n\n  Votre choix : ");scanf("%d",&choi);

            switch (choi)
            {
            case 1:      /* initialiser une matrice plainne */

                lect2D(M,&lign1,&col1);
                affich_mat(M,lign1,col1);
                convert_t(M,T1,lign1,col1);
                choix_mat_result(T1,lign1,col1,A,&lignA,&colA,B,&lignB,&colB,C,&lignC,&colC);

            break;

            case 2:     /* initialiser une matrice creuse */

                lect_tab(T1,&lign1,&col1);
                affich_tab(T1,lign1);
                choix_mat_result(T1,lign1,col1,A,&lignA,&colA,B,&lignB,&colB,C,&lignC,&colC);

            break;

            default :
                printf("\n\t\t\tERREUR  !!!!\n"); goto case1;
            break;
            }

            Color(0,6);
            printf("\n\n\n\n\n\nLa complexite de l'algorithme du lecture est O ( nbr_lignes x nbr_collonnes ) . ");getch();

        break;

/****************************************************************************************************************************/
///--------------------------------importer une matrice depuis un fichier-----------------------------------------------------

        case 2:

            printf("\nEntrer le nom de fichier d'une matrice enregistr%ce : ",130);
            scanf("%s",name_file);

            file=fopen(name_file,"r+");


            ///----importer la matrice-----------
            if (file!=NULL)
            {
                fscanf(file,"%d",&lign1);  //importer le nombre de lignes
                fscanf(file,"%d",&col1);  //importer le nombre de collonnes

                for (i=0;i<lign1;i++)
                {
                    for (j=0;j<col1;j++)
                    {
                        fscanf(file,"%f",&M[i][j]);  //importer les valeurs des cases
                    }
                }
                fclose(file);

                affich_mat(M,lign1,col1);
                convert_t(M,T1,lign1,col1);
                choix_mat_result(T1,lign1,col1,A,&lignA,&colA,B,&lignB,&colB,C,&lignC,&colC);
            }
            else
            {
                printf("\n\n\t\t\t\tERREURE !! \n\n\t\t\tle fichier n'existe pas ...");
            }

            Color(0,6);
            printf("\n\n\n\n\nLa complexite de l'algorithme d'importation depuis un fichier est O ( nbr_ligne x nbr_collonnes ) . ");getch();

        break;

/****************************************************************************************************************************/
///------------------------------------------afficher une matrice---------------------------------------------------------------

        case 3:   case2:

            choix_mat_manipul(A,lignA,colA,B,lignB,colB,C,lignC,colC,T1,&lign1,&col1);
            printf("\nVoullez vous afficher :\n\n         1.Matrice plainne.\n\n         2.Matrice creuse.\n\n  Votre choix : ");scanf("%d",&choi);

            switch (choi)
            {
            case 1:  //plainne
                convert_m(T1,M,lign1,col1);
                affich_mat(M,lign1,col1);
                break;

            case 2:  //creuse
                affich_tab(T1,lign1);
                break;

            default :
                printf("\n\t\t\tERREUR  !!!!\n"); goto case2;
                break;
            }

            Color(0,6);
            printf("\n\n\n\n\n\nLa complexite de l'algorithme d'affichage est O ( nbr_lignes x nbr_collonnes ) . ");getch();

        break;

/****************************************************************************************************************************/
///-------------------------------la somme de deux matrices----------------------------------------------------------------

        case 4:
            ///choix de la première matrice

            printf("La premiere matrice : \n ");
            choix_mat_manipul(A,lignA,colA,B,lignB,colB,C,lignC,colC,T1,&lign1,&col1);
            convert_m(T1,M,lign1,col1);
            affich_mat(M,lign1,col1);

            ///choix de la deuxieme matrice

            printf("\nLa deuxieme matrice : \n ");
            choix_mat_manipul(A,lignA,colA,B,lignB,colB,C,lignC,colC,T2,&lign2,&col2);
            convert_m(T2,M,lign2,col2);
            affich_mat(M,lign2,col2);

                ///si elles ont la meme taille
            if ((lign1==lign2)&&(col1==col2))
            {
                somme(T1,T2,lign1,col1,T3);
                printf("\n\n- La somme des  matrices : \n\n");
                convert_m(T3,M,lign1,col1);
                affich_mat(M,lign1,col1);

                printf("\n- Voullez vous enregistrer le resultat dans une matrice (oui-->'o') : ");scanf("%s",&choi);
                if (choi=='o')
                {
                    choix_mat_result(T3,lign1,col1,A,&lignA,&colA,B,&lignB,&colB,C,&lignC,&colC);
                }
            }
            else
            {
                printf("\n\n\t\t\t\t ERREUR !! \n\n\t\t\t les deux matrices ont pas la meme taille \n");
            }

            Color(0,6);
            printf("\n\n\n\n\n\n\nLa complexite de l'algorithme de la somme est O ( nbr_lignes x max_collonnes_non_nule ) . ");getch();


        break;

/****************************************************************************************************************************/
///----------------------------------le produit de deux matrices--------------------------------------------------------------

        case 5:
            ///choix de la première matrice

            printf("La premiere matrice : \n ");
            choix_mat_manipul(A,lignA,colA,B,lignB,colB,C,lignC,colC,T1,&lign1,&col1);
            convert_m(T1,M,lign1,col1);
            affich_mat(M,lign1,col1);

            ///choix de la deuxieme matrice

            printf("\nLa deuxieme matrice : \n ");
            choix_mat_manipul(A,lignA,colA,B,lignB,colB,C,lignC,colC,T2,&lign2,&col2);
            convert_m(T2,M,lign2,col2);
            affich_mat(M,lign2,col2);

            if (col1!=lign2)
            {     printf("\n\n\t\t\t\t\tERREUR !!\n\n \t\t il faut que :   le nombre de collonnes de la premieres = le nombre de lignes de la deuxieme\n");}
            else
            {
                printf("\n\n- Le produit des  matrices : \n\n");
                prod(T1,T2,lign1,col1,lign2,col2,T3);
                convert_m(T3,M,lign1,col2);
                affich_mat(M,lign1,col2);

                printf("\n- Voullez vous enregistrer le resultat dans une matrice (oui-->'o') : ");scanf("%s",&choi);
                if (choi=='o')
                {
                    choix_mat_result(T3,lign1,col2,A,&lignA,&colA,B,&lignB,&colB,C,&lignC,&colC);
                }
            }

            Color(0,6);
            printf("\n\n\n\n\n\n\nLa complexite de l'algorithme du produit est O ( (nbr_lignes_1er_mat x nbr_collonnes_2eme_mat)%c ) . ",253);getch();

        break;

/****************************************************************************************************************************/
///-----------------------------produit par un scalair -------------------------------------------------------------------------

        case 6:

            choix_mat_manipul(A,lignA,colA,B,lignB,colB,C,lignC,colC,T1,&lign1,&col1);
            convert_m(T1,M,lign1,col1);
            affich_mat(M,lign1,col1);

            do
            {   printf("\n\n- Multiplier par le scalair : ");
                scanf("%f",&N);
            }while(N==0);

            prod_scal(T1,lign1,&N);

            convert_m(T1,M,lign1,col1);
            affich_mat(M,lign1,col1);

            printf("\n- Voullez vous enregistrer le resultat dans une matrice (oui-->'o') : ");scanf("%s",&choi);
            if (choi=='o')
            {
                choix_mat_result(T1,lign1,col1,A,&lignA,&colA,B,&lignB,&colB,C,&lignC,&colC);
            }

            Color(0,6);
            printf("\n\n\n\n\n\n\nLa complexite de l'algorithme du produit par un scalair est O ( nbr_lignes x nbr_collonnes ) . ");getch();

        break;

/****************************************************************************************************************************/
///-------------------------------la transposée ----------------------------------------------------------------------------------

        case 7:

            choix_mat_manipul(A,lignA,colA,B,lignB,colB,C,lignC,colC,T1,&lign1,&col1);
            convert_m(T1,M,lign1,col1);
            affich_mat(M,lign1,col1);

            printf("\n\nLa matrice transposee est : \n\n");
            transpos(T1,lign1,col1,T2);

            convert_m(T2,M,col1,lign1);
            affich_mat(M,col1,lign1);

            printf("\nVoullez vous enregistrer le resultat dans une matrice (oui-->'o') : ");scanf("%s",&choi);
            if (choi=='o')
            {
                choix_mat_result(T2,col1,lign1,A,&lignA,&colA,B,&lignB,&colB,C,&lignC,&colC);
            }

            Color(0,6);
            printf("\n\n\n\n\n\n\nLa complexite de l'algorithme de la transposee est O ( nbr_lignes x nbr_collonnes ) . ");getch();


        break;

/****************************************************************************************************************************/
///----------------------------------Determinant---------------------------------------------------------------------------

        case 8:

            choix_mat_manipul(A,lignA,colA,B,lignB,colB,C,lignC,colC,T1,&lign1,&col1);
            convert_m(T1,M,lign1,col1);
            affich_mat(M,lign1,col1);

            if(lign1==col1)
            {
                printf("\n\nLe determinant de cette matrice est :  %.2f \n",detr(T1,lign1));
            }
            else
            {
                printf("\n\n\t\t\t\tERREUR !!\n\n\t\t\tla matrice n'est pas carree");
            }

            Color(0,6);
            printf("\n\n\n\n\n\n\nLa complexite de l'algorithme du determinant est O ( (nbr_lignes x max_collonnes_non_nule%c)^(nbr_ligne-2) ) . ",253);getch();


        break;

/****************************************************************************************************************************/
///------------------------------matrice inverse---------------------------------------------------------------------------

        case 9:

            choix_mat_manipul(A,lignA,colA,B,lignB,colB,C,lignC,colC,T1,&lign1,&col1);
            convert_m(T1,M,lign1,col1);
            affich_mat(M,lign1,col1);

            if(lign1==col1)
            {
                if(detr(T1,lign1)==0)
                            { printf("\n\n\t\t\t\t\t  ERREUR !! \n\n\t\t\t\tLa matrice est singuliere (detr=0)\n");}
                else
                {
                    printf("\n\nLa matrice inverse est : \n\n");
                    invers(T1,lign1,col1,T2);
                    convert_m(T2,M,lign1,col1);
                    affich_mat(M,lign1,col1);

                    printf("\nVoullez vous enregistrer le resultat dans une matrice (oui-->'o') : ");scanf("%s",&choi);
                    if (choi=='o')
                    {
                        choix_mat_result(T2,lign1,col1,A,&lignA,&colA,B,&lignB,&colB,C,&lignC,&colC);
                    }
                }
            }
            else
            {
                printf("\n\n\t\t\t\tERREUR !!\n\n\t\t\tla matrice n'est pas carree");
            }

            Color(0,6);
            printf("\n\n\n\n\n\n\n  La complexite de l'algorithme de la matrice inverse est O ( (nbr_lignes)^4 ) . ");getch();


        break;

/****************************************************************************************************************************/
///------------------------résoudre un système d'équation basé sur une matrice creuse-----------------------------------------

        case 10:

            choix_mat_manipul(A,lignA,colA,B,lignB,colB,C,lignC,colC,T1,&lign1,&col1);

            if(lign1==col1)
            {
                convert_m(T1,M,lign1,col1);   //--just pour l'affichage
                affich_sys(M,lign1);

                invers(T1,lign1,col1,T3);      //T3 contient l'inverse de la matrice manipuler

                lect_vect(T2,lign1);        //lire le vecteur Y dans T2

                prod(T3,T2,lign1,col1,lign1,1,T1);      //-produit de l'inverse (T3) par le vecteur y (T2) -> la solution dans T1
                affich_sol_sys(T1,lign1);
            }
            else
            {
                printf("\n\n\t\t\t\t\tERREUR !!!\n\n\t\t\t\tLa matrice n'est pas carree\n");
            }

            Color(0,6);
            printf("\n\n\n\n\n\n\n  La complexite de l'algorithme de la resolution d'un systeme d'equation est O ( (nbr_lignes)^4 ) . ");getch();


        break;

/****************************************************************************************************************************/
///----------------------------------enregistrer une matrice--------------------------------------------------------------

        case 11:

            printf("\nQulle matrice voullez vous enregistrer ? ( A , B , C ) : ");
            scanf("%s",&choi);

            ///choix de matrice
            if(choi=='A')
            {
                lign1=lignA;col1=colA;
                convert_m(A,M,lign1,col1);
                affich_mat(M,lign1,col1);
            }
            else if (choi=='B')
            {
                lign1=lignB;col1=colB;
                convert_m(B,M,lign1,col1);
                affich_mat(M,lign1,col1);
            }
            else if (choi=='C')
            {
                lign1=lignC;col1=colC;
                convert_m(C,M,lign1,col1);
                affich_mat(M,lign1,col1);
            }

            ///--entrer le nom du fichier
            do
            {
                printf("\n\n\nEntrer le nom de fichier ou vous voullez enregistre la matrice (max 18car ): ");
                scanf("%s",name_file);

            }while(strlen(name_file)>18);

            file=fopen(name_file,"w+");


            ///----enregistrer la matrice-----------
            if (file!=NULL)
            {
                fprintf(file,"%d\n",lign1);  //enregistrer le nombre des lignes
                fprintf(file,"%d\n",col1);   //enregistrer le nombre des collonnes

                for (i=0;i<lign1;i++)
                {
                    for (j=0;j<col1;j++)
                    {
                        fprintf(file,"%.2f ",M[i][j]);  //enregistrer la valeur de chaque case
                    }
                }
                fclose(file);
            }
            printf("\n\n\t\tVotre matrice a %ct%c enregistr%ce %c %c.",130,130,130,1,2);

            Color(0,6);
            printf("\n\n\n\n\n\n\n  La complexite de l'algorithme de l'enregistrement dans un fichier est O ( nbr_lignes x nbr_collonnes ) . ");getch();


        break;

//-------------------------------------------------------------------------------------------------------------------------
        default :

            system("color f0");
            printf("\n\n\n\n\n\n\n\n\n\t\t\t\t\t   ERREUR !!!  \n\n\t\t\tVous avez pas entrer un choix parmis le MENU !!\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n");
            system("pause");

        break;

        }
    }



    return 0;
}


