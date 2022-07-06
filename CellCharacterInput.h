std::vector <int> CellAlphabeticInput()
{
    std::vector <int>
        characterContainer;

    for (char element = 'A'; element <= 'Z'; element++)
    {
        characterContainer.push_back(element);
    }

    return characterContainer;
}

std::vector <int> CellNumericInput()
{
    std::vector <int>
        characterContainer;

    for (char element = '0'; element <= '9'; element++)
    {
        characterContainer.push_back(element);
    }

    return characterContainer;
}

std::vector <int> CellNumpadNumericInput()
{
    std::vector <int>
        characterContainer;

    for (char element = VK_NUMPAD0; element <= VK_NUMPAD9; element++)
    {
        characterContainer.push_back(element);
    }

    return characterContainer;
}
