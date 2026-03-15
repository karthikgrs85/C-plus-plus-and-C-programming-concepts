// NumericConversionAndStorage.cpp : This file contains the 'main' function. Program execution begins and ends there.
//
#include <iostream>
#include <string>
#include <vector>
#include <conio.h>
#include "Numeric.h"

int main()
{
    std::cout << "Hello World!\n";

    std::string num, hexPart = "0x";
    int choice = 0, numId = 0;
    std::vector<Numeric*> numbers;
    Numeric* numberPtr;
    std::cout << "\n Welcome to Number Conversion Program: ";
    do {
        std::cout << "\n Enter 1 to add a number, "
            "\n 2 to view a numbers, "
            "\n 3 to view all numbers, "
            "\n 4 to delete a number "
            "\n 5 to exit\n:\n";
        std::cin >> choice;
        switch (choice)
        {
        case 1:
            std::cout << "\n Enter a number "
				"\n preceded by B for binary,"
                "\n preceded by 0 for octal,"
                "\n normal number for decimal,"
                "\n 0x for hexadecimal:\n";
            std::cin >> num;
            if (num.substr(0, 2) == hexPart)
            {
                numberPtr = new Numeric(HEX, num);
            }
            else if (num[0] == '0')
            {
                numberPtr = new Numeric(OCT, num);
            }
            else
            {
                numberPtr = new Numeric(DEC, num);
            }
            numbers.push_back(numberPtr);
            std::cout << "\n Number added successfully...\n";
            break;
        case 2:
            std::cout << "\n Enter the Number ID to display :\n";
            std::cin >> numId;
            if (numId <= 0 || numId > numbers.size())
            {
                std::cout << "\n Invalid Number ID \n";
                continue;
            }
            numbers[numId-1]->printData();
            break;
        case 3:
            printAllNumbers(numbers);
            break;
        case 4:
            std::cout << "\n Enter the Number ID to delete :\n";
            std::cin >> numId;
            if (numId <= 0 || numId > numbers.size())
            {
                std::cout << "\n Invalid Number ID \n";
                continue;
            }
			delete numbers[numId - 1];
            numbers.erase(numbers.begin() + (numId - 1));
            std::cout << "\n Number deleted successfully...\n";
            break;
        case 5:
            break;
        default:
            std::cout << "\n Invalid input !!...Please try again...";
            continue;

        }
    } while (choice != 5);
    deleteAllNumbers(numbers);
    _getch();
}

// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu

// Tips for Getting Started: 
//   1. Use the Solution Explorer window to add/manage files
//   2. Use the Team Explorer window to connect to source control
//   3. Use the Output window to see build output and other messages
//   4. Use the Error List window to view errors
//   5. Go to Project > Add New Item to create new code files, or Project > Add Existing Item to add existing code files to the project
//   6. In the future, to open this project again, go to File > Open > Project and select the .sln file
