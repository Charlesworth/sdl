#include "SDL2/SDL.h"
#include "input.h"

INPUT getInput() {
    SDL_Event e;

    if ( SDL_PollEvent( &e ) == 0 ) {
        // error here
        return NO_INPUT;
    }

    if( e.type == SDL_QUIT ) { 
        return QUIT; 
    }

    if( e.type == SDL_KEYDOWN ) {
        switch( e.key.keysym.sym ) {
            case SDLK_UP:
            case SDLK_w:
                return UP;
            case SDLK_DOWN:
            case SDLK_s:
                return DOWN;
            case SDLK_LEFT:
            case SDLK_a:
                return LEFT;
            case SDLK_RIGHT:
            case SDLK_d:
                return RIGHT;
            case SDLK_ESCAPE:
                return QUIT;
            default:
                return NO_INPUT;
        }
    }
}