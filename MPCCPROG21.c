/*
*********************************************************************************************************
This is to certify that this project is my own work, based on my personal efforts in studying and applying the concepts
learned.  I have constructed the functions and their respective algorithms and corresponding code by myself.  The
program was run, tested, and debugged by my own efforts.  I further certify that I have not copied in part or whole or
otherwise plagiarized the work of other students and/or persons.
                                                                                                                 John Raphael Pineda, DLSU ID# <number>
														 Fritz Ian B. Fernandez, 12410764
*********************************************************************************************************
*/

#include <stdio.h>
#include <string.h>

#define MAX_PASSENGERS 16
#define MAX_TRIPS 20
#define NAME_LENGTH 50
#define TRIP_CODE_LENGTH 10

// Passenger structure
typedef struct {
    char tripNumber[TRIP_CODE_LENGTH];
    char name[NAME_LENGTH];
    char idNumber[15];
    char dropOffPoint[50];
    int priority;
} Passenger;

// Shuttle structure
typedef struct {
    char tripNumber[TRIP_CODE_LENGTH];
    char embarkationPoint[50];
    int passengerCount;
    Passenger passengers[MAX_PASSENGERS];
    int dropOffCount[4];
} Shuttle;

// Function Prototypes
void encodePassenger(Shuttle trips[], int *tripCount);
void viewPassengerCount(Shuttle trips[], int tripCount);
void viewDropOffCount(Shuttle trips[], int tripCount);
void viewPassengerInfo(Shuttle trips[], int tripCount);
void loadPassengerFromFile(Shuttle trips[], int tripCount);
void searchPassenger(Shuttle trips[], int tripCount);
void saveTripsToFile(Shuttle trips[], int tripCount);
void loadRecentTripFile();
void initializeTrips(Shuttle trips[], int *tripCount);
int findTripIndex(Shuttle trips[], int tripCount, char tripNumber[]);
void exitProgram(Shuttle trips[], int tripCount);
void displayMenu();

// Main Function
int main() {
    Shuttle trips[MAX_TRIPS];
    int tripCount = 0;
    int userType = 0;
    int choice;
    char date[11]; 
    initializeTrips(trips, &tripCount);
    printf("Input the current date (mm/dd/yy):");
    scanf("%s", date);
    
    do {
        printf("\n--- User Type Selection ---\n");
        printf("1. Passenger\n");
        printf("2. Arrows Express Personnel\n");
        printf("3. Exit Program (End of Day)\n");
        printf("User type: ");
        scanf("%d", &userType);

    while(userType == 1 || userType == 2){
        displayMenu(userType);
        printf("Enter your choice: ");
        scanf("%d", &choice);
        
        switch(choice){
        case 1:
        if(userType == 1){
            encodePassenger(trips, &tripCount);
            printf("need to apply special shuttle system\n\n");
        }
        if(userType == 2){
            viewPassengerCount(trips, tripCount);
            printf("\n");
        }break;
        case 2:
        if(userType == 1){
            userType = 0;
        }
        if(userType == 2){
            viewDropOffCount(trips, tripCount);
            printf("\n");
        }break;
        case 3:
        if(userType == 2){
            viewPassengerInfo(trips, tripCount);
        }break;
        case 4:
        if(userType == 2){
            loadPassengerFromFile(trips, tripCount);
        }break;
        case 5:
        if(userType == 2){
            searchPassenger(trips, tripCount);
            printf("WIP Search passenger\n");
        }break;
        case 6:
        if(userType == 2){
            loadRecentTripFile();
            printf("WIP Load recent trip file for viewing\n");
        }break;
        case 7:
        if(userType == 2){
            userType = 0;
        }break;

    }
    }
}while(userType != 3);

	//saveTripsToFile(trips, tripCount);

    return 0;
}

void initializeTrips(Shuttle trips[], int *tripCount) {
    FILE *trip;
    int i = 0;
    trip = fopen("Tripnumber.txt", "r");
    if (trip == NULL) {
        printf("Error: Could not open Tripnumber.txt\n");
        *tripCount = 0;
    }

    while (i < MAX_TRIPS && fscanf(trip, "%s", trips[i].tripNumber) == 1) {
        i++;
    }

    *tripCount = i; // Update the trip count
    fclose(trip); // Close the file
}

