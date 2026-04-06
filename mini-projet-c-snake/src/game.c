#include "game.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#include "raylib.h"

#define BEST_SCORE_FILE "best_score.txt"
#define START_LENGTH 4
#define INITIAL_TICK 0.16f
#define MIN_TICK 0.07f
#define TICK_STEP 0.005f
#define FOODS_PER_LEVEL 4
#define MAX_LEVEL 6
#define CHALLENGE_SECONDS 60.0f

static float difficulty_base_tick(Difficulty difficulty) {
    switch (difficulty) {
        case DIFF_EASY:
            return 0.20f;
        case DIFF_NORMAL:
            return INITIAL_TICK;
        case DIFF_HARD:
            return 0.12f;
    }

    return INITIAL_TICK;
}

static float difficulty_speed_step(Difficulty difficulty) {
    switch (difficulty) {
        case DIFF_EASY:
            return 0.0035f;
        case DIFF_NORMAL:
            return TICK_STEP;
        case DIFF_HARD:
            return 0.007f;
    }

    return TICK_STEP;
}

static bool is_reverse(Direction a, Direction b) {
    return (a == DIR_UP && b == DIR_DOWN) || (a == DIR_DOWN && b == DIR_UP) ||
           (a == DIR_LEFT && b == DIR_RIGHT) || (a == DIR_RIGHT && b == DIR_LEFT);
}

static Vec2i direction_to_offset(Direction dir) {
    switch (dir) {
        case DIR_UP:
            return (Vec2i){0, -1};
        case DIR_DOWN:
            return (Vec2i){0, 1};
        case DIR_LEFT:
            return (Vec2i){-1, 0};
        case DIR_RIGHT:
            return (Vec2i){1, 0};
    }

    return (Vec2i){0, 0};
}

static bool snake_contains(const Snake *snake, int x, int y, bool ignore_head) {
    size_t start = ignore_head ? 1 : 0;
    for (size_t i = start; i < snake->length; ++i) {
        if (snake->body[i].x == x && snake->body[i].y == y) {
            return true;
        }
    }

    return false;
}

static bool obstacle_contains(const Game *game, int x, int y) {
    for (int i = 0; i < game->obstacle_count; ++i) {
        if (game->obstacles[i].x == x && game->obstacles[i].y == y) {
            return true;
        }
    }

    return false;
}

static bool is_safe_spawn_zone(int x, int y, int grid_width, int grid_height) {
    int center_x = grid_width / 2;
    int center_y = grid_height / 2;
    int dx = x - center_x;
    int dy = y - center_y;

    return (dx >= -3 && dx <= 3 && dy >= -3 && dy <= 3);
}

static void generate_obstacles(Game *game, int grid_width, int grid_height) {
    game->obstacle_count = 0;

    if (game->level <= 1) {
        return;
    }

    int target_count = (game->level - 1) * 10;
    if (target_count > MAX_OBSTACLES) {
        target_count = MAX_OBSTACLES;
    }

    int tries = 0;
    while (game->obstacle_count < target_count && tries < 3000) {
        int x = GetRandomValue(1, grid_width - 2);
        int y = GetRandomValue(1, grid_height - 2);
        tries++;

        if (is_safe_spawn_zone(x, y, grid_width, grid_height)) {
            continue;
        }

        if (snake_contains(&game->snake, x, y, false) || obstacle_contains(game, x, y)) {
            continue;
        }

        game->obstacles[game->obstacle_count++] = (Vec2i){x, y};
    }
}

static int load_best_score(void) {
    FILE *f = fopen(BEST_SCORE_FILE, "r");
    if (!f) {
        return 0;
    }

    int best = 0;
    if (fscanf(f, "%d", &best) != 1 || best < 0) {
        best = 0;
    }

    fclose(f);
    return best;
}

static void save_best_score(int best_score) {
    FILE *f = fopen(BEST_SCORE_FILE, "w");
    if (!f) {
        return;
    }

    fprintf(f, "%d\n", best_score);
    fclose(f);
}

static void place_food(Game *game, int grid_width, int grid_height) {
    int free_cells = (grid_width * grid_height) - (int)game->snake.length - game->obstacle_count;
    if (free_cells <= 0) {
        game->food.x = -1;
        game->food.y = -1;
        return;
    }

    for (int tries = 0; tries < 500; ++tries) {
        int x = GetRandomValue(0, grid_width - 1);
        int y = GetRandomValue(0, grid_height - 1);
        if (!snake_contains(&game->snake, x, y, false) && !obstacle_contains(game, x, y)) {
            game->food.x = x;
            game->food.y = y;
            return;
        }
    }

    for (int y = 0; y < grid_height; ++y) {
        for (int x = 0; x < grid_width; ++x) {
            if (!snake_contains(&game->snake, x, y, false) && !obstacle_contains(game, x, y)) {
                game->food.x = x;
                game->food.y = y;
                return;
            }
        }
    }

    game->food.x = -1;
    game->food.y = -1;
}

