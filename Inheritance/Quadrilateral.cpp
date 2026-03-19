#include "Quadrilateral.h"
#include <iomanip>
#include <iostream>

Quadrilateral::Quadrilateral() :Shape() {};
Quadrilateral::Quadrilateral(const float& side1, const float& side2, const float& side3, const float& side4,
    const float& angle1, const float& angle2,
    QuadType qtype) :
    Shape(4, QUAD), m_QuadType(qtype)
{
    m_perimeter = 0;
    m_UniqueEdges.push_back(side1);
    m_UniqueEdges.push_back(side2);
    m_UniqueEdges.push_back(side3);
    m_UniqueEdges.push_back(side4);
    m_Angles.push_back(angle1);
    m_Angles.push_back(angle2);
}
Quadrilateral::~Quadrilateral()
{
    std::cout << "\n Destroying  Quadrilateral with id = " << m_id;
}

void Quadrilateral::calculateArea()
{
    float semiPerimeter = (m_UniqueEdges[0] + m_UniqueEdges[1] + m_UniqueEdges[2] + m_UniqueEdges[3]) / 2;
    m_area = sqrt((semiPerimeter - m_UniqueEdges[0]) * (semiPerimeter - m_UniqueEdges[1]) *
        (semiPerimeter - m_UniqueEdges[2]) * (semiPerimeter - m_UniqueEdges[3]));
}
void Quadrilateral::printData()
{
    std::cout << std::endl << "The Shape ID = " << m_id << "\n The Type of Shape is " << QuadTypeNames[m_QuadType] << "\n"
        << "The area = " << std::fixed << std::setprecision(2) << m_area << " square units\n"
        << "The perimeter = " << std::fixed << std::setprecision(2) << m_perimeter << " units" << std::endl;
}
void Quadrilateral::calculatePerimeter()
{
    std::vector<float>::const_iterator iter = m_UniqueEdges.begin();
    m_perimeter = 0;
    while (iter != m_UniqueEdges.end())
    {
        m_perimeter = *iter;
        ++iter;
    }
}

void Quadrilateral::draw()
{

}
