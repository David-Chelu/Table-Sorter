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

std::string StripString(const std::string &target)
{
    size_t
        start,
        stop;

    for (start = 0;                  target[start] == ' '; start++);
    for (stop = target.length() - 1; target[stop]  == ' '; stop--);

    return target.substr(start, stop - start + 1);
}

void ChangeTextColor(WORD newColor)
{
    SetConsoleTextAttribute(Default::consoleOutputHandle,
                            newColor);
}

void ResetScreen(uint16_t numberOfLines = -1)
{
    SetConsoleCursor();
    ChangeTextColor(Settings::Color::idle);

    std::cout << std::string(Default::consoleBufferInfo.dwSize.X * std::min<uint16_t>(Default::consoleBufferInfo.dwSize.Y, numberOfLines),
                             ' ');

    SetConsoleCursor();
}

bool LoadSettings(const std::string &directory)
{
    bool
        result = true;

    std::fstream
        loadFile;

    loadFile.open(directory.c_str(), FILE_IN);

    if (loadFile)
    {
        loadFile.read((char*)&Settings::Color::idle, sizeof(Settings::Color::idle));
        loadFile.read((char*)&Settings::Color::line, sizeof(Settings::Color::line));
        loadFile.read((char*)&Settings::Color::word, sizeof(Settings::Color::word));

        loadFile.read((char*)&Settings::Key::sortAscending,        sizeof(Settings::Key::sortAscending));
        loadFile.read((char*)&Settings::Key::sortDescending,       sizeof(Settings::Key::sortDescending));
        loadFile.read((char*)&Settings::Key::customSortAscending,  sizeof(Settings::Key::customSortAscending));
        loadFile.read((char*)&Settings::Key::customSortDescending, sizeof(Settings::Key::customSortDescending));
        loadFile.read((char*)&Settings::Key::expandColumn,         sizeof(Settings::Key::expandColumn));
        loadFile.read((char*)&Settings::Key::shrinkColumn,         sizeof(Settings::Key::shrinkColumn));
        loadFile.read((char*)&Settings::Key::moveSelectionUp,      sizeof(Settings::Key::moveSelectionUp));
        loadFile.read((char*)&Settings::Key::moveSelectionDown,    sizeof(Settings::Key::moveSelectionDown));
        loadFile.read((char*)&Settings::Key::moveSelectionLeft,    sizeof(Settings::Key::moveSelectionLeft));
        loadFile.read((char*)&Settings::Key::moveSelectionRight,   sizeof(Settings::Key::moveSelectionRight));
        loadFile.read((char*)&Settings::Key::exit,                 sizeof(Settings::Key::exit));
        loadFile.read((char*)&Settings::Key::open,                 sizeof(Settings::Key::open));
        loadFile.read((char*)&Settings::Key::reassignValue,        sizeof(Settings::Key::reassignValue));
        loadFile.read((char*)&Settings::Key::increaseAttribute,    sizeof(Settings::Key::increaseAttribute));
        loadFile.read((char*)&Settings::Key::decreaseAttribute,    sizeof(Settings::Key::decreaseAttribute));
        loadFile.read((char*)&Settings::Key::selectFirstPart,      sizeof(Settings::Key::selectFirstPart));
        loadFile.read((char*)&Settings::Key::selectSecondPart,     sizeof(Settings::Key::selectSecondPart));
        loadFile.read((char*)&Settings::Key::deleteLastCharacter,  sizeof(Settings::Key::deleteLastCharacter));

        loadFile.close();
    }
    else
    {
        Settings::Color::idle = Default::Color::idle;
        Settings::Color::line = Default::Color::line;
        Settings::Color::word = Default::Color::word;

        Settings::Key::sortAscending        = Default::Key::sortAscending;
        Settings::Key::sortDescending       = Default::Key::sortDescending;
        Settings::Key::customSortAscending  = Default::Key::customSortAscending;
        Settings::Key::customSortDescending = Default::Key::customSortDescending;
        Settings::Key::expandColumn         = Default::Key::expandColumn;
        Settings::Key::shrinkColumn         = Default::Key::shrinkColumn;
        Settings::Key::moveSelectionUp      = Default::Key::moveSelectionUp;
        Settings::Key::moveSelectionDown    = Default::Key::moveSelectionDown;
        Settings::Key::moveSelectionLeft    = Default::Key::moveSelectionLeft;
        Settings::Key::moveSelectionRight   = Default::Key::moveSelectionRight;
        Settings::Key::exit                 = Default::Key::exit;
        Settings::Key::open                 = Default::Key::open;
        Settings::Key::reassignValue        = Default::Key::reassignValue;
        Settings::Key::increaseAttribute    = Default::Key::increaseAttribute;
        Settings::Key::decreaseAttribute    = Default::Key::decreaseAttribute;
        Settings::Key::selectFirstPart      = Default::Key::selectFirstPart;
        Settings::Key::selectSecondPart     = Default::Key::selectSecondPart;
        Settings::Key::deleteLastCharacter  = Default::Key::deleteLastCharacter;

        result = false;
    }

    GetConsoleScreenBufferInfo(Default::consoleOutputHandle,
                               &Default::consoleBufferInfo);

    return result;
}

