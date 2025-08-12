#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <windows.h>
#include <conio.h>

#define BOOKINGS_FILE "bookings.txt"

void welcomePage();
void loginPage();
void dashboard();
void viewEvents();
void bookSeat();
void cancelBooking();
void adminDashboard();
void saveBooking(int eventID, const char *name);
void removeBooking(int eventID, const char *name);
void viewAllBookings();
void adminViewAllEvents();
void dashboardDesign();
void addEvent();
void clear();
void printLeftAlignedBlock(const char *str);
void resetLeftAlignedBlock();

int main()
{
    system("chcp 65001");
    loginPage();
    return 0;
}

void printCenteredInline(const char *str)
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
    printf("%s", str); // No newline!
    fflush(stdout);
}

void clear()
{
    system("cls");
}

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

// New function to print a block of text left-aligned but centered as a block
void printLeftAlignedBlock(const char *str)
{
    static int maxLen = 0;
    static int first = 1;
    static int pad = 0;

    // If this is the first call or reset was done, measure width
    if (first)
    {
        CONSOLE_SCREEN_BUFFER_INFO csbi;
        int width = 80; // default width
        HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
        if (GetConsoleScreenBufferInfo(hConsole, &csbi))
            width = csbi.srWindow.Right - csbi.srWindow.Left + 1;

        // Scan through strings to find max length
        maxLen = (int)strlen(str);

        // Calculate padding for centering the block
        pad = (width - maxLen) / 2;
        if (pad < 0)
            pad = 0;

        first = 0;
    }
    else
    {
        // For subsequent calls, update maxLen if needed
        int currentLen = (int)strlen(str);
        if (currentLen > maxLen)
        {
            // Recalculate padding based on new max length
            CONSOLE_SCREEN_BUFFER_INFO csbi;
            int width = 80; // default width
            HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
            if (GetConsoleScreenBufferInfo(hConsole, &csbi))
                width = csbi.srWindow.Right - csbi.srWindow.Left + 1;

            maxLen = currentLen;
            pad = (width - maxLen) / 2;
            if (pad < 0)
                pad = 0;
        }
    }

    // Apply padding and print
    for (int i = 0; i < pad; i++)
        putchar(' ');
    printf("%s\n", str);
}

// Function to reset the maxLen for a new block
void resetLeftAlignedBlock()
{
    static int first;
    static int maxLen;
    static int pad;

    first = 1;
    maxLen = 0;
    pad = 0;
}

void inputCentered(const char *prompt, char *buffer, int size)
{
    CONSOLE_SCREEN_BUFFER_INFO csbi;
    int width = 80; // default width
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    if (GetConsoleScreenBufferInfo(hConsole, &csbi))
        width = csbi.srWindow.Right - csbi.srWindow.Left + 1;
    int promptLen = (int)strlen(prompt);
    int pad = (width - promptLen - size) / 2;
    if (pad < 0)
        pad = 0;
    COORD pos = csbi.dwCursorPosition;
    pos.X = pad;
    SetConsoleCursorPosition(hConsole, pos);
    printf("%s", prompt);
    fflush(stdout);
    // Move cursor right after prompt
    pos.X += promptLen;
    SetConsoleCursorPosition(hConsole, pos);
    fgets(buffer, size, stdin);
    size_t len = strlen(buffer);
    if (len > 0 && buffer[len - 1] == '\n')
        buffer[len - 1] = '\0';
}

