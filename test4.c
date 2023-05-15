#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAP_WIDTH 20
#define MAP_LENGTH 10

struct kippa {

    char fname[30];
    int posx;
    int posy;
    int id;
    struct kippa *link;

};

int map[MAP_LENGTH][MAP_WIDTH] = {{}};
int latest_id = 0;

void add(struct kippa *p) {

    struct kippa *newn;
    newn = malloc(sizeof(struct kippa));

    newn -> fname[0] = '\0';
    newn -> posx = -1;
    newn -> posy = -1;
    newn -> id = latest_id + 1;
    newn -> link = NULL;

    latest_id += 1;

    if (p -> link == NULL) {

        p -> link = newn;

    } else {

        p = p -> link;
        add(p);

    }

}

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

void printLinkedlist(struct kippa *p, int count) {

  if (p == NULL) {

    printf("The list is empty.\n");

  } else if (count == 0) {

    printf("[");

    if ((p -> link) == NULL) {
        
        printf("%d]\n\n", p -> id);

    } else if (p != NULL) {

        printf("%d, ", p -> id);
        printLinkedlist(p -> link, count + 1);
        
    }

  } else {

    if ((p -> link) == NULL) {
      printf("%d]\n\n", p -> id);
    } else if (p != NULL) {
      printf("%d, ", p -> id);
      printLinkedlist(p -> link, count + 1);
    }

  }

}

int main(void) {

    // initialize first node

    struct kippa *head;
    struct kippa *pnew = NULL;

    pnew = malloc(sizeof(struct kippa));

    strcpy(pnew -> fname, "Fred");
    pnew -> posx = 2;
    pnew -> posy = 3;
    pnew -> id = 0;
    pnew -> link = NULL;
    head = pnew;

    add(head);
    modifystr(head, 1, "fname", "Mann");
    modifyint(head, 1, "posx", 5);
    modifyint(head, 1, "posy", 5);

    setup();
    place(head);

    draw_map();

    printLinkedlist(head, 0);

}