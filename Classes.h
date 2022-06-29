#ifndef CLASSES_H
#define CLASSES_H



namespace Default
{
    // this handle will be used to get the console buffer size
    HANDLE
        consoleOutputHandle = GetStdHandle(STD_OUTPUT_HANDLE);

    CONSOLE_SCREEN_BUFFER_INFO
        consoleBufferInfo;

    namespace Key
    {
        int
            sortAscending        = VK_OEM_COMMA,
            sortDescending       = VK_OEM_PERIOD,
            customSortAscending  = VK_DIVIDE,
            customSortDescending = VK_MULTIPLY,
            expandColumn         = VK_ADD,
            shrinkColumn         = VK_SUBTRACT,
            moveSelectionUp      = VK_UP,
            moveSelectionDown    = VK_DOWN,
            moveSelectionLeft    = VK_LEFT,
            moveSelectionRight   = VK_RIGHT;
    }
}

namespace Settings
{
    WORD
        idleColor = FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE,
        lineColor = BACKGROUND_RED | BACKGROUND_GREEN | BACKGROUND_BLUE | BACKGROUND_INTENSITY,
        wordColor = BACKGROUND_INTENSITY;

    namespace Key
    {
        int
            sortAscending,
            sortDescending,
            customSortAscending,
            customSortDescending,
            expandColumn,
            shrinkColumn,
            moveSelectionUp,
            moveSelectionDown,
            moveSelectionLeft,
            moveSelectionRight;
    }
}



// this file exists to include other files, in order to reduce clutter in the main file
#include "Functions.h"
#include "Entry.h"
#include "File.h"
#include "Table.h"



#endif // ClASSES_H