static void snake_reset(Snake *snake, int grid_width, int grid_height) {
    int center_x = grid_width / 2;
    int center_y = grid_height / 2;

    snake->length = START_LENGTH;
    snake->dir = DIR_RIGHT;
    snake->next_dir = DIR_RIGHT;
    snake->should_grow = false;

    for (size_t i = 0; i < snake->length; ++i) {
        snake->body[i] = (Vec2i){center_x - (int)i, center_y};
    }
}

static bool snake_step(Game *game, int grid_width, int grid_height) {
    Snake *snake = &game->snake;
    snake->dir = snake->next_dir;

    Vec2i offset = direction_to_offset(snake->dir);
    Vec2i new_head = {snake->body[0].x + offset.x, snake->body[0].y + offset.y};

    if (new_head.x < 0 || new_head.x >= grid_width || new_head.y < 0 || new_head.y >= grid_height) {
        return false;
    }

    if (obstacle_contains(game, new_head.x, new_head.y)) {
        return false;
    }

    bool grows_now = snake->should_grow;
    size_t body_check_start = grows_now ? 0 : 1;
    for (size_t i = body_check_start; i < snake->length; ++i) {
        if (snake->body[i].x == new_head.x && snake->body[i].y == new_head.y) {
            return false;
        }
    }

    if (grows_now) {
        if (snake->length >= snake->capacity) {
            return false;
        }
        snake->length += 1;
        snake->should_grow = false;
    }

    memmove(&snake->body[1], &snake->body[0], (snake->length - 1) * sizeof(Vec2i));
    snake->body[0] = new_head;

    if (new_head.x == game->food.x && new_head.y == game->food.y) {
        game->foods_eaten += 1;
        game->score += 10;
        if (game->score > game->best_score) {
            game->best_score = game->score;
            save_best_score(game->best_score);
        }

        if (game->tick_interval > MIN_TICK) {
            game->tick_interval -= game->speed_step;
            if (game->tick_interval < MIN_TICK) {
                game->tick_interval = MIN_TICK;
            }
        }

        snake->should_grow = true;

        if (game->foods_eaten % FOODS_PER_LEVEL == 0 && game->level < MAX_LEVEL) {
            game->level += 1;
            generate_obstacles(game, grid_width, grid_height);

            if (game->tick_interval > MIN_TICK) {
                game->tick_interval -= game->speed_step;
                if (game->tick_interval < MIN_TICK) {
                    game->tick_interval = MIN_TICK;
                }
            }
        }

        place_food(game, grid_width, grid_height);

        if (game->food.x < 0) {
            game->is_game_over = true;
        }
    }

    return true;
}

bool game_init(Game *game, int grid_width, int grid_height) {
    if (!game || grid_width <= 4 || grid_height <= 4) {
        return false;
    }

    memset(game, 0, sizeof(*game));

    size_t max_cells = (size_t)(grid_width * grid_height);
    game->snake.body = (Vec2i *)malloc(max_cells * sizeof(Vec2i));
    if (!game->snake.body) {
        return false;
    }

    game->snake.capacity = max_cells;
    game->best_score = load_best_score();
    game->difficulty = DIFF_NORMAL;
    game->challenge_mode = false;
    game->challenge_duration = CHALLENGE_SECONDS;
    game->speed_step = difficulty_speed_step(game->difficulty);

    SetRandomSeed((unsigned int)time(NULL));
    game_restart(game, grid_width, grid_height);

    return true;
}

void game_set_mode(Game *game, Difficulty difficulty, bool challenge_mode, int grid_width, int grid_height) {
    if (!game) {
        return;
    }

    game->difficulty = difficulty;
    game->challenge_mode = challenge_mode;
    game->speed_step = difficulty_speed_step(difficulty);
    game_restart(game, grid_width, grid_height);
}

void game_restart(Game *game, int grid_width, int grid_height) {
    if (!game || !game->snake.body) {
        return;
    }

    snake_reset(&game->snake, grid_width, grid_height);

    game->score = 0;
    game->level = 1;
    game->foods_eaten = 0;
    game->obstacle_count = 0;
    game->tick_interval = difficulty_base_tick(game->difficulty);
    game->challenge_time_left = game->challenge_duration;
    game->tick_accumulator = 0.0f;
    game->is_game_over = false;
    game->is_paused = false;
    game->is_victory = false;

    generate_obstacles(game, grid_width, grid_height);
    place_food(game, grid_width, grid_height);
}

