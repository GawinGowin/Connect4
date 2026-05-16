#include "connect4.h"
#include "libft.h"

int main() {
  t_board board = {.cols = 7, .rows = 6, .grid = {}, .stack_top = {}, .moves_count = 0};

  draw_board(&board);
  ft_printf("\n");
  board_drop(&board, 3, CELL_P1);
  board_drop(&board, 4, CELL_P2);
  board_drop(&board, 3, CELL_P1);
  draw_board(&board);
  ft_printf("\n");
  board_undo(&board, 3);
  draw_board(&board);
  ft_printf("\n");

  board_drop(&board, 3, CELL_P1);
  int row;
  row = board_drop(&board, 3, CELL_P1);
  draw_board(&board);
  ft_printf("win: %d\n", board_check_win(&board, row, 3));
  row = board_drop(&board, 3, CELL_P1);
  draw_board(&board);
  ft_printf("win: %d\n", board_check_win(&board, row, 3));
  return (0);
}
