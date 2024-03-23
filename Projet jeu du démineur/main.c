// codé par FLorent B
// ESGIS Benin projet c avancée

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>

char JEU[8][8];//grille de jeu 
int i,j;//i les lignes, j les colonnes
int x,y;//x les ligne des mines, y les colonnes des mines
char MINES[8][8];//la grille avec les mines
int N;//Nombre de mines autour
int NbMines; // Nombre total de mines
int MinesMarquees = 0; // Nombre de mines marquées par le joueur


// Fonction pour afficher le temps écoulé
void AfficherTempsEcoule(time_t debut) {
    time_t maintenant = time(NULL);
    int temps_ecoule = maintenant - debut;
    printf("Temps écoulé : %d secondes\n", temps_ecoule);
}


// Fonction pour effacer l'écran
void effacerEcran() {
    system("cls||clear");
}
////////////////////////////////////////
// FONCTION AFFICHER LA GRILLE DE JEU //
////////////////////////////////////////
void AfficheJeu()
{
     printf("     0    1    2    3    4    5    6    7  \n");
     printf("   ________________________________________\n");
     for(i=0;i<8;i++) {
        printf(" %d | ", (i));
        for(j=0;j<8;j++) {                
            printf("%c  | ",JEU[i][j]);
        }
        printf("\n");
    }
}
/////////////////////////////////////////////
// FONCTION CALCULER LE NB DE MINES AUTOUR //
/////////////////////////////////////////////
int NbMinesAutour()
{
    N=0;
    if ((i - 1) > -1 && (j - 1) > -1 && MINES[i - 1][j - 1] == 'M')
        N++;
    if ((i - 1) > -1 && MINES[i - 1][j] == 'M')
        N++;
    if ((i - 1) > -1 && (j + 1) < 8 && MINES[i - 1][j + 1] == 'M')
        N++;
    if ((j - 1) > -1 && MINES[i][j - 1] == 'M')
        N++;
    if ((j + 1) < 8 && MINES[i][j + 1] == 'M')
        N++;
    if ((i + 1) < 8 && (j - 1) > -1 && MINES[i + 1][j - 1] == 'M')
        N++;
    if ((i + 1) < 8 && MINES[i + 1][j] == 'M')
        N++;
    if ((i + 1) < 8  && (j + 1) < 8 && MINES[i + 1][j + 1] == 'M')
        N++;
    return(N);
    }               

void discoveur()
{
    int savei = i;
    int savej = j;

    NbMinesAutour();
    if (N != 0) {
        JEU[i][j]= N + 48;
        return;
    } else {
        if (MINES[i][j] == 'M')
            return;
        JEU[i][j]='0';
        i -= 1;
        if (i > -1) {
            j -= 1;
            if (j > -1 && JEU[i][j] == 'O')
                discoveur();
            j += 1;
            if (JEU[i][j] == 'O')
                discoveur();
            j += 1;
            if (j < 10 && JEU[i][j] == 'O')
                discoveur();
        }
        i += 1;
        j = savej - 1;
        if (j > -1 && JEU[i][j] == 'O')
                discoveur();
        j = savej + 1;
        if (j < 10 && JEU[i][j] == 'O')
                discoveur();
        i += 1;
        if (i < 10) {
            j = savej - 1;
            if (j > -1 && JEU[i][j] == 'O')
                discoveur();
            j += 1;
            if (JEU[i][j] == 'O')
                discoveur();
            j += 1;
            if (j < 10 && JEU[i][j] == 'O')
                discoveur();
        }
    }
    i = savei;
    j = savej;
}

int check_win(int NbMines)
{
    int compte = 0;

    for (int x = 0; x < 8; x++)
        for (int y = 0; y < 8; y++)
            if (JEU[x][y] == 'O' || JEU[x][y] == 'D')
                compte += 1;
    if (compte == NbMines)
        return 1;
    return 0;
}

