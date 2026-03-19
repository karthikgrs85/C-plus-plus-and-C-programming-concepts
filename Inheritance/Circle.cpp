#include "Circle.h"
#include <cmath>
#include <iostream>


void drawCircle(const Circle& circle)
{
    
    int i, j;
	float radius = circle.m_radius;
    for (i = 0; i <= 2 * radius; i++)
    {
        for (j = 0; j <= 2 * radius; j++)
        {
            double distance = sqrt((double)(i - radius) * (i - radius) + (j - radius) * (j - radius));
            if (distance > radius - 0.65 && distance < radius + 0.2)
            {
                std::cout << "**";
            }
            else
            {
                std::cout << "  ";
            }
        }
        std::cout << std::endl;
    }

}

Circle::Circle(const float& radius) : Shape(0, ShapeType::CIRCLE), m_radius(radius) {}
void Circle::calculateArea()
{
    m_area = pi * pow(m_radius, 2);
}
void Circle::calculatePerimeter()
{
    m_perimeter = 2 * pi * m_radius;
}
void Circle::draw()
{
    drawCircle(*this);
}
void Circle::printData()
{
    Shape::printData();
    std::cout << " The radius of the circle = " << m_radius << " units\n";
}
Circle::~Circle()
{
    std::cout << "\n Destroying Circle with id = " << m_id;
}