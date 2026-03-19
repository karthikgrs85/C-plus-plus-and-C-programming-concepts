#pragma once
#include "Shapes.h"
#include <vector>

class Quadrilateral :
    public Shape
{
protected:
    std::vector<float> m_UniqueEdges;
    std::vector<float> m_Angles;//angle in degrees
    QuadType m_QuadType;
public:
    Quadrilateral();
    Quadrilateral(const float& side1, const float& side2, const float& side3, const float& side4,
        const float& angle1, const float& angle2,
        QuadType qtype);
        virtual ~Quadrilateral();
    

        virtual void calculateArea();
    
        virtual void printData();
    
        virtual void calculatePerimeter();
    

        virtual void draw();
    
};

