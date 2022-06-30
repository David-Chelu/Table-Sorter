#ifndef SETTINGS_SCREEN_H
#define SETTINGS_SCREEN_H



struct SettingsScreen
{
    SettingsScreen();

    void
        Display();

    int unsigned
        selectedLine;

    std::vector <std::string>
        lines;

    std::vector <int unsigned>
        optionLine;
};

SettingsScreen::SettingsScreen()
{
    this->selectedLine = 0;

    this->lines.push_back("    Color:");
    this->lines.push_back("Idle (No Selection)");
    this->lines.push_back("Line Selection");
    this->lines.push_back("Word Selection");

    this->optionLine.push_back(1);
    this->optionLine.push_back(2);
    this->optionLine.push_back(3);


/*
    this->lines.push_back("\n    Key Bindings:");
    this->lines.push_back("sortAscending");
    this->lines.push_back("sortDescending");
    this->lines.push_back("customSortAscending");
    this->lines.push_back("customSortDescending");
    this->lines.push_back("expandColumn");
    this->lines.push_back("shrinkColumn");
    this->lines.push_back("moveSelectionUp");
    this->lines.push_back("moveSelectionDown");
    this->lines.push_back("moveSelectionLeft");
    this->lines.push_back("moveSelectionRight");
    this->lines.push_back("exit");
    this->lines.push_back("open");

    this->optionLine.push_back(6);
    this->optionLine.push_back(7);
    this->optionLine.push_back(8);
    this->optionLine.push_back(9);
    this->optionLine.push_back(10);
    this->optionLine.push_back(11);
    this->optionLine.push_back(12);
    this->optionLine.push_back(13);
    this->optionLine.push_back(14);
    this->optionLine.push_back(15);
    this->optionLine.push_back(16);
    this->optionLine.push_back(17);*/
}

void SettingsScreen::Display()
{
    std::string
        outputMainScreen;

    for (auto element : this->lines)
    {
        outputMainScreen += element + '\n';
    }

    ChangeTextColor(Settings::Color::idle);
    SetConsoleCursor(0, 0);
    std::cout << outputMainScreen;

    switch (this->selectedLine)
    {
        case 0:
        {
            ChangeTextColor(Settings::Color::idle);
            break;
        }
        case 1:
        {
            ChangeTextColor(Settings::Color::line);
            break;
        }
        case 2:
        {
            ChangeTextColor(Settings::Color::word);
            break;
        }
        default:
        {
            ChangeTextColor(Settings::Color::line);
            break;
        }
    }

    SetConsoleCursor(0, this->optionLine[this->selectedLine]);
    std::cout << this->lines[this->optionLine[this->selectedLine]];

    ChangeTextColor(Settings::Color::idle);
}



#endif // SETTINGS_SCREEN_H
