#ifndef TWEENTRANSITIONS_H
#define TWEENTRANSITIONS_H

#include <string>
#include <fstream>

using namespace std;

class TweenTransitions {

public:
   void applyTransition(double percentDone);
   void easeInOut(double percentDone);
private:
    
};

#endif