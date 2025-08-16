// Header Functions

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <windows.h>
#include <conio.h>

#define BOOKINGS_FILE "bookings.txt"

// ===== UTILITY FUNCTION DECLARATIONS =====
int getConsoleWidth();
void clear();
void printCentered(const char *str);
void printCenteredInline(const char *str);
void printCenteredBlock(const char *items[], int count);
void inputCentered(const char *prompt, char *buffer, int size);

// ===== UI FUNCTION DECLARATIONS =====
void welcomePage();
void dashboardDesign();

// ===== AUTHENTICATION FUNCTION DECLARATIONS =====
void loginPage();

// ===== MENU FUNCTION DECLARATIONS =====
void dashboard();
void adminDashboard();

// ===== EVENT FUNCTION DECLARATIONS =====
void viewEvents();
void addEvent();
void showEventSummary(const char *name, const char *venue, const char *date, const char *time, int seatCapacity);
void adminViewAllEvents();

// ===== BOOKING FUNCTION DECLARATIONS =====
void bookSeat();
void cancelBooking();
void saveBooking(int eventID, const char *name);
void removeBooking(int eventID, const char *name);
void viewAllBookings();

int main()
{
    system("chcp 65001");
    loginPage();
    return 0;
}

// ===== UTILITY FUNCTIONS =====
int getConsoleWidth()
{
    CONSOLE_SCREEN_BUFFER_INFO csbi;
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    if (GetConsoleScreenBufferInfo(hConsole, &csbi))
        return csbi.srWindow.Right - csbi.srWindow.Left + 1;
    return 80; // default width
}

void clear()
{
    system("cls");
}

void printCentered(const char *str)
{
    int width = getConsoleWidth();
    int len = (int)strlen(str);
    int pad = (width - len) / 2;
    if (pad < 0)
        pad = 0;
    for (int i = 0; i < pad; i++)
        putchar(' ');
    printf("%s\n", str);
}

void printCenteredInline(const char *str)
{
    int width = getConsoleWidth();
    int len = (int)strlen(str);
    int pad = (width - len) / 2;
    if (pad < 0)
        pad = 0;
    for (int i = 0; i < pad; i++)
        putchar(' ');
    printf("%s", str); // No newline!
    fflush(stdout);
}

// Function to print a block of menu items centered as a group but left-aligned within the block
void printCenteredBlock(const char *items[], int count)
{
    if (count <= 0)
        return;

    int width = getConsoleWidth();

    // Find the maximum length among all items
    int maxLen = 0;
    for (int i = 0; i < count; i++)
    {
        int len = (int)strlen(items[i]);
        if (len > maxLen)
            maxLen = len;
    }

    // Calculate padding to center the block
    int pad = (width - maxLen) / 2;
    if (pad < 0)
        pad = 0;

    // Print each item with the same left padding
    for (int i = 0; i < count; i++)
    {
        for (int j = 0; j < pad; j++)
            putchar(' ');
        printf("%s\n", items[i]);
    }
}

void inputCentered(const char *prompt, char *buffer, int size)
{
    int width = getConsoleWidth();
    int promptLen = (int)strlen(prompt);
    int pad = (width - promptLen) / 2;
    if (pad < 0)
        pad = 0;

    // Print padding and prompt
    for (int i = 0; i < pad; i++)
        putchar(' ');
    printf("%s", prompt);
    fflush(stdout);

    // Get input directly without cursor manipulation
    fgets(buffer, size, stdin);
    size_t len = strlen(buffer);
    if (len > 0 && buffer[len - 1] == '\n')
        buffer[len - 1] = '\0';
}

// ===== UI FUNCTIONS =====

// ===== UI FUNCTIONS =====
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

// ===== AUTHENTICATION FUNCTIONS =====

// ===== AUTHENTICATION FUNCTIONS =====
void loginPage()
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

// ===== MENU FUNCTIONS =====

