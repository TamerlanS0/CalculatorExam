#include "functions.h"
#include <iostream>
#include <fstream>
#include <cmath>

using namespace std;

void ifade::skipSPACE()
{
    while (expr[i] == ' ') i++;
}

double ifade::checkNUM()
{
    skipSPACE();

    double num = 0.0;
    bool isNegative = false;
    bool hasDecimal = false;
    double decimalFactor = 0.1;

    if (expr[i] == '-')
    {
        isNegative = true;
        i++;
    }

    if (!(expr[i] >= '0' && expr[i] <= '9'))
    {
        throw "Reqem yazmaq lazim idi";
    }

    while (expr[i] >= '0' && expr[i] <= '9')
    {
        num = num * 10 + (expr[i] - '0');
        i++;
    }

    if (expr[i] == '.')
    {
        hasDecimal = true;
        i++;
        while (expr[i] >= '0' && expr[i] <= '9')
        {
            num += (expr[i] - '0') * decimalFactor;
            decimalFactor /= 10;
            i++;
        }
    }

    return isNegative ? -num : num;
}

double ifade::factor()
{
    skipSPACE();

    double result = 0;
    if (expr[i] == '(')
    {
        i++;
        result = Resultator();
        skipSPACE();
        if (expr[i] != ')')
        {
            throw "Baglayan ')' tapilmadi!";
        }
        i++;
    }
    else
    {
        result = checkNUM();
    }

    return result;
}

double ifade::term()
{
    double result = factor();
    while (true)
    {
        skipSPACE();
        if (expr[i] == '*' || expr[i] == '/')
        {
            char op = expr[i];
            i++;
            double next = factor();
            if (op == '*') result *= next;
            else
            {
                if (next == 0) throw "0-a bolme xetasi!";
                result /= next;
            }
        }
        else break;
    }
    return result;
}

double ifade::Resultator()
{
    double result = term();
    while (true)
    {
        skipSPACE();
        if (expr[i] == '+' || expr[i] == '-')
        {
            char op = expr[i];
            i++;
            double next = term();
            if (op == '+') result += next;
            else result -= next;
        }
        else if (expr[i] == '(')
        {
            i++;
            result *= term();
        }
        else break;
    }
    return result;
}

void FileManager::saveToFile(const string& expr, double result)
{
    ofstream file("note.txt");
    file << expr << " = " << result << endl;
    file.close();
}

bool equal(const char* a, const char* b)
{
    while (*a && *b)
    {
        if (*a != *b) return false;
        a++; b++;
    }
    return (*a == '\0' && *b == '\0');
}
