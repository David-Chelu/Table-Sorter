#ifndef MAIN_SCREEN_H
#define MAIN_SCREEN_H



struct MainScreen
{
    MainScreen();

    void
        Display(),
        AddLine(const std::string &target);

    int unsigned
        selectedLine;

    std::vector <std::string>
        lines;
};

MainScreen::MainScreen()
{
    this->selectedLine = 0;
}

void MainScreen::Display()
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

    ChangeTextColor(Settings::Color::line);
    SetConsoleCursor(0, this->selectedLine);
    std::cout << this->lines[this->selectedLine];

    ChangeTextColor(Settings::Color::idle);
}

void MainScreen::AddLine(const std::string &target)
{
    this->lines.push_back(target);
}



#endif // MAIN_SCREEN_H
