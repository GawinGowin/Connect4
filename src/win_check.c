#include "connect4.h"

static int count_dir(t_board *b, int r, int c, t_cell mark, int dr, int dc);

int board_check_win(t_board *b, int last_row, int last_col) {
  if (last_row < 0 || last_row >= b->rows || last_col < 0 || last_col >= b->cols) {
    return (-1);
  }

  t_cell mark = b->grid[last_row][last_col];

  if (1 + count_dir(b, last_row, last_col, mark, 0, 1) +
          count_dir(b, last_row, last_col, mark, 0, -1) >=
      4)
    return 1;
  if (1 + count_dir(b, last_row, last_col, mark, 1, 0) +
          count_dir(b, last_row, last_col, mark, -1, 0) >=
      4)
    return 1;
  if (1 + count_dir(b, last_row, last_col, mark, 1, 1) +
          count_dir(b, last_row, last_col, mark, -1, -1) >=
      4)
    return 1;
  if (1 + count_dir(b, last_row, last_col, mark, 1, -1) +
          count_dir(b, last_row, last_col, mark, -1, 1) >=
      4)
    return 1;
  return 0;
}

static int count_dir(t_board *b, int r, int c, t_cell mark, int dr, int dc) {
  int n = 0;
  r += dr;
  c += dc;
  while (r >= 0 && r < b->rows && c >= 0 && c < b->cols && b->grid[r][c] == mark) {
    n++;
    r += dr;
    c += dc;
  }
  return n;
}
