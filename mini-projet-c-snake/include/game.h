#ifndef GAME_H
#define GAME_H

#include <stdbool.h>
#include <stddef.h>

typedef struct {
    int x;
    int y;
} Vec2i;

#define MAX_OBSTACLES 160

typedef enum {
    DIR_UP,
    DIR_DOWN,
    DIR_LEFT,
    DIR_RIGHT
} Direction;

typedef enum {
    DIFF_EASY = 0,
    DIFF_NORMAL = 1,
    DIFF_HARD = 2
} Difficulty;

typedef struct {
    Vec2i *body;
    size_t length;
    size_t capacity;
    Direction dir;
    Direction next_dir;
    bool should_grow;
} Snake;

typedef struct {
    Snake snake;
    Vec2i food;
    Vec2i obstacles[MAX_OBSTACLES];
    int obstacle_count;
    int score;
    int best_score;
    int level;
    int foods_eaten;
    Difficulty difficulty;
    bool challenge_mode;
    float challenge_duration;
    float challenge_time_left;
    float speed_step;
    float tick_interval;
    float tick_accumulator;
    bool is_game_over;
    bool is_paused;
    bool is_victory;
} Game;

bool game_init(Game *game, int grid_width, int grid_height);
void game_set_mode(Game *game, Difficulty difficulty, bool challenge_mode, int grid_width, int grid_height);
void game_update(Game *game, int grid_width, int grid_height, float dt);
void game_draw(const Game *game, int grid_width, int grid_height, int cell_size);
void game_restart(Game *game, int grid_width, int grid_height);
void game_shutdown(Game *game);

#endif
