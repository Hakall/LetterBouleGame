/* 
 * File:   main.c
 * Author: Alex
 *
 * Created on 25 octobre 2013, 13:50
 */

#include <stdio.h>
#include <windows.h>
#include <stdlib.h>
#include <SDL/SDL.h>
#include <SDL/SDL_gfxPrimitives.h>
#include <chipmunk/chipmunk.h>
#include <time.h>

#define TAILLE_MAX 1000

void algo_1(char* nom_fichier, char* chaine)
{
    FILE* fichier = NULL;
    char* chaine_search = ""; // Chaine vide pour recherche
    char* chaine_res = ""; // Chaine vide résultat
    int max_length = 0;
    
    fichier = fopen(nom_fichier, "r"); // Ouverture du fichier
    
    if (fichier != NULL)
    {
        // Recherche d'un mot du dico dans la chaine donnée,
        // on garde la plus longue
        
        while (fgets(chaine_search, TAILLE_MAX, fichier) != NULL)
        {
            if (strlen(strstr(chaine,chaine_search)) > max_length)
            {
                chaine_res = strstr(chaine,chaine_search);
                max_length = strlen(chaine_res);
            }
        }
    }
    else
    {
        printf("Impossible d'ouvrir le fichier. Veuillez spécifier un nom valide/vérifier que le fichier est au bon endroit.");
    }
}
 
/**
 * Affichage fenetre
 */
void pause()
{
    int continuer = 1;
    SDL_Event event;
  
    while (continuer)
    {
        SDL_WaitEvent(&event);
        switch(event.type)
        {
            case SDL_QUIT:
                continuer = 0;
        }
    }

}

void bille(SDL_Surface *ecran)
{   srand(time(NULL));
    circleColor(ecran, rand()%640, 10, 10, SDL_MapRGB(ecran->format,rand()%255,rand()%255,rand()%255));
    
}
/*
 * main
 */
int main(int argc, char** argv) {

    SDL_Surface *ecran = NULL;
    SDL_Event event;
    int continuer=1;
    SDL_Init(SDL_INIT_VIDEO);
    ecran=SDL_SetVideoMode(640, 480, 32, SDL_HWSURFACE);

     if (ecran == NULL)

    
    //char* fichier_dico = "dico.txt";
    //algo_1(fichier_dico, "asdfarbre");
    
    SDL_Surface *ecran = NULL; // Le pointeur qui va stocker la surface de l'écran

    SDL_Init(SDL_INIT_VIDEO);
    
    if (SDL_Init(SDL_INIT_VIDEO) == -1)
    {
        fprintf(stderr, "Erreur d'initialisation de la SDL");
        exit(EXIT_FAILURE);
    }
     
    SDL_WM_SetCaption("Letter Boule Game !", NULL);
    SDL_FillRect(ecran, NULL, SDL_MapRGB(ecran->format,0,0,0));
    while(continuer)
    {
        SDL_PollEvent(&event);
        switch(event.type) /* Test du type d'événement */
        {
            case SDL_QUIT: /* Si c'est un événement de type "Quitter" */
                    continuer = 0;
            break;
            case SDL_KEYDOWN:
                bille(ecran); 
                SDL_Flip(ecran);
              
            break;
        }
         
        }
    
    ecran = SDL_SetVideoMode(640, 480, 32, SDL_HWSURFACE); // On tente d'ouvrir une fenêtre
    if (ecran == NULL) // Si l'ouverture a échoué, on le note et on arrête
    {
        fprintf(stderr, "Impossible de charger le mode vidéo : %s\n", SDL_GetError());
        exit(EXIT_FAILURE);
    }
    
    SDL_WM_SetCaption("Letter Boule Game v0.1", NULL);
    
    SDL_FillRect(ecran, NULL, SDL_MapRGB(ecran->format, 255, 255, 255));
    SDL_Flip(ecran);
   
    
    pause();
  
    SDL_Quit();
  
    return (EXIT_SUCCESS);
}
