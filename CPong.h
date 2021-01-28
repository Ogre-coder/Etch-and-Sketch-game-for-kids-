#pragma once

#include "CBase4618.h"

class CPong : public CBase4618 {

public:
	
	int xpos, ypos, xpos2, ypos2;
	int width, height;
	bool count;
	int _color = 1;
	float FPS;
	Rect r;
	Point center;
	Scalar color;
	int thickness, lineType, shift;
	float elapsed_time;
	CPong(int w, int h, int comport);
	~CPong();
	void draw();
	void update();
	void run();
};
