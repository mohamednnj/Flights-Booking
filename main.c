#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_LEN 100

typedef struct {
    int id;
    char destination[30];
    char departure[20];
    int seats;
} Flight;

typedef struct {
    int id;
    char email[50];
    int flight_id;
} Booking;
// Function Prototypes
int login();
void registerUser();
void userMenu(char email[]);
void loadFlights();
void saveFlights();
void viewFlights();
void bookFlight(char email[]);
void viewBookings(char email[]);
void cancelBooking(char email[]);

// Global
Flight flights[50];
int flight_count = 0;

void pressEnter() {
    printf("\nPress Enter to continue...");
    getchar();
}

void loadFlightsTest() {
    flight_count = 3;
    flights[0] = (Flight){1, "London", "08:00", 30};
    flights[1] = (Flight){2, "Paris", "14:00", 25};
    flights[2] = (Flight){3, "Tokyo", "22:00", 20};
}

// Load Flights from file
void loadFlights() {
    FILE *f = fopen("flights.txt", "r");
    if (!f) {
        perror("Error opening flights.txt");
        return;
    }

    flight_count = 0;
    while (fscanf(f, "%d %s %s %d", &flights[flight_count].id,
                  flights[flight_count].destination,
                  flights[flight_count].departure,
                  &flights[flight_count].seats) == 4) {
        flight_count++;
                  }

    fclose(f);
}
// Save Flights to file
void saveFlights() {
    FILE *f = fopen("./flights.txt", "w");
    for (int i = 0; i < flight_count; i++) {
        fprintf(f, "%d %s %s %d\n", flights[i].id,
                flights[i].destination,
                flights[i].departure,
                flights[i].seats);
    }
    fclose(f);
}

// Register a new user
void registerUser() {
    char email[50], password[50];
    printf("Enter new email: ");
    scanf("%s", email);
    printf("Enter password: ");
    scanf("%s", password);

    FILE *f = fopen("users.txt", "a");
    if (!f) {
        printf("Error: Could not open user file.\n");
        return;
    }
    fprintf(f, "%s %s\n", email, password);
    fclose(f);
    printf("Account created successfully!\n");
}

// Login function
int login() {
    char email[50], password[50], line[MAX_LEN];
    char file_email[50], file_pass[50];

    printf("Enter email: ");
    scanf("%s", email);
    printf("Enter password: ");
    scanf("%s", password);

    FILE *f = fopen("users.txt", "r");
    if (!f) {
        printf("User file not found.\n");
        return 0;
    }

    while (fgets(line, sizeof(line), f)) {
        sscanf(line, "%s %s", file_email, file_pass);
        if (strcmp(file_email, email) == 0 && strcmp(file_pass, password) == 0) {
            fclose(f);
            printf("Login successful. Welcome %s!\n", email);
            userMenu(email); // Calls the user menu on successful login
            return 1;
        }
    }

    fclose(f);
    printf("Invalid email or password.\n");
    return 0;
}
// View available flights
void viewFlights() {
    if (flight_count == 0) {
        printf("\nNo flights available.\n");
        return;
    }

    printf("\n--- Available Flights ---\n");
    for (int i = 0; i < flight_count; i++) {
        printf("ID: %d | To: %s | Time: %s | Seats: %d\n",
               flights[i].id,
               flights[i].destination,
               flights[i].departure,
               flights[i].seats);
    }
}
// Book a flight
void bookFlight(char email[]) {
    int id;
    viewFlights();
    printf("Enter Flight ID to book: ");
    scanf("%d", &id);

    for (int i = 0; i < flight_count; i++) {
        if (flights[i].id == id && flights[i].seats > 0) {
            FILE *f = fopen("bookings.txt", "a");
            int booking_id = rand() % 10000;
            fprintf(f, "%d %s %d\n", booking_id, email, id);
            fclose(f);

            flights[i].seats--;
            saveFlights();
            printf("Booking confirmed! Booking ID: %d\n", booking_id);
            return;
        }
    }

    printf("Flight not found or no seats available.\n");
}

// View user's bookings
void viewBookings(char email[]) {
    FILE *f = fopen("bookings.txt", "r");
    if (!f) {
        printf("No bookings found.\n");
        return;
    }

    int id, flight_id, found = 0;
    char user[50];

    printf("\n--- Your Bookings ---\n");
    while (fscanf(f, "%d %s %d", &id, user, &flight_id) == 3) {
        if (strcmp(user, email) == 0) {
            printf("Booking ID: %d | Flight ID: %d\n", id, flight_id);
            found = 1;
        }
    }

    fclose(f);
    if (!found)
        printf("You have no bookings.\n");
}

// Cancel a booking
void cancelBooking(char email[]) {
    int id;
    printf("Enter Booking ID to cancel: ");
    scanf("%d", &id);

    FILE *f = fopen("bookings.txt", "r");
    FILE *temp = fopen("temp.txt", "w");

    int b_id, flight_id, found = 0;
    char user[50];

    while (fscanf(f, "%d %s %d", &b_id, user, &flight_id) == 3) {
        if (b_id == id && strcmp(user, email) == 0) {
            found = 1;
            for (int i = 0; i < flight_count; i++) {
                if (flights[i].id == flight_id) {
                    flights[i].seats++;
                    break;
                }
            }
        } else {
            fprintf(temp, "%d %s %d\n", b_id, user, flight_id);
        }
    }

    fclose(f);
    fclose(temp);
    remove("bookings.txt");
    rename("temp.txt", "bookings.txt");
    saveFlights();

    if (found)
        printf("Booking canceled.\n");
    else
        printf("Booking ID not found.\n");
}

// User Menu
void userMenu(char email[]) {
    int choice;
    loadFlights();

    do {
        printf("\n--- Menu ---\n");
        printf("1. View Flights\n");
        printf("2. Book Flight\n");
        printf("3. View My Bookings\n");
        printf("4. Cancel Booking\n");
        printf("5. Logout\n");
        printf("Enter choice: ");
        scanf("%d", &choice);
        getchar(); // clear buffer

        switch (choice) {
            case 1: viewFlights(); break;
            case 2: bookFlight(email); break;
            case 3: viewBookings(email); break;
            case 4: cancelBooking(email); break;
            case 5: printf("Logged out.\n"); break;
            default: printf("Invalid choice.\n");
        }
    } while (choice != 5);
}

// Main Program
int main() {
    int choice;
    do {
        printf("\n--- Flight Booking System ---\n");
        printf("1. Login\n");
        printf("2. Register\n");
        printf("3. Exit\n");
        printf("Enter choice: ");
        scanf("%d", &choice);
        getchar(); // buffer clear

        switch (choice) {
            case 1: login(); break;
            case 2: registerUser(); break;
            case 3: printf("Exiting program.\n"); break;
            default: printf("Invalid choice.\n");
        }
    } while (choice != 3);

    return 0;
}