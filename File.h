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
        file;

    file.open(this->formatDirectory, std::ios_base::ios_base::in);

    if (file.is_open())
    {
        int unsigned
            entryCount = 0;

        while (!file.eof())
        {
            entryCount++;

            format.column.push_back({"Column #" + StringFromUnsignedInt(entryCount), ""});
            file >> format.column.back().second;
        }

        file.close();
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



#endif // FILE_H
