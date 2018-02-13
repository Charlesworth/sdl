#ifndef PLAYER_H
#define PLAYER_H

#include <set>
#include "SDL2/SDL.h"
#include "input.h"

class Player
{
    public:
		//Initializes the variables
		Player( SDL_Surface* );

        //Destroys the variables
		~Player();

		//Takes player input and does stuff
		void handleInputs( std::set<INPUT> );

		//Shows the dot on the screen
		void render( SDL_Surface* );
};
 
#endif