// ===== MENU FUNCTIONS =====
void dashboard()
{
    int choice;

    while (1)
    {
        dashboardDesign();

        // Create menu items array
        const char *menuItems[] = {
            "1. View Events",
            "2. Book Seat",
            "3. Cancel Booking",
            "4. View All Bookings",
            "0. Exit"};

        // Print the menu as a centered block
        printCenteredBlock(menuItems, 5);

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
void adminDashboard()
{
    int choice;
    while (1)
    {
        dashboardDesign();

        // Create admin menu items array
        const char *adminMenuItems[] = {
            "1. View all bookings",
            "2. Add Event",
            "3. View All Events",
            "0. Exit"};

        // Print the admin menu as a centered block
        printCenteredBlock(adminMenuItems, 4);

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

// ===== EVENT FUNCTIONS =====
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
    char events[50][300];         // Store up to 50 events
    char eventMenuItems[51][200]; // Array for menu items (50 events + return option)

    printCentered("-- All Events --");

    while (fgets(line, sizeof(line), file))
    {
        if (sscanf(line, "%99[^|]|%99[^|]|%19[^|]|%19[^|]|%d", name, venue, date, time, &seatCapacity) == 5)
        {
            eventCount++;
            strncpy(events[eventCount - 1], line, sizeof(events[eventCount - 1]) - 1);
            events[eventCount - 1][sizeof(events[eventCount - 1]) - 1] = '\0';
            snprintf(eventMenuItems[eventCount - 1], sizeof(eventMenuItems[eventCount - 1]), "%d. %s", eventCount, name);
        }
    }
    fclose(file);

    // Add return option
    snprintf(eventMenuItems[eventCount], sizeof(eventMenuItems[eventCount]), "%d. Return to admin menu", eventCount + 1);

    // Convert to const char* array for printCenteredBlock
    const char *menuPtrs[51];
    for (int i = 0; i <= eventCount; i++)
    {
        menuPtrs[i] = eventMenuItems[i];
    }

    // Print the event menu as a centered block
    printCenteredBlock(menuPtrs, eventCount + 1);

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

    // Create event details array
    char eventDetails[5][200];
    snprintf(eventDetails[0], sizeof(eventDetails[0]), "Name: %s", name);
    snprintf(eventDetails[1], sizeof(eventDetails[1]), "Venue: %s", venue);
    snprintf(eventDetails[2], sizeof(eventDetails[2]), "Date (DD-MM-YYYY): %s", date);
    snprintf(eventDetails[3], sizeof(eventDetails[3]), "Time: %s", time);
    snprintf(eventDetails[4], sizeof(eventDetails[4]), "Seat Capacity: %d", seatCapacity);

    // Convert to const char* array for printCenteredBlock
    const char *detailsPtrs[5];
    for (int i = 0; i < 5; i++)
    {
        detailsPtrs[i] = eventDetails[i];
    }

    // Print event details as a centered block
    printCenteredBlock(detailsPtrs, 5);

    // Create action menu
    const char *actionMenuItems[] = {
        "1. Edit Event",
        "2. Delete Event",
        "3. Return"};

    // Print action menu as a centered block
    printCenteredBlock(actionMenuItems, 3);
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

    // Create bookings list with header
    char bookingLines[102][200]; // 100 bookings + header + footer
    int lineCount = 0;

    // Add header
    strcpy(bookingLines[lineCount++], "Event ID | Name");
    strcpy(bookingLines[lineCount++], "-------------------");

    char line[200];
    int eventID;
    char name[100];

    while (fgets(line, sizeof(line), file) && lineCount < 100)
    {
        if (sscanf(line, "%d %[^\n]", &eventID, name) == 2)
        {
            snprintf(bookingLines[lineCount], sizeof(bookingLines[lineCount]), "%8d | %s", eventID, name);
            lineCount++;
        }
    }

    // Add footer
    strcpy(bookingLines[lineCount++], "-------------------");
    fclose(file);

    // Convert to const char* array for printCenteredBlock
    const char *bookingPtrs[102];
    for (int i = 0; i < lineCount; i++)
    {
        bookingPtrs[i] = bookingLines[i];
    }

    // Print bookings as a centered block
    printCenteredBlock(bookingPtrs, lineCount);

    // Add prompt to continue
    char continueBuf[10];
    inputCentered("Press Enter to continue...", continueBuf, sizeof(continueBuf));
    clear(); // Clear screen after viewing bookings
}

// Function to show event summary before saving
void showEventSummary(const char *name, const char *venue, const char *date, const char *time, int seatCapacity)
{
    printCentered("=== Event Summary ===");
    printf("\n");

    // Create event details array for centered display
    char eventDetails[5][200];
    snprintf(eventDetails[0], sizeof(eventDetails[0]), "Event Name: %s", name);
    snprintf(eventDetails[1], sizeof(eventDetails[1]), "Venue: %s", venue);
    snprintf(eventDetails[2], sizeof(eventDetails[2]), "Date: %s", date);
    snprintf(eventDetails[3], sizeof(eventDetails[3]), "Time: %s", time);
    snprintf(eventDetails[4], sizeof(eventDetails[4]), "Seat Capacity: %d", seatCapacity);

    // Convert to const char* array for printCenteredBlock
    const char *detailsPtrs[5];
    for (int i = 0; i < 5; i++)
    {
        detailsPtrs[i] = eventDetails[i];
    }

    // Print event details as a centered block
    printCenteredBlock(detailsPtrs, 5);
    printf("\n");
}

// ===== BOOKING FUNCTIONS =====
void addEvent()
{
    char name[100], venue[100], date[20], time[20];
    int seatCapacity;

    printCentered("-- Add New Event --");
    printf("\n"); // Add some spacing

    // Simply collect the inputs with centered prompts - no duplicate display
    inputCentered("Event Name: ", name, sizeof(name));
    inputCentered("Venue: ", venue, sizeof(venue));
    inputCentered("Date (DD-MM-YYYY): ", date, sizeof(date));
    inputCentered("Time (HH:MM): ", time, sizeof(time));

    char buf[16];
    inputCentered("Seat Capacity: ", buf, sizeof(buf));
    if (sscanf(buf, "%d", &seatCapacity) != 1)
    {
        printCentered("Invalid input for seat capacity.");
        return;
    }

    // Show event summary
    clear();
    showEventSummary(name, venue, date, time, seatCapacity);

    // Ask for confirmation
    const char *confirmOptions[] = {
        "1. Save Event",
        "2. Cancel"};
    printCenteredBlock(confirmOptions, 2);

    char choice[10];
    inputCentered("Choose an option (1-2): ", choice, sizeof(choice));

    if (choice[0] == '1')
    {
        FILE *file = fopen("events.txt", "a");
        if (file == NULL)
        {
            printCentered("Error opening events file!");
            return;
        }
        fprintf(file, "%s|%s|%s|%s|%d\n", name, venue, date, time, seatCapacity);
        fclose(file);
        printCentered("Event added successfully!");
    }
    else if (choice[0] == '2')
    {
        printCentered("Event creation cancelled.");
    }
    else
    {
        printCentered("Invalid choice. Event creation cancelled.");
    }

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
    char events[50][300];         // Store up to 50 events
    char eventMenuItems[51][200]; // Array for menu items (50 events + return option)

    printCentered("-- Available Events --");

    while (fgets(line, sizeof(line), file))
    {
        if (sscanf(line, "%99[^|]|%99[^|]|%19[^|]|%19[^|]|%d", name, venue, date, time, &seatCapacity) == 5)
        {
            eventCount++;
            snprintf(events[eventCount - 1], sizeof(events[eventCount - 1]), "%s|%s|%s|%s|%d", name, venue, date, time, seatCapacity);
            snprintf(eventMenuItems[eventCount - 1], sizeof(eventMenuItems[eventCount - 1]), "%d. %s", eventCount, name);
        }
    }
    fclose(file);

    // Add return option
    snprintf(eventMenuItems[eventCount], sizeof(eventMenuItems[eventCount]), "%d. Return to main menu", eventCount + 1);

    // Convert to const char* array for printCenteredBlock
    const char *menuPtrs[51];
    for (int i = 0; i <= eventCount; i++)
    {
        menuPtrs[i] = eventMenuItems[i];
    }

    // Print the event menu as a centered block
    printCenteredBlock(menuPtrs, eventCount + 1);

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

    // Create event details array
    char eventDetails[5][200];
    snprintf(eventDetails[0], sizeof(eventDetails[0]), "Name: %s", name);
    snprintf(eventDetails[1], sizeof(eventDetails[1]), "Venue: %s", venue);
    snprintf(eventDetails[2], sizeof(eventDetails[2]), "Date (DD-MM-YYYY): %s", date);
    snprintf(eventDetails[3], sizeof(eventDetails[3]), "Time: %s", time);
    snprintf(eventDetails[4], sizeof(eventDetails[4]), "Seat Capacity: %d", seatCapacity);

    // Convert to const char* array for printCenteredBlock
    const char *detailsPtrs[5];
    for (int i = 0; i < 5; i++)
    {
        detailsPtrs[i] = eventDetails[i];
    }

    // Print event details as a centered block
    printCenteredBlock(detailsPtrs, 5);

    // Add prompt to continue
    char continueBuf[10];
    inputCentered("Press Enter to continue...", continueBuf, sizeof(continueBuf));
    clear(); // Clear screen after viewing event details
}

// ===== BOOKING FUNCTIONS =====
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
