#ifndef ENTRY_H
#define ENTRY_H



struct Entry
{
    Entry
        &operator =(const Entry &targetEntry);

    std::string
        &operator [](int unsigned index);



    void
        DisplayValues();



    int unsigned
        ID;

    std::vector <std::string>
        column;
};



Entry &Entry::operator =(const Entry &targetEntry)
{
    this->column = targetEntry.column;

    return *this;
}

std::string &Entry::operator [](int unsigned index)
{
    return this->column[index];
}



void Entry::DisplayValues()
{
    std::cout << "Entry #" + StringFromUnsignedInt(this->ID) + ": ";

    for (auto component : this->column)
    {
        std::cout << component + "; ";
    }

    std::cout << "\n";
}



#endif // ENTRY_H
