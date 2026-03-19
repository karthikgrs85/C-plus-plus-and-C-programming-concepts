#pragma once
#include "Quadrilateral.h"
class Rhombus :
    public Quadrilateral
//Rhombus class
{

    public:
        Rhombus(const float& length, const float& angle);

        virtual ~Rhombus();
        

        virtual void calculateArea();
        
        virtual void calculatePerimeter();
        
        virtual void draw();
       


};

