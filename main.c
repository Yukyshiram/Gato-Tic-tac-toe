#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <windows.h>
#include <time.h>

#define SIZE 3
#define ENTER 13
#define ESC 27
#define UP 72
#define DOWN 80
#define LEFT 75
#define RIGHT 77

void cleanTerminal() {
    system("cls");
}

void tableInit(char table[SIZE][SIZE], int *axisX, int *axisY) {
    for (int i = 0; i < SIZE; i++)
        for (int j = 0; j < SIZE; j++)
            table[i][j] = ' ';
    *axisX = *axisY = 0;
}

void tablePrint(char table[SIZE][SIZE], char player, int mode, int axisX, int axisY) {
    cleanTerminal();
    printf(">-> The battle cats <-<\n\n");
    printf("Usa las keys de flecha para moverte y ENTER para seleccionar.\n\n");

    if (mode == 1)
        printf("Turno de: %c\n\n", player);

    for (int i = 0; i < SIZE; i++) {
        for (int j = 0; j < SIZE; j++) {
            if (i == axisY && j == axisX)
                printf("[%c]", table[i][j]);
            else
                printf(" %c ", table[i][j]);
            if (j < SIZE - 1) printf("|");
        }
        printf("\n");
        if (i < SIZE - 1) printf("---|---|---\n");
    }

    printf("\nDato curioso: los gatos pueden rotar sus orejas 180 grados.\n");
}

int winVerify(char table[SIZE][SIZE], char player) {
    for (int i = 0; i < SIZE; i++) {
        if (table[i][0] == player && table[i][1] == player && table[i][2] == player) return 1;
        if (table[0][i] == player && table[1][i] == player && table[2][i] == player) return 1;
    }
    if (table[0][0] == player && table[1][1] == player && table[2][2] == player) return 1;
    if (table[0][2] == player && table[1][1] == player && table[2][0] == player) return 1;
    return 0;
}

int tableLleno(char table[SIZE][SIZE]) {
    for (int i = 0; i < SIZE; i++)
        for (int j = 0; j < SIZE; j++)
            if (table[i][j] == ' ') return 0;
    return 1;
}

void superPcMove(char table[SIZE][SIZE]) {
    int row, column;
    do {
        row = rand() % SIZE;
        column = rand() % SIZE;
    } while (table[row][column] != ' ');
    table[row][column] = 'O';
}

void InteractionGame(int mode) {
    char table[SIZE][SIZE];
    int axisX = 0, axisY = 0;
    char player = 'X';
    int playing = 1;

    tableInit(table, &axisX, &axisY);

    while (playing) {
        tablePrint(table, player, mode, axisX, axisY);

        if (player == 'X' || mode == 1) {
            int key = getch();
            if (key == 0 || key == 224) key = getch();

            switch (key) {
                case UP: if (axisY > 0) axisY--; break;
                case DOWN: if (axisY < SIZE - 1) axisY++; break;
                case LEFT: if (axisX > 0) axisX--; break;
                case RIGHT: if (axisX < SIZE - 1) axisX++; break;
                case ENTER:
                    if (table[axisY][axisX] == ' ') {
                        table[axisY][axisX] = player;
                        if (winVerify(table, player)) {
                            tablePrint(table, player, mode, axisX, axisY);
                            printf("\n\n\tEl jugador: %c gana!\n", player);
                            Sleep(5000);
                            playing = 0;
                        } else if (tableLleno(table)) {
                            tablePrint(table, player, mode, axisX, axisY);
                            printf("\n\n\t\tEmpate!\n");
                            Sleep(5000);
                            playing = 0;
                        } else {
                            player = (player == 'X') ? 'O' : 'X';
                        }
                    } else {
                        tablePrint(table, player, mode, axisX, axisY);
                        printf("\nCasilla ocupada, elige otra.\n");
                        Sleep(1000);
                    }
                    break;
            }
        } else {
            printf("\nTurno de la computadora...\n");
            Sleep(1000);
            superPcMove(table);
            if (winVerify(table, 'O')) {
                tablePrint(table, player, mode, axisX, axisY);
                printf("\n\nLa computadora gana!\n");
                printf("Es imposible este suceso...\n");
                Sleep(5000);
                playing = 0;
            } else if (tableLleno(table)) {
                tablePrint(table, player, mode, axisX, axisY);
                printf("\n\n\t\tEmpate!\n");
                Sleep(5000);
                playing = 0;
            } else {
                player = 'X';
            }
        }
    }
}

int menuSec() {
    int selection = 0;
    const char* opciones[] = {
        "Jugar nueva partida",
        "Cambiar modo de juego",
        "Salir del programa"
    };

    while (1) {
        cleanTerminal();
        printf("\n>-> Si te ha gustado, puedes volverlo a jugar <-<\n\n");
        for (int i = 0; i < 3; i++) {
            if (i == selection) printf(" > %s < \n", opciones[i]);
            else printf("   %s\n", opciones[i]);
        }

        int key = getch();
        if (key == 0 || key == 224) key = getch();

        switch (key) {
            case UP: if (selection > 0) selection--; break;
            case DOWN: if (selection < 2) selection++; break;
            case ENTER: return selection;
        }
    }
}

int mainMenu() {
    int selection = 0;
    const char* opciones[] = {
        "Jugador vs Jugador",
        "Jugador vs Computadora"
    };

    while (1) {
        cleanTerminal();
        printf("\n>-> Deberiamos jugar! <-<\n\n");
        printf("Instrucciones:\n");
        printf("1. Usa las flechas para moverte.\n");
        printf("2. Presiona ENTER para seleccionar.\n");
        printf("3. Elige entre dos modos de juego:\n\n");

        for (int i = 0; i < 2; i++) {
            if (i == selection) printf(" > %s < \n", opciones[i]);
            else printf("   %s\n", opciones[i]);
        }

        int key = getch();
        if (key == 0 || key == 224) key = getch();

        switch (key) {
            case UP: if (selection > 0) selection--; break;
            case DOWN: if (selection < 1) selection++; break;
            case ENTER: return selection + 1;
        }
    }
}

int main() {
    srand(time(NULL));
    int gameMode = mainMenu();

    while (1) {
        InteractionGame(gameMode);

        int option = menuSec();
        if (option == 0) continue;
        else if (option == 1) gameMode = mainMenu();
        else break;
    }

    cleanTerminal();
    printf("\n>-> Thanks for playing <-<\n\n");
    printf(">-> By: Im_JVallejo <-< \n\n");
    return 0;
}
