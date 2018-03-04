// Copyright 2018 Charles Cochrane

#ifndef PLAYER_H_
#define PLAYER_H_

#include <set>

#include "SDL2/SDL.h"

#include "./input.h"

class Player {
 public:
    // The dimensions of the player
    static const int k_player_width = 20;
    static const int k_player_height = 20;

    // Axis and horizontal velocity of the player
    static const int k_player_axis_vel = 10;
    static const int k_player_horizontal_vel = 7;

    float x_position;
    float y_position;

    // Initializes the player with default starting x_position and y_position
    explicit Player(SDL_Surface* player_texture);

    // Initializes the player with defined x_position and y_position
    Player(SDL_Surface* player_texture, float x_position, float y_position);

    // Destroys the player
    ~Player();

    // Takes player input and does stuff
    void HandleInputs(std::set<INPUT>);

    // Render the player onto the screen
    void Render(SDL_Surface*);

 private:
    SDL_Surface* texture_;
    SDL_Rect rect_;
};

#endif  // PLAYER_H_
