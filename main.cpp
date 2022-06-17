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

    std::cout << "\n\n\n";

    entry = file.ReadData(format, "data2.txt");

    for (auto component : entry)
    {
        component.DisplayValues();
    }

    std::cout << "\n\n\n";

    format = file.ReadFormat("format.txt");
    std::swap(format.column[0], format.column[1]);
    file.WriteFormat(format, "new format.txt");

    entry[0].column[1] = "999";
    entry[1].column[0] = "Corrupted_File";
    file.WriteData(entry, "new data.txt");



    std::cout << "Press any key to end the program.";

    getch();

    return 0;
}
