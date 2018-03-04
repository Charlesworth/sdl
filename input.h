// Copyright 2018 Charles Cochrane

#ifndef INPUT_H_
#define INPUT_H_

#include <set>

// Player input enum
enum Input {
    NO_INPUT,
    UP,
    DOWN,
    LEFT,
    RIGHT,
    QUIT
};

std::set<Input> GetInputs();

#endif  // INPUT_H_
