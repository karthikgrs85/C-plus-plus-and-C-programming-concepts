/******************************************************************************

                              Online C++ Compiler.
               Code, Compile, Run and Debug C++ program online.
Write your code in this editor and press "Run" button to compile and execute it.

*******************************************************************************/

#include <iostream>
#include <math.h>
#include <iomanip>
#include <vector>
#include <algorithm>

#define pi 3.14159

using namespace std;

void SortAndRemoveDuplicateElementsFromVector(vector<float>& edges)
{
    sort(edges.begin(), edges.end());
    vector<float>::const_iterator lastUnique = std::unique(edges.begin(), edges.end());
    edges.erase(lastUnique, edges.end());
}

void drawCircle(const float& radius)
{
    int i,j;
    for (i=0; i<=2*radius; i++)
    {
        for (j=0; j<=2*radius; j++)
        {
            double distance = sqrt((double)(i-radius)*(i-radius) + (j-radius)*(j-radius));
            if (distance>radius-0.65 && distance<radius+0.2)
            {
                std::cout << "**";
            }
            else
            { 
                std::cout << "  ";
            }
        }
        std::cout << std::endl;
    }
    
}

void draw_rect(int width,int height) 
{
    using std::cout;
    cout << "+";
    for (int i = 0; i < width - 2; i++)
    {
        cout << "__";
    }
    cout << "+\n";

    for (int i = 0; i < height - 2; i++)
    {
        cout << "|";
        for (int j = 0; j < width - 2; j++)
        {
            cout << "  ";
        }
        cout << "|\n";
    }

    cout << "+";
    for (int i = 0; i < width - 2; i++)
    {
        cout << "__";
    }
    cout << "+\n";
}

enum ShapeType
{
    CIRCLE= 0,
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

const char *ShapeTypeNames[MAX_SHAPES] =
{
    "Circle",
    "Triangle",
    "Quadrilateral",
    "Undefined"
};

const char *QuadTypeNames[MAX_QUADTYPES] =
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

                
class Shape{
    
protected:
    int m_numEdges, m_id;
    float m_area, m_perimeter;
    ShapeType m_shapeType;

    static int id;
    
public:
    Shape():m_id(++id), m_numEdges(0), m_area(0), m_perimeter(0), m_shapeType(UNDEF_SHAPE){};
    Shape(const int& edges, const ShapeType& stype):m_numEdges(edges), m_shapeType(stype), m_id(++id){};
    virtual ~Shape()
    {
        std::cout<<"\n Destroying shape :"<<m_id;
    }
    virtual void printData()
    {
        std::cout<<std::endl<<"The Shape ID = "<<m_id<<"\n The Type of Shape is "
        <<ShapeTypeNames[m_shapeType]<<"\n"
        <<"The area = "<<std::fixed<<std::setprecision(2)<<m_area<<" square units\n"
        <<"The perimeter = "<<std::fixed<<std::setprecision(2)<<m_perimeter<<std::endl;
    }
    
    int getID()
    {
        return m_id;
    }
    
    //Pure Virtual Function to be defined in derived class
    virtual void calculateArea() = 0;
    virtual void calculatePerimeter() = 0;
    virtual void draw() = 0;
};


int Shape::id =0;

//Circle class
class Circle : public Shape
{
    float m_radius;
public:
    Circle(const float &radius): Shape(0, CIRCLE), m_radius(radius){}
    virtual void calculateArea()
    {
        m_area = pi*pow(m_radius,2);
    }
    virtual void calculatePerimeter()
    {
        m_perimeter = 2*pi*m_radius;
    }
    virtual void draw()
    {
        drawCircle(m_radius);
    }
    virtual void printData()
    {
        Shape::printData();
        cout<<" The radius of the circle = "<<m_radius<<" units\n";
    }
    virtual ~Circle()
    {
        std::cout<<"\n Destroying Circle with id = "<<m_id;
    }
};


//Triangle class
class Triangle : public Shape
{
    float m_side1, m_side2, m_side3;
public:
    Triangle(const float &side1, const float &side2, const float &side3): Shape(3, TRI),
    m_side1(side1), m_side2(side2), m_side3(side3)
    {}
    virtual ~Triangle()
    {
        std::cout<<"\n Destroying Triangle with id = "<<m_id;
    }
    virtual void calculateArea()
    {
        float semiPerimeter = (m_side1+m_side2+m_side3)/2;
        m_area = sqrt(semiPerimeter*(semiPerimeter-m_side1)*(semiPerimeter-m_side2)*(semiPerimeter-m_side3));
    }
    virtual void calculatePerimeter()
    {
        m_perimeter = m_side1+m_side2+m_side3;
    }
    virtual void draw()
    {
        
    }
};



//Quadrilateral class
class Quadrilateral : public Shape
{

protected:    
    std::vector<float> m_UniqueEdges;
    std::vector<float> m_Angles;//angle in degrees
    QuadType m_QuadType;
public:
    Quadrilateral():Shape(){};
    Quadrilateral(const float &side1, const float &side2, const float &side3, const float &side4,
    const float &angle1, const float& angle2,
    QuadType qtype):
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
    virtual ~Quadrilateral()
    {
        std::cout<<"\n Destroying  Quadrilateral with id = "<<m_id;
    }
    
