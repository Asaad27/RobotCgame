
#include "constantes.h"
#include "jeu.h"
#include "editeur.h"
#include "sdl.h"
#include "howtoplay.h"

int main(int argc, char* argv[])
{
	SDL_Surface *ecran = NULL, *menu = NULL, * selector = NULL;
	SDL_Rect SelectorPos;
	SDL_Event event;
	int select = 0;
	bool continuer = true;

	ecran = init(ecran, "ressources/robot.png", "ROBOT INTELLIGENT");    //charger la fenetre, le titre et l'icone de la fenetre
	menu = chargerImage("ressources/menu.png");
	selector = chargerImage("ressources/selector.png");

	SelectorPos.x = 108;
	SelectorPos.y = 210;

	while (continuer)												//boucle du jeu
	{
		SDL_WaitEvent(&event);
		switch (event.type)                                    //traitement des entrees de l'utilisateur
		{
			case SDL_QUIT:
				continuer = false;
				break;

			case SDL_KEYDOWN:
				switch (event.key.keysym.sym)
				{
					case SDLK_ESCAPE:										// Veut arrêter le jeu
						continuer = false;
						break;

					case SDLK_RETURN:										// Demande à jouer
						if (select == 0)
							jouer(ecran);
						else if (select == 1)
						{
							ecran = SDL_SetVideoMode(LARGEUR_FENETRE, HAUTEUR_FENETRE + 160, 32, SDL_HWSURFACE | SDL_DOUBLEBUF);
							editeur(ecran);
						}
						else if (select == 2)
							howtoplay(ecran);
						break;

					case SDLK_DOWN:
						SelectorPos = ToucheBas(&select, SelectorPos);   //deplace le curseur de selection
						break;

					case SDLK_UP:
						SelectorPos = ToucheHaut(&select, SelectorPos);  //deplace le curseur de selection
						break;
                    default :
                        break;
				}

			break;
		}

		SDL_FillRect(ecran, NULL, SDL_MapRGB(ecran->format, 0, 0, 0));	// Effacement de l'écran
		appliquer_surface(0, 0, menu, ecran);							//mise a jour de l'ecran
		SDL_BlitSurface(selector, NULL, ecran, &SelectorPos);
		SDL_Flip(ecran);
	}

	SDL_FreeSurface(menu);										//libere les espaces dynamiquement alloues
	SDL_FreeSurface(ecran);
	SDL_FreeSurface(selector);
	SDL_Quit();

	return EXIT_SUCCESS;
}
