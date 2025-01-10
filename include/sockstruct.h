#ifndef SOCKSTRUCT_H
#define SOCKSTRUCT_H

typedef struct SnakeData {
    int snaketail_x[100];
	int snaketail_y[100];
	int snaketail_len;
	int score;
	int x;
	int y;
	int fruitx;
	int fruity;
    int gameover;
} SnakeData;

#endif