void welcomePage()
{
    const char *art[] = {
        "                                                                               ",
        "                                                                               ",
        "                                                                       @@@     ",
        "                                                                     @@@ @@    ",
        "                                                                  @@@@    @@   ",
        "                                                               @@@@  @    @@   ",
        "                                                             @@@          @    ",
        "                                                          @@@-        @   @@@  ",
        "                                                       %@@@           .     @  ",
        "                                                     @@@               @    @  ",
        "                                                    @#                     @@  ",
        "                                                   @@                   #   @@ ",
        "                                                   @@                   @    @@",
        "                                                    @@                       @@",
        "        @@@@@@ @@     @@  @@@@@@ #@@    @@ @@@@@@@@  *@                  @   @ ",
        "        @@@@@@ *@@   @@@ @@@@@@@ @@@@   @@ @@@@@@@@  @@                  @.@@@ ",
        "        @@      @@   @@  @@      @@ @   @@    @@     @                  @@@    ",
        "        @@      @@   @@  @@      @@@@@  @@    @@     @@@             @@@@      ",
        "        @@@@@@  @@   @@  @@@@@@  @@@@@  @@    @@       @            @@         ",
        "        @@@@@@   @@ @@   @@@@@@  @@@ @@ @@    @@     .+#@@@@@@@@@@@@@@@@@@@@   ",
        "        @@       @@ @@   @@      @@@ @@ @@    @@     @@@@@@@@@@*-.     @   @@  ",
        "        @@       @@ @@   @@      @@@  @@@@    @@    @@                 @    @  ",
        "        @@@@@@   .@@@@   @@@@@@@ @@@  @@@@    @@    @                       @  ",
        "        @@@@@@    @@@     @@@@@@ @@@   @@@    @@    @@                 @   @:  ",
        "                                                     @                 @   @   ",
        "                        @@@@@   @@+   @@@@  @@@@@   @@                 @    @  ",
        "                        @@     @@@@  @@     @@      @                       @  ",
        "                        @@     @@ @  @@     @       @@                 @   @@  ",
        "                        @@@@@  @  @   @@@.  @@@@     @                 @   @   ",
        "                        @@    .@@@@@   :@@  @        @                 @   @@  ",
        "                        @@    @@@@@@     @@ @       @@                      @+ ",
        "                        @@@@@ @@   @ @@@@@@ @@@@@   @                  @    @@ ",
        "                         @@@@ @    @@*@@@@   @@@@   @@               =%@@@@@=  ",
        "                                                     @@@@@@@@@@@@@@@@@@@@@@@   ",
        "                                                                               ",
    };

    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    WORD originalAttrs;

    CONSOLE_SCREEN_BUFFER_INFO csbi;
    GetConsoleScreenBufferInfo(hConsole, &csbi);
    originalAttrs = csbi.wAttributes;

    // Set color to light green (0x0A)
    SetConsoleTextAttribute(hConsole, FOREGROUND_GREEN | FOREGROUND_INTENSITY);

    int rows = sizeof(art) / sizeof(art[0]);

    for (int i = 0; i < rows; i++)
    {
        for (const char *p = art[i]; *p; p++)
        {
            putchar(*p);
            putchar(*p); // stretch horizontally
            fflush(stdout);
            Sleep(0);
        }
        putchar('\n');
    }

    // Reset original color
    SetConsoleTextAttribute(hConsole, originalAttrs);
}

void dashboardDesign()
{
    HANDLE h = GetStdHandle(STD_OUTPUT_HANDLE);
    CONSOLE_SCREEN_BUFFER_INFO ci;
    GetConsoleScreenBufferInfo(h, &ci);

    // Cyan = FOREGROUND_GREEN | FOREGROUND_BLUE | FOREGROUND_INTENSITY
    SetConsoleTextAttribute(h, FOREGROUND_GREEN | FOREGROUND_BLUE | FOREGROUND_INTENSITY);

    const char *art[] = {
        "  _____             _____  _    _  ____    ____            _____   _____  ",
        " |  __ \\    /\\     / ____|| |  | ||  _ \\  / __ \\    /\\    |  __ \\ |  __ \\ ",
        " | |  | |  /  \\   | (___  | |__| || |_) || |  | |  /  \\   | |__) || |  | |",
        " | |  | | / /\\ \\   \\___ \\ |  __  ||  _ < | |  | | / /\\ \\  |  _  / | |  | |",
        " | |__| |/ ____ \\  ____) || |  | || |_) || |__| |/ ____ \\ | | \\ \\ | |__| |",
        " |_____//_/    \\_\\|_____/ |_|  |_||____/  \\____//_/    \\_\\|_|  \\_\\|_____/ ",
        "                                                                          "};

    int lines = sizeof(art) / sizeof(art[0]);
    for (int i = 0; i < lines; i++)
    {
        printCentered(art[i]);
        Sleep(60);
    }

    SetConsoleTextAttribute(h, ci.wAttributes);
}