// Function Definitions
void displayMenu(int userType) {
    if(userType == 1){
        printf("1 - Encode Passenger Information\n");
        printf("2 - Back to Main Menu\n");
        }
        if(userType == 2){
        printf("1 - View Passenger Count\n");
        printf("2 - View Drop-off Count\n");
        printf("3 - View Passenger Information\n");
        printf("4 - Load Passenger(Single passenger)\n");
        printf("5 - Search Passenger\n");
        printf("6 - Load Recent Trip File for Viewing\n");
        printf("7 - Back to Main Menu\n");
        }
}

void encodePassenger(Shuttle trips[], int *tripCount) {
    char tripNumber[TRIP_CODE_LENGTH];
    int index, choice;

    printf("Enter trip number: ");
    scanf("%s", tripNumber);
    index = findTripIndex(trips, *tripCount, tripNumber);

    while (index == -1) {
        printf("Trip not found! \nEnter a valid trip number: ");
        scanf("%s", tripNumber);
        index = findTripIndex(trips, *tripCount, tripNumber);
    }

    while (trips[index].passengerCount >= MAX_PASSENGERS) {
        printf("Trip is full! Enter a different trip number: ");
        scanf("%s", tripNumber);
        index = findTripIndex(trips, *tripCount, tripNumber);
    }

    Passenger newPassenger;
    strcpy(newPassenger.tripNumber, tripNumber); // Store trip number

    printf("Enter passenger name: ");
    scanf(" %[^\n]", newPassenger.name);

    printf("Enter passenger ID: ");
    scanf("%14s", newPassenger.idNumber);

    do {
        printf("Enter priority (1-6): ");
        scanf("%d", &newPassenger.priority);
        if (newPassenger.priority < 1 || newPassenger.priority > 6) {
            printf("Invalid priority! Please enter a number between 1 and 6.\n");
        }
    } while (newPassenger.priority < 1 || newPassenger.priority > 6);

    // Display correct drop-off points based on index
    printf("Available drop-off points:\n");

    if (index >= 0 && index <= 4) {
        printf("1.) Mamplasan Toll Exit\n");
        printf("2.) Phase 5, San Jose Village\n");
        printf("3.) Milagros Del Rosario (MRR) Building East Canopy\n");
    } else if (index >= 5 && index <= 8) {
        printf("1.) Laguna Blvd. Guard House\n");
        printf("2.) Milagros Del Rosario (MRR) Building East Canopy\n");
    } else if (index >= 10 && index <= 14) {
        printf("1.) Petron Gasoline Station Along Gil Puyat Avenue\n");
        printf("2.) Gate 4: Gokongwei Gate\n");
        printf("3.) Gate 2: North Gate (HSSH)\n");
        printf("4.) Gate 1: South Gate (LS Building Entrance)\n");
    } else if (index >= 16 && index <= 21) {
        printf("1.) College of St. Benilde (CSB) along Taft Avenue\n");
        printf("2.) Gate 4: Gokongwei Gate\n");
        printf("3.) Gate 2: North Gate (HSSH)\n");
        printf("4.) Gate 1: South Gate (LS Building Entrance)\n");
    } else {
        printf("No valid drop-off points available for this trip.\n");
        return;
    }

    // Ask user to select a drop-off point
    do {
        printf("Choose a drop-off point: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                if (index >= 0 && index <= 4){
                    strcpy(newPassenger.dropOffPoint, "Mamplasan Toll Exit");          
                    trips[index].dropOffCount[0]++;  
                }
                else if (index >= 5 && index <= 9){
                    strcpy(newPassenger.dropOffPoint, "Laguna Blvd. Guard House");
                    trips[index].dropOffCount[0]++;
                }
                else if (index >= 10 && index <= 15){
                    strcpy(newPassenger.dropOffPoint, "Petron Gasoline Station Along Gil Puyat Avenue");
                    trips[index].dropOffCount[0]++;
                } 
                else if (index >= 16 && index <= 21){
                    strcpy(newPassenger.dropOffPoint, "College of St. Benilde (CSB) along Taft Avenue");
                    trips[index].dropOffCount[0]++;
                }
                break;
            case 2:
                if (index >= 0 && index <= 4){
                    strcpy(newPassenger.dropOffPoint, "Phase 5, San Jose Village");
                    trips[index].dropOffCount[1]++;
                }
                else if (index >= 5 && index <= 9){
                    strcpy(newPassenger.dropOffPoint, "Milagros Del Rosario (MRR) Building East Canopy");
                    trips[index].dropOffCount[1]++;
                }
                else if (index >= 10 && index <= 15){
                    strcpy(newPassenger.dropOffPoint, "Gate 4: Gokongwei Gate");
                    trips[index].dropOffCount[1]++;
                }
                else if (index >= 16 && index <= 21){
                    strcpy(newPassenger.dropOffPoint, "Gate 4: Gokongwei Gate");
                    trips[index].dropOffCount[1]++;
                }
                break;
            case 3:
                if (index >= 0 && index <= 4){
                    strcpy(newPassenger.dropOffPoint, "Milagros Del Rosario (MRR) Building East Canopy");
                    trips[index].dropOffCount[2]++;
                }
                else if (index >= 10 && index <= 15){
                    strcpy(newPassenger.dropOffPoint, "Gate 2: North Gate (HSSH)");
                    trips[index].dropOffCount[2]++;
                }
                else if (index >= 16 && index <= 21){
                    strcpy(newPassenger.dropOffPoint, "Gate 2: North Gate (HSSH)");
                    trips[index].dropOffCount[2]++;
                }
                else choice = 0; // Invalid choice
                break;
            case 4:
                if (index >= 10 && index <= 15){
                    strcpy(newPassenger.dropOffPoint, "Gate 1: South Gate (LS Building Entrance)");
                    trips[index].dropOffCount[3]++;
                }
                else if (index >= 16 && index <= 21){
                strcpy(newPassenger.dropOffPoint, "Gate 1: South Gate (LS Building Entrance)");
                trips[index].dropOffCount[3]++;
                }
                else choice = 0; // Invalid choice
                break;
            default:
                printf("Invalid choice! Please choose a valid drop-off point.\n");
                choice = 0;
        }
    } while (choice == 0);

    trips[index].passengers[trips[index].passengerCount] = newPassenger;
    trips[index].passengerCount++;
    printf("Passenger added successfully!\n");
}



