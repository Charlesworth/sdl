// Copyright 2018 Charles Cochrane

#ifndef OBJECT_H_
#define OBJECT_H_

#include <set>
#include <memory>

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
    explicit Object(std::shared_ptr<SDL_Texture> player_texture);

    // Initializes the object with defined x_position and y_position
    Object(std::shared_ptr<SDL_Texture> player_texture, float x_position, float y_position);

    // Destroys the object
    ~Object();

    // Takes player input and does stuff
    void HandleInputs(std::set<Input>);

    // Render the player onto the screen
    void Render(std::shared_ptr<Renderer>);

    std::shared_ptr<SDL_Texture> GetTexture();

 private:
    std::shared_ptr<SDL_Texture> texture_;
    // InputComponent* input_;
    // PhysicsComponent* physics_;
};

// class InputComponent {
//  public:
//   virtual ~InputComponent() {}
//   virtual std::set<Input> GetInputs() = 0;
// };

// class PlayerInputComponent : public InputComponent {
//  public:
//   virtual std::set<Input> GetInputs() {
//     // Input code...
//   }
// };

// class PhysicsComponent {
//  public:
//   virtual ~PhysicsComponent() {}
//   virtual void Update(Object* object) = 0;
// };

// class PlayerPhysicsComponent : public PhysicsComponent {
//  public:
//   virtual void update(Object* object) {
//     // Physics code...
//   }
// };

// Object* createPlayer()
// {
//   return new GameObject(new PlayerInputComponent(),
//                         new BjornPhysicsComponent(),
//                         new BjornGraphicsComponent());
// }


#endif  // OBJECT_H_
