#ifndef CONNECT4_H
#define CONNECT4_H

#define MAX_ROWS 128
#define MAX_COLS 128

typedef enum e_cell { CELL_EMPTY = 0, CELL_P1 = 1, CELL_P2 = 2 } t_cell;

typedef struct s_board {
  t_cell grid[MAX_ROWS][MAX_COLS];
  int rows;
  int cols;
  int stack_top[MAX_COLS];
  int moves_count;
} t_board;

typedef struct s_player {
  t_cell mark;
  int is_ai;
} t_player;

typedef struct s_io {
  void (*draw_board)(t_board *);
  int (*get_input)(t_board *);
  void (*show_result)(const char *);
} t_io;

typedef struct s_args {
  long rows;
  long cols;
  int opt_gui;
} t_args;

typedef enum e_parse_err {
  PARSE_OK = 0,
  PARSE_USAGE,
  PARSE_NOT_DIGIT,
  PARSE_NEGATIVE,
  PARSE_TOO_SMALL,
  PARSE_UNKNOWN_OPT
} t_parse_err;

int board_drop(t_board *b, int col, t_cell mark);
int board_undo(t_board *b, int col);
int board_is_full(t_board *b);

int board_check_win(t_board *board, int last_row, int last_col);

int input_terminal(t_board *b);

void draw_board(t_board *b);

int ai_choose_move(t_board *board, t_cell player_mark);
int ai_greedy(t_board *b, t_cell player_mark);

#endif /* CONNECT4_H */
