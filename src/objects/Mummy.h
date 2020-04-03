#ifndef MUMMY_H
#define MUMMY_H

#include "Enemy.h"
#include "../engine/AnimatedSprite.h"

using namespace std;

class Mummy : public Enemy{
    public:
        Mummy(string id);
};

#endif