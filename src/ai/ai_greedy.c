#include "connect4.h"

static int check_instant_win(t_board *b, t_cell player_mark);
static int build_order_array(int *array, int cols, int max_cols);

int ai_greedy(t_board *b, t_cell player_mark) {
  t_cell opponent_mark = OPPONENT(player_mark);
  int order[MAX_COLS] = {};
  build_order_array((int *)order, b->cols, MAX_COLS);

  int next_col;
  // check ai's instant win
  next_col = check_instant_win(b, player_mark);
  if (next_col >= 0) {
    return next_col;
  }

  // check opponent's instant win
  next_col = check_instant_win(b, opponent_mark);
  if (next_col >= 0) {
    return next_col;
  }

  // check 2 moves future
  for (int i = 0; i < b->cols; i++) {
    int col = order[i];
    if (b->stack_top[col] >= b->rows) {
      continue;
    }
    board_drop(b, col, player_mark);
    int gift = 0;

    int opp_next_col = check_instant_win(b, opponent_mark);
    if (opp_next_col >= 0) {
      gift = 1;
    }
    board_undo(b, col);
    if (!gift) {
      return col;
    }
  }
  // when all moves are gifts for opponent
  for (int i = 0; i < b->cols; i++) {
    int col = order[i];
    if (b->stack_top[col] < b->rows) {
      return col;
    }
  }
  // something wrong
  return -1;
}

static int check_instant_win(t_board *b, t_cell player_mark) {
  for (int col = 0; col < b->cols; col++) {
    if (b->stack_top[col] >= b->rows) {
      continue;
    }
    int row = board_drop(b, col, player_mark);
    int is_win = board_check_win(b, row, col);
    board_undo(b, col);
    if (is_win) {
      return col;
    }
  }
  return -1;
}
