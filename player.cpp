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
        SDL_Surface* _texture;
        SDL_Rect _rect;    
};

Player::Player( SDL_Surface* inputTexture ) : _texture(inputTexture)
{
    _rect.x = 30;
	_rect.y = 30;
	_rect.w = PLAYER_WIDTH;
	_rect.h = PLAYER_HEIGHT;
}

Player::~Player()
{
    SDL_FreeSurface( _texture );
    _texture = NULL;
}

void Player::render( SDL_Surface* screenSurface )
{
    SDL_BlitScaled( _texture, NULL, screenSurface, &_rect );
}

void Player::handleInputs( std::set<INPUT> inputs ) {
    if ( inputs.count(INPUT::LEFT) ) {
        _rect.x--;
    }

    if ( inputs.count(INPUT::RIGHT) ) {
        _rect.x++;
    }

    if ( inputs.count(INPUT::UP) ) {
        _rect.y--;
    }

    if ( inputs.count(INPUT::DOWN) ) {
        _rect.y++;
    }
}
