#define _WIN32_WINNT 0x0500

#define SETTINGS 0
#define TABLE    1
#define MAIN     2

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
#include "CellCharacterInput.h"



int main()
{
    bool
        updateRequired = true,
        pressing[256],
        pressed[256],
        tableModified = false;

    char
        screen = MAIN,
        valueSegment = 1;

    uint16_t
        printedTableLines = 0,
        printedSettingsLines = 0,
        printedMainLines = 0;

    Table
        table;

    MainScreen
        mainScreen;

    SettingsScreen
        settingsScreen;

    File
        file;

    std::vector <std::string>
        menuLines{"Table View",
                  "Settings",
                  "Exit"};

    std::vector <int>
        cellAlphabeticCharacters = CellAlphabeticInput(),
        cellNumericCharacters = CellNumericInput(),
        cellNumpadNumericCharacters = CellNumpadNumericInput();

    WORD
        previousIdleColor;



    settingsScreen.reassignMode = false;

    table.reassignMode = false;
    table.format.ID = -1;
    table.ReadFormat(file);
    table.ReadData(file);
    table.CalculateColumnWidths();

    for (auto element : menuLines)
    {
        mainScreen.AddLine(element);
    }

    LoadSettings();

//    LoadSettings("asd");
//    SaveSettings();

    ResetScreen();

    previousIdleColor = Settings::Color::idle;

    table.startDisplay.Y = Default::consoleBufferInfo.dwCursorPosition.Y;

    ZeroMemory(pressing, sizeof(pressing) / sizeof(pressing[0]));
    ZeroMemory(pressed,  sizeof(pressed)  / sizeof(pressed [0]));



    while (1)
    {
        if (updateRequired)
        {
            if (screen == TABLE)
            {
                printedTableLines = table.Display();
            }
            else if (screen == MAIN)
            {
                printedMainLines = mainScreen.Display();
            }
            else if (screen == SETTINGS)
            {
                printedSettingsLines = settingsScreen.Display();
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
            if (screen == TABLE)
            {
                if (table.CustomSort(ASCENDING))
                {
                    updateRequired = true;
                }
            }
        }

        if (!pressed[Settings::Key::customSortDescending] && pressing[Settings::Key::customSortDescending])
        {
            if (screen == TABLE)
            {
                if (table.CustomSort(DESCENDING))
                {
                    updateRequired = true;
                }
            }
        }

        if (!pressed[Settings::Key::sortAscending] && pressing[Settings::Key::sortAscending])
        {
            if (screen == TABLE)
            {
                if (table.selection.Y == -1)
                {
                    if (table.Sort(ASCENDING))
                    {
                        updateRequired = true;
                    }
                }
            }
        }

        if (!pressed[Settings::Key::sortDescending] && pressing[Settings::Key::sortDescending])
        {
            if (screen == TABLE)
            {
                if (table.selection.Y == -1)
                {
                    if (table.Sort(DESCENDING))
                    {
                        updateRequired = true;
                    }
                }
            }
        }

        if (!pressed[Settings::Key::moveSelectionUp] && pressing[Settings::Key::moveSelectionUp])
        {
            if (screen == TABLE)
            {
                if (table.selection.Y > -1)
                {
                    table.selection.Y--;
                    updateRequired = true;
                }
            }
            else if (screen == MAIN)
            {
                if (mainScreen.selectedLine > 0)
                {
                    mainScreen.selectedLine--;
                    updateRequired = true;
                }
            }
            else if (screen == SETTINGS)
            {
                if (settingsScreen.selectedLine > 0)
                {
                    settingsScreen.selectedLine--;
                    updateRequired = true;
                }
            }
        }

        if (!pressed[Settings::Key::moveSelectionDown] && pressing[Settings::Key::moveSelectionDown])
        {
            if (screen == TABLE)
            {
                if (table.selection.Y < int(table.lines.size() - 1))
                {
                    table.selection.Y++;
                    updateRequired = true;
                }
            }
            else if (screen == MAIN)
            {
                if (mainScreen.selectedLine < mainScreen.lines.size() - 1)
                {
                    mainScreen.selectedLine++;
                    updateRequired = true;
                }
            }
            else if (screen == SETTINGS)
            {
                if (settingsScreen.selectedLine < settingsScreen.optionLine.size() - 1)
                {
                    settingsScreen.selectedLine++;
                    updateRequired = true;
                }
            }
        }

        if (!pressed[Settings::Key::moveSelectionLeft] && pressing[Settings::Key::moveSelectionLeft])
        {
            if (screen == TABLE)
            {
                if (table.selection.X > 0)
                {
                    table.selection.X--;
                    updateRequired = true;
                }
            }
        }

        if (!pressed[Settings::Key::moveSelectionRight] && pressing[Settings::Key::moveSelectionRight])
        {
            if (screen == TABLE)
            {
                if (table.selection.X < int(table.columnWidth.size() - 1))
                {
                    table.selection.X++;
                    updateRequired = true;
                }
            }
        }

        if (!pressed[Settings::Key::shrinkColumn] && pressing[Settings::Key::shrinkColumn])
        {
            if (screen == TABLE)
            {
                if (table.columnWidth[table.selection.X] > 2)
                {
                    table.columnWidth[table.selection.X]--;
                    updateRequired = true;
                }
            }
        }

        if (!pressed[Settings::Key::expandColumn] && pressing[Settings::Key::expandColumn])
        {
            if (screen == TABLE)
            {
                if (table.columnWidth[table.selection.X] < 39)
                {
                    table.columnWidth[table.selection.X]++;
                    updateRequired = true;
                }
            }
        }

        if (!pressed[Settings::Key::exit] && pressing[Settings::Key::exit])
        {
            if (screen == TABLE)
            {
                if (true == table.reassignMode)
                {
                    updateRequired = true;
                }
                else
                {
                    ResetScreen(printedTableLines);

                    screen = MAIN;
                    updateRequired = true;
                }

                table.reassignMode = false;
            }
            else if (screen == MAIN)
            {
                break;
            }
            else if (screen == SETTINGS)
            {
                ResetScreen(printedSettingsLines);

                screen = MAIN;
                updateRequired = true;
                settingsScreen.reassignMode = false;
            }
        }

        if (!pressed[Settings::Key::open] && pressing[Settings::Key::open])
        {
            if (screen == TABLE)
            {
                if (true == table.reassignMode)
                {
                    (-1 == table.selection.Y?
                         table.format :
                         table.lines[table.selection.Y]).column[table.selection.X] = table.cellText;

                    table.reassignMode = false;
                }
                else
                {
                    if (true == tableModified)
                    {
                        table.WriteFormat(file);
                        table.WriteData(file);
                        tableModified = false;
                    }
                }
            }
            else if (screen == MAIN)
            {
                if (!mainScreen.lines[mainScreen.selectedLine].compare(menuLines[0]))
                {
                    ResetScreen(printedMainLines);

                    screen = TABLE;
                    updateRequired = true;
                }
                else if (!mainScreen.lines[mainScreen.selectedLine].compare(menuLines[1]))
                {
                    ResetScreen(printedMainLines);

                    screen = SETTINGS;
                    updateRequired = true;
                }
                else if (!mainScreen.lines[mainScreen.selectedLine].compare(menuLines[2]))
                {
                    break;
                }
            }
            else if (screen == SETTINGS)
            {
                if (previousIdleColor == Settings::Color::idle)
                {
                    ResetScreen(printedSettingsLines);
                }
                else
                {
                    ResetScreen();

                    previousIdleColor = Settings::Color::idle;
                }

                settingsScreen.reassignMode = false;
                updateRequired = true;

                SaveSettings();
            }
        }

        if (!pressed[Settings::Key::reassignValue] && pressing[Settings::Key::reassignValue])
        {
            if (screen == TABLE)
            {
                if (false == table.reassignMode)
                {
                    table.cellText = (-1 == table.selection.Y? table.format : table.lines[table.selection.Y]).column[table.selection.X];
                }

                table.reassignMode = true;
            }
            else if (screen == SETTINGS)
            {
                settingsScreen.reassignMode = true;
            }
        }

        if (!pressed[Settings::Key::selectFirstPart] && pressing[Settings::Key::selectFirstPart])
        {
            if (screen == SETTINGS)
            {
                if (settingsScreen.reassignMode == true)
                {
                    valueSegment = 1;
                }
            }
        }

        if (!pressed[Settings::Key::selectSecondPart] && pressing[Settings::Key::selectSecondPart])
        {
            if (screen == SETTINGS)
            {
                if (settingsScreen.reassignMode == true)
                {
                    valueSegment = 2;
                }
            }
        }

        if (!pressed[Settings::Key::increaseAttribute] && pressing[Settings::Key::increaseAttribute])
        {
            if (screen == SETTINGS)
            {
                if (settingsScreen.reassignMode == true)
                {
                    switch (settingsScreen.selectedLine)
                    {
                        case 0:
                        {
                            if (valueSegment == 1)
                            {
                                if (Settings::Color::idle < 0b11110000)
                                {
                                    Settings::Color::idle += (1 << 4);
                                }
                            }
                            else if (valueSegment == 2)
                            {
                                if (Settings::Color::idle % (1 << 4) < 0b1111)
                                {
                                    Settings::Color::idle++;
                                }
                            }

                            break;
                        }
                        case 1:
                        {
                            if (valueSegment == 1)
                            {
                                if (Settings::Color::line < 0b11110000)
                                {
                                    Settings::Color::line += (1 << 4);
                                }
                            }
                            else if (valueSegment == 2)
                            {
                                if (Settings::Color::line % (1 << 4) < 0b1111)
                                {
                                    Settings::Color::line++;
                                }
                            }

                            break;
                        }
                        case 2:
                        {
                            if (valueSegment == 1)
                            {
                                if (Settings::Color::word < 0b11110000)
                                {
                                    Settings::Color::word += (1 << 4);
                                }
                            }
                            else if (valueSegment == 2)
                            {
                                if (Settings::Color::word % (1 << 4) < 0b1111)
                                {
                                    Settings::Color::word++;
                                }
                            }

                            break;
                        }
                    }

                    updateRequired = true;
                }
            }
        }

        if (!pressed[Settings::Key::decreaseAttribute] && pressing[Settings::Key::decreaseAttribute])
        {
            if (screen == SETTINGS)
            {
                if (settingsScreen.reassignMode == true)
                {
                    switch (settingsScreen.selectedLine)
                    {
                        case 0:
                        {
                            if (valueSegment == 1)
                            {
                                if (Settings::Color::idle >= (1 << 4))
                                {
                                    Settings::Color::idle -= (1 << 4);
                                }
                            }
                            else if (valueSegment == 2)
                            {
                                if (Settings::Color::idle % (1 << 4) > 0)
                                {
                                    Settings::Color::idle--;
                                }
                            }

                            break;
                        }
                        case 1:
                        {
                            if (valueSegment == 1)
                            {
                                if (Settings::Color::line >= (1 << 4))
                                {
                                    Settings::Color::line -= (1 << 4);
                                }
                            }
                            else if (valueSegment == 2)
                            {
                                if (Settings::Color::line % (1 << 4) > 0)
                                {
                                    Settings::Color::line--;
                                }
                            }

                            break;
                        }
                        case 2:
                        {
                            if (valueSegment == 1)
                            {
                                if (Settings::Color::word >= (1 << 4))
                                {
                                    Settings::Color::word -= (1 << 4);
                                }
                            }
                            else if (valueSegment == 2)
                            {
                                if (Settings::Color::word % (1 << 4) > 0)
                                {
                                    Settings::Color::word--;
                                }
                            }

                            break;
                        }
                    }

                    updateRequired = true;
                }
            }
        }



        if (table.reassignMode)
        {
            if (screen == TABLE)
            {
                for (auto element : cellAlphabeticCharacters)
                {
                    if (!pressed[element] && pressing[element])
                    {
                        table.cellText.push_back(char(element + (pressing[VK_SHIFT] || pressing[VK_RSHIFT]? 0 : 32)));

                        tableModified = true;
                        updateRequired = true;
                    }
                }

                for (auto element : cellNumericCharacters)
                {
                    if (!pressed[element] && pressing[element])
                    {
                        table.cellText.push_back(char(element));

                        tableModified = true;
                        updateRequired = true;
                    }
                }

                for (auto element : cellNumpadNumericCharacters)
                {
                    if (!pressed[element] && pressing[element])
                    {
                        table.cellText.push_back(char(element - 48));

                        tableModified = true;
                        updateRequired = true;
                    }
                }

                if (!pressed[' '] && pressing[' '])
                {
                    table.cellText.push_back(' ');

                    tableModified = true;
                    updateRequired = true;
                }

                if (!pressed[Settings::Key::deleteLastCharacter] &&
                    pressing[Settings::Key::deleteLastCharacter])
                {
                    table.cellText.pop_back();

                    tableModified = true;
                    updateRequired = true;
                }
            }
        }



        Sleep(1);
    }



    return 0;
}





























