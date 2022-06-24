#ifndef TABLE_H
#define TABLE_H



struct Table
{
    Table();

    void
        CalculateColumnWidths(),
        Display(),
        DisplayValues(),
        FillLine(std::string &outputLine, int short unsigned lineSize);



    bool
        shortened;

    char
        horizontalWall,
        verticalWall;

    COORD
        selection,
        startDisplay,
        word;

    Entry
        format;

    int short unsigned
        defaultColumnWidth,
        wordWidth;

    std::pair <int, int>
        bufferSize;

    std::vector <Entry>
        lines;

    std::vector <int short unsigned>
        columnWidth;
};



Table::Table()
{
    this->shortened = false;

    this->horizontalWall = '-';
    this->verticalWall = '|';

    this->selection.X = 0;
    this->selection.Y = -1;

    this->startDisplay.X = 0;
    this->startDisplay.Y = 0;

    this->defaultColumnWidth = 8;

    this->bufferSize = ReadBufferSizeFromWindow();
}

void Table::CalculateColumnWidths()
{
    this->columnWidth.resize(this->format.column.size());

    for (int unsigned column = 0; column < this->format.column.size(); column++)
    {
        this->columnWidth[column] = this->format.column[column].length() + 1;
    }
}

void Table::Display()
{
    SetConsoleCursor(this->startDisplay.X,
                     this->startDisplay.Y);

    static int short unsigned
        lineSize;

    static std::string
        coloredLine,
        outputLine,
        outputTable;

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
            this->wordWidth = this->columnWidth[component];
        }
        else
        {
            (outputLine += AllocateAndCompensate(this->format.column[component], this->columnWidth[component] - 1)) += this->verticalWall;
        }
    }

    if (this->selection.Y == -1)
    {
        coloredLine = outputLine;
    }

    lineSize = outputLine.length();
    this->FillLine(outputLine, lineSize);
    outputTable += outputLine;
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

        if (this->selection.Y == int(line))
        {
            coloredLine = outputLine;
        }

        this->FillLine(outputLine, lineSize);
        outputTable += outputLine;
    }

    outputLine = std::string(lineSize, this->horizontalWall);
    this->FillLine(outputLine, lineSize);
    outputTable += outputLine;

    std::cout << outputTable;

    SetConsoleTextAttribute(Default::consoleOutputHandle,
                            7 << 4);
    SetConsoleCursor(0, this->word.Y);
    std::cout << coloredLine;

    SetConsoleTextAttribute(Default::consoleOutputHandle,
                            8 << 4);
    SetConsoleCursor(this->word.X, this->word.Y);
    std::cout << coloredLine.substr(this->word.X, this->wordWidth);

    SetConsoleTextAttribute(Default::consoleOutputHandle,
                            7);

    this->shortened = false;
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



#endif // TABLE_H
