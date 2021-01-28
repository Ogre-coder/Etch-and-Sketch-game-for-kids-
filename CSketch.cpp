#include "stdafx.h"
#include "CSketch.h"
#include "time.h"
#include "conio.h"
#include "CControl.h"

CSketch::CSketch(int w, int h, int comport)
{
    width = w;
    height = h;
    Control.init_com(comport);
    Size size(w, h);
    _canvas = Mat::zeros(size, CV_8UC3);
    //waitKey(1);
}

CSketch::~CSketch()
{

}

void CSketch::draw()
{
    if (count == true)
    {
        _canvas = Mat::zeros(Size(width, height), CV_8UC3);
        count = false;

    }
    else
    {
        line(_canvas, pt1, pt2, color, thickness = 1, lineType = LINE_AA);
        imshow("blank", _canvas);
        waitKey(1);
    }

}

void CSketch::update()
{
    Control.get_analog();
    ypos2 = ((100 - Control.pos1) * _canvas.size().height) / 100;
    xpos2 = ((Control.pos2 * (_canvas.size().width) * 3) / 100) - _canvas.size().width;

    if (xpos2 < 0)
    {
        xpos2 = 2;
    }
    else if (xpos2 > _canvas.size().width)
    {
        xpos2 = _canvas.size().width - 4;
    }
    else if (ypos2 > (_canvas.size().height - 3))
    {
        ypos2 = _canvas.size().height - 5;
    }
    else if (ypos2 < 3)
    {
        ypos2 = 3.5;
    }

    pt2 = Point(xpos2, ypos2);


    Control.get_button(32);
    if (Control.button_count == true)
    {
        count = true;
        Control.button_count = false;
    }

    Control.get_button(33);

    if (Control.button_count == true && _color == 0)
    {
        color = Scalar(0, 0, 255);
        _color++;
        Control.button_count = false;
        Control.set_data(0, 39, 1);
        Control.set_data(0, 38, 0);
        Control.set_data(0, 37, 0);
    }
    else if (Control.button_count == true && _color == 1)
    {
        color = Scalar(0, 255, 0);
        _color++;
        Control.button_count = false;
        Control.set_data(0, 38, 1);
        Control.set_data(0, 39, 0);
        Control.set_data(0, 37, 0);
    }
    else if (Control.button_count == true && _color == 2)
    {
        color = Scalar(255, 0, 0);
        _color = 0;
        Control.button_count = false;
        Control.set_data(0, 37, 1);
        Control.set_data(0, 38, 0);
        Control.set_data(0, 39, 0);
    }
}

void CSketch::run()
{
    Control.get_analog();
    ypos = ((100 - Control.pos1) * _canvas.size().height) / 100;
    xpos = (Control.pos2 * _canvas.size().width) / 100;
    Control.set_data(0, 39, 1);
    Control.set_data(0, 38, 0);
    Control.set_data(0, 37, 0);
    color = Scalar(0, 0, 255);
    pt1 = Point(xpos, ypos);

    while (!(kbhit() == 'q'))
    {
        update();
        draw();
        pt1 = pt2;
    }

}