void viewDropOffCount(Shuttle trips[], int tripCount) {
    char tripNumber[10];
    int index = -1;
    int i;

    while (index == -1) {
        printf("Enter trip number: ");
        scanf("%s", tripNumber);
        index = findTripIndex(trips, tripCount, tripNumber);
        if (index == -1) {
            printf("Trip not found! Please enter a valid trip number.\n");
        }
    }

    printf("Drop-off counts for trip %s:\n", tripNumber);
    for (i = 0; i < 4; i++) {
        if(index >= 0)
        printf("Drop-off point %d: %d passengers\n", i + 1, trips[index].dropOffCount[i]);
    }
}


void viewPassengerInfo(Shuttle trips[], int tripCount) {
    char tripNumber[TRIP_CODE_LENGTH];
    int i, j;
    int found = 0;  // Flag to track if trip was found

    printf("Enter trip number: ");
    scanf("%s", tripNumber);

    for (i = 0; i < tripCount && !found; i++) {
        if (strcmp(trips[i].tripNumber, tripNumber) == 0) {
            printf("Passengers for trip %s:\n", tripNumber);
            for (j = 0; j < trips[i].passengerCount; j++) {
                printf("%s - ID: %s - Priority: %d\n", 
                      trips[i].passengers[j].name, 
                      trips[i].passengers[j].idNumber, 
                      trips[i].passengers[j].priority);
            }
            found = 1;  // Set flag to indicate trip was found
        }
    }

    if (!found) {
        printf("Trip not found.\n");
    }
}

