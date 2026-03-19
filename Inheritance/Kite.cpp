#include "Kite.h"
#include <cmath>

Kite::Kite(const float& side1, const float& side2, const float& angle1, const float& angle2)
{
    m_QuadType = KITE;
    m_UniqueEdges.push_back(side1);
    m_UniqueEdges.push_back(side2);
    m_Angles.push_back(angle1);
    m_Angles.push_back(angle2);
}

Kite:: ~Kite()
{
    std::cout << "\n Destroying Kite with id = " << m_id;
}

void Kite::calculateArea()
{
    float d1 = 2 * (m_UniqueEdges[0] * cos(pi / 180 * (m_Angles[0] / 2)));
    float d2 = 2 * (m_UniqueEdges[0] * sin(pi / 180 * (m_Angles[0] / 2)));
    m_area = 0.5 * (d1 * d2);
}

void Kite::calculatePerimeter()
{
    m_perimeter = 2 * (m_UniqueEdges[0] + m_UniqueEdges[1]);
}

void Kite::draw()
{
}