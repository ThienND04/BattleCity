#ifndef INPUT_H

#define INPUT_H
#include"lib.h"

struct Input{
    enum Type{
        QUIT, 
        // move
        A, 
        W, 
        S,
        D, 
        K, // Enter
        SHIFT, // change selection
        NONE 
    };
    Type type;
    void clear();
};

#endif