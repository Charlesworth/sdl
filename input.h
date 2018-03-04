// Copyright 2018 Charles Cochrane

#ifndef INPUT_H_
#define INPUT_H_

#include <set>

// Player input enum
enum Input {
    UP,
    DOWN,
    LEFT,
    RIGHT,
    ENTER,
    QUIT
};

std::set<Input> GetInputs();

#endif  // INPUT_H_