/*
void loadPassengerFromFile(Shuttle trips[], int tripCount) {
    FILE *file = fopen("trip.txt", "r");
    Passenger p;
    //int i;
    int index;
    int choice;
    if (!file) {
        printf("Error opening file.\n");
        return;
    }
    fscanf(file, "%s %s %s %d %d", p.tripNumber, p.name, p.idNumber, &p.priority, &choice);
        index = findTripIndex(trips, tripCount, p.tripNumber); //index is always returning 0 for some reason
        switch (choice) {
            case 1:
                if (index >= 0 && index <= 4){
                    strcpy(p.dropOffPoint, "Mamplasan Toll Exit");          
                    trips[index].dropOffCount[0]++;  
                }
                else if (index >= 5 && index <= 9){
                    strcpy(p.dropOffPoint, "Laguna Blvd. Guard House");
                    trips[index].dropOffCount[0]++;
                }
                else if (index >= 10 && index <= 15){
                    strcpy(p.dropOffPoint, "Petron Gasoline Station Along Gil Puyat Avenue");
                    trips[index].dropOffCount[0]++;
                } 
                else if (index >= 16 && index <= 21){
                    strcpy(p.dropOffPoint, "College of St. Benilde (CSB) along Taft Avenue");
                    trips[index].dropOffCount[0]++;
                }
                break;
            case 2:
                if (index >= 0 && index <= 4){
                    strcpy(p.dropOffPoint, "Phase 5, San Jose Village");
                    trips[index].dropOffCount[1]++;
                }
                else if (index >= 5 && index <= 9){
                    strcpy(p.dropOffPoint, "Milagros Del Rosario (MRR) Building East Canopy");
                    trips[index].dropOffCount[1]++;
                }
                else if (index >= 10 && index <= 15){
                    strcpy(p.dropOffPoint, "Gate 4: Gokongwei Gate");
                    trips[index].dropOffCount[1]++;
                }
                else if (index >= 16 && index <= 21){
                    strcpy(p.dropOffPoint, "Gate 4: Gokongwei Gate");
                    trips[index].dropOffCount[1]++;
                }
                break;
            case 3:
                if (index >= 0 && index <= 4){
                    strcpy(p.dropOffPoint, "Milagros Del Rosario (MRR) Building East Canopy");
                    trips[index].dropOffCount[2]++;
                }
                else if (index >= 10 && index <= 15){
                    strcpy(p.dropOffPoint, "Gate 2: North Gate (HSSH)");
                    trips[index].dropOffCount[2]++;
                }
                else if (index >= 16 && index <= 21){
                    strcpy(p.dropOffPoint, "Gate 2: North Gate (HSSH)");
                    trips[index].dropOffCount[2]++;
                }
                else choice = 0; // Invalid choice
                break;
            case 4:
                if (index >= 10 && index <= 15){
                    strcpy(p.dropOffPoint, "Gate 1: South Gate (LS Building Entrance)");
                    trips[index].dropOffCount[3]++;
                }
                else if (index >= 16 && index <= 21){
                strcpy(p.dropOffPoint, "Gate 1: South Gate (LS Building Entrance)");
                trips[index].dropOffCount[3]++;
                }
                else choice = 0; // Invalid choice
                break;
        }
    fclose(file);
    printf("Passenger loaded successfully!\n");
    printf("%d\n", index);
}

*/
void loadPassengerFromFile(Shuttle trips[], int tripCount) {
    FILE *file = fopen("trip.txt", "r");
    if (file) {
        Passenger p;
        int index, choice;

        while (fscanf(file, "%s %s %s %d %d", p.tripNumber, p.name, p.idNumber, &p.priority, &choice) == 5) {
            printf("Read from file: TripNumber = %s, Name = %s, ID = %s, Priority = %d, Choice = %d\n", 
                p.tripNumber, p.name, p.idNumber, p.priority, choice);

            index = findTripIndex(trips, tripCount, p.tripNumber);
            printf("Trip index found: %d\n", index);  // Debugging output

            if (index != -1) {
                // Process drop-off selection
                switch (choice) {
                    case 1:
                        if (index >= 0 && index <= 4) {
                            strcpy(p.dropOffPoint, "Mamplasan Toll Exit");
                            trips[index].dropOffCount[0]++;
                        } else if (index >= 5 && index <= 9) {
                            strcpy(p.dropOffPoint, "Laguna Blvd. Guard House");
                            trips[index].dropOffCount[0]++;
                        } else if (index >= 10 && index <= 15) {
                            strcpy(p.dropOffPoint, "Petron Gasoline Station Along Gil Puyat Avenue");
                            trips[index].dropOffCount[0]++;
                        } else if (index >= 16 && index <= 21) {
                            strcpy(p.dropOffPoint, "College of St. Benilde (CSB) along Taft Avenue");
                            trips[index].dropOffCount[0]++;
                        }
                        break;
                    case 2:
                        if (index >= 0 && index <= 4) {
                            strcpy(p.dropOffPoint, "Phase 5, San Jose Village");
                            trips[index].dropOffCount[1]++;
                        } else if (index >= 5 && index <= 9) {
                            strcpy(p.dropOffPoint, "Milagros Del Rosario (MRR) Building East Canopy");
                            trips[index].dropOffCount[1]++;
                        } else if (index >= 10 && index <= 21) {
                            strcpy(p.dropOffPoint, "Gate 4: Gokongwei Gate");
                            trips[index].dropOffCount[1]++;
                        }
                        break;
                    case 3:
                        if (index >= 0 && index <= 4) {
                            strcpy(p.dropOffPoint, "Milagros Del Rosario (MRR) Building East Canopy");
                            trips[index].dropOffCount[2]++;
                        } else if (index >= 10 && index <= 21) {
                            strcpy(p.dropOffPoint, "Gate 2: North Gate (HSSH)");
                            trips[index].dropOffCount[2]++;
                        }
                        break;
                    case 4:
                        if (index >= 10 && index <= 21) {
                            strcpy(p.dropOffPoint, "Gate 1: South Gate (LS Building Entrance)");
                            trips[index].dropOffCount[3]++;
                        }
                        break;
                    default:
                        printf("Invalid drop-off choice for passenger %s.\n", p.name);
                }
                printf("Passenger %s added to trip %s at drop-off point: %s\n", p.name, p.tripNumber, p.dropOffPoint);
            } else {
                printf("Trip %s not found.\n", p.tripNumber);
            }
        }
        fclose(file);
        printf("Passenger loaded successfully.\n");
    } else {
        printf("Error opening file.\n");
    }
}

