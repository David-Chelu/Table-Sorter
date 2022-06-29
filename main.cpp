#define _WIN32_WINNT 0x0500

#define OPTIONS 0
#define TABLE   1

#include <iostream>
#include <fstream>
#include <string>
#include <windows.h>
#include <conio.h>
#include <stdio.h>
#include <vector>
#include <algorithm>
#include <stdlib.h>
#include <limits.h>

#include "Classes.h"

#include "CustomSort.h"



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

    LoadSettings();

    table.startDisplay.Y = Default::consoleBufferInfo.dwCursorPosition.Y;

    bool
        updateRequired = true,
        pressing[256],
        pressed[256];

    char
        screen = TABLE;

    ZeroMemory(pressing, sizeof(pressing) / sizeof(pressing[0]));
    ZeroMemory(pressed,  sizeof(pressed)  / sizeof(pressed [0]));

    while (1)
    {
        if (updateRequired)
        {
            if (screen == OPTIONS)
            {
            }
            else
            {
                table.Display();
            }
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

        if (!pressed[Settings::Key::customSortAscending] && pressing[Settings::Key::customSortAscending])
        {
            if (table.CustomSort(ASCENDING))
            {
                updateRequired = true;
            }
        }

        if (!pressed[Settings::Key::customSortDescending] && pressing[Settings::Key::customSortDescending])
        {
            if (table.CustomSort(DESCENDING))
            {
                updateRequired = true;
            }
        }

        if (!pressed[Settings::Key::sortAscending] && pressing[Settings::Key::sortAscending])
        {
            if (table.selection.Y == -1)
            {
                if (table.Sort(ASCENDING))
                {
                    updateRequired = true;
                }
            }
        }

        if (!pressed[Settings::Key::sortDescending] && pressing[Settings::Key::sortDescending])
        {
            if (table.selection.Y == -1)
            {
                if (table.Sort(DESCENDING))
                {
                    updateRequired = true;
                }
            }
        }

        if (!pressed[Settings::Key::moveSelectionUp] && pressing[Settings::Key::moveSelectionUp])
        {
            if (table.selection.Y > -1)
            {
                table.selection.Y--;
                updateRequired = true;
            }
        }

        if (!pressed[Settings::Key::moveSelectionDown] && pressing[Settings::Key::moveSelectionDown])
        {
            if (table.selection.Y < int(table.lines.size() - 1))
            {
                table.selection.Y++;
                updateRequired = true;
            }
        }

        if (!pressed[Settings::Key::moveSelectionLeft] && pressing[Settings::Key::moveSelectionLeft])
        {
            if (table.selection.X > 0)
            {
                table.selection.X--;
                updateRequired = true;
            }
        }

        if (!pressed[Settings::Key::moveSelectionRight] && pressing[Settings::Key::moveSelectionRight])
        {
            if (table.selection.X < int(table.columnWidth.size() - 1))
            {
                table.selection.X++;
                updateRequired = true;
            }
        }

        if (!pressed[Settings::Key::shrinkColumn] && pressing[Settings::Key::shrinkColumn])
        {
            if (table.columnWidth[table.selection.X] > 2)
            {
                table.columnWidth[table.selection.X]--;
                updateRequired = true;
            }
        }
        else if (!pressed[Settings::Key::expandColumn] && pressing[Settings::Key::expandColumn])
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
