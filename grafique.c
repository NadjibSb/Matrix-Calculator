#include <windows.h>
#include <string.h>



/*
Color Codes:
0 = Black
1 = Blue
2 = Green
3 = Aqua
4 = Red
5 = Purple
6 = Yellow
7 = White
8 = Gray
9 = Light Blue
A = Light Green
B = Light Aqua
C = Light Red
D = Light Purple
E = Light Yellow
F = Bright White
*/


void Color(int couleurDuTexte,int couleurDeFond) // fonction d'affichage des couleurs
{
        HANDLE H=GetStdHandle(STD_OUTPUT_HANDLE);
        SetConsoleTextAttribute(H,couleurDeFond*16+couleurDuTexte);
}


/*------------------------------------------------------------------------------------------------------------------------------*/
void textcolor(unsigned int color)
{
    if (color >15 || color <=0)
    {
        HANDLE hcon = GetStdHandle(STD_OUTPUT_HANDLE);
        SetConsoleTextAttribute(hcon,15);

    }
    else
    {
        HANDLE hcon = GetStdHandle(STD_OUTPUT_HANDLE);
        SetConsoleTextAttribute(hcon,color);
    }
}



/*-----------------------------------------------------------------------------------------------------------------------------*/
void textbackground(int bcolor)
{
     WORD wColor;
     //We will need this handle to get the current background attribute
     HANDLE hStdOut = GetStdHandle(STD_OUTPUT_HANDLE);
     CONSOLE_SCREEN_BUFFER_INFO csbi;

     //We use csbi for the wAttributes word.
     if(GetConsoleScreenBufferInfo(hStdOut, &csbi))
     {
        //make a color form the current backgound and our forground color
          wColor = (csbi.wAttributes & 0xF) | ((bcolor  << 4 ) & 0xF0);
          SetConsoleTextAttribute(hStdOut, wColor);

     }
}


/*-----------------------------------------------------------------------------------------------------------------------------*/
int wherex()
{
        CONSOLE_SCREEN_BUFFER_INFO coninfo;

        GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &coninfo);
        return coninfo.dwCursorPosition.X+1;
}


/*-----------------------------------------------------------------------------------------------------------------------------*/
int wherey()
{
        CONSOLE_SCREEN_BUFFER_INFO coninfo;

        GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &coninfo);
        return coninfo.dwCursorPosition.Y;
}


/*-----------------------------------------------------------------------------------------------------------------------------*/
void gotoxy(int xpos, int ypos)
{
        COORD scrn;
        HANDLE hOuput = GetStdHandle(STD_OUTPUT_HANDLE);

        scrn.X = xpos-1;
        scrn.Y = ypos;
        SetConsoleCursorPosition(hOuput, scrn);
}


/*-----------------------------------------------------------------------------------------------------------------------------*/


/*******************************************************************************************************************************/
void MENU(int *choix)
{
    system("mode con lines=50 cols=120");
    system("cls");
    system("color 7f");
    Color(0,7);
    Sleep(100);



    printf("\n\n\n\n\n");
    printf("    %c%c%c%c%c%c%c  %c%c%c%c%c%c  ",219,219,219,219,219,219,219,219,219,219,219,219,219);
    Color(9,7);printf("%c%c\n",223,223);Color(0,7);
    printf("    %c%c       %c%c      %c%c\n",219,219,219,219,219,219);
    printf("    %c%c       %c%c      %c%c\n",219,219,219,219,219);
    printf("    %c%c%c%c%c%c%c  %c%c%c%c%c%c  %c%c\t\t\t\t\t\t",219,219,219,219,219,219,219,219,219,219,219,219,219,219,219);
    Color(15,3);
    printf(" TP -1- \n");
    Color(0,7);
    printf("    %c%c           %c%c  %c%c\t\t\t\t",219,219,219,219,219,219);
    Color(15,3);
    printf(" IMPLEMENTATION DES MATRICES CREUSES \n");
    Color(0,7);
    printf("    %c%c           %c%c  %c%c\t\t\t\t%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c\n",219,219,219,219,219,219,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205);
    printf("    %c%c%c%c%c%c%c  %c%c%c%c%c%c  %c%c\n\n\n\n\n\n\n\n\n",219,219,219,219,219,219,219,219,219,219,219,219,219,219,219);
    Color(0,7);
    Sleep(600);

    printf("\t 1.initialiser une matrice.\n\n");
    Sleep(300);
    printf("\t 2.Importer une matrice.\n\n");
    Sleep(300);
    printf("\t 3.afficher une matrice.\n\n");
    Sleep(300);
    printf("\t 4.La somme de deux  matrices.\n\n");
    Sleep(300);
    printf("\t 5.Le produit de deux matrices.\n\n");
    Sleep(300);
    printf("\t 6.Le produit d'une matrice par un scalair.\n\n");
    Sleep(300);
    printf("\t 7.La transposee d'une matrice.\n\n");
    Sleep(300);
    printf("\t 8.Calculer le determinant d'une matrice.\n\n");
    Sleep(300);
    printf("\t 9.L'inverse d'une matrice.\n\n");
    Sleep(300);
    printf("\t 10.Resoudre un systeme d'equation base sur une matrice creuse.\n\n");
    Sleep(300);
    printf("\t 11.Enregistrer une matrice.\n\n");
    Sleep(300);
    printf("\t 0.sortir.\n");
    Sleep(500);

    printf("\n\n\n\t\t");
    Color(6,7);
    printf("Choisissez un choix parmis le MENU : ");
    scanf("%d",choix);

    system("cls");
    system("color 4f");
}
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


