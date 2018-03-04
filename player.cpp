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
		static const int PLAYER_AXIS_VEL = 10;
        static const int PLAYER_HORIZONTAL_VEL = 7;

		//Initializes the player with default starting posX and posY
		Player( SDL_Surface* playerTexture );

		//Initializes the player with defined posX and posY
        Player( SDL_Surface* playerTexture, int posX, int posY );
        
        //Destroys the player
		~Player();

		//Takes player input and does stuff
		void handleInputs( std::set<INPUT> );

		//Render the player onto the screen
		void render( SDL_Surface* );

    private:
        SDL_Surface* _texture;
        SDL_Rect _rect;    
};

Player::Player( SDL_Surface* playerTexture ) : _texture(playerTexture)
{
    _rect.x = 30;
	_rect.y = 30;
	_rect.w = PLAYER_WIDTH;
	_rect.h = PLAYER_HEIGHT;
}

Player::Player( SDL_Surface* inputTexture, int posX, int posY ) : _texture(inputTexture)
{
    _rect.x = posX;
	_rect.y = posY;
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
    float velocity;
    if ( ( inputs.count(INPUT::LEFT) || inputs.count(INPUT::RIGHT) ) && ( inputs.count(INPUT::UP) || inputs.count(INPUT::DOWN) ) ) {
        velocity = PLAYER_HORIZONTAL_VEL;
    } else {
        velocity = PLAYER_AXIS_VEL;    
    }

    if ( inputs.count(INPUT::LEFT) ) {
        _rect.x -= velocity;
    }

    if ( inputs.count(INPUT::RIGHT) ) {
        _rect.x += velocity;
    }

    if ( inputs.count(INPUT::UP) ) {
        _rect.y -= velocity;
    }

    if ( inputs.count(INPUT::DOWN) ) {
        _rect.y += velocity;
    }
}
