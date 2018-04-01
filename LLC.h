#ifndef LLC_H_INCLUDED
#define LLC_H_INCLUDED
#include "type.h"
#include <math.h>
#define maxl 100


/**--------------------------------------lecture d'une matrice creuse----------------------------------------------**/

void lect_tab(type_tab t[maxl],int *l,int *c);
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////



/**--------------------------------------afficher une matrise creuse----------------------------------------------**/

void ecrire_llc(maillon *tete);           ///pour afficher une LLC d'une case
void affich_tab(type_tab t[maxl],int l);
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////



/**---------------------------------ordonner la liste selon les collonnes----------------------------------------------**/

void tri_bulle(maillon *tete);
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////



/**------------------------------convertir une matrice plainne donnée à une matrice creuse------------------------------------**/

void convert_t(float M[maxl][maxl],type_tab t[maxl],int l,int c);
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////



/**----------------------------------choisir la matrice dont l'utilisateur va manipuler------------------------------------**/

void affect_mat(type_tab t1[maxl],int l1,int c1,type_tab t2[maxl],int *l2,int *c2); ///affecter une matrice creuse à une autres

void choix_mat_manipul(type_tab A[maxl],int lA,int cA,type_tab B[maxl],int lB,int cB,type_tab C[maxl],int lC,int cC,type_tab T[maxl],int *l,int *c);

///--choisir la matrice dont laquelle on va enregistrer le résultat
void choix_mat_result(type_tab T[maxl],int l,int c,type_tab A[maxl],int *lA,int *cA,type_tab B[maxl],int *lB,int *cB,type_tab C[maxl],int *lC,int *cC);

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////




//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/****                                          CALCULE MATRICIEL                                                         ****/
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////





/****************************************************************************************************************************/
/**-----------------------------------------la somme de deux matrice--------------------------------------------------------**/

void somme(type_tab t1[maxl],type_tab t2[maxl],int l,int c,type_tab t3[maxl]);



/*********************************************************************************************************************************/
/**------------------------------------la recherche du maillon qui a la collonne j----------------------------------------------**/

void rech_col(maillon *tete,int j,maillon **prec,maillon **p,int *exist);



/****************************************************************************************************************************/
/**--------------------------------------------le produit de deux matrices-----------------------------------------------------**/

void prod(type_tab t1[maxl],type_tab t2[maxl],int l1,int c1,int l2,int c2,type_tab t3[maxl]);



/****************************************************************************************************************************/
/**----------------------------------------produit par un scalair---------------------------------------------------------------**/

void prod_scal(type_tab t[maxl],int l,float *N);



/****************************************************************************************************************************/
/**------------------------------------calculer la transposé d'une matrice donnée----------------------------------------------**/

void transpos(type_tab t1[maxl],int l ,int c,type_tab t2[maxl]);



/****************************************************************************************************************************/
/**-------------------------------------------le determinant----------------------------------------------------------------**/

void supp_col(maillon**tete,int col);   ///supprimer le maillon qui est dans la colonne (col)

void copy_llc(maillon *tet1,maillon **tet2);    ///copier une llc dans une autre

void decoup_m(type_tab t1[maxl],int tail,int l,int col,type_tab t2[maxl]);  ///decouper t1 en supprimant la ligne 'l' et la  colonne  (col)

float detr(type_tab t[maxl],int l); ///calcule du determinant




/****************************************************************************************************************************/
/**--------------------------------------------calculer la matrice inverse-----------------------------------------------------**/

void invers(type_tab T[maxl],int l,int col,type_tab T1[maxl]);














/*******************************************************************************************************************************/
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
///******************                               Debut des procedures                                    ******************///
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/*******************************************************************************************************************************/




/******************************************************************************************************************/
/**--------------------------------------lecture d'une matrice creuse----------------------------------------------**/

