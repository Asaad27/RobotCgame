//contient des fonctions en relation avec la SDL et utilisées frequemment dans la fonction main, en tenant compte de la gestion des erreurs

#ifndef SDL_H_INCLUDED
#define SDL_H_INCLUDED

#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <SDL/SDL.h>
#include <SDL_image.h>


void appliquer_surface(int x, int y, SDL_Surface* source, SDL_Surface* destination); //applique les changements subis par l'ecran
SDL_Surface *init(SDL_Surface* ecran, char* icone, char *caption);					//charge l'interface graphique en tenant compte de la gestion d'erreurs dans un fichier
SDL_Surface *chargerImage(char* chemin);											//charge les images en tenant compte de la gestion d'erreurs dans un fichier 
SDL_Rect ToucheHaut(int *select, SDL_Rect SelectorPos);                             //fait monter le curseur de selection
SDL_Rect ToucheBas(int *select, SDL_Rect SelectorPos);								//fait descendre le curseur de selection
#endif // SDL_H_INCLUDED