void loginPage() // Function used for login
{

#define USERNAME "user"
#define PASSWORD "weakpassword"
#define aUSERNAME "admin"
#define aPASSWORD "strongpassword"
    char user[50], pass[50];
    while (1)
    {
        clear(); // Clear screen before welcome page
        welcomePage();
        printCentered("Enter your User name and password to login...");
        inputCentered("Username: ", user, sizeof(user));
        inputCentered("Password: ", pass, sizeof(pass));

        if (strcmp(user, USERNAME) == 0 && strcmp(pass, PASSWORD) == 0)
        {
            printCentered("Login Success");
            clear();
            dashboard();
            break;
        }
        else if (strcmp(user, aUSERNAME) == 0 && strcmp(pass, aPASSWORD) == 0)
        {
            printCentered("Admin Access granted");
            clear();
            adminDashboard();
            break;
        }
        else
        {
            printCentered("Invalid Credentials. Try again");
            clear();
        }
    }
}

void adminDashboard()
{
    int choice;
    while (1)
    {
        dashboardDesign();
        resetLeftAlignedBlock(); // Reset the block formatting
        printLeftAlignedBlock("1. View all bookings");
        printLeftAlignedBlock("2. Add Event");
        printLeftAlignedBlock("3. View All Events");
        printLeftAlignedBlock("0. Exit");
        char buf[16];
        inputCentered("Select an option: ", buf, sizeof(buf));
        if (sscanf(buf, "%d", &choice) != 1)
        {
            printCentered("Invalid input. Please enter a number.");
            continue;
        }

        switch (choice)
        {
        case 1:
            clear();
            viewAllBookings();
            break;
        case 2:
            clear();
            addEvent();
            break;
        case 3:
            clear();
            adminViewAllEvents();
            break;
        case 0:
            clear();
            printCentered("Logging out of admin panel...");
            return;
        default:
            clear();
            printCentered("Invalid choice. Please select again.");
        }
    }
}
// Admin function to view, edit, or delete events
void adminViewAllEvents()
{
    FILE *file = fopen("events.txt", "r");
    if (file == NULL)
    {
        printCentered("No events found.");
        return;
    }

    char line[300], name[100], venue[100], date[20], time[20];
    int seatCapacity, newSeatCapacity;
    int eventCount = 0;
    char events[50][300]; // Store up to 50 events

    printCentered("-- All Events --");
    resetLeftAlignedBlock(); // Reset the block formatting
    while (fgets(line, sizeof(line), file))
    {
        if (sscanf(line, "%99[^|]|%99[^|]|%19[^|]|%19[^|]|%d", name, venue, date, time, &seatCapacity) == 5)
        {
            eventCount++;
            strncpy(events[eventCount - 1], line, sizeof(events[eventCount - 1]) - 1);
            events[eventCount - 1][sizeof(events[eventCount - 1]) - 1] = '\0';
            char eventBuf[200];
            snprintf(eventBuf, sizeof(eventBuf), "%d. %s", eventCount, name);
            printLeftAlignedBlock(eventBuf);
        }
    }
    fclose(file);
    char returnBuf[100];
    snprintf(returnBuf, sizeof(returnBuf), "%d. Return to admin menu", eventCount + 1);
    printLeftAlignedBlock(returnBuf);

    if (eventCount == 0)
        return;

    int choice;
    char selectPrompt[100];
    snprintf(selectPrompt, sizeof(selectPrompt), "Select an event to view/edit/delete or %d to return: ", eventCount + 1);
    char buf[16];
    inputCentered(selectPrompt, buf, sizeof(buf));
    if (sscanf(buf, "%d", &choice) != 1)
    {
        printCentered("Invalid input.");
        return;
    }
    if (choice < 1 || choice > eventCount + 1)
    {
        printCentered("Invalid choice.");
        return;
    }
    if (choice == eventCount + 1)
    {
        clear(); // Clear screen before returning to admin dashboard
        return;
    }

    // Show details for selected event
    sscanf(events[choice - 1], "%99[^|]|%99[^|]|%19[^|]|%19[^|]|%d", name, venue, date, time, &seatCapacity);
    printCentered("--- Event Details ---");
    resetLeftAlignedBlock(); // Reset the block formatting
    char buf_output[200];
    snprintf(buf_output, sizeof(buf_output), "Name: %s", name);
    printLeftAlignedBlock(buf_output);
    snprintf(buf_output, sizeof(buf_output), "Venue: %s", venue);
    printLeftAlignedBlock(buf_output);
    snprintf(buf_output, sizeof(buf_output), "Date (DD-MM-YYYY): %s", date);
    printLeftAlignedBlock(buf_output);
    snprintf(buf_output, sizeof(buf_output), "Time: %s", time);
    printLeftAlignedBlock(buf_output);
    snprintf(buf_output, sizeof(buf_output), "Seat Capacity: %d", seatCapacity);
    printLeftAlignedBlock(buf_output);

    resetLeftAlignedBlock(); // Reset for menu options
    printLeftAlignedBlock("1. Edit Event");
    printLeftAlignedBlock("2. Delete Event");
    printLeftAlignedBlock("3. Return");
    int action;
    char buf2[16];
    inputCentered("Select an option: ", buf2, sizeof(buf2));
    if (sscanf(buf2, "%d", &action) != 1)
    {
        printCentered("Invalid input.");
        return;
    }

    if (action == 1)
    {
        // Edit event
        char newName[100], newVenue[100], newDate[20], newTime[20];
        while (getchar() != '\n')
            ; // clear input buffer
        char promptName[150];
        snprintf(promptName, sizeof(promptName), "Enter new event name (or press Enter to keep '%s'): ", name);
        inputCentered(promptName, newName, sizeof(newName));
        if (newName[0] == '\n')
            strcpy(newName, name);
        else
        {
            size_t l = strlen(newName);
            if (l > 0 && newName[l - 1] == '\n')
                newName[l - 1] = '\0';
        }

        char promptVenue[150];
        snprintf(promptVenue, sizeof(promptVenue), "Enter new venue (or press Enter to keep '%s'): ", venue);
        inputCentered(promptVenue, newVenue, sizeof(newVenue));
        if (newVenue[0] == '\n')
            strcpy(newVenue, venue);
        else
        {
            size_t l = strlen(newVenue);
            if (l > 0 && newVenue[l - 1] == '\n')
                newVenue[l - 1] = '\0';
        }

        char promptDate[150];
        snprintf(promptDate, sizeof(promptDate), "Enter new date (DD-MM-YYYY) (or press Enter to keep '%s'): ", date);
        inputCentered(promptDate, newDate, sizeof(newDate));
        if (newDate[0] == '\n')
            strcpy(newDate, date);
        else
        {
            size_t l = strlen(newDate);
            if (l > 0 && newDate[l - 1] == '\n')
                newDate[l - 1] = '\0';
        }

        char promptTime[150];
        snprintf(promptTime, sizeof(promptTime), "Enter new time (or press Enter to keep '%s'): ", time);
        inputCentered(promptTime, newTime, sizeof(newTime));
        if (newTime[0] == '\n')
            strcpy(newTime, time);
        else
        {
            size_t l = strlen(newTime);
            if (l > 0 && newTime[l - 1] == '\n')
                newTime[l - 1] = '\0';
        }

        char promptSeat[100];
        snprintf(promptSeat, sizeof(promptSeat), "Enter new seat capacity (or 0 to keep %d): ", seatCapacity);
        char buf3[16];
        inputCentered(promptSeat, buf3, sizeof(buf3));
        if (sscanf(buf3, "%d", &newSeatCapacity) != 1 || newSeatCapacity <= 0)
            newSeatCapacity = seatCapacity;

        // Update event in array
        snprintf(events[choice - 1], sizeof(events[choice - 1]), "%s|%s|%s|%s|%d\n", newName, newVenue, newDate, newTime, newSeatCapacity);
        printCentered("Event updated successfully!");

        // Add prompt to continue
        char continueBuf[10];
        inputCentered("Press Enter to continue...", continueBuf, sizeof(continueBuf));
        clear(); // Clear screen after event update
    }
    else if (action == 2)
    {
        // Delete event
        for (int i = choice - 1; i < eventCount - 1; i++)
        {
            strcpy(events[i], events[i + 1]);
        }
        eventCount--;
        clear();
        printCentered("Event deleted successfully!");
    }
    else
    {
        clear();
        return;
    }

    // Write updated events back to file
    file = fopen("events.txt", "w");
    if (file == NULL)
    {
        printCentered("Error updating events file!");
        return;
    }
    for (int i = 0; i < eventCount; i++)
    {
        fputs(events[i], file);
    }
    fclose(file);
}

