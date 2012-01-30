#ifndef AnimationBuffer_h
#define AnimationBuffer_h

#include <vector>

using namespace std;

class AnimFrame{
public:
	float translate[4];
	float rotate[4];
};

class Animation{
public:
	vector<vector<float> > Animations;
	float interpRatio;
	int frames;
	Animation();
	Animation(float * frames, int frameCount, int boneCount);
};

#endif
