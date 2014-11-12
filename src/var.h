#include "ofAppGLFWWindow.h"
#include "ofMain.h"

ofShader normal,tex,bump,toon,kal;
ofEasyCam camera;
ofImage img;

bool sphere;
bool bAnimate;
bool bAnimateMouse;
float animationPosition;
int w,h;
