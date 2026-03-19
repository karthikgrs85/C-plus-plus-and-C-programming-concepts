#include "Shapes.h"
#include <iomanip>
#include <iostream>

int Shape::id = 0;

const char* ShapeTypeNames[MAX_SHAPES] =
{
    "Circle",
    "Triangle",
    "Quadrilateral",
    "Undefined"
};

const char* QuadTypeNames[MAX_QUADTYPES] =
{
    "Square",
    "Rectangle",
    "Rhombus",
    "Parallelogram",
    "Trapezoid",
    "Kite",
    "Convex Quadrilateral",
    "Concave Quadrilateral",
    "Undefined"
};

Shape::Shape() :m_id(++id), m_numEdges(0), m_area(0), m_perimeter(0), m_shapeType(UNDEF_SHAPE) {};
Shape::Shape(const int& edges, const ShapeType& stype) :m_numEdges(edges), m_shapeType(stype), m_id(++id) {};
Shape:: ~Shape()
{
    std::cout << "\n Destroying shape :" << m_id;
}
void Shape::printData()
{
    std::cout << std::endl << "The Shape ID = " << m_id << "\n The Type of Shape is "
        << ShapeTypeNames[m_shapeType] << "\n"
        << "The area = " << std::fixed << std::setprecision(2) << m_area << " square units\n"
        << "The perimeter = " << std::fixed << std::setprecision(2) << m_perimeter << std::endl;
}

int Shape::getID()
{
    return m_id;
}