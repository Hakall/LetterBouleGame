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
#include <SDL/SDL_ttf.h>
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
 
 
void UpdateEvents(Input* in)
{
	SDL_Event event;
	int peutDessiner=0;
	int continuer=1;
	while(continuer)
	{
	    SDL_PollEvent(&event);
		switch (event.type)
		{
        case SDL_MOUSEMOTION:
			in->mousex=event.motion.x;
			in->mousey=event.motion.y;
			in->mousexrel=event.motion.xrel;
			in->mouseyrel=event.motion.yrel;
			xFin=in->mousexrel;
			yFin=in->mouseyrel;
			break;
		case SDL_MOUSEBUTTONDOWN:
           x=event.motion.x;
           y=event.motion.y;
            peutDessiner=1;
			in->mousebuttons[event.button.button]=1;
			break;
		case SDL_MOUSEBUTTONUP:
			in->mousebuttons[event.button.button]=0;
			if(peutDessiner){
                    xFin=event.motion.x;
                    yFin=event.motion.y;
                    lineRGBA(ecran,
                             x,
                             y,
                             xFin,
                             yFin,
                             0,100,255,255);
                    peutDessiner=0;
			}
            SDL_Flip(ecran);
			continuer=0;
			break;
		default:
            break;
		}
	}
}






/**
 * Init
 */
cpSpace *init(){
    // cpVect is a 2D vector and cpv() is a shortcut for initializing them.
  cpVect gravity = cpv(50, 0);
  
  // Create an empty space.
  espace = cpSpaceNew();
  cpSpaceSetGravity(espace, gravity);
  
  // Add a static line segment shape for the ground.
  // We'll make it slightly tilted so the ball will roll off.
  // We attach it to space->staticBody to tell Chipmunk it shouldn't be movable.
  cpShape *ground = cpSegmentShapeNew(espace->staticBody, cpv(420, 0), cpv(420, 640), 0);
  cpShape *murGauche = cpSegmentShapeNew(espace->staticBody, cpv(0, 10), cpv(470, 10), 0);
  cpShape *murDroit = cpSegmentShapeNew(espace->staticBody, cpv(0, 630), cpv(470, 630), 0);
  cpShapeSetFriction(ground, 0.5);
  cpShapeSetFriction(murGauche, 1);
  cpShapeSetFriction(murDroit, 1);
  cpSpaceAddShape(espace, ground);
  cpSpaceAddShape(espace, murGauche);
  cpSpaceAddShape(espace, murDroit);
  
  
  return espace;  
}
void tracerLigne(){
    Input *inputLigne;
    UpdateEvents(inputLigne);
}

char* genChar(){
    char* tabChar[50]={"E","E","E","E","E","E","S","S","S","S","A","A","A","A","T","T","T","I","I","I","I","N","N","N","R","R","R","U","U","L","L","L","O","O","D","C","P","M","V","Q","F","B","G","H","J","X","Y","Z","W","K"};
    char* lettre=tabChar[rand()% 50];
    return lettre;
}

Boule creerBoule()
{   
  cpFloat radius = rand() % 16 + 25;// radius entre 25 et 40
  cpFloat mass =  rand() % 3 + 1;// masse entre 1 et 3;
  
  cpFloat moment = cpMomentForCircle(mass, 0, radius, cpvzero);
  

  cpBody *ballBody = cpSpaceAddBody(espace, cpBodyNew(mass, moment));
  cpBodySetPos(ballBody, cpv(0, 310));
  
  cpShape *ballShape = cpSpaceAddShape(espace, cpCircleShapeNew(ballBody, radius, cpvzero));
  cpShapeSetFriction(ballShape, -0.2);
  Boule laBoule={radius, cpBodyGetPos(ballBody).x,0,SDL_MapRGB(ecran->format,rand() % 136 + 120,rand() % 136 + 120,rand() % 136 + 120),ballShape,ballBody, genChar()};
  return laBoule;

  }
void initLesBoules(){
    for(int i=0;i<50;i++){        
                lesBoules[i]=creerBoule(espace); 
                };
}

void initPolice(){
    if(TTF_Init() == -1)
    {
        fprintf(stderr, "Erreur d'initialisation de TTF_Init : %s\n", TTF_GetError());
        exit(EXIT_FAILURE);
    }
    
  police = TTF_OpenFont("imagine_font.ttf", 20);
}

void affichage(int x1, int y1, int x2, int y2,boolean clic){
 cpFloat timeStep = 1.0/120.0;
      
          for(cpFloat time = 0; time < 2; time += timeStep){
              SDL_FillRect(ecran, NULL, SDL_MapRGB(ecran->format,0,0,0));
              for(int i=0;i<50;i++){
                 cpVect pos = cpBodyGetPos(lesBoules[i].body);
                 cpVect vel = cpBodyGetVel(lesBoules[i].body);
    
                 rectangleColor(ecran,10, 0, 630, 420,SDL_MapRGB(ecran->format,255,255,255));
                 circleColor(ecran, pos.y, pos.x, lesBoules[i].radius, lesBoules[i].couleurs); 
                 
                 //lettre
                 SDL_Color white={255,255,255};
                 SDL_Surface *lettre= TTF_RenderText_Solid(police, lesBoules[i].lettre, white);
                 SDL_Rect position;
                 position.y=pos.x;
                 position.x=pos.y;
                 SDL_BlitSurface(lettre, NULL, ecran, &position);
                 
                 //segment
                 
               }
              if(clic==TRUE)
                 lineRGBA(ecran,x1,y1,x2,y2,255,255,255,255);
                 
              cpSpaceStep(espace, timeStep);
              SDL_Flip(ecran);
          }
 SDL_Flip(ecran);
}


/*
 * main
 */
int main(int argc, char** argv) {

    
    
    espace=init();
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
    initPolice();
    initLesBoules(espace);
    boolean clic=FALSE;
    int x_debut=0;
    int y_debut=0;
    while(continuer)
    {
        
        SDL_PollEvent(&event);
        
        switch(event.type) // Test du type d'événement
        {
            case SDL_QUIT: // Si c'est un événement de type "Quitter" 
                    continuer = 0;
            break;
            case SDL_MOUSEBUTTONDOWN:
                tracerLigne();
                break;
        }
        affichage(0,0,0,0,clic);
        SDL_Flip(ecran);
  }
   
    cpSpaceFree(espace);
    TTF_CloseFont(police);
    TTF_Quit();
    SDL_Quit();
  
    return (EXIT_SUCCESS);
}
