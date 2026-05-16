#include "connect4.h"
#include "libft.h"

int main(int argc, char **argv) {
  t_args args = {};
  t_board board = {.cols = 7, .rows = 6, .grid = {}, .stack_top = {}, .moves_count = 0};

  t_cell next_palyer = CELL_P1; // TODO: select randomly

  t_parse_err err = parse_args(argc, argv, &args);
  if (err) {
    print_usage(argv[0], err);
    return 1;
  }
  board_init(&board, &args);

  while (1) {
    draw_board(&board);
    int col = -1;
    while (next_palyer == CELL_P1 && col < 0) {
      ft_printf("Player %d: ", next_palyer);
      col = input_terminal(&board);
      if (col == -1) {
        ft_printf("\nGame Exited\n");
        return 0;
      } else if (col == -2) {
        continue;
      }
    }
    if (next_palyer == CELL_P2) {
      col = ai_choose_move(&board, CELL_P2);
      if (col < 0) {
        ft_printf("something wrong\n");
        return 1;
      }
      ft_printf("Player %d: %d\n", next_palyer, col);
    }
    int row = board_drop(&board, col, next_palyer);
    if (board_check_win(&board, row, col) > 0) {
      draw_board(&board);
      ft_printf("Player: %d won!\n", next_palyer);
      break;
    }
    if (board_is_full(&board)) {
      draw_board(&board);
      ft_printf("It's a draw!\n");
      return (0);
    }

    if (next_palyer == CELL_P1) {
      next_palyer = CELL_P2;
    } else if (next_palyer == CELL_P2) {
      next_palyer = CELL_P1;
    }
  }
  return (0);
}
