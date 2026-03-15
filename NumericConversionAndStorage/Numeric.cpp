#include "Numeric.h"
#include <string>
#include <iostream>
#include <vector>

int Numeric::id = 0;

unsigned int getDecimalValueOf(const Base& baseIn, const std::string& valueIn)
{
    if (baseIn == DEC)
        return std::stoul(valueIn);

    std::string inp = valueIn;
    unsigned int digit = 0, countDigit = 0;
    unsigned int numVal = 0;
    int baseInInt = static_cast<int>(baseIn);
    char inVal = ' ', outVal = ' ';
    while ((baseIn==BIN&&inp.size()>1)||(baseIn==OCT&&inp.size()>1)||(baseIn==HEX&&inp.size()>2))
    {
        inVal = inp[inp.size() - 1];
        digit = ((inVal >= '0' && inVal <= '9') ? (int)(inVal - '0') : (int)(10 + (inVal - 'a')));
        numVal += digit * pow(baseInInt, countDigit++);
        inp.resize(inp.size() - 1);
    }
    return numVal;
}

void convertNumeric(const unsigned int& number,
    const Base& baseOut, std::string& valueOut)
{
    if (baseOut == DEC)
    {
        valueOut = std::to_string(number);
        return;
    }

    unsigned int numVal = number, digit;
    int baseOutInt = static_cast<int>(baseOut);
    while (numVal)
    {
        digit = numVal % baseOutInt;
        valueOut += (digit >= 0 && digit <= 9) ? ('0' + digit) : ('a' + (digit - 10));
		numVal /= baseOutInt;
    }
    std::reverse(valueOut.begin(), valueOut.end());
    if (baseOut == OCT)
        valueOut.insert(0, "0");
    else if (baseOut == HEX)
        valueOut.insert(0, "0x");
}

Numeric::Numeric()
{
    num_id = ++id;
    m_Value = 0;
    octal = "0";
    hex = "0x0";
	binary = "0";  
}
Numeric::Numeric(const Base& base, const std::string& Val) :num_id(++id)
{
    m_Value = getDecimalValueOf(base, Val);
    switch (base)
    {
    case BIN:
        binary = Val;
        binary.erase(0, 1);
        convertNumeric(m_Value, OCT, octal);
        convertNumeric(m_Value, HEX, hex);
		break;
    case OCT:
        octal = Val;
        convertNumeric(m_Value, HEX, hex);
		convertNumeric(m_Value, BIN, binary);           
        break;
    case DEC:
		convertNumeric(m_Value, BIN, binary);
        convertNumeric(m_Value, OCT, octal);
        convertNumeric(m_Value, HEX, hex);
        break;
    case HEX:
        hex = Val;
		convertNumeric(m_Value, BIN, binary);
        convertNumeric(m_Value, OCT, octal);
        break;

    }
}

void Numeric::setData(const std::string& Val, const Base& base)
{
    m_Value = getDecimalValueOf(base, Val);
    switch (base)
    {
    case OCT:
        octal = Val;
        convertNumeric(m_Value, HEX, hex);
        break;
    case DEC:
        convertNumeric(m_Value, OCT, octal);
        convertNumeric(m_Value, HEX, hex);
        break;
    case HEX:
        hex = Val;
        convertNumeric(m_Value, OCT, octal);
        break;

    }
}
Numeric::~Numeric()
{
    std::cout << "\n Deleting number id: " << num_id;
}

void Numeric::printData()
{
    std::cout << "\n Details of number ID " << num_id;
	std::cout << "\n The number in binary = " << binary;
    std::cout << "\n The representation in decimal = " << m_Value;
    std::cout << "\n The representation in octal = " << octal;
    std::cout << "\n The representation in Hexadecimal =" << hex << std::endl;
}

void printAllNumbers(const std::vector<Numeric*>& numbers)
{
    if (numbers.size() == 0)
    {
        std::cout << "\n No numbers in vector !...";
        return;
    }
    std::vector<Numeric*>::const_iterator iter = numbers.begin();
    while (iter != numbers.end())
    {
        (*(iter++))->printData();
    }
}

void deleteAllNumbers(std::vector<Numeric*>& numbers)
{
    std::vector<Numeric*>::const_iterator iter = numbers.begin();
    while (iter != numbers.end())
    {
        delete *iter;
        iter++;
    }
}