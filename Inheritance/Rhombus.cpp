#include "Rhombus.h"
#include <iostream> 

Rhombus::Rhombus(const float& length, const float& angle)
{
    m_QuadType = RHOMBUS;
    m_UniqueEdges.push_back(length);
    m_Angles.push_back(angle);
}
Rhombus::~Rhombus()
{
    std::cout << "\n Destroying Rhombus with id = " << m_id;
}

void Rhombus::calculateArea()
{
    m_area = pow(m_UniqueEdges[0], 2) * sin(pi / 180 * m_Angles[0]);
}
void Rhombus::calculatePerimeter()
{
    m_perimeter = 4 * (m_UniqueEdges[0]);
}
void Rhombus::draw()
{
}