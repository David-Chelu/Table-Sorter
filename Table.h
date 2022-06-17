#ifndef TABLE_H
#define TABLE_H



struct Table
{
    Table();

    void
        CalculateColumnWidths(),
        Display(),
        DisplayValues();



    char
        horizontalWall,
        verticalWall;

    COORD
        selection;

    Entry
        format;

    int short unsigned
        defaultColumnWidth;

    std::vector <Entry>
        lines;

    std::vector <int short unsigned>
        columnWidth;
};



Table::Table()
{
    this->horizontalWall = '-';
    this->verticalWall = '|';

    this->selection.X = this->selection.Y = 0;

    this-> defaultColumnWidth = 8;
}

void Table::CalculateColumnWidths()
{
    this->columnWidth.resize(this->format.column.size());

    for (int unsigned column = 0; column < this->format.column.size(); column++)
    {
        this->columnWidth[column] = this->format.column[column].length() + 1;
    }
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



#endif // TABLE_H
