#include "AnimatedSprite.h"
#include "Game.h"
#include <string>
#include <iostream>
#include <fstream>
#include <sstream>


using namespace std;

AnimatedSprite::AnimatedSprite() : Sprite() {
    this->type = "AnimatedSprite";
}

AnimatedSprite::AnimatedSprite(string id) : Sprite(id, 0, 0, 0) {
    this->type = "AnimatedSprite";
}

AnimatedSprite::AnimatedSprite(string id, string spritesheet, string xml) : Sprite(id, 0,0,0){
   vector<string> lines;
   std::ifstream infile(xml);
   string line;
    while (getline(infile, line)){
        istringstream iss(line);
        lines.push_back(line);
        //cout << "Adding line to vector " << endl;
    }
    for (int i = 22; i < lines.size()-1; i++){
       // cout << lines[i]<<endl;
        istringstream in(lines[i]);
        vector<string> temp;
        string t;
        while (in >> t) {
            temp.push_back(t);
        }
        split.push_back(temp); //Vector of vectors representing the parsed xml data.
    }
    /*FORMAT OF THE XML DATA:
    Vector of vectors -> each vector is a line from the xml document

    The x position is at position 2
    The y position is at position 3
    The width is at position 4
    The height is at position 5

    Each sub-vector represents a new frame in the animation.  */
}



AnimatedSprite::~AnimatedSprite() {
    for (Animation* an : animations) {
        for (int i = 0; i < an->numFrames; i++) {// this needs to be an iterator loop
            if(an->frames[i]->image != NULL) SDL_FreeSurface(an->frames[i]->image);
	        if(an->frames[i]->texture != NULL && Game::renderer != NULL) SDL_DestroyTexture(an->frames[i]->texture);
            delete an->frames[i];
        }
        delete an->frames;
        delete an;
    }
}

void AnimatedSprite::addAnimation(string basepath, string animName, int numFrames, int frameRate, bool loop) {
    Animation* anim = new Animation();
    anim->basepath = basepath;
    anim->animName = animName;
    anim->numFrames = numFrames;
    anim->frameRate = frameRate;
    anim->loop = loop;
    anim->curFrame = 0;
    anim->frames = new Frame*[numFrames]; // new frame pointer array of size numFrames;
    for (int i = 0; i < numFrames; i++ ) {
        Frame* f = new Frame();
        string path = basepath + animName + "_" + to_string(i+1) + ".png";
        f->image = IMG_Load(path.c_str());
        f->texture = SDL_CreateTextureFromSurface(Game::renderer, f->image);
        anim->frames[i] = f;
    }
    animations.push_back(anim);
}

void AnimatedSprite::addAnimationFromSpriteSheet(string texture, string animName, int numFrames, int frameRate, bool loop){
    //for each sprite in the spritesheet:
        //new frame
        //no need for a path, just need the location of the image
        //f->image is the render copy of that location of the sprite sheet
        //f->texture is the render copy of that entire spritesheet
        cout << "Loading Sprites From SpriteSheet";
        Animation* anim = new Animation();
        anim->basepath = texture;
        anim->animName = animName;
        anim->numFrames = numFrames;
        anim->frameRate = frameRate;
        anim->loop = loop;
        anim->curFrame = 0;
        anim->frames = new Frame*[numFrames];
        SDL_RendererFlip flip;

        int startPos = getAnimationPosition(anim->animName);

        for (int i = startPos; i < numFrames+startPos; i++){
            Frame* f = new Frame();
            string name = split[i][1];
            cout << "." << std::flush;

            //cout << name << endl;

            f->image = IMG_Load(anim->basepath.c_str());
            SDL_SetSurfaceBlendMode(f->image, SDL_BLENDMODE_NONE); 
            f->texture = SDL_CreateTextureFromSurface(Game::renderer, f->image);

            int xVal = stoi(split[i][2].substr(3).substr(0, split[i][2].substr(3).length()-1));
            int yVal = stoi(split[i][3].substr(3).substr(0, split[i][3].substr(3).length()-1));
            int wVal = stoi(split[i][4].substr(3).substr(0, split[i][4].substr(3).length()-1));
            int hVal = stoi(split[i][5].substr(3).substr(0, split[i][5].substr(3).length()-3));


            SDL_Texture* result = SDL_CreateTexture(Game::renderer, SDL_PIXELFORMAT_RGBA32, SDL_TEXTUREACCESS_TARGET, wVal, hVal);
            SDL_SetTextureBlendMode(result, SDL_BLENDMODE_BLEND);
    
            SDL_SetRenderTarget(Game::renderer, result);
            SDL_Rect srcrect = { xVal, yVal, wVal, hVal };

            SDL_RenderCopy(Game::renderer, f->texture, &srcrect, NULL); //already set the render target.
            f->texture = result;
            SDL_SetTextureAlphaMod(f->texture, 0);

            //SDL_SetTextureColorMod(f->texture, 255, 0, 0 );
            SDL_SetRenderTarget(Game::renderer, NULL);

            anim->frames[i-startPos] = f;

        }
        animations.push_back(anim);
        cout << "Animation \"" << anim->animName << "\" Added" << endl;

}