void game_update(Game *game, int grid_width, int grid_height, float dt) {
    if (!game) {
        return;
    }

    if (game->is_game_over && (IsKeyPressed(KEY_ENTER) || IsKeyPressed(KEY_KP_ENTER))) {
        game_restart(game, grid_width, grid_height);
        return;
    }

    if (IsKeyPressed(KEY_R)) {
        game_restart(game, grid_width, grid_height);
        return;
    }

    if (IsKeyPressed(KEY_P) && !game->is_game_over) {
        game->is_paused = !game->is_paused;
    }

    if (game->is_game_over || game->is_paused) {
        return;
    }

    if (game->challenge_mode) {
        game->challenge_time_left -= dt;
        if (game->challenge_time_left <= 0.0f) {
            game->challenge_time_left = 0.0f;
            game->is_game_over = true;
            game->is_victory = true;
            return;
        }
    }

    Direction requested = game->snake.next_dir;
    if (IsKeyPressed(KEY_UP)) {
        requested = DIR_UP;
    } else if (IsKeyPressed(KEY_DOWN)) {
        requested = DIR_DOWN;
    } else if (IsKeyPressed(KEY_LEFT)) {
        requested = DIR_LEFT;
    } else if (IsKeyPressed(KEY_RIGHT)) {
        requested = DIR_RIGHT;
    }

    if (!is_reverse(game->snake.dir, requested)) {
        game->snake.next_dir = requested;
    }

    game->tick_accumulator += dt;

    while (game->tick_accumulator >= game->tick_interval && !game->is_game_over) {
        game->tick_accumulator -= game->tick_interval;
        if (!snake_step(game, grid_width, grid_height)) {
            game->is_game_over = true;
            game->is_victory = false;
        }
    }
}

void game_draw(const Game *game, int grid_width, int grid_height, int cell_size) {
    if (!game) {
        return;
    }

    int play_height = grid_height * cell_size;

    for (int y = 0; y < grid_height; ++y) {
        for (int x = 0; x < grid_width; ++x) {
            Color tile = ((x + y) % 2 == 0) ? (Color){22, 36, 58, 255} : (Color){18, 30, 50, 255};
            DrawRectangle(x * cell_size, y * cell_size, cell_size, cell_size, tile);
        }
    }

    for (int i = 0; i < game->obstacle_count; ++i) {
        int ox = game->obstacles[i].x * cell_size;
        int oy = game->obstacles[i].y * cell_size;
        DrawRectangle(ox + 2, oy + 2, cell_size - 4, cell_size - 4, (Color){120, 89, 62, 255});
        DrawRectangleLines(ox + 2, oy + 2, cell_size - 4, cell_size - 4, (Color){180, 142, 103, 255});
    }

    if (game->food.x >= 0 && game->food.y >= 0) {
        DrawCircle(game->food.x * cell_size + (cell_size / 2),
                   game->food.y * cell_size + (cell_size / 2),
                   cell_size * 0.34f,
                   (Color){249, 65, 68, 255});
    }

    for (size_t i = 0; i < game->snake.length; ++i) {
        Color c = (i == 0) ? (Color){76, 201, 240, 255} : (Color){56, 176, 0, 255};
        int px = game->snake.body[i].x * cell_size;
        int py = game->snake.body[i].y * cell_size;

        DrawRectangle(px + 2, py + 2, cell_size - 4, cell_size - 4, c);
    }

    DrawRectangleLinesEx((Rectangle){0, 0, (float)(grid_width * cell_size), (float)play_height}, 3, (Color){70, 86, 112, 255});

    if (game->is_paused) {
        DrawRectangle(0, 0, grid_width * cell_size, play_height, (Color){2, 6, 12, 140});
        DrawText("PAUSE", (grid_width * cell_size) / 2 - 70, play_height / 2 - 20, 40, RAYWHITE);
    }

    if (game->is_game_over) {
        Color overlay = game->is_victory ? (Color){4, 30, 10, 170} : (Color){20, 4, 4, 170};
        DrawRectangle(0, 0, grid_width * cell_size, play_height, overlay);
        DrawText(game->is_victory ? "VICTOIRE" : "GAME OVER",
                 (grid_width * cell_size) / 2 - 120,
                 play_height / 2 - 48,
                 48,
                 (Color){255, 215, 0, 255});
        DrawText(TextFormat("Score obtenu: %d", game->score),
                 (grid_width * cell_size) / 2 - 115,
                 play_height / 2 - 10,
                 24,
                 RAYWHITE);
        DrawText(TextFormat("Meilleur score: %d", game->best_score),
                 (grid_width * cell_size) / 2 - 125,
                 play_height / 2 + 18,
                 24,
                 (Color){255, 215, 0, 255});
        DrawText("Appuie sur ENTREE ou R pour recommencer",
                 (grid_width * cell_size) / 2 - 210,
                 play_height / 2 + 52,
                 24,
                 RAYWHITE);
    }
}

void game_shutdown(Game *game) {
    if (!game) {
        return;
    }

    free(game->snake.body);
    game->snake.body = NULL;
    game->snake.length = 0;
    game->snake.capacity = 0;
}
