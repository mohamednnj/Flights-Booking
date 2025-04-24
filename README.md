# Project Title: Flight Booking System
## Table of Contents
1. [Project Overview](#project-overview)
2. [Features](#features)
3. [Setup Instructions](#setup-instructions)
4. [How to Run](#how-to-run)
5. [Function Descriptions](#function-descriptions)
6. [Flowchart](#flowchart)

## Project Overview
The **Flight Booking System** is a C-based application that allows users to search for available flights, book tickets, view bookings, and cancel bookings. It also includes a basic user registration and login feature to ensure secure usage. All information about flights and bookings is managed within the application.
## Features
- User Registration and Login.
- View available flights.
- Book a flight.
- View previously booked flights.
- Cancel bookings.
- Persistent data storage for flights and bookings.

## Setup Instructions
To set up and run the project locally:
1. Clone the repository:
``` bash
   git clone <repository_url>
```
1. Navigate to the project directory:
``` bash
   cd untitled
```
1. Open the folder in an IDE of your choice (e.g., CLion).
2. Ensure that you have a C compiler (GCC recommended).

## How to Run
### Compiling the Project:
Compile the project using the terminal:
``` bash
gcc -o FlightBookingSystem main.c
```
### Running the Program:
Run the compiled program using the command:
``` bash
./FlightBookingSystem
```
### Steps:
1. The system will prompt you to **Log in** or **Register**.
2. Once logged in, you'll access a user menu for various operations:
    - View Flights
    - Book a Flight
    - View Your Bookings
    - Cancel a Booking
    - Exit

## Function Descriptions
### Functions Overview:
Below is the list of functions along with their descriptions:
1. **int login():**
    - Allows the user to log in with their email and password.
    - If the credentials are incorrect, it denies access.

2. **void registerUser():**
    - Registers a new user by taking input (e.g., email and password).
    - Stores the user data for future logins.

3. **void userMenu(char email[]):**
    - Displays the main menu for logged-in users.
    - Calls appropriate functions based on user selection.

4. **void loadFlights():**
    - Loads available flights from a file into memory for users to browse.

5. **void saveFlights():**
    - Saves any changes to flights into a file (persistent storage).

6. **void viewFlights():**
    - Displays a list of available flights.

7. **void bookFlight(char email[]):**
    - Allows a user to book a flight by entering details.
    - Stores the booking under the user's profile.

8. **void viewBookings(char email[]):**
    - Displays all flights booked by the logged-in user.

9. **void cancelBooking(char email[]):**
    - Allows the user to cancel a specific booking by providing details.

10. **void pressEnter():**
    - Utility function prompting the user to press Enter to continue.

11. **void loadFlightsTest():**
    - A test function used for loading flights (for purposes like debugging or testing).

## Flowchart
### Overview of the Application's Workflow:
Below is a flowchart describing how the system operates:
``` plaintext
          Start
            |
           Menu
            |
    [Log In] [Register]
          |
        User Menu
            |
    ---------------------------------
   |       |       |       |       |
 View   Book  View Book  Cancel    Exit
Flights Flight Bookings  Booking 
```
### Textual Steps:
1. Start the program.
2. The user logs in or registers to access the system.
3. The user is taken to the main menu.
4. From the menu, the user can:
    - View flights.
    - Book a flight.
    - View previously booked flights.
    - Cancel a booking.
    - Exit the program.

Feel free to expand or contact me for any changes or clarifications! 😊