/*
void searchPassenger(Shuttle trips[], int tripCount) {
    char lastName[NAME_LENGTH];
    int i, j, found = 0;

    printf("Enter last name to search: ");
    scanf("%s", lastName);

    for (i = 0; i < tripCount; i++) {
        for (j = 0; j < trips[i].passengerCount; j++) {
            if (strstr(trips[i].passengers[j].name, lastName)) {
                printf("%s - Trip: %s - ID: %s - Priority: %d\n", trips[i].passengers[j].name, trips[i].tripNumber, trips[i].passengers[j].idNumber, trips[i].passengers[j].priority);
                found = 1;
            }
        }
    }
    if (!found) {
        printf("Passenger not found.\n");
    }
}
*/

void searchPassenger(Shuttle trips[], int tripCount) {
    char lastName[NAME_LENGTH];
    int i, j, k, found = 0;

    printf("Enter last name to search: ");
    scanf(" %s", lastName);  // Space before %s to handle buffer issues

    for (i = 0; i < tripCount; i++) {
        for (j = 0; j < trips[i].passengerCount; j++) {
            // Extract last name (Find last space without consecutive while loops)
            char *passengerName = trips[i].passengers[j].name;
            char *lastNamePtr = passengerName;  // Default to full name

            for (k = 0; passengerName[k] != '\0'; k++) {
                if (passengerName[k] == ' ') {
                    lastNamePtr = &passengerName[k + 1]; // Move to character after space
                }
            }

            // Compare extracted last name with input
            if (strcmp(lastNamePtr, lastName) == 0) {
                printf("%s - Trip: %s - ID: %s - Priority: %d\n",
                       trips[i].passengers[j].name, trips[i].tripNumber,
                       trips[i].passengers[j].idNumber, trips[i].passengers[j].priority);
                found = 1;
            }
        }
    }

    if (!found) {
        printf("Passenger not found.\n");
    }
}


