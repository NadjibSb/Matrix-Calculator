#ifndef TYPE_H_INCLUDED
#define TYPE_H_INCLUDED


//---------------------------------------------------------------------


typedef struct  maillon
{
    int col;
    float val;
     struct maillon *next;
}maillon;



typedef struct type_tab
{
    int taille;
    struct maillon *llc;
}type_tab;


//-----------------------------------------------------------------------


void allouer (maillon **nouveau);

void liberer(maillon **ancien);

void aff_adr(maillon *p,maillon *q);

void aff_val(maillon *p,float valeur);

void aff_col(maillon*p,int j);

maillon *suivant(maillon *p);

float valeur(maillon *p);

int colonne(maillon*p);


//----------------------------------------------------------------


void allouer (maillon **nouveau)
{
    *nouveau = (maillon*)malloc(sizeof(maillon));
}


void liberer(maillon **ancien)
{
    free(*ancien) ; *ancien=NULL;
}


void aff_adr(maillon *p,maillon *q)
{
    p->next=q;
}


void aff_val(maillon *p,float valeur)
{
    p->val=valeur;
}


void aff_col(maillon*p,int j)
{
    p->col=j;
}


maillon *suivant(maillon *p)
{
    return p->next;
}


float valeur(maillon *p)
{
    return p->val;
}


int colonne(maillon*p)
{
    return p->col ;
}



#endif // TYPE_H_INCLUDED
