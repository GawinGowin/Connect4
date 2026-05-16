#include "connect4.h"
#include "libft.h"

static char cell_char(t_cell cell);

void draw_board(t_board *b) {
  for (int row = b->rows - 1; row >= 0; row--) {
    for (int col = 0; col < b->cols; col++)
      ft_printf("%c ", cell_char(b->grid[row][col]));
    ft_printf("\n");
  }
  for (int col = 0; col < b->cols; col++)
    ft_printf("%d ", col);
  ft_printf("\n");
}

static char cell_char(t_cell cell) { return (cell == CELL_P1 ? 'X' : cell == CELL_P2 ? 'O' : '.'); }