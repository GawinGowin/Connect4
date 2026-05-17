#include "connect4.h"

#include <limits.h>

#define WIN_SCORE 100000000

static int negamax(t_board *b, int depth, t_cell player_mark, const int *order);

int ai_negamax(t_board *b, t_cell player_mark) {
  t_cell opponent_mark = OPPONENT(player_mark);
  int remaining = b->rows * b->cols - b->moves_count;
  int depth = MIN(6, remaining);
  int best_score = INT_MIN;
  int best_col = -1;
  int order[MAX_COLS];

  build_order_array(order, b->cols, MAX_COLS);
  for (int i = 0; i < b->cols; i++) {
    int col = order[i];
    if (b->stack_top[col] >= b->rows)
      continue;
    int last_row = b->stack_top[col];
    board_drop(b, col, player_mark);
    if (board_check_win(b, last_row, col)) {
      board_undo(b, col);
      return col;
    }
    int score = -negamax(b, depth - 1, opponent_mark, order);
    board_undo(b, col);
    if (score > best_score) {
      best_score = score;
      best_col = col;
    }
  }
  return best_col;
}

static int negamax(t_board *b, int depth, t_cell player_mark, const int *order) {
  t_cell opponent_mark = OPPONENT(player_mark);

  if (board_is_full(b))
    return 0;
  int best_score = -WIN_SCORE;
  for (int i = 0; i < b->cols; i++) {
    int col = order[i];
    if (b->stack_top[col] >= b->rows)
      continue;
    int last_row = b->stack_top[col];
    board_drop(b, col, player_mark);
    int score;
    if (board_check_win(b, last_row, col))
      score = WIN_SCORE;
    else if (depth == 0)
      score = ai_evaluate(b, player_mark);
    else
      score = -negamax(b, depth - 1, opponent_mark, order);
    board_undo(b, col);
    if (score > best_score)
      best_score = score;
  }
  return best_score;
}
