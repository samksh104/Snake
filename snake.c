#include <stdio.h>
#include <conio.h>
#include <windows.h>

int length;
int bend_no;
int len;
char key;

#define SIZE 20

int life;
int score;
int x, y, fruitx, fruity, flag;

int tailX[100], tailY[100];
int countTail = 0;

void gotoxy(int x, int y) {
    COORD coord = {x, y};
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
}

void delay(int ms) {
    Sleep(ms);
}

void Board() {
    system("cls");
    for (int i = 0; i <= SIZE; i++) {
        for (int j = 0; j <= SIZE; j++) {
            if (i == 0 || i == SIZE || j == 0 || j == SIZE)
                printf("#");
            else if (i == y && j == x)
                printf("O"); // Snake head
            else if (i == fruity && j == fruitx)
                printf("*"); // Fruit
            else {
                int isTail = 0;
                for (int k = 0; k < countTail; k++) {
                    if (tailX[k] == j && tailY[k] == i) {
                        printf("o");
                        isTail = 1;
                    }
                }
                if (!isTail)
                    printf(" ");
            }
        }
        printf("\n");
    }
    printf("Score: %d\n", score);
}

void Setup() {
    x = SIZE / 2;
    y = SIZE / 2;
    fruitx = rand() % (SIZE - 2) + 1;
    fruity = rand() % (SIZE - 2) + 1;
    score = 0;
    flag = 0;
}

void Input() {
    if (_kbhit()) {
        switch (_getch()) {
            case 'a': flag = 1; break;
            case 'd': flag = 2; break;
            case 'w': flag = 3; break;
            case 's': flag = 4; break;
            case 'x': exit(0);
        }
    }
}

void Move() {
    int prevX = tailX[0];
    int prevY = tailY[0];
    int prev2X, prev2Y;
    tailX[0] = x;
    tailY[0] = y;

    for (int i = 1; i < countTail; i++) {
        prev2X = tailX[i];
        prev2Y = tailY[i];
        tailX[i] = prevX;
        tailY[i] = prevY;
        prevX = prev2X;
        prevY = prev2Y;
    }

    switch (flag) {
        case 1: x--; break;
        case 2: x++; break;
        case 3: y--; break;
        case 4: y++; break;
    }

    if (x == 0 || x == SIZE || y == 0 || y == SIZE) {
        printf("Game Over!\n");
        exit(0);
    }

    for (int i = 0; i < countTail; i++) {
        if (tailX[i] == x && tailY[i] == y) {
            printf("Game Over! You bit yourself.\n");
            exit(0);
        }
    }

    if (x == fruitx && y == fruity) {
        score += 10;
        fruitx = rand() % (SIZE - 2) + 1;
        fruity = rand() % (SIZE - 2) + 1;
        countTail++;
    }
}

int main() {
    Setup();
    while (1) {
        Board();
        Input();
        Move();
        delay(100);
    }
    return 0;
}
