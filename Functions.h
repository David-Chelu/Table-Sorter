#ifndef FUNCTIONS_H
#define FUNCTIONS_H



// this function sets the console cursor (used by printf and cout) at the given coordinates
void SetConsoleCursor(SHORT xCursor = 0, SHORT yCursor = 0)
{
    static HANDLE
        consoleOutputHandle = GetStdHandle(STD_OUTPUT_HANDLE);

    SetConsoleCursorPosition(consoleOutputHandle, {xCursor, yCursor});
}

// converts an int unsigned into a string, where each character represents one digit
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

// for the table display, this function makes sure all columns are aligned to their respective size
// it does so by adding spaces after the text, when needed (when text is aligned to the left)
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

// for the table display, this function makes sure all columns are aligned to their respective size
// it does so by adding spaces before the text, when needed (when text is aligned to the right)
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

// this function makes use of windows functions to directly check the buffer size of the console
std::pair<int, int> ReadBufferSizeFromWindow()
{
    std::pair<int, int>
        bufferSize;

    BOOL
        result = GetConsoleScreenBufferInfo(Default::consoleOutputHandle,
                                            &Default::consoleBufferInfo);

    if (!result)
    {
        MessageBox(NULL,
                   "Could not read console buffer size.",
                   "Error",
                   MB_OK);
    }

    bufferSize.first  = Default::consoleBufferInfo.dwSize.X;
    bufferSize.second = Default::consoleBufferInfo.dwSize.Y;

    return bufferSize;
}



#endif
