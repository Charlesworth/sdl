#ifndef INPUT_H
#define INPUT_H

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
 
#endif