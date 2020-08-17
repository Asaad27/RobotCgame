
#include "constantes.h"
#include "editeur.h"
#include "fichiers.h"
#include "sdl.h"



int chercheRobotMap(int carte[NB_BLOCS_LARGEUR][NB_BLOCS_HAUTEUR])
{
    int nbrRobots = 0;
    for (int i = 0; i < NB_BLOCS_LARGEUR; i++)
        for (int j = 0; j < NB_BLOCS_HAUTEUR; j++)
            nbrRobots += (carte[i][j] == ROBOT) ? 1:0;
    return nbrRobots;
}

SDL_Rect flecheDroite(int *objetActuel, SDL_Rect posselector)
{
    if (*objetActuel == CARRE)
    {
        *objetActuel = DISQUE;
        posselector.x = 45;
    }
    else if (*objetActuel == DISQUE)
    {
        *objetActuel = RECT;
        posselector.x = 86;
    }
    else if (*objetActuel == RECT)
    {
        *objetActuel = ROBOT;
        posselector.x = 125;
    }
    else if (*objetActuel == ROBOT)
    {
        *objetActuel = CARRE;
        posselector.x = 4;
    }

    return posselector;
}

SDL_Rect flecheGauche(int *objetActuel, SDL_Rect posselector)
{
    if (*objetActuel == CARRE)
    {
        *objetActuel = ROBOT;
        posselector.x = 125;
    }
    else if (*objetActuel == DISQUE)
    {
        *objetActuel = CARRE;
        posselector.x = 4;
    }
    else if (*objetActuel == RECT)
    {
        *objetActuel = DISQUE;
        posselector.x = 45;
    }
    else if (*objetActuel == ROBOT)
    {
        *objetActuel = RECT;
        posselector.x = 86;
    }

    return posselector;
}

void editeur(SDL_Surface* ecran)
{
	SDL_Surface *carre = NULL, *objectif = NULL, *robot = NULL;
	SDL_Surface *arrierePlan = NULL,  *rect = NULL, *selection = NULL, *selector = NULL, *saved=NULL;
	SDL_Rect position, posgfx, posselector, possaved;
	SDL_Event event;


    int s=0;
    SDL_TimerID timer;
	bool continuer = true;
	int clicGaucheEnCours = 0, clicDroitEnCours = 0, objetActuel = CARRE, i = 0, j = 0;
	int carte[NB_BLOCS_LARGEUR][NB_BLOCS_HAUTEUR] = { 0 };



    possaved.x= 335;
    possaved.y= 388;


	posgfx.y = 365;
	posgfx.x = 2;

	posselector.x = 4;
	posselector.y = 340;

	// Chargement des objets et du niveau
	selector = chargerImage("ressources/selector2.png");
	selection = chargerImage("ressources/editgfx.png");
	arrierePlan = chargerImage("ressources/arrierePlan.png");
	carre = chargerImage("ressources/carre.png");
	objectif = chargerImage("ressources/objectif.png");
	rect = chargerImage("ressources/rect.png");
	robot = chargerImage("ressources/robot_bas.gif");
	saved = chargerImage("ressources/save.png");

	if (!chargerMap(carte))
		exit(EXIT_FAILURE);

	while (continuer)   //boucle principale
	{
		SDL_WaitEvent(&event);
		switch (event.type)
		{
		case SDL_QUIT:
			continuer = 0;
			break;
		case SDL_MOUSEBUTTONDOWN:
			if (event.button.button == SDL_BUTTON_LEFT)
			{
				if (objetActuel == ROBOT)
				{
					int nbrRobots = chercheRobotMap(carte);
					if (nbrRobots)
						break;
				}
				carte[event.button.x / TAILLE_BLOC][event.button.y / TAILLE_BLOC] = objetActuel;
				clicGaucheEnCours = 1;                          // On active un booléen pour retenir qu'un bouton est enfoncé
			}
			else if (event.button.button == SDL_BUTTON_RIGHT) // Le clic droit sert à effacer
			{
				carte[event.button.x / TAILLE_BLOC][event.button.y / TAILLE_BLOC] = VIDE;
				clicDroitEnCours = 1;
			}
			break;
		case SDL_MOUSEBUTTONUP:                             // On met a false le booleen qui dit qu'un bouton était enfoncé
			if (event.button.button == SDL_BUTTON_LEFT)
				clicGaucheEnCours = 0;
			else if (event.button.button == SDL_BUTTON_RIGHT)
				clicDroitEnCours = 0;
			break;
		case SDL_MOUSEMOTION:
			if (clicGaucheEnCours)                          //deplacement de la souris avec clic gauce
				carte[event.motion.x / TAILLE_BLOC][event.motion.y / TAILLE_BLOC] = objetActuel;
			else if (clicDroitEnCours)                      // de meme pour le bouton droit de la souris
				carte[event.motion.x / TAILLE_BLOC][event.motion.y / TAILLE_BLOC] = VIDE;
			break;
		case SDL_KEYDOWN:
			switch (event.key.keysym.sym)
			{
				case SDLK_ESCAPE:
					continuer = 0;
					s=0;
					break;

				case SDLK_s:
					sauvegarderNiveau(carte);
                    s=1;
					break;

				case SDLK_KP1:
					objetActuel = CARRE;
					posselector.x = 4;
					break;

				case SDLK_KP2:
					objetActuel = DISQUE;
					posselector.x = 45;
					break;

				case SDLK_KP3:
					objetActuel = RECT;
					posselector.x = 86;
					break;

				case SDLK_KP4:
					objetActuel = ROBOT;
					posselector.x = 125;
					break;

				case SDLK_RIGHT:
					posselector = flecheDroite(&objetActuel, posselector);
                    break;

				case SDLK_LEFT:
					posselector = flecheGauche(&objetActuel, posselector);
					break;

				break;

				default :
                    break;
			}
			break;


		}
		// Effacement de l'écran

		SDL_FillRect(ecran, NULL, SDL_MapRGB(ecran->format, 255, 255, 255));
		SDL_BlitSurface(arrierePlan, NULL, ecran, NULL);
		SDL_BlitSurface(selection, NULL, ecran, &posgfx);

		SDL_BlitSurface(selector, NULL, ecran, &posselector);

		if(s==1)
        {
            SDL_BlitSurface(saved, NULL, ecran, &possaved);
        }

		// Placement des objets à l'écran
		for (i = 0; i < NB_BLOCS_LARGEUR; i++)
		{

			for (j = 0; j < NB_BLOCS_HAUTEUR; j++)
			{
				position.x = i * TAILLE_BLOC;
				position.y = j * TAILLE_BLOC;

				switch (carte[i][j])
				{
				case CARRE:
					SDL_BlitSurface(carre, NULL, ecran, &position);
					break;
				case DISQUE:
					SDL_BlitSurface(objectif, NULL, ecran, &position);
					break;
				case RECT:
					SDL_BlitSurface(rect, NULL, ecran, &position);
					break;
				case ROBOT:
					SDL_BlitSurface(robot, NULL, ecran, &position);
					break;
				}
			}
		}

		// Mise à jour de l'écran
		SDL_Flip(ecran);

	}
	//liberation de la memoire
	SDL_FreeSurface(carre);
	SDL_FreeSurface(objectif);
	SDL_FreeSurface(robot);
	SDL_FreeSurface(arrierePlan);
	SDL_FreeSurface(rect);
	ecran = SDL_SetVideoMode(LARGEUR_FENETRE, HAUTEUR_FENETRE + 267, 32, SDL_HWSURFACE | SDL_DOUBLEBUF);


}

