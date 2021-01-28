#pragma once


#include "CBase4618.h"

class CSketch : public CBase4618 {

public:

	int xpos, ypos, xpos2, ypos2;
	int width, height;
	bool count;
	int _color = 1;
	Point pt1;
	Point pt2;
	Scalar color;
	int thickness, lineType, shift;
	CSketch(int w, int h, int comport);
	~CSketch();
	void draw();
	void update();
	void run();
};
