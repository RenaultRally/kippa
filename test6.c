#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <windows.h>

#define MAP_WIDTH 20
#define MAP_LENGTH 10

struct kippa {

    char fname[30];
    int posx;
    int posy;
    int id;
    struct kippa *link;

};

// initialize first node
struct kippa *head;

int map[MAP_LENGTH][MAP_WIDTH] = {0};
int latest_id = 0;
int pause = 0;
int refresh = 30;

// Creates a new blank node with a unique ID
void addkippa(struct kippa *p) {

    struct kippa *newn;
    newn = malloc(sizeof(struct kippa));

    if (newn == NULL) {

        printf("Memory allocation was unsuccessful.\n");
        return;

    }

    newn -> fname[0] = '\0';
    newn -> posx = -1;
    newn -> posy = -1;
    newn -> id = latest_id + 1;
    newn -> link = NULL;

    if (p -> link == NULL) {

        p -> link = newn;
        latest_id += 1;

    } else {

        p = p -> link;
        addkippa(p);

    }

}

// Sets up the 2D array representing the map
void setup() {

    for (int i = 0; i < MAP_LENGTH; i += 1) {

        for (int j = 0; j < MAP_WIDTH; j += 1) {

            map[i][j] = 0;

        }

    }

    for (int i = 0; i < MAP_LENGTH; i += 1) {

        map[i][0] = 3;
        map[i][MAP_WIDTH - 1] = 3;

    }

    for (int i = 0; i < MAP_WIDTH; i += 1) {

        map[0][i] = 2;
        map[MAP_LENGTH - 1][i] = 2;

    }

}

// Adjusts the map, placing the kippas onto the blank grid
int place(struct kippa *p) {

    if (p == NULL) {
        return 0;
    }

    if (p->posx >= 0 && p->posy >= 0) {
        map[p->posy][p->posx] = 1;
    }

    place(p->link);

    return 0;
}

// Adjusts one of a kippa's attributes, specific to integer attributes
void modifyint(struct kippa *p, int id, char *attribute, int value) {

    while (p != NULL) {

        if (p -> id == id) {

            if (strcmp(attribute, "posx") == 0) {

                p -> posx = value;

            } else if (strcmp(attribute, "posy") == 0) {

                p -> posy = value;

            } else {

                printf("You're using the wrong function, dumbass.");

            }

            return;

        }

        p = p->link;

    }

    printf("Kippa with id %d not found.\n", id);

}

// Adjusts one of a kippa's attributes, specific to string attributes
void modifystr(struct kippa *p, int id, char *attribute, char value[]) {

    while (p != NULL) {

        if (p -> id == id) {

            if (strcmp(attribute, "fname") == 0) {

                strcpy(p -> fname, value);

            } else {

                printf("You're using the wrong function, dumbass.");

            }

            return;

        }

        p = p -> link;

    }

    printf("Kippa with id %d not found.\n", id);

}

void printinfo(struct kippa *p, int kid) {

    if (p -> id == kid) {

        printf("\nID: %d\n", p -> id);
        printf("Name: %s\n", p -> fname);
        printf("Position: (%d, %d)\n\n", p -> posx, p -> posy);

    }

}

char* returninfo(struct kippa *p, int kid, char *attribute) {
    
    char* num = NULL;

    if (kid == p -> id) {
        if (strcmp(attribute, "fname") == 0) {

            return p -> fname;

        } else if (strcmp(attribute, "posx") == 0) {

            num = malloc(30 * sizeof(char));  // Allocate memory for the string
            sprintf(num, "%d", p -> posx);
            return num;

        } else if (strcmp(attribute, "posy") == 0) {

            num = malloc(30 * sizeof(char));  // Allocate memory for the string
            sprintf(num, "%d", p -> posy);
            return num;

        } else {

            printf("%s: Attribute not found. ", attribute);
            return "Continuing...";

        }
    } else if (p -> link == NULL) {

        printf("%d: Invalid kID.\n", kid);
        return "Continuing...";

    } else {

        p = p -> link;
        return returninfo(p, kid, attribute);

    }
}

// Displays the map
void draw_map() {

    system("cls");

    for (int i = 0; i < MAP_LENGTH; i += 1) {

        for (int j = 0; j < MAP_WIDTH; j += 1) {

            switch (map[i][j]) {

                case 0:

                    printf(" ");
                    break;

                case 1:

                    printf("#");
                    break;

                case 2:

                    printf("-");
                    break;

                case 3:

                    printf("|");
                    break;

            }

        }

        printf("\n");

    }

}

