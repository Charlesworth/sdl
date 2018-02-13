#include "SDL2/SDL.h"
#include "input.h"
#include <stdio.h>
#include <vector>

class Player
{
    public:
		//The dimensions of the player
		static const int PLAYER_WIDTH = 20;
		static const int PLAYER_HEIGHT = 20;

		//Maximum axis velocity of the player
		static const int PLAYER_VEL = 10;

		//Initializes the variables
		Player( SDL_Surface* );

        //Destroys the variables
		~Player();

		//Takes player input and does stuff
		void handleInputs( std::set<INPUT> );

		//Shows the dot on the screen
		void render( SDL_Surface* );

    private:
        SDL_Surface* texture;
        SDL_Rect rect;    
};

Player::Player( SDL_Surface* inputTexture )
{
    rect.x = 30;
	rect.y = 30;
	rect.w = PLAYER_WIDTH;
	rect.h = PLAYER_HEIGHT;

    SDL_Surface* texture = new SDL_Surface;
    texture = inputTexture;
}

Player::~Player()
{
    SDL_FreeSurface( texture );
    texture = NULL;
}

void Player::render( SDL_Surface* screenSurface )
{
    SDL_BlitScaled( texture, NULL, screenSurface, &rect );
}

void Player::handleInputs( std::set<INPUT> inputs ) {
    if ( inputs.count(INPUT::LEFT) ) {
        rect.x--;
    }

    if ( inputs.count(INPUT::RIGHT) ) {
        rect.x++;
    }

    if ( inputs.count(INPUT::UP) ) {
        rect.y--;
    }

    if ( inputs.count(INPUT::DOWN) ) {
        rect.y++;
    }
}
