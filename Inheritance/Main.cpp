#include <iostream>
#include <algorithm>
#include <iomanip>
#include <vector>
#include "Shapes.h"
#include "Circle.h"
#include "Kite.h"
#include "Parallelogram.h"
#include "Quadrilateral.h"
#include "Rectangle.h"
#include "Rhombus.h"
#include "Square.h"
#include "Trapezoid.h"
#include "Triangle.h"



void SortAndRemoveDuplicateElementsFromVector(std::vector<float>& edges)
{
    std::sort(edges.begin(), edges.end());
    std::vector<float>::const_iterator lastUnique = std::unique(edges.begin(), edges.end());
    edges.erase(lastUnique, edges.end());
}



Shape* GetShapeForQuadrilateral(const float& side1, const float& side2, const float& side3, const float& side4,
    const float& angle1, const float& angle2)
{
    std::vector<float> fVec = { side1, side2, side3, side4 };

    SortAndRemoveDuplicateElementsFromVector(fVec);

    if (fVec.size() == 1)
    {
        if (angle1 == 90 && angle2 == 90)
            return new Square(fVec[0]);
        else if (angle1 == 180 - angle2)
            return new Rhombus(fVec[0], angle1);
    }

    else if (fVec.size() == 2)
    {
        if (angle1 == 90 && angle2 == 90)
            return new Rectangle(fVec[0], fVec[1]);
        else if (angle1 == 180 - angle2)
            return new Parallelogram(fVec[0], fVec[1], angle1);
        else
            return new Kite(fVec[0], fVec[1], angle1, angle2);
    }
    else if (angle1 == 180 - angle2)
    {
        return new Trapezoid(side1, side2, side3, side4, angle1);
    }
    else if (angle1 < 180 && angle2 < 180)
        return new Quadrilateral(side1, side2, side3, side4, angle1, angle2, CONVEXQUAD);

    return new Quadrilateral(side1, side2, side3, side4, angle1, angle2, CONCAVEQUAD);
}

void displayAllShapes(const std::vector<Shape*>& shapes)
{
    if (shapes.size() == 0)
    {
        std::cout << "\n No shapes added !....\n\n";
        return;
    }
    std::vector<Shape*>::const_iterator iter = shapes.begin();
    while (iter != shapes.end())
    {
        (*iter)->printData();
        (*iter)->draw();
        iter++;
    }
}

void addShapes(std::vector<Shape*>& shapes)
{
    Shape* shape = nullptr;
    int choice;
    float side[4], angle[2];
    do {
        std::cout << "Menu for adding shapes: \n";
        std::cout << "\n Enter 1 for circle, 2 for triangle, 3 for Any Cyclic Quadrilateral, 4 to exit: \n";
        std::cin >> choice;
        switch (choice)
        {
        case 1:
            std::cout << "\n Enter radius of circle: ";
            std::cin >> side[0];
            shape = new Circle(side[0]);
            break;
        case 2:
            std::cout << "\n Enter the sides of the triangle: ";
            std::cin >> side[0] >> side[1] >> side[2];
            shape = new Triangle(side[0], side[1], side[2]);
            break;
        case 3:
            std::cout << "\n Enter the 4 sides of the Quadrilateral: ";
            std::cin >> side[0] >> side[1] >> side[2] >> side[3];
            std::cout << "\n Enter the first two angles in degrees: ";
            std::cin >> angle[0] >> angle[1];
            shape = GetShapeForQuadrilateral(side[0], side[1], side[2], side[3], angle[0], angle[1]);
            break;
        case 4:
            std::cout << "\n Exiting Shape Adder....";
            break;
        default:
            std::cout << "\n Not a valid input, please try again!...";
            continue;
        }
        if (choice != 4)
        {
            if (shape != nullptr)
            {
                shape->calculateArea();
                shape->calculatePerimeter();
                shapes.push_back(shape);
            }
        }

    } while (choice != 4);
}

void deleteShape(std::vector<Shape*>& shapes, const int& shapeID)
{
    if (shapes.size() == 0)
    {
        std::cout << "\n Vector empty... \n";
        return;
    }
    std::vector<Shape*>::iterator iter = shapes.begin();
    while (iter != shapes.end())
    {
        if ((*iter)->getID() == shapeID)
        {
            delete* iter;
            shapes.erase(iter);
            std::cout << "\n Successfully deleted element with shapeID : " << shapeID << std::endl;
            return;
        }
        ++iter;
    }
    std::cout << "\n ShapeID : " << shapeID << " does not exist \n";
}

void mainMenu(std::vector<Shape*>& shapes)
{
    int choice;
    int shapeID;
    std::cout << "Hello World, Welcome to Shaping your Life!, Main Menu select your choice: \n";
    do {
        std::cout << "\n Enter 1 to add a shape,"
            "\n 2 to display all shapes,"
            "\n 3 to display a particular shape,"
            "\n 4 to delete a shape,"
            "\n 5 to exit:\n";
        std::cin >> choice;
        switch (choice)
        {
        case 1:
            addShapes(shapes);
            break;
        case 2:
            displayAllShapes(shapes);
            break;
        case 3:
            std::cout << "\n Enter Shape ID :";
            std::cin >> shapeID;
            if (shapeID<1 || shapeID>shapes.size())
            {
                std::cout << "\n Incorrect ID !...";
                continue;
            }
            shapes[shapeID - 1]->printData();
            shapes[shapeID - 1]->draw();
            break;
        case 4:
            std::cout << "\n Enter Shape ID to delete :";
            std::cin >> shapeID;
            deleteShape(shapes, shapeID);
            break;
        case 5:
            break;
        default:
            std::cout << "\n Incorrect input, please try again!...";
            continue;

        }
    } while (choice != 5);

}

void deleteAllShapes(std::vector<Shape*>& shapes)
{
    if (shapes.size() == 0)
        return;
    std::vector<Shape*>::iterator iter = shapes.begin();

    while (iter != shapes.end())
    {
        delete *iter;
        iter++;

    }
}

int main()
{
    int choice;
    std::vector<Shape*> Shapes;

    mainMenu(Shapes);
    
    deleteAllShapes(Shapes);


    return 0;
}