#include <stdbool.h>
#include <stdio.h>

#include "raylib.h"

#include "game.h"

typedef enum {
    SCREEN_MENU,
    SCREEN_HELP,
    SCREEN_PLAY
} AppScreen;

typedef enum {
    MENU_START,
    MENU_DIFFICULTY,
    MENU_CHALLENGE,
    MENU_HELP,
    MENU_QUIT,
    MENU_COUNT
} MenuItem;

static const char *difficulty_label(Difficulty diff) {
    switch (diff) {
        case DIFF_EASY:
            return "Easy";
        case DIFF_NORMAL:
            return "Normal";
        case DIFF_HARD:
            return "Hard";
    }

    return "Normal";
}

int main(void) {
    const int grid_width = 24;
    const int grid_height = 18;
    const int cell_size = 36;
    const int ui_height = 72;

    const int window_width = grid_width * cell_size;
    const int window_height = (grid_height * cell_size) + ui_height;

    InitWindow(window_width, window_height, "Snake C - Mini projet Raylib");
    SetTargetFPS(60);

    Game game;
    if (!game_init(&game, grid_width, grid_height)) {
        TraceLog(LOG_ERROR, "Echec initialisation: memoire insuffisante");
        CloseWindow();
        return 1;
    }

    AppScreen screen = SCREEN_MENU;
    Difficulty menu_difficulty = DIFF_NORMAL;
    bool menu_challenge_mode = false;
    int selected_menu_item = MENU_START;
    bool should_close = false;

    while (!WindowShouldClose() && !should_close) {
        float dt = GetFrameTime();

        if (screen == SCREEN_MENU) {
            if (IsKeyPressed(KEY_UP)) {
                selected_menu_item -= 1;
                if (selected_menu_item < 0) {
                    selected_menu_item = MENU_COUNT - 1;
                }
            }

            if (IsKeyPressed(KEY_DOWN)) {
                selected_menu_item = (selected_menu_item + 1) % MENU_COUNT;
            }

            if (selected_menu_item == MENU_DIFFICULTY && (IsKeyPressed(KEY_LEFT) || IsKeyPressed(KEY_RIGHT) || IsKeyPressed(KEY_ENTER) || IsKeyPressed(KEY_KP_ENTER))) {
                menu_difficulty = (Difficulty)(((int)menu_difficulty + 1) % 3);
            }

            if (selected_menu_item == MENU_CHALLENGE && (IsKeyPressed(KEY_LEFT) || IsKeyPressed(KEY_RIGHT) || IsKeyPressed(KEY_ENTER) || IsKeyPressed(KEY_KP_ENTER))) {
                menu_challenge_mode = !menu_challenge_mode;
            }

            if (IsKeyPressed(KEY_ENTER) || IsKeyPressed(KEY_KP_ENTER)) {
                if (selected_menu_item == MENU_START) {
                    game_set_mode(&game, menu_difficulty, menu_challenge_mode, grid_width, grid_height);
                    screen = SCREEN_PLAY;
                } else if (selected_menu_item == MENU_HELP) {
                    screen = SCREEN_HELP;
                } else if (selected_menu_item == MENU_QUIT) {
                    should_close = true;
                }
            }
        } else if (screen == SCREEN_HELP) {
            if (IsKeyPressed(KEY_BACKSPACE) || IsKeyPressed(KEY_ESCAPE) || IsKeyPressed(KEY_ENTER) || IsKeyPressed(KEY_KP_ENTER)) {
                screen = SCREEN_MENU;
            }
        } else {
            if (IsKeyPressed(KEY_TAB)) {
                screen = SCREEN_MENU;
            } else {
                game_update(&game, grid_width, grid_height, dt);
            }
        }

        BeginDrawing();
        ClearBackground((Color){15, 23, 42, 255});

        if (screen == SCREEN_MENU) {
            DrawRectangle(60, 70, window_width - 120, window_height - 140, (Color){8, 14, 26, 220});
            DrawRectangleLines(60, 70, window_width - 120, window_height - 140, (Color){80, 115, 160, 255});

            DrawText("SNAKE C", 110, 110, 56, (Color){76, 201, 240, 255});
            DrawText("Menu principal", 112, 168, 28, RAYWHITE);

            Color c_start = (selected_menu_item == MENU_START) ? (Color){150, 255, 160, 255} : (Color){210, 220, 235, 255};
            Color c_diff = (selected_menu_item == MENU_DIFFICULTY) ? (Color){255, 215, 0, 255} : (Color){210, 220, 235, 255};
            Color c_challenge = (selected_menu_item == MENU_CHALLENGE) ? (Color){255, 215, 0, 255} : (Color){210, 220, 235, 255};
            Color c_help = (selected_menu_item == MENU_HELP) ? (Color){150, 210, 255, 255} : (Color){210, 220, 235, 255};
            Color c_quit = (selected_menu_item == MENU_QUIT) ? (Color){255, 130, 130, 255} : (Color){210, 220, 235, 255};

            DrawText(TextFormat("%s Jouer", selected_menu_item == MENU_START ? ">" : " "), 120, 240, 34, c_start);
            DrawText(TextFormat("%s Difficulte: %s", selected_menu_item == MENU_DIFFICULTY ? ">" : " ", difficulty_label(menu_difficulty)),
                     120,
                     290,
                     34,
                     c_diff);
            DrawText(TextFormat("%s Challenge 60s: %s", selected_menu_item == MENU_CHALLENGE ? ">" : " ", menu_challenge_mode ? "ON" : "OFF"),
                     120,
                     340,
                     34,
                     c_challenge);
            DrawText(TextFormat("%s Help (commandes)", selected_menu_item == MENU_HELP ? ">" : " "), 120, 390, 34, c_help);
            DrawText(TextFormat("%s Quitter", selected_menu_item == MENU_QUIT ? ">" : " "), 120, 440, 34, c_quit);

            DrawText("Haut/Bas: naviguer | Entree: valider", 110, 510, 24, (Color){186, 200, 220, 255});
            DrawText(TextFormat("Meilleur score: %d", game.best_score), 110, 545, 24, GOLD);
        } else if (screen == SCREEN_HELP) {
            DrawRectangle(60, 70, window_width - 120, window_height - 140, (Color){8, 14, 26, 220});
            DrawRectangleLines(60, 70, window_width - 120, window_height - 140, (Color){80, 115, 160, 255});

            DrawText("HELP - COMMANDES", 110, 110, 46, (Color){150, 210, 255, 255});
            DrawText("En jeu:", 110, 190, 30, RAYWHITE);
            DrawText("- Fleches : bouger", 130, 235, 28, (Color){210, 220, 235, 255});
            DrawText("- P : pause", 130, 273, 28, (Color){210, 220, 235, 255});
            DrawText("- R : recommencer", 130, 311, 28, (Color){210, 220, 235, 255});
            DrawText("- ENTREE : recommencer apres defaite", 130, 349, 28, (Color){210, 220, 235, 255});
            DrawText("- TAB : retour menu", 130, 387, 28, (Color){210, 220, 235, 255});
            DrawText("- ESC : quitter", 130, 425, 28, (Color){210, 220, 235, 255});

            DrawText("BACKSPACE / ESC / ENTREE : retour menu", 110, 525, 24, (Color){186, 200, 220, 255});
        } else {
            game_draw(&game, grid_width, grid_height, cell_size);

            DrawRectangle(0, grid_height * cell_size, window_width, ui_height, (Color){8, 14, 26, 255});
            DrawText(TextFormat("Score: %d", game.score), 16, grid_height * cell_size + 12, 28, RAYWHITE);
            DrawText(TextFormat("Best: %d", game.best_score), 220, grid_height * cell_size + 12, 28, GOLD);
            if (game.challenge_mode) {
                DrawText(TextFormat("Time: %.0f", game.challenge_time_left), 390, grid_height * cell_size + 12, 28, (Color){255, 190, 70, 255});
            }
            DrawText("Fleches: bouger | P: pause | R: restart | Entree: restart KO | TAB: menu | ESC: quitter",
                     16,
                     grid_height * cell_size + 42,
                     18,
                     (Color){186, 200, 220, 255});
        }

        EndDrawing();
    }

    game_shutdown(&game);
    CloseWindow();

    return 0;
}
