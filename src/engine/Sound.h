#ifndef SOUND_H
#define SOUND_H

#include <string>

using namespace std;

class Sound {

public:
	Sound();
	~Sound();
	
	void playSFX(string soundFilePath);
    void playMusic(string soundFilePath);

private:

};

#endif