#include "connect4.h"

int ai_choose_move(t_board *board, t_cell player_mark) { return ai_negamax(board, player_mark); }
