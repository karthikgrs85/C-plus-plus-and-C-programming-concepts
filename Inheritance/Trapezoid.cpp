#include "Trapezoid.h"
#include <iostream>

Trapezoid::Trapezoid(const float& base, const float& secondSide, const float& thirdSide,
    const float& fourthSide, const float& angle)
{
    m_QuadType = TRAPEZM;
    m_UniqueEdges.push_back(base);
    m_UniqueEdges.push_back(secondSide);
    m_UniqueEdges.push_back(thirdSide);
    m_UniqueEdges.push_back(fourthSide);
    m_Angles.push_back(angle);
}

Trapezoid::~Trapezoid()
{
    std::cout << "\n Destroying Trapezoid with id = " << m_id;
}

void Trapezoid::calculateArea()
{
    float ht = m_UniqueEdges[1] * sin(pi / 180 * m_Angles[0]);
    m_area = 0.5 * (m_UniqueEdges[0] + m_UniqueEdges[2]) * ht;
}

void Trapezoid::calculatePerimeter()
{
    m_perimeter = m_UniqueEdges[0] + m_UniqueEdges[1] + m_UniqueEdges[2] + m_UniqueEdges[3];
}

void Trapezoid::draw()
{
}