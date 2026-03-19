#pragma once

#define pi 3.14159
enum ShapeType
{
    CIRCLE = 0,
    TRI,
    QUAD,
    UNDEF_SHAPE,
    MAX_SHAPES
};

enum QuadType
{
    SQ,
    RECT,
    RHOMBUS,
    PARALLOGM,
    TRAPEZM,
    KITE,
    CONVEXQUAD,
    CONCAVEQUAD,
    UNDEF_QUADTYPE,
    MAX_QUADTYPES
};

extern const char* QuadTypeNames[MAX_QUADTYPES];
extern const char* ShapeTypeNames[MAX_SHAPES];

class Shape {

protected:
    int m_numEdges, m_id;
    float m_area, m_perimeter;
    ShapeType m_shapeType;

    static int id;

public:
    Shape();
    Shape(const int& edges, const ShapeType& stype);
    virtual ~Shape();
    virtual void printData();

    int getID();

    //Pure Virtual Function to be defined in derived class
    virtual void calculateArea() = 0;
    virtual void calculatePerimeter() = 0;
    virtual void draw() = 0;
};


