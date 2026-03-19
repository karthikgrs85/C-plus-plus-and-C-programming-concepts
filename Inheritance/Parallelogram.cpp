#include "Parallelogram.h"
#include <iostream>

    Parallelogram::Parallelogram(const float& breadth, const float& length, const float& angle)
    {
        m_QuadType = PARALLOGM;
        m_UniqueEdges.push_back(breadth);
        m_UniqueEdges.push_back(length);
        m_Angles.push_back(angle);
    }

     Parallelogram::~Parallelogram()
    {
        std::cout << "\n Destroying Parallelogram with id = " << m_id;
    }

    void Parallelogram::calculateArea()
    {
        float ht = m_UniqueEdges[0] * sin(pi / 180 * m_Angles[0]);
        m_area = m_UniqueEdges[1] * ht;
    }

    void Parallelogram::calculatePerimeter()
    {
        m_perimeter = 2 * (m_UniqueEdges[0] + m_UniqueEdges[1]);
    }
    void Parallelogram::draw()
    {

    }