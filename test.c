#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAP_WIDTH 20
#define MAP_LENGTH 30

struct kippa {

    char name[30];
    struct kippa *link;

};

int map[MAP_LENGTH][MAP_WIDTH] = {{}};

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

    map[2][3] = 1;

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

int main(void) {

    setup();

    struct kippa *head;
    struct kippa *pnew = NULL;

    pnew = malloc(sizeof(struct kippa));

    strcpy(pnew -> name, "Fred");

    draw_map();

}