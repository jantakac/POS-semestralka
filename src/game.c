#include "game.h"

struct Game {
    char map[MAXWIDTH * MAXHEIGHT + 1];
	SnakeData snakeData1;
    time_t start_time;
    time_t current_time;
    int max_seconds;
    int elapsed_time;
    int gamewidth;
    int gameheight;
    char key;
};

void game_init(Game *self, int max_seconds, int gamewidth, int gameheight) {
    srand(time(NULL));
    self->max_seconds = max_seconds;
    self->elapsed_time = 0;
    self->gamewidth = gamewidth;
    self->gameheight = gameheight;
    
    self->snakeData1.gameover = 0;
    self->snakeData1.score = 0;
    self->snakeData1.snaketail_len = 0;
    self->snakeData1.x = self->gamewidth / 2;
    self->snakeData1.y = self->gameheight / 2;
    self->snakeData1.fruitx = rand() % self->gamewidth;
    self->snakeData1.fruity = rand() % self->gameheight;
    while(self->snakeData1.fruitx == 0) {
        self->snakeData1.fruitx = rand() % self->gamewidth;
    }
    while(self->snakeData1.fruity == 0) {
        self->snakeData1.fruity = rand() % self->gameheight;
    }
    time(&self->start_time);
}

Game *game_create(int max_seconds, int gamewidth, int gameheight) {
    Game *self = malloc(sizeof(Game));
    game_init(self, max_seconds, gamewidth, gameheight);
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

    time(&self->current_time);
    self->elapsed_time = (int)(self->current_time - self->start_time);
    self->snakeData1.elapsed_time = self->elapsed_time;
    // ak presiel cas
    if (self->max_seconds != 0 && self->elapsed_time > self->max_seconds) {
        self->snakeData1.gameover = 1;
    }
    
    // ak je mimo mapy
    if (self->snakeData1.x < 0 || self->snakeData1.x >= self->gamewidth || self->snakeData1.y < 0 || self->snakeData1.y >= self->gameheight) {
        self->snakeData1.gameover = 1;
    }
    
    // kolizie mapa
    if (self->map[self->snakeData1.y * self->gamewidth + self->snakeData1.x] == 'X') {
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
            self->snakeData1.fruitx = rand() % self->gamewidth;
            self->snakeData1.fruity = rand() % self->gameheight;
        } while (self->map[self->snakeData1.fruity * self->gamewidth + self->snakeData1.fruitx] == 'X');
        self->snakeData1.score += 10;
        self->snakeData1.snaketail_len++;
    }
}

int game_getgameover(Game *self) {
    return self->snakeData1.gameover;
}

SnakeData *game_getsnakedataptr(Game *self) {
    return &self->snakeData1;
}

void game_setkey(Game *self, char keytoset) {
    self->key = keytoset;
}

void game_setelapsedtime(Game* self, int seconds) {
    self->snakeData1.elapsed_time = seconds;
}


char *game_generatemap(Game *self) {
    puts("generatemap");
    memset(self->map, '.', self->gameheight * self->gamewidth);
    int numOfObstacles = (self->gameheight * self->gamewidth) >> 5;
    for (int i = 0; i < numOfObstacles; ++i) {
        self->map[rand() % (self->gameheight * self->gamewidth)] = 'X';
    }
    self->map[self->gameheight * self->gamewidth] = '\0';
    puts("return 5 odoslanej mapy");
    printf("%s\n", self->map);
    return self->map;
}