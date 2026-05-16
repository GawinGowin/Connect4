#include "connect4.h"
#include "libft.h"

void board_init(t_board *b, t_args *args) {
  ft_memset(b, 0, sizeof(*b));
  b->rows = args->rows;
  b->cols = args->cols;
}

int board_drop(t_board *b, int col, t_cell mark) {
  if (col < 0 || col >= b->cols || b->stack_top[col] >= b->rows) {
    return (-1);
  }
  int row = b->stack_top[col];

  b->grid[row][col] = mark;
  b->stack_top[col]++;
  b->moves_count++;

  return row;
}

int board_undo(t_board *b, int col) {
  if (col < 0 || col >= b->cols || b->stack_top[col] <= 0) {
    return (-1);
  }
  b->stack_top[col]--;
  int row = b->stack_top[col];
  b->grid[row][col] = CELL_EMPTY;
  b->moves_count--;
  return (row);
}

int board_is_full(t_board *b) { return b->moves_count >= b->rows * b->cols; }
