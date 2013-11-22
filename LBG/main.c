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
 

void bille(SDL_Surface *ecran)
{   srand(time(NULL));
    circleColor(ecran, rand()%640, 10, 10, SDL_MapRGB(ecran->format,rand()%255,rand()%255,rand()%255));
    
  // cpVect is a 2D vector and cpv() is a shortcut for initializing them.
  cpVect gravity = cpv(0, -100);
  
  // Create an empty space.
  cpSpace *space = cpSpaceNew();
  cpSpaceSetGravity(space, gravity);
  
  // Add a static line segment shape for the ground.
  // We'll make it slightly tilted so the ball will roll off.
  // We attach it to space->staticBody to tell Chipmunk it shouldn't be movable.
  cpShape *ground = cpSegmentShapeNew(space->staticBody, cpv(-20, 5), cpv(20, -5), 0);
  cpShapeSetFriction(ground, 1);
  cpSpaceAddShape(space, ground);
  
  // Now let's make a ball that falls onto the line and rolls off.
  // First we need to make a cpBody to hold the physical properties of the object.
  // These include the mass, position, velocity, angle, etc. of the object.
  // Then we attach collision shapes to the cpBody to give it a size and shape.
  
  cpFloat radius = 5;
  cpFloat mass = 1;
  
  // The moment of inertia is like mass for rotation
  // Use the cpMomentFor*() functions to help you approximate it.
  cpFloat moment = cpMomentForCircle(mass, 0, radius, cpvzero);
  
  // The cpSpaceAdd*() functions return the thing that you are adding.
  // It's convenient to create and add an object in one line.
  cpBody *ballBody = cpSpaceAddBody(space, cpBodyNew(mass, moment));
  cpBodySetPos(ballBody, cpv(0, 15));
  
  // Now we create the collision shape for the ball.
  // You can create multiple collision shapes that point to the same body.
  // They will all be attached to the body and move around to follow it.
  cpShape *ballShape = cpSpaceAddShape(space, cpCircleShapeNew(ballBody, radius, cpvzero));
  cpShapeSetFriction(ballShape, 0.7);
  
  // Now that it's all set up, we simulate all the objects in the space by
  // stepping forward through time in small increments called steps.
  // It is *highly* recommended to use a fixed size time step.
  cpFloat timeStep = 1.0/60.0;
  for(cpFloat time = 0; time < 2; time += timeStep){
    cpVect pos = cpBodyGetPos(ballBody);
    cpVect vel = cpBodyGetVel(ballBody);
    printf(
      "Time is %5.2f. ballBody is at (%5.2f, %5.2f). It's velocity is (%5.2f, %5.2f)\n",
      time, pos.x, pos.y, vel.x, vel.y
    );
    
    cpSpaceStep(space, timeStep);
  }
  
  // Clean up our objects and exit!
  cpShapeFree(ballShape);
  cpBodyFree(ballBody);
  cpShapeFree(ground);
  cpSpaceFree(space);
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


    
    //char* fichier_dico = "dico.txt";
    //algo_1(fichier_dico, "asdfarbre");
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
