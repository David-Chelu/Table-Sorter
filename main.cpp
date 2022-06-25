#define _WIN32_WINNT 0x0500

#define ASCENDING  0
#define DESCENDING 1
#define SORT_BY_ID 2

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
    table.ReadFormat(file);
    table.ReadData(file);
    table.CalculateColumnWidths();
/*
    table.DisplayValues();

    Sleep(1000);
    system("cls");
*/

    std::cout << "Press the arrow keys to navigate the table.\nPress '-' and '+' to narrow and widen the column on which the cursor exists.\nPress ',' to sort the table ascending and '.' to sort the table descending. This will only take place when the cursor is on the first line of the table.";

    GetConsoleScreenBufferInfo(Default::consoleOutputHandle,
                               &Default::consoleBufferInfo);

    table.startDisplay.Y = Default::consoleBufferInfo.dwCursorPosition.Y + 1;

    bool
        updateRequired = true,
        pressing[256],
        pressed[256];

    int
        sortAscendingKey  = VK_OEM_COMMA,
        sortDescendingKey = VK_OEM_PERIOD;

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

        if (!pressed[sortAscendingKey] && pressing[sortAscendingKey])
        {
            if (table.selection.Y == -1)
            {
                if (table.Sort(ASCENDING))
                {
                    updateRequired = true;
                }
            }
        }

        if (!pressed[sortDescendingKey] && pressing[sortDescendingKey])
        {
            if (table.selection.Y == -1)
            {
                if (table.Sort(DESCENDING))
                {
                    updateRequired = true;
                }
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

        if (!pressed[VK_SUBTRACT] && pressing[VK_SUBTRACT])
        {
            if (table.columnWidth[table.selection.X] > 2)
            {
                table.columnWidth[table.selection.X]--;
                updateRequired = true;
            }
        }
        else if (!pressed[VK_ADD] && pressing[VK_ADD])
        {
            if (table.columnWidth[table.selection.X] < 39)
            {
                table.columnWidth[table.selection.X]++;
                updateRequired = true;
            }
        }

        Sleep(1);
    }



    std::cout << "\n\nPress any key to end the program.";

    getch();

    return 0;
}
