/* 
 * File:   main.c
 * Author: Alex
 *
 * Created on 25 octobre 2013, 13:50
 */

#include <stdio.h>
#include <stdlib.h>
//#include <SDL/SDL.h>
#include <chipmunk/chipmunk.h>
//#include <SDL/SDL_gfxPrimitives.h>

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
/*
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
*/

/*
 * 
 */
int main(int argc, char** argv) 
{
    char* fichier_dico = "dico.txt";
    algo_1(fichier_dico, "asdfarbre");
    
    /*
     if (SDL_Init(SDL_INIT_VIDEO) == -1)
    {
        fprintf(stderr, "Erreur d'initialisation de la SDL");
        exit(EXIT_FAILURE);
    }
     SDL_SetVideoMode(640, 480, 32, SDL_HWSURFACE);
     
   pause();
  
    SDL_Quit();
  */
    return (EXIT_SUCCESS);
}

