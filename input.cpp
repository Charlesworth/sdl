#include "SDL2/SDL.h"
#include "input.h"
#include <vector>
#include <set>


INPUT getInput() {
    SDL_Event e;

    if ( SDL_PollEvent( &e ) == 0 ) {
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

std::vector<INPUT> getKeydownInputs() {
    std::vector<INPUT> inputVector;
    SDL_Event e;

    while ( SDL_PollEvent( &e ) != 0 ) {
        // Check for quit events
        if( e.type == SDL_QUIT || (e.key.type == SDL_KEYDOWN && e.key.keysym.sym == SDLK_ESCAPE) ) {
            std::vector<INPUT> quitVector = {QUIT};
            return quitVector;
        }

        if( e.key.type == SDL_KEYDOWN ) {
            switch( e.key.keysym.sym ) {
                case SDLK_UP:
                case SDLK_w:
                    inputVector.push_back(UP);
                    continue;
                case SDLK_DOWN:
                case SDLK_s:
                    inputVector.push_back(DOWN);
                    continue;
                case SDLK_LEFT:
                case SDLK_a:
                    inputVector.push_back(LEFT);
                    continue;
                case SDLK_RIGHT:
                case SDLK_d:
                    inputVector.push_back(RIGHT);
                    continue;
                default:
                    continue;
            }
        }
    }

    return inputVector;
}

std::set<INPUT> getInputs() {
    SDL_Event e;
    
    while ( SDL_PollEvent( &e ) != 0 ) {
        // Check for quit events
        if( e.type == SDL_QUIT ) {
            return std::set<INPUT>{QUIT};
        }
    }
    
    // All events must be processed before checking GetKeyboardState
    const Uint8 *keys = SDL_GetKeyboardState(NULL);
    
    // Check for quit keys
    if( keys[SDL_SCANCODE_ESCAPE] ) {
        return std::set<INPUT>{QUIT};
    }
    
    // Process key presses
    std::set<INPUT> inputSet;

    if (keys[SDL_SCANCODE_W] || keys[SDL_SCANCODE_UP]){
        inputSet.insert(UP);
    }

    if (keys[SDL_SCANCODE_S] || keys[SDL_SCANCODE_DOWN]){
        inputSet.insert(DOWN);
    }

    if (keys[SDL_SCANCODE_A] || keys[SDL_SCANCODE_LEFT]){
        inputSet.insert(LEFT);
    }

    if (keys[SDL_SCANCODE_D] || keys[SDL_SCANCODE_RIGHT]){
        inputSet.insert(RIGHT);
    }
    return inputSet;
}


