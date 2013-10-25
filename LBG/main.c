/* 
 * File:   main.c
 * Author: Alex
 *
 * Created on 25 octobre 2013, 13:50
 */

#include <stdio.h>
#include <stdlib.h>
#include <SDL/SDL.h>

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
/*
 * 
 */
int main(int argc, char** argv) {
     if (SDL_Init(SDL_INIT_VIDEO) == -1)
    {
        fprintf(stderr, "Erreur d'initialisation de la SDL");
        exit(EXIT_FAILURE);
    }
     SDL_SetVideoMode(640, 480, 32, SDL_HWSURFACE);
     
   pause();
  
    SDL_Quit();
  
    return (EXIT_SUCCESS);
}

