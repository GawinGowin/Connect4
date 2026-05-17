#include "connect4.h"

int ai_choose_move(t_board *board, t_cell player_mark) {
  if (board->cols < 8 && board->rows < 8) {
    return ai_negamax(board, player_mark);
  }
  return ai_greedy(board, player_mark);
}
