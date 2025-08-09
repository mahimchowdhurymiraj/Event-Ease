void printCentered(const char *str)
{
    CONSOLE_SCREEN_BUFFER_INFO csbi;
    int width = 80; // default width
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    if (GetConsoleScreenBufferInfo(hConsole, &csbi))
        width = csbi.srWindow.Right - csbi.srWindow.Left + 1;
    int len = (int)strlen(str);
    int pad = (width - len) / 2;
    if (pad < 0)
        pad = 0;
    for (int i = 0; i < pad; i++)
        putchar(' ');
    printf("%s\n", str);
}
