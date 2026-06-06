// HOTEL BOOKING SYSTEM
// Mini Project - Practical Programming in C

#include <stdio.h>
#include <string.h>

// MACROs
#define MAX_ROOMS 10 // Total rooms in the hotel
#define MAX_NAME 50  // Max characters in a guest name

// STRUCTURE TO REPRESENT A HOTEL ROOM
struct Room
{
    int room_number;           // unique room number
    char type[10];             // "Single", "Double", "Suite"
    float price_per_night;     // Price in rupees
    int is_booked;             // 0 = available, 1 = booked
    char guest_name[MAX_NAME]; // Name of the guest (if booked)
    int nights;                // Number of nights booked
};

// GLOBAL ARRAY OF STRUCTURES
struct Room hotel[MAX_ROOMS];

// FUNCTIONS
void initialize_rooms();
void view_all_rooms();
void book_room();
void checkout_room();
void view_available_rooms();
float calculate_bill(int index);

/* ================================================================
 *                           MAIN FUNCTION
 * ================================================================ */
int main()
{
    int choice = 0;

    initialize_rooms();

    printf("\n  Welcome to Hotel SKYHIGH Inn \n");

    do
    {
        // display menu
        printf("\n");
        printf("  ============================================\n");
        printf("          HOTEL SKYHIGH INN - MAIN MENU       \n");
        printf("  ============================================\n");
        printf("  1. View All Rooms\n");
        printf("  2. View Available Rooms\n");
        printf("  3. Book a Room\n");
        printf("  4. Check Out\n");
        printf("  5. Exit\n");
        printf("  ========================================\n");
        printf("  Enter your choice: ");
        scanf("%d", &choice);

        switch (choice)
        {
        case 1:
            view_all_rooms();
            break;
        case 2:
            view_available_rooms();
            break;
        case 3:
            book_room();
            break;
        case 4:
            checkout_room();
            break;
        case 5:
            printf("\n  Thank you for using Hotel SKYHIGH Inn! Goodbye!\n\n");
            break;
        default:
            printf("\n  Invalid choice! Please enter 1-5.\n");
        }

    } while (choice != 5);

    return 0;
}

// FUNCTION DEFINITIONS

void initialize_rooms()
{
    int i;

    for (i = 0; i < MAX_ROOMS; i++)
    {
        hotel[i].room_number = 101 + i; // ROOM NOS. 101, 102, ... 110
        hotel[i].is_booked = 0;         // all rooms start as available
        hotel[i].nights = 0;
        strcpy(hotel[i].guest_name, "");

        // Assign room type and price based on room number (101-104: Single, 105-108: Double, 109,110: Suite)
        if (i < 4)
        {
            strcpy(hotel[i].type, "Single");
            hotel[i].price_per_night = 1500.0;
        }
        else if (i < 8)
        {
            strcpy(hotel[i].type, "Double");
            hotel[i].price_per_night = 2500.0;
        }
        else
        {
            strcpy(hotel[i].type, "Suite");
            hotel[i].price_per_night = 5000.0;
        }
    }
}

void view_all_rooms()
{
    int i;

    printf("\n  ============================================================\n");
    printf("  Room No. |   Type   | Price/Night |   Status   | Guest Name | Nights\n");
    printf("  ============================================================\n");

    for (i = 0; i < MAX_ROOMS; i++)
    {
        printf("    %d   | %-8s |  Rs. %.2f | ",
               hotel[i].room_number,
               hotel[i].type,
               hotel[i].price_per_night);

        /* if-else to print status */
        if (hotel[i].is_booked == 0)
        {
            printf("Available | -  | -\n");
        }
        else
        {
            printf(" Booked   | %s | %d \n",
                   hotel[i].guest_name,
                   hotel[i].nights);
        }
    }

    printf("  ============================================================\n");
}

