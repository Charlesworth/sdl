// Copyright 2018 Charles Cochrane

#ifndef OBJECT_H_
#define OBJECT_H_

#include <set>

#include "SDL2/SDL.h"

#include "./input.h"
#include "./renderer.h"

class Object {
 public:
    // The dimensions of the player
    static const int k_player_width = 20;
    static const int k_player_height = 20;

    // Axis and horizontal velocity of the player
    static constexpr float k_player_axis_vel = 1.0;
    static constexpr float k_player_horizontal_vel = 0.7;

    float x_position;
    float y_position;

    // Initializes the object with default starting x_position and y_position
    explicit Object(SDL_Texture* player_texture);

    // Initializes the object with defined x_position and y_position
    Object(SDL_Texture* player_texture, float x_position, float y_position);

    // Destroys the object
    ~Object();

    // Takes player input and does stuff
    void HandleInputs(std::set<Input>);

    // Render the player onto the screen
    void Render(Renderer*);

 private:
    SDL_Texture* texture_;
    SDL_Rect rect_;
};

#endif  // OBJECT_H_
