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
    Table
        table;

    File
        file;



    table.format.ID = -1;
    table.format = file.ReadFormat();
    table.lines = file.ReadData(table.format, "data2.txt");
    table.CalculateColumnWidths();

    table.DisplayValues();



    std::cout << "Press any key to end the program.";

    getch();

    return 0;
}