void view_available_rooms()
{
    int i;
    int found = 0; // flag to check if any room is available

    printf("\n  --- Available Rooms ---\n");
    printf("  Room No. |   Type   | Price per Night\n");
    printf("  -----------------------------------------\n");

    for (i = 0; i < MAX_ROOMS; i++)
    {
        if (hotel[i].is_booked == 0)
        {
            printf("    %d   | %s |  Rs. %.2f\n",
                   hotel[i].room_number,
                   hotel[i].type,
                   hotel[i].price_per_night);
            found = 1;
        }
    }

    if (found == 0)
    {
        printf("  Sorry! No rooms are available right now.\n");
    }

    printf("  -----------------------------------------\n");
}

void book_room()
{
    int room_no, i, index = -1;
    char name[MAX_NAME];
    int nights;

    view_available_rooms();

    printf("\n  Enter Room Number to book: ");
    scanf("%d", &room_no);

    // Search for the room in our hotel array
    for (i = 0; i < MAX_ROOMS; i++)
    {
        if (hotel[i].room_number == room_no)
        {
            index = i;
            break;
        }
    }

    // Check if room number is valid
    if (index == -1)
    {
        printf("\n  Room number %d does not exist!\n", room_no);
        return;
    }

    // Check if room is already booked
    if (hotel[index].is_booked == 1)
    {
        printf("\n  Sorry! Room %d is already booked.\n", room_no);
        return;
    }

    // Get guest details
    printf(" Enter Guest Name : ");
    scanf(" %[^\n]", name);

    printf("  Enter Number of Nights: ");
    scanf("%d", &nights);

    if (nights <= 0)
    {
        printf("\n  Invalid number of nights!\n");
        return;
    }

    // Save booking details into the structure and mark room as booked
    hotel[index].is_booked = 1;
    hotel[index].nights = nights;
    strcpy(hotel[index].guest_name, name);

    /* Show confirmation */
    printf("\n  ==============================\n");
    printf("     BOOKING CONFIRMED!\n");
    printf("  ==============================\n");
    printf("  Room Number : %d\n", hotel[index].room_number);
    printf("  Room Type   : %s\n", hotel[index].type);
    printf("  Guest Name  : %s\n", hotel[index].guest_name);
    printf("  Nights      : %d\n", hotel[index].nights);
    printf("  Total Bill  : Rs. %.2f\n", calculate_bill(index));
    printf("  ==============================\n");
}

void checkout_room()
{
    int room_no, i, index = -1;

    printf("\n  Enter Room Number to Check Out: ");
    scanf("%d", &room_no);

    // Search for the room in our hotel array
    for (i = 0; i < MAX_ROOMS; i++)
    {
        if (hotel[i].room_number == room_no)
        {
            index = i;
            break;
        }
    }

    // Check if room number is valid
    if (index == -1)
    {
        printf("\n  Room %d does not exist!\n", room_no);
        return;
    }

    // Check if the room is actually booked
    if (hotel[index].is_booked == 0)
    {
        printf("\n  Room %d is not currently booked!\n", room_no);
        return;
    }

    // Show bill before checkout
    printf("\n  ==============================\n");
    printf("     CHECKOUT SUMMARY\n");
    printf("  ==============================\n");
    printf("  Room Number : %d\n", hotel[index].room_number);
    printf("  Guest Name  : %s\n", hotel[index].guest_name);
    printf("  Room Type   : %s\n", hotel[index].type);
    printf("  Nights      : %d\n", hotel[index].nights);
    printf("  Total Bill  : Rs. %.2f\n", calculate_bill(index));
    printf("  ==============================\n");

    // Reset room details to make it available again
    hotel[index].is_booked = 0;
    hotel[index].nights = 0;
    strcpy(hotel[index].guest_name, "");

    printf("  Room %d is now available again.\n", room_no);
    printf("  Thank you, %s! We hope to see you again!\n",
           hotel[index].guest_name[0] == '\0' ? "Guest" : hotel[index].guest_name);
}

float calculate_bill(int index)
{
    return hotel[index].price_per_night * hotel[index].nights;
}