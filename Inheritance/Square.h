#pragma once
#include "Quadrilateral.h"
class Square :
    public Quadrilateral
{

public:
    Square(const float& side);

    virtual void calculateArea();

    virtual void calculatePerimeter();

    virtual void draw();

    virtual void printData();

    virtual ~Square();
};

