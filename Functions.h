#ifndef FUNCTIONS_H
#define FUNCTIONS_H



// this function sets the console cursor (used by printf and cout) at the given coordinates
void SetCursor(SHORT xCursor = 0, SHORT yCursor = 0)
{
    static HANDLE
        consoleOutputHandle = GetStdHandle(STD_OUTPUT_HANDLE);

    SetConsoleCursorPosition(consoleOutputHandle, {xCursor, yCursor});
}



#endif

