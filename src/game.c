#include "game.h"

struct Game {
    char map[HEIGHT * WIDTH + 1];
	int snaketail_x[100];
	int snaketail_y[100];
	int snaketail_len;
	int score;
	int x;
	int y;
	int fruitx;
	int fruity;
    char key;
	bool gameover;
};

void game_init(Game *self) {
    
    self->gameover = false;
    self->score = 0;
    self->snaketail_len = 0;
    self->x = WIDTH / 2;
    self->y = HEIGHT / 2;
    self->fruitx = rand() % WIDTH;
    self->fruity = rand() % HEIGHT;
    while (self->fruitx == 0) {
        self->fruitx = rand() % WIDTH;
    }
    while (self->fruity == 0) {
        self->fruity = rand() % HEIGHT;
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

    int prevX = self->snaketail_x[0];
    int prevY = self->snaketail_y[0];
    int prev2X, prev2Y;
    self->snaketail_x[0] = self->x;
    self->snaketail_y[0] = self->y;
    for (int i = 1; i < self->snaketail_len; i++) {
        prev2X = self->snaketail_x[i];
        prev2Y = self->snaketail_y[i];
        self->snaketail_x[i] = prevX;
        self->snaketail_y[i] = prevY;
        prevX = prev2X;
        prevY = prev2Y;
    }

    switch (self->key) {
    case 1: //vlavo
        --(self->x);
        break;
    case 2: //vpravo
        ++(self->x);
        break;
    case 3: //hore
        --(self->y);
        break;
    case 4: //dole
        ++(self->y);
        break;
    default:
        break;
    }
}


void game_logic(Game *self) {
    game_move(self);
    // ak je mimo mapy
    if (self->x < 0 || self->x >= WIDTH || self->y < 0 || self->y >= HEIGHT) {
        self->gameover = true;
    }
    // kolizie mapa
    if (self->map[self->x * self->y] == 'X') {
        self->gameover = true;
    }
    // kolizie chvost
    for (int i = 0; i < self->snaketail_len; i++) {
        if (self->snaketail_x[i] == self->x && self->snaketail_y[i] == self->y) {
            self->gameover = true;
        }
    }

    // pridaj skore ak zjedol ovocie
    if (self->x == self->fruitx && self->y == self->fruity) {
        self->fruitx = rand() % WIDTH;
        self->fruity = rand() % HEIGHT;
        while (self->fruitx == 0) {
            self->fruitx = rand() % WIDTH;
        }

        // nove ovocie gen
        while (self->fruity == 0) {
            self->fruity = rand() % HEIGHT;
        }
        self->score += 10;
        self->snaketail_len++;
    }
}

bool game_isgameover(Game *self) {
    return self->gameover;
}

void game_setkey(Game *self, char keytoset) {
    self->key = keytoset;
}

char *game_generatemap(Game *self) {
    memset(self->map, '.', HEIGHT * WIDTH);
    self->map[HEIGHT * WIDTH] = '\0';
    for (int i = 1; i < 5; ++i) {
        self->map[WIDTH + i] = 'X';
    }
    puts("return 5 odoslanej mapy");
    printf("%s\n", self->map);
    return self->map;
}