    virtual void calculateArea()
    {
        float semiPerimeter = (m_UniqueEdges[0]+m_UniqueEdges[1]+m_UniqueEdges[2]+m_UniqueEdges[3])/2;
        m_area = sqrt((semiPerimeter-m_UniqueEdges[0])*(semiPerimeter-m_UniqueEdges[1])*
        (semiPerimeter-m_UniqueEdges[2])*(semiPerimeter-m_UniqueEdges[3]));
    }
    virtual void printData()
    {
        std::cout<<std::endl<<"The Shape ID = "<<m_id<<"\n The Type of Shape is "<<QuadTypeNames[m_QuadType]<<"\n"
        <<"The area = "<<std::fixed<<std::setprecision(2)<<m_area<<" square units\n"
        <<"The perimeter = "<<std::fixed<<std::setprecision(2)<<m_perimeter<<" units"<<std::endl;
    }
    virtual void calculatePerimeter()
    {
        std::vector<float>::const_iterator iter = m_UniqueEdges.begin();
        m_perimeter = 0;
        while(iter!=m_UniqueEdges.end())
        {
            m_perimeter =*iter;
            ++iter;
        }
    }
    
    virtual void draw()
    {
        
    }
};
//Square class
class Square : public Quadrilateral
{
    
public:
    Square(const float &side)
    {
        m_QuadType = SQ;
        m_UniqueEdges.push_back(side);
        m_Angles.push_back(90);
    }
    virtual void calculateArea()
    {
        m_area = pow(m_UniqueEdges[0], 2);
    }
    
    virtual void calculatePerimeter()
    {
        m_perimeter = 4 * m_UniqueEdges[0];
    }
    
    virtual void draw()
    {
        draw_rect(m_UniqueEdges[0],m_UniqueEdges[0]);
    }
    virtual void printData()
    {
        Quadrilateral::printData();
        std::cout<<"The side = "<<m_UniqueEdges[0]<<" units\n";
    }
    virtual ~Square()
    {
        std::cout<<"\n Destroying Square with id = "<<m_id;
    }
};

//Rectangle class
class Rectangle : public Quadrilateral
{
    
public:
    Rectangle(const float &breadth, const float &length) 
    {
        m_QuadType = RECT;
        m_UniqueEdges.push_back(breadth);
        m_UniqueEdges.push_back(length);
        m_Angles.push_back(90);
    }
    virtual ~Rectangle()
    {
        std::cout<<"\n Destroying Rectangle with id = "<<m_id;
    }
    virtual void calculateArea()
    {
        m_area = m_UniqueEdges[0]*m_UniqueEdges[1];
    }
    virtual void calculatePerimeter()
    {
        m_perimeter = 2*(m_UniqueEdges[0]+m_UniqueEdges[1]);
    }
    
    virtual void draw()
    {
        draw_rect(m_UniqueEdges[0],m_UniqueEdges[1]);
    }
    virtual void printData()
    {
        Quadrilateral::printData();
        std::cout<<" The length  = "<<m_UniqueEdges[1]<<" units\n";
        std::cout<<" The breadth = "<<m_UniqueEdges[0]<<" units\n";
    }
    
};

//Rhombus class
class Rhombus : public Quadrilateral
{

public:
    Rhombus(const float &length, const float &angle)
    {
        m_QuadType = RHOMBUS;
        m_UniqueEdges.push_back(length);
        m_Angles.push_back(angle);
    }
    virtual ~Rhombus()
    {
        std::cout<<"\n Destroying Rhombus with id = "<<m_id;
    }
    
