#define _WIN32_WINNT 0x0500

#include <iostream>
#include <fstream>
#include <string>
#include <windows.h>
#include <conio.h>
#include <stdio.h>
#include <vector>
#include <algorithm>

#include "Classes.h"



int main()
{
    Entry
        format;

    File
        file;

    std::vector <Entry>
        entry;



    format.ID = -1;

    format = file.ReadFormat();
    format.DisplayValues();

    format = file.ReadFormat("format2.txt");
    format.DisplayValues();

    format = file.ReadFormat();
    format.DisplayValues();



    std::cout << "Press any key to end the program.";

    getch();

    return 0;
}
