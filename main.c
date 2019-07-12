//
//  main.c
//  SnakeGame
//
//  Created by Teng Teng on 2019-07-10.
//  Copyright © 2019 Teng Teng. All rights reserved.
//

#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <math.h>
#include <unistd.h>
#include <time.h>
#include <curses.h>
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
	// show snake position
	for (int i = 0; i < snake.size; i++) {
		gotoXY(snake.body[i].X, snake.body[i].Y);

		if (i == 0)
			putchar('@');
		else
			putchar('*');
	}

	// show food position
	gotoXY(food[0], food[1]);
	putchar('#');
}

void gotoXY(int x, int y) {
	printf("\x1b[%d;%df", y, x);
}

void playGame() {
	char key = 'D';

	while (snake.body[0].X >= 0 && snake.body[0].X < WIDTH
		&& snake.body[0].Y >= 0 && snake.body[0].Y < HEIGHT) {
		showUI();

		// Direction control
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
		for (int i = 0; i < snake.size; i++) {
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

		//        sleep(1);
	}
}

int main(int argc, const char* argv[]) {
	srand((size_t)time(NULL));

	initFood();
	initSnake();
	playGame();

	//    while(1) {
	//        sleep(1); // will sleep for 1 s
	//        printf("%d\n", 888);
	//    }


	getchar();

	return 0;
}


