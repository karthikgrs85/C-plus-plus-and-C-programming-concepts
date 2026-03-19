
#pragma once
#include "Shapes.h"
class Circle :
    public Shape
{
    float m_radius;
public:
    Circle(const float& radius);
    virtual void calculateArea();
    virtual void calculatePerimeter();
    virtual void draw();
    virtual void printData();
    virtual ~Circle();
	friend void drawCircle(const Circle& circle);
};