    virtual void calculateArea()
    {
        m_area = pow(m_UniqueEdges[0],2) * sin(pi/180*m_Angles[0]);
    }
    virtual void calculatePerimeter()
    {
        m_perimeter = 4*(m_UniqueEdges[0]);
    }
    virtual void draw()
    {}
    
};

class Parallelogram : public Quadrilateral
{

public:
    Parallelogram(const float &breadth, const float &length, const float &angle)
    {
        m_QuadType = PARALLOGM;
        m_UniqueEdges.push_back(breadth);
        m_UniqueEdges.push_back(length);
        m_Angles.push_back(angle);
    }
    
    virtual ~Parallelogram()
    {
        std::cout<<"\n Destroying Parallelogram with id = "<<m_id;
    }
    
    virtual void calculateArea()
    {
        float ht = m_UniqueEdges[0] * sin(pi/180 *m_Angles[0]);
        m_area = m_UniqueEdges[1] * ht;
    }
    
    virtual void calculatePerimeter()
    {
        m_perimeter = 2*(m_UniqueEdges[0]+m_UniqueEdges[1]);
    }
    virtual void draw()
    {
        
    }
    
    
};


class Kite: public Quadrilateral
{

public:

    Kite(const float& side1, const float& side2, const float& angle1, const float& angle2)
    {
        m_QuadType = KITE; 
        m_UniqueEdges.push_back(side1);
        m_UniqueEdges.push_back(side2);
        m_Angles.push_back(angle1);
        m_Angles.push_back(angle2);
    }
    
    virtual ~Kite()
    {
        std::cout<<"\n Destroying Kite with id = "<<m_id;
    }
    
    virtual void calculateArea()
    {
        float d1 = 2*(m_UniqueEdges[0]*cos(pi/180*(m_Angles[0]/2)));
        float d2 = 2*(m_UniqueEdges[0]*sin(pi/180*(m_Angles[0]/2)));
        m_area = 0.5*(d1*d2);
    }
    
    virtual void calculatePerimeter()
    {
        m_perimeter= 2*(m_UniqueEdges[0]+m_UniqueEdges[1]);
    }
    
    virtual void draw()
    {}
};

class Trapezoid: public Quadrilateral
{
public:
    Trapezoid(const float& base, const float& secondSide, const float &thirdSide, 
    const float &fourthSide, const float& angle)
    {
        m_QuadType = TRAPEZM;
        m_UniqueEdges.push_back(base);
        m_UniqueEdges.push_back(secondSide);
        m_UniqueEdges.push_back(thirdSide);
        m_UniqueEdges.push_back(fourthSide);
        m_Angles.push_back(angle);
    }
    
    virtual ~Trapezoid()
    {
        std::cout<<"\n Destroying Trapezoid with id = "<<m_id;
    }
    
    virtual void calculateArea()
    {
        float ht = m_UniqueEdges[1] * sin(pi/180*m_Angles[0]);
        m_area = 0.5 *(m_UniqueEdges[0]+m_UniqueEdges[2])* ht;
    }
    
    virtual void calculatePerimeter()
    {
        m_perimeter = m_UniqueEdges[0]+m_UniqueEdges[1]+m_UniqueEdges[2]+m_UniqueEdges[3];
    }
    
