#ifndef TABLE_H
#define TABLE_H



struct Table
{
    Table();



    Entry
        &operator [](int unsigned index);



    bool
        Sort(int mode = ASCENDING),
        CustomSort(int mode = ASCENDING);

    uint16_t
        Display();

    void
        CalculateColumnWidths(),
        DisplayValues(),
        FillLine(std::string &outputLine, int short unsigned lineSize),
        ReadFormat(File &file),
        ReadData(File &file),
        WriteFormat(File &file),
        WriteData(File &file);



    bool
        modifiedFormat,
        modifiedLines,
        reassignMode;

    char
        horizontalWall,
        verticalWall;

    COORD
        selection,
        startDisplay,
        word;

    Entry
        format,
        fileFormat;

    int short unsigned
        defaultColumnWidth,
        wordWidth;

    std::pair <int, int>
        bufferSize;

    std::string
        cellText;

    std::vector <Entry>
        lines,
        fileLines;

    std::vector <int short unsigned>
        columnWidth;
};



Table::Table()
{
    this->modifiedFormat =
    this->modifiedLines = false;

    this->horizontalWall = '-';
    this->verticalWall = '|';

    this->selection.X = 0;
    this->selection.Y = -1;

    this->startDisplay.X = 0;
    this->startDisplay.Y = 0;

    this->defaultColumnWidth = 8;

    this->bufferSize = ReadBufferSizeFromWindow();
}



Entry &Table::operator [](int unsigned index)
{
    return this->lines[index];
}



bool Table::Sort(int mode)
{
    static bool
        rearranged;

    rearranged = false;

    switch (mode % 2)
    {
        case ASCENDING:
        {
            if (mode & SORT_BY_ID)
            {
                for (int unsigned line = 0; line < this->lines.size() - 1; line++)
                {
                    for (int unsigned compareLine = line + 1; compareLine < this->lines.size(); compareLine++)
                    {
                        if (this->lines[line].ID > this->lines[compareLine].ID)
                        {
                            std::swap(this->lines.at(line), this->lines.at(compareLine));
                            rearranged = true;
                        }
                    }
                }
            }
            else
            {
                for (int unsigned line = 0; line < this->lines.size() - 1; line++)
                {
                    for (int unsigned compareLine = line + 1; compareLine < this->lines.size(); compareLine++)
                    {
                        if (this->lines[line].column[this->selection.X] > this->lines[compareLine].column[this->selection.X])
                        {
                            std::swap(this->lines.at(line), this->lines.at(compareLine));
                            rearranged = true;
                        }
                    }
                }
            }

            break;
        }

        case DESCENDING:
        {
            if (mode & SORT_BY_ID)
            {
                for (int unsigned line = 0; line < this->lines.size() - 1; line++)
                {
                    for (int unsigned compareLine = line + 1; compareLine < this->lines.size(); compareLine++)
                    {
                        if (this->lines[line].ID < this->lines[compareLine].ID)
                        {
                            std::swap(this->lines.at(line), this->lines.at(compareLine));
                            rearranged = true;
                        }
                    }
                }
            }
            else
            {
                for (int unsigned line = 0; line < this->lines.size() - 1; line++)
                {
                    for (int unsigned compareLine = line + 1; compareLine < this->lines.size(); compareLine++)
                    {
                        if (this->lines[line].column[this->selection.X] < this->lines[compareLine].column[this->selection.X])
                        {
                            std::swap(this->lines.at(line), this->lines.at(compareLine));
                            rearranged = true;
                        }
                    }
                }
            }

            break;
        }
    }

    return rearranged;
}

void Table::CalculateColumnWidths()
{
    this->columnWidth.resize(this->format.column.size());

    for (int unsigned column = 0; column < this->format.column.size(); column++)
    {
        this->columnWidth[column] = this->format.column[column].length() + 1;
    }
}

