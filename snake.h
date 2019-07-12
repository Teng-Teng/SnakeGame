#pragma once

#define WIDTH 60
#define HEIGHT 20

struct BODY {
	int X;
	int Y;
};

struct SNAKE {
	int size;
	struct BODY body[WIDTH * HEIGHT];
}snake;

// Food coordinate
int food[2] = { 0 };
int score = 0;

// coordinates offset
int dx = 0;
int dy = 0;

void initFood(void);
void initSnake(void);
void showUI(void);
void gotoXY(int x, int y);
void playGame(void);

