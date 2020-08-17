
#include "sdl.h"
#include "constantes.h"


void appliquer_surface(int x, int y, SDL_Surface* source, SDL_Surface* destination)		//applique les changements subis par la fenetre
{
	SDL_Rect position;
	position.x = x;
	position.y = y;
	SDL_BlitSurface(source, NULL, destination, &position);
}


SDL_Surface *init(SDL_Surface* ecran, char* icone, char *caption)
{
    FILE *erreur = fopen("erreur.txt", "w");     //fichier contenant les erreurs
	bool chargementReussi = true;

	if (SDL_Init(SDL_INIT_VIDEO) < 0)            //geston d'erreurs
	{
		fprintf(erreur, "erreur de l'initialisation de la SDL: %s", SDL_GetError());
		chargementReussi = false;
	}

	SDL_WM_SetIcon(chargerImage(icone), NULL);      // L'icône doit être chargée avant SDL_SetVideoMode
	ecran = SDL_SetVideoMode(LARGEUR_FENETRE, HAUTEUR_FENETRE + 267, 32, SDL_HWSURFACE | SDL_DOUBLEBUF);
	SDL_WM_SetCaption(caption, NULL);

	if (ecran == NULL)
	{
		fprintf(erreur, "erreur lors du chargement de l'ecran %s", SDL_GetError);  //ecrire les erreurs dans un fichier
		chargementReussi = false;
	}
	fclose(erreur);
    if (!chargementReussi)														  //ouvre le fichier erreur et quitte le programme
        {
            system("erreur.txt");
            SDL_Quit();
        }

	return ecran;
}

SDL_Surface *chargerImage(char *chemin)
{
    FILE *erreur = fopen("erreur.txt", "w");
	SDL_Surface* image;
	image = IMG_Load(chemin);

	if (!image)                                            //ouvre le fichier erreur et quitte le programme
	{
		fprintf(erreur, "chargerImage: %s\n", IMG_GetError()); //ecrire les erreurs dans un fichier
		fclose(erreur);
		system("erreur.txt");
        SDL_Quit();
	}
    fclose(erreur);
	return image;
}

SDL_Rect ToucheBas(int *select, SDL_Rect SelectorPos)   //fait monter le curseur de selection
{
	switch (*select)
	{
		case 0:
			*select = 1;
			SelectorPos.y = 241;
			break;

		case 1:
			*select = 2;
			SelectorPos.y = 274;
			break;

		case 2:
			*select = 0;
			SelectorPos.y = 210;
			break;
	}

	return SelectorPos;									//retourne la nouvelle position du curseur
}

SDL_Rect ToucheHaut(int *select, SDL_Rect SelectorPos)		//fait descendre le curseur de selection
{
	switch (*select)
	{
		case 0:
			*select = 2;
			SelectorPos.y = 274;
			break;

		case 1:
			*select = 0;
			SelectorPos.y = 210;
			break;

		case 2:
			*select = 1;
			SelectorPos.y = 241;
			break;
	}

	return SelectorPos;									//retourne la nouvelle position du curseur
}