void viewAllBookings()
{
    FILE *file = fopen(BOOKINGS_FILE, "r");
    if (file == NULL)
    {
        printCentered("No bookings found.");
        return;
    }

    printCentered("--- All Bookings ---");
    resetLeftAlignedBlock(); // Reset the block formatting
    printLeftAlignedBlock("Event ID | Name");
    printLeftAlignedBlock("-------------------");

    char line[200];
    int eventID;
    char name[100];

    while (fgets(line, sizeof(line), file))
    {
        if (sscanf(line, "%d %[^\n]", &eventID, name) == 2)
        {
            char buf[200];
            snprintf(buf, sizeof(buf), "%8d | %s", eventID, name);
            printLeftAlignedBlock(buf);
        }
    }
    printLeftAlignedBlock("-------------------");
    fclose(file);

    // Add prompt to continue
    char continueBuf[10];
    inputCentered("Press Enter to continue...", continueBuf, sizeof(continueBuf));
    clear(); // Clear screen after viewing bookings
}

// Dashboard for user
void dashboard()
{
    int choice;

    while (1)
    {
        dashboardDesign();
        resetLeftAlignedBlock(); // Reset the block formatting
        printLeftAlignedBlock("1. View Events");
        printLeftAlignedBlock("2. Book Seat");
        printLeftAlignedBlock("3. Cancel Booking");
        printLeftAlignedBlock("4. View All Bookings");
        printLeftAlignedBlock("0. Exit");
        char buf[16];
        inputCentered("Select an option: ", buf, sizeof(buf));
        if (sscanf(buf, "%d", &choice) != 1)
        {
            printCentered("Invalid input. Please enter a number.");
            continue;
        }

        switch (choice)
        {
        case 1:
            clear();
            viewEvents();
            break;
        case 2:
            clear();
            bookSeat();
            break;
        case 3:
            clear();
            cancelBooking();
            break;
        case 4:
            clear();
            viewAllBookings();
            break;
        case 0:
            clear();
            printCentered("Thank you for using EventEase!");
            exit(0);
        default:
            clear();
            printCentered("Invalid choice. Please select again.");
        }
    }
}
// Function to add event information and save to events.txt
void addEvent()
{
    char name[100], venue[100], date[20], time[20];
    int seatCapacity;

    printCentered("-- Add New Event --");
    resetLeftAlignedBlock(); // Reset the block formatting for prompts
    inputCentered("Event Name: ", name, 40);
    inputCentered("Venue: ", venue, 40);
    inputCentered("Date (DD-MM-YYYY): ", date, sizeof(date));
    inputCentered("Time (HH:MM): ", time, sizeof(time));

    char buf[16];
    inputCentered("Seat Capacity: ", buf, sizeof(buf));
    if (sscanf(buf, "%d", &seatCapacity) != 1)
    {
        printCentered("Invalid input for seat capacity.");
        return;
    }

    FILE *file = fopen("events.txt", "a");
    if (file == NULL)
    {
        printCentered("Error opening events file!");
        return;
    }
    fprintf(file, "%s|%s|%s|%s|%d\n", name, venue, date, time, seatCapacity);
    fclose(file);
    printCentered("Event added successfully!");

    // Add prompt to continue
    char continueBuf[10];
    inputCentered("Press Enter to continue...", continueBuf, sizeof(continueBuf));
    clear(); // Clear screen after adding event
}

