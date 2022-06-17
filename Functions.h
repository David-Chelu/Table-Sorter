#ifndef FUNCTIONS_H
#define FUNCTIONS_H



// this function sets the console cursor (used by printf and cout) at the given coordinates
void SetConsoleCursor(SHORT xCursor = 0, SHORT yCursor = 0)
{
    static HANDLE
        consoleOutputHandle = GetStdHandle(STD_OUTPUT_HANDLE);

    SetConsoleCursorPosition(consoleOutputHandle, {xCursor, yCursor});
}

std::string StringFromUnsignedInt(int unsigned value)
{
    std::string
        stringFromNumber;

    if (value == 0)
    {
        stringFromNumber = '0';
    }
    else
    {
        while (value != 0)
        {
            stringFromNumber += char(value % 10 + 48);
            value /= 10;
        }

        std::reverse(stringFromNumber.begin(), stringFromNumber.end());
    }

    return stringFromNumber;
}



#endif