// Lists out the current IDs
void printIDs(struct kippa *p, int count) {

    if (p == NULL) {

        printf("The list is empty.\n");

    } else if (count == 0) {

        printf("[");

        if ((p -> link) == NULL) {
        
            printf("%d]\n\n", p -> id);

        } else if (p != NULL) {

            printf("%d, ", p -> id);
            printIDs(p -> link, count + 1);
        
        }

    } else {

        if ((p -> link) == NULL) {
            printf("%d]\n\n", p -> id);
        } else if (p != NULL) {
            printf("%d, ", p -> id);
            printIDs(p -> link, count + 1);
        }

    }

}

DWORD WINAPI input_thread(LPVOID arg) {

    char input[50];
    char instruct[20];
    char parameter_1[20];
    char parameter_2[20];
    char parameter_3[20];
    char parameter_4[20];
    int result;

    HANDLE hStdin = GetStdHandle(STD_INPUT_HANDLE);
    DWORD dwRead;

    while (1) {

        if (ReadFile(hStdin, input, sizeof(input), &dwRead, NULL)) {

            input[dwRead - 2] = '\0';  // Remove the newline character

            sscanf(input, "%s %s %s %s %s", instruct, parameter_1, parameter_2, parameter_3, parameter_4);

            if (strcmp(instruct, "pause") == 0) {

                pause = 1;
                printf("The map refresh has been paused. Enter the 'resume' command to continue.\n");

            } else if (strcmp(instruct, "resume") == 0) {

                pause = 0;
                printf("The map refresh is now resuming.\n");

            } else if (strcmp(instruct, "info") == 0) {

                printf("%s\n", returninfo(head, atoi(parameter_1), parameter_2));

            } else if (strcmp(instruct, "modify") == 0) {

                if (strcmp(parameter_2, "fname") == 0) {

                    modifystr(head, atoi(parameter_1), parameter_2, parameter_3);
                    printf("Attribute %s changed to %s.\n", parameter_2, parameter_3);

                } else {

                    modifyint(head, atoi(parameter_1), parameter_2, atoi(parameter_3));
                    printf("Attribute %s changed to %s.\n", parameter_2, parameter_3);

                }

            } else if (strcmp(instruct, "faster") == 0) {

                refresh /= 2;
                printf("Update refresh period halved to %d seconds.\n", refresh);

            } else if (strcmp(instruct, "slower") == 0) {

                refresh *= 2;
                printf("Update refresh period doubled to %d seconds.\n", refresh);

            } else if (strcmp(instruct, "createent") == 0) {

                if (strcmp(parameter_1, "kippa") == 0) {

                    addkippa(head);
                    modifystr(head, latest_id, "fname", parameter_2);
                    modifyint(head, latest_id, "posx", atoi(parameter_3));
                    modifyint(head, latest_id, "posy", atoi(parameter_4));

                    printf("%s '%s' successfully created at (%s, %s).", parameter_1, parameter_2, parameter_3, parameter_4);

                }
            
            } else {

                printf("Command '%s' not recognized. Resuming...\n", instruct);

            }

        } else {

            fprintf(stderr, "ReadFile() failed with error %lu\n", GetLastError());
            exit(EXIT_FAILURE);

        }
    }

    return 0;

}

int main(void) {

    // Create a thread for input handling
    HANDLE hInputThread = CreateThread(NULL, 0, input_thread, NULL, 0, NULL);
    if (hInputThread == NULL) {
        fprintf(stderr, "CreateThread() failed with error %lu\n", GetLastError());
        exit(EXIT_FAILURE);
    }

    struct kippa *pnew = NULL;

    pnew = malloc(sizeof(struct kippa));

    strcpy(pnew -> fname, "Fred");
    pnew -> posx = 2;
    pnew -> posy = 3;
    pnew -> id = 0;
    pnew -> link = NULL;
    head = pnew;

    while (1) {
        
        if (pause == 0) {

            setup();
            place(head);
            draw_map();

        }

        Sleep(refresh * 1000);

    }

    // Free the dynamically allocated memory
    struct kippa *current = head;
    struct kippa *next;

    while (current != NULL) {

        next = current->link;
        free(current);
        current = next;

    }

    // Wait for the input thread to finish
    WaitForSingleObject(hInputThread, INFINITE);
    CloseHandle(hInputThread);

    return 0;

}