void viewPassengerCount(Shuttle trips[], int tripCount) {
    char tripNumber[TRIP_CODE_LENGTH];
    int i, j, row, col;
    int found = 0;
    
    printf("Enter trip number: ");
    scanf("%s", tripNumber);
    
    for (i = 0; i < tripCount; i++) {
        if (found == 0 && strcmp(trips[i].tripNumber, tripNumber) == 0) {
            found = 1;
            printf("\nPassenger count for trip %s: %d/%d\n", 
                   tripNumber, trips[i].passengerCount, 
                   MAX_PASSENGERS);
            
            int columns = 3;
            if (trips[i].passengerCount > 13) {
                columns = 4;
            }
            
            int total_seats = 13;
            if (columns == 4) {
                total_seats = 16;
            }
            
            printf("\nSeating arrangement:\n");
            printf("-------------------\n");
            
            int seat = 1;
            for (row = 0; row < 5; row++) {
                printf("| ");
                for (col = 0; col < columns; col++) {
                    if (seat <= total_seats) {
                        int occupied = 0;
                        for (j = 0; j < trips[i].passengerCount; j++) {
                            if (trips[i].passengers[j].priority == seat) {
                                occupied = 1;
                                j = trips[i].passengerCount;
                            }
                        }
                        
                        if (seat == total_seats - 1 && columns == 4) {
                            printf("Driver | ");
                            seat++;
                        } 
                        else if (seat == 14 && columns == 4) {
                            printf("     | ");
                            seat++;
                        }
                        else {
                            if (occupied) {
                                printf("X%2d | ", seat);
                            } else {
                                printf("O%2d | ", seat);
                            }
                            seat++;
                        }
                    }
                }
                printf("\n");
            }
        }
    }

    if (found == 0) {
        printf("Trip not found.\n");
    }
}

void saveTripsToFile(Shuttle trips[], int tripCount) {
    FILE *file = fopen("Trip-dd-mm-yyyy.txt", "w");
    int i, j;
    
    if (!file) {
        printf("Error saving file.\n"); 
    } else {
        for (i = 0; i < tripCount; i++) {
            for (j = 0; j < trips[i].passengerCount; j++) {
                fprintf(file, "%s\n%s\n%s\n%s\n%d\n%s\n\n", 
                        trips[i].tripNumber, 
                        trips[i].embarkationPoint, 
                        trips[i].passengers[j].name, 
                        trips[i].passengers[j].idNumber, 
                        trips[i].passengers[j].priority, 
                        trips[i].passengers[j].dropOffPoint);
            }
        }
        fclose(file);
        printf("Trip data saved successfully.\n");
    }
}


void loadRecentTripFile() {
    FILE *file = fopen("Trip-dd-mm-yyyy.txt", "r");
    char line[100];
    
    if (!file) {
        printf("Error opening trip file.\n");
    } else {
        printf("\n=== Recent Trip Data ===\n");
        while (fgets(line, sizeof(line), file)) {
            printf("%s", line);
        }
        fclose(file);
    }
}


int findTripIndex(Shuttle trips[], int tripCount, char tripNumber[]) {
    int i;
    int result = -1;  // Default to not found
    
    for (i = 0; i < tripCount; i++) {
        if (strcmp(trips[i].tripNumber, tripNumber) == 0) {
            result = i;  // Store the found index
        }
    }
    return result;  // Single return at the end
}


void exitProgram(Shuttle trips[], int tripCount) {
    saveTripsToFile(trips, tripCount);
    printf("Exiting program... Data has been saved.\n");
}
