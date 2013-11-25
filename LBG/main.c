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
#include "main.h"

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
 * 
 * TO DO : fonctions: Init, Affichage, créer boule
 */

/**
 * Init
 */
cpSpace *init(){
    // cpVect is a 2D vector and cpv() is a shortcut for initializing them.
  cpVect gravity = cpv(50, 0);
  
  // Create an empty space.
  cpSpace *space = cpSpaceNew();
  cpSpaceSetGravity(space, gravity);
  
  // Add a static line segment shape for the ground.
  // We'll make it slightly tilted so the ball will roll off.
  // We attach it to space->staticBody to tell Chipmunk it shouldn't be movable.
  cpShape *ground = cpSegmentShapeNew(space->staticBody, cpv(420, 0), cpv(420, 640), 0);
  cpShape *murGauche = cpSegmentShapeNew(space->staticBody, cpv(0, 10), cpv(470, 10), 0);
  cpShape *murDroit = cpSegmentShapeNew(space->staticBody, cpv(0, 630), cpv(470, 630), 0);
  cpShapeSetFriction(ground, 0.3);
  cpShapeSetFriction(murGauche, 1);
  cpShapeSetFriction(murDroit, 1);
  cpSpaceAddShape(space, ground);
  cpSpaceAddShape(space, murGauche);
  cpSpaceAddShape(space, murDroit);
  
  
  return space;  
}

Boule creerBoule(cpSpace *space)
{   
  cpFloat radius = 10;
  cpFloat mass = 1;
  
  cpFloat moment = cpMomentForCircle(mass, 0, radius, cpvzero);
  

  cpBody *ballBody = cpSpaceAddBody(space, cpBodyNew(mass, moment));
  cpBodySetPos(ballBody, cpv(0, 310));
  
  cpShape *ballShape = cpSpaceAddShape(space, cpCircleShapeNew(ballBody, radius, cpvzero));
  cpShapeSetFriction(ballShape, -0.5);
  Boule laBoule={cpBodyGetPos(ballBody).x,0,ballShape,ballBody, 'A'};
  return laBoule;

  }



void affichage(Boule tab[], SDL_Surface *ecran,cpSpace *space, int nbBoules){
      cpFloat timeStep = 1.0/120.0;
      
          for(cpFloat time = 0; time < 2; time += timeStep){
              for(int i=0;i<nbBoules+1;i++){
                 cpVect pos = cpBodyGetPos(tab[i].body);
                 cpVect vel = cpBodyGetVel(tab[i].body);
    
                 rectangleColor(ecran,10, 0, 630, 420,SDL_MapRGB(ecran->format,255,255,255));
                 circleColor(ecran, pos.y, pos.x, 10, SDL_MapRGB(ecran->format,255,255,255));
   
                 SDL_Flip(ecran);
   
                 SDL_FillRect(ecran, NULL, SDL_MapRGB(ecran->format,0,0,0));
    
                 cpSpaceStep(space, timeStep);
               }
             }
}
/*
 * main
 */
int main(int argc, char** argv) {

    cpSpace *espace=init();
    Boule lesBoules[30]={0,0,NULL,NULL,'A'};
    SDL_Surface *ecran = NULL;
    SDL_Event event;
    int continuer=1;
    SDL_Init(SDL_INIT_VIDEO);
    ecran=SDL_SetVideoMode(640, 480, 32, SDL_HWSURFACE | SDL_DOUBLEBUF);


    
    //char* fichier_dico = "dico.txt";
    //algo_1(fichier_dico, "asdfarbre");
    if (ecran == NULL)
    {
        fprintf(stderr, "Erreur d'initialisation de la SDL");
        exit(EXIT_FAILURE);
    }
     
    SDL_WM_SetCaption("Letter Boule Game !", NULL);
    SDL_FillRect(ecran, NULL, SDL_MapRGB(ecran->format,0,0,0));
    lesBoules[0]=creerBoule(espace);
    int nbBoules=0;
    while(continuer)
    {
        SDL_PollEvent(&event);
        
        switch(event.type) // Test du type d'événement
        {
            case SDL_QUIT: // Si c'est un événement de type "Quitter" 
                    continuer = 0;
            break;
            case SDL_KEYDOWN:
                nbBoules++;
                lesBoules[nbBoules]=creerBoule(espace); 
               //SDL_Flip(ecran);
              
            break;
        }
        affichage(lesBoules,ecran,espace,nbBoules);
         
  }
   
    cpSpaceFree(espace);
    SDL_Quit();
  
    return (EXIT_SUCCESS);
}
