// Copyright 2018 Charles Cochrane

#include "./player.h"

#include <stdio.h>
#include <vector>

#include "SDL2/SDL.h"

#include "./input.h"

Player::Player(SDL_Surface* player_texture) : texture_(player_texture) {
  x_position = 100.0;
  y_position = 100.0;
  rect_.w = k_player_width;
  rect_.h = k_player_height;
}

Player::Player(SDL_Surface* player_texture, float x_position, float y_position) :
texture_(player_texture), x_position(x_position), y_position(y_position) {
  rect_.w = k_player_width;
  rect_.h = k_player_height;
}

Player::~Player() {
  SDL_FreeSurface(texture_);
  texture_ = NULL;
}

void Player::Render(SDL_Surface* screenSurface) {
  SDL_BlitScaled(texture_, NULL, screenSurface, &rect_);
}

void Player::HandleInputs(std::set<INPUT> inputs) {
  float velocity;
  if ((inputs.count(INPUT::LEFT) || inputs.count(INPUT::RIGHT)) &&
  (inputs.count(INPUT::UP) || inputs.count(INPUT::DOWN))) {
    velocity = k_player_horizontal_vel;
  } else {
    velocity = k_player_axis_vel;
  }

  if ( inputs.count(INPUT::LEFT) ) {
    rect_.x -= velocity;
  }

  if ( inputs.count(INPUT::RIGHT) ) {
    rect_.x += velocity;
  }

  if ( inputs.count(INPUT::UP) ) {
    rect_.y -= velocity;
  }

  if ( inputs.count(INPUT::DOWN) ) {
    rect_.y += velocity;
  }
}
