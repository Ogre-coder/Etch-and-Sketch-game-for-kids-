#include "stdafx.h"
#include "CPong.h"
#include "time.h"
#include "conio.h"
#include "CControl.h"

CPong::CPong(int w, int h, int comport)
{
    width = w;
    height = h;
    Control.init_com(comport);
    Size size(w,h);
    _canvas = Mat::zeros(size , CV_8UC3);
    //waitKey(1);
}

CPong::~CPong()
{

}

void CPong::draw()
{
        auto calc_start = steady_clock::now();

        rectangle(_canvas, r, color, FILLED);
        circle(_canvas, center, 8, color, FILLED);

        imshow("blank", _canvas);
        //waitKey(1);

        auto calc_end = steady_clock::now();
        auto calc_elapsed = duration_cast<milliseconds>(calc_end - calc_start);

        elapsed_time = calc_elapsed.count();
        
        //FPS = 1 / elapsed_time;
}

void CPong::update()
{
        Control.get_analog();
        ypos2 = ((100 - Control.pos1) * _canvas.size().height) / 100;
       // xpos2 = ((Control.pos2 * (_canvas.size().width) * 3) / 100) - _canvas.size().width;
        xpos2 = 2;

        if (ypos2 > (_canvas.size().height - 94))
        {
            ypos2 = _canvas.size().height - 94;
        }
        else if (ypos2 < 3)
        {
            ypos2 = 3.5;
        }

        r = Rect(xpos2, ypos2, 13, 90);


        center.x = _canvas.size().width * rand() / RAND_MAX;
        center.y = _canvas.size().height * rand() / RAND_MAX;

        //center = Point( elapsed_time * 2 + center.x , elapsed_time * 2 + center.y);
       
}

void CPong::run()
{

    Control.get_analog();
    ypos = ((100 - Control.pos1) * _canvas.size().height) / 100;
    xpos = 2;
    color = Scalar(255, 255, 255);
    r = Rect(xpos, ypos, 13, 90);
    center = Point(_canvas.size().width / 2, _canvas.size().height / 2);

    while (!(kbhit() == 'q')) 
    {
        draw();
        update();
        _canvas = Mat::zeros(Size(width, height), CV_8UC3);
    }

}