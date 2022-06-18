#define _WIN32_WINNT 0x0500

#define ONE 0
#define TWO 1
#define SUB 2
#define ADD 3

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
    table.lines = file.ReadData(table.format);
    table.CalculateColumnWidths();
/*
    table.DisplayValues();

    Sleep(1000);
    system("cls");
*/

    std::cout << "Press '1' and '2' to select the column, and '-' and '+' to narrow and widen the selected columns, respectively.";

    bool
        updateRequired = true,
        pressing[] = {false, false, false, false},
        pressed[] = {false, false, false, false};

    int unsigned
        selectedColumn = -1;

    while (1)
    {
        if (updateRequired)
        {
            table.Display();
            updateRequired = false;
        }

        CopyMemory(pressed, pressing, sizeof(pressing) / sizeof(pressing[0]));

        if (GetAsyncKeyState('1'))
        {
            pressing[ONE] = true;
        }
        else
        {
            pressing[ONE] = false;
        }

        if (GetAsyncKeyState('2'))
        {
            pressing[TWO] = true;
        }
        else
        {
            pressing[TWO] = false;
        }

        if (GetAsyncKeyState(VK_SUBTRACT))
        {
            pressing[SUB] = true;
        }
        else
        {
            pressing[SUB] = false;
        }

        if (GetAsyncKeyState(VK_ADD))
        {
            pressing[ADD] = true;
        }
        else
        {
            pressing[ADD] = false;
        }

        for (int unsigned column = 0; column < 2; column++)
        {
            if (!pressed[column] && pressing[column])
            {
                selectedColumn = column;
                break;
            }
        }

        if (selectedColumn != UINT_MAX)
        {
            if (!pressed[SUB] && pressing[SUB])
            {
                if (table.columnWidth[selectedColumn] > 2)
                {
                    table.columnWidth[selectedColumn]--;
                    updateRequired = true;
                }
            }
            else if (!pressed[ADD] && pressing[ADD])
            {
                if (table.columnWidth[selectedColumn] < 39)
                {
                    table.columnWidth[selectedColumn]++;
                    updateRequired = true;
                }
            }
        }

        Sleep(1);
    }



    std::cout << "\n\nPress any key to end the program.";

    getch();

    return 0;
}