bool LoadSettings()
{
    return LoadSettings(Default::settingsDirectory);
}

bool SaveSettings(const std::string &directory)
{
    std::fstream
        saveFile;

    saveFile.open(directory.c_str(), FILE_OUT);

    if (saveFile.is_open())
    {
        saveFile.write((char*)&Settings::Color::idle, sizeof(Settings::Color::idle));
        saveFile.write((char*)&Settings::Color::line, sizeof(Settings::Color::line));
        saveFile.write((char*)&Settings::Color::word, sizeof(Settings::Color::word));

        saveFile.write((char*)&Settings::Key::sortAscending,        sizeof(Settings::Key::sortAscending));
        saveFile.write((char*)&Settings::Key::sortDescending,       sizeof(Settings::Key::sortDescending));
        saveFile.write((char*)&Settings::Key::customSortAscending,  sizeof(Settings::Key::customSortAscending));
        saveFile.write((char*)&Settings::Key::customSortDescending, sizeof(Settings::Key::customSortDescending));
        saveFile.write((char*)&Settings::Key::expandColumn,         sizeof(Settings::Key::expandColumn));
        saveFile.write((char*)&Settings::Key::shrinkColumn,         sizeof(Settings::Key::shrinkColumn));
        saveFile.write((char*)&Settings::Key::moveSelectionUp,      sizeof(Settings::Key::moveSelectionUp));
        saveFile.write((char*)&Settings::Key::moveSelectionDown,    sizeof(Settings::Key::moveSelectionDown));
        saveFile.write((char*)&Settings::Key::moveSelectionLeft,    sizeof(Settings::Key::moveSelectionLeft));
        saveFile.write((char*)&Settings::Key::moveSelectionRight,   sizeof(Settings::Key::moveSelectionRight));
        saveFile.write((char*)&Settings::Key::exit,                 sizeof(Settings::Key::exit));
        saveFile.write((char*)&Settings::Key::open,                 sizeof(Settings::Key::open));
        saveFile.write((char*)&Settings::Key::reassignValue,        sizeof(Settings::Key::reassignValue));
        saveFile.write((char*)&Settings::Key::increaseAttribute,    sizeof(Settings::Key::increaseAttribute));
        saveFile.write((char*)&Settings::Key::decreaseAttribute,    sizeof(Settings::Key::decreaseAttribute));
        saveFile.write((char*)&Settings::Key::selectFirstPart,      sizeof(Settings::Key::selectFirstPart));
        saveFile.write((char*)&Settings::Key::selectSecondPart,     sizeof(Settings::Key::selectSecondPart));
        saveFile.write((char*)&Settings::Key::deleteLastCharacter,  sizeof(Settings::Key::deleteLastCharacter));

        saveFile.close();
    }
    else
    {
        MessageBox(NULL,
                   (std::string("In function \"bool SaveSettings(const std::string &directory)\":\n\n"
                                "Could not save file ") + directory + '.').c_str(),
                   "Error",
                   MB_OK);

        return false;
    }

    return true;
}

bool SaveSettings()
{
    return SaveSettings(Default::settingsDirectory);
}



#endif
