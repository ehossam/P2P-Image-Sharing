#ifndef STEG_H
#define STEG_H

#include <iostream>
#include <iomanip>
#include <stdio.h>
#include <fstream>
#include <stdlib.h>
#include <cstring>

using namespace std;

class Steg
{
public:
    Steg();
    static void embedStringIntoImage(string imagePath, string text, string password);
    static string restoreStringFromImage(string imagePath, string password);
};

#endif // STEG_H