void lect_tab(type_tab t[maxl],int *l,int *c)
{
    int i,j;
    char conf;
    float val;
    maillon *prec=NULL,*p=NULL;

    printf("\n\n- Donner le nombre de lignes : ");scanf("%d",l);
    printf("\n\n- Donner le nombre de colonnes : ");scanf("%d",c);

    for (i=0;i<*l;i++)     /*--boucle pour parcourir le tableau t--*/
    {
        t[i].taille=0;
        t[i].llc=NULL;
        printf("\n\nEst ce que la ligne '%d' contient des element non nuls (oui-->'o'): ",i);
        scanf("%s",&conf);

        if ((conf=='o')||(conf=='O'))    /*--si la ligne contient des element non nuls--*/
        {
            allouer(&p);
            t[i].llc=p;

            while((conf=='o')||(conf=='O'))    /*--boucle pour lire les elements de LLC--*/
            {
                t[i].taille++;

                do
                {
                    printf("\n\t- Donner la colonne du valeur : ");  scanf("%d",&j);
                }while((j>*c)||(j<=0));   //si la colonne est plus grande q la taille ou elle est negative on repete
                aff_col(p,j);

                do
                {
                    printf("\t     M [ %d ][ %d ] = ",i,j); scanf("%f",&val);
                }while(val==0);  //--si la valeur (val)est nul on répète la demende
                aff_val(p,val);

                prec=p;
                allouer(&p);
                aff_adr(prec,p);

                printf("\n\tEst ce qu'il reste des elements non nuls dans la ligne: ");
                scanf("%s",&conf);
            }
            liberer(&p);
            aff_adr(prec,NULL);
        }
    }
}
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////




/******************************************************************************************************************/
/**--------------------------------------afficher une matrise creuse----------------------------------------------**/

///pour afficher une LLC d'une case

void ecrire_llc(maillon *tete)
{
    maillon *p;
    p=tete;
    while(p!=NULL)
    {
        printf("%c %d: %.2f %c",179,colonne(p),valeur(p),179);
        p=suivant(p);
    }
    printf("\n");
}

//----------------------------------------------------------

void affich_tab(type_tab t[maxl],int l)
{
    int i;
    for (i=0;i<l;i++)
    {
        printf("\n");
        printf("- Ligne n: %d \t- Taille: %d  ",i,t[i].taille);
        if (t[i].llc!=NULL)
        {
            printf("\t - LLC : ");
            ecrire_llc(t[i].llc);
        }
        else  {printf("\n");}
    }
}
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////





/*********************************************************************************************************************/
/**---------------------------------ordonner la liste selon les collonnes----------------------------------------------**/

void tri_bulle(maillon *tete)
{
    maillon *p;
    int trie=1,perm;

    while(trie)
    {
        trie=0;
        p=tete;
        while((p!=NULL)&&(suivant(p)!=NULL))    ///--pour parcourir llc
        {
            if (colonne(p)>colonne(suivant(p)))   ///si les deux elements sont pas ordonnes
            {
                perm=valeur(p)   ; aff_val(p,valeur(suivant(p)))  ; aff_val(suivant(p),perm);    ///--permuter les valeurs
                perm=colonne(p)   ; aff_col(p,colonne(suivant(p)))  ; aff_col(suivant(p),perm);  ///--permuter les colonnes
                trie=1;
            }
            p=suivant(p);
        }
    }

}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////





/****************************************************************************************************************************/
/**------------------------------convertir une matrice plainne donnée à une matrice creuse------------------------------------**/

void convert_t(float M[maxl][maxl],type_tab t[maxl],int l,int c)
{
    maillon *p=NULL,*prec=NULL;
    int i,j;

    for(i=0;i<l;i++)
    {
        p=NULL;
        t[i].llc=NULL;
        t[i].taille=0;

        for(j=0;j<c;j++)
        {
            if(M[i][j]!=0)   ///--si la valeur est non nul
            {
                t[i].taille++;
                allouer(&p);
                if (t[i].llc==NULL)  {t[i].llc=p;}       ///--si la liste llc est vide
                else                 {aff_adr(prec,p);}  ///--sinon
                aff_val(p,M[i][j]);
                aff_col(p,j+1);
                prec=p;
            }
        }
        if (t[i].llc!=NULL)    ///--si la liste n'est pas vide
        {
            aff_adr(prec,NULL);
        }
    }
}
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////





