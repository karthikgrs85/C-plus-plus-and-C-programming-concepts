#pragma once
#include "Shapes.h"
class Triangle :
    public Shape
{
    float m_side1, m_side2, m_side3;
public:
    Triangle(const float& side1, const float& side2, const float& side3);
    virtual ~Triangle();
    
    virtual void calculateArea();
 
    virtual void calculatePerimeter();
   
    virtual void draw();
};

