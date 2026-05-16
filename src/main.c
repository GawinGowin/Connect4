#include "connect4.h"
#include "libft.h"

int main() {
  t_board board = {.cols = 7, .rows = 6, .grid = {}, .stack_top = {}, .moves_count = 0};

  t_cell next_palyer = CELL_P1;

  while (1) {
    draw_board(&board);
    int col = -1;
    while (col < 0) {
      ft_printf("Player %d: ", next_palyer);
      col = input_terminal(&board);
      if (col == -1) {
        ft_printf("\nGame Exited\n");
        return 0;
      } else if (col == -2) {
        continue;
      }
    }

    int row = board_drop(&board, col, next_palyer);

    if (board_check_win(&board, row, col)) {
      ft_printf("Player: %d won!\n", next_palyer);
      break;
    }

    if (next_palyer == CELL_P1) {
      next_palyer = CELL_P2;
    } else if (next_palyer == CELL_P2) {
      next_palyer = CELL_P1;
    }
  }
  return (0);
}