/*******************************************************************************************************************************/
void debut()
{
    system("mode con lines=40 cols=110");
    system("color f9");
    printf("\n\n\n\n");

    printf("\t ******************************                  **********      **        **************\n");
    Sleep(100);
    printf("\t *******************************             ****************** ***        ***************\n");
    Sleep(100);
    printf("\t     ****** ********************           *******       ***********           *******\n");
    Sleep(100);
    printf("\t      *****                 *****         *****              *******            *****\n");
    Sleep(100);
    printf("\t      *****                   ****        ****                 ******           *****\n");
    Sleep(100);
    printf("\t      *****                    ***       *****                  *****           *****\n");
    Sleep(100);
    printf("\t      *****          ***        **       ******                   ***           *****\n");
    Sleep(100);
    printf("\t      *****          ***                  *******                  **           *****\n");
    Sleep(100);
    printf("\t      *****         ****                  ***********                           *****\n");
    Sleep(100);
    printf("\t     ******        *****                    ***************                     *****\n");
    Sleep(100);
    printf("\t     *******************                      *****************                 *****\n");
    Sleep(100);
    printf("\t     *******************                         ******************             *****\n");
    Sleep(100);
    printf("\t     ******        *****                               **************           *****\n");
    Sleep(100);
    printf("\t      *****         ****                                     *********          *****\n");
    Sleep(100);
    printf("\t      *****          ***                ****                    *******         *****\n");
    Sleep(100);
    printf("\t      *****          ***         ***    ****                     ******         *****\n");
    Sleep(100);
    printf("\t      *****                     ****     ****                     *****         *****\n");
    Sleep(100);
    printf("\t      *****                    ****      ******                   *****         *****\n");
    Sleep(100);
    printf("\t      *****                  ******       ******                 *****          *****\n");
    Sleep(100);
    printf("\t     ******                *******        *********            ******          *******\n");
    Sleep(100);
    printf("\t ** *****************************         **** *********************       **************\n");
    Sleep(100);
    printf("\t ********************************         ***    ****************          ***************\n");
    Sleep(100);
    printf("\t **\n");
    Sleep(100);
    printf("\n\n\n\n\n\n\n\n\n\n");
    system("PAUSE");
}
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////



/********************************************************************************************************************************/
void EXIT()
{
    system("cls");
    system("color 0f");
    int i;
    char chain[50]="MERCI d'avoir utilise notre programme ";

    textcolor(10);
    gotoxy(1,5);
    printf("\t*****           *****      ***************       *** *******              ***********       ******* \n");
    Sleep(100);
    printf("\t *****         *****        ***************      *****      ***         **************        ***   \n");
    Sleep(100);
    printf("\t *** **       ** ***        ***                  ***         ***       ***                    ***   \n");
    Sleep(100);
    printf("\t ***  **     **  ***        ***                  ***          **      ***                     ***  \n");
    Sleep(100);
    printf("\t ***   **   **   ***        ***                  ***         ***      ***                     ***   \n");
    Sleep(100);
    printf("\t ***    ** **    ***       **************        ***        ***       ***                     ***    \n");
    Sleep(100);
    printf("\t ***     ***     ***       **************        ************         ***                     ***   \n");
    Sleep(100);
    printf("\t ***    *****    ***        ***                  *** ******           ***                     ***   \n");
    Sleep(100);
    printf("\t ***             ***        ***                  ***    ***           ***                     ***  \n");
    Sleep(100);
    printf("\t ***             ***        ***                  ***      ***          ***                    ***   \n");
    Sleep(100);
    printf("\t ***             ***        ***************      ***        ***         **************        *** \n");
    Sleep(100);
    printf("\t*****           *****      ***************      *****        *****        ***********        *****   \n");


    Sleep(300);
    gotoxy(35,20);
    for(i=0;i<strlen(chain);i++)
    {
        printf("%c",chain[i]);
        Sleep(20);
    }

    Sleep(1000);
    textcolor(13);
    gotoxy(45,30);
    printf("*  SEMESTRE -2- TP1  *");
    textcolor(9);
    gotoxy(20,36);
    printf("- Section B  ; G06");
    gotoxy(20,38);
    printf("- Encadr%c par : CHARABI.L ",130);

    gotoxy(70,35);
    textcolor(11);
    printf("r%calis%c par :",130,130);
    gotoxy(80,38);
    textcolor(12);
    printf("- SOUAB NADJIB");
    gotoxy(80,40);
    printf("- KHIARI OKBA");
    printf("\n\n");

    textcolor(0);
    gotoxy(1,45);

}

