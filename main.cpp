//Using SDL and standard IO
#include "SDL2/SDL.h"
#include <stdio.h>
#include <string>
#include "input.h"
#include "player.h"
#include <vector>
#include <iterator>
#include <memory>

//Screen dimension constants
const int SCREEN_WIDTH = 640;
const int SCREEN_HEIGHT = 480;

//Starts up SDL and creates window
bool init();

//Frees media and shuts down SDL
void close();

//The window we'll be rendering to
SDL_Window* gWindow = NULL;
	
//The surface contained by the window
SDL_Surface* gScreenSurface = NULL;

bool init()
{
	//Initialization flag
	bool success = true;

	//Initialize SDL
	if( SDL_Init( SDL_INIT_VIDEO | SDL_INIT_AUDIO ) < 0 )
	{
		printf( "SDL could not initialize! SDL_Error: %s\n", SDL_GetError() );
		success = false;
	}
	else
	{
		//Create window
		gWindow = SDL_CreateWindow( "SDL", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN );
		if( gWindow == NULL )
		{
			printf( "Window could not be created! SDL_Error: %s\n", SDL_GetError() );
			success = false;
		}
		else
		{
			//Get window surface
			gScreenSurface = SDL_GetWindowSurface( gWindow );
		}
	}

	return success;
}

void close()
{
	//Destroy window
	SDL_DestroyWindow( gWindow );
	gWindow = NULL;

	//Quit SDL subsystems
	SDL_Quit();
}

//Load image at specified path 
SDL_Surface* loadBMPSurface( std::string path ) { 
	//Load image at specified path
    SDL_Surface* loadedSurface = SDL_LoadBMP( path.c_str() ); if( loadedSurface == NULL ) { 
        printf( "Unable to load image %s! SDL Error: %s\n", path.c_str(), SDL_GetError() );
		return NULL;
    }

	//Convert surface to screen format
	SDL_Surface* optimizedSurface = SDL_ConvertSurface( loadedSurface, gScreenSurface->format, 0);
	if( optimizedSurface == NULL ){
		printf( "Unable to optimize image %s! SDL Error: %s\n", path.c_str(), SDL_GetError() );
		return NULL;
	}

	//Get rid of old loaded surface 
	SDL_FreeSurface( loadedSurface );
    
	return optimizedSurface; 
}

int main( int argc, char* args[] )
{
	bool quit = false;

	//Start up SDL and create window
	if( !init() )
	{
		printf( "Failed to initialize!\n" );
        return 1;
	}
	
	SDL_Surface* playerTexture = loadBMPSurface("assets/man.bmp");
    if( playerTexture == NULL) {
		quit = true;
	}	

	Player* charlie = new Player( playerTexture );
	
	// Background image
    SDL_Surface* gBackground = loadBMPSurface("assets/space.bmp");
    if( gBackground == NULL) {
		quit = true;
    }
	
    while(!quit) {
		// fill screen with background image
        SDL_BlitSurface( gBackground, NULL, gScreenSurface, NULL );
		
        //Handle events on queue
        std::set<INPUT> inputs = getInputs();
		
		if( inputs.count(INPUT::QUIT) ) { 
			//User requests quit 
			quit = true; 
		}
		
		charlie->handleInputs( inputs );
		charlie->render( gScreenSurface );
        
        //Update the surface
        SDL_UpdateWindowSurface( gWindow );
		
		SDL_Delay( 16 );
    }
	
    //Deallocate surfaces
	SDL_FreeSurface( gBackground );
	gBackground = NULL;
	
	delete charlie;
	
	//Free resources and close SDL
	close();
	
	return 0;
}