#pragma once
#include "Quadrilateral.h"
class Parallelogram :
    public Quadrilateral
{
public:
    Parallelogram(const float& breadth, const float& length, const float& angle);
 

    virtual ~Parallelogram();
    

    virtual void calculateArea();
   

    virtual void calculatePerimeter();
   
    virtual void draw();
    
};

