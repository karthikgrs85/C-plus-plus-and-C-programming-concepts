#include "Rectangle.h"
#include <iomanip>
#include <iostream>

Rectangle::Rectangle(const float& breadth, const float& length)
{
    m_QuadType = RECT;
    m_UniqueEdges.push_back(breadth);
    m_UniqueEdges.push_back(length);
    m_Angles.push_back(90);
}
Rectangle::~Rectangle()
{
    std::cout << "\n Destroying Rectangle with id = " << m_id;
}
void Rectangle::calculateArea()
{
    m_area = m_UniqueEdges[0] * m_UniqueEdges[1];
}
void Rectangle::calculatePerimeter()
{
    m_perimeter = 2 * (m_UniqueEdges[0] + m_UniqueEdges[1]);
}

void Rectangle::draw()
{
    draw_rect(m_UniqueEdges[0], m_UniqueEdges[1]);
}
void Rectangle::printData()
{
    Quadrilateral::printData();
    std::cout << " The length  = " << m_UniqueEdges[1] << " units\n";
    std::cout << " The breadth = " << m_UniqueEdges[0] << " units\n";
}

void draw_rect(int width, int height)
{

    std::cout << "+";
    for (int i = 0; i < width - 2; i++)
    {
        std::cout << "__";
    }
    std::cout << "+\n";

    for (int i = 0; i < height - 2; i++)
    {
        std::cout << "|";
        for (int j = 0; j < width - 2; j++)
        {
            std::cout << "  ";
        }
        std::cout << "|\n";
    }

    std::cout << "+";
    for (int i = 0; i < width - 2; i++)
    {
        std::cout << "__";
    }
    std::cout << "+\n";
}
