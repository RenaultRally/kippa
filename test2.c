#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAP_WIDTH 20
#define MAP_LENGTH 10

struct guy {

    char fname[30];
    int posx;
    int posy;
    struct guy *link;

};

int map[MAP_LENGTH][MAP_WIDTH] = {{}};

void add(struct guy *p, char val[], char pox, char poy) {

    if (p -> link == NULL) {

        struct guy *pnew = NULL;
        pnew = malloc(sizeof(struct guy));

        p -> link = pnew;
        pnew -> link = NULL;
        strcpy(pnew -> fname, val);
        pnew -> posx = pox;
        pnew -> posy = poy;

    } else {

        p = p -> link;
        add(p, val, pox, poy);

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

int place(struct guy *p) {

    map[p -> posy][p -> posx] = 1;

    if (p -> link == NULL) {

        return 0;

    } else {

        p = p -> link;
        place(p);

    }

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

void printLinkedlist(struct guy *p, int count) {

  if (p == NULL) {

    printf("The list is empty.\n");

  } else if (count == 0) {

    printf("[");

    if ((p -> link) == NULL) {
      printf("%s]\n\n", p -> fname);
    } else if (p != NULL) {
      printf("%s, ", p -> fname);
      printLinkedlist(p -> link, count + 1);
    }

  } else {

    if ((p -> link) == NULL) {
      printf("%s]\n\n", p -> fname);
    } else if (p != NULL) {
      printf("%s, ", p -> fname);
      printLinkedlist(p -> link, count + 1);
    }

  }

}

int main(void) {

    struct guy *head;
    struct guy *pnew = NULL;

    pnew = malloc(sizeof(struct guy));

    strcpy(pnew -> fname, "Fred");
    pnew -> posx = 2;
    pnew -> posy = 3;
    pnew -> link = NULL;
    head = pnew;

    add(head, "Peter", 4, 5);

    setup();
    place(head);

    draw_map();

    printLinkedlist(head, 0);

}