int main()
{
        int NbMines;//le nombre de mines choisi par le joueur
        int CompteMines = 0;//compteur de mines
        int choix;//le choix effectué par le joueur pour découvrir ou placer un drapeau
        int rep; // boucle pour recommencer


            printf("Bienvenue dans le jeu du déminineur:)\n\n\n");
            printf("Codé par Florent B. :)\n\n\n");
            sleep(3);
            
        do
        {
            effacerEcran();
            srand(time(NULL));       
            //Afficher le début du jeu
            printf(" ________________________________\n");
            printf("|                                |\n");
            printf("|        Jeu du demineur         |\n");
            printf("|________________________________|\n\n");
            //initialisation des deux grilles
            for(i=0;i<8;i++) {
                for(j=0;j<8;j++) {
                    JEU[i][j]=' ';//' 'implique case cachée
                    MINES[i][j]='0';
                }           
            }
            //demander à l'utilisateur de choisir un nombre de mines
            do  {
                    printf("\nCombien de mines voulez-vous [8 , 12] ?\n\n");
                    scanf("%d",&NbMines);
            }
            while(NbMines>=13 || NbMines<=7);
            printf("D'accord, vous avez choisi de jouer avec %d mines",NbMines);
            ////////////////////////////
            // Démarrage de la partie //
            ////////////////////////////
            //On affiche le jeu au joueur
            printf("\n\nVoici votre grille : A vous de jouer !\n");
                // Début du chronomètre
            time_t debut = time(NULL);

            printf("     0    1    2    3    4    5    6    7  \n");
            printf("   ________________________________________\n");
            for(i=0;i<8;i++) {
                if(i<8)
                    printf(" %d | ",i+1);
                else
                    printf("%d | ",i+1);
                for(j=0;j<8;j++) {
                    JEU[i][j]='O';//'O'implique case cachées
                    printf("%c  | ",JEU[i][j]);
                }
                printf("\n");
            }
            //On demande au joueur de choisir une case
            //la case est définie par sa ligne i et sa colonne j
            while (check_win(NbMines) != 1) {
                printf("\n\nVeuillez entrer la case choisie (numero de ligne [espace] numero de colonne):\t");
                scanf("%d %d",&i,&j);
                printf("Vous avez choisi la case (%d,%d).\n Que voulez-vous faire ?\n",i,j);
                i=i-1;
                j=j-1;
                // Demander au joueur ce qu'il veut faire
                printf("\t1. Marquer une mine\n");
                printf("\t2. Ouvrir une case vide\n");
                printf("\t2. Ouvrir voisin case jouee\n");
                do {
                    printf("\t\tVotre choix : ");
                    scanf("%d",&choix);
                }while (choix != 1 && choix != 2);
                // Choix : dévoiler une case ou placer un drapeau
                //////////////////////////////
                // Initialisation des mines //
                //////////////////////////////
                for (;CompteMines<NbMines ;CompteMines++) {  
                    x=rand()%10;//on choisit la ligne de manière aléatoire
                    y=rand()%10;//on choisit la colonne de manière aléatoire
                    if(MINES[x][y]=='0' && (x < i - 1 || x > i + 1) && (y < j - 1 || y > j + 1)) {//On vérifie que la case est libre
                        MINES[x][y]='M';//on place un M pour indiquer qu'il y a une mine
                    } else {
                        CompteMines--;//Sinon, il y a déjà un M et il faut faire un tour de plus
                    }
                }
                switch (choix) {
                    case 1 : //fonction devoile mines autour
                        if(MINES[i][j]=='M') {
                            printf("BOUM!!!!!\nVous avez perdu !!!\n\n");
                            printf("     0    1    2    3    4    5    6    7  \n");
                            printf("   ________________________________________\n");
                            for(i=0;i<8;i++) {
                                if(i<7)
                                    printf(" %d | ",i+1);
                                else
                                    printf("%d | ",i+1);
                                for(j=0;j<8;j++)                
                                    printf("%c  | ",MINES[i][j]);
                                printf("\n");
                            }
                            exit(0);
                        }
                        NbMinesAutour();
                        if (N!=0) {//Il y a des mines autour
                            JEU[i][j]= N + 48;
                        } else {//Il n'y a pas de mines autour
                            JEU[i][j]='0';
                            discoveur();
                        }
                        break;
                    case 2 :
                        if (JEU[i][j] == 'O')
                            JEU[i][j]='D';
                        break;
                    default: printf("Veuillez saisir les valeurs de l'ecran");
                }
            effacerEcran(); // Effacer l'écran avant d'afficher la grille mise à jour
            //AFFICHER LA GRILLE
            AfficherTempsEcoule(debut);
            AfficheJeu();
            sleep(1);
            }
            printf("\n\n\t\tBravo vous avez gagné !\n");
            printf("Voulez-vous recommencer ?\n Oui(1)\n Non(0):\n");
            scanf("%d",&rep);
        } while(rep==1);
    
    return 0;
}