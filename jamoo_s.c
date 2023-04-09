#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include <stdlib.h>
#include <time.h>
#ifdef _WIN32
#include <windows.h>
#endif

typedef struct {
    int x, y;
    char c;
} Point;

typedef struct {
    int x, y;
    int magnitude;
} Vector;

#define WIDTH 36
#define HEIGHT 5
#define BORDER_WIDTH 72
#define BORDER_HEIGHT 18

bool is_inside_bounds(int x, int y, int limitX, int limitY) {
    return x >= 0 && x < limitX && y >= 0 && y < limitY - 2;
}

void clear_screen() {
    #ifdef _WIN32
    system("cls");
    #else
    printf("\033[2J");
    #endif
}

void move_cursor_home() {
    #ifdef _WIN32
    HANDLE hStdout = GetStdHandle(STD_OUTPUT_HANDLE);
    COORD coord = {0, 0};
    SetConsoleCursorPosition(hStdout, coord);
    #else
    printf("\033[H");
    #endif
}

void initialize_vector(Vector *vector) {
    srand(time(NULL));
    do {
        vector->x = (rand() % 3) - 1;
        vector->y = (rand() % 3) - 1;
    } while (vector->x == 0 || vector->y == 0); 
    vector->magnitude = 1;
}

bool share_row(int y, Point points[], int num_points, int offsetX, int offsetY) {
    for (int i = 0; i < num_points; i++) {
        int pointY = points[i].y + offsetY;
        if (pointY == y || pointY == y - 1) {
            return true;
        }
    }
    return false;
}

void render_ascii_art(Point points[], int num_points, int offsetX, int offsetY) {
    char buffer[BORDER_HEIGHT][BORDER_WIDTH + 1];
    memset(buffer, ' ', sizeof(buffer));

    for (int i = 0; i < BORDER_HEIGHT; i++) {
        buffer[i][0] = '|';
        buffer[i][BORDER_WIDTH - 1] = '|';
    }
    for (int i = 0; i < BORDER_WIDTH; i++) {
        buffer[0][i] = '_';
        buffer[BORDER_HEIGHT - 1][i] = '_';
    }

    for (int i = 0; i < num_points; i++) {
        int x = points[i].x + offsetX;
        int y = points[i].y + offsetY;
        if (x >= 0 && x < BORDER_WIDTH && y >= 0 && y < BORDER_HEIGHT) {
            buffer[y][x] = points[i].c;
        }
    }

    for (int y = 0; y < BORDER_HEIGHT; y++) {
        for (int x = 0; x < BORDER_WIDTH; x++) {
            if (buffer[y][x] != ' ' || (y == 0 || y == BORDER_HEIGHT - 1 || x == 0 || x == BORDER_WIDTH - 1)) {
                if ((x == BORDER_WIDTH - 1) && share_row(y, points, num_points, offsetX, offsetY)) {
                    putchar(' ');
                }
                putchar(buffer[y][x]);
            } else {
                putchar(' ');
            }
        }
        putchar('\n');
    }
}

int main() {
    const char *ascii_art[] = {
        "     __     __    __     __  __    ",
        "    /\\ \\   /\\ \"-./  \\   /\\ \\/\\ \\   ",
        "   _\\_\\ \\  \\ \\ \\-./\\ \\  \\ \\ \\_\\ \\  ",
        "  /\\_____\\  \\ \\_\\ \\ \\_\\  \\ \\_____\\ ",
        "  \\/_____/   \\/_/  \\/_/   \\/_____/ ",
    };

    Point points[128];
    int num_points = 0;

    Vector vector;
    initialize_vector(&vector);
    

    int offsetX = (BORDER_WIDTH - WIDTH) / 2;
    int offsetY = (BORDER_HEIGHT - HEIGHT - 2) / 2;
    for (int y = 0; y < HEIGHT; y++) {
        for (int x = 0; x < WIDTH; x++) {
            if (ascii_art[y][x] != ' ') {
                points[num_points++] = (Point) {x, y - HEIGHT / 2, ascii_art[y][x]};
            }
        }
    }   

    while (1) {
        clear_screen();
        move_cursor_home();

        render_ascii_art(points, num_points, offsetX, offsetY);
        usleep(66000);

        offsetX += vector.x * vector.magnitude;
        offsetY += vector.y * vector.magnitude;
        if (vector.magnitude > 1) {
            vector.magnitude = 1;
        }
        if (!is_inside_bounds(offsetX, offsetY - 4, BORDER_WIDTH - WIDTH, BORDER_HEIGHT - HEIGHT)) {
            if (offsetX < 0 || offsetX >= BORDER_WIDTH - WIDTH) {
                vector.x = -vector.x;
            }
            if (offsetY < 0 || offsetY >= BORDER_HEIGHT - HEIGHT - 1) {
                vector.y = -vector.y;
            }
        }
        for (int i = 0; i < num_points; i++) {
            if (points[i].y == -HEIGHT / 2 && offsetY + points[i].y < 1) {
                vector.y = abs(vector.y);
            }
        }
    }

    return 0;
}