void viewEvents()
{
    FILE *file = fopen("events.txt", "r");
    if (file == NULL)
    {
        printCentered("No events found.");
        return;
    }

    char line[300], name[100], venue[100], date[20], time[20];
    int seatCapacity;
    int eventCount = 0;
    char events[50][300]; // Store up to 50 events

    printCentered("-- Available Events --");
    resetLeftAlignedBlock(); // Reset the block formatting
    while (fgets(line, sizeof(line), file))
    {
        if (sscanf(line, "%99[^|]|%99[^|]|%19[^|]|%19[^|]|%d", name, venue, date, time, &seatCapacity) == 5)
        {
            eventCount++;
            snprintf(events[eventCount - 1], sizeof(events[eventCount - 1]), "%s|%s|%s|%s|%d", name, venue, date, time, seatCapacity);
            char buf[200];
            snprintf(buf, sizeof(buf), "%d. %s", eventCount, name);
            printLeftAlignedBlock(buf);
        }
    }
    fclose(file);
    char buf[100];
    snprintf(buf, sizeof(buf), "%d. Return to main menu", eventCount + 1);
    printLeftAlignedBlock(buf);

    if (eventCount == 0)
        return;

    int choice;
    char selectPrompt[100];
    snprintf(selectPrompt, sizeof(selectPrompt), "Select an event to view details or %d to return: ", eventCount + 1);
    char buf_input[16];
    inputCentered(selectPrompt, buf_input, sizeof(buf_input));
    if (sscanf(buf_input, "%d", &choice) != 1)
    {
        printCentered("Invalid input.");
        return;
    }
    if (choice < 1 || choice > eventCount + 1)
    {
        printCentered("Invalid choice.");
        return;
    }
    if (choice == eventCount + 1)
    {
        clear(); // Clear screen before returning to dashboard
        return;
    }

    // Show details for selected event
    sscanf(events[choice - 1], "%99[^|]|%99[^|]|%19[^|]|%19[^|]|%d", name, venue, date, time, &seatCapacity);
    printCentered("\n--- Event Details ---");
    resetLeftAlignedBlock(); // Reset the block formatting
    snprintf(buf, sizeof(buf), "Name: %s", name);
    printLeftAlignedBlock(buf);
    snprintf(buf, sizeof(buf), "Venue: %s", venue);
    printLeftAlignedBlock(buf);
    snprintf(buf, sizeof(buf), "Date (DD-MM-YYYY): %s", date);
    printLeftAlignedBlock(buf);
    snprintf(buf, sizeof(buf), "Time: %s", time);
    printLeftAlignedBlock(buf);
    snprintf(buf, sizeof(buf), "Seat Capacity: %d", seatCapacity);
    printLeftAlignedBlock(buf);

    // Add prompt to continue
    char continueBuf[10];
    inputCentered("Press Enter to continue...", continueBuf, sizeof(continueBuf));
    clear(); // Clear screen after viewing event details
}

