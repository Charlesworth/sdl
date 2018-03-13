// Copyright 2018 Charles Cochrane

#include "./object.h"

#include <stdio.h>
#include <vector>

#include "SDL2/SDL.h"

#include "./input.h"

Object::Object(std::shared_ptr<SDL_Texture> player_texture) :
texture_(player_texture) {
  x_position = 100.0;
  y_position = 100.0;
}

Object::Object(std::shared_ptr<SDL_Texture> player_texture, float x_position, float y_position) :
texture_(player_texture), x_position(x_position), y_position(y_position) {}

Object::~Object() {
  // TODO(charlesworth) something here?
}

void Object::Render(std::shared_ptr<Renderer> renderer) {
  renderer->Render(texture_, x_position, y_position, k_player_width, k_player_height);
}

std::shared_ptr<SDL_Texture> Object::GetTexture() {
  return texture_;
}

void Object::HandleInputs(std::set<Input> inputs) {
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