int AnimatedSprite::getAnimationPosition(string animName){
    for (int i = 0; i < split.size(); i++){
        if (split[i][1].find(animName) != std::string::npos){
            //cout << "Starting position is" << i;
            return i;
        }
    }
    return -1;
}


Animation* AnimatedSprite::getAnimation(string animName) {
    for (int i = 0; i < animations.size(); i++) {
        if (animations[i]->animName == animName) {
            //cout << animations[i]->animName;
            return animations[i];
        }
    }
    return NULL;
}

void AnimatedSprite::play(string animName) {
    Animation* anim = getAnimation(animName);
    if (anim != NULL) {
        this->current = anim;
        this->current->curFrame = 0;
        frameCount = 0;
        playing = true;
        //cout << "playing" << endl;
    }
}

void AnimatedSprite::replay() {
    if (this->current != NULL) {
        current->curFrame = 0;
        frameCount = 0;
        playing = true;
    }
}

void AnimatedSprite::stop() {
    this->playing = false;
}

string AnimatedSprite::currentAnimName() {
	if (current == NULL) {
		return "";
	}
	else {
		return current->animName;
	}
}

void AnimatedSprite::update(set<SDL_Scancode> pressedKeys, vector<ControllerState *> controllerStates) {
    Sprite::update(pressedKeys, controllerStates);
    if (playing) {
        frameCount++;
        if (frameCount % current->frameRate == 0) {
            // increment local frame counter
            current->curFrame++;
            // check for array out of bounds
            if (current->curFrame >= current->numFrames) {
                // reset the animation
                current->curFrame = 0;
                // check for looping
                if (!current->loop) {
                    stop();
                }
            }
            //cout << "Setting texture" << endl;
            DisplayObject::setTexture(current->frames[current->curFrame]->texture);
        }

    }

}

void AnimatedSprite::draw(AffineTransform &at) {
    Sprite::draw(at);
}

void AnimatedSprite::writeSceneData(ostream &stream) {
	stream << type << " ";
	stream << id << " ";
	stream << position.x << " ";
	stream << position.y << " ";
	stream << pivot.x << " ";
	stream << pivot.y << " ";
	stream << scaleX << " ";
	stream << scaleY << " ";
	stream << rotation << " ";
	stream << height << " ";
	stream << width << " ";
	stream << alpha << " ";
	stream << animations.size();
	// Animation args
	if (parent != NULL && parent->type != "Scene") {
		stream << " " << parent->id;
	}
	stream << endl;
	for (Animation * animation : animations) {
		stream << animation->basepath << " ";
		stream << animation->animName << " ";
		stream << animation->numFrames << " ";
		stream << animation->frameRate << " ";
		stream << animation->loop << endl;
	}
}
