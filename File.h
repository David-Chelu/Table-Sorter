#ifndef FILE_H
#define FILE_H



struct File
{
    File();

    void
        DisplayValues();

    Entry
        ReadFormat(),
        ReadFormat(const std::string directory);

    std::vector <Entry>
        ReadData(const Entry &format),
        ReadData(const Entry &format, const std::string directory);

    bool
        WriteFormat(const Entry &format) const,
        WriteFormat(const Entry &format, const std::string directory),
        WriteData(const std::vector <Entry> &entry) const,
        WriteData(const std::vector <Entry> &entry, const std::string directory);



    std::string
        formatDirectory,
        dataDirectory;
};



File::File()
{
    this->formatDirectory = "format.txt";
    this->dataDirectory   = "data.txt";
}

void File::DisplayValues()
{
    std::cout << "Format Directory: " + this->formatDirectory
               + "\nData Directory: " + this->dataDirectory
               + "\n\n";
}

Entry File::ReadFormat()
{
    Entry
        format;

    std::fstream
        formatFile;

    formatFile.open(this->formatDirectory, std::ios_base::ios_base::in);

    if (formatFile.is_open())
    {
        int unsigned
            entryCount = 0;

        while (!formatFile.eof())
        {
            entryCount++;

            format.column.push_back("");
            formatFile >> format.column.back();
            std::replace(format.column.back().begin(), format.column.back().end(), '_', ' ');
        }

        formatFile.close();
    }
    else
    {
        MessageBox(NULL,
                   (std::string("In method \"Entry File::ReadFormat()\":\n\n"
                                "File ") + this->formatDirectory + " could not be opened.").c_str(),
                   "Error",
                   MB_OK);
    }

    return format;
}

Entry File::ReadFormat(const std::string directory)
{
    this->formatDirectory = directory;

    return this->ReadFormat();
}

std::vector <Entry> File::ReadData(const Entry &format)
{
    std::vector <Entry>
        entry;

    std::fstream
        dataFile;

    dataFile.open(this->dataDirectory, std::ios_base::ios_base::in);

    if (dataFile.is_open())
    {
        int unsigned
            entryCount = 1;

        static Entry
            fileLine;

        fileLine.column.resize(format.column.size());

        while (!dataFile.eof())
        {
            fileLine.ID = entryCount;

            for (int unsigned component = 0; component < format.column.size() && !dataFile.eof(); component++)
            {
                dataFile >> fileLine.column[component];

                std::replace(fileLine.column[component].begin(), fileLine.column[component].end(), '_', ' ');
            }

            entry.push_back(fileLine);

            entryCount++;
        }

        dataFile.close();
    }
    else
    {
        MessageBox(NULL,
                   (std::string("In method \"std::vector <Entry> File::ReadData(const Entry &format)\":\n\n"
                                "File ") + this->dataDirectory + " could not be opened.").c_str(),
                   "Error",
                   MB_OK);
    }

    return entry;
}

std::vector <Entry> File::ReadData(const Entry &format, const std::string directory)
{
    this->dataDirectory = directory;

    return this->ReadData(format);
}

bool File::WriteFormat(const Entry &format) const
{
    std::fstream
        formatFile;

    formatFile.open(this->formatDirectory, std::ios_base::ios_base::out);

    if (formatFile.is_open())
    {
        std::string
            fileOutput;

        for (auto component : format.column)
        {
            component = StripString(component);

            std::replace(component.begin(), component.end(), ' ', '_');

            fileOutput = fileOutput + component + ' ';
        }

        while (fileOutput.back() == ' ')
        {
            fileOutput.pop_back();
        }

        formatFile << fileOutput;

        formatFile.close();

        return true;
    }
    else
    {
        MessageBox(NULL,
                   (std::string("In method \"bool File::WriteFormat(const Entry &format) const\":\n\n"
                                "File ") + this->formatDirectory + " could not be opened.").c_str(),
                   "Error",
                   MB_OK);
    }

    return false;
}

bool File::WriteFormat(const Entry &format, const std::string directory)
{
    this->formatDirectory = directory;

    return this->WriteFormat(format);
}

bool File::WriteData(const std::vector <Entry> &entry) const
{
    std::fstream
        dataFile;

    dataFile.open(this->dataDirectory, std::ios_base::ios_base::out);

    if (dataFile.is_open())
    {
        std::string
            fileOutput;

        for (auto line : entry)
        {
            for (auto column : line.column)
            {
                column = StripString(column);

                std::replace(column.begin(), column.end(), ' ', '_');

                fileOutput = fileOutput + column + ' ';
            }

            while (fileOutput.back() == ' ')
            {
                fileOutput.pop_back();
            }

            fileOutput += '\n';
        }

        fileOutput.pop_back();
        dataFile << fileOutput;

        dataFile.close();

        return true;
    }
    else
    {
        MessageBox(NULL,
                   (std::string("In method \"bool File::WriteData(const std::vector <Entry> &entry) const\":\n\n"
                                "File ") + this->dataDirectory + " could not be opened.").c_str(),
                   "Error",
                   MB_OK);
    }

    return false;
}

bool File::WriteData(const std::vector <Entry> &entry, const std::string directory)
{
    this->dataDirectory = directory;

    return this->WriteData(entry);
}



#endif // FILE_H
