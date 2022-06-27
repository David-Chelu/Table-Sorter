#ifndef CLASSES_H
#define CLASSES_H



namespace Default
{
    // this handle will be used to get the console buffer size
    HANDLE
        consoleOutputHandle = GetStdHandle(STD_OUTPUT_HANDLE);

    CONSOLE_SCREEN_BUFFER_INFO
        consoleBufferInfo;
}
/*
namespace Config
{
    WORD
        defaultColor,
        lineColor,
        wordColor;
}
*/


// this file exists to include other files, in order to reduce clutter in the main file
#include "Functions.h"
#include "Entry.h"
#include "File.h"
#include "Table.h"



#endif // ClASSES_H
