#ifndef FILE_H
#define FILE_H



struct File
{
    File();

    void
        DisplayValues();

    Entry
        ReadFormat(),
        ReadFormat(std::string directory);

    std::vector <Entry>
        ReadData(const Entry &format),
        ReadData(const Entry &format, std::string directory);



    std::string
        formatDirectory,
        dataDirectory;
};



File::File()
{
    this->formatDirectory = "format.txt";
    this->dataDirectory = "data.txt";
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

Entry File::ReadFormat(std::string directory)
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
                                "File ") + this->formatDirectory + " could not be opened.").c_str(),
                   "Error",
                   MB_OK);
    }

    return entry;
}

std::vector <Entry> File::ReadData(const Entry &format, std::string directory)
{
    this->dataDirectory = directory;

    return this->ReadData(format);
}



#endif // FILE_H