uint16_t Table::Display()
{
    static int short unsigned
        lineSize;

    static std::string
        coloredLine,
        outputLine,
        outputTable;

    uint16_t
        cursorY;

    coloredLine = "";
    outputLine  = "";
    outputTable = "";

    this->wordWidth =
    this->word.X =
    this->word.Y = 0;

    for (int unsigned component = 0; component < this->format.column.size(); component++)
    {
        if (this->selection.Y == -1 && int(component) == this->selection.X)
        {
            this->word.Y = startDisplay.Y;
            this->word.X = outputLine.length();
            (outputLine += AllocateAndCompensate(this->format.column[component], this->columnWidth[component] - 1)) += this->verticalWall;
            this->wordWidth = this->columnWidth[component] - 1;
        }
        else
        {
            (outputLine += AllocateAndCompensate(this->format.column[component], this->columnWidth[component] - 1)) += this->verticalWall;
        }
    }

    lineSize = outputLine.length();
    this->FillLine(outputLine, lineSize);
    outputTable += outputLine;

    if (this->selection.Y == -1)
    {
        coloredLine = outputLine;
    }

    outputLine  = "";

    for (auto component : this->columnWidth)
    {
        (outputLine += std::string(component - 1, this->horizontalWall)) += this->verticalWall;
    }

    this->FillLine(outputLine, lineSize);
    outputTable += outputLine;

    for (int unsigned line = 0; line < this->lines.size(); line++)
    {
        outputLine  = "";

        for (int unsigned column = 0; column < this->lines[line].column.size(); column++)
        {
            if (this->selection.Y == int(line) && int(column) == this->selection.X)
            {
                this->word.Y = startDisplay.Y + line + 2;
                this->word.X = outputLine.length();
                (outputLine += AllocateAndCompensate(this->lines[line].column[column], this->columnWidth[column] - 1)) += this->verticalWall;
                this->wordWidth = this->columnWidth[column] - 1;
            }
            else
            {
                (outputLine += AllocateAndCompensate(this->lines[line].column[column], this->columnWidth[column] - 1)) += this->verticalWall;
            }
        }

        this->FillLine(outputLine, lineSize);
        outputTable += outputLine;

        if (this->selection.Y == int(line))
        {
            coloredLine = outputLine;
        }
    }

    outputLine = std::string(lineSize, this->horizontalWall);
    this->FillLine(outputLine, lineSize);
    outputTable += outputLine;

    ChangeTextColor(Settings::Color::idle);
    SetConsoleCursor(this->startDisplay.X,
                     this->startDisplay.Y);
    std::cout << outputTable;

    ReadBufferSizeFromWindow();
    cursorY = Default::consoleBufferInfo.dwCursorPosition.Y;

    ChangeTextColor(Settings::Color::line);
    SetConsoleCursor(0, this->word.Y);
    std::cout << coloredLine.substr(0, lineSize);

    ChangeTextColor(Settings::Color::word);
    SetConsoleCursor(this->word.X, this->word.Y);
    std::cout << (this->reassignMode? AllocateAndCompensate(cellText, this->wordWidth) : coloredLine.substr(this->word.X, this->wordWidth));

    ChangeTextColor(Settings::Color::idle);



    return cursorY;
}

void Table::DisplayValues()
{
    std::cout << std::string("Character for horizontal walls is \'") + this->horizontalWall + "\'."
               + "\nCharacter for vertical walls is \'" + this->verticalWall + "\'.";

    std::cout << "\nSelected cell at (" + StringFromUnsignedInt(this->selection.X) + ", " + StringFromUnsignedInt(this->selection.Y) + ").";

    std::cout << "\nNumber of columns: " + StringFromUnsignedInt(this->format.column.size()) + ".\n";
    this->format.DisplayValues();

    std::cout << "Default column width: " + StringFromUnsignedInt(this->defaultColumnWidth);

    std::cout << "\nEntries:\n";

    for (auto component : this->lines)
    {
        component.DisplayValues();
    }

    std::cout << "Column Widths: ";

    for (auto component : this->columnWidth)
    {
        std::cout << component << "; ";
    }

    std::cout << "\n\n\n";
}

void Table::FillLine(std::string &outputLine, int short unsigned lineSize)
{
    outputLine = AllocateAndCompensate(outputLine, this->bufferSize.first);
}

void Table::ReadFormat(File &file)
{
    this->fileFormat = this->format = file.ReadFormat();
}

void Table::ReadData(File &file)
{
    this->fileLines = this->lines = file.ReadData(this->format);
}

void Table::WriteFormat(File &file)
{
    file.WriteFormat(this->format);
}

void Table::WriteData(File &file)
{
    file.WriteData(this->lines);
}



#endif // TABLE_H
