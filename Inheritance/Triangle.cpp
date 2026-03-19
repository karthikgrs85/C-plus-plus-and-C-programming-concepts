#include "Triangle.h"
#include <iostream>

Triangle::Triangle(const float& side1, const float& side2, const float& side3) : Shape(3, TRI),
m_side1(side1), m_side2(side2), m_side3(side3)
{
}
Triangle::~Triangle()
{
    std::cout << "\n Destroying Triangle with id = " << m_id;
}
void Triangle::calculateArea()
{
    float semiPerimeter = (m_side1 + m_side2 + m_side3) / 2;
    m_area = sqrt(semiPerimeter * (semiPerimeter - m_side1) * (semiPerimeter - m_side2) * (semiPerimeter - m_side3));
}
void Triangle::calculatePerimeter()
{
    m_perimeter = m_side1 + m_side2 + m_side3;
}
void Triangle::draw()
{

}