void bookSeat()
{
    char name[100];
    int eventID;

    printCentered("-- Book a Seat --");
    // Check if there are any events
    FILE *file = fopen("events.txt", "r");
    if (file == NULL)
    {
        printCentered("No events found.");
        return;
    }
    int eventCount = 0;
    char line[300];
    while (fgets(line, sizeof(line), file))
    {
        eventCount++;
    }
    fclose(file);
    if (eventCount == 0)
    {
        printCentered("No events found.");
        return;
    }

    viewEvents();
    char buf[100];
    snprintf(buf, sizeof(buf), "Enter Event ID to book (1-%d): ", eventCount);
    char buf2[16];
    inputCentered(buf, buf2, sizeof(buf2));
    if (sscanf(buf2, "%d", &eventID) != 1)
    {
        printCentered("Invalid input for Event ID.");
        return;
    }

    if (eventID < 1 || eventID > eventCount)
    {
        printCentered("Invalid Event ID");
        return;
    }

    while (getchar() != '\n')
        ;
    inputCentered("Enter your name: ", name, sizeof(name));

    saveBooking(eventID, name);

    snprintf(buf, sizeof(buf), "Seat booked successfully for %s at event ID %d.", name, eventID);
    printCentered(buf);

    // Add prompt to continue
    char continueBuf[10];
    inputCentered("Press Enter to continue...", continueBuf, sizeof(continueBuf));
    clear(); // Clear screen after booking confirmation
}

