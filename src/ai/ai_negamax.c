#include "connect4.h"

#include <limits.h>

static int negamax(t_board *b, int depth, t_cell player_mark);

int ai_negamax(t_board *b, t_cell player_mark) {
  t_cell opponent_mark = OPPONENT(player_mark);
  int remaining = b->rows * b->cols - b->moves_count;
  int depth = MIN(6, remaining);
  int best_score = INT_MIN;
  int best_col = -1;

  for (int col = 0; col < b->cols; col++) {
    if (b->stack_top[col] >= b->rows)
      continue;
    board_drop(b, col, player_mark);
    int score = -negamax(b, depth - 1, opponent_mark);
    board_undo(b, col);
    if (score > best_score) {
      best_score = score;
      best_col = col;
    }
  }
  return best_col;
}

static int negamax(t_board *b, int depth, t_cell player_mark) {
  t_cell opponent_mark = OPPONENT(player_mark);
  int best_score = INT_MIN;
  if (depth == 0 || board_is_full(b)) {
    return ai_evaluate(b, player_mark);
  }
  for (int col = 0; col < b->cols; col++) {
    if (b->stack_top[col] >= b->rows) {
      continue;
    }
    board_drop(b, col, player_mark);
    int score = -negamax(b, depth - 1, opponent_mark);
    board_undo(b, col);
    best_score = MAX(best_score, score);
  }
  return best_score;
}
