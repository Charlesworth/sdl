// Copyright 2018 Charles Cochrane

#include "./player.h"

#include <stdio.h>
#include <vector>

#include "SDL2/SDL.h"

#include "./input.h"

Player::Player(SDL_Texture* player_texture) :
texture_(player_texture) {
  x_position = 100.0;
  y_position = 100.0;
  rect_.w = k_player_width;
  rect_.h = k_player_height;
}

Player::Player(SDL_Texture* player_texture, float x_position, float y_position) :
texture_(player_texture), x_position(x_position), y_position(y_position) {
  rect_.w = k_player_width;
  rect_.h = k_player_height;
}

Player::~Player() {
  SDL_DestroyTexture(texture_);
  texture_ = NULL;
}

void Player::Render(SDL_Renderer* renderer) {
  rect_.x = x_position;
  rect_.y = y_position;
  SDL_RenderCopy(renderer, texture_, NULL, &rect_);
}

void Player::HandleInputs(std::set<Input> inputs) {
  float velocity;

  if ((inputs.count(Input::LEFT) || inputs.count(Input::RIGHT)) &&
  (inputs.count(Input::UP) || inputs.count(Input::DOWN))) {
    velocity = k_player_horizontal_vel;
  } else {
    velocity = k_player_axis_vel;
  }

  if (inputs.count(Input::LEFT)) {
    x_position -= velocity;
  }

  if (inputs.count(Input::RIGHT)) {
    x_position += velocity;
  }

  if (inputs.count(Input::UP)) {
    y_position -= velocity;
  }

  if (inputs.count(Input::DOWN)) {
    y_position += velocity;
  }
}
