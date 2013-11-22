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
 * 
 */
int main(int argc, char** argv) {
    SDL_Surface *ecran = NULL;
    SDL_Event event;
    int continuer=1;
    SDL_Init(SDL_INIT_VIDEO);
    ecran=SDL_SetVideoMode(640, 480, 32, SDL_HWSURFACE);

     if (ecran == NULL)
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
    SDL_Quit();
  
    return (EXIT_SUCCESS);
}

