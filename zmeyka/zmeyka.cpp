#include <iostream>
#include <windows.h>
#include <conio.h>
#include <cstdlib>
#include <ctime>

using namespace std;

const int WIDTH = 20;
const int HEIGHT = 20;
const int MAX_LENGTH = WIDTH * HEIGHT;

enum Direction { UP, DOWN, LEFT, RIGHT };

struct Point {
    int x, y;
};

class SnakeGame {
private:
    Point snake[MAX_LENGTH];
    int snakeLength;
    Point food;
    Direction dir;
    bool gameOver;
    int score;

    char board[HEIGHT][WIDTH];

    void generateFood() {
        while (true) {
            food.x = rand() % (WIDTH - 2) + 1;
            food.y = rand() % (HEIGHT - 2) + 1;
            bool onSnake = false;
            for (int i = 0; i < snakeLength; i++) {
                if (snake[i].x == food.x && snake[i].y == food.y) {
                    onSnake = true;
                    break;
                }
            }
            if (!onSnake) break;
        }
    }

    void drawBoard() {
        for (int i = 0; i < HEIGHT; i++) {
            for (int j = 0; j < WIDTH; j++) {
                board[i][j] = ' ';
            }
        }
        for (int i = 0; i < HEIGHT; i++) {
            board[i][0] = board[i][WIDTH - 1] = '#';
        }
        for (int j = 0; j < WIDTH; j++) {
            board[0][j] = board[HEIGHT - 1][j] = '#';
        }
        for (int i = 0; i < snakeLength; i++) {
            board[snake[i].y][snake[i].x] = '*';
        }
        board[food.y][food.x] = 'O';
        system("cls");
        for (int i = 0; i < HEIGHT; i++) {
            for (int j = 0; j < WIDTH; j++) {
                cout << board[i][j];
            }
            cout << endl;
        }
        cout << "Score: " << score << endl;
    }

    void moveSnake() {
        Point newHead = snake[0];
        switch (dir) {
        case UP:    newHead.y--; break;
        case DOWN:  newHead.y++; break;
        case LEFT:  newHead.x--; break;
        case RIGHT: newHead.x++; break;
        }

        if (newHead.x <= 0 || newHead.y <= 0 || newHead.y >= HEIGHT - 1 || newHead.x >= WIDTH - 1) {
            gameOver = true;
            return;
        }

        for (int i = 0; i < snakeLength; i++) {
            if (snake[i].x == newHead.x && snake[i].y == newHead.y) {
                gameOver = true;
                return;
            }
        }

        if (newHead.x == food.x && newHead.y == food.y) {
            score += 10;
            snakeLength++;
            generateFood();
        }

        for (int i = snakeLength - 1; i > 0; i--) {
            snake[i] = snake[i - 1];
        }
        snake[0] = newHead;
    }

    void showGameOverMenu() {
        char choice;
        cout << "Game Over! Final Score: " << score << endl;
        cout << "Press 'R' to restart or 'Q' to quit: ";
        choice = _getch();
        if (choice == 'r' || choice == 'R') {
            gameOver = false;
            snakeLength = 1;
            snake[0] = { WIDTH / 2, HEIGHT / 2 };
            dir = RIGHT;
            score = 0;
            generateFood();
            play();
        }
        else if (choice == 'q' || choice == 'Q') {
            exit(0);
        }
    }

public:
    SnakeGame() : gameOver(false), score(0), dir(RIGHT), snakeLength(1) {
        snake[0] = { WIDTH / 2, HEIGHT / 2 };
        generateFood();
    }

    void play() {
        while (!gameOver) {
            if (_kbhit()) {
                char key = _getch();
                switch (key) {
                case 'w': if (dir != DOWN) dir = UP; break;
                case 's': if (dir != UP) dir = DOWN; break;
                case 'a': if (dir != RIGHT) dir = LEFT; break;
                case 'd': if (dir != LEFT) dir = RIGHT; break;
                }
            }
            moveSnake();
            drawBoard();
            Sleep(100);
        }
        showGameOverMenu();
    }
};

int main() {
    srand(time(0));
    SnakeGame game;
    game.play();
    return 0;
}
