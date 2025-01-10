#include "game.h"

struct Game {
    char map[HEIGHT * WIDTH + 1];
	SnakeData snakeData1;
    char key;
};

void game_init(Game *self) {
    self->snakeData1.gameover = 0;
    self->snakeData1.score = 0;
    self->snakeData1.snaketail_len = 0;
    self->snakeData1.x = WIDTH / 2;
    self->snakeData1.y = HEIGHT / 2;
    self->snakeData1.fruitx = rand() % WIDTH;
    self->snakeData1.fruity = rand() % HEIGHT;
    while (self->snakeData1.fruitx == 0) {
        self->snakeData1.fruitx = rand() % WIDTH;
    }
    while (self->snakeData1.fruity == 0) {
        self->snakeData1.fruity = rand() % HEIGHT;
    }
}

Game *game_create() {
    Game *self = malloc(sizeof(Game));
    game_init(self);
    return self;
}

void game_destroy(Game *self) {
    if (self) {
        free(self);
    }
}

void game_move(Game *self) {

    int prevX = self->snakeData1.snaketail_x[0];
    int prevY = self->snakeData1.snaketail_y[0];
    int prev2X, prev2Y;
    self->snakeData1.snaketail_x[0] = self->snakeData1.x;
    self->snakeData1.snaketail_y[0] = self->snakeData1.y;
    for (int i = 1; i < self->snakeData1.snaketail_len; i++) {
        prev2X = self->snakeData1.snaketail_x[i];
        prev2Y = self->snakeData1.snaketail_y[i];
        self->snakeData1.snaketail_x[i] = prevX;
        self->snakeData1.snaketail_y[i] = prevY;
        prevX = prev2X;
        prevY = prev2Y;
    }

    switch (self->key) {
    case 'l': //vlavo
        --(self->snakeData1.x);
        break;
    case 'r': //vpravo
        ++(self->snakeData1.x);
        break;
    case 'u': //hore
        --(self->snakeData1.y);
        break;
    case 'd': //dole
        ++(self->snakeData1.y);
        break;
    default:
        break;
    }
}


void game_logic(Game *self) {
    game_move(self);
    
    // ak je mimo mapy
    if (self->snakeData1.x < 0 || self->snakeData1.x >= WIDTH || self->snakeData1.y < 0 || self->snakeData1.y >= HEIGHT) {
        self->snakeData1.gameover = 1;
    }
    
    // kolizie mapa
    if (self->map[self->snakeData1.y * WIDTH + self->snakeData1.x] == 'X') {
        self->snakeData1.gameover = 1;
    }
    
    // kolizie chvost
    for (int i = 0; i < self->snakeData1.snaketail_len; i++) {
        if (self->snakeData1.snaketail_x[i] == self->snakeData1.x && self->snakeData1.snaketail_y[i] == self->snakeData1.y) {
            self->snakeData1.gameover = 1;
        }
    }

    
    // pridaj skore ak zjedol ovocie
    if (self->snakeData1.x == self->snakeData1.fruitx && self->snakeData1.y == self->snakeData1.fruity) {
        do {
            self->snakeData1.fruitx = rand() % WIDTH;
            self->snakeData1.fruity = rand() % HEIGHT;
        } while (self->map[self->snakeData1.fruity * WIDTH + self->snakeData1.fruitx] == 'X');
        self->snakeData1.score += 10;
        self->snakeData1.snaketail_len++;
    }
}

int game_getgameover(Game *self) {
    return self->snakeData1.gameover;
}

void game_setkey(Game *self, char keytoset) {
    self->key = keytoset;
}

SnakeData *game_getsnakedataptr(Game *self) {
    return &self->snakeData1;
}

char *game_generatemap(Game *self) {
    puts("generatemap");
    memset(self->map, '.', HEIGHT * WIDTH);
    int numOfObstacles = (HEIGHT * WIDTH) >> 5;
    for (int i = 0; i < numOfObstacles; ++i) {
        self->map[rand() % (HEIGHT * WIDTH)] = 'X';
    }
    self->map[HEIGHT * WIDTH] = '\0';
    puts("return 5 odoslanej mapy");
    printf("%s\n", self->map);
    return self->map;
}