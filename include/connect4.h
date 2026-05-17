#ifndef CONNECT4_H
#define CONNECT4_H

#define MAX_ROWS 128
#define MAX_COLS 128

#define OPPONENT(player) (player == CELL_P1) ? CELL_P2 : CELL_P1;

// CELL_P1: Human
// CELL_P2: AI
typedef enum e_cell { CELL_EMPTY = 0, CELL_P1 = 1, CELL_P2 = 2 } t_cell;

typedef struct s_board {
  t_cell grid[MAX_ROWS][MAX_COLS];
  int rows;
  int cols;
  int stack_top[MAX_COLS];
  int moves_count;
} t_board;

typedef struct s_args {
  int rows;
  int cols;
} t_args;

typedef enum e_parse_err {
  PARSE_OK = 0,
  PARSE_USAGE,
  PARSE_NOT_DIGIT,
  PARSE_NEGATIVE,
  PARSE_TOO_SMALL,
  PARSE_TOO_BIG,
} t_parse_err;

t_parse_err parse_args(int argc, char **argv, t_args *ret);
void print_usage(char *program, t_parse_err err);

void board_init(t_board *b, t_args *args);
int board_drop(t_board *b, int col, t_cell mark);
int board_undo(t_board *b, int col);
int board_is_full(t_board *b);

int board_check_win(t_board *board, int last_row, int last_col);

int input_terminal(t_board *b);

void draw_board(t_board *b);

int ai_choose_move(t_board *board, t_cell player_mark);
int ai_greedy(t_board *b, t_cell player_mark);
int build_order_array(int *array, int cols, int max_cols);

#endif /* CONNECT4_H */
