#ifndef FUNCTIONS_H
#define FUNCTIONS_H

#include <string>

class ifade
{
public:
    char expr[100];
    int i = 0;

    void skipSPACE();
    double checkNUM();
    double factor();
    double term();
    double Resultator();
};

class FileManager
{
public:
    void saveToFile(const std::string& expr, double result);
};

bool equal(const char* a, const char* b);

#endif
