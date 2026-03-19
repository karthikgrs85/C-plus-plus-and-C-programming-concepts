#pragma once
#include "Quadrilateral.h"
class Trapezoid :
    public Quadrilateral
{
public:
    Trapezoid(const float& base, const float& secondSide, const float& thirdSide,
        const float& fourthSide, const float& angle);
    

    virtual ~Trapezoid();
    

    virtual void calculateArea();
    

    virtual void calculatePerimeter();
   

    virtual void draw();
    
};

