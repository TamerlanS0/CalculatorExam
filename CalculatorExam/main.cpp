#include <iostream>
#include <cstring>
#include "functions.h"

using namespace std;

int main()
{
    ifade ifade;
    FileManager fileManager;

    cout << "\nWelcome to iPhone Calculator\n";
    cout << "\nProqramnan cixmaq ucun exit yaz\n";

    while (true)
    {
        cout << "\nIfadeni yaz: ";
        cin.getline(ifade.expr, 100);

        int length = strlen(ifade.expr);
        if (length > 0 && ifade.expr[length - 1] == '=')
        {
            ifade.expr[length - 1] = '\0';
        }

        if (equal(ifade.expr, "exit"))
        {
            cout << "Proqram dayandirildi." << endl;
            break;
        }

        bool isNumberOnly = true;
        for (int j = 0; ifade.expr[j] != '\0'; j++)
        {
            if (!(isdigit(ifade.expr[j]) || ifade.expr[j] == ' ' || ifade.expr[j] == '-' || ifade.expr[j] == '+' ||
                ifade.expr[j] == '*' || ifade.expr[j] == '/' || ifade.expr[j] == '(' || ifade.expr[j] == ')' ||
                ifade.expr[j] == '.'))
            {
                isNumberOnly = false;
                break;
            }
        }

        if (!isNumberOnly)
        {
            cout << "Duzgun reqem ve operatorlardan ibaret ifade yazin!" << endl;
            continue;
        }

        try
        {
            ifade.i = 0;
            double result = ifade.Resultator();
            ifade.skipSPACE();
            if (ifade.expr[ifade.i] != '\0')
            {
                throw "Duzgun tamamlanmamis ifade!";
            }

            int parenCount = 0;
            for (int j = 0; ifade.expr[j] != '\0'; j++)
            {
                if (ifade.expr[j] == '(') parenCount++;
                else if (ifade.expr[j] == ')') parenCount--;

                if (parenCount < 0)
                {
                    throw "Baglayan ) artiqdir, acan ( yoxdur!";
                }
            }

            if (parenCount > 0)
            {
                throw "Baglayan ) tapilmadi!";
            }

            cout << "Netice: " << result << endl;
            fileManager.saveToFile(ifade.expr, result);
        }
        catch (const char* msg)
        {
            cout << "Xeta: " << msg << endl;
        }
    }

    return 0;
}
