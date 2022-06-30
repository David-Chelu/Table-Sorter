#ifndef CLASSES_H
#define CLASSES_H



#define ASCENDING  0
#define DESCENDING 1
#define SORT_BY_ID 2

#define FILE_IN  std::ios_base::ios_base::in
#define FILE_OUT std::ios_base::ios_base::out



namespace Default
{
    // this handle will be used to get the console buffer size
    HANDLE
        consoleOutputHandle = GetStdHandle(STD_OUTPUT_HANDLE);

    CONSOLE_SCREEN_BUFFER_INFO
        consoleBufferInfo;

    std::string
        settingsDirectory = "settings.tsr";

    int unsigned
        linesDrawn;

    namespace Color
    {
        WORD
            idle = FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE,
            line = BACKGROUND_RED | BACKGROUND_GREEN | BACKGROUND_BLUE | BACKGROUND_INTENSITY,
            word = BACKGROUND_INTENSITY;
    }

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
            moveSelectionRight   = VK_RIGHT,
            exit                 = VK_ESCAPE;
    }
}

namespace Settings
{
    namespace Color
    {
        WORD
            idle,
            line,
            word;
    }

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
            moveSelectionRight,
            exit;
    }
}



// this file exists to include other files, in order to reduce clutter in the main file
#include "Functions.h"
#include "Entry.h"
#include "File.h"
#include "Table.h"



#endif // ClASSES_H
