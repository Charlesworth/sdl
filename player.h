#ifndef PLAYER_H
#define PLAYER_H

#include <set>
#include "SDL2/SDL.h"
#include "input.h"

class Player
{
    public:
		//Initializes the player with default starting posX and posY
		Player( SDL_Surface* playerTexture );
		
		//Initializes the player with defined posX and posY
		Player( SDL_Surface* playerTexture, int posX, int posY );

        //Destroys the player
		~Player();

		//Takes player input and does stuff
		void handleInputs( std::set<INPUT> );

		//Shows the dot on the screen
		void render( SDL_Surface* );
};
 
#endif