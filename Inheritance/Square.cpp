#include "Square.h"
#include <iomanip>
#include "Rectangle.h"


    Square::Square(const float& side)
    {
        m_QuadType = SQ;
        m_UniqueEdges.push_back(side);
        m_Angles.push_back(90);
    }
    void Square::calculateArea()
    {
        m_area = pow(m_UniqueEdges[0], 2);
    }

    void Square::calculatePerimeter()
    {
        m_perimeter = 4 * m_UniqueEdges[0];
    }

    void Square::draw()
    {
        draw_rect(m_UniqueEdges[0], m_UniqueEdges[0]);
    }
    void Square::printData()
    {
        Quadrilateral::printData();
        std::cout << "The side = " << m_UniqueEdges[0] << " units\n";
    }
    Square::~Square()
    {
        std::cout << "\n Destroying Square with id = " << m_id;
    }
