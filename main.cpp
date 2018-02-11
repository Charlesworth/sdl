//Using SDL and standard IO
#include "SDL2/SDL.h"
#include <stdio.h>
#include <string>
#include "input.h"
#include <vector>
#include <iterator>

//Screen dimension constants
const int SCREEN_WIDTH = 640;
const int SCREEN_HEIGHT = 480;

//Starts up SDL and creates window
bool init();

//Loads media
bool loadMedia();

//Frees media and shuts down SDL
void close();

//Main loop flag 
bool quit = false;

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
		gWindow = SDL_CreateWindow( "SDL Tutorial", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN );
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
SDL_Surface* loadSurface( std::string path ) { 
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
	//Start up SDL and create window
	if( !init() )
	{
		printf( "Failed to initialize!\n" );
        return 1;
	}

    //The image we will load and show on the screen
    SDL_Surface* gHelloWorld = loadSurface("man.bmp");
    if( gHelloWorld == NULL) {
        quit = true;
    }

    //Event handler
	int x = 10;
	int y = 10;

    while(!quit) {
        //Handle events on queue
        std::set<INPUT> inputs = getInputs();

		if( inputs.count(INPUT::QUIT) ) { 
			//User requests quit 
			quit = true; 
		}

		if ( inputs.count(INPUT::LEFT) ) {
			x--;
		}

		if ( inputs.count(INPUT::RIGHT) ) {
			x++;
		}

		if ( inputs.count(INPUT::UP) ) {
			y--;
		}

		if ( inputs.count(INPUT::DOWN) ) {
			y++;
		}


		SDL_Rect man;
		man.x = x;
		man.y = y;
		man.w = 40;
		man.h = 40;

		SDL_BlitScaled( gHelloWorld, NULL, gScreenSurface, &man );

        // Use this for any background image
        // SDL_BlitSurface( gHelloWorld, NULL, gScreenSurface, NULL );
        
        //Update the surface
        SDL_UpdateWindowSurface( gWindow );

		SDL_Delay( 16 );
    }

    //Deallocate surface
	SDL_FreeSurface( gHelloWorld );
	gHelloWorld = NULL;

	//Free resources and close SDL
	close();

	return 0;
}