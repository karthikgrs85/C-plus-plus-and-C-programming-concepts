#pragma once
#include "Quadrilateral.h"
#include <iostream>

class Rectangle :
    public Quadrilateral
{
public:
    Rectangle(const float& breadth, const float& length);
    
    virtual ~Rectangle();
    
    virtual void calculateArea();

    virtual void calculatePerimeter();

    virtual void draw();
    
    virtual void printData();

};
void draw_rect(int width, int height);