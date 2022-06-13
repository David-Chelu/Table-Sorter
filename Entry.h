#ifndef ENTRY_H
#define ENTRY_H



struct Entry
{
    void
        DisplayValues();

    int unsigned
        ID;

    std::string
        name;

    float
        weight;

    std::vector <std::pair <std::string, std::string>>
        column;
};



void Entry::DisplayValues()
{
    std::cout << this->ID << ", " << this->name + ", " << this->weight;

    for (auto component : this->column)
    {
        std::cout << ", " + component.first + ", " + component.second;
    }

    std::cout << "\n\n";
}



#endif // ENTRY_H
