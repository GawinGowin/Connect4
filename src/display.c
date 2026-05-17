#include "connect4.h"
#include "libft.h"

static char cell_char(t_cell cell);
static int count_digits(int n);
static void print_num_padded(int n, int w);

void draw_board(t_board *b) {
  int w = count_digits(b->cols - 1);

  for (int row = b->rows - 1; row >= 0; row--) {
    for (int col = 0; col < b->cols; col++) {
      for (int i = 1; i < w; i++)
        write(STDOUT_FILENO, " ", 1);
      ft_printf("%c", cell_char(b->grid[row][col]));
      write(STDOUT_FILENO, " ", 1);
    }
    ft_printf("\n");
  }
  for (int col = 0; col < b->cols; col++) {
    print_num_padded(col, w);
    write(STDOUT_FILENO, " ", 1);
  }
  ft_printf("\n");
}

static int count_digits(int n) {
  int d = 1;
  while (n >= 10) {
    d++;
    n /= 10;
  }
  return d;
}

static void print_num_padded(int n, int w) {
  int pad = w - count_digits(n);
  while (pad-- > 0)
    write(STDOUT_FILENO, " ", 1);
  ft_printf("%d", n);
}

static char cell_char(t_cell cell) { return (cell == CELL_P1 ? 'X' : cell == CELL_P2 ? 'O' : '.'); }