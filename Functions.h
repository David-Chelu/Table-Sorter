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

std::string AllocateAndCompensate(const std::string &targetString, int short unsigned allocateSize)
{
    std::string
        allocatedString;

    allocatedString = targetString.substr(0, allocateSize);

    if (allocatedString.length() < allocateSize)
    {
        allocatedString = allocatedString.append(allocateSize - allocatedString.length(), ' ');
    }

    return allocatedString;
}

std::string AllocateAndCompensate(int short unsigned allocateSize, const std::string &targetString)
{
    std::string
        allocatedString;

    allocatedString = targetString.substr(0, allocateSize);

    if (allocatedString.length() < allocateSize)
    {
        allocatedString = std::string(allocateSize - allocatedString.length(), ' ') + allocatedString;
    }

    return allocatedString;
}



#endif