/****************************************************************************************************************************/
/**----------------------------------choisir la matrice dont l'utilisateur va manipuler------------------------------------**/

///affecter une matrice creuse à une autres

void affect_mat(type_tab t1[maxl],int l1,int c1,type_tab t2[maxl],int *l2,int *c2)
{
    int i;
    *l2=l1;
    *c2=c1;
    for (i=0;i<l1;i++)
    {
        t2[i].llc=t1[i].llc;
        t2[i].taille=t2[i].taille;
    }
}

//-----------------------------------------------------------------------------

void choix_mat_manipul(type_tab A[maxl],int lA,int cA,type_tab B[maxl],int lB,int cB,type_tab C[maxl],int lC,int cC,type_tab T[maxl],int *l,int *c)
{
    char choi;
    choix:
    printf("\nQuelle matrice voullez vous travailler avec ( A , B , C ) : ");scanf("%s",&choi);
    if(choi=='A')
    {
        affect_mat(A,lA,cA,T,l,c);
    }
    else if (choi=='B')
    {
        affect_mat(B,lB,cB,T,l,c);
    }
    else if (choi=='C')
    {
        affect_mat(C,lC,cC,T,l,c);
    }
    else
    {
        printf("\n\t  ERREUR !!\n");goto choix;
    }
}

//----------------------------------------------------------------------------

///--choisir la matrice dont laquelle on va enregistrer le résultat

