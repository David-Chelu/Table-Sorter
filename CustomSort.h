bool Table::CustomSort(int mode)
{
    static bool
        rearranged;

    std::vector <std::pair <std::string, int unsigned>>
        lookupColumns {{"weight",     UINT_MAX},
                       {"complexity", UINT_MAX}};

    std::vector <double>
        values(this->lines.size());

    for (int unsigned column = 0; column < this->format.column.size(); column++)
    {
        for (auto &element : lookupColumns)
        {
            if (element.first == this->format.column[column])
            {
                element.second = column;
            }
        }
    }

    for (int unsigned line = 0; line < this->lines.size(); line++)
    {
        values[line] = 1;

        if (lookupColumns[0].second != UINT_MAX)
        {
            values[line] *= atof(this->lines[line].column[lookupColumns[0].second].c_str());
            values[line] *= values[line];
        }

        if (lookupColumns[1].second != UINT_MAX)
        {
            values[line] += atof(this->lines[line].column[lookupColumns[1].second].c_str());
        }
    }

    rearranged = false;

    switch (mode % 2)
    {
        case ASCENDING:
        {
            for (int unsigned line = 0; line < this->lines.size() - 1; line++)
            {
                for (int unsigned compareLine = line + 1; compareLine < this->lines.size(); compareLine++)
                {
                    if (values[line] > values[compareLine])
                    {
                        std::swap(this->lines.at(line), this->lines.at(compareLine));
                        rearranged = true;
                    }
                }
            }

            break;
        }

        case DESCENDING:
        {
            for (int unsigned line = 0; line < this->lines.size() - 1; line++)
            {
                for (int unsigned compareLine = line + 1; compareLine < this->lines.size(); compareLine++)
                {
                    if (values[line] < values[compareLine])
                    {
                        std::swap(this->lines.at(line), this->lines.at(compareLine));
                        rearranged = true;
                    }
                }
            }

            break;
        }
    }

    return rearranged;
}
