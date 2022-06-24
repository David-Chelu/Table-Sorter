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
        selection;

    Entry
        format;

    int short unsigned
        defaultColumnWidth;

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

    this->selection.X = this->selection.Y = 0;

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
    SetConsoleCursor(0, 1);

    static int short unsigned
        lineSize;

    static std::string
        outputLine,
        outputTable;

    outputTable = "";
    outputLine  = "";

    for (int unsigned component = 0; component < this->format.column.size(); component++)
    {
        (outputLine += AllocateAndCompensate(this->format.column[component], this->columnWidth[component] - 1)) += '|';
    }

    lineSize = outputLine.length();
    this->FillLine(outputLine, lineSize);
    outputTable += outputLine;
    outputLine  = "";

    for (auto component : this->columnWidth)
    {
        (outputLine += std::string(component - 1, '-')) += '|';
    }

    this->FillLine(outputLine, lineSize);
    outputTable += outputLine;

    for (auto line : this->lines)
    {
        outputLine  = "";

        for (int unsigned column = 0; column < line.column.size(); column++)
        {
            (outputLine += AllocateAndCompensate(line.column[column], this->columnWidth[column] - 1)) += '|';
        }

        this->FillLine(outputLine, lineSize);
        outputTable += outputLine;
    }

    outputLine = std::string(lineSize, '-');
    this->FillLine(outputLine, lineSize);
    outputTable += outputLine;

    std::cout << outputTable;

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
