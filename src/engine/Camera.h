#ifndef CAMERA_H
#define CAMERA_H

class Camera{ 

public:
	Camera();
	~Camera();

	int x = 0;
	int y = 0;
	int viewportWidth = 1920;
	int viewportHeight = 1000;
	double scaleX = 1;
	double scaleY = 1;

private:

	
};

#endif