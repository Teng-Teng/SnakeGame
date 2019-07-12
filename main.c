#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>
#include <Windows.h>
#include <conio.h>
#include "snake.h"

void initFood() {
	food[0] = rand() % WIDTH;
	food[1] = rand() % HEIGHT;
}

void initSnake() {
	snake.size = 2;

	snake.body[0].X = WIDTH / 2;
	snake.body[0].Y = HEIGHT / 2;

	snake.body[1].X = WIDTH / 2 - 1;
	snake.body[1].Y = HEIGHT / 2;
}

void showUI() {
	COORD coord;

	// show snake position
	for (int i = 0; i < snake.size; i++) {
		coord.X = snake.body[i].X;
		coord.Y = snake.body[i].Y;

		SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);

		if (i == 0)
			putchar('@');
		else
			putchar('*');
	}

	// show food position
	coord.X = food[0];
	coord.Y = food[1];
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
	putchar('#');

}

void playGame() {
	char key = 'D';

	while (snake.body[0].X >= 0 && snake.body[0].X < WIDTH
		&& snake.body[0].Y >= 0 && snake.body[0].Y < HEIGHT) {
		showUI();

		// Direction control
		while (_kbhit()) 
			key = _getch();

		switch (key) {
		case 'D': case 'd':
			dx = 1;
			dy = 0;
			break;

		case 'A': case 'a':
			dx = -1;
			dy = 0;
			break;

		case 'W': case 'w':
			dx = 0;
			dy = -1;
			break;

		case 'S': case 's':
			dx = 0;
			dy = 1;
			break;

		default:
			break;
		}

		// Whether it collides with itself
		for (int i = 1; i < snake.size; i++) {
			if (snake.body[0].X == snake.body[i].X && snake.body[0].Y == snake.body[i].Y)
				return;
		}

		// Snake and food collision
		if (snake.body[0].X == food[0] && snake.body[0].Y == food[1]) {
			initFood();
			snake.size++;
			score += 10;
		}

		// update coordinate for the snake
		for (int i = snake.size - 1; i > 0; i--) {
			snake.body[i].X = snake.body[i - 1].X;
			snake.body[i].Y = snake.body[i - 1].Y;
		}

		snake.body[0].X += dx;
		snake.body[0].Y += dy;

		Sleep(200);
		system("cls");
	}
}

int main(int argc, const char* argv[]) {
	srand((size_t)time(NULL));

	initFood();
	initSnake();
	playGame();
	
	return EXIT_SUCCESS;
}


