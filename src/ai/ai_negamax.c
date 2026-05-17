#include "connect4.h"

#include <limits.h>
#include <time.h>

static int negamax(
    t_board *b,
    int depth,
    int alpha,
    int beta,
    t_cell player_mark,
    const int *order,
    time_t start,
    int *timed_out);

int ai_negamax(t_board *b, t_cell player_mark) {
  int remaining = b->rows * b->cols - b->moves_count;
  int order[MAX_COLS];

  build_order_array(order, b->cols, MAX_COLS);
  int best_col = order[0];

  time_t start = time(NULL);
  int timed_out = 0;

  for (int depth = 1; depth <= remaining; depth++) {
    if (time(NULL) - start >= AI_TIMEOUT_S)
      break;
    timed_out = 0;
    int best_score = INT_MIN + 1;
    int depth_best = best_col;

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
      int score = -negamax(
          b, depth - 1, INT_MIN + 1, INT_MAX, OPPONENT(player_mark), order, start, &timed_out);
      board_undo(b, col);
      if (timed_out)
        break;
      if (score > best_score) {
        best_score = score;
        depth_best = col;
      }
    }
    if (timed_out)
      break;
    best_col = depth_best;
    if (best_score >= WIN_SCORE - depth)
      break;
  }
  return best_col;
}

static int negamax(
    t_board *b,
    int depth,
    int alpha,
    int beta,
    t_cell player_mark,
    const int *order,
    time_t start,
    int *timed_out) {
  t_cell opponent_mark = OPPONENT(player_mark);

  if (time(NULL) - start >= AI_TIMEOUT_S) {
    *timed_out = 1;
    return 0;
  }
  if (board_is_full(b))
    return 0;
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
      score = -negamax(b, depth - 1, -beta, -alpha, opponent_mark, order, start, timed_out);
    board_undo(b, col);

    if (*timed_out)
      return 0;
    if (score > alpha)
      alpha = score;
    if (alpha >= beta)
      break;
  }
  return alpha;
}
