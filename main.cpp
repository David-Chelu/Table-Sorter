#define _WIN32_WINNT 0x0500

#include <iostream>
#include <fstream>
#include <string>
#include <windows.h>
#include <conio.h>
#include <stdio.h>
#include <vector>
#include <algorithm>

namespace Default
{
    // this handle will be used to get the console buffer size
    HANDLE
        consoleOutputHandle = GetStdHandle(STD_OUTPUT_HANDLE);

    CONSOLE_SCREEN_BUFFER_INFO
        consoleBufferInfo;
}

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

    std::cout << "Press a number from '1' to '4' to select the column, and '-' and '+' to narrow and widen the selected columns, respectively.";

    GetConsoleScreenBufferInfo(Default::consoleOutputHandle,
                               &Default::consoleBufferInfo);

    table.startDisplay.Y = Default::consoleBufferInfo.dwCursorPosition.Y + 1;

    bool
        updateRequired = true,
        pressing[256],
        pressed[256];

    int unsigned
        selectedColumn = -1;

    ZeroMemory(pressing, sizeof(pressing) / sizeof(pressing[0]));
    ZeroMemory(pressed,  sizeof(pressed)  / sizeof(pressed [0]));

    while (1)
    {
        if (updateRequired)
        {
            table.Display();
            updateRequired = false;
        }

        CopyMemory(pressed, pressing, sizeof(pressing) / sizeof(pressing[0]));

        for (int unsigned index = 0; index < 256; index++)
        {
            if (GetAsyncKeyState(index))
            {
                pressing[index] = true;
            }
            else
            {
                pressing[index] = false;
            }
        }

        for (int unsigned column = '1'; column < '5'; column++)
        {
            if (!pressed[column] && pressing[column])
            {
                selectedColumn = column - '1';
                break;
            }
        }

        if (!pressed[VK_UP] && pressing[VK_UP])
        {
            if (table.selection.Y > -1)
            {
                table.selection.Y--;
                updateRequired = true;
            }
        }

        if (!pressed[VK_DOWN] && pressing[VK_DOWN])
        {
            if (table.selection.Y < int(table.lines.size() - 1))
            {
                table.selection.Y++;
                updateRequired = true;
            }
        }

        if (!pressed[VK_LEFT] && pressing[VK_LEFT])
        {
            if (table.selection.X > 0)
            {
                table.selection.X--;
                updateRequired = true;
            }
        }

        if (!pressed[VK_RIGHT] && pressing[VK_RIGHT])
        {
            if (table.selection.X < int(table.columnWidth.size() - 1))
            {
                table.selection.X++;
                updateRequired = true;
            }
        }

        if (selectedColumn != UINT_MAX)
        {
            if (!pressed[VK_SUBTRACT] && pressing[VK_SUBTRACT])
            {
                if (table.columnWidth[selectedColumn] > 2)
                {
                    table.columnWidth[selectedColumn]--;
                    table.shortened = true;
                    updateRequired = true;
                }
            }
            else if (!pressed[VK_ADD] && pressing[VK_ADD])
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
