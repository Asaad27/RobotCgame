#include "sdl.h"
#include "constantes.h"

void howtoplay(SDL_Surface* ecran)
{
	SDL_Event event;
	SDL_Surface* howto_play = NULL;
	bool continuer = true;

	while (continuer)
	{
		SDL_WaitEvent(&event);
		switch (event.type)
		{
			case SDL_QUIT:
				continuer = false;
				break;

			case SDL_KEYDOWN:
				switch (event.key.keysym.sym)
				{
					case SDLK_ESCAPE:
						continuer = false;
						break;

					case SDLK_RETURN:
						continuer = false;
						break;
                    default:
                        break;
				}
            default:
                break;
		}
		howto_play = chargerImage("ressources/howtoplay.png");
		SDL_BlitSurface(howto_play, NULL, ecran, NULL);
		SDL_Flip(ecran);
	}
	SDL_FreeSurface(howto_play);
}
