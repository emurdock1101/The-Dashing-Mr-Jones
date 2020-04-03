#ifndef MUMMY_H
#define MUMMY_H

#include "Enemy.h"
#include "AnimatedSprite.h"

using namespace std;

class Mummy : public Enemy{
    public:
        Mummy(string id);
};

#endif