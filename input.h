#ifndef INPUT_H
#define INPUT_H

#include <set>

//Key press surfaces constants 
enum INPUT { 
    NO_INPUT, 
    UP, 
    DOWN, 
    LEFT, 
    RIGHT, 
    QUIT 
};

INPUT getInput();

std::set<INPUT> getInputs();
 
#endif