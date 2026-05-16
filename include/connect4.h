#ifndef CONNECT4_H
#define CONNECT4_H

#define MAX_ROWS 128
#define MAX_COLS 128

typedef enum e_cell { CELL_EMPTY = 0, CELL_P1 = 1, CELL_P2 = 2 } t_cell;

typedef struct s_board {
  t_cell **grid;
  int rows;
  int cols;
  int *stack_top;
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

#endif /* CONNECT4_H */