void cancelBooking()
{
    char name[100];
    int eventID;

    printCentered("-- Cancel Booking --");
    while (getchar() != '\n')
        ;
    inputCentered("Enter your name: ", name, sizeof(name));

    char buf[16];
    inputCentered("Enter Event ID to cancel: ", buf, sizeof(buf));
    if (sscanf(buf, "%d", &eventID) != 1)
    {
        printCentered("Invalid input for Event ID.");
        return;
    }

    removeBooking(eventID, name);

    // Add prompt to continue
    char continueBuf[10];
    inputCentered("Press Enter to continue...", continueBuf, sizeof(continueBuf));
    clear(); // Clear screen after cancellation process
}

void saveBooking(int eventID, const char *name)
{
    FILE *file = fopen(BOOKINGS_FILE, "a");
    if (file == NULL)
    {
        printCentered("Error opening file, Name of event ID not Found!");
        return;
    }

    fprintf(file, "%d %s\n", eventID, name);
    fclose(file);
}

void removeBooking(int eventID, const char *name)
{
    FILE *file = fopen(BOOKINGS_FILE, "r");
    FILE *tempFile = fopen("temp.txt", "w");

    if (file == NULL || tempFile == NULL)
    {
        printCentered("Error opening file!");
        if (file)
            fclose(file);
        if (tempFile)
            fclose(tempFile);
        return;
    }

    char line[200];
    int eventInLine;
    char nameInLine[100];
    int found = 0;

    while (fgets(line, sizeof(line), file))
    {
        if (sscanf(line, "%d %[^\n]", &eventInLine, nameInLine) == 2)
        {
            if (eventInLine == eventID && strcmp(nameInLine, name) == 0)
            {
                found = 1;
                continue;
            }
        }
        fputs(line, tempFile);
    }

    fclose(file);
    fclose(tempFile);

    if (found)
    {
        remove(BOOKINGS_FILE);
        rename("temp.txt", BOOKINGS_FILE);
        printCentered("Booking successfully canceled.");
    }
    else
    {
        remove("temp.txt");
        char buf[200];
        snprintf(buf, sizeof(buf), "No booking found for %s at event ID %d.", name, eventID);
        printCentered(buf);
    }
}
