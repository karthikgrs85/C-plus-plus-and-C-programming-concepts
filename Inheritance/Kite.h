#pragma once
#include <iostream>
#include "Quadrilateral.h"


class Kite :
    public Quadrilateral
{
public:
    Kite(const float& side1, const float& side2, const float& angle1, const float& angle2);
    

    virtual ~Kite();
    

    virtual void calculateArea();
    

    virtual void calculatePerimeter();
    

    virtual void draw();
    
};