void choix_mat_result(type_tab T[maxl],int l,int c,type_tab A[maxl],int *lA,int *cA,type_tab B[maxl],int *lB,int *cB,type_tab C[maxl],int *lC,int *cC)
{
    char choi;
    choix:
    printf("\nVoullez vous affecter le resultat dans ( A , B , C ) : ");scanf("%s",&choi);
    if(choi=='A')
    {
        affect_mat(T,l,c,A,lA,cA);
    }
    else if (choi=='B')
    {
        affect_mat(T,l,c,B,lB,cB);
    }
    else if (choi=='C')
    {
        affect_mat(T,l,c,C,lC,cC);
    }
    else
    {
        printf("\n\t  ERREUR !!\n");goto choix;
    }
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////







//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/****************************************************************************************************************************/
/****                                          CALCULE MATRICIEL                                                         ****/
/****************************************************************************************************************************/
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////



/****************************************************************************************************************************/
/**-----------------------------------------la somme de deux matrice--------------------------------------------------------**/

void somme(type_tab t1[maxl],type_tab t2[maxl],int l,int c,type_tab t3[maxl])
{
    maillon *p1,*p2,*p3=NULL,*prec3;
    int i;

    for (i=0;i<l;i++)    ///--pour parcourir les lignes du tableau
    {
        p1=t1[i].llc;    ///--pour chaque ligne on initialise p1 et p2 à la tete de LLC 1 et 2
        p2=t2[i].llc;
        prec3=NULL;      ///--pour chaque ligne les maillons du tableau resultat (t3) sont intialisé à NULL
        t3[i].llc=NULL;
        t3[i].taille=0;

        while ((p1!=NULL)&&(p2!=NULL))   /// une boucle qui parcoure les deux listes à la fois
        {
            if (t3[i].llc==NULL)  {  allouer(&p3);  t3[i].llc=p3; }           /// si llc du tableau somme(t3) est vide
            else                  {  aff_adr(prec3,p3); }

            if (colonne(p1)==colonne(p2))     /// si les deux valeurs sont dans la meme colonne
            {
                aff_col(p3,colonne(p1));
                aff_val(p3,valeur(p1)+valeur(p2));
                p1=suivant(p1);
                p2=suivant(p2);
            }
            else if (colonne(p1)<colonne(p2))       /// sinon les deux valeurs sont dans des colonnes différentes alors on les insert par ordre de colonnes
            {
                aff_col(p3,colonne(p1));
                aff_val(p3,valeur(p1));
                p1=suivant(p1);
            }
            else  if (colonne(p1)>colonne(p2))      /// colonne(p1) > colonne(p2)
            {
                aff_col(p3,colonne(p2));
                aff_val(p3,valeur(p2));
                p2=suivant(p2);
            }
            t3[i].taille++;
            prec3=p3;
            allouer(&p3);
        }
        ///maintenant le parcour d'une des listes est terminé , ou les deux sont terminé à la fois


        if ((p1==NULL)&&(p2!=NULL))       /// si le parcour du la première liste est terminé et du la deuxéme n'est pas encore fini
        {
            while (p2!=NULL)      ///copier le reste de t2[i].llc dans t3[i].llc
            {
                if (t3[i].llc==NULL)  {  allouer(&p3);  t3[i].llc=p3; }
                else                  {  aff_adr(prec3,p3); }
                aff_col(p3,colonne(p2));
                aff_val(p3,valeur(p2));
                p2=suivant(p2);
                prec3=p3;
                t3[i].taille++;
                allouer(&p3);
            }

        }
        else if ((p2==NULL)&&(p1!=NULL))   /// si le parcour du la deuxième liste est terminé et du la première n'est pas encore fini
        {
            while (p1!=NULL)      ///copier le reste de t1[i].llc dans t3[i].llc
            {
                if (t3[i].llc==NULL)  {  allouer(&p3);  t3[i].llc=p3; }
                else                  {  aff_adr(prec3,p3); }
                aff_col(p3,colonne(p1));
                aff_val(p3,valeur(p1));
                p1=suivant(p1);
                prec3=p3;
                t3[i].taille++;
                allouer(&p3);
            }
        }
        if (prec3!=NULL)              /// si le parcour des deux listes est terminé. //prec3!=NULL : pour éviter un cas particulié qui se pose si les deux llc sont vides
        {
            aff_adr(prec3,NULL);
            liberer(&p3);
        }
    }
}
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////





/*********************************************************************************************************************************/
/**------------------------------------la recherche du maillon qui a la collonne j----------------------------------------------**/

void rech_col(maillon *tete,int j,maillon **prec,maillon **p,int *exist)
{
    *p=tete;  *exist=0  ;  *prec=NULL;

    while((*exist==0)&&(*p!=NULL))
    {
        if (colonne(*p)==j)        {  *exist=1; }
        else
        {
            *prec=*p;
            *p=suivant(*p);
        }
    }
}
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////





/*******************************************************************************************************************************/
/**--------------------------------------------le produit de deux matrices-----------------------------------------------------**/

void prod(type_tab t1[maxl],type_tab t2[maxl],int l1,int c1,int l2,int c2,type_tab t3[maxl])
{
    maillon *p1=NULL,*p2,*p3,*prec3,*prec2;
    int i,j,exist;
    float val;


    for (i=0;i<l1;i++)      ///la boucle qui parcourie les lignes de tableau t3 (tableau de resultat)
    {
        t3[i].llc=NULL;     //chaque ligne contient une llc vide au depart
        prec3=NULL;
        t3[i].taille=0;

        for(j=1;j<=c2;j++)     ///parcourir les collonnes de t3
        {
            p1=t1[i].llc;
            val=0;

            while (p1!=NULL)  ///parcourir les collonnes de ligne i du tableau t1
            {
                rech_col(t2[colonne(p1)-1].llc,j,&prec2,&p2,&exist);  ///rechercher s'il existe une valeur dans t2 dont laquelle on va multiplier
                if (exist)   //si elle existe
                {
                    val=val+valeur(p1)*valeur(p2);
                }
                p1=suivant(p1);
            }

            if(val!=0)          ///si la valeur est non nul on va l'affecter dans p3
            {
                if(t3[i].llc==NULL)  {allouer(&p3);  t3[i].llc=p3; }  //si la tete n'est pas encore initialisée
                else        {aff_adr(prec3,p3);}
                aff_val(p3,val);
                aff_col(p3,j);
                prec3=p3;
                t3[i].taille++;
                allouer(&p3);
            }
        }

        if(prec3!=NULL)    ///llc de la ligne i est terminée
        {
            aff_adr(prec3,NULL);
            liberer(&p3);
        }
    }
}
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////





/*******************************************************************************************************************************/
/**----------------------------------------produit par un scalair---------------------------------------------------------------**/

void prod_scal(type_tab t[maxl],int l,float *N)
{
    int i;
    maillon *p;

    for(i=0;i<l;i++)  ///parcourir le tableau
    {
        p=t[i].llc;

        while (p!=NULL)   ///parcourir llc
        {
            aff_val(p,valeur(p)*(*N));
            p=suivant(p);
        }
    }
}
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////





/*******************************************************************************************************************************/
/**------------------------------------calculer la transposé d'une matrice donnée----------------------------------------------**/

void transpos(type_tab t1[maxl],int l ,int c,type_tab t2[maxl])
{
    maillon *p1,*p2,*prec2;
    int i;

    for(i=0;i<c;i++)    ///pour intialisé tous les cases à 0
    {
        t2[i].llc=NULL;
        t2[i].taille=0;
    }

    for (i=0;i<l;i++)    ///boucle pour parcourir le tableau donné (t1)
    {
        p1=t1[i].llc;
        while (p1!=NULL)     ///parcour de llc de chaque ligne
        {
            allouer(&p2);
            if (t2[colonne(p1)-1].llc==NULL)    {t2[colonne(p1)-1].llc=p2;}    ///si la tete de llc est encore vide
            else
            {
                prec2=t2[colonne(p1)-1].llc;
                while(suivant(prec2)!=NULL)    {prec2=suivant(prec2);}   ///llc contient deja des maillon alors on va renvoyer le dernier maillon
                aff_adr(prec2,p2);
            }
            ///affecter la valeur de p1 de tableau t1 dans sa place dans le tableau de transposé t2
            t2[colonne(p1)-1].taille++;
            aff_col(p2,i+1);
            aff_val(p2,valeur(p1));
            prec2=p2;
            aff_adr(prec2,NULL);
            p1=suivant(p1);
        }
    }
}
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////






/****************************************************************************************************************************/
/**-------------------------------------------le determinant----------------------------------------------------------------**/

//-------------------------------------------------------------
///supprimer le maillon qui est dans la colonne (col)

void supp_col(maillon**tete,int col)
{
    maillon *prev,*p;
    int trouv;

    rech_col(*tete,col,&prev,&p,&trouv);
    if (trouv)   //si la colonne existe alors
    {
        if (p==*tete) {*tete=suivant(p);} //si la colonne est dans la tete de la liste
        else       {aff_adr(prev,suivant(p));}
        liberer(&p);
    }

}


//----------------------------------------------------------
///copier une llc dans une autre

void copy_llc(maillon *tet1,maillon **tet2)
{
    maillon *p,*prec=NULL,*q;
    *tet2=NULL;
    q=tet1;

    while (q!=NULL)  //tant que la 1er liste n'est pas encore terminée
    {
        allouer(&p);
        if (*tet2==NULL)    {*tet2=p;}
        else       {aff_adr(prec,p);}
        aff_col(p,colonne(q));
        aff_val(p,valeur(q));
        prec=p;
        q=suivant(q);
    }
    if (prec!=NULL)   {aff_adr(prec,NULL);}
}


//------------------------------------------------------------------
///decouper t1 en supprimant la ligne 'l' et la  colonne  (col)

void decoup_m(type_tab t1[maxl],int tail,int l,int col,type_tab t2[maxl])
{
    int i;
    maillon *p;
    for(i=0;i<tail;i++)
    {
        copy_llc(t1[i].llc,&t2[i].llc);
        supp_col(&t2[i].llc,col);          //pour supprimer la colonne

        p=t2[i].llc;
        while(p!=NULL)    //pour decrémenté la colonne de chaque élément qui est après la valeur supprimée
        {
            if(colonne(p)>col)
            {
                aff_col(p,colonne(p)-1);
            }
            p=suivant(p);
        }

        if (i>l)    {t2[i-1].llc=t2[i].llc;}//pour supprimer la  ligne l
    }
}


//--------------------------------------------------------------------
///calcule du determinant

float detr(type_tab t[maxl],int l)
{
    maillon *p,*q;
    type_tab t2[maxl];
    float det=0;

    p=t[0].llc;
    while((p!=NULL)&&(l>2))    ///tant que la matrice est plus grande q 2x2 :on va parcourir la 1er ligne pour calculer le detr
    {
        decoup_m(t,l,0,colonne(p),t2);
        det=det+(valeur(p)*(detr(t2,l-1))*(pow((-1),colonne(p)+1))); ///c'est la forme du detr . //on va utilisé la récursivité
        p=suivant(p);
    }

    if ((p!=NULL)&&(l==2))   ///si la matrice est du taille 2x2
    {
        q=t[1].llc;
        if (q!=NULL)   //les différantes conditions pour calculer le detr d'une matrice 2x2
        {
            if((colonne(p)==1)&&(colonne(q)==2))
                                               { det=det+valeur(p)*valeur(q);  }
            else if ((colonne(p)==1)&&(suivant(q)!=NULL))
                                               { det=det+valeur(p)*valeur(suivant(q));  }

            if((colonne(p)==2)&&(colonne(q)==1))
                                                { det=det-valeur(p)*valeur(q);  }
            else if ((suivant(p)!=NULL)&&(colonne(q)==1))
                                                { det=det-valeur(suivant(p))*valeur(q);  }

        }
    }
    return det;
}
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////





/*******************************************************************************************************************************/
/**--------------------------------------------calculer la matrice inverse-----------------------------------------------------**/

void invers(type_tab T[maxl],int l,int col,type_tab T1[maxl])
{
    type_tab t2[maxl],t3[maxl];
    int i,j;
    float inv_det;
    maillon *p,*q;


//-------
    if(l>2) ///si la matrice est grande
    {
        for (i=0;i<l;i++)  ///on va parcourir T
        {
            t2[i].llc=NULL;

            for (j=1;j<=col;j++)
            {
                decoup_m(T,l,i,j,t3); ///c'est une méthode pour construire la matrice inverse :
                ///on va éléminé la ligne i et la colonne de (p) puis on calcule le determinant de la matrice obtenue et on range le résultat dans t2

                allouer(&p);
                if(t2[i].llc==NULL)  {t2[i].llc=p;}
                else                {aff_adr(q,p);}
                aff_col(p,j);
                aff_val(p,(detr(t3,l-1))*(pow((-1),(i+j+1))));
                q=p;
            }
            aff_adr(p,NULL);
        }

        transpos(t2,l,l,T1);       ///la transposée de t2 dans T
    }

    else if (l==2) ///si la taille du matrice est 2x2
    {
        T1[0].llc=NULL;  T1[1].llc=NULL;  //initialiser la matrice résult

        p=T[0].llc;
        while(p!=NULL)      ///parcourir la 1er ligne
        {
            allouer(&q);
            if(colonne(p)==1)       ///permuter T[1][1] et T[2][2]
            {
                aff_adr(q,T1[1].llc);
                T1[1].llc=q;
                aff_val(q,valeur(p));
                aff_col(q,2);
            }
            else if(colonne(p)==2)      ///affecter la valeur de T[1][2] en négative
            {
                aff_adr(q,T1[0].llc);
                T1[0].llc=q;
                aff_val(q,-valeur(p));
                aff_col(q,2);
            }
            p=suivant(p);
        }

        p=T[1].llc;
        while(p!=NULL)      ///parcourir la 2ème ligne
        {
            allouer(&q);
            if(colonne(p)==1)     ///affecter la valeur de T[2][1] en négative
            {
                aff_adr(q,T1[1].llc);
                T1[1].llc=q;
                aff_val(q,-valeur(p));
                aff_col(q,1);
            }
            else if(colonne(p)==2)    ///permuter T[1][1] et T[2][2]
            {
                aff_adr(q,T1[0].llc);
                T1[0].llc=q;
                aff_val(q,valeur(p));
                aff_col(q,1);
            }
            p=suivant(p);
        }

        tri_bulle(T1[0].llc);
        tri_bulle(T1[1].llc);
    }
//--------

inv_det=1/detr(T,l);

prod_scal(T1,l,&inv_det);   ///produit scalair de T1 par 1/det

}
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////





/*******************************************************************************************************************************/
/**--------------------------------------------affichage du systeme d'équation-----------------------------------------------------**/

void affich_sys(float M[maxl][maxl],int tail)    ///afficher le système d'équation à résoudre
{
    int i,j,x,y;

    printf("\n\t\t\tM\tx\tX\t=\tY\n\n\n\t%c",218);
    for(j=0;j<tail;j++)
    {
        printf("  %.2f  ",M[0][j]);
    }
    printf("%c",191);
    printf("\t%c  X0  %c\t\t%c  b0  %c\n",218,191,218,191);

    for(i=1;i<tail-1;i++)
    {
        printf("\t%c",179);
        for(j=0;j<tail;j++)
        {
            printf("  %.2f  ",M[i][j]);
        }
        x=wherex()+22;
        printf("%c\t%c  X%d  %c\t\t%c  b%d  %c\n",179,179,i,179,179,i,179);
    }

    printf("\t%c",192);
    for(j=0;j<tail;j++)
    {
        printf("  %.2f  ",M[tail-1][j]);
    }
    printf("%c",217);
    printf("\t%c  X%d  %c\t\t%c  b%d  %c\n\n\n",192,tail-1,217,192,tail-1,217);

    y=wherey()-(tail/2)-3;
    gotoxy(x,y);
    printf("=");
    y=y+tail;
    gotoxy(1,y);

}



//------------------------------------------------------------------

void lect_vect(type_tab Y[maxl],int tail)   ///lecture du vecteur Y
{
    int i;
    float val;

    printf("\n\n-Donnez le vecteur  Y  : \n");
    for(i=0;i<tail;i++)
    {
        printf("\n\t\t- b%d = ",i);
        scanf("%f",&val);
        if(val!=0)
        {
            allouer(&Y[i].llc);
            aff_val(Y[i].llc,val);
            aff_adr(Y[i].llc,NULL);
            aff_col(Y[i].llc,1);
            Y[i].taille=1;
        }
        else
        {
            Y[i].llc=NULL;
            Y[i].taille=0;
        }
    }
}


//----------------------------------------------------------

void affich_sol_sys(type_tab X[maxl],int tail)  ///afficher la solution du système
{
    int i;

    printf("\n\n\n-La solution du systeme : \n");
    for(i=0;i<tail;i++)
    {
        if(X[i].llc!=NULL)
            { printf("\n\t\t- X%d = %.2f\n",i,valeur(X[i].llc));}
        else
            { printf("\n\t\t- X%d = %.2f\n",i,0.00);}
    }
}
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


#endif // LLC_H_INCLUDED