    virtual void draw()
    {}
};

/*//Function to calculate area of square
float shape_area(const float& side)
{
    return (side*side);
}

//Function to calculate area of rectangle
float shape_area(const float& length, const float& breadth)
{
    return (length*breadth);
}

//Function to calculate are of triangle
float shape_area(const float& side1, const float& side2, const float& side3)
{
    float semiPerimeter = (side1+side2+side3)/2;
    return sqrt(semiPerimeter*(semiPerimeter-side1)*(semiPerimeter-side2)*(semiPerimeter-side3));
}
*/

Shape* GetShapeForQuadrilateral(const float &side1, const float &side2, const float &side3, const float &side4, 
const float& angle1, const float& angle2)
{
    std::vector<float> fVec = { side1, side2, side3, side4};
    
    SortAndRemoveDuplicateElementsFromVector(fVec);
    
    if(fVec.size()==1)
    {
        if(angle1==90&&angle2==90)
            return new Square(fVec[0]);
        else if(angle1==180-angle2)
            return new Rhombus(fVec[0], angle1);
    }
        
    else if(fVec.size()==2)
    {
        if(angle1==90&&angle2==90)
            return new Rectangle(fVec[0], fVec[1]);
        else if(angle1==180-angle2)
            return new Parallelogram(fVec[0], fVec[1], angle1);
        else 
            return new Kite(fVec[0], fVec[1], angle1, angle2); 
    }
    else if(angle1==180-angle2)
    {
        return new Trapezoid(side1, side2, side3, side4, angle1);
    }
    else if(angle1<180&&angle2<180)   
        return new Quadrilateral(side1, side2, side3, side4, angle1, angle2, CONVEXQUAD);
    
        return new Quadrilateral(side1, side2, side3, side4, angle1, angle2, CONCAVEQUAD);
}

void displayAllShapes(const vector<Shape*> &shapes)
{
    if(shapes.size()==0)
    {
        std::cout<<"\n No shapes added !....\n\n";
        return;
    }
    vector<Shape*>::const_iterator iter = shapes.begin();
    while(iter!=shapes.end())
    {
        (*(iter))->printData();
        (*(iter++))->draw();
    }
}

void addShapes(vector<Shape*> &shapes)
{
    Shape *shape;
    int choice;
    float side[4], angle[2];
    do{
        cout<<"Menu for adding shapes: \n";
        cout<<"\n Enter 1 for circle, 2 for triangle, 3 for Any Cyclic Quadrilateral, 4 to exit: \n";
        cin>>choice;
        switch(choice)
        {
            case 1:
                cout<<"\n Enter radius of circle: ";
                cin>>side[0];
                shape = new Circle(side[0]);
                break;
            case 2:
                cout<<"\n Enter the sides of the triangle: ";
                cin>>side[0]>>side[1]>>side[2];
                shape = new Triangle(side[0], side[1], side[2]);
                break;
            case 3:
                cout<<"\n Enter the 4 sides of the Quadrilateral: ";
                cin>>side[0]>>side[1]>>side[2]>>side[3];
                cout<<"\n Enter the first two angles in degrees: ";
                cin>>angle[0]>>angle[1];
                shape = GetShapeForQuadrilateral(side[0], side[1], side[2], side[3], angle[0], angle[1]);
                break;
            case 4:
                cout<<"\n Exiting Shape Adder....";
                break;
            default:
                cout<<"\n Not a valid input, please try again!...";
                continue;
        }
        if(choice!=4)
        {
            shape->calculateArea();
            shape->calculatePerimeter();
            shapes.push_back(shape);
        }  
        
    }while(choice!=4);
}

void deleteShape(vector<Shape*> &shapes, const int& shapeID)
{
    if(shapes.size()==0)
    {
        cout<<"\n Vector empty... \n";
        return;
    }
    vector<Shape*>::iterator iter = shapes.begin();
    while(iter!=shapes.end())
    {
        if((*iter)->getID()==shapeID)
        {
            delete *iter;
            shapes.erase(iter);
            cout<<"\n Successfully deleted element with shapeID : "<<shapeID<<endl;
            return;
        }
        ++iter;
    }
    cout<<"\n ShapeID : "<<shapeID<<" does not exist \n";
}

void mainMenu(vector<Shape*> &shapes)
{
    int choice;
    int shapeID;
    cout<<"Hello World, Welcome to Shaping your Life!, Main Menu select your choice: \n";
    do{
        cout<<"\n Enter 1 to add a shape,"
        "\n 2 to display all shapes,"
        "\n 3 to display a particular shape,"
        "\n 4 to delete a shape,"
        "\n 5 to exit:\n";
        cin>>choice;
        switch(choice)
        {
            case 1:
                addShapes(shapes);
                break;
            case 2:
                displayAllShapes(shapes);
                break;
            case 3:
                cout<<"\n Enter Shape ID :";
                cin>>shapeID;
                if(shapeID<1||shapeID>shapes.size())
                    {
                        cout<<"\n Incorrect ID !...";
                        continue;
                    }
                shapes[shapeID-1]->printData();
                shapes[shapeID-1]->draw();
                break;
            case 4:
                cout<<"\n Enter Shape ID to delete :";
                cin>>shapeID;
                deleteShape(shapes, shapeID);
                break;
            case 5:
                break;
            default:
                cout<<"\n Incorrect input, please try again!...";
                continue;
            
        }
    }while(choice!=5);
 
}

void deleteAllShapes(vector<Shape*> &shapes)
{
    if(shapes.size()==0)
        return;
    vector<Shape*>::iterator iter = shapes.begin();
    
    while(iter!=shapes.end())
    {
        delete *(iter++);
        
    }
}

int main()
{
    int choice;
    vector<Shape*> Shapes;
    
    mainMenu(Shapes);
    /*for(vector<Shape*>::const_iterator iter = Shapes.begin(); iter!=Shapes.end();++iter)
    {
        delete *iter;
    }*/
    deleteAllShapes(Shapes);
    
    
    return 0;
}
