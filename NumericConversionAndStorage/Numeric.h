#pragma once
#include <string>
#include <vector>


enum Base
{
	BIN = 2,
    OCT = 8,
    DEC = 10,
    HEX = 16,
    UNDEF_BASE = -1,
    MAX_BASE = 5
};

static const char *baseValues[MAX_BASE] = {
    "Binary",
    "Octal",
    "Decimal",
    "Hexadecimal",
    "Undefined"
};


class Numeric
{
    unsigned int m_Value;
    int num_id;
    std::string binary, hex, octal;

    static int id;


public:

    Numeric();
    Numeric(const Base& base, const std::string& Val);
    ~Numeric();

    void setData(const std::string& Val, const Base& base);
	void printData();
    
    
};

void printAllNumbers(const std::vector<Numeric*>& numbers);
void deleteAllNumbers(std::vector<Numeric*>& numbers);


